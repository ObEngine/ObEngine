#pragma once

#include <Collision/PolygonalCollider.hpp>
#include <Graphics/Sprite.hpp>
#include <Scene/Camera.hpp>
#include <Scene/SceneNode.hpp>
#include <Script/GameObject.hpp>

#include <sol/sol.hpp>

#include <vili/node.hpp>

namespace obe
{
    namespace System
    {
        class Window;
    }
}

namespace obe::Scene
{
    using OnSceneLoadCallback = sol::protected_function;

    /**
     * \brief The Scene class is a container of all the game elements
     */
    class Scene : public Types::Serializable
    {
    private:
        std::string m_levelName;
        std::string m_baseFolder;
        std::string m_futureLoad;
        Camera m_camera;
        Transform::UnitVector m_cameraInitialPosition;
        Transform::Referential m_cameraInitialReferential;
        bool m_updateState = true;

        Engine::ResourceManager* m_resources = nullptr;
        std::vector<std::unique_ptr<Graphics::Sprite>> m_spriteArray;
        std::vector<std::unique_ptr<Collision::PolygonalCollider>> m_colliderArray;
        std::vector<std::unique_ptr<Script::GameObject>> m_gameObjectArray;
        std::vector<std::string> m_scriptArray;
        SceneNode m_sceneRoot;

        std::string m_levelFileName;
        std::map<std::string, bool> m_showElements;
        OnSceneLoadCallback m_onLoadCallback;
        Triggers::TriggerManager& m_triggers;
        Triggers::TriggerGroupPtr t_scene;
        sol::state_view m_lua;

    public:
        /**
         * \brief Creates a new Scene
         */
        Scene(Triggers::TriggerManager& triggers, sol::state_view lua);

        void attachResourceManager(Engine::ResourceManager& resources);
        /**
         * \nobind
         * \brief Loads the Scene from a .map.vili file
         * \param path Path to the Scene file
         */
        void loadFromFile(const std::string& path);
        /**
         * \bind{loadFromFile}
         * \brief Same that loadFromFile excepts the map will load at the next
         *        update
         * \param path Path to the Scene file
         */
        void setFutureLoadFromFile(const std::string& path);
        /**
         * \brief Same that loadFromFile excepts the map will load at the next
         * update
         * \param path Path to the Scene file
         * \param callback Lua Function called when new map has
         *        been loaded
         */
        void setFutureLoadFromFile(
            const std::string& path, const OnSceneLoadCallback& callback);
        /**
         * \brief Removes all elements in the Scene
         */
        void clear();
        /**
         * \brief Dumps all elements of the Scene in a vili tree
         * \return
         */
        [[nodiscard]] vili::node dump() const override;
        void load(vili::node& data) override;
        /**
         * \brief Updates all elements in the Scene
         */
        void update();
        /**
         * \brief Draws all elements of the Scene on the screen
         */
        void draw(Graphics::RenderTarget surface);
        /**
         * \brief Get the name of the level
         * \return A std::string containing the name of the level
         */
        [[nodiscard]] std::string getLevelName() const;
        /**
         * \brief Sets the name of the level
         * \param newName A std::string containing the new name of the level
         */
        void setLevelName(const std::string& newName);
        /**
         * \brief Enables or disables the Scene update
         * \param state true if the Scene should update, false otherwise
         */
        void setUpdateState(bool state);

        // GameObjects
        /**
         * \brief Creates a new GameObject
         * \param obj Type of the GameObject
         * \param id Id of the new GameObject (If empty the id will be randomly
         *        generated)
         * \return A pointer to the newly created GameObject
         */
        Script::GameObject& createGameObject(
            const std::string& obj, const std::string& id = "");
        /**
         * \brief Get how many GameObjects are present in the Scene
         * \return The amount of GameObjects in the Scene
         */
        [[nodiscard]] std::size_t getGameObjectAmount() const;
        /**
         * \brief Get all the GameObjects present in the Scene
         * \return
         */
        std::vector<Script::GameObject*> getAllGameObjects(
            const std::string& objectType = "");
        /**
         * \brief Get a GameObject by Id (Raises an exception if not found)
         * \param id Id of the GameObject to retrieve
         * \return A pointer to the GameObject
         */
        Script::GameObject& getGameObject(const std::string& id);
        /**
         * \brief Check if a GameObject exists in the Scene
         * \param id Id of the GameObject to check the existence
         * \return true if the GameObject exists in the Scene, false otherwise
         */
        bool doesGameObjectExists(const std::string& id);
        /**
         * \brief Removes a GameObject from the Scene
         * \param id Id of the GameObject to remove from the Scene
         */
        void removeGameObject(const std::string& id);

        // Camera
        /**
         * \brief Gets the Scene Camera
         * \return A pointer to the Scene Camera
         */
        Camera& getCamera();

        // Sprites
        /**
         * \brief Reorganize all the Sprite (by Layer and z-depth)
         */
        void reorganizeLayers();
        /**
         * \brief Creates a new Sprite
         * \param id Id of the new Sprite
         * \param addToSceneRoot Add the Sprite to the root Scene Node if
         *        true
         * \return A pointer to the newly created Sprite
         */
        Graphics::Sprite& createSprite(
            const std::string& id = "", bool addToSceneRoot = true);
        /**
         * \brief Get how many Sprites are present in the Scene
         * \return The amount of Sprites in the Scene
         */
        [[nodiscard]] std::size_t getSpriteAmount() const;
        /**
         * \brief Get all the Sprites present in the Scene
         * \return A std::vector of Sprites pointer
         */
        std::vector<Graphics::Sprite*> getAllSprites();
        /**
         * \brief Get all the Sprites present in the Scene in the given
         *        layer
         * \param layer Layer to get all the Sprites from \return A
         *        std::vector of Sprites pointer
         */
        std::vector<Graphics::Sprite*> getSpritesByLayer(int layer);
        /**
         * \brief Get the first found Sprite with the BoundingRect
         *        including the given position
         * \param position Position to check
         * \param layer Layer where to check
         * \return The pointer to a Sprite if found, nullptr otherwise
         */
        Graphics::Sprite* getSpriteByPosition(
            const Transform::UnitVector& position, int layer);
        /**
         * \brief Get a Sprite by Id (Raises an exception if not found)
         * \param id Id of the Sprite to get
         * \return A pointer to the Sprite
         */
        Graphics::Sprite& getSprite(const std::string& id);
        /**
         * \brief Check if a Sprite exists in the Scene
         * \param id Id of the Sprite to check the existence
         * \return true if the Sprite exists in the Scene, false otherwise
         */
        bool doesSpriteExists(const std::string& id);
        /**
         * \brief Removes the Sprite with the given Id
         * \param id Id of the Sprite to remove
         */
        void removeSprite(const std::string& id);

        // Colliders
        /**
         * \brief Creates a new Collider
         * \param id Id of the new Collider
         * \param addToSceneRoot Add the Collider to the root Scene Node if true
         * \return A pointer to the newly created Collider
         */
        Collision::PolygonalCollider& createCollider(
            const std::string& id = "", bool addToSceneRoot = true);
        /**
         * \brief Get how many Colliders are present in the Scene
         * \return The amount of Colliders present in the Scene
         */
        [[nodiscard]] std::size_t getColliderAmount() const;
        /**
         * \brief Get all the pointers of the Colliders in the Scene
         * \return A std::vector containing all the pointers of the Colliders
         *         present in the Scene
         */
        [[nodiscard]] std::vector<Collision::PolygonalCollider*> getAllColliders() const;
        /**
         * \brief Get the first Collider found with a point on the given
         *        position
         * \param position Position to get the Point of a Collider
         * \return A std::pair containing the pointer to the Collider with a
         *         point at the given position and the index of the point
         */
        std::pair<Collision::PolygonalCollider*, int> getColliderPointByPosition(
            const Transform::UnitVector& position);
        /**
         * \brief Get the Collider using the centroid Position
         * \param position Position to check
         * \return A Pointer to the Collider if found, nullptr otherwise
         */
        Collision::PolygonalCollider* getColliderByCentroidPosition(
            const Transform::UnitVector& position);
        /**
         * \brief Get the Collider with the given Id (Raises an exception if not
         *        found)
         * \param id Id of the Collider to retrieve
         * \return A pointer to the Collider
         */
        Collision::PolygonalCollider& getCollider(const std::string& id);
        /**
         * \brief Check the existence of the Collider with given Id in the Scene
         * \param id Id of the Collider to check the existence
         * \return true if the Collider was found, false otherwise
         */
        bool doesColliderExists(const std::string& id);
        /**
         * \brief Removes the Collider with the given Id from the Scene
         * \param id Id of the Collider to remove
         */
        void removeCollider(const std::string& id);
        SceneNode& getSceneRootNode();

        // Other
        /**
         * \brief Folder where was the map loaded with loadFromFile method
         * \return A std::string containing the folder where was loaded the map
         *         file
         */
        [[nodiscard]] std::string getFilePath() const;
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
         * \brief Name of the last loaded map file with loadFromFile method
         * \return A std::string containing the name of the last loaded map file
         *         with loadFromFile method
         */
        [[nodiscard]] std::string getLevelFile() const;
        void enableShowSceneNodes(bool showNodes);
        [[nodiscard]] SceneNode* getSceneNodeByPosition(
            const Transform::UnitVector& position) const;
    };

    /**
     * \proxy{obe::Scene::Scene::getGameObject}
     */
    sol::table sceneGetGameObjectProxy(Scene* self, const std::string& id);
    /**
     * \proxy{obe::Scene::Scene::createGameObject}
     */
    sol::function sceneCreateGameObjectProxy(
        Scene* self, const std::string& obj, const std::string& id = "");
} // namespace obe::Scene