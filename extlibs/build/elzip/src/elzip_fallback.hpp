#pragma once

#if defined _MSC_VER
#include <direct.h>
#elif defined __GNUC__
#include <sys/types.h>
#include <sys/stat.h>
#endif

#include <iostream>
#include <fstream>
#include <string>

#include "unzipper.hpp"
#include "tinydir.h"

namespace elz
{
	void extractZip(std::string zipname, std::string target = ".");
	void extractFile(std::string zipname, std::string filename, std::string target = ".");
}

template <typename V>
inline bool isInList(V term, const std::vector<V>& list1)
{
	for (size_t k = 0; k < list1.size(); k++)
	{
		if (term == list1[k])
			return true;
	}
	return false;
}