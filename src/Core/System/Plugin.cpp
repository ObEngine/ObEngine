#include <Debug/Logger.hpp>
#include <System/Plugin.hpp>

#include <sol/sol.hpp>

namespace obe::System
{
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
            Debug::Log->debug(
                "<System:Plugins> : (Plugin '{}') > Found function OnInit", id);
            m_hasOnInitFn = true;
            m_onInitFn->operator()();
        }
        catch (const dynamicLinker::dynamicLinkerException& e)
        {
        }
        try
        {
            m_onLoadBindingsFn
                = getPluginFunction<void(sol::state_view)>(m_dl, "OnLoadBindings");
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
            Debug::Log->debug(
                "<System:Plugins> : (Plugin '{}') > Found function OnUpdate", id);
        }
        catch (const dynamicLinker::dynamicLinkerException& e)
        {
        }
        try
        {
            m_onRenderFn = getPluginFunction<void()>(m_dl, "OnRender");
            m_onRenderFn->init();
            m_hasOnRenderFn = true;
            Debug::Log->debug(
                "<System:Plugins> : (Plugin '{}') > Found function OnRender", id);
        }
        catch (const dynamicLinker::dynamicLinkerException& e)
        {
        }
        try
        {
            m_onExitFn = getPluginFunction<void()>(m_dl, "OnExit");
            m_onExitFn->init();
            m_hasOnExitFn = true;
            Debug::Log->debug(
                "<System:Plugins> : (Plugin '{}') > Found function OnExit", id);
        }
        catch (const dynamicLinker::dynamicLinkerException& e)
        {
        }

        Debug::Log->info("<System:Plugin> : Loaded : '{}'", id);
    }

    void Plugin::onLoadBindings(sol::state_view lua) const
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
