//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "Vili.hpp"

namespace vili
{
    void LoadErrors(const std::string& errorFile)
    {
        ViliParser errors(errorFile);

        errors->walk([](NodeIterator& node) -> void
        {
            if (node->contains(NodeType::DataNode, "message"))
            {
                std::vector<std::string> location;
                std::vector<std::string> errorIdParts;
                std::string message = node->getDataNode("message").get<std::string>();
                ComplexNode* currentParent = node.get();
                while (currentParent != nullptr)
                {
                    if (currentParent->contains(NodeType::DataNode, "where"))
                        location.insert(location.begin(), currentParent->getDataNode("where").get<std::string>());
                    errorIdParts.push_back(currentParent->getId());
                    if (currentParent->getParent() != nullptr)
                        currentParent = static_cast<ComplexNode*>(currentParent->getParent());
                    else
                        currentParent = nullptr;
                }
                errorIdParts.pop_back();
                reverse(errorIdParts.begin(), errorIdParts.end());
                std::string errorId = Functions::Vector::join(errorIdParts, ".");
                aube::ErrorHandler::Load(errorId, location, message);
            }
        });
    }
}
