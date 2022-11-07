local Color = require("Lib/StdLib/ConsoleColor");
local Commands = require("Lib/Toolkit/Commands");
local Style = require("Lib/Toolkit/Stylesheet");
local SampleProjectTemplate = require("Lib/Toolkit/Templates/SampleProject");

local fs = obe.utils.file;

local function is_in_engine_directory()
    return fs.file_exists("projects.vili");
end

local function contains(t, item)
    for _, v in pairs(t) do
        if v == item then
            return true;
        end
    end
    return false;
end

local function get_project_list()
    local project_definition_filepath = obe.system.Path("obe://projects.vili"):find(
        obe.system.PathType.File
    );
    local parser = vili.parser.from_file(project_definition_filepath:path(), vili.parser.state());
    local projects = vili.to_lua(parser);
    local project_list = {};
    for project_name, _ in pairs(projects) do
        table.insert(project_list, project_name);
    end
    return project_list;
end

local function get_non_indexed_projects()
    local lookup_path = fs.get_current_directory();
    if is_in_engine_directory() then
        lookup_path = fs.get_current_directory() .. "/Projects";
    end
    print("Lookup path", lookup_path);
    local all_directories = fs.get_directory_list(lookup_path);
    local indexed_projects = get_project_list();

    local non_indexed_projects = {};
    for _, directory_name in pairs(all_directories) do
        if not contains(indexed_projects, directory_name) then
            if fs.file_exists(directory_name .. "/mount.vili") then
                table.insert(non_indexed_projects, directory_name);
            end
        end
    end
    return non_indexed_projects;
end

local function write_to_file(path, content)
    print("Opening file", path)
    local file_handle = io.open(path, "w");
    if file_handle ~= nil then
        file_handle:write(content);
        file_handle:close();
    else
        error(("failed to write to file at path '%s'"):format(path))
    end
end

local function _mount_(project_name)
    local project_definition_filepath = obe.system.Path("obe://projects.vili"):find(
        obe.system.PathType.File
    );
    local parser = vili.parser.from_file(project_definition_filepath:path(), vili.parser.state());
    local projects = vili.to_lua(parser);
    Color.print(
        {
            {text = "Mounting Project '", color = Style.Execute},
            {text = project_name, color = Style.Project},
            {text = "' ...", color = Style.Execute}
        }, 1
    );
    if projects[project_name] then
        local mount_file = {project = project_name};
        local mount_file_export = vili.writer.dump(
            vili.from_lua(mount_file), vili.writer.dump_options()
        );
        write_to_file("mount.vili", mount_file_export);
        Color.print(
            {
                {text = "Project '", color = Style.Success},
                {text = project_name, color = Style.Project},
                {text = "' has  been successfully mounted !", color = Style.Success}
            }, 2
        );
        obe.system.MountablePath.LoadMountFile();
    else
        Color.print(
            {
                {text = "Project '", color = Style.Error},
                {text = project_name, color = Style.Project},
                {text = "' does not exists", color = Style.Error}
            }, 2
        );
    end
end

local function _create_(project_name)
    local project_definition_filepath = obe.system.Path("obe://projects.vili"):find(
        obe.system.PathType.File
    );
    local parser = vili.parser.from_file(project_definition_filepath:path(), vili.parser.state());
    local projects = vili.to_lua(parser);
    Color.print(
        {
            {text = "Creating Project '", color = Style.Execute},
            {text = project_name, color = Style.Project},
            {text = "' ...", color = Style.Execute}
        }, 1
    );
    if projects[project_name] then
        Color.print(
            {
                {text = "Project '", color = Style.Error},
                {text = project_name, color = Style.Project},
                {text = "' already exists", color = Style.Error}
            }, 2
        );

        return;
    end
    local path = project_name;

    if is_in_engine_directory() then
        path = "Projects/" .. project_name;
    end

    -- Creating the whole project default file structure
    fs.create_directory(path);
    fs.create_directory(path .. "/Data");
    fs.create_directory(path .. "/Data/GameObjects");
    fs.create_directory(path .. "/Data/GameObjects/SampleObject");
    fs.create_directory(path .. "/Scenes");
    fs.create_directory(path .. "/Sprites");
    write_to_file(
        path .. "/Data/GameObjects/SampleObject/SampleObject.lua",
            SampleProjectTemplate.HELLO_WORLD_GO_SCRIPT
    );
    write_to_file(
        path .. "/Data/GameObjects/SampleObject/SampleObject.obj.vili",
            SampleProjectTemplate.HELLO_WORLD_GO_DEF
    );
    write_to_file(path .. "/Scenes/sample.map.vili", SampleProjectTemplate.HELLO_WORLD_SCENE);
    write_to_file(path .. "/boot.lua", SampleProjectTemplate.HELLO_WORLD_BOOT);

    -- Updating projects.vili file
    projects[project_name] = {path = fs.get_current_directory() .. "/" .. path};
    local projects_export = vili.writer.dump(vili.from_lua(projects), vili.writer.dump_options());
    write_to_file(project_definition_filepath:path(), projects_export);

    -- Writing project's mount.vili
    local project_file = {
        id = project_name,
        name = project_name,
        version = "0.1.0",
        obengine_version = "0.5.0",
        source = "",
        mounts = {scenes = "game://Scenes", sprites = "game://Sprites"}
    };
    local project_file_content = vili.writer.dump(
        vili.from_lua(project_file), vili.writer.dump_options()
    );
    write_to_file(path .. "/project.vili", project_file_content);

    Color.print(
        {
            {text = "Project '", color = Style.Success},
            {text = project_name, color = Style.Project},
            {text = "' has  been successfully created !", color = Style.Success}
        }, 2
    );
end

local function _list_()
    local project_list = get_project_list();
    Color.print({{text = "All Registered Projects : ", color = Style.Execute}}, 1);
    for _, project_name in pairs(project_list) do
        Color.print(
            {
                {text = "- Project : ", color = Style.Default},
                {text = project_name, color = Style.Project}
            }, 2
        );
    end
end

local function _index_(project_name)
    local non_indexed_projects = get_non_indexed_projects();
    if contains(non_indexed_projects, project_name) then
        local project_definition_filepath = obe.system.Path("obe://projects.vili"):find(
            obe.system.PathType.File
        );
        local parser = vili.parser
                           .from_file(project_definition_filepath:path(), vili.parser.state());
        local projects = vili.to_lua(parser);

        local path = fs.get_current_directory();
        if is_in_engine_directory() then
            path = path .. "/Projects/" .. project_name;
        else
            path = path .. "/" .. project_name;
        end

        projects[project_name] = {path = path};

        local projects_export = vili.writer
                                    .dump(vili.from_lua(projects), vili.writer.dump_options());
        write_to_file(project_definition_filepath:path(), projects_export)

        Color.print(
            {
                {text = "Project '", color = Style.Success},
                {text = project_name, color = Style.Project},
                {text = "' has  been successfully indexed !", color = Style.Success}
            }, 2
        );
    else
        local existing_projects = get_project_list();
        local directory_not_found = true;
        for _, existing_project in pairs(existing_projects) do
            if existing_project == project_name then
                directory_not_found = false;
                break
            end
        end
        if directory_not_found then
            Color.print(
                {
                    {text = "Directory '", color = Style.Error},
                    {text = project_name, color = Style.Project},
                    {text = "' not found", color = Style.Error}
                }, 2
            );
        else
            Color.print(
                {
                    {text = "Project '", color = Style.Error},
                    {text = project_name, color = Style.Project},
                    {text = "' is already indexed", color = Style.Error}
                }, 2
            );
        end
    end
end

return {
    Commands.help("Commands to work with Projects"),
    create = Commands.command {
        Commands.help("Creates a new Project"),
        project_name = Commands.arg {
            Commands.help("Name of the new Project to create"),
            Commands.call(_create_)
        }
    },
    mount = Commands.command {
        Commands.help("Mounts a Project"),
        project_name = Commands.arg {
            Commands.call(_mount_),
            Commands.help("Name of the Project you want to mount"),
            Commands.autocomplete(get_project_list)
        }
    },
    index = Commands.command {
        Commands.help("Indexes an existing Project"),
        project_name = Commands.arg {
            Commands.call(_index_),
            Commands.help("Name of the directory you want to index as a Project"),
            Commands.autocomplete(get_non_indexed_projects)
        }
    },
    list = Commands.command {Commands.help("Lists all existing Projects"), Commands.call(_list_)}
};
