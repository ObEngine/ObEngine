#include <Graphics/LevelSprite.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>
#include <Types/Any.hpp>
#include <Graphics/DrawUtils.hpp>
#include <Utils/MathUtils.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe
{
    namespace Graphics
    {
        LevelSprite::LevelSprite(std::string id) : Selectable(false)
        {
            m_id = id;
            m_drawable = false;

            for (int i = 0; i < 9; i++)
            {
                Transform::Referencial refIndex = static_cast<Transform::Referencial>(i);
                m_handlePoints.emplace_back(this, refIndex);
            }
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
            std::map<std::string, Types::Any> drawOptions;

            drawOptions["lines"] = true;
            drawOptions["points"] = m_selected;
            drawOptions["radius"] = HandlePoint::radius;
            drawOptions["point_color"] = sf::Color::White;

            std::vector<sf::Vector2i> drawPoints;
            Transform::UnitVector spriteSize = m_size.to<Transform::Units::WorldPixels>();

            drawOptions["point_color_0"] = sf::Color(255, 0, 0);
            drawOptions["point_color_1"] = sf::Color(255, 128, 0);
            drawOptions["point_color_2"] = sf::Color(255, 255, 0);
            drawOptions["point_color_3"] = sf::Color(128, 255, 0);
            drawOptions["point_color_4"] = sf::Color(0, 255, 0);
            drawOptions["point_color_5"] = sf::Color(0, 255, 128);
            drawOptions["point_color_6"] = sf::Color(0, 255, 255);
            drawOptions["point_color_7"] = sf::Color(0, 128, 255);
            drawOptions["point_color_8"] = sf::Color(0, 0, 255);

            int pOffX = this->getXScaleFactor();
            int pOffY = this->getYScaleFactor();

            Transform::UnitVector pixelPosition(spritePositionX, spritePositionY, Transform::Units::WorldPixels);
            drawPoints.emplace_back(pixelPosition.x, pixelPosition.y);
            drawPoints.emplace_back(pixelPosition.x + spriteSize.x / 2, pixelPosition.y);
            drawPoints.emplace_back(pixelPosition.x + spriteSize.x, pixelPosition.y);
            drawPoints.emplace_back(pixelPosition.x + spriteSize.x, pixelPosition.y + spriteSize.y / 2);
            drawPoints.emplace_back(pixelPosition.x + spriteSize.x, pixelPosition.y + spriteSize.y);
            drawPoints.emplace_back(pixelPosition.x + spriteSize.x / 2, pixelPosition.y + spriteSize.y);
            drawPoints.emplace_back(pixelPosition.x, pixelPosition.y + spriteSize.y);
            drawPoints.emplace_back(pixelPosition.x, pixelPosition.y + spriteSize.y / 2);

            Utils::drawPolygon(target, drawPoints, drawOptions);
        }

        LevelSprite::HandlePoint* LevelSprite::getHandlePoint(Transform::UnitVector& cameraPosition, int posX, int posY)
        {
            for (int i = 0; i < 9; i++)
            {
                Transform::Referencial refIndex = static_cast<Transform::Referencial>(i);
                Transform::UnitVector refPoint = this->getPosition(refIndex).to<Transform::Units::WorldPixels>();
                int lowerXBound = std::min(refPoint.x - HandlePoint::radius, refPoint.x + HandlePoint::radius);
                int upperXBound = std::max(refPoint.x - HandlePoint::radius, refPoint.x + HandlePoint::radius);
                if (obe::Utils::Math::isBetween(posX, lowerXBound, upperXBound) && refIndex != Transform::Referencial::Center)
                {
                    int lowerYBound = std::min(refPoint.y - HandlePoint::radius, refPoint.y + HandlePoint::radius);
                    int upperYBound = std::max(refPoint.y - HandlePoint::radius, refPoint.y + HandlePoint::radius);
                    if (obe::Utils::Math::isBetween(posY, lowerYBound, upperYBound))
                        return &m_handlePoints[i];
                }
            }
            return nullptr;
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
            //std::cout << "Applying Size of " << m_id << std::endl;
            Transform::UnitVector pixelSize = m_size.to<Transform::Units::WorldPixels>();
            double spriteWidth = this->getSpriteWidth() * this->getXScaleFactor(); 
            double spriteHeight = this->getSpriteHeight() * this->getYScaleFactor(); 
            /*std::cout << "Apply size : " << pixelSize << " for LevelSprite " << m_id << std::endl;
            std::cout << "Before : " << spriteWidth << ", " << spriteHeight << std::endl;
            std::cout << "From : " << pixelSize << std::endl;*/
            double widthScale = pixelSize.x / spriteWidth;
            double heightScale = pixelSize.y / spriteHeight;
            //std::cout << "ISSCALE : " << widthScale << ", " << heightScale << std::endl;
            //std::cout << "ShiftTest : " << (pixelSize.x > 1 || pixelSize.x < -1) << ", " << (pixelSize.y > 1 || pixelSize.y < -1) << std::endl;
            if ((pixelSize.x >= 1 || pixelSize.x <= -1) && (pixelSize.y >= 1 || pixelSize.y <= -1))
                m_returnSprite.scale(widthScale, heightScale);
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

        Transform::UnitVector LevelSprite::getDrawPosition(Transform::UnitVector& cameraPosition)
        {
            Transform::UnitVector pixelPosition = m_position.to<Transform::Units::WorldPixels>();

            int layeredX = (pixelPosition.x * m_layer -
                cameraPosition.x) / m_layer;
            int layeredY = (pixelPosition.y * m_layer -
                cameraPosition.y) / m_layer;
            if (obe::Utils::Vector::isInList(static_cast<std::string>("+FIX"), m_currentAtr))
            {
                layeredX = pixelPosition.x;
                layeredY = pixelPosition.y;
            }
            else if (obe::Utils::Vector::isInList(static_cast<std::string>("+HFIX"), m_currentAtr))
            {
                layeredX = pixelPosition.x;
            }
            else if (obe::Utils::Vector::isInList(static_cast<std::string>("+VFIX"), m_currentAtr))
            {
                layeredY = pixelPosition.y;
            }
            else if (obe::Utils::Vector::isInList(static_cast<std::string>("+PHFIX"), m_currentAtr))
            {
                layeredX = pixelPosition.x - cameraPosition.x;
            }
            else if (obe::Utils::Vector::isInList(static_cast<std::string>("+PVFIX"), m_currentAtr))
            {
                layeredY = pixelPosition.y - cameraPosition.y;
            }
            else if (obe::Utils::Vector::isInList(static_cast<std::string>("+PFIX"), m_currentAtr))
            {
                layeredX = pixelPosition.x - cameraPosition.x;
                layeredY = pixelPosition.y - cameraPosition.y;
            }
            
            return Transform::UnitVector(layeredX, layeredY, Transform::Units::WorldPixels);
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

            Transform::UnitVector realPosition = m_position.to<Transform::Units::WorldPixels>();

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

        int LevelSprite::getHandlePointRadius() const
        {
            return HandlePoint::radius;
        }

        int LevelSprite::getXScaleFactor()
        {
            return obe::Utils::Math::sign(m_returnSprite.getScale().x);
        }
        
        int LevelSprite::getYScaleFactor()
        {
            return obe::Utils::Math::sign(m_returnSprite.getScale().y);
        }

        LevelSprite::HandlePoint::HandlePoint(Transform::Rect* parentRect, Transform::Referencial ref)
        {
            m_rect = parentRect;
            m_referencial = ref;
        }

        void LevelSprite::HandlePoint::moveTo(int x, int y)
        {
            std::cout << "Was at : " << m_rect->getPosition(m_referencial).to<Transform::Units::WorldPixels>() << std::endl;
            std::cout << "Set : " << x << ", " << y << std::endl;
            m_rect->setPointPosition(Transform::UnitVector(x, y, Transform::Units::WorldPixels), m_referencial);
            std::cout << "Is now at " << m_rect->getPosition(m_referencial).to<Transform::Units::WorldPixels>() << std::endl;
        }

        Transform::Referencial LevelSprite::HandlePoint::getReferencial() const
        {
            return m_referencial;
        }

        Transform::Rect& LevelSprite::HandlePoint::getRect() const
        {
            return *m_rect;
        }
    }
}
