//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <random>
#include <algorithm>
#include <iterator>

#include "tinydir.h"

namespace fn
{
	namespace Coord
	{
		extern int baseWidth;
		extern int baseHeight;
		extern int width;
		extern int height;
		int adaptCamX(int camX, int sizeX);
		int adaptCamY(int camY, int sizeY);
	}
	namespace File
	{
		std::vector<std::string> listDirInDir(std::string path);
		std::vector<std::string> listFileInDir(std::string path);
	}
	namespace Map
	{
		template <typename T, typename U>
		bool isInMap(T item, std::map<U,T>& map);
		template <typename T, typename U>
		bool keyInMap(T item, std::map<T, U>& map);
	}
	namespace Math
	{
		extern double pi;
		int randint(int min, int max);
		double randfloat();
		template <typename N>
		int getMin(N min1, N min2);
		template <typename N>
		int getMax(N max1, N max2);
		template <typename N>
		bool isBetween(N target, N lowerBound, N upperBound);
		bool isDoubleInt(double& value);
	}
	namespace Run
	{
		class Parser
		{
			private:
				char** start;
				int size;
			public:
				Parser(char** start, int size);
				bool argumentExists(std::string arg);
				std::string getArgumentValue(std::string arg);
		};
	}
	namespace String
	{
		std::vector<std::string> split(const std::string &str, const std::string &delimiters = " ");
		std::vector<std::string> multiSplit(std::string str, std::vector<std::string> seps, std::vector<std::string> sepsBef, std::vector<std::string> sepsAft);
		std::vector<std::string> multiSplit(std::string str, std::vector<std::string> sepsBef, std::vector<std::string> sepsAft);
		std::vector<std::string> multiSplit(std::string str, std::vector<std::string> seps);
		int occurencesInString(std::string str, std::string occur);
		bool isStringAlpha(std::string str);
		bool isStringAlphaNumeric(std::string str);
		bool isStringNumeric(std::string str);
		bool isStringInt(std::string str);
		bool isStringFloat(std::string str);
		void removeCharFromString(std::string &str, std::string charToRemove);
		void replaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace);
		std::string replaceString(std::string subject, const std::string& search, const std::string &replace);
		bool isBetween(const std::string& string, const std::string& bet);
		std::string extract(const std::string& base, int start, int end);
		std::vector<std::string> extractBetween(std::string &str, char delimiter1, char delimiter2);
		std::string getRandomKey(std::string set, int len);
		void regenerateEncoding(std::string& str);
		std::string stringToAsciiCode(std::string& str);
		std::string cutBeforeAsciiCode(std::string& str, int asciiCode);
	}
	namespace Vector
	{
		template <typename V>
		bool isInList(V item, const std::vector<V>& vector);
		std::string join(std::vector<std::string>& vector, std::string sep = "", int start = 0, int end = 0);
		template <typename V>
		void eraseAll(std::vector<V>& vector, V elem);
		void joinBetween(std::vector<std::string>& vector, std::string joinValue, std::string sep = "");
		void mergeNeighboors(std::vector<std::string>& vector, std::string n1, std::string n2, std::string sep = "", bool strict = false);
		template <typename V>
		int findSubVector(std::vector<V>& vector, std::vector<V>& find);
		template <typename V>
		std::vector<V> getSubVector(const std::vector<V>& vector, int start = 0, int end = 0);
	}
}

//Functions::Map
template <typename T, typename U>
inline bool fn::Map::isInMap(T item, std::map<U, T>& map)
{
	for (auto iterator = map.begin(); iterator != map.end(); iterator++) {
		if (iterator->second == item)
			return true;
	}
	return false;
}
template <typename T, typename U>
inline bool fn::Map::keyInMap(T item, std::map<T, U>& map) {
	for (auto iterator = map.begin(); iterator != map.end(); iterator++) {
		if (iterator->first == item)
			return true;
	}
	return false;
}

//Functions::Math
template <typename N>
inline int fn::Math::getMin(N min1, N min2) {
	return (min1 < min2) ? min1 : min2;
}
template <typename N>
inline int fn::Math::getMax(N max1, N max2) {
	return (max1 > max2) ? max1 : max2;
}
template <typename N>
inline bool fn::Math::isBetween(N target, N lowerBound, N upperBound)
{
	if (target >= lowerBound && target <= upperBound)
		return true;
	else
		return false;
}

//Functions::Vector
template <typename V>
inline bool fn::Vector::isInList(V term, const std::vector<V>& list1)
{
	for (size_t k = 0; k < list1.size(); k++)
	{
		if (term == list1[k])
			return true;
	}
	return false;
}
template <typename V>
inline void fn::Vector::eraseAll(std::vector<V>& vector, V elem)
{
	std::vector<int> toErase;
	for (int i = 0; i < vector->size(); i++)
	{
		if (vector->at(i) == elem)
			toErase.push_back(i);
	}
	for (int i = toErase.size() - 1; i >= 0; i--)
		vector->erase(vector->begin() + toErase[i]);
}
template <typename V>
inline int fn::Vector::findSubVector(std::vector<V>& vector, std::vector<V>& find)
{
	int occ = 0;
	int potentialIndex = -1;
	bool startedSearch = false;
	if (find.size() < vector.size())
	{
		for (int i = 0; i < vector.size(); i++)
		{
			std::cout << "Compare : " << find[occ] << " and " << vector[i] << std::endl;
			if (find[occ] == vector[i])
			{
				if (!startedSearch)
				{
					potentialIndex = i;
					startedSearch = true;
				}
				occ++;
			}
			else if (startedSearch && find[occ] == vector[i])
			{
				startedSearch = false;
				occ = 0;
				potentialIndex = -1;
			}
		}
	}
	return potentialIndex;
}
template <typename V>
inline std::vector<V> fn::Vector::getSubVector(const std::vector<V>& vector, int start, int end)
{
	auto first = vector.begin() + start;
	auto last = vector.end() - end;
	std::vector<V> newVec(first, last);
	return newVec;
}