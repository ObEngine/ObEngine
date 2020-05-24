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
    vili::node Shader::dump() const
    {
        vili::node result;
        return result;
    }
    void Shader::load(vili::node& data)
    {
    }
} // namespace obe::Graphics