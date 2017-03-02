//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <iterator>

namespace vili
{
	namespace Functions
	{
		namespace String
		{
			std::vector<std::string> split(const std::string &str, const std::string &delimiters = " ");
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
			typedef std::tuple<std::vector<std::string>, std::vector<std::string>, std::vector<std::pair<int, int>>> StringExtractor;
			StringExtractor extractAllStrings(std::string);
			bool contains(const std::string& string, const std::string& search);
		}
		namespace Vector
		{
			template <typename V>
			bool isInList(V item, const std::vector<V>& vector);
			template <typename V>
			int indexOfElement(V item, const std::vector<V>& vector);
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

		//Functions::Vector
		template <typename V>
		inline bool Vector::isInList(V term, const std::vector<V>& list1)
		{
			for (size_t k = 0; k < list1.size(); k++)
			{
				if (term == list1[k])
					return true;
			}
			return false;
		}
		template<typename V>
		int Vector::indexOfElement(V item, const std::vector<V>& vector)
		{
			for (size_t k = 0; k < vector.size(); k++)
			{
				if (item == vector[k])
					return k;
			}
			return -1;
		}
		template <typename V>
		inline void Vector::eraseAll(std::vector<V>& vector, V elem)
		{
			std::vector<int> toErase;
			for (int i = 0; i < vector.size(); i++)
			{
				if (vector.at(i) == elem)
					toErase.push_back(i);
			}
			for (int i = toErase.size() - 1; i >= 0; i--)
				vector.erase(vector.begin() + toErase[i]);
		}
		template <typename V>
		inline int Vector::findSubVector(std::vector<V>& vector, std::vector<V>& find)
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
		inline std::vector<V> Vector::getSubVector(const std::vector<V>& vector, int start, int end)
		{
			auto first = vector.begin() + start;
			auto last = vector.end() - end;
			std::vector<V> newVec(first, last);
			return newVec;
		}
	}
}
