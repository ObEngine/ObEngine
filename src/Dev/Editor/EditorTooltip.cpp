#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <Editor/EditorTooltip.hpp>
#include <Graphics/ResourceManager.hpp>
#include <System/Window.hpp>

namespace obe::Editor
{
    Tooltip::Tooltip()
    {
        m_background.setFillColor(sf::Color(0, 0, 0, 200));

        m_text.setFont(*Graphics::ResourceManager::GetInstance().getFont("Data/Fonts/arial.ttf"));
        m_text.setCharacterSize(16);
        m_text.setFillColor(sf::Color::White);
    }

    void Tooltip::clear()
    {
        m_empty = true;
        m_text.setString("");
    }

    void Tooltip::draw() const
    {
        System::MainWindow.draw(m_background);
        System::MainWindow.draw(m_text);
    }

    void Tooltip::setPosition(int x, int y)
    {
        m_background.setPosition(x, y);
        m_text.setPosition(x + 10, y);
    }

    bool Tooltip::empty() const
    {
        return m_empty;
    }
} // namespace obe::Editor