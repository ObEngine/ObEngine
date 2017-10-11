#include <Editor/TGUIFallback.hpp>

namespace obe
{
    namespace tguif
    {
        int bindRight(tgui::Widget::Ptr widget)
        {
            return widget->getPosition().x + widget->getSize().x;
        }

        int bindBottom(tgui::Widget::Ptr widget)
        {
            return widget->getPosition().y + widget->getSize().y;
        }

        int bindLeft(tgui::Widget::Ptr widget)
        {
            return widget->getPosition().x;
        }

        int bindTop(tgui::Widget::Ptr widget)
        {
            return widget->getPosition().y;
        }

        int bindWidth(tgui::Widget::Ptr widget)
        {
            return widget->getSize().x;
        }

        int bindHeight(tgui::Widget::Ptr widget)
        {
            return widget->getSize().y;
        }
    }
}