#include <Scene/Scene.hpp>
#include <Tiles/Layer.hpp>
#include <Tiles/Scene.hpp>

#include "Debug/Logger.hpp"

namespace obe::Tiles
{
    void TileScene::build()
    {
        Debug::Log->info("Build TileScene @{} with Animations @{}", fmt::ptr(this),
            fmt::ptr(&m_animatedTiles));
        for (auto& layer : m_layers)
        {
            layer->build();
        }
    }

    TileScene::TileScene(Scene::Scene& scene)
        : m_scene(scene)
    {
    }

    vili::node TileScene::dump() const
    {
        return vili::object {};
    }

    void TileScene::load(const vili::node& data)
    {
        m_width = data["width"];
        m_height = data["height"];
        m_tileWidth = data["tileWidth"];
        m_tileHeight = data["tileHeight"];

        const vili::node& tilesets = data["sources"];
        for (const auto& [tilesetId, tileset] : tilesets.items())
        {
            m_tilesets.addTileset(tileset["firstTileId"], tilesetId,
                tileset["image"]["path"], tileset["columns"], tileset["tile"]["width"],
                tileset["tile"]["height"], tileset["tilecount"]);

            const Tileset& currentTileset = m_tilesets.tilesetFromId(tilesetId);
            if (tileset.contains("animations"))
            {
                for (const vili::node& animation : tileset.at("animations"))
                {
                    std::vector<Time::TimeUnit> sleeps;
                    std::vector<uint32_t> tileIds;
                    for (const vili::node& frame : animation.at("frames"))
                    {
                        const uint32_t sleepMilliseconds = frame.at("clock");
                        sleeps.push_back(
                            static_cast<double>(sleepMilliseconds) * Time::milliseconds);
                        tileIds.push_back(frame.at("tileid").as<vili::integer>()
                            + tileset.at("firstTileId").as<vili::integer>());
                    }
                    m_animatedTiles.push_back(
                        std::make_unique<AnimatedTile>(currentTileset, tileIds, sleeps));
                }
            }
            if (tileset.contains("collisions"))
            {
                for (const vili::node& collision : tileset.at("collisions"))
                {
                    const std::string collisionId
                        = std::to_string(collision.at("id").as<vili::integer>()
                            + tileset.at("firstTileId").as<vili::integer>());
                    std::unique_ptr<Collision::PolygonalCollider> model
                        = std::make_unique<Collision::PolygonalCollider>(collisionId);
                    int i = 0;
                    for (const vili::node& point : collision.at("points"))
                    {
                        model->addPoint(Transform::UnitVector(
                            point.at("x"), point.at("y"), Transform::Units::ScenePixels));
                        Transform::PolygonPoint pointDbg = model->get(i);
                        Debug::Log->info("  - BUILD[{}] P{} = ({}, {})", collisionId, i,
                            pointDbg.x, pointDbg.y);
                        i++;
                    }

                    m_colliderModels.push_back(std::move(model));
                }
            }
            if (tileset.contains("objects"))
            {
                for (const vili::node& gameObject : tileset.at("objects"))
                {
                    m_gameObjectsModels.push_back(gameObject);
                }
            }
        }

        AnimatedTiles animations = this->getAnimatedTiles();

        const vili::node& layers = data["layers"];
        for (const auto& [layerId, layer] : layers.items())
        {
            std::vector<uint32_t> tiles;
            tiles.reserve(layer["tiles"].size());
            for (const uint32_t tile : layer["tiles"])
            {
                tiles.push_back(tile);
            }
            m_layers.push_back(std::make_unique<TileLayer>(*this, layerId, layer["layer"],
                layer["x"], layer["y"], layer["width"], layer["height"], tiles));
        }

        this->build();

        for (auto& animation : m_animatedTiles)
        {
            animation->start();
        }
    }

    void TileScene::update()
    {
        for (auto& animation : m_animatedTiles)
        {
            animation->update();
        }
    }

    void TileScene::clear()
    {
        m_tilesets.clear();
        m_layers.clear();
        m_animatedTiles.clear();
        m_colliderModels.clear();
        m_width = 0;
        m_height = 0;
        m_tileWidth = 0;
        m_tileHeight = 0;
    }

    TileLayer& TileScene::getLayer(const std::string& id) const
    {
        for (const auto& layer : m_layers)
        {
            if (layer->getId() == id)
            {
                Debug::Log->info("GetLayer TileScene @{} with Animations @{}",
                    fmt::ptr(this), fmt::ptr(&m_animatedTiles));
                return *layer;
            }
        }
    }

    AnimatedTiles TileScene::getAnimatedTiles() const
    {
        AnimatedTiles animations;
        for (const auto& animation : m_animatedTiles)
        {
            animations.push_back(animation.get());
        }
        return animations;
    }

    const TilesetCollection& TileScene::getTilesets() const
    {
        return m_tilesets;
    }

    std::vector<Graphics::Renderable*> TileScene::getRenderables() const
    {
        std::vector<Graphics::Renderable*> result;
        for (const auto& layer : m_layers)
        {
            result.push_back(layer.get());
        }
        return result;
    }

    std::vector<Collision::PolygonalCollider*> TileScene::getColliderModels() const
    {
        std::vector<Collision::PolygonalCollider*> result;
        for (const auto& collider : m_colliderModels)
        {
            result.push_back(collider.get());
        }
        return result;
    }

    const std::vector<vili::node>& TileScene::getGameObjectsModels() const
    {
        return m_gameObjectsModels;
    }

    uint32_t TileScene::getWidth() const
    {
        return m_width;
    }

    uint32_t TileScene::getHeight() const
    {
        return m_height;
    }

    uint32_t TileScene::getTileWidth() const
    {
        return m_tileWidth;
    }

    uint32_t TileScene::getTileHeight() const
    {
        return m_tileHeight;
    }

    Scene::Scene& TileScene::getScene() const
    {
        return m_scene;
    }
}
