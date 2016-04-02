////////////////////////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////////////////////////
#include "RichText.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <SFML/System/String.hpp>

namespace sfe
{

////////////////////////////////////////////////////////////////////////////////
void RichText::Line::setCharacterSize(unsigned int size)
{
    for (sf::Text &text : m_texts)
        text.setCharacterSize(size);

    updateGeometry();
}


////////////////////////////////////////////////////////////////////////////////
void RichText::Line::setFont(const sf::Font &font)
{
    for (sf::Text &text : m_texts)
        text.setFont(font);

    updateGeometry();
}


////////////////////////////////////////////////////////////////////////////////
const std::vector<sf::Text> &RichText::Line::getTexts() const
{
    return m_texts;
}


////////////////////////////////////////////////////////////////////////////////
void RichText::Line::appendText(sf::Text text)
{
    // Set text offset
    updateTextAndGeometry(text);

    // Push back
    m_texts.push_back(std::move(text));
}


////////////////////////////////////////////////////////////////////////////////
sf::FloatRect RichText::Line::getLocalBounds() const
{
    return m_bounds;
}


////////////////////////////////////////////////////////////////////////////////
sf::FloatRect RichText::Line::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}


////////////////////////////////////////////////////////////////////////////////
void RichText::Line::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    for (const sf::Text &text : m_texts)
        target.draw(text, states);
}


////////////////////////////////////////////////////////////////////////////////
void RichText::Line::updateGeometry() const
{
    m_bounds = sf::FloatRect();

    for (sf::Text &text : m_texts)
        updateTextAndGeometry(text);
}


////////////////////////////////////////////////////////////////////////////////
void RichText::Line::updateTextAndGeometry(sf::Text &text) const
{
    // Set text offset
    text.setPosition(m_bounds.width, 0.f);

    // Update bounds
    int lineSpacing = text.getFont()->getLineSpacing(text.getCharacterSize());
    m_bounds.height = std::max(m_bounds.height, static_cast<float>(lineSpacing));
    m_bounds.width += text.getGlobalBounds().width;
}


////////////////////////////////////////////////////////////////////////////////
RichText::RichText()
    : RichText(nullptr)
{

}


////////////////////////////////////////////////////////////////////////////////
RichText::RichText(const sf::Font &font)
    : RichText(&font)
{

}


////////////////////////////////////////////////////////////////////////////////
RichText & RichText::operator << (const sf::Color &color)
{
    m_currentColor = color;
    return *this;
}


////////////////////////////////////////////////////////////////////////////////
RichText & RichText::operator << (sf::Text::Style style)
{
    m_currentStyle = style;
    return *this;
}


////////////////////////////////////////////////////////////////////////////////
std::vector<sf::String> explode(const sf::String &string, sf::Uint32 delimiter) {
    if (string.isEmpty())
        return std::vector<sf::String>();

    // For each character in the string
    std::vector<sf::String> result;
    sf::String buffer;
    for (sf::Uint32 character : string) {
        // If we've hit the delimiter character
        if (character == delimiter) {
            // Add them to the result vector
            result.push_back(buffer);
            buffer.clear();
        } else {
            // Accumulate the next character into the sequence
            buffer += character;
        }
    }

    // Add to the result if buffer still has contents or if the last character is a delimiter
    if (!buffer.isEmpty() || string[string.getSize() - 1] == delimiter)
        result.push_back(buffer);

    return result;
}


////////////////////////////////////////////////////////////////////////////////
RichText & RichText::operator << (const sf::String &string)
{
    // Maybe skip
    if (string.isEmpty())
        return *this;

    // Explode into substrings
    std::vector<sf::String> subStrings = explode(string, '\n');

    // Append first substring using the last line
    auto it = subStrings.begin();
    if (it != subStrings.end()) {
        // If there isn't any line, just create it
        if (m_lines.empty())
            m_lines.resize(1);

        // Remove last line's height
        Line &line = m_lines.back();
        m_bounds.height -= line.getGlobalBounds().height;

        // Append text
        line.appendText(createText(*it));

        // Update bounds
        m_bounds.height += line.getGlobalBounds().height;
        m_bounds.width = std::max(m_bounds.width, line.getGlobalBounds().width);
    }

    // Append the rest of substrings as new lines
    while (++it != subStrings.end()) {
        Line line;
        line.setPosition(0.f, m_bounds.height);
        line.appendText(createText(*it));
        m_lines.push_back(std::move(line));

        // Update bounds
        m_bounds.height += line.getGlobalBounds().height;
        m_bounds.width = std::max(m_bounds.width, line.getGlobalBounds().width);
    }

    // Return
    return *this;
}


////////////////////////////////////////////////////////////////////////////////
void RichText::setCharacterSize(unsigned int size)
{
    // Maybe skip
    if (m_characterSize == size)
        return;

    // Update character size
    m_characterSize = size;

    // Set texts character size
    for (Line &line : m_lines)
        line.setCharacterSize(size);

    updateGeometry();
}


////////////////////////////////////////////////////////////////////////////////
void RichText::setFont(const sf::Font &font)
{
    // Maybe skip
    if (m_font == &font)
        return;

    // Update font
    m_font = &font;

    // Set texts font
    for (Line &line : m_lines)
        line.setFont(font);

    updateGeometry();
}


////////////////////////////////////////////////////////////////////////////////
void RichText::clear()
{
    // Clear texts
    m_lines.clear();

    // Reset bounds
    m_bounds = sf::FloatRect();
}


////////////////////////////////////////////////////////////////////////////////
const std::vector<RichText::Line> &RichText::getLines() const
{
    return m_lines;
}


////////////////////////////////////////////////////////////////////////////////
unsigned int RichText::getCharacterSize() const
{
    return m_characterSize;
}


////////////////////////////////////////////////////////////////////////////////
const sf::Font *RichText::getFont() const
{
    return m_font;
}


////////////////////////////////////////////////////////////
sf::FloatRect RichText::getLocalBounds() const
{
    return m_bounds;
}


////////////////////////////////////////////////////////////
sf::FloatRect RichText::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}


////////////////////////////////////////////////////////////////////////////////
void RichText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    for (const Line &line : m_lines)
        target.draw(line, states);
}


////////////////////////////////////////////////////////////////////////////////
RichText::RichText(const sf::Font *font)
    : m_font(font),
      m_characterSize(30),
      m_currentColor(sf::Color::White),
      m_currentStyle(sf::Text::Regular)
{

}


////////////////////////////////////////////////////////////////////////////////
sf::Text RichText::createText(const sf::String &string) const
{
    sf::Text text;
    text.setString(string);
    text.setColor(m_currentColor);
    text.setStyle(m_currentStyle);
    text.setCharacterSize(m_characterSize);
    if (m_font)
        text.setFont(*m_font);

    return text;
}


////////////////////////////////////////////////////////////////////////////////
void RichText::updateGeometry() const
{
    m_bounds = sf::FloatRect();

    for (Line &line : m_lines) {
        line.setPosition(0.f, m_bounds.height);

        m_bounds.height += line.getGlobalBounds().height;
        m_bounds.width = std::max(m_bounds.width, line.getGlobalBounds().width);
    }
}

}
