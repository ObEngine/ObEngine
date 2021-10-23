/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2021 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <TGUI/Renderers/ChildWindowRenderer.hpp>
#include <TGUI/RendererDefines.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    TGUI_RENDERER_PROPERTY_OUTLINE(ChildWindowRenderer, Borders)

    TGUI_RENDERER_PROPERTY_COLOR(ChildWindowRenderer, TitleBarColor, Color::White)
    TGUI_RENDERER_PROPERTY_COLOR(ChildWindowRenderer, TitleColor, Color::Black)
    TGUI_RENDERER_PROPERTY_COLOR(ChildWindowRenderer, BackgroundColor, Color::White)
    TGUI_RENDERER_PROPERTY_COLOR(ChildWindowRenderer, BorderColor, Color::Black)
    TGUI_RENDERER_PROPERTY_COLOR(ChildWindowRenderer, BorderColorFocused, {})

    TGUI_RENDERER_PROPERTY_TEXTURE(ChildWindowRenderer, TextureTitleBar)
    TGUI_RENDERER_PROPERTY_TEXTURE(ChildWindowRenderer, TextureBackground)

    TGUI_RENDERER_PROPERTY_RENDERER(ChildWindowRenderer, CloseButton, "ChildWindowButton")
    TGUI_RENDERER_PROPERTY_RENDERER(ChildWindowRenderer, MaximizeButton, "ChildWindowButton")
    TGUI_RENDERER_PROPERTY_RENDERER(ChildWindowRenderer, MinimizeButton, "ChildWindowButton")

    TGUI_RENDERER_PROPERTY_NUMBER(ChildWindowRenderer, BorderBelowTitleBar, 0)
    TGUI_RENDERER_PROPERTY_NUMBER(ChildWindowRenderer, DistanceToSide, 3)
    TGUI_RENDERER_PROPERTY_NUMBER(ChildWindowRenderer, PaddingBetweenButtons, 1)
    TGUI_RENDERER_PROPERTY_NUMBER(ChildWindowRenderer, MinimumResizableBorderWidth, 10)

    TGUI_RENDERER_PROPERTY_BOOL(ChildWindowRenderer, ShowTextOnTitleButtons, false)

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float ChildWindowRenderer::getTitleBarHeight() const
    {
        auto it = m_data->propertyValuePairs.find("TitleBarHeight");
        if (it != m_data->propertyValuePairs.end())
            return it->second.getNumber();
        else
        {
            it = m_data->propertyValuePairs.find("TextureTitleBar");
            if (it != m_data->propertyValuePairs.end() && it->second.getTexture().getData())
                return static_cast<float>(it->second.getTexture().getImageSize().y);
            else
                return 20;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void ChildWindowRenderer::setTitleBarHeight(float number)
    {
        setProperty("TitleBarHeight", ObjectConverter{number});
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
