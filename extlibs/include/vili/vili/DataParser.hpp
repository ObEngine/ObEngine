#pragma once

#include "ComplexAttribute.hpp"
#include "DataTemplate.hpp"

namespace vili
{
    class DataParser
    {
    private:
        std::unique_ptr<ComplexAttribute> m_root = nullptr;
        std::map<std::string, DataTemplate*> m_templateList;
        std::vector<std::string> m_flagList;
        unsigned int m_spacing = 4;
        std::vector<std::string> m_includes;
        ComplexAttribute& getPath(std::string path) const;
        ComplexAttribute& getRootChild(std::string child) const;
    public:
        DataParser();
        DataParser(std::string file);
        ComplexAttribute* operator->() const;
        ComplexAttribute& root() const;
        void createFlag(const std::string& flag);
        ComplexAttribute& operator[](const std::string& cPath) const;
        ComplexAttribute& at(std::string cPath) const;
        template <class ...Args>
        ComplexAttribute& at(const std::string& cPath, Args ...pathParts);
        template <class T, class ...Args>
        T& at(const std::string& cPath, Args ...pathParts);
        bool parseFile(const std::string& filename, bool verbose = false, bool visible = true);
        void generateTemplate(const std::string& templateName);
        void writeFile(const std::string& filename, bool verbose = false) const;
        bool hasFlag(const std::string& flagName) const;
        unsigned int getAmountOfFlags() const;
        std::string getFlagAtIndex(int index) const;
        void setSpacing(unsigned int spacing);
        unsigned int getSpacing() const;
        void includeFile(const std::string& filename, bool verbose = false);
        std::vector<std::string> getIncludes() const;
        DataTemplate* getTemplate(const std::string& templateId) const;
    };

    template <class ...Args>
    ComplexAttribute& DataParser::at(const std::string& cPath, Args ...pathParts)
    {
        return m_root->at(cPath, pathParts...);
    }

    template <class T, class ...Args>
    T& DataParser::at(const std::string& cPath, Args ...pathParts)
    {
        return m_root->at<T>(cPath, pathParts...);
    }
}
