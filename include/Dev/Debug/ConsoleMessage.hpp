#pragma once

#include <string>

#include <SFML/Graphics/Color.hpp>

#include <Time/TimeUtils.hpp>

namespace obe::Debug
{
    /**
     * \brief A Message (line) displayed in the Console
     * @Bind
     */
    class ConsoleMessage
    {
    private:
        std::string m_header;
        std::string m_text;
        sf::Color m_color;
        Time::TimeUnit m_timestamp;

    public:
        /**
         * \brief Creates a Message
         * \param header Name of the stream of the Message
         * \param message Text of the Message
         * \param textColor Color of the Message
         */
        ConsoleMessage(const std::string& header, const std::string& message,
                       const sf::Color& textColor);
        /**
         * \brief Get the whole Message (with header and text)
         * \return A std::string containing the whole Message
         */
        std::string getFormatedMessage() const;
        /**
         * \brief Get the header of the Message
         * \return A std::string containing the header of the Message
         */
        std::string getHeader() const;
        /**
         * \brief Get the text of the Message
         * \return A std::string containing the text of the Message
         */
        std::string getText() const;
        /**
         * \brief Get the Color of the Message
         * \return A sf::Color containing the color of the Message
         */
        sf::Color getColor() const;
        /**
         * \brief Set a next text for the Message
         * \param text New text for the Message
         */
        void setMessage(const std::string& text);
        /**
         * \brief Set the color of the Message
         * \param color sf::Color for the Message
         */
        void setColor(const sf::Color& color);
    };
} // namespace obe::Debug