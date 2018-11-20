#include <fstream>

#include <vili/Types.hpp>
#include <vili/ViliParser.hpp>

#include <Bindings/Bindings.hpp>
#include <Bindings/ViliBindings.hpp>
#include <Utils/VectorUtils.hpp>

#include <kaguya/kaguya.hpp>

namespace obe::Bindings::ViliBindings
{
    void LoadViliDataType(kaguya::State* lua)
    {
        (*lua)["Vili"]["DataType"] = kaguya::NewTable();
        (*lua)["Vili"]["DataType"]["String"] = vili::DataType::String;
        (*lua)["Vili"]["DataType"]["Int"] = vili::DataType::Int;
        (*lua)["Vili"]["DataType"]["Float"] = vili::DataType::Float;
        (*lua)["Vili"]["DataType"]["Bool"] = vili::DataType::Bool;
        (*lua)["Vili"]["DataType"]["Range"] = vili::DataType::Range;
        (*lua)["Vili"]["DataType"]["Link"] = vili::DataType::Link;
        (*lua)["Vili"]["DataType"]["Template"] = vili::DataType::Template;
        (*lua)["Vili"]["DataType"]["Unknown"] = vili::DataType::Unknown;
    }

    void LoadViliNodeType(kaguya::State* lua)
    {
        (*lua)["Vili"]["NodeType"] = kaguya::NewTable();
        (*lua)["Vili"]["NodeType"]["Node"] = vili::NodeType::Node;
        (*lua)["Vili"]["NodeType"]["ContainerNode"] = vili::NodeType::ContainerNode;
        (*lua)["Vili"]["NodeType"]["DataNode"] = vili::NodeType::DataNode;
        (*lua)["Vili"]["NodeType"]["ArrayNode"] = vili::NodeType::ArrayNode;
        (*lua)["Vili"]["NodeType"]["ComplexNode"] = vili::NodeType::ComplexNode;
        (*lua)["Vili"]["NodeType"]["LinkNode"] = vili::NodeType::LinkNode;
    }

    void LoadViliNode(kaguya::State* lua)
    {
        (*lua)["Vili"]["Node"].setClass(kaguya::UserdataMetatable<vili::Node>()
            .addFunction("copy", &vili::Node::copy)
            .addFunction("getAnnotation", &vili::Node::getAnnotation)
            .addFunction("getDepth", &vili::Node::getDepth)
            .addFunction("getId", &vili::Node::getId)
            .addFunction("getNodePath", &vili::Node::getNodePath)
            .addFunction("getType", &vili::Node::getType)
            .addFunction("isVisible", &vili::Node::isVisible)
            .addFunction("setAnnotation", &vili::Node::setAnnotation)
            .addFunction("setId", &vili::Node::setId)
            .addFunction("setParent", &vili::Node::setParent)
            .addFunction("setVisible", &vili::Node::setVisible)
            .addFunction("write", &vili::Node::write)
        );
    }

    void LoadViliContainerNode(kaguya::State* lua)
    {
        Load(lua, "Vili.Node");
        (*lua)["Vili"]["ContainerNode"].setClass(kaguya::UserdataMetatable<vili::ContainerNode, vili::Node>()
            .addFunction("copy", &vili::ContainerNode::copy)
            .addFunction("extractElement", &vili::ContainerNode::extractElement)
            .addFunction("removeOwnership", &vili::ContainerNode::removeOwnership)
            .addFunction("write", &vili::ContainerNode::write)
        );
    }

    void LoadViliDataNode(kaguya::State* lua)
    {
        Load(lua, "Vili.Node");
        (*lua)["Vili"]["DataNode"].setClass(kaguya::UserdataMetatable<vili::DataNode, vili::Node>()
            .addFunction("autoset", &vili::DataNode::autoset)
            .addFunction("copy", &vili::DataNode::copy)
            .addFunction("dumpData", &vili::DataNode::dumpData)
            .addFunction("getInt", &vili::DataNode::get<int>)
            .addFunction("getFloat", &vili::DataNode::get<double>)
            .addFunction("getBool", &vili::DataNode::get<bool>)
            .addFunction("getString", &vili::DataNode::get<std::string>)
            .addFunction("getDataType", &vili::DataNode::getDataType)
            .addOverloadedFunctions("set", 
                static_cast<void (vili::DataNode::*)(bool)>(&vili::DataNode::set),
                static_cast<void (vili::DataNode::*)(double)>(&vili::DataNode::set),
                static_cast<void (vili::DataNode::*)(const std::string&)>(&vili::DataNode::set),
                static_cast<void (vili::DataNode::*)(int)>(&vili::DataNode::set)
            )
            .addFunction("write", &vili::DataNode::write)
        );
    }

    void LoadViliLinkNode(kaguya::State* lua)
    {
        Load(lua, "Vili.Node");
        (*lua)["Vili"]["LinkNode"].setClass(kaguya::UserdataMetatable<vili::LinkNode, vili::Node>()
            .addFunction("apply", &vili::LinkNode::apply)
            .addFunction("copy", &vili::LinkNode::copy)
            .addFunction("equals", &vili::LinkNode::operator==)
            .addFunction("getFullPath", &vili::LinkNode::getFullPath)
            .addFunction("getPath", &vili::LinkNode::getPath)
            .addFunction("getTarget", &vili::LinkNode::getTarget)
            .addFunction("write", &vili::LinkNode::write)
        );
    }

    void LoadViliArrayNode(kaguya::State* lua)
    {
        Load(lua, "Vili.ContainerNode");
        (*lua)["Vili"]["ArrayNode"].setClass(kaguya::UserdataMetatable<vili::ArrayNode, vili::ContainerNode>()
            .addFunction("clear", &vili::ArrayNode::clear)
            .addFunction("copy", &vili::ArrayNode::copy)
            .addFunction("erase", &vili::ArrayNode::erase)
            .addFunction("extractElement", &vili::ArrayNode::extractElement)
            .addOverloadedFunctions("insert",
                static_cast<void (vili::ArrayNode::*)(unsigned int, const std::string&)>(&vili::ArrayNode::insert),
                static_cast<void (vili::ArrayNode::*)(unsigned int, int)>(&vili::ArrayNode::insert),
                static_cast<void (vili::ArrayNode::*)(unsigned int, bool)>(&vili::ArrayNode::insert),
                static_cast<void (vili::ArrayNode::*)(unsigned int, double)>(&vili::ArrayNode::insert)
            )
            .addOverloadedFunctions("push",
                static_cast<void (vili::ArrayNode::*)(const std::string&)>(&vili::ArrayNode::push),
                static_cast<void (vili::ArrayNode::*)(int)>(&vili::ArrayNode::push),
                static_cast<void (vili::ArrayNode::*)(bool)>(&vili::ArrayNode::push),
                static_cast<void (vili::ArrayNode::*)(double)>(&vili::ArrayNode::push)
            )
            .addFunction("size", &vili::ArrayNode::size)
            .addFunction("write", &vili::ArrayNode::write)
        );

        (*lua)["Vili"]["ArrayNode"]["get"] = kaguya::function(
            [](vili::ArrayNode& attribute, unsigned int index)
        {
            return &attribute.get(index);
        });
    }

    void LoadViliComplexNode(kaguya::State* lua)
    {
        Load(lua, "Vili.ContainerNode");
        (*lua)["Vili"]["ComplexNode"].setClass(kaguya::UserdataMetatable<vili::ComplexNode, vili::ContainerNode>()
            .addOverloadedFunctions("contains",
                static_cast<bool (vili::ComplexNode::*)(const std::string&) const>(&vili::ComplexNode::contains),
                static_cast<bool (vili::ComplexNode::*)(vili::NodeType, const std::string&) const>(&vili::ComplexNode::contains)
            )
            .addFunction("copy", &vili::ComplexNode::copy)
            .addFunction("extractElement", &vili::ComplexNode::extractElement)
            .addFunction("get", &vili::ComplexNode::get)
            .addFunction("getAll", static_cast<std::vector<vili::Node*> (vili::ComplexNode::*)(vili::NodeType) const>(&vili::ComplexNode::getAll))
            .addFunction("getCurrentTemplate", &vili::ComplexNode::getCurrentTemplate)
            .addFunction("getNodeType", &vili::ComplexNode::getNodeType)
            .addFunction("heritage", &vili::ComplexNode::heritage)
            .addFunction("remove", &vili::ComplexNode::remove)
            .addFunction("useTemplate", &vili::ComplexNode::useTemplate)
            .addFunction("walk", static_cast<void (vili::ComplexNode::*)(std::function<void(vili::NodeIterator&)>, bool)>(&vili::ComplexNode::walk))
            .addFunction("write", &vili::ComplexNode::write)
        );

        (*lua)["Vili"]["ComplexNode"]["at"] = kaguya::function(
            [](vili::ComplexNode& attribute, kaguya::VariadicArgType args)
        {
            std::vector<std::string> fullPath;
            for (auto arg : args)
            {
                fullPath.push_back(arg.get<std::string>());
            }
            std::string stringPath = Utils::Vector::join(fullPath, "/");
            return &attribute.at(stringPath);
        });

        (*lua)["Vili"]["ComplexNode"]["getDataNode"] = kaguya::function(
            [](vili::ComplexNode& attribute, const std::string& id)
        {
            return &attribute.getDataNode(id);
        });

        (*lua)["Vili"]["ComplexNode"]["getComplexNode"] = kaguya::function(
            [](vili::ComplexNode& attribute, const std::string& id)
        {
            return &attribute.getComplexNode(id);
        });

        (*lua)["Vili"]["ComplexNode"]["getLinkNode"] = kaguya::function(
            [](vili::ComplexNode& attribute, const std::string& id)
        {
            return &attribute.getLinkNode(id);
        });

        (*lua)["Vili"]["ComplexNode"]["getArrayNode"] = kaguya::function(
            [](vili::ComplexNode& attribute, const std::string& id)
        {
            return &attribute.getArrayNode(id);
        });

        (*lua)["Vili"]["ComplexNode"]["createDataNode"] = kaguya::overload(
            [](vili::ComplexNode& attribute, const std::string& id, const std::string& stringValue)
        {
            return &attribute.createDataNode(id, stringValue);
        },
            [](vili::ComplexNode& attribute, const std::string& id, double floatValue)
        {
            return &attribute.createDataNode(id, floatValue);
        },
            [](vili::ComplexNode& attribute, const std::string& id, bool boolValue)
        {
            return &attribute.createDataNode(id, boolValue);
        },
            [](vili::ComplexNode& attribute, const std::string& id, int intValue)
        {
            return &attribute.createDataNode(id, intValue);
        },
            [](vili::ComplexNode& attribute, const std::string& id, vili::DataType type, const std::string& data)
        {
            return &attribute.createDataNode(id, type, data);
        }
        );

        (*lua)["Vili"]["ComplexNode"]["createArrayNode"] = kaguya::function(
            [](vili::ComplexNode& attribute, const std::string& id)
        {
            return &attribute.createArrayNode(id);
        });

        (*lua)["Vili"]["ComplexNode"]["createComplexNode"] = kaguya::function(
            [](vili::ComplexNode& attribute, const std::string& id)
        {
            return &attribute.createComplexNode(id);
        }
        );

        (*lua)["Vili"]["ComplexNode"]["createLinkNode"] = kaguya::function(
            [](vili::ComplexNode& attribute, const std::string& id, const std::string& path)
        {
            return &attribute.createLinkNode(id, path);
        }
        );

        (*lua)["Vili"]["ComplexNode"]["pushDataNode"] = kaguya::function(
            [](vili::ComplexNode& attribute, vili::DataNode* node)
        {
            return &attribute.pushDataNode(node);
        }
        );

        (*lua)["Vili"]["ComplexNode"]["pushArrayNode"] = kaguya::function(
            [](vili::ComplexNode& attribute, vili::ArrayNode* node)
        {
            return &attribute.pushArrayNode(node);
        }
        );

        (*lua)["Vili"]["ComplexNode"]["pushComplexNode"] = kaguya::function(
            [](vili::ComplexNode& attribute, vili::ComplexNode* node)
        {
            return &attribute.pushComplexNode(node);
        }
        );

        (*lua)["Vili"]["ComplexNode"]["pushLinkNode"] = kaguya::function(
            [](vili::ComplexNode& attribute, vili::LinkNode* node)
        {
            return &attribute.pushLinkNode(node);
        }
        );
    }

    KAGUYA_MEMBER_FUNCTION_OVERLOADS(ViliParser_parseFile_wrapper, vili::ViliParser, parseFile, 1, 3);
    KAGUYA_MEMBER_FUNCTION_OVERLOADS(ViliParser_includeFile_wrapper, vili::ViliParser, includeFile, 1, 2);
    void LoadViliViliParser(kaguya::State* lua)
    {
        (*lua)["Vili"]["ViliParser"].setClass(kaguya::UserdataMetatable<vili::ViliParser>()
            .setConstructors<vili::ViliParser(), vili::ViliParser(const std::string&)>()
            .addFunction("addFlag", &vili::ViliParser::addFlag)
            .addFunction("generateTemplate", &vili::ViliParser::generateTemplate)
            .addFunction("getAllFlags", &vili::ViliParser::getAllFlags)
            .addFunction("getIncludes", &vili::ViliParser::getIncludes)
            .addFunction("getSpacing", &vili::ViliParser::getSpacing)
            .addFunction("getTemplate", &vili::ViliParser::getTemplate)
            .addFunction("hasFlag", &vili::ViliParser::hasFlag)
            .addFunction("includeFile", ViliParser_includeFile_wrapper())
            .addFunction("parseFile", ViliParser_parseFile_wrapper())
            .addFunction("root", &vili::ViliParser::operator->)
            .addFunction("setSpacing", &vili::ViliParser::setSpacing)
            .addFunction("writeFile", &vili::ViliParser::writeFile)
        );
    }

    void LoadViliNodeIterator(kaguya::State* lua)
    {
        (*lua)["Vili"]["NodeIterator"].setClass(kaguya::UserdataMetatable<vili::NodeIterator>()
            .addFunction("first", &vili::NodeIterator::first)
            .addFunction("get", &vili::NodeIterator::get)
            .addFunction("hasCache", &vili::NodeIterator::hasCache)
            .addFunction("index", &vili::NodeIterator::index)
            .addFunction("last", &vili::NodeIterator::last)
            .addFunction("node", &vili::NodeIterator::operator->)
            .addFunction("over", &vili::NodeIterator::over)
            .addFunction("size", &vili::NodeIterator::size)
            .addFunction("terminate", &vili::NodeIterator::terminate)
        );
    }

    void LoadViliNodeTemplate(kaguya::State* lua)
    {
        (*lua)["Vili"]["NodeTemplate"].setClass(kaguya::UserdataMetatable<vili::NodeTemplate>()
            .addFunction("addConstraintManager", &vili::NodeTemplate::addConstraintManager)
            .addFunction("build", &vili::NodeTemplate::build)
            .addFunction("getArgumentCount", &vili::NodeTemplate::getArgumentCount)
            .addFunction("getBody", &vili::NodeTemplate::getBody)
            .addFunction("getName", &vili::NodeTemplate::getName)
            .addFunction("isVisible", &vili::NodeTemplate::isVisible)
            .addFunction("setVisible", &vili::NodeTemplate::setVisible)
            .addFunction("useDefaultLinkRoot", &vili::NodeTemplate::useDefaultLinkRoot)
        );
    }

    void LoadViliNodeConstraintManager(kaguya::State* lua)
    {
        (*lua)["Vili"]["NodeConstraintManager"].setClass(kaguya::UserdataMetatable<vili::NodeConstraintManager>()
            .addFunction("addConstraint", &vili::NodeConstraintManager::addConstraint)
            .addFunction("checkAllConstraints", &vili::NodeConstraintManager::checkAllConstraints)
            .addFunction("getArgumentPath", &vili::NodeConstraintManager::getArgumentPath)
            .addFunction("getLinkNode", &vili::NodeConstraintManager::getLinkNode)
        );
    }

    void LoadViliErrorHandler(kaguya::State* lua)
    {
    }
}