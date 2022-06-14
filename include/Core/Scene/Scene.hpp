#pragma once

#include <unordered_set>

#include <sol/sol.hpp>
#include <vili/node.hpp>

#include <Collision/PolygonalCollider.hpp>
#include <Engine/ResourceManager.hpp>
#include <Event/EventGroup.hpp>
#include <Event/EventNamespace.hpp>
#include <Graphics/Sprite.hpp>
#include <Scene/Camera.hpp>
#include <Scene/SceneNode.hpp>
#include <Script/GameObject.hpp>
#include <Tiles/Scene.hpp>

namespace obe
{
    namespace system
    {
        class Window;
    }
}

namespace obe::events::scene
{
    struct Loaded
    {
        static constexpr std::string_view id = "Loaded";
        std::string filename;
    };
}

namespace obe::scene
{
    using OnSceneLoadCallback = sol::protected_function;

    struct SceneRenderOptions
    {
        bool sprites = true;
        bool collisions = false;
        bool scene_nodes = false;
    };

    /**
     * \brief The Scene class is a container of all the game elements
     */
    class Scene : public Types::Serializable, public engine::ResourceManagedObject
    {
    private:
        std::string m_level_name;
        std::string m_base_folder;
        std::string m_deferred_scene_load;
        Camera m_camera;
        transform::UnitVector m_camera_initial_position;
        transform::Referential m_camera_initial_referential;
        bool m_update_state = true;

        std::vector<std::unique_ptr<graphics::Sprite>> m_sprite_array;
        std::unordered_set<std::string> m_sprite_ids;

        std::vector<std::unique_ptr<collision::PolygonalCollider>> m_collider_array;
        std::unordered_set<std::string> m_collider_ids;

        std::vector<std::unique_ptr<script::GameObject>> m_game_object_array;
        std::unordered_set<std::string> m_game_object_ids;

        std::vector<std::string> m_script_array;
        std::unique_ptr<tiles::TileScene> m_tiles;

        SceneNode m_scene_root;

        std::string m_level_file_name;
        SceneRenderOptions m_render_options;
        OnSceneLoadCallback m_on_load_callback;
        event::EventGroupPtr e_scene;
        sol::state_view m_lua;

        std::unordered_map<std::string, Component::ComponentBase*> m_components;

        bool m_sort_renderables = true;
        std::vector<graphics::Renderable*> m_render_cache;
        void _reorganize_layers();
        void _rebuild_ids();

    public:
        /**
         * \brief Creates a new Scene
         */
        Scene(event::EventNamespace& events, sol::state_view lua);
        /**
         * \nobind
         * \brief Loads the Scene from a .map.vili file
         * \param path Path to the Scene file
         */
        void load_from_file(const std::string& path);
        /**
         * \rename{load_from_file}
         * \brief Same that load_from_file excepts the map will load at the next
         *        update
         * \param path Path to the Scene file
         */
        void set_future_load_from_file(const std::string& path);
        /**
         * \rename{load_from_file}
         * \brief Same that load_from_file excepts the map will load at the next
         * update
         * \param path Path to the Scene file
         * \param callback Lua Function called when new map has
         *        been loaded
         */
        void set_future_load_from_file(
            const std::string& path, const OnSceneLoadCallback& callback);
        /**
         * \brief Removes all elements in the Scene
         */
        void clear();

        [[nodiscard]] vili::node schema() const override;
        /**
         * \brief Dumps all elements of the Scene in a vili tree
         * \return vili::node containing the Scene details
         */
        [[nodiscard]] vili::node dump() const override;
        void load(const vili::node& data) override;
        /**
         * \brief Updates all elements in the Scene
         */
        void update();
        /**
         * \brief Draws all elements of the Scene on the screen
         */
        void draw(graphics::RenderTarget surface);
        /**
         * \brief Get the name of the level
         * \return A std::string containing the name of the level
         */
        [[nodiscard]] std::string get_level_name() const;
        /**
         * \brief Sets the name of the level
         * \param new_name A std::string containing the new name of the level
         */
        void set_level_name(const std::string& new_name);
        /**
         * \brief Enables or disables the Scene update
         * \param state true if the Scene should update, false otherwise
         */
        void set_update_state(bool state);

        // GameObjects
        /**
         * \brief Creates a new GameObject
         * \param object_type Type of the GameObject
         * \param id Id of the new GameObject (If empty the id will be randomly
         *        generated)
         * \return A pointer to the newly created GameObject
         */
        script::GameObject& create_game_object(
            const std::string& object_type, const std::string& id = "");
        /**
         * \brief Get how many GameObjects are present in the Scene
         * \return The amount of GameObjects in the Scene
         */
        [[nodiscard]] std::size_t get_game_object_amount() const;
        /**
         * \brief Get all the GameObjects present in the Scene
         * \return
         */
        std::vector<script::GameObject*> get_all_game_objects(
            const std::string& object_type = "") const;
        /**
         * \brief Get a GameObject by Id (Raises an exception if not found)
         * \param id Id of the GameObject to retrieve
         * \return A pointer to the GameObject
         */
        script::GameObject& get_game_object(const std::string& id) const;
        /**
         * \brief Check if a GameObject exists in the Scene
         * \param id Id of the GameObject to check the existence
         * \return true if the GameObject exists in the Scene, false otherwise
         */
        bool does_game_object_exists(const std::string& id) const;
        /**
         * \brief Removes a GameObject from the Scene
         * \param id Id of the GameObject to remove from the Scene
         */
        void remove_game_object(const std::string& id);

        // Camera
        /**
         * \brief Gets the Scene Camera
         * \return A pointer to the Scene Camera
         */
        Camera& get_camera();

        // Sprites
        /**
         * \brief Reorganize all the Sprite (by layer and sublayer)
         */
        void reorganize_layers();
        /**
         * \brief Creates a new Sprite
         * \param id Id of the new Sprite
         * \param add_to_scene_root Add the Sprite to the root Scene Node if
         *        true
         * \return A pointer to the newly created Sprite
         */
        graphics::Sprite& create_sprite(const std::string& id = "", bool add_to_scene_root = true);
        /**
         * \brief Get how many Sprites are present in the Scene
         * \return The amount of Sprites in the Scene
         */
        [[nodiscard]] std::size_t get_sprite_amount() const;
        /**
         * \brief Get all the Sprites present in the Scene
         * \return A std::vector of Sprites pointer
         */
        std::vector<graphics::Sprite*> get_all_sprites() const;
        /**
         * \brief Get all the Sprites present in the Scene in the given
         *        layer
         * \param layer Layer to get all the Sprites from \return A
         *        std::vector of Sprites pointer
         */
        std::vector<graphics::Sprite*> get_sprites_by_layer(int layer) const;
        /**
         * \brief Get the first found Sprite with the BoundingRect
         *        including the given position
         * \param position Position to check
         * \param layer Layer where to check
         * \return The pointer to a Sprite if found, nullptr otherwise
         */
        graphics::Sprite* get_sprite_by_position(
            const transform::UnitVector& position, int layer) const;
        /**
         * \brief Get a Sprite by Id (Raises an exception if not found)
         * \param id Id of the Sprite to get
         * \return A pointer to the Sprite
         */
        graphics::Sprite& get_sprite(const std::string& id) const;
        /**
         * \brief Check if a Sprite exists in the Scene
         * \param id Id of the Sprite to check the existence
         * \return true if the Sprite exists in the Scene, false otherwise
         */
        bool does_sprite_exists(const std::string& id) const;
        /**
         * \brief Removes the Sprite with the given Id
         * \param id Id of the Sprite to remove
         */
        void remove_sprite(const std::string& id);

        // Colliders
        /**
         * \brief Creates a new Collider
         * \param id Id of the new Collider
         * \param add_to_scene_root Add the Collider to the root Scene Node if true
         * \return A pointer to the newly created Collider
         */
        collision::PolygonalCollider& create_collider(
            const std::string& id = "", bool add_to_scene_root = true);
        /**
         * \brief Get how many Colliders are present in the Scene
         * \return The amount of Colliders present in the Scene
         */
        [[nodiscard]] std::size_t get_collider_amount() const;
        /**
         * \brief Get all the pointers of the Colliders in the Scene
         * \return A std::vector containing all the pointers of the Colliders
         *         present in the Scene
         */
        [[nodiscard]] std::vector<collision::PolygonalCollider*> get_all_colliders() const;
        /**
         * \brief Get the first Collider found with a point on the given
         *        position
         * \param position Position to get the Point of a Collider
         * \return A std::pair containing the pointer to the Collider with a
         *         point at the given position and the index of the point
         */
        std::pair<collision::PolygonalCollider*, int> get_collider_point_by_position(
            const transform::UnitVector& position) const;
        /**
         * \brief Get the Collider using the centroid Position
         * \param position Position to check
         * \return A Pointer to the Collider if found, nullptr otherwise
         */
        collision::PolygonalCollider* get_collider_by_centroid_position(
            const transform::UnitVector& position) const;
        /**
         * \brief Get the Collider with the given Id (Raises an exception if not
         *        found)
         * \param id Id of the Collider to retrieve
         * \return A pointer to the Collider
         */
        collision::PolygonalCollider& get_collider(const std::string& id) const;
        /**
         * \brief Check the existence of the Collider with given Id in the Scene
         * \param id Id of the Collider to check the existence
         * \return true if the Collider was found, false otherwise
         */
        bool does_collider_exists(const std::string& id) const;
        /**
         * \brief Removes the Collider with the given Id from the Scene
         * \param id Id of the Collider to remove
         */
        void remove_collider(const std::string& id);
        SceneNode& get_scene_root_node();

        // Other
        /**
         * \brief Folder where was the map loaded with load_from_file method
         * \return A std::string containing the folder where was loaded the map
         *         file
         */
        [[nodiscard]] std::string get_filesystem_path() const;
        /**
         * \brief Reloads the Scene from the level file
         */
        void reload();
        /**
         * \brief Reloads the Scene from the level file
         * \param callback Lua Function called when the map has been reloaded
         */
        void reload(const OnSceneLoadCallback& callback);
        /**
         * \brief Name of the last loaded map file with load_from_file method
         * \return A std::string containing the name of the last loaded map file
         *         with load_from_file method
         */
        [[nodiscard]] std::string get_level_file() const;
        [[nodiscard]] SceneNode* get_scene_node_by_position(
            const transform::UnitVector& position) const;
        bool has_tiles() const;
        const tiles::TileScene& get_tiles() const;
        SceneRenderOptions get_render_options() const;
        void set_render_options(SceneRenderOptions options);

        // Components
        Component::ComponentBase* get_component(const std::string& id) const;
    };

    /**
     * \proxy{obe::scene::scene::get_game_object}
     */
    sol::table scene_get_game_object_proxy(const Scene* self, const std::string& id);
    /**
     * \proxy{obe::scene::scene::create_game_object}
     */
    sol::function scene_create_game_object_proxy(
        Scene* self, const std::string& object_type, const std::string& id = "");
    /**
    * \proxy{obe::scene::scene::get_all_game_objects}
    */
    sol::nested<std::vector<sol::table>> scene_get_all_game_objects_proxy(
        const Scene* self, const std::string& object_type = "");
} // namespace obe::scene
