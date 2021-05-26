#include <TGUI/Vector2.hpp>
#include <TGUI/Loading/ImageLoader.hpp>


namespace tgui
{
    std::uint8_t* _ImageLoader_loadFromFile_proxy(
        tgui::ImageLoader* self, const tgui::String& filename, tgui::Vector2u& imageSize)
    {
        auto ptr = self->loadFromFile(filename, imageSize);
        std::uint8_t* raw = ptr.release();
        return raw;
    }

    std::uint8_t* _ImageLoader_loadFromMemory_proxy(tgui::ImageLoader* self,
        const std::uint8_t* data, std::size_t dataSize, tgui::Vector2u& imageSize)
    {
        auto ptr = self->loadFromMemory(data, dataSize, imageSize);
        std::uint8_t* raw = ptr.release();
        return raw;
    }
}
