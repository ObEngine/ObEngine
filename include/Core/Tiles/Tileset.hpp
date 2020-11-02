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
    class Tile
    {
    private:
        const Graphics::Texture& m_texture;
        unsigned int m_x;
        unsigned int m_y;

    public:
        Tile(const Graphics::Texture& texture, unsigned int x, unsigned int y);
    };

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
        Tileset(const std::string& id, const std::string& imagePath, uint32_t columns,
            uint32_t tileWidth, uint32_t tileHeight, uint32_t margin = 0,
            uint32_t spacing = 0);
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

    struct TileLayer
    {
        std::string id;
        uint32_t x;
        uint32_t y;
        uint32_t width;
        uint32_t height;
        bool visible = true;
        double opacity = 1.0;
        std::vector<uint32_t> data;

        TileLayer(const std::string& id, uint32_t x, uint32_t y, uint32_t width,
            uint32_t height, const std::vector<uint32_t>& data);
    };

    class TileScene : public Types::Serializable
    {
    private:
        uint32_t m_tileWidth;
        uint32_t m_tileHeight;
        std::map<int32_t, std::unique_ptr<Tileset>> m_tilesets;
        std::vector<std::unique_ptr<TileLayer>> m_layers;
        std::vector<sf::VertexArray> m_cache;

        void buildCache();
        sf::VertexArray buildLayer(const TileLayer& layer);

    public:
        Tileset& tilesetFromTileId(uint32_t tileId) const;
        vili::node dump() const;
        void load(const vili::node& data) override;
        /**
         * \brief Draws all elements of the TileLayer on the screen
         */
        void draw(Graphics::RenderTarget surface, const Scene::Camera& camera);
    };
} // namespace obe::Scene