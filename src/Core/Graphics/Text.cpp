#include <Graphics/Text.hpp>
#include <codecvt>

namespace obe::graphics
{
    Text::Text()
    {
    }

    Text::Text(const std::string& string)
    {
        this->string = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(string);
    }

    void RichText::Line::set_character_size(unsigned int size) const
    {
        for (sf::Text& text : m_texts)
            text.setCharacterSize(size);

        update_geometry();
    }

    void RichText::Line::set_font(const sf::Font& font) const
    {
        for (sf::Text& text : m_texts)
            text.setFont(font);

        update_geometry();
    }

    const std::vector<sf::Text>& RichText::Line::get_texts() const
    {
        return m_texts;
    }

    void RichText::Line::append_text(sf::Text text) const
    {
        // Set text offset
        update_text_and_geometry(text);

        // Push back
        m_texts.push_back(std::move(text));
    }

    ////////////////////////////////////////////////////////////////////////////////
    sf::FloatRect RichText::Line::get_local_bounds() const
    {
        return m_bounds;
    }

    ////////////////////////////////////////////////////////////////////////////////
    sf::FloatRect RichText::Line::get_global_bounds() const
    {
        return getTransform().transformRect(get_local_bounds());
    }

    ////////////////////////////////////////////////////////////////////////////////
    void RichText::Line::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        for (const sf::Text& text : m_texts)
            target.draw(text, states);
    }

    ////////////////////////////////////////////////////////////////////////////////
    void RichText::Line::update_geometry() const
    {
        m_bounds = sf::FloatRect();

        for (sf::Text& text : m_texts)
            update_text_and_geometry(text);
    }

    ////////////////////////////////////////////////////////////////////////////////
    void RichText::Line::update_text_and_geometry(sf::Text& text) const
    {
        // Set text offset
        text.setPosition(m_bounds.width, 0.f);

        // Update bounds
        const int line_spacing = text.getFont()->getLineSpacing(text.getCharacterSize());
        m_bounds.height = std::max(m_bounds.height, static_cast<float>(line_spacing));
        m_bounds.width += text.getGlobalBounds().width;
    }

    ////////////////////////////////////////////////////////////////////////////////
    RichText::RichText()
    {
    }

    ////////////////////////////////////////////////////////////////////////////////
    RichText::RichText(const Font& font)
        : m_font(font)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////
    std::vector<sf::String> explode(const sf::String& string, sf::Uint32 delimiter)
    {
        if (string.isEmpty())
            return std::vector<sf::String>();

        // For each character in the string
        std::vector<sf::String> result;
        sf::String buffer;
        for (const sf::Uint32 character : string)
        {
            // If we've hit the delimiter character
            if (character == delimiter)
            {
                // Add them to the result vector
                result.push_back(buffer);
                buffer.clear();
            }
            else
            {
                // Accumulate the next character into the sequence
                buffer += character;
            }
        }

        // Add to the result if buffer still has contents or if the last character is a delimiter
        if (!buffer.isEmpty() || string[string.getSize() - 1] == delimiter)
            result.push_back(buffer);

        return result;
    }

    void RichText::set_character_size(unsigned int size)
    {
        // Maybe skip
        if (m_character_size == size)
            return;

        // Update character size
        m_character_size = size;

        // Set texts character size
        for (Line& line : m_lines)
            line.set_character_size(size);

        update_geometry();
    }

    ////////////////////////////////////////////////////////////////////////////////
    void RichText::set_font(const Font& font)
    {
        // Maybe skip
        if (m_font == font)
            return;

        // Update font
        m_font = font;

        // Set texts font
        for (Line& line : m_lines)
            line.set_font(font);

        update_geometry();
    }

    ////////////////////////////////////////////////////////////////////////////////
    void RichText::clear()
    {
        // Clear texts
        m_lines.clear();

        // Reset bounds
        m_bounds = sf::FloatRect();
    }

    RichText& RichText::append(const Text& text)
    {
        // Maybe skip
        if (text.string.empty())
            return *this;

        // Explode into substrings
        std::vector<sf::String> sub_strings = explode(text.string, '\n');

        // Append first substring using the last line
        auto it = sub_strings.begin();
        if (it != sub_strings.end())
        {
            // If there isn't any line, just create it
            if (m_lines.empty())
                m_lines.resize(1);

            // Remove last line's height
            Line& line = m_lines.back();
            m_bounds.height -= line.get_global_bounds().height;

            // Append text
            line.append_text(
                create_text(*it, text.color, text.outline, text.thickness, text.style));

            // Update bounds
            m_bounds.height += line.get_global_bounds().height;
            m_bounds.width = std::max(m_bounds.width, line.get_global_bounds().width);
        }

        // Append the rest of substrings as new lines
        while (++it != sub_strings.end())
        {
            Line line;
            line.setPosition(0.f, m_bounds.height);
            line.append_text(
                create_text(*it, text.color, text.outline, text.thickness, text.style));

            // Update bounds
            m_bounds.height += line.get_global_bounds().height;
            m_bounds.width = std::max(m_bounds.width, line.get_global_bounds().width);

            m_lines.push_back(std::move(line));
        }

        // Return
        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////////
    const std::vector<RichText::Line>& RichText::get_lines() const
    {
        return m_lines;
    }

    ////////////////////////////////////////////////////////////////////////////////
    unsigned int RichText::get_character_size() const
    {
        return m_character_size;
    }

    ////////////////////////////////////////////////////////////////////////////////
    const Font& RichText::get_font() const
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
        return getTransform().transformRect(m_bounds);
    }

    ////////////////////////////////////////////////////////////////////////////////
    void RichText::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        for (const Line& line : m_lines)
            target.draw(line, states);
    }

    ////////////////////////////////////////////////////////////////////////////////
    sf::Text RichText::create_text(const sf::String& string, const Color& color,
        const Color& outline, unsigned int thickness, sf::Text::Style style) const
    {
        sf::Text text;
        text.setString(string);
        text.setFillColor(color);
        text.setOutlineColor(outline);
        text.setOutlineThickness(thickness);
        text.setStyle(style);
        text.setCharacterSize(m_character_size);
        if (m_font)
            text.setFont(m_font);

        return text;
    }

    ////////////////////////////////////////////////////////////////////////////////
    void RichText::update_geometry() const
    {
        m_bounds = sf::FloatRect();

        for (Line& line : m_lines)
        {
            line.setPosition(0.f, m_bounds.height);

            m_bounds.height += line.get_global_bounds().height;
            m_bounds.width = std::max(m_bounds.width, line.get_global_bounds().width);
        }
    }
}
