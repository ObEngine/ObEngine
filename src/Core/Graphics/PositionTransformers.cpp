#include <Graphics/PositionTransformers.hpp>

namespace obe::Graphics
{
    std::map<std::string, CoordinateTransformer> Transformers;

    CoordinateTransformer Parallax = [](double pos, double cam, int layer) -> double {
        return (pos * layer - cam) / double(layer);
    };
    CoordinateTransformer Camera
        = [](double pos, double cam, int layer) -> double { return pos - cam; };
    CoordinateTransformer Position
        = [](double pos, double cam, int layer) -> double { return pos; };

    PositionTransformer::PositionTransformer()
    {
        m_xTransformer = Transformers[m_xTransformerName];
        m_yTransformer = Transformers[m_yTransformerName];
    }

    PositionTransformer::PositionTransformer(
        const std::string& xTransformer, const std::string& yTransformer)
    {
        m_xTransformerName = xTransformer;
        m_yTransformerName = yTransformer;
        m_xTransformer = Transformers[m_xTransformerName];
        m_yTransformer = Transformers[m_yTransformerName];
    }

    Transform::UnitVector PositionTransformer::operator()(
        const Transform::UnitVector& position, const Transform::UnitVector& camera, int layer) const
    {
        Transform::UnitVector transformedPosition(position.unit);
        transformedPosition.x = m_xTransformer(position.x, camera.to(position.unit).x, layer);
        transformedPosition.y = m_yTransformer(position.y, camera.to(position.unit).y, layer);
        return transformedPosition;
    }

    CoordinateTransformer& PositionTransformer::getXTransformer()
    {
        return m_xTransformer;
    }

    CoordinateTransformer& PositionTransformer::getYTransformer()
    {
        return m_yTransformer;
    }

    std::string PositionTransformer::getXTransformerName() const
    {
        return m_xTransformerName;
    }

    std::string PositionTransformer::getYTransformerName() const
    {
        return m_yTransformerName;
    }

    void InitPositionTransformer()
    {
        Transformers["Parallax"] = Parallax;
        Transformers["Camera"] = Camera;
        Transformers["Position"] = Position;
    }
} // namespace obe::Graphics