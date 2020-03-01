#pragma once

#include <functional>
#include <optional>
#include <string>

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <kaguya/kaguya.hpp>
#include <vili/Vili.hpp>

namespace obe::System
{
    class LoaderResult
    {
    private:
        bool m_success;
        std::string m_path;

    public:
        LoaderResult();
        LoaderResult(const std::string& path);
        std::string path() const;
        bool success() const;
        operator bool() const;
    };

    class LoaderMultipleResult
    {
    private:
        std::vector<std::string> m_paths;
        unsigned int m_loadCount;

    public:
        LoaderMultipleResult();
        LoaderMultipleResult(const std::vector<std::string>& paths);
        std::vector<std::string> paths() const;
        unsigned int loadCount() const;
        bool success() const;
        operator bool() const;
    };
} // namespace obe::System

/**
 * \brief Lambdas used to load different kind of resources using the
 * System::Path
 */
namespace obe::System::Loaders
{
    /*template <template <class ResourceType> class LoaderType>
    class NonOwnedLoaderResult
    {
    private:
        LoaderType<ResourceType>& m_loader;
        ResourceType& m_non_owned_resource;
        std::string path;
    public:
        NonOwnedLoaderResult(const LoaderType<ResourceType>& loader,
    LoadedResource& reference, const std::string& path); bool load();
        std::string getPath() const;
    };

    template <template <class ResourceType> class LoaderType>
    class LoaderResult
    {
    private:
        LoaderType<ResourceType>& m_loader;
        std::string path;
    public:
        LoaderResult(const LoaderType<ResourceType>& loader, const std::string&
    path); NonOwnedLoaderResult<LoaderType<ResourceType>>& use(ResourceType&
    resource); template <class ...Args>
        std::optional<std::unique_ptr<ResourceType>> load(Args... args);
        std::string getPath() const;
    };*/

    template <class Resource> class Loader
    {
    private:
        std::function<bool(Resource&, const std::string&)> m_function;

    public:
        Loader(
            const std::function<bool(Resource&, const std::string&)>& function);
        bool load(Resource& resource, const std::string& path) const;
    };

    /**
     * \brief Load a sf::Texture from a file
     */
    extern Loader<sf::Texture> textureLoader;
    /**
     * \brief Load a vili::DataParser from a file
     */
    extern Loader<vili::ViliParser> dataLoader;
    // extern Loader<vili::ViliParser> dataLoader;
    /**
     * \brief Load a sf::Font from a file
     */
    extern Loader<sf::Font> fontLoader;
    /**
     * \brief List all folders in the specified path
     */
    extern Loader<std::vector<std::string>> dirPathLoader;
    /**
     * \brief List all files in the specified path
     */
    extern Loader<std::vector<std::string>> filePathLoader;
    /**
     * \brief Load the Lua source from a file
     */
    extern Loader<kaguya::State> luaLoader;

    /*template <class LoaderType<class ResourceType>>
    inline
    NonOwnedLoaderResult<LoaderType<ResourceType>>::NonOwnedLoaderResult(const
    LoaderType<ResourceType>& loader, LoadedResource& reference, const
    std::string& path) : m_non_owned_resource(reference), m_loader(loader)
    {
        m_path = path;
    }

    template <class LoaderType<class ResourceType>>
    inline bool NonOwnedLoaderResult<LoaderType<ResourceType>>::load()
    {
        return loader.load(&m_non_owned_resource, m_path);
    }

    template <class LoaderType<class ResourceType>>
    inline std::string NonOwnedLoaderResult<LoaderType<ResourceType>>::getPath()
    const
    {
        return m_path;
    }

    template <class LoaderType<class ResourceType>>
    inline LoaderResult<LoaderType<ResourceType>>::LoaderResult(const
    LoaderType<ResourceType>& loader, const std::string& path) :
    m_loader(loader)
    {
        m_path = path;
    }

    template <class LoaderType<class ResourceType>>
    inline NonOwnedLoaderResult<LoaderType<ResourceType>>&
    LoaderResult<LoaderType<ResourceType>>::use(LoadedResource& resource)
    {
        return NonOwnedLoaderResult<LoadedResource, LoaderClass>(resource,
    m_path);
    }

    template <class LoaderType<class ResourceType>>
    template <class ...Args>
    inline std::optional<std::unique_ptr<ResourceType>>
    LoaderResult<LoaderType<ResourceType>>::load(Args... args)
    {
        std::unique_ptr<LoadedResource> newResource =
    std::make_unique<LoadedResource>(std::forward(args...)); if
    (m_loader.load(&newResource, m_path))
        {
            return
    std::make_optional<std::unique_ptr<LoadedResource>>(std::move(newResource));
        }
        else
        {
            return std::make_optional<std::unique_ptr<LoadedResource>>();
        }
    }

    template <class LoaderType<class ResourceType>>
    inline std::string LoaderResult<LoaderType<ResourceType>>::getPath() const
    {
        return m_path;
    }*/

    template <class Resource>
    inline Loader<Resource>::Loader(
        const std::function<bool(Resource&, const std::string&)>& function)
    {
        m_function = function;
    }

    template <class Resource>
    inline bool Loader<Resource>::load(
        Resource& resource, const std::string& path) const
    {
        return m_function(resource, path);
    }
} // namespace obe::System::Loaders