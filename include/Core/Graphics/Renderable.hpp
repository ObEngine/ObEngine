#pragma once

#include <cstdint>

#include <Graphics/RenderTarget.hpp>

namespace obe::Scene
{
    class Camera;
}

namespace obe::Graphics
{
    class Renderable
    {
    protected:
        int32_t m_layer = 1;
        int32_t m_zdepth = 1;
        bool m_visible = true;

    public:
        Renderable() = default;
        virtual ~Renderable() = default;

        /**
         * \brief Get the layer of the Renderable
         * \return An int containing the Layer where the Renderable is (Higher layer
         *         is behind lower ones)
         */
        [[nodiscard]] int32_t getLayer() const;
        /**
         * \brief Get the Z-depth of the Renderable
         * \return An int containing the z-depth where the sprite is (Higher
         *         z-depth is behind lower ones)
         */
        [[nodiscard]] int32_t getZDepth() const;
        /**
         * \brief Get the visibility of the Renderable
         * \return true if the Renderable is visible, false otherwise
         */
        [[nodiscard]] bool isVisible() const;

        /**
         * \brief Set the layer of the Renderable
         * \param layer Layer where to put the Renderable (Higher layer is behind
         *        lower ones)
         */
        void setLayer(int32_t layer);
        /**
         * \brief Set the Z-Depth of the Renderable (SubLayers)
         * \param zdepth z-depth of the Renderable (Higher z-depth is behind lower
         *        ones)
         */
        void setZDepth(int32_t zdepth);
        /**
         * \brief Set the visibility of the Renderable
         * \param visible If visible is equal to true, the Renderable will be
         *        visible, if visible is equal to false, it won't be visible
         */
        void setVisible(bool visible);
        void show();
        void hide();

        virtual void draw(RenderTarget& surface, const Scene::Camera& camera) = 0;
    };
}
