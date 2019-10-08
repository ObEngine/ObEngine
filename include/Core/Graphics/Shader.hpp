#pragma once

#include <SFML/Graphics/Shader.hpp>
#include <vili/ComplexNode.hpp>

#include <Types/Serializable.hpp>

namespace obe::Graphics
{
    /**
     * \brief Shader class to use GLSL
     * @Bind
     */
    class Shader : public sf::Shader, public Types::Serializable
    {
    private:
        std::string m_path;

    public:
        Shader();
        explicit Shader(const std::string& path);
        /**
         * \brief Dumps the content of the Shader to a ComplexNode
         * \param target ComplexNode where to serialize the Shader
         */
        void dump(vili::ComplexNode& target) const override;
        /**
         * \brief Loads the Shader from a ComplexNode
         * \param data ComplexNode containing the data of the Shader
         */
        void load(vili::ComplexNode& data) override;
        void loadShader(const std::string& path);
    };
} // namespace obe::Graphics