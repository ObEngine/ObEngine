#include <Graphics/Renderable.hpp>

namespace obe::Graphics
{
    int32_t Renderable::getLayer() const
    {
        return m_layer;
    }

    int32_t Renderable::getZDepth() const
    {
        return m_zdepth;
    }

    bool Renderable::isVisible() const
    {
        return m_visible;
    }

    void Renderable::setLayer(int32_t layer)
    {
        m_layer = layer;
    }

    void Renderable::setZDepth(int32_t zdepth)
    {
        m_zdepth = zdepth;
    }

    void Renderable::setVisible(bool visible)
    {
        m_visible = visible;
    }

    void Renderable::show()
    {
        m_visible = true;
    }

    void Renderable::hide()
    {
        m_visible = false;
    }
}
