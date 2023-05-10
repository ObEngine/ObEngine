#pragma once

#include <Engine/ResourceManager.hpp>
#include <Graphics/Texture.hpp>
#include <Transform/AABB.hpp>
#include <Types/Serializable.hpp>

namespace obe::graphics
{
    class Spritesheet : public types::Serializable
    {
    private:
        engine::ResourceManager* m_resources;
        graphics::Texture m_texture;
        std::vector<transform::AABB> m_frames;

        graphics::Texture load_texture(const std::string& texture_path) const;

    public:
        Spritesheet(engine::ResourceManager* resources = nullptr);

        [[nodiscard]] static const vili::node& Schema();

        [[nodiscard]] virtual vili::node schema() const override;
        [[nodiscard]] virtual vili::node dump() const override;
        virtual void load(const vili::node& data) override;

        const graphics::TexturePart get_texture(uint32_t index) const;
    };
}