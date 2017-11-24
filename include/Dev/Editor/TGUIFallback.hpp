#pragma once

#include <TGUI/Widget.hpp>

namespace obe
{
    /**
     * \brief TGUI Fallback
     */
    namespace tguif
    {
        int bindRight(tgui::Widget::Ptr widget);
        int bindBottom(tgui::Widget::Ptr widget);
        int bindLeft(tgui::Widget::Ptr widget);
        int bindTop(tgui::Widget::Ptr widget);
        int bindWidth(tgui::Widget::Ptr widget);
        int bindHeight(tgui::Widget::Ptr widget);
    }
}
