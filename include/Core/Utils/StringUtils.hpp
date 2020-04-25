#pragma once

#include <string>
#include <vector>

/**
 * \brief Functions to work with Strings
 */
namespace obe::Utils::String
{
    /**
     * \brief A string containing all the letters of the Alphabet
     */
    const std::string Alphabet = "abcdefghijklmnopqrstuvwxyz";
    /**
     * \brief A string containing all the numbers from 0 to 9
     */
    const std::string Numbers = "0123456789";

    /**
     * \brief Splits a std::string using a delimited
     * \param str String you want to split
     * \param delimiters Delimiter used to split the string
     * \return The split string in a std::vector of std::string
     */
    std::vector<std::string> split(
        const std::string& str, const std::string& delimiters = " ");
    /**
     * \brief Count of the occurences of occur in string str
     * \param str String you want to count the occurences in
     * \param occur String you want to search
     * \return The amount of times the occurence of occur has been found in the
     *         string str
     */
    int occurencesInString(const std::string& str, const std::string& occur);
    /**
     * \brief Get if the string only contains letters
     * \param str String you want to check
     * \return true if the string only contains letters, false otherwise
     */
    bool isStringAlpha(const std::string& str);
    /**
     * \brief Get if the string only contains letters and numbers
     * \param str String you want to check
     * \return true if the string only contains letters and numbers, false
     *         otherwise
     */
    bool isStringAlphaNumeric(const std::string& str);
    /**
     * \brief Get if the string is a number
     * \param str String you want to check
     * \return true if the string only is a number, false otherwise
     */
    bool isStringNumeric(const std::string& str);
    /**
     * \brief Get if the string is an integer
     * \param str String you want to check
     * \return true if the string is an integer, false otherwise
     */
    bool isStringInt(const std::string& str);
    /**
     * \brief Get if the string is a float
     * \param str String you want to check
     * \return true if the string is a float, false otherwise
     */
    bool isStringFloat(const std::string& str);
    /**
     * \nobind
     * \brief Replace all the occurences of search to replace in the string
     *        subject in place
     * \param subject The reference of the string you want to modify
     * \param search The string to replace
     * \param replace The content that will replace search occurences
     */
    void replaceInPlace(
        std::string& subject, const std::string& search, const std::string& replace);
    /**
     * \brief Replace all the occurences of search to replace in the string
     *        subject
     * \param subject The string you want to modify
     * \param search The string to replace
     * \param replace The content that will replace search occurences
     * \return A std::string containing the modified string
     */
    std::string replace(
        std::string subject, const std::string& search, const std::string& replace);
    /**
     * \brief Check if the string is surrounded by the given string
     * \param string String you want to check
     * \param bet String you want to check if it surrounds the first string
     * \return true if bet surrounds the string, false otherwise
     */
    bool isSurroundedBy(const std::string& string, const std::string& bet);
    /**
     * \brief Generates a random string witch characters from the given set
     * \param set Set of characters to use for the generation
     * \param len Length of the string you want to generate
     * \return The generated string
     */
    std::string getRandomKey(const std::string& set, int len);
    /**
     * \brief Check if a string contains another one
     * \param string The string to check
     * \param search The content to search in the first string
     * \return true if the string contains search, false otherwise
     */
    bool contains(const std::string& string, const std::string& search);
    /**
     * \brief Checks if "string" starts with "search"
     * \param string String where to search the prefix
     * \param search Prefix to check
     * \return true if search is a prefix of string, false otherwise
     */
    bool startsWith(const std::string& string, const std::string& search);
    /**
     * \brief Checks if "string" ends with "search"
     * \param string String where to search the suffix
     * \param search Suffix to check
     * \return true if search is a suffix of string, false otherwise
     */
    bool endsWith(const std::string& string, const std::string& search);

    std::size_t distance(std::string_view source, std::string_view target);

    std::vector<std::string> sortByDistance(const std::string& source,
        const std::vector<std::string>& words, std::size_t limit = 0);

    std::string quote(const std::string& source);
} // namespace obe::Utils::String