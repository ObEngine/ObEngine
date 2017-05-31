//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "Vili.hpp"

namespace vili
{
    void LoadErrors(const std::string& errorFile)
    {
        DataParser errors(errorFile);

        errors->walk([](NodeIterator& node) -> void
        {
            if (node->contains(Types::BaseAttribute, "message"))
            {
                std::vector<std::string> location;
                std::vector<std::string> errorIdParts;
                std::string filename = "";
                std::string message = node->getBaseAttribute("message").get<std::string>();
                ComplexAttribute* currentParent = node.get();
                while (currentParent != nullptr)
                {
                    if (currentParent->contains(Types::BaseAttribute, "where"))
                        location.insert(location.begin(), currentParent->getBaseAttribute("where").get<std::string>());
                    if (currentParent->contains(Types::BaseAttribute, "file") && filename.empty())
                        filename = currentParent->getBaseAttribute("file").get<std::string>();
                    errorIdParts.push_back(currentParent->getID());
                    if (currentParent->getParent() != nullptr)
                        currentParent = static_cast<ComplexAttribute*>(currentParent->getParent());
                    else
                        currentParent = nullptr;
                }
                errorIdParts.pop_back();
                reverse(errorIdParts.begin(), errorIdParts.end());
                std::string errorId = Functions::Vector::join(errorIdParts, ".");
                aube::ErrorHandler::Load(errorId, filename, location, message);
            }
        });
    }
}
