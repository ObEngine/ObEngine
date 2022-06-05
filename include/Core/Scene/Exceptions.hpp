#pragma once

#include <Exception.hpp>

namespace obe::Scene::Exceptions
{
    class ChildNotInSceneNode : public Exception<ChildNotInSceneNode>
    {
    public:
        using Exception::Exception;
        ChildNotInSceneNode(void* sceneNode, void* child, DebugInfo info)
            : Exception(info)
        {
            this->error("Impossible to remove Movable {} from SceneNode {} as it is not "
                        "one of its children",
                fmt::ptr(sceneNode), fmt::ptr(child));
        }
    };

    class MissingSceneFileBlock : public Exception<MissingSceneFileBlock>
    {
    public:
        using Exception::Exception;
        MissingSceneFileBlock(
            std::string_view sceneFile, std::string_view blockName, DebugInfo info)
            : Exception(info)
        {
            this->error(
                "Scene from file '{}' does not have any required <{}> block", sceneFile, blockName);
            this->hint("Add a '{}' block to the Scene file", blockName);
        }
    };

    class UnknownGameObject : public Exception<UnknownGameObject>
    {
    public:
        using Exception::Exception;
        UnknownGameObject(std::string_view sceneFile, std::string_view objectId,
            const std::vector<std::string>& allObjectIds, DebugInfo info)
            : Exception(info)
        {
            this->error(
                "GameObject with id '{}' does not exists inside Scene '{}'", objectId, sceneFile);
            std::vector<std::string> suggestions
                = Utils::String::sortByDistance(objectId.data(), allObjectIds, 5);
            std::transform(
                suggestions.begin(), suggestions.end(), suggestions.begin(), Utils::String::quote);
            suggestions.push_back("...");
            this->hint("Try one of the GameObjects with id ({})", fmt::join(suggestions, ", "));
        }
    };

    class GameObjectAlreadyExists : public Exception<GameObjectAlreadyExists>
    {
    public:
        using Exception::Exception;
        GameObjectAlreadyExists(std::string_view sceneFile, std::string_view objectType,
            std::string_view objectId, DebugInfo info)
            : Exception(info)
        {
            this->error("Scene '{}' already contains a GameObject of type '{}' with id '{}'",
                sceneFile, objectType, objectId);
            this->hint("Try choosing a different id to avoid name conflict");
        }
    };

    class UnknownSprite : public Exception<UnknownSprite>
    {
    public:
        using Exception::Exception;
        UnknownSprite(std::string_view sceneFile, std::string_view spriteId,
            const std::vector<std::string>& allSpritesIds, DebugInfo info)
            : Exception(info)
        {
            this->error(
                "Sprite with id '{}' does not exists inside Scene '{}'", spriteId, sceneFile);
            std::vector<std::string> suggestions
                = Utils::String::sortByDistance(spriteId.data(), allSpritesIds, 5);
            std::transform(
                suggestions.begin(), suggestions.end(), suggestions.begin(), Utils::String::quote);
            suggestions.push_back("...");
            this->hint("Try one of the Sprites with id ({})", fmt::join(suggestions, ", "));
        }
    };

    class UnknownCollider : public Exception<UnknownCollider>
    {
    public:
        using Exception::Exception;
        UnknownCollider(std::string_view sceneFile, std::string_view colliderId,
            const std::vector<std::string>& allCollidersIds, DebugInfo info)
            : Exception(info)
        {
            this->error(
                "Collider with id '{}' does not exists inside Scene '{}'", colliderId, sceneFile);
            std::vector<std::string> suggestions
                = Utils::String::sortByDistance(colliderId.data(), allCollidersIds, 5);
            std::transform(
                suggestions.begin(), suggestions.end(), suggestions.begin(), Utils::String::quote);
            suggestions.push_back("...");
            this->hint("Try one of the Colliders with id ({})", fmt::join(suggestions, ", "));
        }
    };

    class SceneScriptLoadingError : public Exception<SceneScriptLoadingError>
    {
    public:
        using Exception::Exception;
        SceneScriptLoadingError(std::string_view sceneFile, std::string_view scriptPath,
            std::string_view errorMessage, DebugInfo info)
            : Exception(info)
        {
            this->error("Failed to load Scene '{}' script file '{}' as it "
                        "encountered following error : '{}'",
                sceneFile, scriptPath, errorMessage);
        }
    };

    class SceneOnLoadCallbackError : public Exception<SceneOnLoadCallbackError>
    {
    public:
        using Exception::Exception;
        SceneOnLoadCallbackError(std::string_view sceneFile, std::string_view nextSceneFile,
            std::string_view errorMessage, DebugInfo info)
            : Exception(info)
        {
            this->error("Encountered error while running OnLoadCallback to load Scene "
                        "'{}' from Scene '{}' : '{}'",
                nextSceneFile, sceneFile, errorMessage);
        }
    };

    class InvalidSceneFile : public Exception<InvalidSceneFile>
    {
    public:
        using Exception::Exception;
        InvalidSceneFile(std::string_view sceneFile, DebugInfo info)
            : Exception(info)
        {
            this->error("Encountered error while loading Scene from file '{}'", sceneFile);
        }
    };
}
