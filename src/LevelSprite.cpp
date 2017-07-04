//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "LevelSprite.hpp"

namespace obe
{
    namespace Graphics
    {
        LevelSprite::LevelSprite(std::string id) : Selectable(false)
        {
            m_id = id;
            m_drawable = false;
        }

        void LevelSprite::load(std::string path)
        {
            if (path != "")
            {
                m_path = path;
                System::Path(path).loadResource(&m_texture, System::Loaders::textureLoader);
                m_returnSprite.setTexture(m_texture);
            }
        }

        void LevelSprite::setSprite(sf::Sprite* spr)
        {
            m_returnSprite.copyFromSprite(*spr);
            int rotOrigX = static_cast<double>(getWidth()) / 2.0;
            int rotOrigY = static_cast<double>(getHeight()) / 2.0;
            this->setRotationOrigin(rotOrigX, rotOrigY);
        }

        void LevelSprite::setTexture(sf::Texture texture)
        {
            m_texture = texture;
            m_returnSprite = sfe::ComplexSprite(m_texture);
        }

        sf::Texture& LevelSprite::getTexture()
        {
            return m_texture;
        }

        void LevelSprite::setLayer(int layer)
        {
            m_layer = layer;
        }

        void LevelSprite::setZDepth(int zdepth)
        {
            m_zdepth = zdepth;
        }

        void LevelSprite::setAtr(std::vector<std::string> atrList)
        {
            m_currentAtr = atrList;
        }

        void LevelSprite::addAtr(std::string atr)
        {
            m_currentAtr.push_back(atr);
        }

        void LevelSprite::removeAtrByIndex(int index)
        {
            m_currentAtr.erase(m_currentAtr.begin() + index);
        }

        void LevelSprite::removeAtrByName(std::string name)
        {
            m_currentAtr.erase(remove(m_currentAtr.begin(), m_currentAtr.end(), name), m_currentAtr.end());
        }

        void LevelSprite::setRotation(double rotate)
        {
            m_rotation = rotate;
            m_returnSprite.setRotation(m_rotation);
        }

        void LevelSprite::rotate(double addRotate)
        {
            m_rotation += addRotate;
            if (m_rotation < 0) m_rotation += 360;
            m_rotation = (static_cast<int>(m_rotation) % 360) + (m_rotation - floor(m_rotation));
            m_returnSprite.setRotation(m_rotation);
        }

        void LevelSprite::setScalingOrigin(int x, int y)
        {
            m_originScaX = x;
            m_originScaY = y;
            m_returnSprite.setScalingOrigin(x, y);
        }

        void LevelSprite::drawHandle(sf::RenderWindow& target, int spritePositionX, int spritePositionY)
        {
            std::map<std::string, obe::Types::any> drawOptions;

            drawOptions["lines"] = true;
            drawOptions["points"] = true;
            drawOptions["radius"] = m_handlePointRadius;
            drawOptions["point_color"] = sf::Color::White;

            std::vector<sf::Vector2i> drawPoints;
            Coord::UnitVector spriteSize = m_size.to<Coord::Units::WorldPixels>();

            drawOptions["point_color_0"] = sf::Color(255, 0, 0);
            drawOptions["point_color_1"] = sf::Color(255, 128, 0);
            drawOptions["point_color_2"] = sf::Color(255, 255, 0);
            drawOptions["point_color_3"] = sf::Color(128, 255, 0);
            drawOptions["point_color_4"] = sf::Color(0, 255, 0);
            drawOptions["point_color_5"] = sf::Color(0, 255, 128);
            drawOptions["point_color_6"] = sf::Color(0, 255, 255);
            drawOptions["point_color_7"] = sf::Color(0, 128, 255);
            drawOptions["point_color_8"] = sf::Color(0, 0, 255);

            Coord::UnitVector pixelPosition(spritePositionX, spritePositionY, Coord::Units::WorldPixels);
            drawPoints.emplace_back(pixelPosition.x + m_handlePointRadius, pixelPosition.y + m_handlePointRadius);
            drawPoints.emplace_back(pixelPosition.x + spriteSize.x / 2, pixelPosition.y + m_handlePointRadius);
            drawPoints.emplace_back(pixelPosition.x + spriteSize.x - m_handlePointRadius, pixelPosition.y + m_handlePointRadius);
            drawPoints.emplace_back(pixelPosition.x + spriteSize.x - m_handlePointRadius, pixelPosition.y + spriteSize.y / 2);
            drawPoints.emplace_back(pixelPosition.x + spriteSize.x - m_handlePointRadius, pixelPosition.y + spriteSize.y - m_handlePointRadius);
            drawPoints.emplace_back(pixelPosition.x + spriteSize.x / 2, pixelPosition.y + spriteSize.y - m_handlePointRadius);
            drawPoints.emplace_back(pixelPosition.x + m_handlePointRadius, pixelPosition.y + spriteSize.y - m_handlePointRadius);
            drawPoints.emplace_back(pixelPosition.x + m_handlePointRadius, pixelPosition.y + spriteSize.y / 2);

            Utils::drawPolygon(target, drawPoints, drawOptions);
        }

        void LevelSprite::getHandlePoint(Coord::UnitVector& cameraPosition, int posX, int posY)
        {
            Coord::UnitVector drawPosition = this->getDrawPosition(cameraPosition);
            Coord::Rect handleRect;
            handleRect.setPosition(drawPosition + Coord::UnitVector(m_handlePointRadius, m_handlePointRadius, Coord::Units::WorldPixels));
            handleRect.setSize(m_size - Coord::UnitVector(2 * m_handlePointRadius, 2 * m_handlePointRadius, Coord::Units::WorldPixels));
            for (int i = 0; i < 9; i++)
            {
                Coord::Referencial refIndex = static_cast<Coord::Referencial>(i);
                std::cout << refIndex << std::endl;
                Coord::UnitVector refPoint = handleRect.getPosition(refIndex).to<Coord::Units::WorldPixels>();
                std::cout << refPoint.x - (m_handlePointRadius / 2) << " <= " << posX << " <= " << refPoint.x + (m_handlePointRadius / 2) << std::endl;
                if (Functions::Math::isBetween(posX, refPoint.x - m_handlePointRadius, refPoint.x + m_handlePointRadius))
                {
                    if (Functions::Math::isBetween(posY, refPoint.y - m_handlePointRadius, refPoint.y + m_handlePointRadius))
                    {
                        std::cout << "CLICKED POINT" << std::endl;
                    }
                }
            }
        }

        void LevelSprite::setTranslationOrigin(int x, int y)
        {
            m_originTraX = x;
            m_originTraY = y;
            m_returnSprite.setTranslationOrigin(m_originTraX, m_originTraY);
        }

        void LevelSprite::setRotationOrigin(int x, int y)
        {
            m_originRotX = x;
            m_originRotY = y;
            m_returnSprite.setRotationOrigin(m_originRotX, m_originRotY);
        }

        void LevelSprite::applySize()
        {
            std::cout << "Applying Size of " << m_id << std::endl;
            Coord::UnitVector pixelSize = m_size.to<Coord::Units::WorldPixels>();
            double spriteWidth = this->getSpriteWidth() * Functions::Math::sign(m_returnSprite.getScale().x); 
            double spriteHeight = this->getSpriteHeight() * Functions::Math::sign(m_returnSprite.getScale().y); 
            /*std::cout << "Apply size : " << pixelSize << " for LevelSprite " << m_id << std::endl;*/
            std::cout << "Before : " << spriteWidth << ", " << spriteHeight << std::endl;
            std::cout << "From : " << pixelSize << std::endl;
            std::cout << "Equals to : " << pixelSize.x / spriteWidth << ", " << pixelSize.y / spriteHeight << std::endl;
            m_returnSprite.scale(pixelSize.x / spriteWidth, pixelSize.y / spriteHeight);
            std::cout << "It gives scale : " << this->getSpriteWidth() << ", " << this->getSpriteHeight() << std::endl;
        }

        void LevelSprite::setColor(sf::Color newColor)
        {
            m_returnSprite.setColor(newColor);
        }

        sfe::ComplexSprite& LevelSprite::getSprite()
        {
            this->applySize();
            //this->applySize();
            //std::cout << "Rect of LevelSprite : " << m_position << ", " << m_size << std::endl;
            //std::cout << "And real size is : " << m_returnSprite.getGlobalBounds().width << ", " << m_returnSprite.getGlobalBounds().height << std::endl;
            //std::cout << "From scale : " << m_returnSprite.getScale().x << ", " << m_returnSprite.getScale().y << std::endl;
            return m_returnSprite;
        }

        double LevelSprite::getSpriteWidth()
        {
            return m_returnSprite.getGlobalBounds().width;
        }

        double LevelSprite::getSpriteHeight()
        {
            return m_returnSprite.getGlobalBounds().height;
        }

        Coord::UnitVector LevelSprite::getDrawPosition(Coord::UnitVector& cameraPosition)
        {
            Coord::UnitVector pixelPosition = m_position.to<Coord::Units::WorldPixels>();

            int layeredX = (pixelPosition.x * m_layer -
                cameraPosition.x) / m_layer;
            int layeredY = (pixelPosition.y * m_layer -
                cameraPosition.y) / m_layer;
            if (Functions::Vector::isInList(static_cast<std::string>("+FIX"), m_currentAtr))
            {
                layeredX = pixelPosition.x;
                layeredY = pixelPosition.y;
            }
            else if (Functions::Vector::isInList(static_cast<std::string>("+HFIX"), m_currentAtr))
            {
                layeredX = pixelPosition.x;
            }
            else if (Functions::Vector::isInList(static_cast<std::string>("+VFIX"), m_currentAtr))
            {
                layeredY = pixelPosition.y;
            }
            else if (Functions::Vector::isInList(static_cast<std::string>("+PHFIX"), m_currentAtr))
            {
                layeredX = pixelPosition.x - cameraPosition.x;
            }
            else if (Functions::Vector::isInList(static_cast<std::string>("+PVFIX"), m_currentAtr))
            {
                layeredY = pixelPosition.y - cameraPosition.y;
            }
            else if (Functions::Vector::isInList(static_cast<std::string>("+PFIX"), m_currentAtr))
            {
                layeredX = pixelPosition.x - cameraPosition.x;
                layeredY = pixelPosition.y - cameraPosition.y;
            }
            
            return Coord::UnitVector(layeredX, layeredY, Coord::Units::WorldPixels);
        }

        float LevelSprite::getRotation() const
        {
            return m_rotation;
        }

        int LevelSprite::getLayer() const
        {
            return m_layer;
        }

        int LevelSprite::getZDepth() const
        {
            return m_zdepth;
        }

        std::string LevelSprite::getID() const
        {
            return m_id;
        }

        std::string LevelSprite::getPath() const
        {
            return m_path;
        }

        std::vector<std::string> LevelSprite::getAttributes() const
        {
            return m_currentAtr;
        }

        sf::FloatRect LevelSprite::getRect()
        {
            m_returnSprite.setTranslationOrigin(m_originTraX, m_originTraY);
            m_returnSprite.setRotationOrigin(m_originRotX, m_originRotY);

            Coord::UnitVector realPosition = m_position.to<Coord::Units::WorldPixels>();

            m_returnSprite.setPosition(realPosition.x, realPosition.y);
            m_returnSprite.setRotation(m_rotation);
            sf::FloatRect mrect = sf::FloatRect(realPosition.x, realPosition.y, m_returnSprite.getGlobalBounds().width, m_returnSprite.getGlobalBounds().height);
            mrect.left = m_returnSprite.getGlobalBounds().left;
            mrect.top = m_returnSprite.getGlobalBounds().top;
            return mrect;
        }

        bool LevelSprite::isDrawable() const
        {
            return m_drawable;
        }

        void LevelSprite::setVisible(bool visible)
        {
            m_visible = visible;
        }

        bool LevelSprite::isVisible() const
        {
            return m_visible;
        }

        std::string LevelSprite::getParentID() const
        {
            return m_parentID;
        }

        void LevelSprite::setParentID(std::string parent)
        {
            m_parentID = parent;
        }

        LevelSprite::HandlePoint::HandlePoint(LevelSprite* parent, Coord::Referencial ref)
        {
            m_parent = parent;
            m_referencial = ref;
            switch (ref)
            {
            case Coord::Referencial::TopLeft: m_changeWidthFactor = -1; m_changeHeightFactor = -1; break;
            case Coord::Referencial::TopRight: m_changeWidthFactor = 1; m_changeHeightFactor = -1; break;
            case Coord::Referencial::Center: /* RAISE ERROR HERE */ break;
            case Coord::Referencial::BottomLeft: m_changeWidthFactor = -1; m_changeHeightFactor = 1; break;
            case Coord::Referencial::BottomRight: m_changeWidthFactor = 1; m_changeHeightFactor = 1; break;
            case Coord::Referencial::Top: m_changeWidthFactor = 0; m_changeHeightFactor = -1; break;
            case Coord::Referencial::Left: m_changeWidthFactor = -1; m_changeHeightFactor = 0; break;
            case Coord::Referencial::Right: m_changeWidthFactor = 1; m_changeHeightFactor = 0; break;
            case Coord::Referencial::Bottom: m_changeWidthFactor = 0; m_changeHeightFactor = 1; break;
            default: ;
            }
}

        void LevelSprite::HandlePoint::moveTo(int x, int y)
        {
            int diffX = (m_x - x) * m_changeWidthFactor;
            int diffY = (m_y - y) * m_changeHeightFactor;
            m_x = x;
            m_y = y;
            Coord::UnitVector scaleParent(diffX, diffY, Coord::Units::WorldPixels);
            m_parent->setScalingOrigin(m_parent->getWidth() / 2, m_parent->getWidth() / 2);
            m_parent->scale(scaleParent);
        }
    }
}
