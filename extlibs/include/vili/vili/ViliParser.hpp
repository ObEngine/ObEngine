#pragma once

#include "ComplexNode.hpp"
#include "NodeTemplate.hpp"

namespace vili
{
    /**
     * \brief A Class that can parse .vili files and create a Node Tree
     * @Bind
     */
    class ViliParser
    {
    private:
        static std::map<std::string, std::unique_ptr<ViliParser>> ViliCache;
        std::vector<std::string> m_quickLook;
        std::vector<std::string> m_quickLookMatches;
        std::unique_ptr<ComplexNode> m_root = nullptr;
        std::map<std::string, NodeTemplate*> m_templateList;
        std::vector<std::string> m_flagList;
        unsigned int m_spacing = 4;
        std::vector<std::string> m_includes;
        ComplexNode& getPath(std::string path) const;
        ComplexNode& getRootChild(std::string child) const;
        bool checkQuickLookMatches(const std::string& attributePath);
    public:
        /**
         * \brief Creates a ViliParser
         */
        ViliParser();
        /**
         * \brief Creates a ViliParser and parses the file at the given path
         * \param file Path of the file to parse
         */
        ViliParser(const std::string& file);
        /**
         * \brief Access the tree root through arrow operator
         * \return A pointer to the tree root Node
         */
        ComplexNode* operator->() const;
        /**
         * \brief Returns a reference to the tree root Node
         * \return A reference of the tree root Node
         */
        ComplexNode& root() const;
        /**
         * \brief Adds a new Flag to the vili file
         * \param flag Flag to add to the .vili file
         */
        void addFlag(const std::string& flag);
        /**
         * \brief Access a direct child of the tree root Node by id
         * \param id Id of the node to get 
         * \return A reference to the ComplexNode child if found (raises an exception otherwise)
         */
        ComplexNode& operator[](const std::string& id) const;
        /**
         * \brief Access a ComplexNode in the tree using a path with slash-separation (.at("NodeA/NodeB/NodeC") for example)
         * \param path Path of the ComplexNode to access
         * \return A reference to the ComplexNode
         */
        ComplexNode& at(const std::string& path) const;
        /**
         * \brief Access a ComplexNode in the tree using a path (with multiple path parts) (.at("NodeA", "NodeB", "NodeB") for example)
         * \tparam Args Variadic Template
         * \param cPath Current Path Part if the Variadic Template
         * \param pathParts All other part parts not yet interpreted
         * \return A reference to the ComplexNode
         */
        template <class ...Args>
        ComplexNode& at(const std::string& cPath, Args ...pathParts);
        /**
         * \brief Access a casted Node in the tree using a path (with multiple path parts) (.at("NodeA", "NodeB", "NodeB") for example)
         * \tparam T Type of the Node used for cast
         * \tparam Args Variadic Template
         * \param cPath Current Path Part if the Variadic Template
         * \param pathParts All other part parts not yet interpreted
         * \return A reference to the casted Node
         */
        template <class T, class ...Args>
        T& at(const std::string& cPath, Args ...pathParts);
        /**
         * \brief Parses a .vili file
         * \param filename Path of the vili file to parse
         * \param verbose Should be true if the parsing should be verbose (prints debug messages), false otherwise
         * \param visible Should be true if the parsed elements (later pushed to the Tree) are supposed to be visible, false otherwise
         * \return true if the parsing was successful, false otherwise
         */
        bool parseFile(const std::string& filename, bool verbose = false, bool visible = true);
        /**
         * \brief Generates a NodeTemplate from a ComplexNode which should be a direct child of the Root
         * \param templateName Id of the ComplexNode to generate a NodeTemplate from (should be a direct child of the Root)
         * \param visible Should be true if the generated NodeTemplate should be visible after its creation, false otherwise
         */
        void generateTemplate(const std::string& templateName, bool visible = true);
        /**
         * \brief Writes the Tree to the given file at filename
         * \param filename Path where to write the file (overwrites the file if it already exists)
         * \param verbose Should be true if the writing should be verbose (prints debug messages), false otherwise
         */
        void writeFile(const std::string& filename, bool verbose = false) const;
        /**
         * \brief Check if the ViliParser contains the given Flag
         * \param flagName Flag to check the existence
         * \return true if the given Flag was found in the ViliParser, false otherwise
         */
        bool hasFlag(const std::string& flagName) const;
        /**
         * \brief Gets all the Flags of the ViliParser
         * \return All the flags of the ViliParser
         */
        std::vector<std::string> getAllFlags() const;
        /**
         * \brief Sets the new spacing of the vili file (default 4)
         * \param spacing New spacing of the vili file
         */
        void setSpacing(unsigned int spacing);
        /**
         * \brief Gets the spacing of the Vili file
         * \return An unsigned int containing the spacing of the vili file
         */
        unsigned int getSpacing() const;
        /**
         * \brief Includes a .vili file (all parsed content will be non-visible)
         * \param filename Path to the .vili file to include
         * \param verbose Should be true if the parsing should be verbose (prints debug messages), false otherwise
         */
        void includeFile(const std::string& filename, bool verbose = false);
        /**
         * \brief Gets a list of all included files
         * \return A std::vector of std::string containing the path to included vili files
         */
        std::vector<std::string> getIncludes() const;
        /**
         * \brief Gets the NodeTemplate at templateId
         * \param templateId Id of the NodeTemplate to get
         * \return A pointer to the NodeTemplate if found (raises an exception otherwise)
         */
        NodeTemplate* getTemplate(const std::string& templateId) const;

        void setQuickLookAttributes(const std::vector<std::string>&& qla);

        std::vector<std::string> getAllTemplates() const;

        static void StoreInCache(const std::string& path);
        static bool CheckCache(ViliParser* parser, const std::string& path, bool visibility);
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
