#include <sol/sol.hpp>

#include <Debug/Logger.hpp>
#include <Engine/Engine.hpp>
#include <System/Plugin.hpp>

namespace obe::system
{
    Plugin::Plugin(const std::string& id, const std::string& path)
        : types::Identifiable(id)
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
            m_on_init_fn = get_plugin_function<void(engine::Engine&)>(m_dl, "OnInit");
            (*m_on_init_fn)->init();
            debug::Log->debug("<System:Plugins> : (Plugin '{}') > Found function OnInit", id);
        }
        catch (const dynamicLinker::dynamicLinkerException& e)
        {
            m_on_init_fn = std::nullopt;
        }
        try
        {
            m_on_exit_fn = get_plugin_function<void(engine::Engine&)>(m_dl, "OnExit");
            (*m_on_exit_fn)->init();
            debug::Log->debug("<System:Plugins> : (Plugin '{}') > Found function OnExit", id);
        }
        catch (const dynamicLinker::dynamicLinkerException& e)
        {
            m_on_exit_fn = std::nullopt;
        }

        debug::Log->info("<System:Plugin> : Loaded : '{}'", id);
    }

    void Plugin::on_init(engine::Engine& engine) const
    {
        if (m_on_init_fn)
        {
            (**m_on_init_fn)(engine);
        }
    }

    void Plugin::on_exit(engine::Engine& engine) const
    {
        if (m_on_exit_fn)
        {
            (**m_on_exit_fn)(engine);
        }
    }

    bool Plugin::has_on_init() const
    {
        return m_on_init_fn.has_value();
    }

    bool Plugin::has_on_exit() const
    {
        return m_on_exit_fn.has_value();
    }

    bool Plugin::is_valid() const
    {
        return m_valid;
    }
} // namespace obe::system
