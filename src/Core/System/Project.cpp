#include <vili/parser.hpp>
#include <vld8/exceptions.hpp>
#include <vld8/validator.hpp>

#include <Config/Validators.hpp>
#include <Debug/Logger.hpp>
#include <System/Path.hpp>
#include <System/Project.hpp>
#include <Utils/FileUtils.hpp>

namespace obe::System::Project
{
    std::string GetProjectLocation(const std::string& projectName)
    {
        if (ProjectExists(projectName))
        {
            const std::string projectsFileLocation = "obe://projects.vili"_fs;
            return vili::parser::from_file(projectsFileLocation).at(projectName).at("path");
        }
        throw Exceptions::UnknownProject(projectName, ListProjects(), EXC_INFO);
    }

    bool ProjectExists(const std::string& projectName)
    {
        const std::string projectsFileLocation = "obe://projects.vili"_fs;
        return vili::parser::from_file(projectsFileLocation).contains(projectName);
    }

    bool Load(
        const std::string& projectName, const std::string& prefix, const unsigned int priority)
    {
        Debug::Log->info(
            "<Project> Loading Project '{0}' with priority {1}", projectName, priority);
        if (ProjectExists(projectName))
        {
            const std::string projectLocation = GetProjectLocation(projectName);
            MountablePath::Mount(
                MountablePath(MountablePathType::Project, projectLocation, prefix, priority));
            Project project;
            project.loadFromFile(Path(projectLocation).add("project.vili"));
            project.mount();
            return true;
        }
        throw Exceptions::UnknownProject(projectName, ListProjects(), EXC_INFO);
    }

    std::vector<std::string> ListProjects()
    {
        const std::string projectsFileLocation = "obe://projects.vili"_fs;
        vili::node projects = vili::parser::from_file(projectsFileLocation);
        std::vector<std::string> projectsNames;
        for (auto [projectName, _] : projects.items())
        {
            projectsNames.push_back(projectName);
        }
        return projectsNames;
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
        vili::node mountDump = vili::object {};
        for (const auto& mount : m_mounts)
        {
            // TODO: handle priorities...
            mountDump.emplace(mount->prefix, mount->basePath);
        }

        // clang-format off
        return vili::object {
            { "id", m_id },
            { "name", m_name },
            { "authors", vili::array(m_authors.begin(), m_authors.end()) },
            { "description", m_description },
            { "obengine_version", m_obengineVersion.string() },
            { "keywords", vili::array(m_keywords.begin(), m_keywords.end()) },
            { "categories", vili::array(m_categories.begin(), m_categories.end()) },
            { "license", m_license },
            { "include", vili::array(m_include.begin(), m_include.end()) },
            { "exclude", vili::array(m_exclude.begin(), m_exclude.end()) },
            { "source", m_source },
            { "urls", m_urls.dump() },
            { "mounts", mountDump }
        };
        // clang-format on
    }

    void Project::load(const vili::node& data)
    {
        const auto validator = Config::Validators::ProjectValidator();
        try
        {
            vili::validator::validate_tree(validator, data);

            m_id = data.at("id");
            m_name = data.at("name");
            m_source = data.at("source");
            m_version = data.at("version");
            m_obengineVersion = data.at("obengine_version").as_string();

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
                for (const auto& [mountName, mount] : data.at("mounts").items())
                {
                    int priority = Priorities::projectmount;
                    bool implicit = false;
                    std::string mountPath;
                    std::string prefix = mountName;

                    if (mount.is_string())
                    {
                        mountPath = mount;
                    }
                    else if (mount.is_object())
                    {
                        mountPath = mount.at("path");
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
                    auto [_, pathPrefix] = splitPathAndPrefix(mountPath, false);
                    if (!pathPrefix.empty())
                    {
                        mountPath = System::Path(mountPath).find(PathType::Directory).path();
                    }
                    m_mounts.push_back(std::make_shared<MountablePath>(
                        MountablePathType::Path, mountPath, prefix, priority, implicit));
                }
            }
            if (data.contains("urls"))
            {
                m_urls.load(data.at("urls"));
            }
        }
        catch (const vili::exceptions::base_exception& e)
        {
            throw Exceptions::InvalidProjectFile("<?>", EXC_INFO).nest(e);
        }
    }

    void Project::mountDefaults()
    {
        const std::string projectRoot
            = System::Path(System::Prefixes::root, ".").find(PathType::Directory).path();

        try
        {
            const MountablePath objectsPath(MountablePathType::Path,
                Utils::File::join({ projectRoot, "GameObjects" }), Prefixes::objects,
                Priorities::projectmount);
            MountablePath::Mount(objectsPath, SamePrefixPolicy::Skip);
        }
        catch (const std::exception& exc)
        {
            Debug::Log->error("Unable to find directory for GameObjects");
        }
        try
        {
            const MountablePath scenesPath(MountablePathType::Path,
                Utils::File::join({ projectRoot, "Scenes" }), Prefixes::objects,
                Priorities::projectmount);
            MountablePath::Mount(scenesPath, SamePrefixPolicy::Skip);
        }
        catch (const std::exception& exc)
        {
            Debug::Log->error("Unable to find directory for Scenes");
        }
    }

    Project::Project()
        : m_obengineVersion(0, 1, 0)
    {
    }

    void Project::loadFromFile(const std::string& path)
    {
        vili::node project = vili::parser::from_file(path);
        try
        {
            this->load(project);
        }
        catch (const Exceptions::InvalidProjectFile& e)
        {
            const std::vector<std::runtime_error>& traceback = e.traceback();
            if (!traceback.empty())
            {
                const std::runtime_error underlying_exception = traceback.back();
                throw Exceptions::InvalidProjectFile(path, EXC_INFO).nest(underlying_exception);
            }
            throw Exceptions::InvalidProjectFile(path, EXC_INFO);
        }
    }

    void Project::mount()
    {
        for (const auto& mount : m_mounts)
        {
            MountablePath::Mount(*mount);
        }
        this->mountDefaults();
    }

    void Project::unmount()
    {
        for (const auto& mount : m_mounts)
        {
            MountablePath::Unmount(*mount);
        }
    }
} // namespace obe::System::Project
