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
        UnitVector rotatePointAroundCenter(const UnitVector& center, const UnitVector& Around, float angle)
        {
            double cY = cos(angle);
            double sY = sin(angle);

            UnitVector moved, delta = Around - center;
            moved.x = (delta.x * cY - delta.y * sY) + center.x;
            moved.y = (delta.x * sY + delta.y * cY) + center.y;

            return moved;
        };

        Rect::Rect(MovableType type, const std::string& id) : Movable(type, id)
        {
        }

        float Rect::getRotation() const
        {
            return m_angle;
        }

        void Rect::setRotation(float angle, Transform::UnitVector origin)
        {
            std::cout << "@ThisPoint : " << m_position << std::endl;
            rotate(angle - m_angle, origin);
        }

        void Rect::rotate(float angle, Transform::UnitVector origin)
        {
            double radAngle = Utils::Math::convertToRadian(angle);
            
            m_position = rotatePointAroundCenter(origin, m_position, radAngle);
            m_angle += angle;
            if (m_angle < 0 || m_angle > 360)
                m_angle = Utils::Math::normalise(m_angle, 0, 360);
        }

        //TODO remove calculation when dx and dy are equal to 0. Directly add to vec in switch case.
        void Rect::transformRef(UnitVector& vec, Referencial ref, ConversionType type) const
        {
            double factor = (type == ConversionType::From) ? 1.0 : -1.0;
            double dx, dy;
            double radAngle = Utils::Math::convertToRadian(m_angle);
            double cosAngle = std::cos(radAngle);
            double sinAngle = std::sin(radAngle);
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
            result.x = (dx * cosAngle - dy * sinAngle) * factor;
            result.y = (dx * sinAngle + dy * cosAngle) * factor;
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

            const std::vector<Referencial> fixDisplayOrder =
            { Referencial::TopLeft, Referencial::Top, Referencial::TopRight,
                Referencial::Right, Referencial::BottomRight,
                Referencial::Bottom, Referencial::BottomLeft, Referencial::Left };

            for (uint8_t i = 0; i < 8; ++i)
            {
                UnitVector pt;
                this->transformRef(pt, fixDisplayOrder[i], ConversionType::From);

                UnitVector world = (pt + dPos).to<Units::WorldPixels>();
                drawPoints.emplace_back(world.x, world.y);
            }

            Graphics::Utils::drawPolygon(target, drawPoints, drawOptions);
        }


        void Rect::setPointPosition(const UnitVector& position, Referencial ref)
        {
            UnitVector refPosition = this->getPosition(ref);
            UnitVector oppositePointPosition = this->getPosition(reverseReferencial(ref));
            double radAngle = Utils::Math::convertToRadian(m_angle);
            UnitVector movedPoint = rotatePointAroundCenter(position, oppositePointPosition, -radAngle);

            this->setPosition(position, ref);

            if (isOnCorner(ref))
            {
                if (isOnTopSide(ref))
                {
                    this->setSize({ movedPoint.x - position.x , movedPoint.y - position.y }, ref);
                }
                else
                {
                    this->setSize({ position.x - movedPoint.x, position.y - movedPoint.y }, ref);
                }
            }
            if (isOnLeftSide(ref) || isOnRightSide(ref))
            {
                if (isOnLeftSide(ref))
                {
                    this->setSize({ movedPoint.x - position.x , m_size.y }, ref);
                }
                else
                {
                    this->setSize({ position.x - movedPoint.x, m_size.y }, ref);
                }
            }
            else // we are on TopSide or LeftSide here, no need to specify the condition [Retard Sygmei] 
            {
                if (isOnTopSide(ref))
                {
                    this->setSize({ m_size.x, movedPoint.y - position.y }, ref);
                }
                else
                {
                    this->setSize({ m_size.x, position.y - movedPoint.y }, ref);
                }
            }
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