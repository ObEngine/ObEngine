#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <Graphics/Font.hpp>
#include <Time/TimeUtils.hpp>

namespace obe::Time
{
    /**
     * \brief Class to display the amount of Frame and Update per Seconds
     */
    class FramerateCounter
    {
    private:
        TimeUnit m_lastTick = epoch();
        int m_framerateCounter = 0;
        int m_updatesCounter = 0;
        int m_framerateBuffer = 0;
        int m_updatesBuffer = 0;
        bool m_canUpdateFPS = false;
        sf::Text m_text;
        Graphics::Font m_font;

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
        void loadFont(Graphics::Font& font);
        /**
         * \brief Draws the calculated stats on the screen
         */
        void draw();
    };
} // namespace obe::Time