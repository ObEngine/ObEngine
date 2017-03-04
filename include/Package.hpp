#pragma once

#include <string>
#include <vector>
#include <elzip/elzip.hpp>
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
