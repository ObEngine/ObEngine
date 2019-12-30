#include <algorithm>
#include <cctype>
#include <clocale>

#include <Utils/MathUtils.hpp>
#include <Utils/StringUtils.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe::Utils::String
{
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

    int occurencesInString(const std::string& str, const std::string& occur)
    {
        int occurrences = 0;
        std::string::size_type start = 0;
        while ((start = str.find(occur, start)) != std::string::npos)
        {
            ++occurrences;
            start += occur.length();
        }
        return occurrences;
    }

    bool isStringAlpha(const std::string& str)
    {
        if (!str.empty())
            return all_of(str.begin(), str.end(), isalpha);
        return false;
    }

    bool isStringAlphaNumeric(const std::string& str)
    {
        if (!str.empty())
            return all_of(str.begin(), str.end(), isalnum);
        return false;
    }

    bool isStringInt(const std::string& str)
    {
        if (!str.empty())
        {
            if (str.substr(0, 1) == "-")
            {
                std::string withoutSign = str.substr(1);
                return all_of(withoutSign.begin(), withoutSign.end(), isdigit);
            }
            return all_of(str.begin(), str.end(), isdigit);
        }
        return false;
    }

    bool isStringFloat(const std::string& str)
    {
        std::string modifyStr = str;
        bool isFloat = false;
        if (!modifyStr.empty())
        {
            if (modifyStr.substr(0, 1) == "-")
                modifyStr = modifyStr.substr(1);
            if (occurencesInString(modifyStr, ".") == 1)
            {
                isFloat = true;
                replaceInPlace(modifyStr, ".", "");
            }
            return (all_of(modifyStr.begin(), modifyStr.end(), isdigit) && isFloat);
        }
        return false;
    }

    bool isStringNumeric(const std::string& str)
    {
        return (isStringFloat(str) || isStringInt(str));
    }

    void replaceInPlace(std::string& subject, const std::string& search, const std::string& replace)
    {
        size_t pos = 0;
        while ((pos = subject.find(search, pos)) != std::string::npos)
        {
            subject.replace(pos, search.length(), replace);
            pos += replace.length();
        }
    }

    std::string replace(std::string subject, const std::string& search, const std::string& replace)
    {
        size_t pos = 0;
        while ((pos = subject.find(search, pos)) != std::string::npos)
        {
            subject.replace(pos, search.length(), replace);
            pos += replace.length();
        }
        return subject;
    }

    bool isSurroundedBy(const std::string& string, const std::string& bet)
    {
        return (string.substr(0, bet.size()) == bet
            && string.substr(string.size() - bet.size(), bet.size()) == bet);
    }

    std::string getRandomKey(const std::string& set, const int len)
    {
        std::string r;
        for (int i = 0; i < len; i++)
            r.push_back(set.at(size_t(Math::randint(0, 100000) % set.size())));
        return r;
    }

    bool contains(const std::string& string, const std::string& search)
    {
        return (string.find(search) != std::string::npos);
    }

    bool startsWith(const std::string& string, const std::string& search)
    {
        if (string.size() < search.size())
            return false;
        return (std::mismatch(search.begin(), search.end(), string.begin()).first == search.end());
    }

    bool endsWith(const std::string& string, const std::string& search)
    {
        if (string.size() < search.size())
        {
            return false;
        }
        return (
            std::mismatch(search.rbegin(), search.rend(), string.rbegin()).first == search.rend());
    }
} // namespace obe::Utils::String