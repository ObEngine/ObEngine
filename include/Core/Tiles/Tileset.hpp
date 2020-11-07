#pragma once

#include <map>

#include <SFML/Graphics/VertexArray.hpp>

#include <Graphics/RenderTarget.hpp>
#include <Graphics/Texture.hpp>
#include <Scene/Camera.hpp>
#include <Types/Identifiable.hpp>
#include <Types/Serializable.hpp>

namespace obe::Tiles
{
    class Tileset : public Types::Identifiable
    {
    private:
        uint32_t m_firstTileId;
        uint32_t m_columns;
        uint32_t m_count;
        uint32_t m_margin;
        uint32_t m_spacing;
        uint32_t m_tileWidth;
        uint32_t m_tileHeight;
        uint32_t m_imageWidth;
        uint32_t m_imageHeight;
        std::string m_imagePath;
        Graphics::Texture m_image;

    public:
        Tileset(const std::string& id, uint32_t firstTileId, uint32_t count,
            const std::string& imagePath, uint32_t columns, uint32_t tileWidth,
            uint32_t tileHeight, uint32_t margin = 0, uint32_t spacing = 0);
        uint32_t getFirstTileId() const;
        uint32_t getLastTileId() const;
        uint32_t getTileCount() const;
        uint32_t getMargin() const;
        uint32_t getSpacing() const;
        uint32_t getTileWidth() const;
        uint32_t getTileHeight() const;
        uint32_t getImageWidth() const;
        uint32_t getImageHeight() const;
        std::string getImagePath() const;
        Graphics::Texture getTexture() const;
    };

    class TilesetCollection
    {
    private:
        std::vector<std::unique_ptr<Tileset>> m_tilesets;

    public:
        TilesetCollection();
        void addTileset(uint32_t firstTileId, const std::string& id,
            const std::string& source, uint32_t columns, uint32_t width, uint32_t height,
            uint32_t count);
        [[nodiscard]] const Tileset& tilesetFromId(const std::string& id) const;
        [[nodiscard]] const Tileset& tilesetFromTileId(uint32_t tileId) const;
        [[nodiscard]] const size_t size() const;
        [[nodiscard]] std::vector<uint32_t> getTilesetsFirstTilesIds() const;
    };
} // namespace obe::Scene