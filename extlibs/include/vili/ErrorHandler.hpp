#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <exception>

namespace aube
{
    class ErrorMessage
    {
    private:
        std::string m_file;
        std::vector<std::string> m_location;
        std::string m_message;
        std::vector<std::string> m_hints;
    public:
        ErrorMessage(std::string file, std::vector<std::string> location, std::string message, std::vector<std::string> hints = {});
        std::string getFile() const;
        std::string getLocation();
        std::string getMessage() const;
        std::vector<std::string> getHints() const;
    };

    class ErrorHandler
    {
    private:
        static std::map<std::string, ErrorMessage*> m_errors;
    public:
        static void Load(const std::string& errorId, const std::string& filename, const std::vector<std::string>& location, const std::string& message, const std::vector<std::string>& hints = {});
        static std::runtime_error Raise(const std::string& errorId, const std::map<std::string, std::string>& parameters = {});
    };
}
