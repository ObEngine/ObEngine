#include <Graphics/Spritesheet.hpp>

namespace obe::graphics
{
    graphics::Texture Spritesheet::load_texture(const std::string& texture_path) const
    {
        return graphics::Texture(); // TODO
    }

    Spritesheet::Spritesheet(engine::ResourceManager* resources)
        : m_resources(resources)
    {
    }

    const vili::node& Spritesheet::Schema()
    {
        // clang-format off
        static const vili::node schema = vili::object {
            { "type", vili::object_typename },
            { "properties", vili::object {
                { "image", vili::object {
                    { "type", vili::string_typename }
                }},
                { "frames", vili::object {
                    { "type", vili::array_typename },
                    { "items", vili::object {
                        { "type", vili::object_typename },
                        { "properties", vili::object {
                            { "x", vili::object {
                                { "type", vili::integer_typename }
                            }},
                            { "y", vili::object {
                                { "type", vili::integer_typename }
                            }},
                            { "width", vili::object {
                                { "type", vili::integer_typename }
                            }},
                            { "height", vili::object {
                                { "type", vili::integer_typename }
                            }},
                        }}
                    }}
                }}
            }}
        };
        // clang-format on
        return schema;
    }

    vili::node Spritesheet::schema() const
    {
        return Spritesheet::Schema();
    }

    vili::node Spritesheet::dump() const
    {
        return vili::node();
    }

    void Spritesheet::load(const vili::node& data)
    {
        const graphics::Texture& texture = this->load_texture(data.at("image"));
        for (const vili::node& frame : data.at("frames"))
        {
            transform::UnitVector frame_texture_rect_position(frame.at("x"), frame.at("y"));
            transform::UnitVector frame_texture_rect_size(frame.at("width"), frame.at("height"));
            m_frames.push_back(
                transform::AABB(frame_texture_rect_position, frame_texture_rect_size));
        }
    }

    const graphics::TexturePart Spritesheet::get_texture(uint32_t index) const
    {
        return TexturePart(m_texture, m_frames[index]);
    }
}
