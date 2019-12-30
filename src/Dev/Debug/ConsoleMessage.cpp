#include <Debug/Console.hpp>
#include <Debug/ConsoleMessage.hpp>

namespace obe::Debug
{
    ConsoleMessage::ConsoleMessage(
        const std::string& header, const std::string& message, const sf::Color& textColor)
    {
        this->m_header = header;
        this->m_text = message;
        this->m_color = textColor;
        this->m_timestamp = Time::getTickSinceEpoch();
    }

    std::string ConsoleMessage::getFormatedMessage() const
    {
        std::string fMessage;
        if (Console::Timestamped)
        {
            fMessage = "(TimeStamp:" + std::to_string(m_timestamp) + ")";
            fMessage += " [" + m_header + "]";
            fMessage += " : " + m_text;
        }
        else
            fMessage = m_text;
        return fMessage;
    }

    std::string ConsoleMessage::getHeader() const
    {
        return m_header;
    }

    std::string ConsoleMessage::getText() const
    {
        return m_text;
    }

    sf::Color ConsoleMessage::getColor() const
    {
        return m_color;
    }

    void ConsoleMessage::setMessage(const std::string& text)
    {
        m_text = text;
    }

    void ConsoleMessage::setColor(const sf::Color& color)
    {
        m_color = color;
    }
} // namespace obe::Debug