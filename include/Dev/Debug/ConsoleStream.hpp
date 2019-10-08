#pragma once

#include <SFML/Graphics/Color.hpp>

#include <Debug/ConsoleMessage.hpp>
#include <Types/Identifiable.hpp>
#include <Types/Togglable.hpp>

namespace obe::Debug
{
    class Console;

    /**
     * \brief A Stream is a bridge to push Message to the Console
     * @Bind
     */
    class ConsoleStream : public Types::Identifiable, public Types::Togglable
    {
    private:
        Console* m_consoleParent;
        sf::Color m_color = sf::Color(255, 255, 255);

    public:
        /**
         * \brief Creates a new Stream
         * \param id Id of the Stream
         * \param consoleParent Pointer to the Console
         */
        ConsoleStream(const std::string& id, Console* consoleParent);
        /**
         * \brief Push a new Message to the Console
         * \param message Text of the Message
         * \return A pointer to the created Message
         */
        ConsoleMessage* push(const std::string& message) const;
        /**
         * \brief Sets a new Color for the Stream
         * \param color Color of the Stream
         */
        void setColor(const sf::Color& color);
        /**
         * \brief Get the color of the Stream
         * \return A sf::Color containing the color of the Stream
         */
        sf::Color getColor() const;
    };
} // namespace obe::Debug