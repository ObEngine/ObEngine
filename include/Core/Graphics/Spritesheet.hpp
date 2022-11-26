#pragma once

#include <Graphics/Texture.hpp>
#include <Transform/AABB.hpp>
#include <Types/Serializable.hpp>

namespace obe::graphics
{
    class Spritesheet : public types::Serializable
    {
    private:
        graphics::Texture m_texture;
        std::vector<transform::AABB> m_frames;
    public:
        virtual vili::node schema() const override;
        virtual vili::node dump() const override;
        virtual void load(const vili::node& data) override;

        const graphics::TexturePart get_texture(uint32_t index) const;
    };
}