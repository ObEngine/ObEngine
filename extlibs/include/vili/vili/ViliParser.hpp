#pragma once

#include "ComplexNode.hpp"
#include "NodeTemplate.hpp"

namespace vili
{
    class ViliParser
    {
    private:
        std::unique_ptr<ComplexNode> m_root = nullptr;
        std::map<std::string, NodeTemplate*> m_templateList;
        std::vector<std::string> m_flagList;
        unsigned int m_spacing = 4;
        std::vector<std::string> m_includes;
        ComplexNode& getPath(std::string path) const;
        ComplexNode& getRootChild(std::string child) const;
    public:
        ViliParser();
        ViliParser(std::string file);
        ComplexNode* operator->() const;
        ComplexNode& root() const;
        void createFlag(const std::string& flag);
        ComplexNode& operator[](const std::string& cPath) const;
        ComplexNode& at(std::string cPath) const;
        template <class ...Args>
        ComplexNode& at(const std::string& cPath, Args ...pathParts);
        template <class T, class ...Args>
        T& at(const std::string& cPath, Args ...pathParts);
        bool parseFile(const std::string& filename, bool verbose = false, bool visible = true);
        void generateTemplate(const std::string& templateName, bool visible = true);
        void writeFile(const std::string& filename, bool verbose = false) const;
        bool hasFlag(const std::string& flagName) const;
        unsigned int getAmountOfFlags() const;
        std::string getFlagAtIndex(int index) const;
        void setSpacing(unsigned int spacing);
        unsigned int getSpacing() const;
        void includeFile(const std::string& filename, bool verbose = false);
        std::vector<std::string> getIncludes() const;
        NodeTemplate* getTemplate(const std::string& templateId) const;
    };

    template <class ...Args>
    ComplexNode& ViliParser::at(const std::string& cPath, Args ...pathParts)
    {
        return m_root->at(cPath, pathParts...);
    }

    template <class T, class ...Args>
    T& ViliParser::at(const std::string& cPath, Args ...pathParts)
    {
        return m_root->at<T>(cPath, pathParts...);
    }
}
