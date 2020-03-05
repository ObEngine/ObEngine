#pragma once

#include <ComplexNode.hpp>
#include <NodeTemplate.hpp>

namespace vili
{
    /**
     * \brief A Class that can parse multiple .vili files and create a Node Tree
     */
    class MultipleViliParser
    {
    private:
        std::map<std::string, std::vector<std::string>> m_filemap;
    public:
        /**
         * \brief Creates a ViliParser
         */
        MultipleViliParser();
        /**
         * \brief Creates a ViliParser and parses the file at the given path
         * \param file Path of the file to parse
         */
        MultipleViliParser(std::string currentFile);
        template <class... files>
        MultipleViliParser(std::string currentFile, files... filepack);
        MultipleViliParser(std::vector<std::string> files);

        void writeFiles(bool verbose = false);
    };
}
