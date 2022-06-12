#include <sol/sol.hpp>

#include <Debug/Logger.hpp>
#include <Engine/Engine.hpp>
#include <System/Plugin.hpp>

namespace obe::System
{
    Plugin::Plugin(const std::string& id, const std::string& path)
        : Types::Identifiable(id)
    {
        debug::Log->info("<System:Plugin> : Loading Plugin '{}' ...", id);
        try
        {
            m_dl = dynamicLinker::dynamicLinker::make_new(path);
            m_dl->open();
        }
        catch (const dynamicLinker::dynamicLinkerException& e)
        {
            debug::Log->warn(
                "<System:Plugin> : Unloadable Plugin : '{}' (Reason : {})", id, e.what());
            return;
        }
        m_valid = true;
        try
        {
            m_onInitFn = getPluginFunction<void(engine::Engine&)>(m_dl, "OnInit");
            (*m_onInitFn)->init();
            debug::Log->debug("<System:Plugins> : (Plugin '{}') > Found function OnInit", id);
        }
        catch (const dynamicLinker::dynamicLinkerException& e)
        {
            m_onInitFn = std::nullopt;
        }
        try
        {
            m_onUpdateFn = getPluginFunction<void(double)>(m_dl, "OnUpdate");
            (*m_onUpdateFn)->init();
            debug::Log->debug("<System:Plugins> : (Plugin '{}') > Found function OnUpdate", id);
        }
        catch (const dynamicLinker::dynamicLinkerException& e)
        {
            m_onUpdateFn = std::nullopt;
        }
        try
        {
            m_onRenderFn = getPluginFunction<void()>(m_dl, "OnRender");
            (*m_onRenderFn)->init();
            debug::Log->debug("<System:Plugins> : (Plugin '{}') > Found function OnRender", id);
        }
        catch (const dynamicLinker::dynamicLinkerException& e)
        {
            m_onRenderFn = std::nullopt;
        }
        try
        {
            m_onExitFn = getPluginFunction<void()>(m_dl, "OnExit");
            (*m_onExitFn)->init();
            debug::Log->debug("<System:Plugins> : (Plugin '{}') > Found function OnExit", id);
        }
        catch (const dynamicLinker::dynamicLinkerException& e)
        {
            m_onExitFn = std::nullopt;
        }

        debug::Log->info("<System:Plugin> : Loaded : '{}'", id);
    }

    void Plugin::onInit(engine::Engine& engine) const
    {
        if (m_onInitFn)
        {
            (**m_onInitFn)(engine);
        }
    }

    void Plugin::onUpdate(double dt) const
    {
        if (m_onUpdateFn)
        {
            (**m_onUpdateFn)(dt);
        }
    }

    void Plugin::onRender() const
    {
        if (m_onRenderFn)
        {
            (**m_onRenderFn)();
        }
    }

    void Plugin::onExit() const
    {
        if (m_onExitFn)
        {
            (**m_onExitFn)();
        }
    }

    bool Plugin::hasOnInit() const
    {
        return m_onInitFn.has_value();
    }

    bool Plugin::hasOnUpdate() const
    {
        return m_onUpdateFn.has_value();
    }

    bool Plugin::hasOnRender() const
    {
        return m_onRenderFn.has_value();
    }

    bool Plugin::hasOnExit() const
    {
        return m_onExitFn.has_value();
    }

    bool Plugin::isValid() const
    {
        return m_valid;
    }
} // namespace obe::System
