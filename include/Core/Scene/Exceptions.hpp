#pragma once

#include <Exception.hpp>

/**
 * \nobind
 */
namespace obe::scene::exceptions
{
    class ChildNotInSceneNode : public Exception<ChildNotInSceneNode>
    {
    public:
        using Exception::Exception;
        ChildNotInSceneNode(void* scene_node, void* child,
            std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error("Impossible to remove Movable {} from SceneNode {} as it is not "
                        "one of its children",
                fmt::ptr(scene_node), fmt::ptr(child));
        }
    };

    class MissingSceneFileBlock : public Exception<MissingSceneFileBlock>
    {
    public:
        using Exception::Exception;
        MissingSceneFileBlock(std::string_view scene_file, std::string_view block_name,
            std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error("Scene from file '{}' does not have any required <{}> block", scene_file,
                block_name);
            this->hint("Add a '{}' block to the Scene file", block_name);
        }
    };

    class UnknownGameObject : public Exception<UnknownGameObject>
    {
    public:
        using Exception::Exception;
        UnknownGameObject(std::string_view scene_file, std::string_view object_id,
            const std::vector<std::string>& all_object_ids,
            std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error(
                "GameObject with id '{}' does not exists inside Scene '{}'", object_id, scene_file);
            std::vector<std::string> suggestions
                = utils::string::sort_by_distance(object_id.data(), all_object_ids, 5);
            std::transform(
                suggestions.begin(), suggestions.end(), suggestions.begin(), utils::string::quote);
            suggestions.emplace_back("...");
            this->hint("Try one of the GameObjects with id ({})", fmt::join(suggestions, ", "));
        }
    };

    class GameObjectAlreadyExists : public Exception<GameObjectAlreadyExists>
    {
    public:
        using Exception::Exception;
        GameObjectAlreadyExists(std::string_view scene_file, std::string_view object_type,
            std::string_view object_id,
            std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error("Scene '{}' already contains a GameObject of type '{}' with id '{}'",
                scene_file, object_type, object_id);
            this->hint("Try choosing a different id to avoid name conflict");
        }
    };

    class UnknownSprite : public Exception<UnknownSprite>
    {
    public:
        using Exception::Exception;
        UnknownSprite(std::string_view scene_file, std::string_view sprite_id,
            const std::vector<std::string>& all_sprites_ids,
            std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error(
                "Sprite with id '{}' does not exists inside Scene '{}'", sprite_id, scene_file);
            std::vector<std::string> suggestions
                = utils::string::sort_by_distance(sprite_id.data(), all_sprites_ids, 5);
            std::transform(
                suggestions.begin(), suggestions.end(), suggestions.begin(), utils::string::quote);
            suggestions.emplace_back("...");
            this->hint("Try one of the Sprites with id ({})", fmt::join(suggestions, ", "));
        }
    };

    class UnknownCollider : public Exception<UnknownCollider>
    {
    public:
        using Exception::Exception;
        UnknownCollider(std::string_view scene_file, std::string_view collider_id,
            const std::vector<std::string>& all_colliders_ids,
            std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error(
                "Collider with id '{}' does not exists inside Scene '{}'", collider_id, scene_file);
            std::vector<std::string> suggestions
                = utils::string::sort_by_distance(collider_id.data(), all_colliders_ids, 5);
            std::transform(
                suggestions.begin(), suggestions.end(), suggestions.begin(), utils::string::quote);
            suggestions.emplace_back("...");
            this->hint("Try one of the Colliders with id ({})", fmt::join(suggestions, ", "));
        }
    };

    class SceneScriptLoadingError : public Exception<SceneScriptLoadingError>
    {
    public:
        using Exception::Exception;
        SceneScriptLoadingError(std::string_view scene_file, std::string_view script_path,
            std::string_view error_message,
            std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error("Failed to load Scene '{}' script file '{}' as it "
                        "encountered following error : '{}'",
                scene_file, script_path, error_message);
        }
    };

    class SceneOnLoadCallbackError : public Exception<SceneOnLoadCallbackError>
    {
    public:
        using Exception::Exception;
        SceneOnLoadCallbackError(std::string_view scene_file, std::string_view next_scene_file,
            std::string_view error_message,
            std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error("Encountered error while running OnLoadCallback to load Scene "
                        "'{}' from Scene '{}' : '{}'",
                next_scene_file, scene_file, error_message);
        }
    };

    class InvalidSceneFile : public Exception<InvalidSceneFile>
    {
    public:
        using Exception::Exception;
        InvalidSceneFile(std::string_view scene_file,
            std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error("Encountered error while loading Scene from file '{}'", scene_file);
        }
    };
} // namespace obe::scene::exceptions
