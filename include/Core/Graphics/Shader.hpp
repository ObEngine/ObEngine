#pragma once

#include <SFML/Graphics/Shader.hpp>
#include <vili/node.hpp>

#include <Types/Serializable.hpp>

namespace obe::graphics
{
    /**
     * \brief Shader class to use GLSL
     */
    class Shader : public sf::Shader, public types::Serializable
    {
    private:
        std::string m_path;

    public:
        Shader();
        explicit Shader(const std::string& path);
        [[nodiscard]] vili::node schema() const override;
        /**
         * \brief Dumps the content of the Shader to a Vili Node
         * \return vili::node containing the serialized Shader
         */
        [[nodiscard]] vili::node dump() const override;
        /**
         * \brief Loads the Shader from a Vili Node
         * \param data Vili Node containing the data of the Shader
         */
        void load(const vili::node& data) override;
        void load_from_file(const std::string& path);
    };
} // namespace obe::graphics
