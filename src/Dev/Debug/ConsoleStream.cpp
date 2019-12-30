#include <Debug/Console.hpp>
#include <Debug/ConsoleStream.hpp>

namespace obe::Debug
{
    ConsoleStream::ConsoleStream(const std::string& id, Console* consoleParent)
        : Identifiable(id)
        , Togglable(true)
    {
        m_consoleParent = consoleParent;
        m_color = sf::Color(255, 255, 255);
    }

    ConsoleMessage* ConsoleStream::push(const std::string& message) const
    {
        return m_consoleParent->pushMessage(m_id, message, m_color);
    }

    void ConsoleStream::setColor(const sf::Color& color)
    {
        m_color = color;
    }

    sf::Color ConsoleStream::getColor() const
    {
        return m_color;
    }
} // namespace obe::Debug