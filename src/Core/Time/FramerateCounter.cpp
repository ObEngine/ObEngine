#include <System/Window.hpp>
#include <Time/FramerateCounter.hpp>

namespace obe::Time
{
    void FramerateCounter::tick()
    {
        if (epoch() - m_lastTick <= 1000)
            m_framerateBuffer++;
    }

    void FramerateCounter::uTick()
    {
        if (epoch() - m_lastTick <= 1000)
            m_updatesBuffer++;
        else
        {
            m_updatesCounter = m_updatesBuffer;
            m_updatesBuffer = 0;
            m_lastTick = epoch();
            m_canUpdateFPS = true;
            m_framerateCounter = m_framerateBuffer;
            m_framerateBuffer = 0;
        }
    }

    void FramerateCounter::loadFont(Graphics::Font& font)
    {
        m_text.setFont(font);
        m_text.setCharacterSize(12);
        m_text.setFillColor(sf::Color::White);
    }

    void FramerateCounter::draw()
    {
        if (m_canUpdateFPS)
        {
            m_canUpdateFPS = false;
            m_text.setString(std::to_string(m_framerateCounter) + " FPS / "
                + std::to_string(m_updatesCounter) + " UPS");
        }
        // System::MainWindow.draw(m_text);
    }
} // namespace obe::Time