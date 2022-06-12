#include <Graphics/Shader.hpp>
#include <System/Path.hpp>

namespace obe::graphics
{
    Shader::Shader()
        : m_path("")
    {
    }

    Shader::Shader(const std::string& path)
    {
        this->load_from_file(path);
    }

    vili::node Shader::schema() const
    {
        return vili::object {};
    }

    void Shader::load_from_file(const std::string& path)
    {
        this->loadFromFile(System::Path(path).find(), sf::Shader::Type::Fragment);
        m_path = path;
    }
    vili::node Shader::dump() const
    {
        vili::node result;
        return result;
    }
    void Shader::load(const vili::node& data)
    {
    }
} // namespace obe::graphics
