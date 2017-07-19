#pragma once

#include <map>
#include <string>
#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <Triggers/TriggerGroup.hpp>
#include <Types/Identifiable.hpp>
#include <Types/Togglable.hpp>

namespace obe
{
    namespace Debug
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
            unsigned long long int timestamp;
        public:
            /**
            * \brief Creates a Message
            * \param header Name of the stream of the Message
            * \param text Text of the Message
            * \param textColor Color of the Message
            */
            ConsoleMessage(const std::string& header, const std::string& text, const sf::Color& textColor);
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

        /**
         * \brief An in-editor Console used to Debug
         * @Bind
         */
        class Console
        {
        private:
            ConsoleStream* m_debugStream;
            ConsoleStream* m_errorStream;
            int m_virtualCursor = 0;
            bool m_consoleVisibility = false;
            int m_consoleScroll = 0;
            bool m_consoleAutoScroll = true;
            bool m_consoleMuted = false;
            int m_consoleHistoryIndex = 0;
            std::vector<std::string> m_consoleHistory;
            sf::Font m_font;
            std::string m_inputBuffer;
            std::map<std::string, std::unique_ptr<ConsoleStream>> m_streamMap;
            std::vector<ConsoleMessage*> consoleText;
            Triggers::TriggerGroupPtr consoleTriggers;
        public:
            /**
             * \brief Creates a new Console
             */
            Console();
            /**
             * \brief Adds a timestamp to every message if equals to true
             */
            static const bool Timestamped = true;
            /**
             * \brief Executes a command (Sent to the Script::ScriptEngine)
             * \param text A std::string containing the command to execute
             */
            void handleCommand(const std::string& text);
            /**
             * \brief Scrolls in the Console content
             * \param power Amount of lines to scroll (Positive integer = Scrolling down, Negative integer = Scrolling up)
             */
            void scroll(int power);
            /**
             * \brief Push a new Message to the Console
             * \param headerName Name of the Category of the Message you want to display
             * \param message Text of the Message you want to display
             * \param color Color of the Message you want to display
             * \return A pointer to the newly created Message
             */
            ConsoleMessage* pushMessage(const std::string& headerName, const std::string& message, const sf::Color& color);
            /**
             * \brief Add a new character to the input buffer
             * \param keyCode ASCII number of the character to add
             */
            void inputKey(int keyCode);
            /**
             * \brief Clears the input
             */
            void clearInputBuffer();
            /**
             * \brief Get the current entered text
             * \return A std::string containing the current text in the input
             */
            std::string getInputBufferContent() const;
            /**
             * \brief Set the content of the input
             * \param content A std::string to put in the input buffer
             */
            void setInputBufferContent(const std::string& content);
            /**
             * \brief Insert content to the input
             * \param content A std::stirng to insert in the input buffer
             */
            void insertInputBufferContent(const std::string& content);
            /**
             * \brief Creates a new Stream to use in the Console
             * \param id Id of the new Stream to create
             * \param enabled Is the Stream enabled at creation ?
             * \return A pointed to the new Stream
             */
            ConsoleStream* createStream(const std::string& id, bool enabled = true);
            /**
             * \brief Get an existing Stream
             * \param id Id of the Stream to get
             * \return A pointer to the Stream
             */
            ConsoleStream* getStream(const std::string& id);
            /**
             * \brief Fill the buffer with the previous command
             */
            void downHistory();
            /**
             * \brief Fill the buffer with the next command
             */
            void upHistory();
            /**
             * \brief Displays the Console on the screen
             * \param target sf::RenderWindow where to display the Console
             */
            void display(sf::RenderWindow& target);
            /**
             * \brief Check the visibility of the Console
             * \return true if the Console is visible, false otherwise
             */
            bool isConsoleVisible() const;
            /**
             * \brief Set if the Console is visible or not
             * \param enabled Boolean containing if the Console should be displayed or not
             */
            void setConsoleVisibility(bool enabled);
            /**
             * \brief Moves the virtual cursor
             * \param position Offset to move the virtual cursor
             */
            void moveCursor(int position);
        };
    }
}
