#include <cmath>

#include <SFML/Graphics/RenderWindow.hpp>

#include <Graphics/DrawUtils.hpp>
#include <Transform/Rect.hpp>
#include <Utils/MathUtils.hpp>
#include <iostream>

namespace obe::Transform
{
    UnitVector rotatePointAroundCenter(
        const UnitVector& center, const UnitVector& Around, float angle)
    {
        double cY = std::cos(angle);
        double sY = std::sin(angle);

        UnitVector moved, delta = Around - center;
        moved.x = (delta.x * cY - delta.y * sY) + center.x;
        moved.y = (delta.x * sY + delta.y * cY) + center.y;

        return moved;
    };

    float Rect::getRotation() const
    {
        return m_angle;
    }

    void Rect::setRotation(float angle, Transform::UnitVector origin)
    {
        this->rotate(angle - m_angle, origin);
    }

    void Rect::rotate(float angle, Transform::UnitVector origin)
    {
        const double radAngle = Utils::Math::convertToRadian(-angle);

        m_position = rotatePointAroundCenter(origin, m_position, radAngle);
        m_angle += angle;
        if (m_angle < 0 || m_angle > 360)
            m_angle = Utils::Math::normalise(m_angle, 0, 360);
    }

    void Rect::transformRef(UnitVector& vec, Referential ref, ConversionType type) const
    {
        const double factor = (type == ConversionType::From) ? 1.0 : -1.0;
        const double radAngle = Utils::Math::convertToRadian(-m_angle);
        const double cosAngle = std::cos(radAngle);
        const double sinAngle = std::sin(radAngle);
        UnitVector result;

        auto [dx, dy] = (ref.getOffset() * m_size).unpack();

        vec.add(UnitVector(
            (dx * cosAngle - dy * sinAngle) * factor, (dx * sinAngle + dy * cosAngle) * factor));
    }

    Rect::Rect()
    {
    }

    Rect::Rect(const Transform::UnitVector& position, const Transform::UnitVector& size)
    {
        m_position = position;
        m_size = size;
    }

    void Rect::draw(int posX, int posY) const
    {
        int r = 6;

        std::vector<sf::Vector2i> drawPoints;
        UnitVector dPos(posX, posY, Transform::Units::ScenePixels);

        const std::vector<Referential> fixDisplayOrder = { Referential::TopLeft, Referential::Top,
            Referential::TopRight, Referential::Right, Referential::BottomRight,
            Referential::Bottom, Referential::BottomLeft, Referential::Left };

        for (uint8_t i = 0; i < 8; ++i)
        {
            UnitVector pt;
            this->transformRef(pt, fixDisplayOrder[i], ConversionType::From);

            UnitVector world = (pt + dPos).to<Units::ScenePixels>();
            drawPoints.emplace_back(world.x, world.y);
        }

        const double radAngle = Utils::Math::convertToRadian(-m_angle);
        const double cosAngle = std::cos(radAngle);
        const double sinAngle = std::sin(radAngle);
        UnitVector topPos;
        this->transformRef(topPos, Referential::Top, ConversionType::From);
        topPos = topPos.to<Units::ScenePixels>();
        topPos += dPos;
        UnitVector vec = topPos;
        UnitVector result;
        double dy = m_size.y / 4;
        result.x = (-dy * sinAngle) * -1;
        result.y = (dy * cosAngle) * -1;
        vec += result;
        Graphics::Utils::drawPoint(vec.x - r, vec.y - r, r, sf::Color::White);
        Graphics::Utils::drawLine(vec.x, vec.y, topPos.x, topPos.y, 2, sf::Color::White);

        Graphics::Utils::drawPolygon(drawPoints,
            { { "lines", true }, { "points", true }, { "radius", r },
                { "point_color", sf::Color::White }, { "point_color_0", sf::Color::Red },
                { "point_color_1", sf::Color(255, 128, 0) }, { "point_color_2", sf::Color::Yellow },
                { "point_color_3", sf::Color(128, 255, 0) }, { "point_color_4", sf::Color::Green },
                { "point_color_5", sf::Color(0, 255, 128) },
                { "point_color_6", sf::Color::Magenta },
                { "point_color_7", sf::Color(0, 128, 255) },
                { "point_color_8", sf::Color::White } });
    }

    void Rect::setPointPosition(const UnitVector& position, Referential ref)
    {
        UnitVector refPosition = this->getPosition(ref);
        UnitVector oppositePointPosition = this->getPosition(ref.flip());
        double radAngle = Utils::Math::convertToRadian(-m_angle);
        UnitVector movedPoint = rotatePointAroundCenter(position, oppositePointPosition, -radAngle);

        this->setPosition(position, ref);

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

    UnitVector Rect::getPosition(Referential ref) const
    {
        UnitVector getPosVec = m_position;
        this->transformRef(getPosVec, ref, ConversionType::From);
        return getPosVec;
    }

    void Rect::setPosition(const UnitVector& position, Referential ref)
    {
        UnitVector pVec = position.to<Units::SceneUnits>();
        this->transformRef(pVec, ref, ConversionType::To);
        m_position.set(pVec);
    }

    void Rect::setSize(const UnitVector& size, Referential ref)
    {
        const UnitVector savePosition = this->getPosition(ref);
        m_size.set(size);
        this->setPosition(savePosition, ref);
    }

    void Rect::setPosition(const UnitVector& position)
    {
        this->setPosition(position, Referential::TopLeft);
    }

    UnitVector Rect::getPosition() const
    {
        return this->getPosition(Referential::TopLeft);
    }

    void Rect::move(const UnitVector& position)
    {
        m_position += position;
    }

    void Rect::scale(const UnitVector& size, Referential ref)
    {
        const UnitVector savePosition = this->getPosition(ref);
        m_size *= size;
        this->setPosition(savePosition, ref);
    }

    UnitVector Rect::getSize() const
    {
        return m_size;
    }

    void Rect::movePoint(const UnitVector& position, Referential ref)
    {
    }

    UnitVector Rect::getScaleFactor() const
    {
        return UnitVector(Utils::Math::sign(m_size.x), Utils::Math::sign(m_size.y));
    }
} // namespace obe::Transform