#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <Time/TimeUtils.hpp>

namespace obe::Time
{
    /**
     * \brief Class to display the amount of Frame and Update per Seconds
     * @Bind
     */
    class FPSCounter
    {
    private:
        TimeUnit m_lastTick = getTickSinceEpoch();
        int m_fpsCounter = 0;
        int m_updCounter = 0;
        int m_saveFPS = 0;
        int m_saveUPD = 0;
        bool m_canUpdateFPS = false;
        sf::Text m_text;
        sf::Font m_font;

    public:
        /**
         * \brief Called when screen is refreshed.
         */
        void tick();
        /**
         * \brief Called when game is updated
         */
        void uTick();
        /**
         * \brief Load a new font to use when drawing the stats
         * \param font Font to use to draw the amount of fps / ups
         */
        void loadFont(sf::Font& font);
        /**
         * \brief Draws the calculated stats on the screen
         */
        void draw();
    };
} // namespace obe::Time