#pragma once

#include <string>

/**
 * \brief Some Classes and Functions to manipulate Engine Execution
 * @Bind
 */
namespace obe::Utils::Exec
{
    /**
     * \brief Parses the execution arguments
     * @Bind
     */
    class RunArgsParser
    {
    private:
        char** start;
        int size;

    public:
        /**
         * \brief Constructor of RunArgsParser takes argc and argv in parameters
         * \param size This is argc
         * \param start This is argv
         */
        RunArgsParser(int size, char** start);
        /**
         * \brief Check if a argument has been entered
         * \param arg Name of the argument you want to check existence
         * \return true if the argument exists, false otherwise
         */
        bool argumentExists(const std::string& arg) const;
        /**
         * \brief Get the given argument's value
         * \param arg Name of the argument you want to retrieve the value
         * \return The value of the argument
         */
        std::string getArgumentValue(const std::string& arg) const;
    };
} // namespace obe::Utils::Exec