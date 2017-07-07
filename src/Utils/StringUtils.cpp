#include <algorithm>
#include <clocale>
#include <cctype>
#include <iostream>
#include <sstream>

#include <Utils/MathUtils.hpp>
#include <Utils/StringUtils.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe
{
    namespace Utils
    {
        namespace String 
        {
            void removeCharFromString(std::string& str, const std::string& charToRemove)
            {
                str.erase(std::remove(str.begin(), str.end(), charToRemove.c_str()[0]), str.end());
            }

            std::vector<std::string> split(const std::string& str, const std::string& delimiters)
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

            std::vector<std::string> multiSplit(std::string str, const std::vector<std::string>& seps)
            {
                for (unsigned int i = 0; i < seps.size(); i++)
                    replaceStringInPlace(str, seps[i], "~" + seps[i] + "~");
                return split(str, "~");
            }

            int occurencesInString(const std::string& str, const std::string& occur)
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

            bool isStringAlpha(const std::string& str)
            {
                if (str.size() > 0)
                    return std::all_of(str.begin(), str.end(), isalpha);
                return false;
            }

            bool isStringAlphaNumeric(const std::string& str)
            {
                if (str.size() > 0)
                    return all_of(str.begin(), str.end(), isalnum);
                return false;
            }

            bool isStringInt(const std::string& str)
            {
                if (str.size() > 0)
                {
                    if (str.substr(0, 1) == "-")
                        return all_of(str.substr(1).begin(), str.substr(1).end(), isdigit);
                    return all_of(str.begin(), str.end(), isdigit);
                }
                return false;
            }

            bool isStringFloat(const std::string& str)
            {
                std::string modifyStr = str;
                bool isFloat = false;
                if (modifyStr.size() > 0)
                {
                    if (modifyStr.substr(0, 1) == "-")
                        modifyStr = modifyStr.substr(1);
                    if (occurencesInString(modifyStr, ".") == 1)
                    {
                        isFloat = true;
                        removeCharFromString(modifyStr, ".");
                    }
                    return (all_of(modifyStr.begin(), modifyStr.end(), isdigit) && isFloat);
                }
                return false;
            }

            bool isStringNumeric(const std::string& str)
            {
                return (isStringFloat(str) || isStringInt(str));
            }

            void replaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace)
            {
                size_t pos = 0;
                while ((pos = subject.find(search, pos)) != std::string::npos)
                {
                    subject.replace(pos, search.length(), replace);
                    pos += replace.length();
                }
            }

            std::string replaceString(std::string subject, const std::string& search, const std::string& replace)
            {
                size_t pos = 0;
                while ((pos = subject.find(search, pos)) != std::string::npos)
                {
                    subject.replace(pos, search.length(), replace);
                    pos += replace.length();
                }
                return subject;
            }

            bool isBetween(const std::string& string, const std::string& bet)
            {
                return (string.substr(0, bet.size()) == bet && string.substr(string.size() - bet.size(), bet.size()) == bet);
            }

            std::string extract(const std::string& base, int start, int end)
            {
                return base.substr(start, base.size() - start - end);
            }

            std::vector<std::string> extractBetween(std::string& str, char delimiter1, char delimiter2)
            {
                std::vector<std::string> strings;
                int start = 0;
                int end = 0;
                bool hasFindStart = false;
                bool hasFind = false;
                for (int i = 0; i < str.size(); i++)
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
                for (int i = 0; i < strings.size(); i++)
                    replaceStringInPlace(str, strings[i], "");
                return strings;
            }

            std::string getRandomKey(std::string set, int len)
            {
                std::string r;
                for (int i = 0; i < len; i++) r.push_back(set.at(size_t(Math::randint(0, 100000) % set.size())));
                return r;
            }

            void regenerateEncoding(std::string& str)
            {
                std::vector<int> data(str.begin(), str.end());
                //for (int i = 0; i < data.size(); i++) { std::cout << data[i] << " "; }
                //std::cout << std::endl;
                int i = 0;
                char ch;
                str = "";
                while (i < data.size())
                {
                    if (data[i] == -61)
                    {
                        if (i < data.size() - 1) { data[i] = data[i + 1] + 64; }
                        data.erase(data.begin() + i + 1);
                    }
                    i++;
                }
                for (int j = 0; j < data.size(); j++)
                {
                    ch = data[j];
                    str += ch;
                }
            }

            std::string stringToAsciiCode(std::string& str)
            {
                std::vector<int> data(str.begin(), str.end());
                std::vector<std::string> dataStr;
                std::transform(data.begin(), data.end(), back_inserter(dataStr), [](const int& idata) { return std::to_string(idata); });
                return Vector::join(dataStr, ",");
            }

            std::string cutBeforeAsciiCode(std::string& str, int asciiCode)
            {
                std::vector<int> data(str.begin(), str.end());
                std::vector<std::string> dataStr;
                for (int i = 0; i < data.size(); i++)
                {
                    if (data[i] != asciiCode)
                    {
                        char a = data[i];
                        std::string strbuf;
                        std::stringstream strbridge;
                        strbridge << a;
                        strbridge >> strbuf;
                        //std::cout << "Trsf : " << strbuf << std::endl;
                        dataStr.push_back(strbuf);
                    }
                    else
                        break;
                }
                return Vector::join(dataStr, ",");
            }

            StringExtractor extractAllStrings(std::string string)
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
                return make_tuple(extractedStrings, otherComponents, indexes);
            }

            bool contains(const std::string& string, const std::string& search)
            {
                return (string.find(search) != std::string::npos);
            }
        }
    }
}