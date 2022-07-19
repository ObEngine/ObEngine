#include <platformfolders/platform_folders.h>
#include <vili/parser.hpp>
#include <vld8/exceptions.hpp>
#include <vld8/validator.hpp>

#include <Config/Validators.hpp>
#include <Debug/Logger.hpp>
#include <System/Path.hpp>
#include <System/Project.hpp>
#include <Utils/FileUtils.hpp>

namespace obe::system::project
{
    std::string get_project_location(const std::string& project_name)
    {
        if (project_exists(project_name))
        {
            const std::string projects_file_location = "obe://projects.vili"_fs;
            return vili::parser::from_file(projects_file_location).at(project_name).at("path");
        }
        throw exceptions::UnknownProject(project_name, list_projects(), EXC_INFO);
    }

    bool project_exists(const std::string& project_name)
    {
        const std::string projects_file_location = "obe://projects.vili"_fs;
        return vili::parser::from_file(projects_file_location).contains(project_name);
    }

    bool load(
        const std::string& project_name, const std::string& prefix, const unsigned int priority)
    {
        debug::Log->info(
            "<Project> Loading Project '{0}' with priority {1}", project_name, priority);
        if (project_exists(project_name))
        {
            const std::string project_location = get_project_location(project_name);
            MountablePath::mount(MountablePath(
                MountablePathType::Project, project_location, prefix, priority, true));

            Project project;
            project.load_from_file(Path(project_location).add("project.vili"));
            project.mount();

            std::string project_cfg_path;
            if (project.is_standalone())
            {
                std::string cfg_path = sago::getConfigHome();
                project_cfg_path = utils::file::join({ cfg_path, project.get_id() });
            }
            else
            {
                std::string cfg_path
                    = MountablePath::from_prefix(obe::system::prefixes::cfg.data()).base_path;
                project_cfg_path = utils::file::join({ cfg_path, "Projects", project.get_id() });
            }
            if (!utils::file::directory_exists(project_cfg_path))
            {
                debug::Log->debug("<Project> Could not find Project configuration directory, "
                                  "creating a new one...");
                utils::file::create_directory(project_cfg_path);
                debug::Log->debug(
                    "<Project> Project configuration directory created at '{}'", project_cfg_path);
            }
            const MountablePath project_cfg(
                MountablePathType::Path, project_cfg_path, "projectcfg", priorities::projectmount);
            MountablePath::mount(project_cfg);
            return true;
        }
        throw exceptions::UnknownProject(project_name, list_projects(), EXC_INFO);
    }

    std::vector<std::string> list_projects()
    {
        const std::string projects_file_location = "obe://projects.vili"_fs;
        vili::node projects = vili::parser::from_file(projects_file_location);
        std::vector<std::string> projects_names;
        for (const auto& [project_name, _] : projects.items())
        {
            projects_names.push_back(project_name);
        }
        return projects_names;
    }

    vili::node ProjectURLs::schema() const
    {
        return vili::object {};
    }

    vili::node ProjectURLs::dump() const
    {
        return vili::object { { "homepage", homepage }, { "issues", issues }, { "readme", readme },
            { "documentation", documentation }, { "license", license } };
    }

    void ProjectURLs::load(const vili::node& data)
    {
        if (data.contains("homepage"))
        {
            homepage = data.at("homepage");
        }
        if (data.contains("issues"))
        {
            issues = data.at("issues");
        }
        if (data.contains("readme"))
        {
            readme = data.at("readme");
        }
        if (data.contains("documentation"))
        {
            documentation = data.at("documentation");
        }
        if (data.contains("license"))
        {
            license = data.at("license");
        }
    }

    vili::node Project::dump() const
    {
        vili::node mount_dump = vili::object {};
        for (const auto& mount : m_mounts)
        {
            // TODO: handle priorities...
            mount_dump.emplace(mount->prefix, mount->base_path);
        }

        // clang-format off
        return vili::object {
            { "id", m_id },
            { "name", m_name },
            { "authors", vili::array(m_authors.begin(), m_authors.end()) },
            { "description", m_description },
            { "obengine_version", m_obengine_version.string() },
            { "keywords", vili::array(m_keywords.begin(), m_keywords.end()) },
            { "categories", vili::array(m_categories.begin(), m_categories.end()) },
            { "license", m_license },
            { "include", vili::array(m_include.begin(), m_include.end()) },
            { "exclude", vili::array(m_exclude.begin(), m_exclude.end()) },
            { "source", m_source },
            { "urls", m_urls.dump() },
            { "mounts", mount_dump }
        };
        // clang-format on
    }

    void Project::load(const vili::node& data)
    {
        const auto validator = config::validators::project_validator();
        try
        {
            vili::validator::validate_tree(validator, data);

            m_id = data.at("id");
            m_name = data.at("name");
            m_source = data.at("source");
            m_version = data.at("version");
            m_obengine_version = data.at("obengine_version").as_string();

            if (data.contains("standalone"))
            {
                m_standalone = data.at("standalone");
            }
            if (data.contains("authors"))
            {
                for (const auto& author : data.at("authors").as<vili::array>())
                {
                    m_authors.push_back(author);
                }
            }
            if (data.contains("description"))
            {
                m_description = data.at("description");
            }
            if (data.contains("keywords"))
            {
                for (const auto& keyword : data.at("keywords").as<vili::array>())
                {
                    m_keywords.emplace(keyword);
                }
            }
            if (data.contains("categories"))
            {
                for (const auto& category : data.at("categories").as<vili::array>())
                {
                    m_categories.emplace(category);
                }
            }
            if (data.contains("license"))
            {
                m_license = data.at("license");
            }
            if (data.contains("include"))
            {
                for (const auto& include : data.at("include").as<vili::array>())
                {
                    m_include.push_back(include);
                }
            }
            if (data.contains("exclude"))
            {
                for (const auto& exclude : data.at("exclude").as<vili::array>())
                {
                    m_include.push_back(exclude);
                }
            }
            if (data.contains("mounts"))
            {
                for (const auto& [mount_name, mount] : data.at("mounts").items())
                {
                    int priority = priorities::projectmount;
                    bool implicit = false;
                    std::string mount_path;
                    std::string prefix = mount_name;

                    if (mount.is_string())
                    {
                        mount_path = mount;
                    }
                    else if (mount.is_object())
                    {
                        mount_path = mount.at("path");
                        if (mount.contains("priority"))
                        {
                            priority = mount.at("priority");
                        }
                        if (mount.contains("implicit"))
                        {
                            implicit = mount.at("implicit");
                        }
                        if (mount.contains("prefix"))
                        {
                            prefix = mount.at("prefix");
                        }
                    }
                    m_mounts.push_back(std::make_shared<MountablePath>(
                        MountablePathType::Path, mount_path, prefix, priority, implicit, true));
                }
            }
            if (data.contains("urls"))
            {
                m_urls.load(data.at("urls"));
            }
        }
        catch (const vili::exceptions::base_exception& e)
        {
            throw exceptions::InvalidProjectFile("<?>", EXC_INFO).nest(e);
        }
    }

    void Project::mount_defaults()
    {
        const std::string project_root
            = system::Path(system::prefixes::game, ".").find(PathType::Directory).path();

        try
        {
            const MountablePath objects_path(MountablePathType::Path,
                utils::file::join({ project_root, "GameObjects" }), Prefixes::objects,
                priorities::projectmount);
            MountablePath::mount(objects_path, SamePrefixPolicy::Skip);
        }
        catch (const std::exception& exc)
        {
            debug::Log->warn("Unable to find default directory for GameObjects");
        }
        try
        {
            const MountablePath scenes_path(MountablePathType::Path,
                utils::file::join({ project_root, "Scenes" }), Prefixes::scenes,
                priorities::projectmount);
            MountablePath::mount(scenes_path, SamePrefixPolicy::Skip);
        }
        catch (const std::exception& exc)
        {
            debug::Log->warn("Unable to find default directory for Scenes");
        }
    }

    Project::Project()
        : m_obengine_version(0, 1, 0)
    {
    }

    vili::node Project::schema() const
    {
        return vili::object {};
    }

    void Project::load_from_file(const std::string& path)
    {
        const vili::node project = vili::parser::from_file(path);
        try
        {
            this->load(project);
        }
        catch (const exceptions::InvalidProjectFile& e)
        {
            const std::vector<std::runtime_error>& traceback = e.traceback();
            if (!traceback.empty())
            {
                const std::runtime_error& underlying_exception = traceback.back();
                throw exceptions::InvalidProjectFile(path, EXC_INFO).nest(underlying_exception);
            }
            throw exceptions::InvalidProjectFile(path, EXC_INFO);
        }
    }

    void Project::mount()
    {
        for (const auto& mount : m_mounts)
        {
            mount->resolve_base_path();
            MountablePath::mount(*mount);
        }
        this->mount_defaults();
    }

    void Project::unmount() const
    {
        for (const auto& mount : m_mounts)
        {
            MountablePath::unmount(*mount);
        }
    }
    std::string Project::get_id() const
    {
        return m_id;
    }
    bool Project::is_standalone() const
    {
        return m_standalone;
    }
} // namespace obe::system::project
