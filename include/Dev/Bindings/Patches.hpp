#pragma once

#include <sol/sol.hpp>
#include <TGUI/GuiBase.hpp>
#include <TGUI/Widget.hpp>


/**
 * \additionalinclude{Bindings/Patches.hpp}
 */
namespace tgui
{
    /**
     * \flagsurrogate{tgui::Any}
     * \nobind
     */
    class _PatchAny {};
    /**
     * \flagsurrogate{tgui::BackendTextureBase::load}
     * \nobind
     */
    class _PatchBackendTextureBaseLoad {};
    /**
     * \flagsurrogate{tgui::Container::operator=}
     * \nobind
     */
    class _PatchContainerOperatorEqual {};
    /**
     * \flagsurrogate{tgui::Widget::operator=}
     * \nobind
     */
    class _PatchWidgetOperatorEqual {};
    /**
     * \flagsurrogate{tgui::TextureManager}
     * \additionalinclude{TGUI/Texture.hpp}
     */
    class _PatchTextureManager {};
    /**
     * \flagsurrogate{tgui::BackendBase}
     * \additionalinclude{TGUI/BackendFont.hpp}
     * \additionalinclude{TGUI/BackendText.hpp}
     * \additionalinclude{TGUI/BackendTexture.hpp}
     */
    class _PatchBackendBase {};
    /**
     * \flagsurrogate{tgui::DefaultBackendWindow}
     * \additionalinclude{TGUI/Event.hpp}
     */
    class _PatchDefaultBackendWindow {};

    class ImageLoader;

    /**
     * \flagsurrogate{tgui::ImageLoader}
     * \additionalinclude{Bindings/Patches.hpp}
     */
    class _PatchImageLoader {};

    template <class U>
    class Vector2;

    using Vector2u = Vector2<unsigned int>;

    class String;

    /**
     * \proxy{tgui::ImageLoader::loadFromFile}
     */
    std::uint8_t* _ImageLoader_loadFromFile_proxy(
        tgui::ImageLoader* self, const tgui::String& filename, tgui::Vector2u& imageSize);
    /**
     * \proxy{tgui::ImageLoader::loadFromMemory}
     */
    std::uint8_t* _ImageLoader_loadFromMemory_proxy(tgui::ImageLoader* self,
            const std::uint8_t* data, std::size_t dataSize, tgui::Vector2u& imageSize);

    /**
     * \flagsurrogate{tgui::ObjectConverter}
     * \additionalinclude{TGUI/Renderers/WidgetRenderer.hpp}
     */
    class _PatchObjectConverter {};

    /**
     * \flagsurrogate{tgui::Text}
     * \additionalinclude{TGUI/BackendText.hpp}
     */
    class _PatchText {};

    /**
     * \flagsurrogate{tgui::Widget}
     * \additionalinclude{TGUI/Container.hpp}
     * \additionalinclude{TGUI/GuiBase.hpp}
     */
    class _PatchWidget {};

    /**
     * \flagsurrogate{tgui::Serializer::getFunction}
     * \nobind
     * TODO: Replace with proxy method ?
     */
    class _PatchSerializerGetFunction {};
    /**
     * \flagsurrogate{tgui::Serializer::setFunction}
     * \nobind
     * TODO: Replace with proxy method ?
     */
    class _PatchSerializerSetFunction
    {
    };
}
