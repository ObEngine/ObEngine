#include <fstream>

#include "vili/ViliParser.hpp"
#include "Functions.hpp"

namespace
{
    std::istream& safeGetline(std::istream& is, std::string& t)
    {
        t.clear();

        std::streambuf* sb = is.rdbuf();

        for (;;)
        {
            int c = sb->sbumpc();
            switch (c)
            {
            case '\n':
                return is;
            case '\r':
                if (sb->sgetc() == '\n')
                    sb->sbumpc();
                return is;
            case EOF:
                if (t.empty())
                    is.setstate(std::ios::eofbit);
                return is;
            default:
                t += static_cast<char>(c);
            }
        }
    }

    std::string Path()
    {
        return "";
    }

    std::string Path(std::string cPath)
    {
        if (cPath.size() > 0 && vili::Functions::String::extract(cPath, cPath.size() - 1, 0) == "/")
            cPath = vili::Functions::String::extract(cPath, 0, 1);
        return cPath;
    }

    std::string Path(const std::vector<std::string>& path)
    {
        std::string strPath = "";
        for (unsigned int i = 0; i < path.size(); i++)
        {
            strPath += path[i];
            if (i != path.size() - 1)
                strPath += "/";
        }
        return strPath;
    }
}

namespace vili
{
    std::map<std::string, std::unique_ptr<ViliParser>> ViliParser::ViliCache;
    ViliParser::ViliParser()
    {
        m_root = std::make_unique<ComplexNode>("root");
        m_root->setAnnotation("NoFile");
    }

    ViliParser::ViliParser(const std::string& file)
    {
        m_root = std::make_unique<ComplexNode>("root");
        m_root->setAnnotation("NoFile");
        parseFile(file);
    }

    ComplexNode* ViliParser::operator->() const
    {
        return m_root.get();
    }

    ComplexNode& ViliParser::root() const
    {
        return *m_root.get();
    }

    void ViliParser::addFlag(const std::string& flag)
    {
        m_flagList.push_back(flag);
    }

    bool ViliParser::hasFlag(const std::string& flagName) const
    {
        return find(m_flagList.begin(), m_flagList.end(), flagName) != m_flagList.end();
    }

    std::vector<std::string> ViliParser::getAllFlags() const
    {
        return m_flagList;
    }

    ComplexNode& ViliParser::getPath(std::string path) const
    {
        if (path.size() > 0 && Functions::String::extract(path, path.size() - 1, 0) == "/")
            path = Functions::String::extract(path, 0, 1);
        if (Functions::String::occurencesInString(path, "/") > 0)
        {
            std::vector<std::string> splittedPath = Functions::String::split(path, "/");
            std::string subPath = Functions::Vector::join(splittedPath, "/", 1);
            return getPath(Functions::String::split(path, "/")[0]).at(subPath);
        }
        return getRootChild(path);
    }

    ComplexNode& ViliParser::getRootChild(std::string child) const
    {
        if (child.empty())
            return *m_root.get();
        return m_root->getComplexNode(child);
    }

    ComplexNode& ViliParser::operator[](const std::string& cPath) const
    {
        return getPath(cPath);
    }

    ComplexNode& ViliParser::at(const std::string& cPath) const
    {
        std::string path = cPath;
        if (cPath.size() > 0 && Functions::String::extract(cPath, cPath.size() - 1, 0) == "/")
            path = Functions::String::extract(cPath, 0, 1);
        return getPath(path);
    }

    bool ViliParser::parseFile(const std::string& filename, bool verbose, bool visible)
    {
        m_root->setAnnotation(filename);

        if (CheckCache(this, filename, visible))
            return true;

        std::string currentLine;
        std::vector<std::string> addPath = {};
        std::string curList = "None";
        int curListIndent = 0;
        bool inList = false;
        std::ifstream useFile;
        useFile.open(filename);

        if (useFile.is_open())
        {
            if (verbose) std::cout << "Start Parsing File : " << filename << std::endl;
            std::istream& lineGetter = safeGetline(useFile, currentLine);
            while (!lineGetter.eof() && !lineGetter.fail())
            {
                Functions::String::StringExtractor stringsInLine = Functions::String::extractAllStrings(currentLine);
                std::string rawLine = Functions::Vector::join(std::get<1>(stringsInLine), "");
                Functions::String::replaceStringInPlace(rawLine, "	", std::string(m_spacing, ' '));
                unsigned int currentIndent = 0;
                unsigned int spacingAmount = 0;
                for (int i = 0; i < rawLine.size(); i++)
                {
                    if (rawLine[i] == ' ')
                    {
                        spacingAmount += 1;
                        if (spacingAmount == m_spacing)
                        {
                            spacingAmount = 0;
                            currentIndent += 1;
                        }
                    }
                    else
                        break;
                }
                Functions::String::replaceStringInPlace(rawLine, std::string(m_spacing, ' '), "");
                std::vector<std::string> parsedLines;
                std::string addParsedLine = "";
                for (int i = 0; i < std::get<2>(stringsInLine).size(); i++)
                {
                    if (std::get<2>(stringsInLine)[i].first == 0)
                        addParsedLine += "\"" + std::get<0>(stringsInLine)[std::get<2>(stringsInLine)[i].second] + "\"";
                    else
                    {
                        std::string removeRawSpacing = Functions::String::replaceString(std::get<1>(stringsInLine)[std::get<2>(stringsInLine)[i].second], "	", "");
                        Functions::String::replaceStringInPlace(removeRawSpacing, "	", ""); //Tabs
                        Functions::String::replaceStringInPlace(removeRawSpacing, " ", ""); //Spaces
                        for (int j = 0; j < removeRawSpacing.size(); j++)
                        {
                            std::string currentRawChar = removeRawSpacing.substr(j, 1);
                            if (currentRawChar == "," && inList)
                            {
                                parsedLines.push_back(addParsedLine);
                                addParsedLine.clear();
                            }
                            else if (currentRawChar == "[")
                            {
                                parsedLines.push_back(addParsedLine + "[");
                                addParsedLine.clear();
                                inList = true;
                            }
                            else if (currentRawChar == "]")
                            {
                                parsedLines.push_back(addParsedLine);
                                parsedLines.push_back("]");
                                addParsedLine.clear();
                                inList = false;
                            }
                            else
                                addParsedLine += currentRawChar;
                        }
                    }
                }
                parsedLines.push_back(addParsedLine);
                for (const std::string& parsedLine : parsedLines)
                {
                    while (!parsedLine.empty() && currentIndent < addPath.size() && addPath.size() > 0)
                    {
                        if (this->checkQuickLookMatches(getPath(Path(addPath)).getRawNodePath()))
                            return true;
                        addPath.pop_back();
                    }
                        
                    std::function<std::string()> indenter = [curList, currentIndent, curListIndent]()
                    {
                        std::string strIndent = "";
                        if (curList == "None")
                        {
                            for (unsigned int p = 0; p <= currentIndent; p++)
                                strIndent += "    ";
                        }
                        else
                        {
                            for (unsigned int p = 0; p <= curListIndent + 1; p++)
                                strIndent += "    ";
                        }
                        return strIndent;
                    };
                    if (curList != "None" && parsedLine == "]")
                    {
                        if (this->checkQuickLookMatches(getPath(Path(addPath)).getArrayNode(curList).getRawNodePath()))
                            return true;
                        curList = "None";
                    }
                    if (!parsedLine.empty() && currentIndent == 0)
                    {
                        if (parsedLine.substr(parsedLine.size() - 1, 1) == ";")
                        {
                            std::string instructionType = Functions::String::split(parsedLine, "(")[0];
                            std::string instructionValue = Functions::String::split(parsedLine, "(")[1];
                            instructionValue = Functions::String::split(instructionValue, ")")[0];
                            if (instructionType == "Flag")
                            {
                                m_flagList.push_back(instructionValue);
                                if (verbose) std::cout << indenter() << "Define New Flag : " << instructionValue << std::endl;
                            }
                            else if (instructionType == "Spacing")
                            {
                                m_spacing = stoi(instructionValue);
                                if (verbose) std::cout << indenter() << "Define New Spacing : " << m_spacing << std::endl;
                            }
                            else if (instructionType == "Include")
                            {
                                if (verbose) std::cout << indenter() << "Include New File : " << instructionValue << std::endl;
                                this->includeFile(instructionValue);
                                m_root->setAnnotation(filename);
                            }
                            else if (instructionType == "Template")
                            {
                                if (verbose) std::cout << indenter() << "Creating New Template from : " << instructionValue << std::endl;
                                this->generateTemplate(instructionValue, visible);
                            }
                        }
                    }
                    if (!parsedLine.empty())
                    {
                        std::vector<std::string> symbolExclusion = {"\"", "#"};

                        std::string pushIndicator = getPath(Path(addPath)).getNodePath();

                        if (!Functions::Vector::isInList(parsedLine.substr(0, 1), symbolExclusion) && Functions::String::occurencesInString(parsedLine, ":[") == 1)
                        {
                            std::string listElementID = Functions::String::split(parsedLine, ":")[0];
                            getPath(Path(addPath)).createArrayNode(listElementID);
                            getPath(Path(addPath)).getArrayNode(listElementID).setVisible(visible);
                            curList = listElementID;
                            curListIndent = currentIndent;
                            if (verbose)
                            {
                                std::cout << indenter() << "Create ListAttribute " << curList << " inside " << pushIndicator << std::endl;
                            }
                        }
                        else if (parsedLine.substr(parsedLine.size() - 1, 1) == ":")
                        {
                            std::string complexElementID = parsedLine.substr(0, parsedLine.size() - 1);
                            std::vector<std::string> complexToHeritIDList;
                            std::vector<ComplexNode*> complexToHerit;
                            if (Functions::String::occurencesInString(complexElementID, "(") == 1 &&
                                Functions::String::occurencesInString(complexElementID, ")") == 1 &&
                                Functions::String::split(complexElementID, "(").size() == 2)
                            {
                                std::string complexToHeritID = Functions::String::replaceString(Functions::String::split(complexElementID, "(")[1], ")", "");
                                complexElementID = Functions::String::split(complexElementID, "(")[0];
                                complexToHeritIDList = Functions::String::split(complexToHeritID, ",");

                                for (std::string& currentHerit : complexToHeritIDList)
                                {
                                    m_root->walk([currentHerit, &complexToHerit](NodeIterator& node)
                                    {
                                        if (node->getId() == currentHerit)
                                        {
                                            complexToHerit.push_back(node.get());
                                            node.terminate();
                                        }
                                    });
                                }
                            }
                            getPath(Path(addPath)).createComplexNode(complexElementID);
                            getPath(Path(addPath)).getComplexNode(complexElementID).setVisible(visible);
                            if (verbose)
                                std::cout << indenter() << "Create ComplexAttribute " << complexElementID << " inside "
                                    << pushIndicator << std::endl;
                            for (unsigned int i = 0; i < complexToHerit.size(); i++)
                            {
                                if (verbose) std::cout << indenter() << "    {Herit from : " << complexToHeritIDList[i] << "}" << std::endl;
                                getPath(Path(addPath)).getComplexNode(complexElementID).heritage(complexToHerit[i]);
                            }

                            addPath.push_back(complexElementID);
                        }
                        else if (!Functions::Vector::isInList(parsedLine.substr(0, 1), symbolExclusion) && Functions::String::occurencesInString(parsedLine, ":"))
                        {
                            std::string attributeID = Functions::String::split(parsedLine, ":")[0];
                            std::vector<std::string> splittedLine = Functions::String::split(parsedLine, ":");
                            std::string attributeValue = Functions::Vector::join(splittedLine, ":", 1, 0);
                            DataType attributeType = Types::getVarType(attributeValue);

                            if (attributeType == DataType::Link)
                            {
                                getPath(Path(addPath)).createLinkNode(attributeID, Functions::String::extract(attributeValue, 2, 1));
                                getPath(Path(addPath)).getLinkNode(attributeID).setVisible(visible);
                                if (verbose)
                                {
                                    std::cout << indenter() << "Create LinkAttribute " << attributeID << " linking to " << attributeValue
                                        << " inside " << pushIndicator << " (Type:" << attributeType << ")" << std::endl;
                                }
                                if (this->checkQuickLookMatches(getPath(Path(addPath)).getLinkNode(attributeID).getRawNodePath()))
                                    return true;
                            }
                            else if (attributeType == DataType::Template)
                            {
                                std::string templateName = attributeValue;
                                templateName = Functions::String::split(templateName, "(")[0];
                                if (m_templateList.find(templateName) != m_templateList.end())
                                {
                                    std::string argPart = Functions::String::split(attributeValue, "(")[1];
                                    argPart = argPart.substr(0, argPart.size() - 1);
                                    std::vector<std::string> templateArgs = Functions::String::split(argPart, ",");
                                    int i = 0;
                                    for (std::string& arg : templateArgs)
                                    {
                                        ComplexNode& cArg = getRootChild(templateName).at("__init__", std::to_string(i));
                                        cArg.remove("value");
                                        cArg.createDataNode("value", Types::getVarType(arg), arg);
                                        cArg.getDataNode("value").setAnnotation("Set");
                                        i++;
                                    }
                                    m_templateList[templateName]->build(&this->getPath(Path(addPath)), attributeID);
                                    getPath(Path(addPath)).getComplexNode(attributeID).useTemplate(m_templateList[templateName]);

                                    if (verbose)
                                    {
                                        std::cout << indenter() << "Create ComplexAttribute " << attributeID << " from Template <" << templateName
                                            << "> inside " << pushIndicator << std::endl;
                                    }

                                    if (this->checkQuickLookMatches(getPath(Path(addPath)).getComplexNode(attributeID).getRawNodePath()))
                                        return true;
                                }
                                else
                                    throw aube::ErrorHandler::Raise("Vili.Vili.ViliParser.UnknownTemplate", {{"template", templateName},{"id", attributeID},{"file", filename}});
                            }
                            else
                            {
                                DataNode& newDataNode = getPath(Path(addPath)).createDataNode(attributeID, attributeType);
                                newDataNode.setVisible(visible);
                                newDataNode.autoset(attributeValue);
                                if (verbose)
                                {
                                    std::cout << indenter() << "Create BaseAttribute " << attributeID << "(" << attributeValue;
                                    std::cout << ") inside " << pushIndicator << " (Type:" << attributeType << ")" << std::endl;
                                }
                                if (this->checkQuickLookMatches(newDataNode.getRawNodePath()))
                                    return true;
                            }
                        }
                        else if (curList != "None")
                        {
                            std::string attributeValue = parsedLine;
                            DataType attributeType = Types::getVarType(attributeValue);
                            if (verbose)
                                std::cout << indenter() << "Create Element #" << getPath(Path(addPath)).getArrayNode(curList).size()
                                    << "(" << attributeValue << ") of ListAttribute " << curList << std::endl;
                            if (attributeType == DataType::String)
                            {
                                attributeValue = Functions::String::extract(attributeValue, 1, 1);
                                getPath(Path(addPath)).getArrayNode(curList).push(attributeValue);
                            }
                            else if (attributeType == DataType::Int)
                            {
                                getPath(Path(addPath)).getArrayNode(curList).push(stoi(attributeValue));
                            }
                            else if (attributeType == DataType::Float)
                            {
                                getPath(Path(addPath)).getArrayNode(curList).push(stod(attributeValue));
                            }
                            else if (attributeType == DataType::Bool)
                            {
                                getPath(Path(addPath)).getArrayNode(curList).push(((attributeValue == "True") ? true : false));
                            }
                            else if (attributeType == DataType::Range)
                            {
                                int rStart = stoi(Functions::String::split(attributeValue, "..")[0]);
                                int rEnd = stoi(Functions::String::split(attributeValue, "..")[1]);
                                int step = 1;
                                if (rStart > rEnd)
                                    step = -1;
                                rEnd += step;
                                for (int i = rStart; i != rEnd; i += step)
                                {
                                    getPath(Path(addPath)).getArrayNode(curList).push(i);
                                }
                            }
                            else
                                throw aube::ErrorHandler::Raise("Vili.Vili.ViliParser.UnknownTypeInList", {{"list", attributeValue},{"file", filename}});
                        }
                    }
                }
                safeGetline(useFile, currentLine);
            }
            useFile.close();
            if (verbose) std::cout << "Parsed over.." << std::endl;
            return true;
        }
        throw aube::ErrorHandler::Raise("Vili.Vili.ViliParser.FileNotFound", {{"file", filename}});
    }

    void ViliParser::generateTemplate(const std::string& templateName, bool visible)
    {
        ComplexNode* templateBase = &getRootChild(templateName);
        NodeTemplate* newTemplate =  new NodeTemplate(templateName); 
        if (templateBase != nullptr)
        {
            if (templateBase->contains(NodeType::ComplexNode, "__init__") && templateBase->contains(NodeType::ComplexNode, "__body__"))
            {
                if (!templateBase->contains(NodeType::DataNode, "__linkroot__"))
                {
                    templateBase->at("__body__").createDataNode("__linkroot__", "/" + templateName + "/__init__");
                    templateBase->at<DataNode>("__body__", "__linkroot__").setVisible(false);
                    newTemplate->useDefaultLinkRoot();
                }

                int i = 0;
                while (true)
                {
                    if (templateBase->at("__init__").contains(NodeType::ComplexNode, std::to_string(i)))
                    {
                        NodeConstraintManager newConstraint(templateBase, templateName + "/__init__/" + std::to_string(i) + "/value");
                        std::vector<std::string> requiredTypes;
                        ComplexNode& currentArgument = templateBase->at("__init__", std::to_string(i));
                        if (currentArgument.contains(NodeType::DataNode, "type"))
                            requiredTypes.push_back(
                                currentArgument.getDataNode("type").get<std::string>()
                            );
                        else
                        {
                            for (unsigned int j = 0; j < currentArgument.getArrayNode("types").size(); j++)
                            {
                                requiredTypes.push_back(currentArgument.getArrayNode("types").get(j).get<std::string>());
                            }
                        }
                        std::vector<DataType> requiredConstraintTypes;
                        for (std::string& reqType : requiredTypes)
                        {
                            requiredConstraintTypes.push_back(Types::stringToDataType(reqType));
                        }
                        newConstraint.addConstraint([requiredConstraintTypes](DataNode* attribute) -> bool
                        {
                            return (Functions::Vector::isInList(attribute->getDataType(), requiredConstraintTypes));
                        });
                        if (templateBase->at("__init__", std::to_string(i)).contains(NodeType::DataNode, "defaultValue"))
                        {
                            std::string defaultValue = templateBase->at<DataNode>("__init__", std::to_string(i), "defaultValue").dumpData();
                            newConstraint.addConstraint([defaultValue](DataNode* attribute) -> bool
                            {
                                if (attribute->getAnnotation() != "Set")
                                {
                                    attribute->setAnnotation("Set");
                                    attribute->autoset(defaultValue);
                                }
                                return true;
                            });
                        }
                        newTemplate->addConstraintManager(newConstraint);
                    }
                    else
                        break;
                    i++;
                }
                templateBase->at("__body__").copy(newTemplate->getBody());
                newTemplate->setVisible(visible);
                m_templateList[templateBase->getId()] = newTemplate;
            }
            else
                throw aube::ErrorHandler::Raise("Vili.Vili.ViliParser.TemplateMissingInitOrBody", {{"template", templateName},{"file", m_root->getAnnotation()}});
        }
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.ViliParser.WrongTemplateBase", {{"attribute", templateName},{"file", m_root->getAnnotation()}});
    }

    void ViliParser::writeFile(const std::string& filename, bool verbose) const
    {
        std::ofstream outFile;
        outFile.open(filename);
        if (verbose) std::cout << "Writing ViliParser's content on file : " << filename << std::endl;
        if (m_spacing != 4)
        {
            outFile << "Spacing (" << m_spacing << ");" << std::endl;
            if (verbose) std::cout << "Define custom spacing : " << m_spacing << std::endl;
        }
        for (const std::string& include : m_includes)
        {
            outFile << "Include (" << include << ");" << std::endl;
            if (verbose) std::cout << "        Add New Include : " << include << std::endl;
        }
        if (verbose && m_flagList.size() > 0) std::cout << "    Writing Flags..." << std::endl;
        for (const std::string& flag : m_flagList)
        {
            outFile << "Flag (" << flag << ");" << std::endl;
            if (verbose) std::cout << "        Write New Flag : " << flag << std::endl;
        }


        if (m_flagList.size() > 0 || m_spacing != 4 || m_includes.size() > 0) outFile << std::endl;
        std::string writeSpacing = "";
        for (unsigned int i = 0; i < m_spacing; i++)
            writeSpacing += " ";
        m_root->write(&outFile, writeSpacing);

        if (m_templateList.size() > 0)
            outFile << std::endl;

        for (auto& templatePair : m_templateList)
        {
            if (templatePair.second->isVisible())
                outFile << "Template (" << templatePair.first << ");" << std::endl;
        }

        outFile.close();
    }

    void ViliParser::setSpacing(unsigned int spacing)
    {
        m_spacing = spacing;
    }

    unsigned ViliParser::getSpacing() const
    {
        return m_spacing;
    }

    void ViliParser::includeFile(const std::string& filename, bool verbose)
    {
        m_includes.push_back(filename);
        this->parseFile(filename + ".vili", verbose, false);
    }

    std::vector<std::string> ViliParser::getIncludes() const
    {
        return m_includes;
    }

    NodeTemplate* ViliParser::getTemplate(const std::string& templateId) const
    {
        if (m_templateList.find(templateId) != m_templateList.end())
            return m_templateList.at(templateId);
        throw aube::ErrorHandler::Raise("Vili.Vili.ViliParser.TemplateNotFound", {{"templateName", templateId}});
    }

    std::vector<std::string> ViliParser::getAllTemplates() const
    {
        std::vector<std::string> allTemplateNames;
        for (auto& cTemplate : m_templateList)
        {
            allTemplateNames.push_back(cTemplate.first);
        }
        return allTemplateNames;
    }

    void ViliParser::setQuickLookAttributes(const std::vector<std::string>&& qla)
    {
        m_quickLook = qla;
    }

    bool ViliParser::checkQuickLookMatches(const std::string& attributePath)
    {
        if (!m_quickLook.empty())
        {
            auto splittedPath = Functions::String::split(attributePath, "/");
            std::string joinedPath;
            if (splittedPath.size() > 1 && splittedPath[0] == "root")
            {
                joinedPath = Functions::Vector::join(splittedPath, "/", 1, 0);
            }
            else
            {
                joinedPath = attributePath;
            }
            
            if (Functions::Vector::isInList(joinedPath, m_quickLook) && !Functions::Vector::isInList(joinedPath, m_quickLookMatches))
            {
                m_quickLookMatches.push_back(joinedPath);
            }
            if (m_quickLookMatches.size() == m_quickLook.size())
            {
                m_quickLook.clear();
                m_quickLookMatches.clear();
                return true;
            }
            return false;
        }
        return false;
    }

    void ViliParser::StoreInCache(const std::string& path)
    {
        std::cout << "Storing : " << path << " in Cache" << std::endl;
        std::unique_ptr<ViliParser> fCache = std::make_unique<ViliParser>();
        std::cout << "Parsing to fill Cache" << std::endl;
        fCache->parseFile(path, true);
        std::cout << "Parsing over" << std::endl;
        ViliCache[path] = std::move(fCache);
    }

    bool ViliParser::CheckCache(ViliParser* parser, const std::string& path, bool visibility)
    {
        if (ViliCache.find(path) != ViliCache.end())
        {
            ComplexNode& cacheRoot = ViliCache[path]->root();
            for (Node* node : cacheRoot.getAll())
            {
                node->copy(parser->operator->());
                parser->root().get(node->getId())->setVisible(visibility);
            }
            for (const std::string& currentTemplate : ViliCache[path]->getAllTemplates())
            {
                parser->generateTemplate(currentTemplate);
                parser->getTemplate(currentTemplate)->setVisible(visibility);
            }
            for (auto& flag : ViliCache[path]->m_flagList)
                parser->m_flagList.push_back(flag);
            for (auto& include : ViliCache[path]->m_includes)
                parser->m_flagList.push_back(include);
            parser->m_spacing = ViliCache[path]->m_spacing;
            return true;
        }
        return false;
    }
}
