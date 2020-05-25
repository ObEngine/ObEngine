#pragma once

#include <SFML/Graphics/Shader.hpp>
#include <vili/node.hpp>

#include <Types/Serializable.hpp>

namespace obe::Graphics
{
    /**
     * \brief Shader class to use GLSL
     * \bind{Shader}
     */
    class Shader : public sf::Shader, public Types::Serializable
    {
    private:
        std::string m_path;

    public:
        Shader();
        explicit Shader(const std::string& path);
        /**
         * \brief Dumps the content of the Shader to a Vili Node
         * \param target Vili Node where to serialize the Shader
         */
        vili::node dump() const override;
        /**
         * \brief Loads the Shader from a Vili Node
         * \param data Vili Node containing the data of the Shader
         */
        void load(vili::node& data) override;
        void loadShader(const std::string& path);
    };
} // namespace obe::Graphics