#include <Graphics/Renderable.hpp>

namespace obe::graphics
{
    int32_t Renderable::get_layer() const
    {
        return m_layer;
    }

    int32_t Renderable::get_sublayer() const
    {
        return m_sublayer;
    }

    bool Renderable::is_visible() const
    {
        return m_visible;
    }

    void Renderable::set_layer(int32_t layer)
    {
        m_layer = layer;
    }

    void Renderable::set_sublayer(int32_t sublayer)
    {
        m_sublayer = sublayer;
    }

    void Renderable::set_visible(bool visible)
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
