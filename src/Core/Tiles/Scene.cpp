#include <Debug/Logger.hpp>
#include <Scene/Scene.hpp>
#include <Tiles/Exceptions.hpp>
#include <Tiles/Scene.hpp>

namespace obe::tiles
{
    void TileScene::build()
    {
        debug::Log->info(
            "Build TileScene @{} with Animations @{}", fmt::ptr(this), fmt::ptr(&m_animated_tiles));
        for (const auto& layer : m_layers)
        {
            layer->build();
        }
    }

    TileScene::TileScene(scene::Scene& scene)
        : m_scene(scene)
    {
    }

    vili::node TileScene::schema() const
    {
        return vili::object {};
    }

    vili::node TileScene::dump() const
    {
        return vili::object {};
    }

    void TileScene::load(const vili::node& data)
    {
        m_width = data["width"];
        m_height = data["height"];
        m_tile_width = data["tileWidth"];
        m_tile_height = data["tileHeight"];
        if (data.contains("smooth"))
        {
            m_smooth = data["smooth"];
        }

        const vili::node& tilesets = data["sources"];
        for (const auto& [tileset_id, tileset] : tilesets.items())
        {
            m_tilesets.add_tileset(tileset["firstTileId"], tileset_id, tileset["image"]["path"],
                tileset["columns"], tileset["tile"]["width"], tileset["tile"]["height"],
                tileset["tilecount"]);

            const Tileset& current_tileset = m_tilesets.tileset_from_id(tileset_id);
            if (tileset.contains("animations"))
            {
                for (const vili::node& animation : tileset.at("animations"))
                {
                    std::vector<time::TimeUnit> sleeps;
                    std::vector<uint32_t> tile_ids;
                    for (const vili::node& frame : animation.at("frames"))
                    {
                        const uint32_t sleep_milliseconds = frame.at("clock");
                        sleeps.push_back(
                            static_cast<double>(sleep_milliseconds) * time::milliseconds);
                        uint32_t full_tile_id
                            = static_cast<uint32_t>(frame.at("tileid").as<vili::integer>()
                                + tileset.at("firstTileId").as<vili::integer>());
                        tile_ids.push_back(full_tile_id);
                    }
                    m_animated_tiles.push_back(
                        std::make_unique<AnimatedTile>(current_tileset, tile_ids, sleeps));
                }
            }
            if (tileset.contains("collisions"))
            {
                for (const vili::node& collision : tileset.at("collisions"))
                {
                    const std::string collision_id
                        = std::to_string(collision.at("id").as<vili::integer>()
                            + tileset.at("firstTileId").as<vili::integer>());
                    std::unique_ptr<collision::PolygonalCollider> model
                        = std::make_unique<collision::PolygonalCollider>(collision_id);
                    model->load(collision);
                    m_collider_models.push_back(std::move(model));
                }
            }
            if (tileset.contains("objects"))
            {
                for (const vili::node& game_object : tileset.at("objects"))
                {
                    m_game_objects_models.push_back(game_object);
                }
            }
        }

        AnimatedTiles animations = this->get_animated_tiles();

        const vili::node& layers = data["layers"];
        for (const auto& [layer_id, layer] : layers.items())
        {
            std::vector<uint32_t> tiles;
            tiles.reserve(layer["tiles"].size());
            for (const uint32_t tile : layer["tiles"])
            {
                tiles.push_back(tile);
            }
            bool visible = true;
            if (layer.contains("visible"))
            {
                visible = layer.at("visible");
            }

            m_layers.push_back(std::make_unique<TileLayer>(*this, layer_id, layer["layer"],
                layer["x"], layer["y"], layer["width"], layer["height"], tiles, visible));
        }

        this->build();

        for (const auto& animation : m_animated_tiles)
        {
            animation->start();
        }
    }

    void TileScene::update() const
    {
        for (const auto& animation : m_animated_tiles)
        {
            animation->update();
        }
    }

    void TileScene::clear()
    {
        m_tilesets.clear();
        m_layers.clear();
        m_animated_tiles.clear();
        m_collider_models.clear();
        m_width = 0;
        m_height = 0;
        m_tile_width = 0;
        m_tile_height = 0;
    }

    std::vector<TileLayer*> TileScene::get_all_layers() const
    {
        std::vector<TileLayer*> layers;
        std::transform(m_layers.begin(), m_layers.end(), std::back_inserter(layers),
            [](const auto& layer) { return layer.get(); });
        return layers;
    }

    std::vector<std::string> TileScene::get_layers_ids() const
    {
        std::vector<std::string> layers_names;
        layers_names.reserve(m_layers.size());
        for (const auto& layer : m_layers)
        {
            layers_names.push_back(layer->get_id());
        }
        return layers_names;
    }

    TileLayer& TileScene::get_layer(const std::string& id) const
    {
        for (const auto& layer : m_layers)
        {
            if (layer->get_id() == id)
            {
                return *layer;
            }
        }

        throw exceptions::UnknownTileLayer(id, this->get_layers_ids(), EXC_INFO);
    }

    AnimatedTiles TileScene::get_animated_tiles() const
    {
        AnimatedTiles animations;
        for (const auto& animation : m_animated_tiles)
        {
            animations.push_back(animation.get());
        }
        return animations;
    }

    const TilesetCollection& TileScene::get_tilesets() const
    {
        return m_tilesets;
    }

    std::vector<graphics::Renderable*> TileScene::get_renderables() const
    {
        std::vector<graphics::Renderable*> result;
        for (const auto& layer : m_layers)
        {
            result.push_back(layer.get());
        }
        return result;
    }

    std::vector<collision::PolygonalCollider*> TileScene::get_collider_models() const
    {
        std::vector<collision::PolygonalCollider*> result;
        for (const auto& collider : m_collider_models)
        {
            result.push_back(collider.get());
        }
        return result;
    }

    const std::vector<vili::node>& TileScene::get_game_objects_models() const
    {
        return m_game_objects_models;
    }

    uint32_t TileScene::get_width() const
    {
        return m_width;
    }

    uint32_t TileScene::get_height() const
    {
        return m_height;
    }

    uint32_t TileScene::get_tile_width() const
    {
        return m_tile_width;
    }

    uint32_t TileScene::get_tile_height() const
    {
        return m_tile_height;
    }

    bool TileScene::is_anti_aliased() const
    {
        return m_smooth;
    }

    scene::Scene& TileScene::get_scene() const
    {
        return m_scene;
    }
}
