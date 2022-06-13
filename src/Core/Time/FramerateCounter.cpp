#include <Time/FramerateCounter.hpp>

namespace obe::time
{
    void FramerateCounter::render_tick()
    {
        if (epoch() - m_last_tick <= 1000)
            m_framerate_buffer++;
    }

    void FramerateCounter::update_tick()
    {
        if (epoch() - m_last_tick <= 1000)
            m_updates_buffer++;
        else
        {
            m_updates_counter = m_updates_buffer;
            m_updates_buffer = 0;
            m_last_tick = epoch();
            m_can_update_fps = true;
            m_framerate_counter = m_framerate_buffer;
            m_framerate_buffer = 0;
        }
    }

    void FramerateCounter::load_font(graphics::Font& font)
    {
        m_text.setFont(font);
        m_text.setCharacterSize(12);
        m_text.setFillColor(sf::Color::White);
    }

    void FramerateCounter::draw()
    {
        if (m_can_update_fps)
        {
            m_can_update_fps = false;
            m_text.setString(std::to_string(m_framerate_counter) + " FPS / "
                + std::to_string(m_updates_counter) + " UPS");
        }
        // System::MainWindow.draw(m_text);
    }
} // namespace obe::time
