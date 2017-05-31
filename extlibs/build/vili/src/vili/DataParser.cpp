#include <fstream>

#include "vili/DataParser.hpp"
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
    DataParser::DataParser()
    {
        m_root = std::make_unique<ComplexAttribute>("root");
        m_root->setAnnotation("NoFile");
    }

    DataParser::DataParser(std::string file)
    {
        m_root = std::make_unique<ComplexAttribute>("root");
        m_root->setAnnotation("NoFile");
        parseFile(file);
    }

    ComplexAttribute* DataParser::operator->() const
    {
        return m_root.get();
    }

    ComplexAttribute& DataParser::root() const
    {
        return *m_root.get();
    }

    void DataParser::createFlag(const std::string& flag)
    {
        m_flagList.push_back(flag);
    }

    bool DataParser::hasFlag(const std::string& flagName) const
    {
        return find(m_flagList.begin(), m_flagList.end(), flagName) != m_flagList.end();
    }

    unsigned int DataParser::getAmountOfFlags() const
    {
        return m_flagList.size();
    }

    std::string DataParser::getFlagAtIndex(int index) const
    {
        return m_flagList.at(index);
    }

    ComplexAttribute& DataParser::getPath(std::string path) const
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

    ComplexAttribute& DataParser::getRootChild(std::string child) const
    {
        if (child.empty())
            return *m_root.get();
        return m_root->getComplexAttribute(child);
    }

    ComplexAttribute& DataParser::operator[](const std::string& cPath) const
    {
        return getPath(cPath);
    }

    ComplexAttribute& DataParser::at(std::string cPath) const
    {
        if (cPath.size() > 0 && Functions::String::extract(cPath, cPath.size() - 1, 0) == "/")
            cPath = Functions::String::extract(cPath, 0, 1);
        return getPath(cPath);
    }

    bool DataParser::parseFile(const std::string& filename, bool verbose, bool visible)
    {
        std::ifstream useFile;
        useFile.open(filename);
        m_root->setAnnotation(filename);
        std::string currentLine;
        std::vector<std::string> addPath = {};
        std::string curList = "None";
        int curListIndent = 0;
        bool inList = false;
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
                        addPath.pop_back();
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
                        curList = "None";
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
                                this->generateTemplate(instructionValue);
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
                            getPath(Path(addPath)).createListAttribute(listElementID);
                            getPath(Path(addPath)).getListAttribute(listElementID).setVisible(visible);
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
                            std::vector<ComplexAttribute*> complexToHerit;
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
                                        if (node->getID() == currentHerit)
                                        {
                                            complexToHerit.push_back(node.get());
                                            node.terminate();
                                        }
                                    });
                                }
                            }
                            getPath(Path(addPath)).createComplexAttribute(complexElementID);
                            getPath(Path(addPath)).getComplexAttribute(complexElementID).setVisible(visible);
                            if (verbose)
                                std::cout << indenter() << "Create ComplexAttribute " << complexElementID << " inside "
                                    << pushIndicator << std::endl;
                            for (unsigned int i = 0; i < complexToHerit.size(); i++)
                            {
                                if (verbose) std::cout << indenter() << "    {Herit from : " << complexToHeritIDList[i] << "}" << std::endl;
                                getPath(Path(addPath)).getComplexAttribute(complexElementID).heritage(complexToHerit[i]);
                            }

                            addPath.push_back(complexElementID);
                        }
                        else if (!Functions::Vector::isInList(parsedLine.substr(0, 1), symbolExclusion) && Functions::String::occurencesInString(parsedLine, ":"))
                        {
                            std::string attributeID = Functions::String::split(parsedLine, ":")[0];
                            std::vector<std::string> splittedLine = Functions::String::split(parsedLine, ":");
                            std::string attributeValue = Functions::Vector::join(splittedLine, ":", 1, 0);
                            Types::DataType attributeType = Types::getVarType(attributeValue);

                            if (attributeType == Types::Link)
                            {
                                getPath(Path(addPath)).createLinkAttribute(attributeID, Functions::String::extract(attributeValue, 2, 1));
                                getPath(Path(addPath)).getLinkAttribute(attributeID).setVisible(visible);
                                if (verbose)
                                {
                                    std::cout << indenter() << "Create LinkAttribute " << attributeID << " linking to " << attributeValue
                                        << " inside " << pushIndicator << " (Type:" << attributeType << ")" << std::endl;
                                }
                            }
                            else if (attributeType == Types::Template)
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
                                        ComplexAttribute& cArg = getRootChild(templateName).at("__init__", std::to_string(i));
                                        cArg.deleteBaseAttribute("value", true);
                                        cArg.createBaseAttribute("value", Types::getVarType(arg), arg);
                                        cArg.getBaseAttribute("value").setAnnotation("Set");
                                        i++;
                                    }
                                    m_templateList[templateName]->build(&getPath(Path(addPath)), attributeID);
                                    getPath(Path(addPath)).getComplexAttribute(attributeID).useTemplate(m_templateList[templateName]);

                                    if (verbose)
                                    {
                                        std::cout << indenter() << "Create ComplexAttribute " << attributeID << " from Template <" << templateName
                                            << "> inside " << pushIndicator << std::endl;
                                    }
                                }
                                else
                                    throw aube::ErrorHandler::Raise("Vili.Vili.DataParser.UnknownTemplate", {{"template", templateName},{"id", attributeID},{"file", filename}});
                            }
                            else
                            {
                                getPath(Path(addPath)).createBaseAttribute(attributeID, attributeType);
                                getPath(Path(addPath)).getBaseAttribute(attributeID).setVisible(visible);
                                getPath(Path(addPath)).getBaseAttribute(attributeID).autoset(attributeValue);
                                if (verbose)
                                {
                                    std::cout << indenter() << "Create BaseAttribute " << attributeID << "(" << attributeValue;
                                    std::cout << ") inside " << pushIndicator << " (Type:" << attributeType << ")" << std::endl;
                                }
                            }
                        }
                        else if (curList != "None")
                        {
                            std::string attributeValue = parsedLine;
                            Types::DataType attributeType = Types::getVarType(attributeValue);
                            if (verbose)
                                std::cout << indenter() << "Create Element #" << getPath(Path(addPath)).getListAttribute(curList).size()
                                    << "(" << attributeValue << ") of ListAttribute " << curList << std::endl;
                            if (attributeType == Types::String)
                            {
                                attributeValue = Functions::String::extract(attributeValue, 1, 1);
                                getPath(Path(addPath)).getListAttribute(curList).push(attributeValue);
                            }
                            else if (attributeType == Types::Int)
                            {
                                getPath(Path(addPath)).getListAttribute(curList).push(stoi(attributeValue));
                            }
                            else if (attributeType == Types::Float)
                            {
                                getPath(Path(addPath)).getListAttribute(curList).push(stod(attributeValue));
                            }
                            else if (attributeType == Types::Bool)
                            {
                                getPath(Path(addPath)).getListAttribute(curList).push(((attributeValue == "True") ? true : false));
                            }
                            else if (attributeType == Types::Range)
                            {
                                int rStart = stoi(Functions::String::split(attributeValue, "..")[0]);
                                int rEnd = stoi(Functions::String::split(attributeValue, "..")[1]);
                                int step = 1;
                                if (rStart > rEnd)
                                    step = -1;
                                rEnd += step;
                                for (int i = rStart; i != rEnd; i += step)
                                {
                                    getPath(Path(addPath)).getListAttribute(curList).push(i);
                                }
                            }
                            else
                                throw aube::ErrorHandler::Raise("Vili.Vili.DataParser.UnknownTypeInList", {{"list", attributeValue},{"file", filename}});
                        }
                    }
                }
                safeGetline(useFile, currentLine);
            }
            useFile.close();
            if (verbose) std::cout << "Parsed over.." << std::endl;
            return true;
        }
        throw aube::ErrorHandler::Raise("Vili.Vili.DataParser.FileNotFound", {{"file", filename}});
    }

    void DataParser::generateTemplate(const std::string& templateName)
    {
        ComplexAttribute* templateBase = &getRootChild(templateName);
        DataTemplate* newTemplate = new DataTemplate(templateName);
        if (templateBase != nullptr)
        {
            if (templateBase->contains(Types::ComplexAttribute, "__init__") && templateBase->contains(Types::ComplexAttribute, "__body__"))
            {
                if (!templateBase->contains(Types::BaseAttribute, "__linkroot__"))
                {
                    templateBase->at("__body__").createBaseAttribute("__linkroot__", "/" + templateName + "/__init__");
                    templateBase->at<BaseAttribute>("__body__", "__linkroot__").setVisible(false);
                    newTemplate->useDefaultLinkRoot();
                }

                int i = 0;
                while (true)
                {
                    if (templateBase->at("__init__").contains(Types::ComplexAttribute, std::to_string(i)))
                    {
                        AttributeConstraintManager newConstraint(templateBase, templateName + "/__init__/" + std::to_string(i) + "/value");
                        std::vector<std::string> requiredTypes;
                        ComplexAttribute& currentArgument = templateBase->at("__init__", std::to_string(i));
                        if (currentArgument.contains(Types::BaseAttribute, "type"))
                            requiredTypes.push_back(
                                currentArgument.getBaseAttribute("type").get<std::string>()
                            );
                        else
                        {
                            for (unsigned int j = 0; j < currentArgument.getListAttribute("types").size(); j++)
                            {
                                requiredTypes.push_back(currentArgument.getListAttribute("types").get(j).get<std::string>());
                            }
                        }
                        std::vector<Types::DataType> requiredConstraintTypes;
                        for (std::string& reqType : requiredTypes)
                        {
                            requiredConstraintTypes.push_back(Types::stringToDataType(reqType));
                        }
                        newConstraint.addConstraint([requiredConstraintTypes](BaseAttribute* attribute) -> bool
                        {
                            return (Functions::Vector::isInList(attribute->getDataType(), requiredConstraintTypes));
                        });
                        if (templateBase->at("__init__", std::to_string(i)).contains(Types::BaseAttribute, "defaultValue"))
                        {
                            std::string defaultValue = templateBase->at<BaseAttribute>("__init__", std::to_string(i), "defaultValue").returnData();
                            newConstraint.addConstraint([defaultValue](BaseAttribute* attribute) -> bool
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
                m_templateList[templateBase->getID()] = newTemplate;
            }
            else
                throw aube::ErrorHandler::Raise("Vili.Vili.DataParser.TemplateMissingInitOrBody", {{"template", templateName},{"file", m_root->getAnnotation()}});
        }
        else
            throw aube::ErrorHandler::Raise("Vili.Vili.DataParser.WrongTemplateBase", {{"attribute", templateName},{"file", m_root->getAnnotation()}});
    }

    void DataParser::writeFile(const std::string& filename, bool verbose) const
    {
        std::ofstream outFile;
        outFile.open(filename);
        if (verbose) std::cout << "Writing DataParser's content on file : " << filename << std::endl;
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
        if (verbose && this->getAmountOfFlags() > 0) std::cout << "    Writing Flags..." << std::endl;
        for (unsigned int i = 0; i < this->getAmountOfFlags(); i++)
        {
            outFile << "Flag (" << this->getFlagAtIndex(i) << ");" << std::endl;
            if (verbose) std::cout << "        Write New Flag : " << this->getFlagAtIndex(i) << std::endl;
        }


        if (this->getAmountOfFlags() > 0 || m_spacing != 4 || m_includes.size() > 0) outFile << std::endl;
        std::string writeSpacing = "";
        for (unsigned int i = 0; i < m_spacing; i++)
            writeSpacing += " ";
        m_root->write(&outFile, writeSpacing);

        if (m_templateList.size() > 0)
            outFile << std::endl;

        for (std::pair<std::string, DataTemplate*> templatePair : m_templateList)
            outFile << "Template (" << templatePair.first << ");";

        outFile.close();
    }

    void DataParser::setSpacing(unsigned int spacing)
    {
        m_spacing = spacing;
    }

    unsigned DataParser::getSpacing() const
    {
        return m_spacing;
    }

    void DataParser::includeFile(const std::string& filename, bool verbose)
    {
        m_includes.push_back(filename);
        this->parseFile(filename + ".vili", verbose, false);
    }

    std::vector<std::string> DataParser::getIncludes() const
    {
        return m_includes;
    }

    DataTemplate* DataParser::getTemplate(const std::string& templateId) const
    {
        if (m_templateList.find(templateId) != m_templateList.end())
            return m_templateList.at(templateId);
        throw aube::ErrorHandler::Raise("Vili.Vili.DataParser.TemplateNotFound", {{"templateName", templateId}});
    }
}
