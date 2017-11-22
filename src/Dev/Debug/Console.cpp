#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vili/ErrorHandler.hpp>

#include <Debug/Console.hpp>
#include <Script/GlobalState.hpp>
#include <System/Window.hpp>
#include <Transform/UnitVector.hpp>
#include <Triggers/TriggerDatabase.hpp>
#include <Utils/StringUtils.hpp>

namespace obe
{
    namespace Debug
    {
        Console::Console() : 
        consoleTriggers(Triggers::TriggerDatabase::GetInstance()->createTriggerGroup("Global", "Console"), Triggers::TriggerGroupPtrRemover)
        {
            m_font.loadFromFile("Data/Fonts/arial.ttf");

            consoleTriggers->addTrigger("UserInput")
                           ->addTrigger("CursorMoved")
                           ->addTrigger("ConsoleScrolled")
                           ->addTrigger("NewMessage")
                           ->addTrigger("ConsoleToggled")
                           ->addTrigger("NewStream");

            m_debugStream = this->createStream("ScriptEngine", true);
            m_errorStream = this->createStream("ScriptError", true);
            m_errorStream->setColor(sf::Color::Red);
        }

        void Console::scroll(int power)
        {
            int oldScroll = m_consoleScroll;
            if (m_consoleScroll + power > 0)
            {
                if (m_consoleScroll + power <= static_cast<int>(consoleText.size()) - 52)
                    m_consoleScroll += power;
            }
            else
                m_consoleScroll = 0;
            if (m_consoleScroll != oldScroll)
            {
                consoleTriggers->pushParameter("ConsoleScrolled", "scroll", power);
                consoleTriggers->trigger("ConsoleScrolled");
            }
        }

        ConsoleStream* Console::createStream(const std::string& id, bool enabled)
        {
            m_streamMap[id] = std::make_unique<ConsoleStream>(id, this);
            if (!enabled)
                m_streamMap[id]->disable();
            consoleTriggers->pushParameter("NewStream", "streamName", id);
            consoleTriggers->pushParameter("NewStream", "enabled", enabled);
            consoleTriggers->trigger("NewStream");
            return m_streamMap[id].get();
        }

        ConsoleStream* Console::getStream(const std::string& id)
        {
            if (m_streamMap.find(id) != m_streamMap.end())
                return m_streamMap[id].get();
            throw aube::ErrorHandler::Raise("ObEngine.Console.Console.UnknownStream", {{"stream", id}});
        }

        void Console::downHistory()
        {
            if (m_consoleHistoryIndex < m_consoleHistory.size() - 1)
                m_consoleHistoryIndex++;
            else
                m_consoleHistoryIndex = m_consoleHistory.size() - 1;
            if (m_consoleHistory.size() != 0)
            {
                m_inputBuffer = m_consoleHistory[m_consoleHistoryIndex];
                m_virtualCursor = m_consoleHistory[m_consoleHistoryIndex].size();
            }
        }

        void Console::upHistory()
        {
            if (m_consoleHistoryIndex > 0)
                m_consoleHistoryIndex--;
            else
                m_consoleHistoryIndex = 0;
            if (m_consoleHistory.size() != 0)
            {
                m_inputBuffer = m_consoleHistory[m_consoleHistoryIndex];
                m_virtualCursor = m_consoleHistory[m_consoleHistoryIndex].size();
            }
        }

        ConsoleMessage* Console::pushMessage(const std::string& headerName, const std::string& message, const sf::Color& color)
        {
            ConsoleMessage* forgeMessage = nullptr;
            if (Utils::String::occurencesInString(message, "\n") > 0 && !m_consoleMuted)
            {
                std::vector<std::string> splittedMessage = Utils::String::split(message, "\n");
                for (const std::string& messagePart : splittedMessage)
                    this->pushMessage(headerName, messagePart, color);
            }
            else if (!m_consoleMuted)
            {
                forgeMessage = new ConsoleMessage(headerName, message, color);
                consoleText.push_back(forgeMessage);
                consoleTriggers->pushParameter("NewMessage", "headerName", headerName);
                consoleTriggers->pushParameter("NewMessage", "message", message);
                consoleTriggers->trigger("NewMessage");
                if (m_consoleAutoScroll)
                {
                    if (consoleText.size() >= 52)
                    {
                        m_consoleScroll = consoleText.size() - 52;
                    }
                }
            }
            return forgeMessage;
        }

        void Console::handleCommand(const std::string& text)
        {
            this->pushMessage("UserInput", text, sf::Color::Cyan);
            if (m_consoleHistory.size() == 0 || text != m_consoleHistory[m_consoleHistory.size() - 1])
                m_consoleHistory.push_back(text);
            m_consoleHistoryIndex = m_consoleHistory.size();
            Script::ScriptEngine(text);
            consoleTriggers->pushParameter("UserInput", "input", text);
            consoleTriggers->trigger("UserInput");
        }

        void Console::inputKey(int keyCode)
        {
            switch (keyCode)
            {
            case 8:
                if (m_virtualCursor > 0)
                {
                    m_virtualCursor--;
                    m_inputBuffer.erase(m_inputBuffer.begin() + m_virtualCursor);
                }
                break;
            case 13:
                this->handleCommand(m_inputBuffer);
                this->clearInputBuffer();
                m_virtualCursor = 0;
                break;
            case 22: //Paste
                break;
            default:
                m_inputBuffer.insert(m_inputBuffer.begin() + m_virtualCursor, static_cast<char>(keyCode));
                m_virtualCursor++;
                break;
            }
        }

        void Console::moveCursor(int move)
        {
            if (m_virtualCursor + move <= m_inputBuffer.size() && m_virtualCursor + move >= 0)
                m_virtualCursor += move;
        }

        void Console::clearInputBuffer()
        {
            m_inputBuffer = "";
        }

        void Console::insertInputBufferContent(const std::string& content)
        {
            m_inputBuffer.insert(m_virtualCursor, content);
            m_virtualCursor += content.size();
        }

        void Console::setInputBufferContent(const std::string& content)
        {
            m_inputBuffer = content;
            m_inputBuffer = content.size();
        }

        std::string Console::getInputBufferContent() const
        {
            return m_inputBuffer;
        }

        bool Console::isVisible() const
        {
            return m_consoleVisibility;
        }

        void Console::setVisible(bool enabled)
        {
            if (m_consoleVisibility != enabled)
            {
                consoleTriggers->pushParameter("ConsoleToggled", "state", enabled);
                consoleTriggers->trigger("ConsoleToggled");
            }
            m_consoleVisibility = enabled;
        }

        void Console::display()
        {
            //OUTPUT
            System::MainWindow.clear(sf::Color(0, 0, 0, 200));
            sf::Text textOutput;
            textOutput.setFont(m_font);
            textOutput.setFillColor(sf::Color(255, 255, 255));
            textOutput.setCharacterSize(13);
            bool alternBackground = false;
            sf::Color backgroundColor = sf::Color(30, 30, 30, 200);
            sf::RectangleShape rectangle = sf::RectangleShape(sf::Vector2f(Transform::UnitVector::Screen.w, 20));
            int textX = 5;
            int textY = 1;
            for (unsigned int i = 0; i < 1040; i += 20)
            {
                alternBackground = !alternBackground;
                if (alternBackground)
                {
                    backgroundColor = sf::Color(30, 30, 30, 200);
                }
                else
                {
                    backgroundColor = sf::Color(50, 50, 50, 200);
                }
                rectangle.setPosition(0, i);
                rectangle.setFillColor(backgroundColor);
                System::MainWindow.draw(rectangle);
            }
            for (unsigned int i = 0 + m_consoleScroll; i < consoleText.size(); i++)
            {
                textOutput.setString(consoleText[i]->getFormatedMessage());
                textOutput.setFillColor(consoleText[i]->getColor());
                textOutput.setPosition(sf::Vector2f(textX, textY));
                System::MainWindow.draw(textOutput);
                textY += 20;
            }

            //FRAME
            sf::RectangleShape rectangleFrame = sf::RectangleShape(sf::Vector2f(Transform::UnitVector::Screen.w - 4, Transform::UnitVector::Screen.h - 4));
            rectangleFrame.setFillColor(sf::Color(0, 0, 0, 0));
            rectangleFrame.setOutlineColor(sf::Color(255, 255, 255, 255));
            rectangleFrame.setOutlineThickness(2);
            rectangleFrame.move(2, 2);
            System::MainWindow.draw(rectangleFrame);

            //INPUT
            sf::RectangleShape rectangleInput = sf::RectangleShape(sf::Vector2f(Transform::UnitVector::Screen.w, 40));
            rectangleInput.setPosition(0, Transform::UnitVector::Screen.h - 40);
            rectangleInput.setFillColor(sf::Color(100, 100, 100));
            System::MainWindow.draw(rectangleInput);
            //CURSOR
            sf::RectangleShape rectangleCursor = sf::RectangleShape(sf::Vector2f(2, 30));
            sf::Text estimate;
            estimate.setFont(m_font);
            estimate.setCharacterSize(26);
            estimate.setString(m_inputBuffer.substr(0, m_virtualCursor));
            int consoleCurPos = estimate.getGlobalBounds().width;
            rectangleCursor.setPosition(consoleCurPos + 2, Transform::UnitVector::Screen.h - 35);
            rectangleCursor.setFillColor(sf::Color(200, 200, 200));
            System::MainWindow.draw(rectangleCursor);
            //TEXT
            sf::Text textInput;
            textInput.setFont(m_font);
            textInput.setFillColor(sf::Color(255, 255, 255));
            textInput.setCharacterSize(26);
            textInput.setPosition(2, Transform::UnitVector::Screen.h - 40);
            textInput.setString(m_inputBuffer);
            System::MainWindow.draw(textInput);
        }
    }
}
