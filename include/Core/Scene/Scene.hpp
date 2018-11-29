#pragma once

#include <Collision/PolygonalCollider.hpp>
#include <Graphics/LevelSprite.hpp>
#include <Scene/Camera.hpp>
#include <Scene/SceneNode.hpp>
#include <Script/GameObject.hpp>
#include <Scene/SceneNode.hpp>
#include <Types/Registrable.hpp>

namespace obe::Scene
{
    /**
    * \brief The Scene class is a container of all the game elements
    * @Bind
    */
    class Scene : public Types::Registrable<Scene>
    {
    private:
        std::string m_levelName = "";
        std::string m_baseFolder = "";
        std::string m_futureLoad = "";
        Camera m_camera;
        Transform::UnitVector m_cameraInitialPosition;
        Transform::Referential m_cameraInitialReferential;
        bool m_updateState = true;

        std::vector<std::unique_ptr<Graphics::LevelSprite>> m_spriteArray;
        std::vector<std::unique_ptr<Collision::PolygonalCollider>> m_colliderArray;
        std::vector<std::unique_ptr<Script::GameObject>> m_gameObjectArray;
        std::vector<std::string> m_scriptArray;
        SceneNode m_sceneRoot;

        vili::ViliParser m_levelFile;
        std::string m_levelFileName;
        std::map<std::string, bool> m_showCollisionModes;
        kaguya::LuaFunction m_onLoadCallback;
        Triggers::TriggerGroupPtr m_sceneTriggers;
    public:
        /**
        * \brief Creates a new Scene
        */
        Scene();
        /**
        * \brief Default destructor of Scene (Removes Map Namespace in TriggerDatabase)
        */
        ~Scene();

        /**
        * \brief Loads the Scene from a .map.vili file
        * \param filename Name of the file located in Data/Maps (using System::Loaders)
        */
        void loadFromFile(const std::string& filename);
        /**
        * \brief Same that loadFromFile excepts the map will load at the next update
        * \param filename Name of the file located in Data/Maps (using System::Loaders)
        */
        void setFutureLoadFromFile(const std::string& filename);
        /**
        * \brief Same that loadFromFile excepts the map will load at the next update
        * \param filename Name of the file located in Data/Maps (using System::Loaders)
        * \param callback Lua Function called when new map has been loaded
        */
        void setFutureLoadFromFile(const std::string& filename, kaguya::LuaFunction callback);
        /**
        * \brief Removes all elements in the Scene
        */
        void clear();
        /**
        * \brief Dumps all elements of the Scene in a vili tree
        * \return 
        */
        vili::ViliParser* dump(bool saveCameraPosition);
        /**
        * \brief Updates all elements in the Scene
        */
        void update();
        /**
        * \brief Draws all elements of the Scene on the screen
        */
        void draw();
        /**
        * \brief Get the name of the level
        * \return A std::string containing the name of the level
        */
        std::string getLevelName() const;
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

        //GameObjects
        /**
        * \brief Creates a new GameObject
        * \param obj Type of the GameObject
        * \param id Id of the new GameObject (If empty the id will be randomly generated)
        * \return A pointer to the newly created GameObject
        */
        Script::GameObject* createGameObject(const std::string& obj, const std::string& id = "");
        /**
        * \brief Get how many GameObjects are present in the Scene
        * \return An unsigned int containing how many GameObjects are present in the Scene
        */
        unsigned int getGameObjectAmount() const;
        /**
        * \brief Get all the GameObjects present in the Scene
        * \return 
        */
        std::vector<Script::GameObject*> getAllGameObjects();
        /**
        * \brief Get a GameObject by Id (Raises an exception if not found)
        * \param id Id of the GameObject to retrieve
        * \return A pointer to the GameObject
        */
        Script::GameObject* getGameObject(const std::string& id);
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

        //Camera
        /**
        * \brief Gets the Scene Camera
        * \return A pointer to the Scene Camera
        */
        Camera* getCamera();

        //LevelSprites
        /**
        * \brief Reorganize all the LevelSprite (by Layer and z-depth)
        */
        void reorganizeLayers();
        /**
        * \brief Creates a new LevelSprite
        * \param id Id of the new LevelSprite
        * \param addToSceneRoot Add the LevelSprite to the root Scene Node if true
        * \return A pointer to the newly created LevelSprite
        */
        Graphics::LevelSprite* createLevelSprite(const std::string& id = "", bool addToSceneRoot = true);
        /**
        * \brief Get how many LevelSprites are present in the Scene
        * \return An unsigned int containing how many LevelSprites are present in the Scene
        */
        unsigned int getLevelSpriteAmount() const;
        /**
        * \brief Get all the LevelSprites present in the Scene
        * \return A std::vector of LevelSprites pointer
        */
        std::vector<Graphics::LevelSprite*> getAllLevelSprites();
        /**
        * \brief Get all the LevelSprites present in the Scene in the given layer
        * \param layer Layer to get all the LevelSprites from
        * \return A std::vector of LevelSprites pointer
        */
        std::vector<Graphics::LevelSprite*> getLevelSpritesByLayer(int layer);
        /**
        * \brief Get the first found LevelSprite with the BoundingRect including the given position
        * \param position Position to check
        * \param camera Camera position
        * \param layer Layer where to check
        * \return The pointer to a LevelSprite if found, nullptr otherwise
        */
        Graphics::LevelSprite* getLevelSpriteByPosition(const Transform::UnitVector& position, const Transform::UnitVector& camera, int layer);
        /**
        * \brief Get a LevelSprite by Id (Raises an exception if not found)
        * \param id Id of the LevelSprite to get
        * \return A pointer to the LevelSprite
        */
        Graphics::LevelSprite* getLevelSprite(const std::string& id);
        /**
        * \brief Check if a LevelSprite exists in the Scene
        * \param id Id of the LevelSprite to check the existence
        * \return true if the LevelSprite exists in the Scene, false otherwise
        */
        bool doesLevelSpriteExists(const std::string& id);
        /**
        * \brief Removes the LevelSprite with the given Id
        * \param id Id of the LevelSprite to remove
        */
        void removeLevelSprite(const std::string& id);

        //Colliders
        /**
        * \brief Creates a new Collider
        * \param id Id of the new Collider
        * \param addToSceneRoot Add the Collider to the root Scene Node if true
        * \return A pointer to the newly created Collider
        */
        Collision::PolygonalCollider* createCollider(const std::string& id = "", bool addToSceneRoot = true);
        /**
        * \brief Get how many Colliders are present in the Scene
        * \return The amount of Colliders present in the Scene
        */
        unsigned int getColliderAmount() const;
        /**
        * \brief Get all the pointers of the Colliders in the Scene
        * \return A std::vector containing all the pointers of the Colliders present in the Scene
        */
        std::vector<Collision::PolygonalCollider*> getAllColliders() const;
        /**
        * \brief Get the first Collider found with a point on the given position
        * \param position Position to get the Point of a Collider 
        * \return A std::pair containing the pointer to the Collider with a point at the given position and the index of the point
        */
        std::pair<Collision::PolygonalCollider*, int> getColliderPointByPosition(const Transform::UnitVector& position);
        /**
        * \brief Get the Collider using the centroid Position
        * \param position Position to check
        * \return A Pointer to the Collider if found, nullptr otherwise
        */
        Collision::PolygonalCollider* getColliderByCentroidPosition(const Transform::UnitVector& position);
        /**
        * \brief Get the Collider with the given Id (Raises an exception if not found)
        * \param id Id of the Collider to retrieve
        * \return A pointer to the Collider
        */
        Collision::PolygonalCollider* getCollider(const std::string& id);
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

        //Other
        /**
        * \brief Folder where was the map loaded with loadFromFile method
        * \return A std::string containing the folder where was loaded the map file
        */
        std::string getBaseFolder() const;
        /**
        * \brief Reloads the Scene from the level file
        */
        void reload();
        /**
        * \brief Reloads the Scene from the level file
        * \param callback Lua Function called when the map has been reloaded
        */
        void reload(kaguya::LuaFunction callback);
        /**
        * \brief Name of the last loaded map file with loadFromFile method
        * \return A std::string containing the name of the last loaded map file with loadFromFile method
        */
        std::string getLevelFile() const;
        /**
        * \brief Draws some elements of the Colliders
        * \param drawLines Draw the lines of the Colliders
        * \param drawPoints Draw the points of the Colliders
        * \param drawMasterPoint Draw the Centroid of the Colliders
        * \param drawSkel Draw the Skeleton of the Colliders
        */
        void enableShowCollision(bool drawLines = false, bool drawPoints = false, bool drawMasterPoint = false, bool drawSkel = false);
    };
}