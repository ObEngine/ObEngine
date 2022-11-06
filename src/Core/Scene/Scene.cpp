#include <vili/parser.hpp>

#include <Debug/Render.hpp>
#include <Scene/Exceptions.hpp>
#include <Scene/Scene.hpp>
#include <Utils/MathUtils.hpp>

namespace obe::scene
{
    void Scene::_reorganize_layers()
    {
        m_render_cache.clear();
        for (const auto& sprite : m_sprite_array)
        {
            m_render_cache.push_back(sprite.get());
        }
        if (m_tiles)
        {
            std::vector<graphics::Renderable*> tile_layers = m_tiles->get_renderables();
            m_render_cache.insert(m_render_cache.end(), tile_layers.begin(), tile_layers.end());
        }

        std::sort(m_render_cache.begin(), m_render_cache.end(),
            [](const auto& renderable1, const auto& renderable2) {
                if (renderable1->get_layer() == renderable2->get_layer())
                {
                    return renderable1->get_sublayer() > renderable2->get_sublayer();
                }
                else
                {
                    return renderable1->get_layer() > renderable2->get_layer();
                }
            });
        m_sort_renderables = false;
    }

    void Scene::_rebuild_ids()
    {
        m_sprite_ids.clear();
        m_collider_ids.clear();
        m_game_object_ids.clear();
        for (const auto& item : m_sprite_array)
        {
            m_sprite_ids.emplace(item->get_id());
        }
        for (const auto& item : m_collider_array)
        {
            m_collider_ids.emplace(item->get_id());
        }
        for (const auto& item : m_game_object_array)
        {
            m_game_object_ids.emplace(item->get_id());
        }
    }

    Scene::Scene(event::EventNamespace& event_namespace, sol::state_view lua)
        : m_lua(lua)
        , e_scene(event_namespace.create_group("Scene"))

    {
        e_scene->add<events::Scene::Loaded>();
    }

    graphics::Sprite& Scene::create_sprite(const std::string& id, bool add_to_scene_root)
    {
        std::string create_id = id;
        if (create_id.empty())
        {
            int i = 0;
            std::string test_id = "sprite" + std::to_string(this->get_sprite_amount() + i);
            while (this->does_sprite_exists(test_id))
            {
                test_id = "sprite" + std::to_string(this->get_sprite_amount() + i++);
            }
            create_id = test_id;
        }
        if (!this->does_sprite_exists(create_id))
        {
            std::unique_ptr<graphics::Sprite> new_sprite
                = std::make_unique<graphics::Sprite>(create_id);
            if (m_resources)
                new_sprite->attach_resource_manager(*m_resources);

            graphics::Sprite* return_sprite = new_sprite.get();
            m_sprite_array.push_back(move(new_sprite));
            m_sprite_ids.insert(create_id);
            m_components[create_id] = return_sprite;

            if (add_to_scene_root)
                m_scene_root.add_child(*return_sprite);

            this->reorganize_layers();
            return *return_sprite;
        }
        else
        {
            debug::Log->warn("<Scene> Sprite '{0}' already exists !", create_id);
            return this->get_sprite(create_id);
        }
    }

    collision::ColliderComponent& Scene::create_collider(
        const std::string& id, bool add_to_scene_root)
    {
        std::string create_id = id;
        if (create_id.empty())
        {
            int i = 0;
            std::string test_id = "collider" + std::to_string(this->get_collider_amount() + i);
            while (this->does_collider_exists(test_id))
            {
                test_id = "collider" + std::to_string(this->get_collider_amount() + i++);
            }
            create_id = test_id;
        }
        if (!this->does_collider_exists(create_id))
        {
            std::unique_ptr<collision::ColliderComponent> new_collider
                = std::make_unique<collision::ColliderComponent>(create_id);
            collision::ColliderComponent* collider = new_collider.get();
            m_collider_array.push_back(std::move(new_collider));
            m_collider_ids.insert(create_id);
            m_components[create_id] = collider;
            if (add_to_scene_root)
                m_scene_root.add_child(*m_collider_array.back()->get_inner_collider());
            m_collision_space.add_collider(collider->get_inner_collider());
            return *collider;
        }
        else
        {
            debug::Log->warn("<Scene> Collider '{0}' already exists !", create_id);
            return this->get_collider(create_id);
        }
    }

    std::size_t Scene::get_collider_amount() const
    {
        return m_collider_array.size();
    }

    std::string Scene::get_filesystem_path() const
    {
        return m_base_folder;
    }

    void Scene::reload()
    {
        debug::Log->debug("<Scene> Reloading Scene");
        m_deferred_scene_load = m_level_file_name;
    }

    void Scene::reload(const OnSceneLoadCallback& callback)
    {
        debug::Log->debug("<Scene> Reloading Scene");
        m_deferred_scene_load = m_level_file_name;
        m_on_load_callback = callback;
    }

    void Scene::load_from_file(const std::string& path)
    {
        debug::Log->debug("<Scene> Loading Scene from map file : '{0}'", path);
        this->clear();
        debug::Log->debug("<Scene> Cleared Scene");

        m_level_file_name = path;
        const std::string filepath = system::Path(path).find();
        vili::node scene_file;
        try
        {
            scene_file = vili::parser::from_file(filepath);
        }
        catch (const std::exception& e)
        {
            throw exceptions::InvalidSceneFile(filepath, EXC_INFO).nest(e);
        }
        this->load(scene_file);
    }

    void Scene::set_future_load_from_file(const std::string& path)
    {
        m_deferred_scene_load = path;
    }

    void Scene::set_future_load_from_file(
        const std::string& path, const OnSceneLoadCallback& callback)
    {
        m_deferred_scene_load = path;
        m_on_load_callback = callback;
    }

    void Scene::clear()
    {
        if (m_resources)
        {
            m_resources->clean();
        }
        for (auto it = m_game_object_array.rbegin(); it != m_game_object_array.rend(); ++it)
        {
            script::GameObject* game_object = it->get();
            if (!game_object->is_permanent())
            {
                debug::Log->debug("<Scene> Deleting GameObject {0}", game_object->get_id());
                game_object->destroy();
            }
        }
        debug::Log->debug("<Scene> Cleaning GameObject Array");
        std::erase_if(m_game_object_array,
            [](const std::unique_ptr<script::GameObject>& ptr) { return (!ptr->is_permanent()); });
        // Required for the next does_game_object_exists
        this->_rebuild_ids();
        debug::Log->debug("<Scene> Cleaning Sprite Array");
        std::erase_if(m_sprite_array, [this](const std::unique_ptr<graphics::Sprite>& ptr) {
            if (!ptr->get_parent_id().empty()
                && this->does_game_object_exists(ptr->get_parent_id()))
                return false;
            return true;
        });
        debug::Log->debug("<Scene> Cleaning Collider Array");
        std::erase_if(
            m_collider_array, [this](const std::unique_ptr<collision::ColliderComponent>& ptr) {
                for (const auto& game_object : m_game_object_array)
                {
                    if (game_object->is_parent_of_component(ptr->get_unique_id()))
                    {
                        return false;
                    }
                        ;
                }
                return true;
            });
        debug::Log->debug("<Scene> Clearing MapScript Array");
        m_script_array.clear();
        debug::Log->debug("<Scene> Scene Cleared !");
        this->_rebuild_ids();
        if (m_tiles)
            m_tiles->clear();
    }

    vili::node Scene::schema() const
    {
        return vili::object {};
    }

    vili::node Scene::dump() const
    {
        vili::node result = vili::object {};

        // Meta
        result["Meta"] = vili::object { { "name", m_level_name } };

        // View
        result["View"] = vili::object {};
        result["View"]["size"] = m_camera.get_size().y / 2;
        result["View"]["position"] = vili::object { { "x", m_camera_initial_position.x },
            { "y", m_camera_initial_position.y },
            { "unit", transform::UnitsMeta::to_string(m_camera_initial_position.unit) } };
        result["View"]["referential"] = m_camera_initial_referential.to_string();

        // Sprites
        if (!m_sprite_array.empty())
            result["Sprites"] = vili::object {};
        for (auto& sprite : m_sprite_array)
        {
            if (sprite->get_parent_id().empty())
            {
                result["Sprites"][sprite->get_id()] = sprite->dump();
            }
        }

        // Collisions
        if (!m_collider_array.empty())
            result["Collisions"] = vili::object {};
        for (auto& collider : m_collider_array)
        {
            if (true) // TODO: fix this
            {
                result["Collisions"][collider->get_id()] = collider->dump();
            }
        }

        // GameObjects
        if (!m_game_object_array.empty())
            result["GameObjects"] = vili::object {};
        for (auto& game_object : m_game_object_array)
        {
            result["GameObjects"][game_object->get_id()] = game_object->dump();
        }

        // Scripts
        if (!m_script_array.empty())
        {
            result["Script"] = vili::object {};
            if (m_script_array.size() == 1)
            {
                result.at("Script")["source"] = m_script_array[0];
            }
            else
            {
                result.at("Script")["sources"]
                    = vili::array(m_script_array.begin(), m_script_array.end());
            }
        }
        return result;
    }

    void Scene::load(const vili::node& data)
    {
        if (data.contains("Meta"))
        {
            const vili::node& meta = data.at("Meta");
            m_level_name = meta.at("name");
            if (meta.contains("background"))
            {
                m_background.from_string(meta.at("background").as<vili::string>());
            }
        }
        else
            throw exceptions::MissingSceneFileBlock(m_level_file_name, "Meta", EXC_INFO);

        if (data.contains("View"))
        {
            const vili::node& view = data.at("View");
            m_camera.set_size(view.at("size"));
            double x = 0.f;
            double y = 0.f;
            transform::Units unit = transform::Units::SceneUnits;
            if (view.contains("position"))
            {
                const vili::node& position = view.at("position");
                if (position.contains("x"))
                {
                    x = position["x"];
                }
                if (position.contains("y"))
                {
                    y = position["y"];
                }
                if (position.contains("unit"))
                {
                    unit = transform::UnitsMeta::from_string(position.at("unit"));
                }
            }
            m_camera_initial_position = transform::UnitVector(x, y, unit);
            m_camera_initial_referential = transform::Referential::TopLeft;
            if (view.contains("referential"))
            {
                m_camera_initial_referential
                    = transform::Referential::from_string(view.at("referential"));
            }
            debug::Log->debug("<Scene> Set Camera Position at : {0}, {1} using "
                              "Referential {2}",
                m_camera_initial_position.x, m_camera_initial_position.y,
                m_camera_initial_referential.to_string());
            m_camera.set_position(m_camera_initial_position, m_camera_initial_referential);
        }
        else
            throw exceptions::MissingSceneFileBlock(m_level_file_name, "View", EXC_INFO);

        if (data.contains("Sprites"))
        {
            const vili::node& sprites = data.at("Sprites");
            m_sprite_array.reserve(sprites.size());
            m_sprite_ids.reserve(sprites.size());
            for (auto [sprite_id, sprite] : data.at("Sprites").items())
            {
                this->create_sprite(sprite_id).load(sprite);
            }
        }

        if (data.contains("Collisions"))
        {
            const vili::node& collisions = data.at("Collisions");
            m_collider_array.reserve(collisions.size());
            m_collider_ids.reserve(collisions.size());
            for (auto [collision_id, collision] : data.at("Collisions").items())
            {
                this->create_collider(collision_id).load(collision);
            }
        }

        if (data.contains("Tiles"))
        {
            m_tiles = std::make_unique<tiles::TileScene>(*this);
            m_tiles->load(data.at("Tiles"));
        }

        if (data.contains("GameObjects"))
        {
            const vili::node& game_objects = data.at("GameObjects");
            m_game_object_array.reserve(game_objects.size());
            m_game_object_ids.reserve(game_objects.size());
            for (auto [game_object_id, game_object] : game_objects.items())
            {
                if (!this->does_game_object_exists(game_object_id))
                {
                    const std::string game_object_type = game_object.at("type");
                    script::GameObject& new_object
                        = this->create_game_object(game_object_type, game_object_id);
                    if (game_object.contains("Requires") && new_object.does_have_script_engine())
                    {
                        const vili::node& object_requirements = game_object.at("Requires");
                        new_object.init_from_vili(object_requirements);
                    }
                    else
                    {
                        new_object.initialize();
                    }
                }
                else if (!this->get_game_object(game_object_id).is_permanent())
                {
                    throw exceptions::GameObjectAlreadyExists(m_level_file_name,
                        this->get_game_object(game_object_id).get_type(), game_object_id, EXC_INFO);
                }
            }
        }

        if (data.contains("Script"))
        {
            const vili::node& script = data.at("Script");
            if (script.contains("source"))
            {
                std::string source = system::Path(script.at("source")).find();
                const sol::protected_function_result result
                    = m_lua.safe_script_file(source, &sol::script_pass_on_error);
                // TODO: wrap into helper
                if (!result.valid())
                {
                    const auto err_obj = result.get<sol::error>();
                    const std::string err_msg = err_obj.what();
                    throw exceptions::SceneScriptLoadingError(m_level_file_name, source,
                        utils::string::replace(err_msg, "\n", "\n        "), EXC_INFO);
                }
                m_script_array.push_back(script.at("source"));
            }
            else if (script.contains("sources"))
            {
                for (const vili::node& script_name : script.at("sources"))
                {
                    m_lua.safe_script_file(system::Path(script_name).find());
                    m_script_array.push_back(script_name);
                }
            }
        }

        this->reorganize_layers();

        e_scene->trigger(events::Scene::Loaded { m_level_file_name });
    }

    void Scene::set_future_load(const vili::node& data)
    {
        m_deferred_scene_load_node = data;
    }

    void Scene::update()
    {
        if (!m_deferred_scene_load.empty())
        {
            const sol::protected_function on_load_callback = std::move(m_on_load_callback);
            const std::string future_load_buffer = std::move(m_deferred_scene_load);
            const std::string current_scene = m_level_file_name;
            this->load_from_file(future_load_buffer);
            if (on_load_callback)
            {
                const sol::protected_function_result result = on_load_callback(future_load_buffer);
                if (!result.valid())
                {
                    const auto error = result.get<sol::error>();
                    const std::string err_msg = "\n        \""
                        + utils::string::replace(error.what(), "\n", "\n        ") + "\"";
                    // TODO: Replace with nest
                    throw exceptions::SceneOnLoadCallbackError(
                        current_scene, future_load_buffer, err_msg, EXC_INFO);
                }
            }
        }
        if (m_deferred_scene_load_node)
        {
            const vili::node& scene_data = m_deferred_scene_load_node.value();
            this->clear();
            this->load(scene_data);
            m_deferred_scene_load_node.reset();
        }
        if (m_update_state)
        {
            const size_t array_size = m_game_object_array.size();
            for (size_t i = 0; i < array_size; i++)
            {
                script::GameObject& game_object = *m_game_object_array[i];
                if (!game_object.deletable)
                    game_object.update();
            }
            std::erase_if(
                m_game_object_array, [this](const std::unique_ptr<script::GameObject>& ptr) {
                    if (ptr->deletable)
                    {
                        m_game_object_ids.erase(ptr->get_id());
                        debug::Log->debug("<Scene> Removing GameObject {}", ptr->get_id());
                        if (ptr->m_sprite)
                            this->remove_sprite(ptr->get_sprite().get_id());
                        if (ptr->m_collider)
                            this->remove_collider(ptr->get_collider().get_id());
                        return true;
                    }
                    return false;
                });
            if (m_tiles)
                m_tiles->update();
        }
    }

    void Scene::draw(graphics::RenderTarget surface)
    {
        this->_reorganize_layers();
        surface.clear(m_background);
        if (m_render_options.sprites)
        {
            for (const auto& renderable : m_render_cache)
            {
                if (renderable->is_visible())
                {
                    renderable->draw(surface, m_camera);
                }
            }
        }

        // m_tiles->draw(surface, m_camera);

        if (m_render_options.collisions)
        {
            // TODO: Move out of Scene
            for (const auto& collider : m_collider_array)
            {
                debug::render::draw_collider(
                    surface, *collider, debug::render::ColliderRenderOptions {});
            }
            /* for (const auto& collider : m_collider_array)
            {
                debug::render::draw_polygon(
                    surface, *collider->get_inner_collider(), true, true, false, false, m_camera.get_position());
            }*/
        }

        if (m_render_options.scene_nodes)
        {
            for (const auto& game_object : m_game_object_array)
            {
                sf::CircleShape scene_node_shape;
                SceneNode& scene_node = game_object->get_scene_node();
                const transform::UnitVector scene_node_position
                    = scene_node.get_position().to<transform::Units::ViewPixels>();
                scene_node_shape.setPosition(scene_node_position.x - 3, scene_node_position.y - 3);
                if (scene_node.is_selected())
                    scene_node_shape.setFillColor(sf::Color::Green);
                else
                    scene_node_shape.setFillColor(sf::Color::Red);
                scene_node_shape.setOutlineColor(sf::Color::Black);
                scene_node_shape.setOutlineThickness(2);
                scene_node_shape.setRadius(6);
                surface.draw(scene_node_shape);
            }
        }
    }

    std::string Scene::get_level_name() const
    {
        return m_level_name;
    }

    void Scene::set_level_name(const std::string& new_name)
    {
        m_level_name = new_name;
    }

    std::vector<collision::ColliderComponent*> Scene::get_all_colliders() const
    {
        std::vector<collision::ColliderComponent*> all_colliders;
        for (const auto& collider : m_collider_array)
            all_colliders.push_back(collider.get());
        return all_colliders;
    }

    Camera& Scene::get_camera()
    {
        return m_camera;
    }

    void Scene::set_update_state(bool state)
    {
        m_update_state = state;
        for (const auto& game_object : m_game_object_array)
        {
            game_object->set_state(state);
        }
    }

    script::GameObject& Scene::get_game_object(const std::string& id) const
    {
        for (auto& game_object : m_game_object_array)
        {
            if (game_object->get_id() == id && !game_object->deletable)
                return *game_object;
        }
        std::vector<std::string> object_ids;
        object_ids.reserve(m_game_object_array.size());
        for (const auto& object : m_game_object_array)
        {
            object_ids.push_back(object->get_id());
        }
        throw exceptions::UnknownGameObject(m_level_file_name, id, object_ids, EXC_INFO);
    }

    bool Scene::does_game_object_exists(const std::string& id) const
    {
        return m_game_object_ids.contains(id);
    }

    void Scene::remove_game_object(const std::string& id)
    {
        std::erase_if(m_game_object_array, [&id](const std::unique_ptr<script::GameObject>& ptr) {
            return (ptr->get_id() == id);
        });
        m_game_object_ids.erase(id);
    }

    std::vector<script::GameObject*> Scene::get_all_game_objects(
        const std::string& object_type) const
    {
        std::vector<script::GameObject*> return_vec;
        for (auto& game_object : m_game_object_array)
        {
            if (!game_object->deletable
                && (object_type.empty() || object_type == game_object->get_type()))
                return_vec.push_back(game_object.get());
        }
        return return_vec;
    }

    script::GameObject& Scene::create_game_object(
        const std::string& object_type, const std::string& id)
    {
        std::string use_id = id;
        if (use_id.empty())
        {
            while (use_id.empty() || this->does_game_object_exists(use_id))
            {
                use_id = object_type + "_"
                    + utils::string::get_random_key(
                        utils::string::Alphabet + utils::string::Numbers, 8);
            }
        }
        else if (this->does_game_object_exists(use_id))
        {
            throw exceptions::GameObjectAlreadyExists(
                m_level_file_name, this->get_game_object(use_id).get_type(), use_id, EXC_INFO);
        }

        std::unique_ptr<script::GameObject> new_game_object
            = std::make_unique<script::GameObject>(m_lua, object_type, use_id);
        vili::node game_object_data
            = script::GameObjectDatabase::get_definition_for_game_object(object_type);
        new_game_object->load_game_object(*this, game_object_data, m_resources);

        if (new_game_object->does_have_sprite())
        {
            new_game_object->get_sprite().set_parent_id(use_id);
        }

        if (new_game_object->does_have_collider())
        {
            // new_game_object->get_collider().set_parent_id(use_id);
        }

        m_game_object_array.push_back(move(new_game_object));
        m_game_object_ids.insert(use_id);

        return *m_game_object_array.back();
    }

    std::size_t Scene::get_game_object_amount() const
    {
        return m_game_object_array.size();
    }

    void Scene::reorganize_layers()
    {
        m_sort_renderables = true;
    }

    std::size_t Scene::get_sprite_amount() const
    {
        return m_sprite_array.size();
    }

    std::vector<graphics::Sprite*> Scene::get_all_sprites() const
    {
        std::vector<graphics::Sprite*> all_sprites;
        all_sprites.reserve(m_sprite_array.size());
        for (auto& sprite : m_sprite_array)
            all_sprites.push_back(sprite.get());
        return all_sprites;
    }

    std::vector<graphics::Sprite*> Scene::get_sprites_by_layer(const int layer) const
    {
        std::vector<graphics::Sprite*> return_layer;

        for (const auto& sprite : m_sprite_array)
        {
            if (sprite->get_layer() == layer)
                return_layer.push_back(sprite.get());
        }

        return return_layer;
    }

    graphics::Sprite* Scene::get_sprite_by_position(
        const transform::UnitVector& position, const int layer) const
    {
        std::vector<transform::Referential> rect_pts
            = { transform::Referential::TopLeft, transform::Referential::TopRight,
                  transform::Referential::BottomRight, transform::Referential::BottomLeft };
        const transform::UnitVector zero_offset(0, 0);

        const std::vector<graphics::Sprite*> sprites_on_layer = this->get_sprites_by_layer(layer);
        const transform::UnitVector camera
            = -(m_camera.get_position().to<transform::Units::ScenePixels>());
        for (const auto& sprite : sprites_on_layer)
        {
            if (sprite->contains(sprite->get_position_transformer()(position, camera, layer)))
            {
                return sprite;
            }
        }
        return nullptr;
    }

    graphics::Sprite& Scene::get_sprite(const std::string& id) const
    {
        for (const auto& sprite : m_sprite_array)
        {
            if (sprite->get_id() == id)
                return *sprite;
        }
        std::vector<std::string> sprites_ids;
        sprites_ids.reserve(m_sprite_array.size());
        for (const auto& sprite : m_sprite_array)
        {
            sprites_ids.push_back(sprite->get_id());
        }
        throw exceptions::UnknownSprite(m_level_file_name, id, sprites_ids, EXC_INFO);
    }

    bool Scene::does_sprite_exists(const std::string& id) const
    {
        return m_sprite_ids.contains(id);
    }

    void Scene::remove_sprite(const std::string& id)
    {
        debug::Log->debug("<Scene> Removing Sprite {0}", id);
        std::erase_if(m_sprite_array, [&id](const std::unique_ptr<graphics::Sprite>& sprite) {
            return (sprite->get_id() == id);
        });
        m_sprite_ids.erase(id);
    }

    SceneNode* Scene::get_scene_node_by_position(const transform::UnitVector& position) const
    {
        for (auto& game_object : m_game_object_array)
        {
            const transform::UnitVector scene_node_position
                = game_object->get_scene_node().get_position();
            const transform::UnitVector p_vec = position.to<transform::Units::SceneUnits>();
            const transform::UnitVector p_tolerance
                = transform::UnitVector(6, 6, transform::Units::ScenePixels)
                      .to<transform::Units::SceneUnits>();

            if (utils::math::is_between(p_vec.x, scene_node_position.x - p_tolerance.x,
                    scene_node_position.x + p_tolerance.x))
            {
                if (utils::math::is_between(p_vec.y, scene_node_position.y - p_tolerance.x,
                        scene_node_position.y + p_tolerance.y))
                    return &game_object->get_scene_node();
            }
        }
        return nullptr;
    }

    bool Scene::has_tiles() const
    {
        return static_cast<bool>(m_tiles);
    }

    const tiles::TileScene& Scene::get_tiles() const
    {
        return *m_tiles;
    }

    SceneRenderOptions Scene::get_render_options() const
    {
        return m_render_options;
    }

    void Scene::set_render_options(SceneRenderOptions options)
    {
        m_render_options = options;
    }

    component::ComponentBase* Scene::get_component(const std::string& id) const
    {
        return m_components.at(id);
    }

    collision::ColliderComponent& Scene::get_collider(const std::string& id) const
    {
        for (const auto& collider : m_collider_array)
        {
            if (id == collider->get_id())
            {
                return *collider;
            }
        }
        std::vector<std::string> colliders_ids;
        colliders_ids.reserve(m_collider_array.size());
        for (const auto& collider : m_collider_array)
        {
            colliders_ids.push_back(collider->get_id());
        }
        throw exceptions::UnknownCollider(m_level_file_name, id, colliders_ids, EXC_INFO);
    }

    bool Scene::does_collider_exists(const std::string& id) const
    {
        return m_collider_ids.contains(id);
    }

    void Scene::remove_collider(const std::string& id)
    {
        const auto collider_it = std::find_if(m_collider_array.begin(), m_collider_array.end(),
            [&id](const std::unique_ptr<collision::ColliderComponent>& collider)
            { return (collider->get_id() == id);
            });
        m_collision_space.remove_collider(collider_it->get()->get_inner_collider());
        m_collider_array.erase(collider_it);
        m_collider_ids.erase(id);
    }

    collision::CollisionSpace& Scene::get_collision_space()
    {
        return m_collision_space;
    }

    SceneNode& Scene::get_scene_root_node()
    {
        return m_scene_root;
    }

    std::string Scene::get_level_file() const
    {
        return m_level_file_name;
    }

    // Proxy functions
    sol::table scene_get_game_object_proxy(const Scene* self, const std::string& id)
    {
        return self->get_game_object(id).access();
    }

    sol::function scene_create_game_object_proxy(
        Scene* self, const std::string& object_type, const std::string& id)
    {
        return self->create_game_object(object_type, id).get_constructor();
    }

    sol::nested<std::vector<sol::table>> scene_get_all_game_objects_proxy(
        const Scene* self, const std::string& object_type)
    {
        std::vector<sol::table> game_objects;

        for (const auto& game_object : self->get_all_game_objects(object_type))
        {
            game_objects.push_back(game_object->access());
        }
        return game_objects;
    }
} // namespace obe::scene
