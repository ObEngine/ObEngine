#include <ErrorHandler.hpp>
#include <Functions.hpp>
#include <ViliParser.hpp>

namespace aube
{
    ErrorMessage::ErrorMessage(const std::vector<std::string>& location,
        const std::string& message, const std::vector<std::string>& hints)
    {
        m_location = location;
        m_message = message;
        m_hints = hints;
    }

    std::string ErrorMessage::getLocation()
    {
        std::string stringLocation = m_location[0];
        for (int i = 1; i < m_location.size(); i++)
        {
            stringLocation += "::" + m_location[i];
        }
        return stringLocation;
    }

    std::string ErrorMessage::getMessage() const
    {
        return m_message;
    }

    std::vector<std::string> ErrorMessage::getHints() const
    {
        return m_hints;
    }

    std::map<std::string, ErrorMessage*> ErrorHandler::m_errors
        = std::map<std::string, ErrorMessage*>();

    void ErrorHandler::Load(const std::string& errorId,
        const std::vector<std::string>& location, const std::string& message,
        const std::vector<std::string>& hints)
    {
        m_errors[errorId] = new ErrorMessage(location, message, hints);
    }

    std::runtime_error ErrorHandler::Raise(
        const std::string& errorId, const std::map<std::string, std::string>& parameters)
    {
        std::cerr << "Raised Exception : " << errorId
                  << " with parameters : " << std::endl;
        for (const std::pair<std::string, std::string>& parameter : parameters)
        {
            std::cerr << "    > " << parameter.first << " = " << parameter.second
                      << std::endl;
        }
        std::cerr << std::flush;
        return std::runtime_error(errorId.c_str());
    }

    void ErrorHandler::Warn(
        const std::string& errorId, const std::map<std::string, std::string>& parameters)
    {
        if (m_errors.find(errorId) != m_errors.end())
        {
            ErrorMessage* currentError = m_errors[errorId];
            std::string errorMessage = "<<Warning>>[" + errorId + "]";
            errorMessage
                += "@" + currentError->getLocation() + " : " + currentError->getMessage();
            for (std::pair<std::string, std::string> parameter : parameters)
            {
                errorMessage
                    = errorMessage.replace(errorMessage.find("%" + parameter.first + "%"),
                        parameter.first.size() + 2, parameter.second);
            }
            std::cerr << errorMessage << std::endl;
            for (std::string& hint : currentError->getHints())
            {
                std::cerr << "    > " << hint << std::endl;
            }
        }
        std::cerr << "Raised Unknown Warning : " << errorId
                  << " with parameters : " << std::endl;
        for (std::pair<std::string, std::string> parameter : parameters)
        {
            std::cerr << "    > " << parameter.first << " = " << parameter.second
                      << std::endl;
        }
    }

    void LoadErrors(const std::string& errorFile)
    {
        vili::ViliParser errors(errorFile);

        errors->walk([](vili::NodeIterator& node) -> void {
            if (node->contains(vili::NodeType::DataNode, "message"))
            {
                std::vector<std::string> location;
                std::vector<std::string> errorIdParts;
                std::string message = node->getDataNode("message").get<std::string>();
                vili::ComplexNode* currentParent = node.get();
                while (currentParent != nullptr)
                {
                    if (currentParent->contains(vili::NodeType::DataNode, "where"))
                        location.insert(location.begin(),
                            currentParent->getDataNode("where").get<std::string>());
                    errorIdParts.push_back(currentParent->getId());
                    if (currentParent->getParent() != nullptr)
                        currentParent
                            = static_cast<vili::ComplexNode*>(currentParent->getParent());
                    else
                        currentParent = nullptr;
                }
                errorIdParts.pop_back();
                std::reverse(errorIdParts.begin(), errorIdParts.end());
                std::string errorId = vili::Functions::Vector::join(errorIdParts, ".");
                aube::ErrorHandler::Load(errorId, location, message);
            }
        });
    }
}
