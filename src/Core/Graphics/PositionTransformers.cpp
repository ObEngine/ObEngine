#include <Graphics/PositionTransformers.hpp>

namespace obe::graphics
{
    std::map<std::string, CoordinateTransformer> Transformers;

    CoordinateTransformer Parallax = [](double pos, double cam, int layer) -> double {
        return (pos * layer - cam) / static_cast<double>(layer);
    };
    CoordinateTransformer Camera
        = [](double pos, double cam, int layer) -> double { return pos - cam; };
    CoordinateTransformer Position
        = [](double pos, double cam, int layer) -> double { return pos; };

    PositionTransformer::PositionTransformer()
    {
        m_x_transformer = Transformers[m_x_transformer_name];
        m_y_transformer = Transformers[m_y_transformer_name];
    }

    PositionTransformer::PositionTransformer(
        const std::string& x_transformer, const std::string& y_transformer)
        : m_x_transformer_name(x_transformer)
        , m_y_transformer_name(y_transformer)
    {
        m_x_transformer = Transformers[m_x_transformer_name];
        m_y_transformer = Transformers[m_y_transformer_name];
    }

    transform::Vector2 PositionTransformer::operator()(
        const transform::Vector2& position, const transform::Vector2& camera, int layer) const
    {
        transform::Vector2 transformed_position;
        transformed_position.x = m_x_transformer(position.x, camera.x, layer);
        transformed_position.y = m_y_transformer(position.y, camera.y, layer);
        return transformed_position;
    }

    CoordinateTransformer& PositionTransformer::get_x_transformer()
    {
        return m_x_transformer;
    }

    CoordinateTransformer& PositionTransformer::get_y_transformer()
    {
        return m_y_transformer;
    }

    std::string PositionTransformer::get_x_transformer_name() const
    {
        return m_x_transformer_name;
    }

    std::string PositionTransformer::get_y_transformer_name() const
    {
        return m_y_transformer_name;
    }

    void init_position_transformers()
    {
        Transformers["Parallax"] = Parallax;
        Transformers["Camera"] = Camera;
        Transformers["Position"] = Position;
    }
} // namespace obe::graphics
