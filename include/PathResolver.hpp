#pragma once

#include <string>
#include <typeinfo>
#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <kaguya/kaguya.hpp>
#include <vili/Vili.hpp>

#include "FileFunctions.hpp"
#include "Functions.hpp"
#include "Package.hpp"
#include "Workspace.hpp"

namespace obe
{
    namespace System
    {
        namespace Loaders
        {
            extern std::function<int(sf::Texture*, std::string)> textureLoader;
            extern std::function<int(vili::DataParser*, std::string)> dataLoader;
            extern std::function<int(sf::Font*, std::string)> fontLoader;
            extern std::function<int(std::vector<std::string>*, std::string)> dirPathLoader;
            extern std::function<int(std::vector<std::string>*, std::string)> filePathLoader;
            extern std::function<int(kaguya::State*, std::string)> luaLoader;
            extern std::function<int(sf::SoundBuffer*, std::string)> soundLoader;
            extern std::function<int(sf::Music*, std::string)> musicLoader;
        }

        namespace PathType
        {
            enum PathType
            {
                Path,
                Package,
                Workspace
            };
        }

        class PriorizedPath
        {
        public:
            PriorizedPath(PathType::PathType pathType, std::string basePath, unsigned int priority = 0);
            PathType::PathType pathType;
            std::string basePath;
            std::string getPath() const;
            unsigned int priority;
        };

        class Path
        {
        private:
            std::string path;
            static void orderPriorizedPaths();
        public:
            Path();
            Path(const Path& path);
            Path(std::string path);
            Path add(std::string path) const;
            std::string getPath(int index);
            std::string toString() const;
            template <typename R>
            static bool CheckType(R type, std::string expectedType);
            template <typename R, typename F>
            std::string loadResource(R* resource, F lambda, bool silent = false);
            static void addPath(PriorizedPath path);
            static std::vector<PriorizedPath> basePaths;
            static std::vector<PriorizedPath>& Paths();
        };

        void MountPaths();

        template <typename R>
        bool Path::CheckType(R type, std::string expectedType)
        {
            return (std::string(typeid(R).name()) == expectedType);
        }

        template <typename R, typename F>
        std::string Path::loadResource(R* resource, F lambda, bool silent)
        {
            int loadSum = 0;
            for (int i = 0; i < basePaths.size(); i++)
            {
                int loadResponse = 0;
                if (Functions::File::fileExists(basePaths[i].getPath() + ((basePaths[i].getPath() != "") ? "/" : "") + this->path))
                {
                    loadResponse = lambda(resource, basePaths[i].getPath() + ((basePaths[i].getPath() != "") ? "/" : "") + this->path);
                }

                loadSum += loadResponse;
                if (loadResponse == 1)
                    return basePaths[i].getPath();
            }
            if (loadSum > 0)
                return "*";
            throw aube::ErrorHandler::Raise("ObEngine.PathResolverHeader.Path.CantFindResource", {{"path", path}});
        }
    }
}
