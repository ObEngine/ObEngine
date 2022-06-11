local TaskManagerContext = class();

function TaskManagerContext:_init(task_manager)
    self.task_manager = task_manager;
end

function TaskManagerContext:wake(co)
    co = co or coroutine.running();
    local task = self.task_manager.tasks[co];
    table.insert(self.task_manager.tasks_to_resume, task);
end

function TaskManagerContext:wait_for(condition, ...)
    local ctx = self;
    local co = coroutine.running();
    local task = self.task_manager.tasks[co];
    assert(co ~= nil, "The main thread cannot wait!");
    if type(condition) == "number" then
        -- Amount of seconds
        local scheduler = Engine.Events:schedule();
        task:on_clean(function()
            scheduler:stop();
        end);
        scheduler:after(condition):run(
            function()
                ctx:wake(co);
            end
        );
    elseif type(condition) == "string" then
        -- Event in string form
        local listener_id = "taskwaitfor." .. condition;
        local ref = {};
        task:on_clean(function()
            getmetatable(ref.hook).clean(ref.hook);
        end);
        local event_callback = ...;
        ref.callback = function(evt)
            if event_callback and not event_callback(evt) then
                return;
            end
            ctx:wake(co);
            getmetatable(ref.hook).clean(ref.hook);
        end
        ref.hook = self.task_manager.listen(
            condition, ref.callback, listener_id
        );
    elseif type(condition) == "function" then
        -- Arbitrary conditional continuation function
        local listener_id = "taskwaitfor.funccondition";
        local ref = {};
        task:on_clean(function()
            getmetatable(ref.hook).clean(ref.hook);
        end);
        ref.hook = self.task_manager.listen(
            "Event.Game.Update", function(evt)
                if condition(evt) then
                    ctx:wake(co);
                    getmetatable(ref.hook).clean(ref.hook);
                end
            end, listener_id
        );
    elseif type(condition) == "table" then
        local condition_mt = getmetatable(condition);
        if condition.__type == "Task" then
            -- Tasks
            condition:on_complete(function(object)
                ctx:wake(co);
            end);
            condition(...);
        elseif condition_mt and condition_mt.event_id then
            -- Events in hook form
            return self:wait_for(condition_mt.event_id, ...);
        else
            error("unsupported wait_for condition");
        end
    else
        error("unsupported wait_for condition");
    end

    return coroutine.yield(co)
end

local Task = class();
Task.__type = "Task";

function Task:_init(task_manager, func, name)
    self.task_manager = task_manager;
    self.func = func;
    self.co = nil;
    self.name = name or "anonymous_task";
    self.on_complete_callbacks = {};
    self.on_clean_callbacks = {};
end

function Task:__call(...)
    local co = coroutine.create(self.func);
    self.task_manager.tasks[co] = self;
    self.co = co;
    return self.task_manager:_resume(self, ...);
end

function Task:on_complete(callback)
    if type(callback) ~= "function" then
        error(("argument #1: callback must be a function (got %s)"):format(type(callback)));
    end
    table.insert(self.on_complete_callbacks, callback);
end

function Task:on_clean(callback)
    if type(callback) ~= "function" then
        error(("argument #1: callback must be a function (got %s)"):format(type(callback)));
    end
    table.insert(self.on_clean_callbacks, callback);
end

function Task:clean()
    for _, on_clean_func in pairs(self.on_clean_callbacks) do
        on_clean_func(self);
    end
    if self.co then
        coroutine.close(self.co);
    end
end

function Task:complete()
    for _, on_complete_func in pairs(self.on_complete_callbacks) do
        on_complete_func(self);
    end
end

local TaskManager = class();

function TaskManager:_init(event_functions)
    self.listen = event_functions.listen;
    self.unlisten = event_functions.unlisten;
    self.schedule = event_functions.schedule;
    self.task_count = 0;
    self.pump_hook = nil;
    self.tasks_to_resume = {};
    self.tasks = {};
    self.ctx = TaskManagerContext(self);
end

function TaskManager:clean()
    for _, task in pairs(self.tasks) do
        task:clean();
    end
end

function TaskManager:_create_or_delete_pump()
    local task_manager = self;
    if self.pump_hook == nil and self.task_count >= 1 then
        self.pump_hook = self.listen(
            "Event.Game.Update", function()
                for _, task in pairs(task_manager.tasks_to_resume) do
                    task_manager:_resume(task);
                end
                task_manager.tasks_to_resume = {};
            end, "TaskManagerPump"
        );
    elseif self.pump_hook and self.task_count < 1 then
        self.unlisten(self.pump_hook);
        self.pump_hook = nil;
    end
    return self.pump_hook;
end

function TaskManager:_resume(task, ...)
    local results = {coroutine.resume(task.co, self.ctx, ...)};
    local ok = results[1];
    if not ok then
        local err = results[2];
        local full_err = ("%s : %s"):format(err, debug.traceback(task.co))
        error(full_err);
    end
    if coroutine.status(task.co) == "dead" then
        task:complete();
        self.tasks[task.co] = nil;
    end
    return table.unpack(results, 2);
end

function TaskManager:_make_task(func, name)
    return Task(self, func, name);
end

function TaskManager:make_task_hook()
    local task_manager = self;
    local hook_mt = {
        __newindex = function(object, key, value)
            if type(value) == "function" then
                local mt = getmetatable(object);
                local task = self:_make_task(value);
                task.name = key;
                mt.__storage[key] = task;
                self.task_count = self.task_count + 1;
                self:_create_or_delete_pump();
                return task;
            elseif type(value) == "nil" then
                local mt = getmetatable(object);
                local task = mt.__storage[key];

                local do_not_resume = {};
                for idx, task_to_resume in pairs(task_manager.tasks_to_resume) do
                    if task == task_to_resume then
                        table.insert(do_not_resume, 1, idx);
                    end
                end
                for _, idx in pairs(do_not_resume) do
                    table.remove(self.tasks_to_resume, idx);
                end
                coroutine.close(task.co);
                task_manager.tasks[task.co] = nil;
                mt.__storage[key] = nil;
                self.task_count = self.task_count - 1;
                self:_create_or_delete_pump();
            end
        end,
        __index = function(object, key)
            local mt = getmetatable(object);
            if mt.__storage[key] then
                return mt.__storage[key];
            else
                error(("Task '%s' is not defined"):format(key));
            end
        end,
        __call = function(object, func)
            local mt = getmetatable(object);
            local task = self:_make_task(func);
            table.insert(mt.__storage, task);
            self.task_count = self.task_count + 1;
            self:_create_or_delete_pump();
            return task;
        end,
        __storage = {}
    };
    return setmetatable({}, hook_mt);
end

return {TaskManager = TaskManager};
