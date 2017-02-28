//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "Functions.hpp"

namespace vili
{
	namespace Functions
	{
		//Functions::String
		void String::removeCharFromString(std::string &str, std::string charToRemove)
		{
			str.erase(remove(str.begin(), str.end(), charToRemove.c_str()[0]), str.end());
		}
		std::vector<std::string> String::split(const std::string &str, const std::string &delimiters)
		{
			std::vector<std::string> tokens;
			std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
			std::string::size_type pos = str.find_first_of(delimiters, lastPos);
			while (std::string::npos != pos || std::string::npos != lastPos)
			{
				tokens.push_back(str.substr(lastPos, pos - lastPos));
				lastPos = str.find_first_not_of(delimiters, pos);
				pos = str.find_first_of(delimiters, lastPos);
			}
			return tokens;
		}
		int String::occurencesInString(std::string str, std::string occur)
		{
			int occurrences = 0;
			std::string::size_type start = 0;
			while ((start = str.find(occur, start)) != std::string::npos)
			{
				++occurrences;
				start += occur.length(); // see the note
			}
			return occurrences;
		}
		bool String::isStringAlpha(std::string str)
		{
			if (str.size() > 0)
				return std::all_of(str.begin(), str.end(), ::isalpha);
			else
				return false;
		}
		bool String::isStringAlphaNumeric(std::string str)
		{
			if (str.size() > 0)
				return std::all_of(str.begin(), str.end(), ::isalnum);
			else
				return false;
		}
		bool String::isStringInt(std::string str)
		{
			if (str.size() > 0)
			{
				if (str.substr(0, 1) == "-")
					str = str.substr(1);
				return std::all_of(str.begin(), str.end(), ::isdigit);
			}
			else
				return false;
		}
		bool String::isStringFloat(std::string str)
		{
			bool isFloat = false;
			if (str.size() > 0)
			{
				if (str.substr(0, 1) == "-")
					str = str.substr(1);
				if (String::occurencesInString(str, ".") == 1)
				{
					isFloat = true;
					String::removeCharFromString(str, ".");
				}
				return (std::all_of(str.begin(), str.end(), ::isdigit) && isFloat);
			}
			else
				return false;
		}
		bool String::isStringNumeric(std::string str)
		{
			return (String::isStringFloat(str) || String::isStringInt(str));
		}

		void String::replaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace)
		{
			size_t pos = 0;
			while ((pos = subject.find(search, pos)) != std::string::npos)
			{
				subject.replace(pos, search.length(), replace);
				pos += replace.length();
			}
		}
		std::string String::replaceString(std::string subject, const std::string& search, const std::string &replace)
		{
			size_t pos = 0;
			while ((pos = subject.find(search, pos)) != std::string::npos)
			{
				subject.replace(pos, search.length(), replace);
				pos += replace.length();
			}
			return subject;
		}
		bool String::isBetween(const std::string& string, const std::string& bet)
		{
			return (string.substr(0, bet.size()) == bet && string.substr(string.size() - bet.size(), bet.size()) == bet);
		}
		std::string String::extract(const std::string& base, int start, int end)
		{
			return base.substr(start, base.size() - start - end);
		}
		std::vector<std::string> String::extractBetween(std::string &str, char delimiter1, char delimiter2)
		{
			std::vector<std::string> strings;
			int start = 0;
			int end = 0;
			bool hasFindStart = false;
			bool hasFind = false;
			for (unsigned int i = 0; i < str.size(); i++)
			{
				if (hasFindStart && str[i] == delimiter2)
				{
					hasFindStart = false;
					end = i;
					hasFind = true;
				}
				if (str[i] == delimiter1 && !hasFindStart && !hasFind)
				{
					start = i;
					hasFindStart = true;
				}
				if (hasFind)
				{
					strings.push_back(str.substr(start + 1, end - start - 1));
					hasFind = false;
				}
			}
			for (unsigned int i = 0; i < strings.size(); i++)
				String::replaceStringInPlace(str, strings[i], "");
			return strings;
		}
		String::StringExtractor String::extractAllStrings(std::string string)
		{
			bool readingString = false;
			std::vector<std::string> extractedStrings;
			std::vector<std::string> otherComponents;
			std::vector<std::pair<int, int>> indexes;
			std::string currentStack = "";
			for (unsigned int i = 0; i < string.size(); i++)
			{
				std::string currentChar = string.substr(i, 1);
				if (currentChar == "\"")
				{
					if (readingString)
					{
						extractedStrings.push_back(currentStack);
						indexes.push_back(std::pair<int, int>(0, extractedStrings.size() - 1));
					}
					else if (currentStack.size() > 0)
					{
						otherComponents.push_back(currentStack);
						indexes.push_back(std::pair<int, int>(1, otherComponents.size() - 1));
					}
					readingString = !readingString;
					currentStack.clear();
				}
				else
				{
					currentStack += currentChar;
				}
			}
			if (!readingString)
			{
				otherComponents.push_back(currentStack);
				indexes.push_back(std::pair<int, int>(1, otherComponents.size() - 1));
			}
			return std::make_tuple(extractedStrings, otherComponents, indexes);
		}
		bool String::contains(const std::string& string, const std::string& search)
		{
			return (string.find(search) != std::string::npos);
		}

		//Functions::Vector
		std::string Vector::join(std::vector<std::string>& vector, std::string sep, int start, int end)
		{
			std::string result = "";
			if (end >= vector.size())
				end = vector.size();
			if (start >= vector.size() - 1)
				start = vector.size() - 1;
			for (unsigned int i = start; i < vector.size() - end; i++)
			{
				if (i != vector.size() - 1)
					result += vector[i] + sep;
				else
					result += vector[i];
			}
			return result;
		}
		void Vector::joinBetween(std::vector<std::string>& vector, std::string joinValue, std::string sep)
		{
			std::string stack = "";
			bool stacking = false;
			std::vector<int> toErase;
			for (unsigned int i = 0; i < vector.size(); i++)
			{
				if (vector.at(i) == joinValue)
				{
					if (stacking)
					{
						stack += vector.at(i);
						vector.at(i) = stack;
						stack = "";
					}
					stacking = !stacking;
				}
				if (stacking)
				{
					stack += vector.at(i) + sep;
					toErase.push_back(i);
				}
			}
			for (int i = toErase.size() - 1; i >= 0; i--)
				vector.erase(vector.begin() + toErase[i]);
		}
		void Vector::mergeNeighboors(std::vector<std::string>& vector, std::string n1, std::string n2, std::string sep, bool strict)
		{
			if (vector.size() > 0)
			{
				std::vector<int> toErase;
				for (unsigned int i = 0; i < vector.size() - 1; i++)
				{
					if (strict)
					{
						if (vector.at(i) == n1 && vector.at(i + 1) == n2)
						{
							vector.at(i) = vector.at(i) + sep + vector.at(i + 1);
							toErase.push_back(i + 1);
						}
					}
					else
					{
						if ((vector.at(i) == n1 && vector.at(i + 1) == n2) || (vector.at(i) == n2 && vector.at(i + 1) == n1))
						{
							vector.at(i) = vector.at(i) + sep + vector.at(i + 1);
							toErase.push_back(i + 1);
						}
					}
				}
				for (int i = toErase.size() - 1; i >= 0; i--)
					vector.erase(vector.begin() + toErase[i]);
			}
		}

	}
}