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


#include <TGUI/Renderers/ScrollbarRenderer.hpp>
#include <TGUI/RendererDefines.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    TGUI_RENDERER_PROPERTY_COLOR(ScrollbarRenderer, TrackColor, Color::White)
    TGUI_RENDERER_PROPERTY_COLOR(ScrollbarRenderer, TrackColorHover, {})
    TGUI_RENDERER_PROPERTY_COLOR(ScrollbarRenderer, ThumbColor, Color(128, 128, 128))
    TGUI_RENDERER_PROPERTY_COLOR(ScrollbarRenderer, ThumbColorHover, {})
    TGUI_RENDERER_PROPERTY_COLOR(ScrollbarRenderer, ArrowBackgroundColor, Color::White)
    TGUI_RENDERER_PROPERTY_COLOR(ScrollbarRenderer, ArrowBackgroundColorHover, {})
    TGUI_RENDERER_PROPERTY_COLOR(ScrollbarRenderer, ArrowColor, Color::Black)
    TGUI_RENDERER_PROPERTY_COLOR(ScrollbarRenderer, ArrowColorHover, {})

    TGUI_RENDERER_PROPERTY_TEXTURE(ScrollbarRenderer, TextureTrack)
    TGUI_RENDERER_PROPERTY_TEXTURE(ScrollbarRenderer, TextureTrackHover)
    TGUI_RENDERER_PROPERTY_TEXTURE(ScrollbarRenderer, TextureThumb)
    TGUI_RENDERER_PROPERTY_TEXTURE(ScrollbarRenderer, TextureThumbHover)
    TGUI_RENDERER_PROPERTY_TEXTURE(ScrollbarRenderer, TextureArrowUp)
    TGUI_RENDERER_PROPERTY_TEXTURE(ScrollbarRenderer, TextureArrowUpHover)
    TGUI_RENDERER_PROPERTY_TEXTURE(ScrollbarRenderer, TextureArrowDown)
    TGUI_RENDERER_PROPERTY_TEXTURE(ScrollbarRenderer, TextureArrowDownHover)
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
