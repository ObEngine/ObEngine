#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Texture.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassTexture(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Texture> bindTexture = tguiNamespace.new_usertype<tgui::Texture>(
            "Texture", sol::call_constructor,
            sol::constructors<tgui::Texture(), tgui::Texture(const char*),
                tgui::Texture(const char*, const tgui::UIntRect&),
                tgui::Texture(const char*, const tgui::UIntRect&, const tgui::UIntRect&),
                tgui::Texture(const char*, const tgui::UIntRect&, const tgui::UIntRect&, bool),
                tgui::Texture(const tgui::String&),
                tgui::Texture(const tgui::String&, const tgui::UIntRect&),
                tgui::Texture(const tgui::String&, const tgui::UIntRect&, const tgui::UIntRect&),
                tgui::Texture(
                    const tgui::String&, const tgui::UIntRect&, const tgui::UIntRect&, bool),
                tgui::Texture(const tgui::Texture&)>());
        bindTexture["operator="]
            = sol::overload(static_cast<tgui::Texture& (tgui::Texture::*)(const tgui::Texture&)>(
                                &tgui::Texture::operator=),
                static_cast<tgui::Texture& (tgui::Texture::*)(tgui::Texture &&)>(
                    &tgui::Texture::operator=));
        bindTexture["load"] = sol::overload(
            [](tgui::Texture* self, const tgui::String& id) -> void { return self->load(id); },
            [](tgui::Texture* self, const tgui::String& id,
                const tgui::UIntRect& partRect) -> void { return self->load(id, partRect); },
            [](tgui::Texture* self, const tgui::String& id, const tgui::UIntRect& partRect,
                const tgui::UIntRect& middleRect) -> void {
                return self->load(id, partRect, middleRect);
            },
            [](tgui::Texture* self, const tgui::String& id, const tgui::UIntRect& partRect,
                const tgui::UIntRect& middleRect,
                bool smooth) -> void { return self->load(id, partRect, middleRect, smooth); },
            [](tgui::Texture* self, tgui::Vector2u size, const std::uint8_t* pixels) -> bool {
                return self->load(size, pixels);
            },
            [](tgui::Texture* self, tgui::Vector2u size, const std::uint8_t* pixels,
                const tgui::UIntRect& partRect) -> bool {
                return self->load(size, pixels, partRect);
            },
            [](tgui::Texture* self, tgui::Vector2u size, const std::uint8_t* pixels,
                const tgui::UIntRect& partRect, const tgui::UIntRect& middleRect) -> bool {
                return self->load(size, pixels, partRect, middleRect);
            });
        bindTexture["loadFromMemory"] = sol::overload(
            [](tgui::Texture* self, const std::uint8_t* data, std::size_t dataSize) -> void {
                return self->loadFromMemory(data, dataSize);
            },
            [](tgui::Texture* self, const std::uint8_t* data, std::size_t dataSize,
                const tgui::UIntRect& partRect) -> void {
                return self->loadFromMemory(data, dataSize, partRect);
            },
            [](tgui::Texture* self, const std::uint8_t* data, std::size_t dataSize,
                const tgui::UIntRect& partRect, const tgui::UIntRect& middleRect) -> void {
                return self->loadFromMemory(data, dataSize, partRect, middleRect);
            },
            [](tgui::Texture* self, const std::uint8_t* data, std::size_t dataSize,
                const tgui::UIntRect& partRect, const tgui::UIntRect& middleRect,
                bool smooth) -> void {
                return self->loadFromMemory(data, dataSize, partRect, middleRect, smooth);
            });
        bindTexture["loadFromPixelData"] = sol::overload(
            [](tgui::Texture* self, tgui::Vector2u size, const std::uint8_t* pixels) -> void {
                return self->loadFromPixelData(size, pixels);
            },
            [](tgui::Texture* self, tgui::Vector2u size, const std::uint8_t* pixels,
                const tgui::UIntRect& partRect) -> void {
                return self->loadFromPixelData(size, pixels, partRect);
            },
            [](tgui::Texture* self, tgui::Vector2u size, const std::uint8_t* pixels,
                const tgui::UIntRect& partRect, const tgui::UIntRect& middleRect) -> void {
                return self->loadFromPixelData(size, pixels, partRect, middleRect);
            },
            [](tgui::Texture* self, tgui::Vector2u size, const std::uint8_t* pixels,
                const tgui::UIntRect& partRect, const tgui::UIntRect& middleRect,
                bool smooth) -> void {
                return self->loadFromPixelData(size, pixels, partRect, middleRect, smooth);
            });
        bindTexture["getId"] = &tgui::Texture::getId;
        bindTexture["getData"] = &tgui::Texture::getData;
        bindTexture["getImageSize"] = &tgui::Texture::getImageSize;
        bindTexture["getPartRect"] = &tgui::Texture::getPartRect;
        bindTexture["isSmooth"] = &tgui::Texture::isSmooth;
        bindTexture["setColor"] = &tgui::Texture::setColor;
        bindTexture["getColor"] = &tgui::Texture::getColor;
        bindTexture["getMiddleRect"] = &tgui::Texture::getMiddleRect;
        bindTexture["isTransparentPixel"] = &tgui::Texture::isTransparentPixel;
        bindTexture["setCopyCallback"] = &tgui::Texture::setCopyCallback;
        bindTexture["setDestructCallback"] = &tgui::Texture::setDestructCallback;
        bindTexture[sol::meta_function::equal_to] = &tgui::Texture::operator==;
        bindTexture["setBackendTextureLoader"] = &tgui::Texture::setBackendTextureLoader;
        bindTexture["getBackendTextureLoader"] = &tgui::Texture::getBackendTextureLoader;
        bindTexture["setTextureLoader"] = &tgui::Texture::setTextureLoader;
        bindTexture["getTextureLoader"] = &tgui::Texture::getTextureLoader;
    }
};