#pragma once

#include <string>
#include <vector>

#ifdef _USE_CPP_NEW_FS
	#include <elzip/elzip.hpp>
#else
	#include <elzip/elzip_fallback.hpp>
#endif 

#include <vili/Vili.hpp>

#include "Functions.hpp"
#include "PathResolver.hpp"

namespace obe
{
	namespace System
	{
		class Package
		{
		public:
			static std::string GetPackageLocation(std::string packageName);
			static bool PackageExists(std::string packageName);
			static bool Install(std::string packageName);
			static bool Load(std::string packageName, unsigned int priority = 1);
		};
	}
}
