#pragma once

#include <Graphics/RenderTarget.hpp>
#include <cstdint>

namespace obe::scene
{
    class Camera;
}

namespace obe::graphics
{
    class Renderable
    {
    protected:
        int32_t m_layer = 1;
        int32_t m_sublayer = 1;
        bool m_visible = true;

    public:
        Renderable() = default;
        Renderable(int32_t layer, int32_t sublayer);
        virtual ~Renderable() = default;

        /**
         * \brief Get the layer of the Renderable
         * \return An int containing the Layer where the Renderable is (Higher layer
         *         is behind lower ones)
         */
        [[nodiscard]] int32_t get_layer() const;
        /**
         * \brief Get the in-layer draw order of the Renderable
         * \return An int containing the sublayer where the sprite is (Higher
         *         sublayer is behind lower ones)
         */
        [[nodiscard]] int32_t get_sublayer() const;
        /**
         * \brief Get the visibility of the Renderable
         * \return true if the Renderable is visible, false otherwise
         */
        [[nodiscard]] bool is_visible() const;

        /**
         * \brief Set the layer of the Renderable
         * \param layer Layer where to put the Renderable (Higher layer is behind
         *        lower ones)
         */
        void set_layer(int32_t layer);
        /**
         * \brief Set the in-layer draw order of the Renderable (SubLayers)
         * \param sublayer in-layer draw order of the Renderable (Higher sublayer is behind lower
         *        ones)
         */
        void set_sublayer(int32_t sublayer);
        /**
         * \brief Set the visibility of the Renderable
         * \param visible If visible is equal to true, the Renderable will be
         *        visible, if visible is equal to false, it won't be visible
         */
        void set_visible(bool visible);
        void show();
        void hide();

        virtual void draw(RenderTarget& surface, const scene::Camera& camera) = 0;
    };
} // namespace obe::graphics
