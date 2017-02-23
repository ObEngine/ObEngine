#pragma once

#include <string>
#include <typeinfo>
#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>
#include <kaguya/kaguya.hpp>

#include "DataParser.hpp"

namespace mse
{
	namespace System
	{
		namespace Loaders
		{
			extern std::function<int(sf::Texture*, std::string)> textureLoader;
			extern std::function<int(Data::DataParser*, std::string)> dataLoader;
			extern std::function<int(sf::Font*, std::string)> fontLoader;
			extern std::function<int(std::vector<std::string>*, std::string)> dirPathLoader;
			extern std::function<int(std::vector<std::string>*, std::string)> filePathLoader;
			extern std::function<int(kaguya::State*, std::string)> luaLoader;
		}
		class Path
		{
			private:
				std::string path;
			public:
				Path();
				Path(const Path& path);
				Path(std::string path);
				Path add(std::string path);
				std::string getPath(int index);
				std::string toString() const;
				template<typename R>
				bool checkType(R type, std::string expectedType);
				template <typename R, typename F>
				std::string loadResource(R* resource, F lambda, bool silent = false);
				static std::vector<std::string> basePaths;
		};
		template<typename R>
		inline bool Path::checkType(R type, std::string expectedType)
		{
			return (std::string(typeid(R).name()) == expectedType);
		}
		template<typename R, typename F>
		inline std::string Path::loadResource(R* resource, F lambda, bool silent)
		{
			int loadSum = 0;
			for (int i = 0; i < basePaths.size(); i++)
			{
				int loadResponse = 0;
				if (Functions::File::fileExists(basePaths[i] + ((basePaths[i] != "") ? "/" : "") + this->path)) {
					loadResponse = lambda(resource, basePaths[i] + ((basePaths[i] != "") ? "/" : "") + this->path);
				}
					
				loadSum += loadResponse;
				if (loadResponse == 1)
					return basePaths[i];
			}
			if (loadSum > 0)
				return "*";
			else
			{
				if (silent)
					std::cout << "<Error:PathResolver:Path>[loadResource] : Can't find resource : " << this->path << std::endl;
				return "";
			}
		}
	}
}
