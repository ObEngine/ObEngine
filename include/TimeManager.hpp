//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <map>
#include <chrono>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace obe
{
    namespace Time
    {
	    /**
		 * \brief TimeUnit to store Epoch milli/micro seconds
		 */
		typedef unsigned long long int TimeUnit;
	    /**
         * \brief Get the amount of milliseconds elapsed since Epoch
         * \return A TimeUnit containing the amount of milliseconds elapsed since Epoch
         */
        TimeUnit getTickSinceEpoch();
		/**
		* \brief Get the amount of microseconds elapsed since Epoch
		* \return A TimeUnit containing the amount of microseconds elapsed since Epoch
		*/
        TimeUnit getTickSinceEpochMicro();

	    /**
         * \brief A Chronometer class to measure time
         */
        class Chronometer
        {
        private:
            std::chrono::high_resolution_clock::time_point m_chronoStart;
            std::chrono::high_resolution_clock::time_point m_chronoCurrent;
            bool m_started = false;
            unsigned long long int m_limit = 0;
        public:
	        /**
             * \brief Chronometer default constructor
             */
            Chronometer();
	        /**
             * \brief Starts the Chronometer
             */
            void start();
	        /**
             * \brief Stops the Chronometer
             */
            void stop();
	        /**
             * \brief Get Time elapsed since the Chronometer started
             * \return The amount of milliseconds elapsed since the Chronometer started
             */
            TimeUnit getTime();
	        /**
             * \brief Defines a limit to the Chronometer
             * \param limit The amount of milliseconds before the limit is exceeded
             */
            void setLimit(TimeUnit limit);
	        /**
             * \brief Check if the defined limit has been exceeded
             * \return true if the limit has been exceeded, false otherwise.
             */
            bool limitExceeded();
        };

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
             * \param target Window to draws that stats on
             */
			void draw(sf::RenderWindow& target);
        };
    }
}
