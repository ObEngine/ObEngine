#include <Graphics/Shader.hpp>
#include <System/Path.hpp>

namespace obe::Graphics
{
    Shader::Shader()
    {
        m_path = "";
    }

    Shader::Shader(const std::string& path)
    {
        this->loadShader(path);
    }

    void Shader::loadShader(const std::string& path)
    {
        this->loadFromFile(System::Path(path).find(), sf::Shader::Type::Fragment);
        m_path = path;
    }
    void Shader::dump(vili::ComplexNode& target) const
    {
    }
    void Shader::load(vili::ComplexNode& data)
    {
    }
} // namespace obe::Graphics