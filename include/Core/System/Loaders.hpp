#pragma once

#include <functional>
#include <string>

#include <Graphics/Font.hpp>
#include <Graphics/Texture.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "vili/node.hpp"

namespace obe::System
{
    // TODO: LoaderResult is not used yet
    class LoaderResult
    {
    private:
        bool m_success;
        std::string m_path;

    public:
        LoaderResult();
        LoaderResult(const std::string& path);
        [[nodiscard]] std::string path() const;
        [[nodiscard]] bool success() const;
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
        [[nodiscard]] std::vector<std::string> paths() const;
        [[nodiscard]] unsigned int loadCount() const;
        [[nodiscard]] bool success() const;
        operator bool() const;
    };
} // namespace obe::System

/**
 * \brief Lambdas used to load different kind of resources using the
 *        System::Path
 */
namespace obe::System::Loaders
{
    template <class Resource> class Loader
    {
    private:
        std::function<bool(Resource&, const std::string&)> m_function;

    public:
        explicit Loader(
            const std::function<bool(Resource&, const std::string&)>& function);
        bool load(Resource& resource, const std::string& path) const;
    };

    /**
     * \brief Load a Texture from a file
     */
    extern Loader<Graphics::Texture> textureLoader;
    /**
     * \brief Load a vili::DataParser from a file
     */
    extern Loader<vili::node> dataLoader;
    /**
     * \brief Load a Font from a file
     */
    extern Loader<Graphics::Font> fontLoader;
    /**
     * \brief List all folders in the specified path
     */
    extern Loader<std::vector<std::string>> dirPathLoader;
    /**
     * \brief List all files in the specified path
     */
    extern Loader<std::vector<std::string>> filePathLoader;

    template <class Resource>
    inline Loader<Resource>::Loader(
        const std::function<bool(Resource&, const std::string&)>& function)
    {
        m_function = function;
    }

    template <class Resource>
    inline bool Loader<Resource>::load(Resource& resource, const std::string& path) const
    {
        return m_function(resource, path);
    }
} // namespace obe::System::Loaders