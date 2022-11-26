local fifo = require "extlibs://fifo";

local TaskManagerContext = class();

function TaskManagerContext:_init(task_manager)
    self.task_manager = task_manager;
end

function TaskManagerContext:wake(co)
    co = co or coroutine.running();
    local task_instance = self.task_manager.tasks[co];
    self.task_manager.tasks_to_resume:push(task_instance);
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
            getmetatable(ref.listener):clean();
        end);
        local event_callback = ...;
        ref.callback = function(evt)
            if event_callback and not event_callback(evt) then
                return;
            end
            ctx:wake(co);
            getmetatable(ref.listener):clean();
        end
        ref.listener = self.task_manager.listen(
            condition, ref.callback, listener_id
        );
    elseif type(condition) == "function" then
        -- Arbitrary conditional continuation function
        local listener_id = "taskwaitfor.funccondition";
        local ref = {};
        task:on_clean(function()
            getmetatable(ref.listener):clean();
        end);
        ref.listener = self.task_manager.listen(
            "Event.Game.Update", function(evt)
                if condition(evt) then
                    ctx:wake(co);
                    getmetatable(ref.listener):clean();
                end
            end, listener_id
        );
    elseif type(condition) == "table" then
        local condition_mt = getmetatable(condition);
        if condition._type == "Task" then
            local tskmgr = self.task_manager;
            -- Tasks
            local task_instance = condition:make_task_instance();
            task_instance:on_complete(function(object)
                ctx:wake(co);
            end);
            task_instance(...);
        elseif condition_mt and condition_mt.event_id then
            -- Events in hook form
            return self:wait_for(condition_mt.event_id, ...);
        else
            error(("unsupported arbitrary table for wait_for condition (%s)"):format(condition));
        end
    else
        error(("unsupported type for wait_for condition (%s)"):format(type(condition)));
    end

    return coroutine.yield(co)
end

-- TaskInstance
local TaskInstance = class();
TaskInstance._type = "TaskInstance";

function TaskInstance:_init(task)
    self.task = task;
    self.name = ("%s.%s"):format(task.name, task.task_instance_counter);
    task.task_instance_counter = task.task_instance_counter + 1;
    self.co = coroutine.create(self.task.func);
    self.on_complete_callbacks = {};
    self.on_clean_callbacks = {};
    self.on_resume_behaviour = nil;
    self.task.task_manager.tasks[self.co] = self;
end

function TaskInstance:__call(...)
    return self.task.task_manager:_resume(self, ...)
end

function TaskInstance:set_resume_behaviour(behaviour)
    if type(behaviour) ~= "function" then
        error(("argument #1: behaviour must be a function (got %s)"):format(type(behaviour)));
    end
    self.on_resume_behaviour = behaviour;
end

function TaskInstance:on_complete(callback)
    if type(callback) ~= "function" then
        error(("argument #1: callback must be a function (got %s)"):format(type(callback)));
    end
    table.insert(self.on_complete_callbacks, callback);
end

function TaskInstance:on_clean(callback)
    if type(callback) ~= "function" then
        error(("argument #1: callback must be a function (got %s)"):format(type(callback)));
    end
    table.insert(self.on_clean_callbacks, callback);
end

function TaskInstance:complete()
    for _, on_complete_func in pairs(self.on_complete_callbacks) do
        on_complete_func(self);
    end
end

function TaskInstance:resume(...)
    if self.on_resume_behaviour then
        return self.on_resume_behaviour(self, ...);
    end
    return coroutine.resume(self.co, self.task.task_manager.ctx, ...)
end

-- Task
local Task = class();
Task._type = "Task";

function Task:_init(task_manager, func, name)
    self.task_manager = task_manager;
    self.func = func;
    self.name = name or "anonymous_task";
    self.instances = {};
    self.task_instance_counter = 1;
end

function Task:__call(...)
    local task_instance = TaskInstance(self);
    return task_instance(...);
end

function Task:make_task_instance()
    return TaskInstance(self);
end

function Task:clean()
    for _, on_clean_func in pairs(self.on_clean_callbacks) do
        on_clean_func(self);
    end
    if self.co then
        coroutine.close(self.co);
    end
end

-- TaskManager
local TaskManager = class();

function TaskManager:_init(event_functions)
    self.listen = event_functions.listen;
    self.unlisten = event_functions.unlisten;
    self.schedule = event_functions.schedule;
    self.task_count = 0;
    self.listener_pump = nil;
    self.tasks_to_resume = fifo();
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
    if self.listener_pump == nil and self.task_count >= 1 then
        self.listener_pump = self.listen(
            "Event.Game.Update", function()
                while #task_manager.tasks_to_resume > 0 do
                    local task_to_resume = task_manager.tasks_to_resume:pop();
                    task_manager:_resume(task_to_resume);
                end
            end, "TaskManagerPump"
        );
    elseif self.listener_pump and self.task_count < 1 then
        self.unlisten(self.listener_pump);
        self.listener_pump = nil;
    end
    return self.listener_pump;
end

function TaskManager:_resume(task, ...)
    local results = {task:resume(...)};
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
                mt._storage[key] = task;
                self.task_count = self.task_count + 1;
                self:_create_or_delete_pump();
                return task;
            elseif type(value) == "nil" then
                local mt = getmetatable(object);
                local task = mt._storage[key];

                local do_not_resume = {};
                for idx, task_to_resume in pairs(task_manager.tasks_to_resume) do
                    if task == task_to_resume then
                        table.insert(do_not_resume, 1, idx);
                    end
                end
                for _, idx in pairs(do_not_resume) do
                    self.tasks_to_resume:remove(idx);
                end
                coroutine.close(task.co);
                task_manager.tasks[task.co] = nil;
                mt._storage[key] = nil;
                self.task_count = self.task_count - 1;
                self:_create_or_delete_pump();
            end
        end,
        __index = function(object, key)
            local mt = getmetatable(object);
            if mt._storage[key] then
                return mt._storage[key];
            else
                error(("Task '%s' is not defined"):format(key));
            end
        end,
        __call = function(object, func)
            local mt = getmetatable(object);
            local task = self:_make_task(func);
            table.insert(mt._storage, task);
            self.task_count = self.task_count + 1;
            self:_create_or_delete_pump();
            return task;
        end,
        _storage = {}
    };
    return setmetatable({}, hook_mt);
end

return {TaskManager = TaskManager};
