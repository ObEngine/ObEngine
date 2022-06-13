#pragma once

#include <SFML/Graphics/Text.hpp>

#include <Graphics/Font.hpp>
#include <Time/TimeUtils.hpp>

namespace obe::time
{
    /**
     * \brief Class to display the amount of Frame and Update per Seconds
     */
    class FramerateCounter
    {
    private:
        TimeUnit m_last_tick = epoch();
        int m_framerate_counter = 0;
        int m_updates_counter = 0;
        int m_framerate_buffer = 0;
        int m_updates_buffer = 0;
        bool m_can_update_fps = false;
        sf::Text m_text;
        graphics::Font m_font;

    public:
        /**
         * \brief Called when screen is refreshed.
         */
        void render_tick();
        /**
         * \brief Called when game is updated
         */
        void update_tick();
        /**
         * \brief Load a new font to use when drawing the stats
         * \param font Font to use to draw the amount of fps / ups
         */
        void load_font(graphics::Font& font);
        /**
         * \brief Draws the calculated stats on the screen
         */
        void draw();
    };
} // namespace obe::time
