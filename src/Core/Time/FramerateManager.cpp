#include <thread>

#include <Debug/Logger.hpp>
#include <Time/FramerateManager.hpp>

namespace obe::time
{
    FramerateManager::FramerateManager(system::Window& window)
        : m_window(window)
        , m_clock(epoch())
        , m_current_frame(0)
        , m_frame_progression(0)
        , m_need_to_render(false)
    {
    }

    void FramerateManager::configure(vili::node& config)
    {
        if (config.contains("framerateTarget"))
        {
            m_framerate_target = config["framerateTarget"];
        }
        if (config.contains("vsync"))
        {
            m_vsync_enabled = config["vsync"];
        }
        if (config.contains("syncUpdateToRender"))
        {
            m_sync_update_render = config["syncUpdateToRender"];
        }
        debug::Log->info("Framerate parameters : {} FPS {}, V-sync {}, Update Lock {}",
            m_framerate_target.value_or(0),
            (m_framerate_target.has_value()) ? "capped" : "uncapped",
            (m_vsync_enabled) ? "enabled" : "disabled",
            (m_sync_update_render) ? "enabled" : "disabled");

        m_window.set_vertical_sync_enabled(m_vsync_enabled);
    }

    void FramerateManager::update()
    {
        const time::TimeUnit since_last_update = epoch() - m_clock;
        const time::TimeUnit expected_frame_time
            = 1.0 / static_cast<double>(m_framerate_target.value());
        if (!m_framerate_target || since_last_update > expected_frame_time)
        {
            m_need_to_render = true;
            m_delta_time = epoch() - m_clock;
            m_clock = epoch();
        }
        else if (!m_sync_update_render)
        {
            std::this_thread::sleep_for(std::chrono::duration<double>(expected_frame_time / 20.f));
        }
    }

    TimeUnit FramerateManager::get_raw_delta_time() const
    {
        return m_delta_time;
    }

    double FramerateManager::get_delta_time() const
    {
        return std::min(m_delta_time * m_speed_coefficient, m_max_delta_time);
    }

    double FramerateManager::get_speed_coefficient() const
    {
        return m_speed_coefficient;
    }

    bool FramerateManager::is_framerate_limited() const
    {
        return m_framerate_target.has_value();
    }

    unsigned int FramerateManager::get_framerate_target() const
    {
        return m_framerate_target.value_or(0);
    }

    bool FramerateManager::is_vsync_enabled() const
    {
        return m_vsync_enabled;
    }

    void FramerateManager::set_speed_coefficient(const double speed)
    {
        m_speed_coefficient = speed;
    }

    void FramerateManager::set_framerate_target(const unsigned int limit)
    {
        if (limit == 0)
        {
            m_framerate_target = std::nullopt;
            return;
        }
        m_framerate_target = limit;
    }

    void FramerateManager::set_vsync_enabled(const bool vsync)
    {
        m_vsync_enabled = vsync;
        m_window.set_vertical_sync_enabled(vsync);
    }

    void FramerateManager::set_max_delta_time(double max_delta_time)
    {
        m_max_delta_time = max_delta_time;
    }

    bool FramerateManager::should_render() const
    {
        return (!m_framerate_target || m_need_to_render);
    }

    bool FramerateManager::should_update() const
    {
        return (!m_sync_update_render || !m_framerate_target || m_need_to_render);
    }

    void FramerateManager::start()
    {
        m_clock = epoch();
    }

    void FramerateManager::reset()
    {
        m_need_to_render = false;
    }
} // namespace obe::time
