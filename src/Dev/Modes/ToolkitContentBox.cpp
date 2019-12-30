#include <Modes/ToolkitContentBox.hpp>
#include <TGUI/Clipping.hpp>

/// TODO: Same font for all lines?

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    static std::map<std::string, ObjectConverter> defaultRendererValues
        = { { "borders", Borders{ 2 } }, { "padding", Padding{ 2, 0, 0, 0 } },
              { "bordercolor", sf::Color::Black }, { "backgroundcolor", Color{ 245, 245, 245 } } };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ToolkitContentBox::ToolkitContentBox()
    {
        m_type = "ToolkitContentBox";
        m_draggableWidget = true;

        m_renderer = aurora::makeCopied<ChatBoxRenderer>();
        setRenderer(RendererData::create(defaultRendererValues));

        setSize({ 200, 126 });
        setTextSize(m_textSize);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ToolkitContentBox::Ptr ToolkitContentBox::create()
    {
        return std::make_shared<ToolkitContentBox>();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ToolkitContentBox::Ptr ToolkitContentBox::copy(ConstPtr chatBox)
    {
        if (chatBox)
            return std::static_pointer_cast<ToolkitContentBox>(chatBox->clone());
        return nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ToolkitContentBox::setPosition(const Layout2d& position)
    {
        Widget::setPosition(position);

        m_scroll.setPosition(getSize().x - m_bordersCached.getRight() - m_paddingCached.getRight()
                - m_scroll.getSize().x,
            m_bordersCached.getTop() + m_paddingCached.getTop());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ToolkitContentBox::setSize(const Layout2d& size)
    {
        Widget::setSize(size);

        m_spriteBackground.setSize(getInnerSize());

        m_bordersCached.updateParentSize(getSize());
        m_paddingCached.updateParentSize(getSize());

        updateRendering();
        setPosition(m_position);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ToolkitContentBox::addLine(const sfe::RichText& text)
    {
        // Remove the oldest line if you exceed the maximum
        if ((m_maxLines > 0) && (m_maxLines == m_lines.size()))
        {
            if (m_newLinesBelowOthers)
                removeLine(0);
            else
                removeLine(m_maxLines - 1);
        }

        sfe::RichText newtext = text;
        recalculateLineText(newtext);

        if (m_newLinesBelowOthers)
            m_lines.push_back(std::move(newtext));
        else
            m_lines.push_front(std::move(newtext));

        recalculateFullTextHeight();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::String ToolkitContentBox::getLine(size_t lineIndex) const
    {
        if (lineIndex < m_lines.size())
        {
            sf::String totalString;
            for (auto& line : m_lines[lineIndex].getLines())
            {
                for (auto& text : line.getTexts())
                {
                    totalString += text.getString();
                }
            }
            return totalString;
        }
        // Index too high
        return "";
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::Color ToolkitContentBox::getLineColor(size_t lineIndex) const
    {
        if (lineIndex < m_lines.size())
        {
        }
        // Index too high
        return m_textColor;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::shared_ptr<sf::Font> ToolkitContentBox::getLineFont(size_t lineIndex) const
    {
        if (lineIndex < m_lines.size())
        {
            // return m_lines[lineIndex].text.getFont();
        }
        // Index too high
        return m_fontCached;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool ToolkitContentBox::removeLine(size_t lineIndex)
    {
        if (lineIndex < m_lines.size())
        {
            m_lines.erase(m_lines.begin() + lineIndex);

            recalculateFullTextHeight();
            return true;
        }
        // Index too high
        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ToolkitContentBox::removeAllLines()
    {
        m_lines.clear();

        recalculateFullTextHeight();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    size_t ToolkitContentBox::getLineAmount()
    {
        return m_lines.size();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ToolkitContentBox::setLineLimit(size_t maxLines)
    {
        m_maxLines = maxLines;

        // Remove the oldest lines if there are too many lines
        if ((m_maxLines > 0) && (m_maxLines < m_lines.size()))
        {
            if (m_newLinesBelowOthers)
                m_lines.erase(m_lines.begin(), m_lines.begin() + m_lines.size() - m_maxLines);
            else
                m_lines.erase(m_lines.begin() + m_maxLines, m_lines.end());

            recalculateFullTextHeight();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    size_t ToolkitContentBox::getLineLimit()
    {
        return m_maxLines;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ToolkitContentBox::setTextSize(unsigned int size)
    {
        // Store the new text size
        m_textSize = size;

        // There is a minimum text size
        if (m_textSize < 8)
            m_textSize = 8;

        m_scroll.setScrollAmount(size);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int ToolkitContentBox::getTextSize() const
    {
        return m_textSize;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ToolkitContentBox::setTextColor(Color color)
    {
        m_textColor = color;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::Color& ToolkitContentBox::getTextColor() const
    {
        return m_textColor;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ToolkitContentBox::setLinesStartFromTop(bool startFromTop)
    {
        if (m_linesStartFromTop != startFromTop)
            m_linesStartFromTop = startFromTop;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool ToolkitContentBox::getLinesStartFromTop() const
    {
        return m_linesStartFromTop;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ToolkitContentBox::setNewLinesBelowOthers(bool newLinesBelowOthers)
    {
        m_newLinesBelowOthers = newLinesBelowOthers;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool ToolkitContentBox::getNewLinesBelowOthers() const
    {
        return m_newLinesBelowOthers;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool ToolkitContentBox::mouseOnWidget(sf::Vector2f pos) const
    {
        return sf::FloatRect{ 0, 0, getSize().x, getSize().y }.contains(pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ToolkitContentBox::leftMousePressed(sf::Vector2f pos)
    {
        // Set the mouse down flag to true
        m_mouseDown = true;

        // Pass the event to the scrollbar
        if (m_scroll.mouseOnWidget(pos - m_scroll.getPosition()))
            m_scroll.leftMousePressed(pos - m_scroll.getPosition());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ToolkitContentBox::leftMouseReleased(sf::Vector2f pos)
    {
        if (m_scroll.isMouseDown())
            m_scroll.leftMouseReleased(pos - m_scroll.getPosition());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ToolkitContentBox::mouseMoved(sf::Vector2f pos)
    {
        if (!m_mouseHover)
            mouseEnteredWidget();

        // Pass the event to the scrollbar when the mouse is on top of it or
        // when we are dragging its thumb
        if (((m_scroll.isMouseDown()) && (m_scroll.isMouseDownOnThumb()))
            || m_scroll.mouseOnWidget(pos - m_scroll.getPosition()))
            m_scroll.mouseMoved(pos - m_scroll.getPosition());
        else
            m_scroll.mouseNoLongerOnWidget();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ToolkitContentBox::mouseNoLongerOnWidget()
    {
        Widget::mouseNoLongerOnWidget();
        m_scroll.mouseNoLongerOnWidget();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ToolkitContentBox::mouseNoLongerDown()
    {
        Widget::mouseNoLongerDown();
        m_scroll.mouseNoLongerDown();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ToolkitContentBox::mouseWheelScrolled(float delta, sf::Vector2f pos)
    {
        if (m_scroll.getLowValue() < m_scroll.getMaximum())
            m_scroll.mouseWheelScrolled(delta, sf::Vector2f(0, 0));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ToolkitContentBox::recalculateLineText(sfe::RichText& line) const
    {

        // Find the maximum width of one line
        float maxWidth = getInnerSize().x - m_scroll.getSize().x - m_paddingCached.getLeft()
            - m_paddingCached.getRight();
        if (maxWidth < 0)
            return;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ToolkitContentBox::recalculateAllLines()
    {
        for (auto& line : m_lines)
            recalculateLineText(line);

        recalculateFullTextHeight();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ToolkitContentBox::recalculateFullTextHeight()
    {
        m_fullTextHeight = 0;
        for (const auto& line : m_lines)
            m_fullTextHeight += line.getGlobalBounds().height;

        // Update the maximum of the scrollbar
        unsigned int oldMaximum = m_scroll.getMaximum();
        m_scroll.setMaximum(static_cast<unsigned int>(m_fullTextHeight));

        // Scroll down to the last item when there is a scrollbar and it is at
        // the bottom
        if (m_newLinesBelowOthers)
        {
            if (((oldMaximum >= m_scroll.getLowValue())
                    && (m_scroll.getValue() == oldMaximum - m_scroll.getLowValue()))
                || ((oldMaximum <= m_scroll.getLowValue())
                       && (m_scroll.getMaximum() > m_scroll.getLowValue())))
            {
                m_scroll.setValue(m_scroll.getMaximum() - m_scroll.getLowValue());
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ToolkitContentBox::updateRendering()
    {
        m_scroll.setSize({ m_scroll.getSize().x,
            getInnerSize().y - m_paddingCached.getTop() - m_paddingCached.getBottom() });
        m_scroll.setLowValue(static_cast<unsigned int>(
            getInnerSize().y - m_paddingCached.getTop() - m_paddingCached.getBottom()));

        recalculateAllLines();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ToolkitContentBox::rendererChanged(const std::string& property)
    {
        if (property == "borders")
        {
            m_bordersCached = getRenderer()->getBorders();
            setSize(m_size);
        }
        else if (property == "padding")
        {
            m_paddingCached = getRenderer()->getPadding();
            setSize(m_size);
        }
        else if (property == "texturebackground")
        {
            m_spriteBackground.setTexture(getRenderer()->getTextureBackground());
        }
        else if (property == "scrollbar")
        {
            m_scroll.setRenderer(getRenderer()->getScrollbar());
        }
        else if (property == "bordercolor")
        {
            m_borderColorCached = getRenderer()->getBorderColor();
        }
        else if (property == "backgroundcolor")
        {
            m_backgroundColorCached = getRenderer()->getBackgroundColor();
        }
        else if (property == "opacity")
        {
            Widget::rendererChanged(property);

            m_spriteBackground.setOpacity(m_opacityCached);
            m_scroll.getRenderer()->setOpacity(m_opacityCached);
            for (auto& line : m_lines)
            {
                for (auto& subline : line.getLines())
                {
                    for (auto& subtext : subline.getTexts())
                    {
                        // OPACITY <REVISION>
                    }
                }
            }
        }
        else if (property == "font")
        {
            Widget::rendererChanged(property);

            if (m_fontCached != nullptr)
            {
                // Look for lines that did not have a font yet and give them
                // this font
                bool lineChanged = false;
                for (auto& line : m_lines)
                {
                }

                if (lineChanged)
                    recalculateAllLines();
            }
        }
        else
            Widget::rendererChanged(property);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::Vector2f ToolkitContentBox::getInnerSize() const
    {
        return { getSize().x - m_bordersCached.getLeft() - m_bordersCached.getRight(),
            getSize().y - m_bordersCached.getTop() - m_bordersCached.getBottom() };
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ToolkitContentBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform.translate(getPosition());

        sf::RenderStates scrollbarStates = states;

        // Draw the borders
        if (m_bordersCached != Borders{ 0 })
        {
            drawBorders(target, states, m_bordersCached, getSize(), m_borderColorCached);
            states.transform.translate({ m_bordersCached.getLeft(), m_bordersCached.getTop() });
        }

        // Draw the background
        if (m_spriteBackground.isSet())
            m_spriteBackground.draw(target, states);
        else
            drawRectangleShape(target, states, getInnerSize(), m_backgroundColorCached);

        states.transform.translate({ m_paddingCached.getLeft(), m_paddingCached.getTop() });

        // Draw the scrollbar
        m_scroll.draw(target, scrollbarStates);

        // Set the clipping for all draw calls that happen until this clipping
        // object goes out of scope
        Clipping clipping{ target, states, {},
            { getInnerSize().x - m_paddingCached.getLeft() - m_paddingCached.getRight()
                    - m_scroll.getSize().x,
                getInnerSize().y - m_paddingCached.getTop() - m_paddingCached.getBottom() } };

        states.transform.translate({ 0, -static_cast<float>(m_scroll.getValue()) });

        // Put the lines at the bottom of the chat box if needed
        if (!m_linesStartFromTop
            && (m_fullTextHeight
                   < getInnerSize().y - m_paddingCached.getTop() - m_paddingCached.getBottom()))
            states.transform.translate(0,
                getInnerSize().y - m_paddingCached.getTop() - m_paddingCached.getBottom()
                    - m_fullTextHeight);

        for (const auto& line : m_lines)
        {
            target.draw(line, states);
            states.transform.translate(0, line.getGlobalBounds().height);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace tgui

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
