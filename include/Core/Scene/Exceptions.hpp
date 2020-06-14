#pragma once

#include <Exception.hpp>

namespace obe::Scene::Exceptions
{
    class ChildNotInSceneNode : public Exception
    {
    public:
        ChildNotInSceneNode(void* sceneNode, void* child, DebugInfo info)
            : Exception("ChildNotInSceneNode", info)
        {
            this->error("Impossible to remove Movable {} from SceneNode {} as it is not "
                        "one of its children",
                fmt::ptr(sceneNode), fmt::ptr(child));
        }
    };

    class MissingSceneFileBlock : public Exception
    {
    public:
        MissingSceneFileBlock(
            std::string_view sceneFile, std::string_view blockName, DebugInfo info)
            : Exception("MissingSceneFileBlock", info)
        {
            this->error("Scene from file '{}' does not have any required <{}> block",
                sceneFile, blockName);
            this->hint("Add a '{}' block to the Scene file", blockName);
        }
    };

    class UnknownGameObject : public Exception
    {
    public:
        UnknownGameObject(std::string_view sceneFile, std::string_view objectId,
            const std::vector<std::string>& allObjectIds, DebugInfo info)
            : Exception("UnknownGameObject", info)
        {
            this->error("GameObject with id '{}' does not exists inside Scene '{}'",
                objectId, sceneFile);
            std::vector<std::string> suggestions
                = Utils::String::sortByDistance(objectId.data(), allObjectIds, 5);
            std::transform(suggestions.begin(), suggestions.end(), suggestions.begin(),
                Utils::String::quote);
            this->hint("Try one of the GameObjects with id ({}...)",
                fmt::join(suggestions, ", "));
        }
    };

    class GameObjectAlreadyExists : public Exception
    {
    public:
        GameObjectAlreadyExists(std::string_view sceneFile, std::string_view objectType,
            std::string_view objectId, DebugInfo info)
            : Exception("GameObjectAlreadyExists", info)
        {
            this->error(
                "Scene '{}' already contains a GameObject of type '{}' with id '{}'",
                sceneFile, objectType, objectId);
            this->hint("Try choosing a different id to avoid name conflict");
        }
    };

    class UnknownSprite : public Exception
    {
    public:
        UnknownSprite(std::string_view sceneFile, std::string_view spriteId,
            const std::vector<std::string>& allSpritesIds, DebugInfo info)
            : Exception("UnknownSprite", info)
        {
            this->error("Sprite with id '{}' does not exists inside Scene '{}'", spriteId,
                sceneFile);
            std::vector<std::string> suggestions
                = Utils::String::sortByDistance(spriteId.data(), allSpritesIds, 5);
            std::transform(suggestions.begin(), suggestions.end(), suggestions.begin(),
                Utils::String::quote);
            this->hint(
                "Try one of the Sprites with id ({}...)", fmt::join(suggestions, ", "));
        }
    };

    class UnknownCollider : public Exception
    {
    public:
        UnknownCollider(std::string_view sceneFile, std::string_view colliderId,
            const std::vector<std::string>& allCollidersIds, DebugInfo info)
            : Exception("UnknownCollider", info)
        {
            this->error("Collider with id '{}' does not exists inside Scene '{}'",
                colliderId, sceneFile);
            std::vector<std::string> suggestions
                = Utils::String::sortByDistance(colliderId.data(), allCollidersIds, 5);
            std::transform(suggestions.begin(), suggestions.end(), suggestions.begin(),
                Utils::String::quote);
            this->hint(
                "Try one of the Colliders with id ({}...)", fmt::join(suggestions, ", "));
        }
    };

    class SceneScriptLoadingError : public Exception
    {
    public:
        SceneScriptLoadingError(std::string_view sceneFile, std::string_view scriptPath,
            std::string_view errorMessage, DebugInfo info)
            : Exception("SceneScriptLoadingError", info)
        {
            this->error("Failed to load Scene '{}' script file '{}' as it "
                        "encountered following error : '{}'",
                sceneFile, scriptPath, errorMessage);
        }
    };

    class SceneOnLoadCallbackError : public Exception
    {
    public:
        SceneOnLoadCallbackError(std::string_view sceneFile,
            std::string_view nextSceneFile, std::string_view errorMessage, DebugInfo info)
            : Exception("SceneOnLoadCallbackError", info)
        {
            this->error("Encountered error while running OnLoadCallback to load Scene "
                        "'{}' from Scene '{}' : '{}'",
                nextSceneFile, sceneFile, errorMessage);
        }
    };
}