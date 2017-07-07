#pragma once

#include <tuple>
#include <string>
#include <vector>

namespace obe
{
    namespace Utils
    {
        namespace String
        {
            std::vector<std::string> split(const std::string& str, const std::string& delimiters = " ");
            std::vector<std::string> multiSplit(std::string str, const std::vector<std::string>& seps);
            int occurencesInString(const std::string& str, const std::string& occur);
            bool isStringAlpha(const std::string& str);
            bool isStringAlphaNumeric(const std::string& str);
            bool isStringNumeric(const std::string& str);
            bool isStringInt(const std::string& str);
            bool isStringFloat(const std::string& str);
            void removeCharFromString(std::string& str, const std::string& charToRemove);
            void replaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace);
            std::string replaceString(std::string subject, const std::string& search, const std::string& replace);
            bool isBetween(const std::string& string, const std::string& bet);
            std::string extract(const std::string& base, int start, int end);
            std::vector<std::string> extractBetween(std::string& str, char delimiter1, char delimiter2);
            std::string getRandomKey(std::string set, int len);
            void regenerateEncoding(std::string& str);
            std::string stringToAsciiCode(std::string& str);
            std::string cutBeforeAsciiCode(std::string& str, int asciiCode);
            typedef std::tuple<std::vector<std::string>, std::vector<std::string>, std::vector<std::pair<int, int>>> StringExtractor;
            StringExtractor extractAllStrings(std::string str);
            bool contains(const std::string& string, const std::string& search);
        }
    }
}