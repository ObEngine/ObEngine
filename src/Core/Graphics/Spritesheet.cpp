#include <Graphics/Spritesheet.hpp>

namespace obe::graphics
{
    vili::node Spritesheet::schema() const
    {
        return vili::node();
    }

    vili::node Spritesheet::dump() const
    {
        return vili::node();
    }

    void Spritesheet::load(const vili::node& data)
    {
    }

    const graphics::TexturePart Spritesheet::get_texture(uint32_t index) const
    {
        return TexturePart(m_texture, m_frames[index]);
    }
}

