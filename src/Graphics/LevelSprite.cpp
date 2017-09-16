#include <Graphics/LevelSprite.hpp>
#include <Graphics/ResourceManager.hpp>
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
        LevelSprite::LevelSprite(const std::string& id) : Selectable(false), Rect(Transform::MovableType::LevelSprite, id)
        {
            m_texture = ResourceManager::GetInstance()->getTexture("Sprites/Others/notexture.png");
            m_sprite.setTexture(*m_texture);
            for (int i = 0; i < 9; i++)
            {
                Transform::Referencial refIndex = static_cast<Transform::Referencial>(i);
                m_handlePoints.emplace_back(this, refIndex);
            }
            m_handlePoints.emplace_back(this);
        }

        void LevelSprite::useTextureSize()
        {
            sf::Vector2u textureSize = this->getTexture().getSize();
            Transform::UnitVector initialSpriteSize(textureSize.x, textureSize.y, Transform::Units::WorldPixels);
            this->setSize(initialSpriteSize);
        }

        void LevelSprite::applySpriteRotation()
        {
            Transform::UnitVector middle = (this->getSize() / Transform::UnitVector(2, 2)).to<Transform::Units::WorldPixels>();
            middle *= Transform::UnitVector(this->getScaleFactor().x, this->getScaleFactor().y, middle.unit);
            m_sprite.setRotationOrigin(middle.x, middle.y);
            m_sprite.setRotation(-m_angle * this->getScaleFactor().x * this->getScaleFactor().y);
        }

        void LevelSprite::load(const std::string& path)
        {
            if (path != "")
            {
                m_path = path;
                m_texture = ResourceManager::GetInstance()->getTexture(System::Path(path).find());
                
                m_sprite.setTexture(*m_texture);
                m_sprite.setTextureRect(sf::IntRect(0, 0, m_texture->getSize().x, m_texture->getSize().y));
            }
        }

        void LevelSprite::resetUnit(Transform::Units unit)
        {
        }

        void LevelSprite::setTexture(const sf::Texture& texture)
        {
            m_texture = &texture;
            m_sprite.setTexture(texture);
        }

        const sf::Texture& LevelSprite::getTexture() const
        {
            return *m_texture;
        }

        void LevelSprite::setLayer(int layer)
        {
            m_layer = layer;
        }

        void LevelSprite::setZDepth(int zdepth)
        {
            m_zdepth = zdepth;
        }

        void LevelSprite::setRotation(double rotate)
        {
            Rect::setRotation(rotate, this->getPosition(Transform::Referencial::Center));
            this->applySpriteRotation();
        }

        void LevelSprite::rotate(double addRotate)
        {
            Rect::rotate(addRotate, this->getPosition(Transform::Referencial::Center));
            this->applySpriteRotation();
        }

        void LevelSprite::setScalingOrigin(int x, int y)
        {
            m_sprite.setScalingOrigin(x, y);
        }

        void LevelSprite::drawHandle(sf::RenderWindow& target, int spritePositionX, int spritePositionY) const
        {
            Rect::display(target, spritePositionX, spritePositionY);
        }

        LevelSpriteHandlePoint* LevelSprite::getHandlePoint(Transform::UnitVector& cameraPosition, int posX, int posY)
        {
            Transform::UnitVector pixelCamera = cameraPosition.to<Transform::Units::WorldPixels>();
            for (int i = 0; i < 9; i++)
            {
                Transform::Referencial refIndex = static_cast<Transform::Referencial>(i);
                Transform::UnitVector refPoint = Rect::getPosition(refIndex).to<Transform::Units::WorldPixels>();
                int lowerXBound = std::min(refPoint.x - LevelSpriteHandlePoint::radius, refPoint.x + LevelSpriteHandlePoint::radius);
                int upperXBound = std::max(refPoint.x - LevelSpriteHandlePoint::radius, refPoint.x + LevelSpriteHandlePoint::radius);
                if (obe::Utils::Math::isBetween(posX + pixelCamera.x, lowerXBound, upperXBound) && refIndex != Transform::Referencial::Center)
                {
                    int lowerYBound = std::min(refPoint.y - LevelSpriteHandlePoint::radius, refPoint.y + LevelSpriteHandlePoint::radius);
                    int upperYBound = std::max(refPoint.y - LevelSpriteHandlePoint::radius, refPoint.y + LevelSpriteHandlePoint::radius);
                    if (obe::Utils::Math::isBetween(posY + pixelCamera.y, lowerYBound, upperYBound))
                        return &m_handlePoints[i];
                }
            }

            double radAngle = obe::Utils::Math::convertToRadian(-m_angle);
            double cosAngle = std::cos(radAngle);
            double sinAngle = std::sin(radAngle);
            Transform::UnitVector topPos = this->getPosition(Transform::Referencial::Top).to<Transform::Units::WorldPixels>();
            Transform::UnitVector rotHandle = topPos;
            Transform::UnitVector result;
            double dy = m_size.y / 4;
            result.x = (-dy * sinAngle) * -1;
            result.y = (dy * cosAngle) * -1;
            rotHandle.add(result);

            int lowerXBound = std::min(rotHandle.x - LevelSpriteHandlePoint::radius, rotHandle.x + LevelSpriteHandlePoint::radius);
            int upperXBound = std::max(rotHandle.x - LevelSpriteHandlePoint::radius, rotHandle.x + LevelSpriteHandlePoint::radius);
            if (obe::Utils::Math::isBetween(posX + pixelCamera.x, lowerXBound, upperXBound))
            {
                int lowerYBound = std::min(rotHandle.y - LevelSpriteHandlePoint::radius, rotHandle.y + LevelSpriteHandlePoint::radius);
                int upperYBound = std::max(rotHandle.y - LevelSpriteHandlePoint::radius, rotHandle.y + LevelSpriteHandlePoint::radius);
                if (obe::Utils::Math::isBetween(posY + pixelCamera.y, lowerYBound, upperYBound))
                    return &m_handlePoints.back();
            }
            return nullptr;
        }

        void LevelSprite::setTranslationOrigin(int x, int y)
        {
            m_sprite.setTranslationOrigin(x, y);
        }

        void LevelSprite::setRotationOrigin(int x, int y)
        {
            m_sprite.setRotationOrigin(x, y);
        }

        void LevelSprite::applySize()
        {
            m_sprite.setRotation(0);
            //std::cout << "Applying Size of " << m_id << std::endl;
            Transform::UnitVector pixelSize = m_size.to<Transform::Units::WorldPixels>();
            double spriteWidth = this->getSpriteWidth() * this->getXScaleFactor();
            double spriteHeight = this->getSpriteHeight() * this->getYScaleFactor();
            sf::Vector2u texSize = m_texture->getSize();
            /*std::cout << "Apply size : " << pixelSize << " for LevelSprite " << m_id << std::endl;
            std::cout << "Before : " << spriteWidth << ", " << spriteHeight << std::endl;
            std::cout << "From : " << pixelSize << std::endl;*/
            double widthScale = pixelSize.x / spriteWidth;
            double heightScale = pixelSize.y / spriteHeight;
            //std::cout << "ISSCALE : " << widthScale << ", " << heightScale << std::endl;
            //std::cout << "ShiftTest : " << (pixelSize.x > 1 || pixelSize.x < -1) << ", " << (pixelSize.y > 1 || pixelSize.y < -1) << std::endl;
            if ((pixelSize.x >= 1 || pixelSize.x <= -1) && (pixelSize.y >= 1 || pixelSize.y <= -1) && (texSize.x >= 1 && texSize.y >= 1))
            {
                m_sprite.scale(widthScale, heightScale);
            }
            this->applySpriteRotation();
        }

        void LevelSprite::setColor(sf::Color newColor)
        {
            m_sprite.setColor(newColor);
        }

        sf::Color LevelSprite::getColor() const
        {
            return m_sprite.getColor();
        }

        sfe::ComplexSprite& LevelSprite::getSprite()
        {
            this->applySize();
            //this->applySize();
            //std::cout << "Rect of LevelSprite : " << m_position << ", " << m_size << std::endl;
            //std::cout << "And real size is : " << m_returnSprite.getGlobalBounds().width << ", " << m_returnSprite.getGlobalBounds().height << std::endl;
            //std::cout << "From scale : " << m_returnSprite.getScale().x << ", " << m_returnSprite.getScale().y << std::endl;
            return m_sprite;
        }

        double LevelSprite::getSpriteWidth() const
        {
            return m_sprite.getGlobalBounds().width;
        }

        double LevelSprite::getSpriteHeight() const
        {
            return m_sprite.getGlobalBounds().height;
        }

        Transform::UnitVector LevelSprite::getDrawPosition(Transform::UnitVector& cameraPosition, Transform::Referencial ref) const
        {
            Transform::UnitVector pixelPosition = this->getPosition(ref).to<Transform::Units::WorldPixels>();
            Transform::UnitVector pixelCamera = cameraPosition.to<Transform::Units::WorldPixels>();

            Transform::UnitVector transformedPosition = m_positionTransformer(pixelPosition, pixelCamera, m_layer);

            return Transform::UnitVector(transformedPosition.x, transformedPosition.y, Transform::Units::ViewPixels);
        }

        int LevelSprite::getLayer() const
        {
            return m_layer;
        }

        int LevelSprite::getZDepth() const
        {
            return m_zdepth;
        }

        std::string LevelSprite::getPath() const
        {
            return m_path;
        }

        void LevelSprite::configure(vili::ComplexNode& configuration)
        {
            std::string spriteXTransformer;
            std::string spriteYTransformer;
            std::string spriteUnits = configuration.contains(vili::NodeType::ComplexNode, "rect") ?
                configuration.at<vili::DataNode>("rect", "unit").get<std::string>() : "WorldUnits";
            std::string spritePath = configuration.contains(vili::NodeType::DataNode, "path") ?
                configuration.getDataNode("path").get<std::string>() : "";
            Transform::UnitVector spritePos(0, 0);
            Transform::UnitVector spriteSize(1, 1);
            if (configuration.contains(vili::NodeType::ComplexNode, "rect"))
            {
                Transform::Units rectUnit = Transform::stringToUnits(spriteUnits);
                spritePos.unit = rectUnit;
                spritePos.x = configuration.at<vili::DataNode>("rect", "x").get<double>();
                spritePos.y = configuration.at<vili::DataNode>("rect", "y").get<double>();
                spriteSize.unit = rectUnit;
                spriteSize.x = configuration.at<vili::DataNode>("rect", "w").get<double>();
                spriteSize.y = configuration.at<vili::DataNode>("rect", "h").get<double>();
                spritePos = spritePos.to<Transform::Units::WorldUnits>();
                spriteSize = spriteSize.to<Transform::Units::WorldUnits>();
            }
            double spriteRot = configuration.contains(vili::NodeType::DataNode, "rotation") ?
                configuration.getDataNode("rotation").get<double>() : 0;
            int layer = configuration.contains(vili::NodeType::DataNode, "layer") ?
                configuration.getDataNode("layer").get<int>() : 1;
            int zdepth = configuration.contains(vili::NodeType::DataNode, "z-depth") ?
                configuration.getDataNode("z-depth").get<int>() : 1;

            if (configuration.contains(vili::NodeType::DataNode, "xTransform"))
                spriteXTransformer = configuration.at<vili::DataNode>("xTransform").get<std::string>();
            else
                spriteXTransformer = "Position";
            if (configuration.contains(vili::NodeType::DataNode, "yTransform"))
                spriteYTransformer = configuration.at<vili::DataNode>("yTransform").get<std::string>();
            else
                spriteYTransformer = "Position";

            if (spritePath != "")
                this->load(spritePath);
            this->setPosition(spritePos);
            this->setSize(spriteSize);
            this->setWorkingUnit(Transform::stringToUnits(spriteUnits));
            PositionTransformer positionTransformer(spriteXTransformer, spriteYTransformer);
            this->setPositionTransformer(positionTransformer);
            this->setLayer(layer);
            this->setZDepth(zdepth);
            this->setRotation(spriteRot);
            this->applySpriteRotation();
        }

        sf::FloatRect LevelSprite::getRect()
        {
            Transform::UnitVector realPosition = Rect::m_position.to<Transform::Units::WorldPixels>();

            m_sprite.setPosition(realPosition.x, realPosition.y);
            sf::FloatRect mrect = sf::FloatRect(realPosition.x, realPosition.y, m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height);
            mrect.left = m_sprite.getGlobalBounds().left;
            mrect.top = m_sprite.getGlobalBounds().top;
            return mrect;
        }

        void LevelSprite::setVisible(bool visible)
        {
            m_visible = visible;
        }

        bool LevelSprite::isVisible() const
        {
            return m_visible;
        }

        std::string LevelSprite::getParentId() const
        {
            return m_parentId;
        }

        void LevelSprite::setParentId(const std::string& parent)
        {
            m_parentId = parent;
        }

        int LevelSprite::getXScaleFactor() const
        {
            return obe::Utils::Math::sign(m_sprite.getScale().x);
        }

        int LevelSprite::getYScaleFactor() const
        {
            return obe::Utils::Math::sign(m_sprite.getScale().y);
        }

        void LevelSprite::setPositionTransformer(PositionTransformer transformer)
        {
            m_positionTransformer = transformer;
        }

        PositionTransformer LevelSprite::getPositionTransformer() const
        {
            return m_positionTransformer;
        }

        unsigned int LevelSpriteHandlePoint::radius = 6;
        LevelSpriteHandlePoint::LevelSpriteHandlePoint(Transform::Rect* parentRect, Transform::Referencial ref)
        {
            m_rect = parentRect;
            m_referencial = ref;
            m_type = LevelSpriteHandlePointType::ScaleHandle;
        }

        LevelSpriteHandlePoint::LevelSpriteHandlePoint(Transform::Rect* parentRect)
        {
            m_rect = parentRect;
            m_type = LevelSpriteHandlePointType::RotateHandle;
        }

        void LevelSpriteHandlePoint::moveTo(int x, int y)
        {
            if (m_type == LevelSpriteHandlePointType::ScaleHandle)
            {
                //std::cout << "Was at : " << m_rect->getPosition(m_referencial).to<Transform::Units::WorldPixels>() << std::endl;
                //std::cout << "Set : " << x << ", " << y << std::endl;
                m_dp = Transform::UnitVector(x, y, Transform::Units::WorldPixels);
                float angle = m_rect->getRotation();
                Transform::UnitVector pos = m_rect->getPosition(m_referencial).to<Transform::Units::WorldPixels>();
                Transform::UnitVector constrainedPos(Transform::Units::WorldPixels);
                Transform::UnitVector oppositePos = m_rect->getPosition(Transform::reverseReferencial(m_referencial)).to<Transform::Units::WorldPixels>();

                if (Transform::isOnCorner(m_referencial))
                {
                    Transform::UnitVector oppositePos = m_rect->getPosition(Transform::reverseReferencial(m_referencial)).to<Transform::Units::WorldPixels>();
                    Transform::UnitVector baseDist = oppositePos - m_dp;
                    Transform::UnitVector scaleVector = baseDist / m_rect->getSize().to<Transform::Units::WorldPixels>();
                    scaleVector.set((isOnRightSide(m_referencial)) ? -scaleVector.x : scaleVector.x, (isOnBottomSide(m_referencial)) ? -scaleVector.y : scaleVector.y);
                    double vScale = std::max(scaleVector.x, scaleVector.y);
                    if (baseDist.x != 0 && baseDist.y != 0)
                        m_rect->scale(Transform::UnitVector(vScale, vScale, m_rect->getSize().unit), Transform::reverseReferencial(m_referencial));
                }
                else
                {
                    float e1_x = oppositePos.x - pos.x;
                    float e1_y = oppositePos.y - pos.y;
                    float e2_x = x - pos.x;
                    float e2_y = y - pos.y;

                    float valDp = e1_x * e2_x + e1_y * e2_y;
                    float len = e1_x * e1_x + e1_y * e1_y;

                    m_dp.x = pos.x + (valDp * e1_x) / len;
                    m_dp.y = pos.y + (valDp * e1_y) / len;

                    m_rect->setPointPosition(m_dp, m_referencial);
                }
            }
            else
            {
                Transform::UnitVector center = m_rect->getPosition(Transform::Referencial::Center).to<Transform::Units::WorldPixels>();
                double n = (90 + ((m_rect->getScaleFactor().y < 0) ? 180 : 0)) - (std::atan2(center.y - y, center.x - x)) * 180.0 / obe::Utils::Math::pi;

                m_rect->setRotation(std::fmod(n, 360), m_rect->getPosition(Transform::Referencial::Center));
            }
        }

        Transform::Referencial LevelSpriteHandlePoint::getReferencial() const
        {
            return m_referencial;
        }

        LevelSpriteHandlePointType LevelSpriteHandlePoint::getType() const
        {
            return m_type;
        }

        Transform::Rect& LevelSpriteHandlePoint::getRect() const
        {
            return *m_rect;
        }
    }
}
