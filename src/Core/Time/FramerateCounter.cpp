#include <System/Window.hpp>
#include <Time/FramerateCounter.hpp>

namespace obe::Time
{
    void FPSCounter::tick()
    {
        if (getTickSinceEpoch() - m_lastTick <= 1000)
            m_fpsCounter++;
    }

    void FPSCounter::uTick()
    {
        if (getTickSinceEpoch() - m_lastTick <= 1000)
            m_updCounter++;
        else
        {
            m_saveUPD = m_updCounter;
            m_updCounter = 0;
            m_lastTick = getTickSinceEpoch();
            m_canUpdateFPS = true;
            m_saveFPS = m_fpsCounter;
            m_fpsCounter = 0;
        }
    }

    void FPSCounter::loadFont(sf::Font& font)
    {
        m_text.setFont(font);
        m_text.setCharacterSize(12);
        m_text.setFillColor(sf::Color::White);
    }

    void FPSCounter::draw()
    {
        if (m_canUpdateFPS)
        {
            m_canUpdateFPS = false;
            m_text.setString(
                std::to_string(m_saveFPS) + " FPS / " + std::to_string(m_saveUPD) + " UPS");
        }
        System::MainWindow.draw(m_text);
    }
} // namespace obe::Time