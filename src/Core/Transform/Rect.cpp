#include <cmath>

#include <Graphics/DrawUtils.hpp>
#include <Transform/Rect.hpp>
#include <Utils/MathUtils.hpp>

namespace obe::Transform
{
    UnitVector rotatePointAroundCenter(
        const UnitVector& center, const UnitVector& Around, double angle)
    {
        const double cY = std::cos(angle);
        const double sY = std::sin(angle);

        UnitVector moved;
        const UnitVector delta = Around - center;
        moved.x = (delta.x * cY - delta.y * sY) + center.x;
        moved.y = (delta.x * sY + delta.y * cY) + center.y;

        return moved;
    };

    double Rect::getRotation() const
    {
        return m_angle;
    }

    void Rect::setRotation(double angle, Transform::UnitVector origin)
    {
        this->rotate(angle - m_angle, origin);
    }

    void Rect::rotate(double angle, Transform::UnitVector origin)
    {
        const double radAngle = Utils::Math::convertToRadian(-angle);

        m_position = rotatePointAroundCenter(origin, m_position, radAngle);
        m_angle += angle;
        if (m_angle < 0 || m_angle > 360)
            m_angle = Utils::Math::normalize(m_angle, 0, 360);
    }

    void Rect::transformRef(
        UnitVector& vec, const Referential& ref, ReferentialConversionType type) const
    {
        const double factor = (type == ReferentialConversionType::From) ? 1.0 : -1.0;
        const double radAngle = Utils::Math::convertToRadian(-m_angle);
        const double cosAngle = std::cos(radAngle);
        const double sinAngle = std::sin(radAngle);

        const auto delta = (ref.getOffset() * m_size);

        vec.add(UnitVector((delta.x * cosAngle - delta.y * sinAngle) * factor,
            (delta.x * sinAngle + delta.y * cosAngle) * factor));
    }

    Rect::Rect(const Transform::UnitVector& position, const Transform::UnitVector& size)
    {
        m_position = position;
        m_size = size;
    }

    void Rect::draw(graphics::RenderTarget surface, int x, int y) const
    {
        float radius = 6.f;

        std::vector<Transform::UnitVector> drawPoints;
        const UnitVector dPos(x, y, Transform::Units::ScenePixels);

        const std::vector<Referential> fixDisplayOrder = { Referential::TopLeft, Referential::Top,
            Referential::TopRight, Referential::Right, Referential::BottomRight,
            Referential::Bottom, Referential::BottomLeft, Referential::Left };

        for (uint8_t i = 0; i < 8; ++i)
        {
            UnitVector pt;
            this->transformRef(pt, fixDisplayOrder[i], ReferentialConversionType::From);

            UnitVector world = (pt + dPos).to<Units::ScenePixels>();
            drawPoints.push_back(world);
        }

        const double radAngle = Utils::Math::convertToRadian(-m_angle);
        const double cosAngle = std::cos(radAngle);
        const double sinAngle = std::sin(radAngle);
        UnitVector topPos;
        this->transformRef(topPos, Referential::Top, ReferentialConversionType::From);
        topPos = topPos.to<Units::ScenePixels>();
        topPos += dPos;
        UnitVector vec = topPos;
        UnitVector result;
        const double dy = m_size.y / 4;
        result.x = (-dy * sinAngle) * -1;
        result.y = (dy * cosAngle) * -1;
        vec += result;
        graphics::utils::draw_point(surface, static_cast<int>(vec.x - radius),
            static_cast<int>(vec.y - radius), radius, sf::Color::White);
        graphics::utils::draw_line(surface, static_cast<int>(vec.x), static_cast<int>(vec.y),
            static_cast<int>(topPos.x), static_cast<int>(topPos.y), 2, sf::Color::White);

        std::unordered_map<unsigned int, graphics::Color> pointsColor
            = { { 0, graphics::Color::Red }, { 1, graphics::Color(255, 128, 0) },
                  { 2, graphics::Color::Yellow }, { 3, graphics::Color(128, 255, 0) },
                  { 4, graphics::Color::Green }, { 5, graphics::Color(0, 255, 128) },
                  { 6, graphics::Color::Magenta }, { 7, graphics::Color(0, 128, 255) },
                  { 8, graphics::Color::Blue } };

        // TODO: Refactor using C++20 designated initializers
        graphics::utils::DrawPolygonOptions options { true, true, radius, graphics::Color::White,
            graphics::Color::White, {}, pointsColor };

        graphics::utils::draw_polygon(surface, drawPoints, options);
    }

    double Rect::x() const
    {
        return m_position.x;
    }

    double Rect::y() const
    {
        return m_position.y;
    }

    double Rect::width() const
    {
        return m_size.x;
    }

    double Rect::height() const
    {
        return m_size.y;
    }

    bool Rect::intersects(const Rect& rect) const
    {
        const auto r1MinX = std::min(m_position.x, m_position.x + m_size.x);
        const auto r1MaxX = std::max(m_position.x, m_position.x + m_size.x);
        const auto r1MinY = std::min(m_position.y, m_position.y + m_size.y);
        const auto r1MaxY = std::max(m_position.y, m_position.y + m_size.y);

        const auto r2MinX = std::min(rect.m_position.x, rect.m_position.x + rect.m_size.x);
        const auto r2MaxX = std::max(rect.m_position.x, rect.m_position.x + rect.m_size.x);
        const auto r2MinY = std::min(rect.m_position.y, rect.m_position.y + rect.m_size.y);
        const auto r2MaxY = std::max(rect.m_position.y, rect.m_position.y + rect.m_size.y);

        return !(r2MinX > r1MaxX || r2MaxX < r1MinX || r2MinY > r1MaxY || r2MaxY < r1MinY);
    }

    std::optional<Rect> Rect::intersection(const Rect& rect) const
    {
        const auto r1MinX = std::min(m_position.x, m_position.x + m_size.x);
        const auto r1MaxX = std::max(m_position.x, m_position.x + m_size.x);
        const auto r1MinY = std::min(m_position.y, m_position.y + m_size.y);
        const auto r1MaxY = std::max(m_position.y, m_position.y + m_size.y);

        const auto r2MinX = std::min(rect.m_position.x, rect.m_position.x + rect.m_size.x);
        const auto r2MaxX = std::max(rect.m_position.x, rect.m_position.x + rect.m_size.x);
        const auto r2MinY = std::min(rect.m_position.y, rect.m_position.y + rect.m_size.y);
        const auto r2MaxY = std::max(rect.m_position.y, rect.m_position.y + rect.m_size.y);

        const auto intersectionLeft = std::max(r1MinX, r2MinX);
        const auto intersectionTop = std::max(r1MinY, r2MinY);
        const auto intersectionRight = std::min(r1MaxX, r2MaxX);
        const auto intersectionBottom = std::min(r1MaxY, r2MaxY);

        if ((intersectionLeft < intersectionRight) && (intersectionTop < intersectionBottom))
        {
            Rect intersection;
            intersection.set_position(
                UnitVector(intersectionLeft, intersectionTop, m_position.unit));
            intersection.setSize(UnitVector(intersectionRight - intersectionLeft,
                intersectionBottom - intersectionTop, m_size.unit));
            return std::make_optional(intersection);
        }
        else
        {
            return std::nullopt;
        }
    }

    bool Rect::contains(const Rect& rect) const
    {
        return contains(rect.get_position(Referential::TopLeft))
            && contains(rect.get_position(Referential::BottomRight));
    }

    bool Rect::contains(const UnitVector& position) const
    {
        const UnitVector converted_position = position.to(m_position.unit);
        const auto minX = std::min(m_position.x, m_position.x + m_size.x);
        const auto maxX = std::max(m_position.x, m_position.x + m_size.x);
        const auto minY = std::min(m_position.y, m_position.y + m_size.y);
        const auto maxY = std::max(m_position.y, m_position.y + m_size.y);

        return (converted_position.x >= minX) && (converted_position.x < maxX)
            && (converted_position.y >= minY) && (converted_position.y < maxY);
    }

    void Rect::setPointPosition(const UnitVector& position, const Referential& ref)
    {
        const UnitVector oppositePointPosition = this->get_position(ref.flip());
        const double radAngle = Utils::Math::convertToRadian(-m_angle);
        const UnitVector movedPoint
            = rotatePointAroundCenter(position, oppositePointPosition, -radAngle);

        this->set_position(position, ref);

        if (ref.isOnCorner())
        {
            if (ref.isOnTopSide())
            {
                this->setSize({ movedPoint.x - position.x, movedPoint.y - position.y }, ref);
            }
            else
            {
                this->setSize({ position.x - movedPoint.x, position.y - movedPoint.y }, ref);
            }
        }
        if (ref.isOnLeftSide() || ref.isOnRightSide())
        {
            if (ref.isOnLeftSide())
            {
                this->setSize({ movedPoint.x - position.x, m_size.y }, ref);
            }
            else
            {
                this->setSize({ position.x - movedPoint.x, m_size.y }, ref);
            }
        }
        else // we are on TopSide or BottomSide here, no need to specify the
            // condition
        {
            if (ref.isOnTopSide())
            {
                this->setSize({ m_size.x, movedPoint.y - position.y }, ref);
            }
            else
            {
                this->setSize({ m_size.x, position.y - movedPoint.y }, ref);
            }
        }
    }

    UnitVector Rect::get_position(const Referential& ref) const
    {
        UnitVector getPosVec = m_position;
        this->transformRef(getPosVec, ref, ReferentialConversionType::From);
        return getPosVec;
    }

    void Rect::set_position(const UnitVector& position, const Referential& ref)
    {
        UnitVector pVec = position.to<Units::SceneUnits>();
        this->transformRef(pVec, ref, ReferentialConversionType::To);
        m_position.set(pVec);
    }

    void Rect::setSize(const UnitVector& size, const Referential& ref)
    {
        const UnitVector savePosition = this->get_position(ref);
        m_size.set(size);
        this->set_position(savePosition, ref);
    }

    void Rect::set_position(const UnitVector& position)
    {
        this->set_position(position, Referential::TopLeft);
    }

    UnitVector Rect::getPosition() const
    {
        return this->get_position(Referential::TopLeft);
    }

    void Rect::move(const UnitVector& position)
    {
        m_position += position;
    }

    void Rect::scale(const UnitVector& size, const Referential& ref)
    {
        const UnitVector savePosition = this->get_position(ref);
        m_size *= size;
        this->set_position(savePosition, ref);
    }

    UnitVector Rect::get_size() const
    {
        return m_size;
    }

    void Rect::movePoint(const UnitVector& position, const Referential& ref)
    {
    }

    UnitVector Rect::getScaleFactor() const
    {
        return UnitVector(Utils::Math::sign(m_size.x), Utils::Math::sign(m_size.y));
    }
} // namespace obe::Transform
