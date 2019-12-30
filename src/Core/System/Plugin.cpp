#include <Debug/Logger.hpp>
#include <Script/GlobalState.hpp>
#include <System/MountablePath.hpp>
#include <System/Path.hpp>
#include <System/Plugin.hpp>
#include <Utils/FileUtils.hpp>
#include <Utils/StringUtils.hpp>

#include <kaguya/kaguya.hpp>

namespace obe::System
{
    std::vector<std::unique_ptr<Plugin>> Plugins;

    void IndexPlugins()
    {
        for (const System::MountablePath& mountedPath : System::Path::MountedPaths)
        {
            Debug::Log->info(
                "<Bindings> Checking Plugins on Mounted Path : {0}", mountedPath.basePath);
            System::Path cPluginPath = System::Path(mountedPath.basePath).add("Plugins");
            if (Utils::File::directoryExists(cPluginPath.toString()))
            {
                for (const std::string& filename : Utils::File::getFileList(cPluginPath.toString()))
                {
                    const std::string pluginPath = cPluginPath.add(filename).toString();
                    const std::string pluginName = Utils::String::split(filename, ".")[0];
                    Plugins.emplace_back(std::make_unique<Plugin>(pluginName, pluginPath));
                }
            }
        }
    }

    Plugin::Plugin(const std::string& id, const std::string& path)
        : Types::Identifiable(id)
    {
        m_hasOnInitFn = false;
        m_hasOnLoadBindingsFn = false;
        m_hasOnUpdateFn = false;
        m_hasOnRenderFn = false;
        m_hasOnExitFn = false;
        Debug::Log->info("<System:Plugin> : Loading Plugin '{}' ...", id);
        try
        {
            m_dl = dynamicLinker::dynamicLinker::make_new(path);
            m_dl->open();
        }
        catch (const dynamicLinker::dynamicLinkerException& e)
        {
            Debug::Log->warn(
                "<System:Plugin> : Unloadable Plugin : '{}' (Reason : {})", id, e.what());
        }
        try
        {
            m_onInitFn = getPluginFunction<void()>(m_dl, "OnInit");
            m_onInitFn->init();
            Debug::Log->debug("<System:Plugins> : (Plugin '{}') > Found function OnInit", id);
            m_hasOnInitFn = true;
            m_onInitFn->operator()();
        }
        catch (const dynamicLinker::dynamicLinkerException& e)
        {
        }
        try
        {
            m_onLoadBindingsFn = getPluginFunction<void(kaguya::State*)>(m_dl, "OnLoadBindings");
            m_onLoadBindingsFn->init();
            m_hasOnLoadBindingsFn = true;
            Debug::Log->debug("<System:Plugins> : (Plugin '{}') > Found "
                              "function OnLoadBindings",
                id);
        }
        catch (const dynamicLinker::dynamicLinkerException& e)
        {
        }
        try
        {
            m_onUpdateFn = getPluginFunction<void(double)>(m_dl, "OnUpdate");
            m_onUpdateFn->init();
            m_hasOnUpdateFn = true;
            Debug::Log->debug("<System:Plugins> : (Plugin '{}') > Found function OnUpdate", id);
        }
        catch (const dynamicLinker::dynamicLinkerException& e)
        {
        }
        try
        {
            m_onRenderFn = getPluginFunction<void()>(m_dl, "OnRender");
            m_onRenderFn->init();
            m_hasOnRenderFn = true;
            Debug::Log->debug("<System:Plugins> : (Plugin '{}') > Found function OnRender", id);
        }
        catch (const dynamicLinker::dynamicLinkerException& e)
        {
        }
        try
        {
            m_onExitFn = getPluginFunction<void()>(m_dl, "OnExit");
            m_onExitFn->init();
            m_hasOnExitFn = true;
            Debug::Log->debug("<System:Plugins> : (Plugin '{}') > Found function OnExit", id);
        }
        catch (const dynamicLinker::dynamicLinkerException& e)
        {
        }

        Debug::Log->info("<System:Plugin> : Loaded : '{}'", id);
    }

    void Plugin::onLoadBindings(kaguya::State* lua) const
    {
        m_onLoadBindingsFn->operator()(lua);
    }

    void Plugin::onUpdate(double dt) const
    {
        m_onUpdateFn->operator()(dt);
    }

    void Plugin::onRender() const
    {
        m_onRenderFn->operator()();
    }

    void Plugin::onExit() const
    {
        m_onExitFn->operator()();
    }

    bool Plugin::hasOnInit() const
    {
        return m_hasOnInitFn;
    }

    bool Plugin::hasOnLoadBindings() const
    {
        return m_hasOnLoadBindingsFn;
    }

    bool Plugin::hasOnUpdate() const
    {
        return m_hasOnUpdateFn;
    }

    bool Plugin::hasOnRender() const
    {
        return m_hasOnRenderFn;
    }

    bool Plugin::hasOnExit() const
    {
        return m_hasOnExitFn;
    }
} // namespace obe::System
