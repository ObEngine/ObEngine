#include <SFML/Graphics/RenderWindow.hpp>

#include <Graphics/DrawUtils.hpp>
#include <Transform/Rect.hpp>
#include <Types/Any.hpp>
#include <Utils/MathUtils.hpp>
#include <iostream>

namespace obe
{
    namespace Transform
    {
        Rect::Rect(MovableType type, const std::string& id) : Movable(type, id)
        {

        }

        float Rect::getRotation() const
        {
            return m_angle;
        }

        /**
        * \brief Sets the angle of the PolygonalCollider (will rotate all points around the given origin)
        * \param angle Angle to set to the PolygonalCollider
        * \param origin Origin to rotate all the points around
        */
        void Rect::setRotation(float angle, Transform::UnitVector origin)
        {
            rotate(angle - m_angle, origin);
        }

        void Rect::rotate(float angle, Transform::UnitVector origin)
        {
            double radAngle = (Utils::Math::pi / 180.0) * -angle;
            double cY = cos(radAngle);
            double sY = sin(radAngle);

            UnitVector delta = m_position - origin;
            m_position.x = (delta.x * cY - delta.y * sY) + origin.x;
            m_position.y = (delta.x * sY + delta.y * cY) + origin.y;

            m_angle += angle;
        }

        void Rect::transformRef(UnitVector& vec, Referencial ref, ConversionType type) const
        {
            double factor = (type == ConversionType::From) ? 1.0 : -1.0;

            //calc once
            double radAngle = (Utils::Math::pi / 180.0) * -m_angle;
            double cY = cos(radAngle);
            double sY = sin(radAngle);
            double dx, dy;
            UnitVector result;

            switch (ref)
            {
            case Referencial::TopLeft:
                dx = 0;
                dy = 0;
                break;

            case Referencial::Top:
                dx = m_size.x / 2;
                dy = 0;
                break;

            case Referencial::TopRight:
                dx = m_size.x;
                dy = 0;
                break;

            case Referencial::Left:
                dx = 0;
                dy = m_size.y / 2;
                break;

            case Referencial::Center:
                dx = m_size.x / 2;
                dy = m_size.y / 2;
                break;

            case Referencial::Right:
                dx = m_size.x;
                dy = m_size.y / 2;
                break;

            case Referencial::BottomLeft:
                dx = 0;
                dy = m_size.y;
                break;

            case Referencial::Bottom:
                dx = m_size.x / 2;
                dy = m_size.y;
                break;

            case Referencial::BottomRight:
                dx = m_size.x;
                dy = m_size.y;
                break;

            default:
                break;
            }
            result.x = (dx * cY - dy * sY) * factor;
            result.y = (dx * sY + dy * cY) * factor;
            vec.add(result);
        }

        void Rect::display(sf::RenderWindow& target, unsigned int posX, unsigned int posY) const
        {
            int r = 6;
            std::map<std::string, Types::Any> drawOptions;

            drawOptions["lines"] = true;
            drawOptions["points"] = true;
            drawOptions["radius"] = r;
            drawOptions["point_color"] = sf::Color::White;

            std::vector<sf::Vector2i> drawPoints;

            drawOptions["point_color_0"] = sf::Color(255, 0, 0);
            drawOptions["point_color_1"] = sf::Color(255, 128, 0);
            drawOptions["point_color_2"] = sf::Color(255, 255, 0);
            drawOptions["point_color_3"] = sf::Color(128, 255, 0);
            drawOptions["point_color_4"] = sf::Color(0, 255, 0);
            drawOptions["point_color_5"] = sf::Color(0, 255, 128);
            drawOptions["point_color_6"] = sf::Color(0, 255, 255);
            drawOptions["point_color_7"] = sf::Color(0, 128, 255);
            drawOptions["point_color_8"] = sf::Color(0, 0, 255);

            UnitVector dPos(posX, posY, Transform::Units::WorldPixels);

            const std::vector<Referencial> realOrder = 
              { Referencial::TopLeft, Referencial::Top, Referencial::TopRight, 
                Referencial::Right, Referencial::BottomRight,
                Referencial::Bottom, Referencial::BottomLeft, Referencial::Left };
            for (uint16_t i = 0; i < 8; ++i)
            {
                UnitVector pt;
                this->transformRef(pt, realOrder.at(i), ConversionType::From);
                UnitVector world = (pt + dPos).to<Units::WorldPixels>();
                drawPoints.emplace_back(world.x, world.y);
            }

            Graphics::Utils::drawPolygon(target, drawPoints, drawOptions);
        }

        void Rect::setPointPosition(const UnitVector& position, Referencial ref)
        {
            UnitVector oppositePointPosition = this->getPosition(reverseReferencial(ref));

            auto rotatePointFromAngle = [=](const UnitVector& center, const UnitVector& Around, float angle)
            {
                double cY = cos(angle);
                double sY = sin(angle);

                UnitVector moved, delta = Around - center;
                moved.x = (delta.x * cY - delta.y * sY) + center.x;
                moved.y = (delta.x * sY + delta.y * cY) + center.y;

                return moved;
            };
            UnitVector movedPoint = rotatePointFromAngle(position, oppositePointPosition, (-m_angle));
            UnitVector newSize = movedPoint - position;


            if (isOnCorner(ref))
            {
                this->setPosition(position, ref);
                this->setSize(newSize, ref);
            }
            else if (isOnLeftSide(ref) || isOnRightSide(ref))
            {
                UnitVector cPos(position.to(m_position.unit).x, this->getPosition(ref).y, m_position.unit);
                this->setPosition(cPos, ref);
                newSize.y = m_size.y;
                this->setSize(newSize, ref);
            }
            else if (isOnTopSide(ref) || isOnBottomSide(ref))
            {
                UnitVector cPos(this->getPosition(ref).x, position.to(m_position.unit).y, m_position.unit);
                this->setPosition(cPos, ref);
                newSize.x = m_size.x;
                this->setSize(newSize, ref);
            }
            /*UnitVector oppositePointPosition = this->getPosition(reverseReferencial(ref));
            UnitVector newSize = (oppositePointPosition - position) * getReferencialOffset(ref);
            if (isOnCorner(ref))
            {
                this->setPosition(position, ref);
                this->setSize(newSize, ref);
            }
            else if (isOnLeftSide(ref) || isOnRightSide(ref))
            {
                UnitVector cPos(position.to(m_position.unit).x, this->getPosition(ref).y, m_position.unit);
                this->setPosition(cPos, ref);
                newSize.y = m_size.y;
                this->setSize(newSize, ref);
            }
            else if (isOnTopSide(ref) || isOnBottomSide(ref))
            {
                UnitVector cPos(this->getPosition(ref).x, position.to(m_position.unit).y, m_position.unit);
                this->setPosition(cPos, ref);
                newSize.x = m_size.x;
                this->setSize(newSize, ref);
            }*/
        }

        UnitVector Rect::getPosition(Referencial ref) const
        {
            UnitVector getPosVec = m_position;
            this->transformRef(getPosVec, ref, ConversionType::From);
            return getPosVec;
        }

        void Rect::setPosition(const UnitVector& position, Referencial ref)
        {
            UnitVector pVec = position.to<Units::WorldUnits>();
            this->transformRef(pVec, ref, ConversionType::To);
            m_position.set(pVec);
        }

        void Rect::setSize(const UnitVector& size, Referencial ref)
        {
            UnitVector savePosition = this->getPosition(ref);
            m_size.set(size);
            this->setPosition(savePosition, ref);
        }

        void Rect::setPosition(const UnitVector& position)
        {
            this->setPosition(position, Referencial::TopLeft);
        }

        UnitVector Rect::getPosition() const
        {
            return this->getPosition(Referencial::TopLeft);
        }   

        void Rect::move(const UnitVector& position)
        {
            m_position += position;
        }

        void Rect::scale(const UnitVector& size, Referencial ref)
        {
            UnitVector savePosition = this->getPosition(ref);
            m_size *= size;
            this->setPosition(savePosition, ref);
        }

        UnitVector Rect::getSize() const
        {
            return m_size;
        }

        void Rect::movePoint(const UnitVector& position, Referencial ref)
        {
        }

        UnitVector Rect::getScaleFactor() const
        {
            return UnitVector(Utils::Math::sign(m_size.x), Utils::Math::sign(m_size.y));
        }
    }
}
