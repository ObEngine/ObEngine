#include <Graphics/LevelSprite.hpp>
#include <Graphics/ResourceManager.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>
#include <Graphics/DrawUtils.hpp>
#include <Utils/MathUtils.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe
{
    namespace Graphics
    {
        LevelSprite::LevelSprite(const std::string& id) : Selectable(false), Rect(Transform::MovableType::LevelSprite), Identifiable(id)
        {
            m_texture = ResourceManager::GetTexture("Sprites/Others/notexture.png");
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

        void LevelSprite::loadTexture(const std::string& path)
        {
            if (path != "")
            {
                m_path = path;
                std::string fPath = System::Path(path).find();
                m_texture = ResourceManager::GetTexture(fPath);
                
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
            m_sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
        }

        const sf::Texture& LevelSprite::getTexture() const
        {
            return *m_texture;
        }

        void LevelSprite::setLayer(int layer)
        {
            m_layer = layer;
            m_layerChanged = true;
        }

        void LevelSprite::setZDepth(int zdepth)
        {
            m_zdepth = zdepth;
            m_layerChanged = true;
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

        void LevelSprite::drawHandle(int spritePositionX, int spritePositionY) const
        {
            Rect::draw(spritePositionX, spritePositionY);
        }

        LevelSpriteHandlePoint* LevelSprite::getHandlePoint(Transform::UnitVector& cameraPosition, int posX, int posY)
        {
            Transform::UnitVector pixelCamera = cameraPosition.to<Transform::Units::WorldPixels>();
            Transform::UnitVector targetPos = Transform::UnitVector(posX, posY, Transform::Units::WorldPixels);
            targetPos = m_positionTransformer(targetPos, -pixelCamera, m_layer);
            for (int i = 0; i < 9; i++)
            {
                Transform::Referencial refIndex = static_cast<Transform::Referencial>(i);
                Transform::UnitVector refPoint = Rect::getPosition(refIndex).to<Transform::Units::WorldPixels>();
                int lowerXBound = std::min(refPoint.x - LevelSpriteHandlePoint::radius, refPoint.x + LevelSpriteHandlePoint::radius);
                int upperXBound = std::max(refPoint.x - LevelSpriteHandlePoint::radius, refPoint.x + LevelSpriteHandlePoint::radius);
                if (obe::Utils::Math::isBetween(targetPos.x, lowerXBound, upperXBound) && refIndex != Transform::Referencial::Center)
                {
                    int lowerYBound = std::min(refPoint.y - LevelSpriteHandlePoint::radius, refPoint.y + LevelSpriteHandlePoint::radius);
                    int upperYBound = std::max(refPoint.y - LevelSpriteHandlePoint::radius, refPoint.y + LevelSpriteHandlePoint::radius);
                    if (obe::Utils::Math::isBetween(targetPos.y, lowerYBound, upperYBound))
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
            if (obe::Utils::Math::isBetween(targetPos.x, lowerXBound, upperXBound))
            {
                int lowerYBound = std::min(rotHandle.y - LevelSpriteHandlePoint::radius, rotHandle.y + LevelSpriteHandlePoint::radius);
                int upperYBound = std::max(rotHandle.y - LevelSpriteHandlePoint::radius, rotHandle.y + LevelSpriteHandlePoint::radius);
                if (obe::Utils::Math::isBetween(targetPos.y, lowerYBound, upperYBound))
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

            return Transform::UnitVector(transformedPosition.x, transformedPosition.y, Transform::Units::WorldPixels);
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
        LevelSpriteHandlePoint::LevelSpriteHandlePoint(LevelSprite* parent, Transform::Referencial ref)
        {
            m_sprite = parent;
            m_referencial = ref;
            m_type = LevelSpriteHandlePointType::ScaleHandle;
        }

        LevelSpriteHandlePoint::LevelSpriteHandlePoint(LevelSprite* parent)
        {
            m_sprite = parent;
            m_type = LevelSpriteHandlePointType::RotateHandle;
        }

        void LevelSpriteHandlePoint::moveTo(const Transform::UnitVector& position, const Transform::UnitVector& camera)
        {
            if (m_type == LevelSpriteHandlePointType::ScaleHandle)
            {
                //std::cout << "Was at : " << m_rect->getPosition(m_referencial).to<Transform::Units::WorldPixels>() << std::endl;
                //std::cout << "Set : " << x << ", " << y << std::endl;
                m_dp = m_sprite->getPositionTransformer()(position, -camera, m_sprite->getLayer());
                float angle = m_sprite->getRotation();
                Transform::UnitVector pos = m_sprite->getPosition(m_referencial).to<Transform::Units::WorldPixels>();
                Transform::UnitVector constrainedPos(Transform::Units::WorldPixels);
                Transform::UnitVector oppositePos = m_sprite->getPosition(Transform::reverseReferencial(m_referencial)).to<Transform::Units::WorldPixels>();

                if (Transform::isOnCorner(m_referencial))
                {
                    Transform::UnitVector oppositePos = m_sprite->getPosition(Transform::reverseReferencial(m_referencial)).to<Transform::Units::WorldPixels>();
                    Transform::UnitVector baseDist = oppositePos - m_dp;
                    Transform::UnitVector scaleVector = baseDist / m_sprite->getSize().to<Transform::Units::WorldPixels>();
                    scaleVector.set((isOnRightSide(m_referencial)) ? -scaleVector.x : scaleVector.x, (isOnBottomSide(m_referencial)) ? -scaleVector.y : scaleVector.y);
                    double vScale = std::max(scaleVector.x, scaleVector.y);
                    if (baseDist.x != 0 && baseDist.y != 0)
                        m_sprite->scale(Transform::UnitVector(vScale, vScale, m_sprite->getSize().unit), Transform::reverseReferencial(m_referencial));
                }
                else
                {
                    float e1_x = oppositePos.x - pos.x;
                    float e1_y = oppositePos.y - pos.y;
                    float e2_x = m_dp.x - pos.x;
                    float e2_y = m_dp.y - pos.y;

                    float valDp = e1_x * e2_x + e1_y * e2_y;
                    float len = e1_x * e1_x + e1_y * e1_y;

                    m_dp.x = pos.x + (valDp * e1_x) / len;
                    m_dp.y = pos.y + (valDp * e1_y) / len;

                    m_sprite->setPointPosition(m_dp, m_referencial);
                }
            }
            else
            {
                m_dp = m_sprite->getPositionTransformer()(position, -camera, m_sprite->getLayer());

                Transform::UnitVector center = m_sprite->getPosition(Transform::Referencial::Center).to<Transform::Units::WorldPixels>();
                double n = (90 + ((m_sprite->getScaleFactor().y < 0) ? 180 : 0)) - 
                    (std::atan2(center.y - m_dp.y, center.x - m_dp.x)) * 180.0 / obe::Utils::Math::pi;

                static_cast<Transform::Rect*>(m_sprite)->setRotation(std::fmod(n, 360), m_sprite->getPosition(Transform::Referencial::Center));
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
            return *m_sprite;
        }

        void LevelSprite::dump(vili::ComplexNode& target) const
        {
            vili::ComplexNode& ser = target.createComplexNode(m_id);
            ser.createDataNode("path", m_path);
            ser.createComplexNode("rect");
            Transform::UnitVector spritePositionRect = this->getPosition().to(m_unit);
            ser.at("rect").createDataNode("x", spritePositionRect.x);
            ser.at("rect").createDataNode("y", spritePositionRect.y);
            Transform::UnitVector spriteSizeRect = this->getSize().to(m_unit);
            ser.at("rect").createDataNode("w", spriteSizeRect.x);
            ser.at("rect").createDataNode("h", spriteSizeRect.y);
            ser.at("rect").createDataNode("unit", Transform::unitsToString(m_unit));

            ser.createDataNode("rotation", m_angle);
            ser.createDataNode("layer", m_layer);
            ser.createDataNode("z-depth", m_zdepth);
            ser.createDataNode("xTransform", m_positionTransformer.getXTransformerName());
            ser.createDataNode("yTransform", m_positionTransformer.getYTransformerName());
        }

        void LevelSprite::load(vili::ComplexNode& data)
        {
            std::string spriteXTransformer;
            std::string spriteYTransformer;
            std::string spriteUnits = data.contains(vili::NodeType::ComplexNode, "rect") ?
                data.at<vili::DataNode>("rect", "unit").get<std::string>() : "WorldUnits";
            std::string spritePath = data.contains(vili::NodeType::DataNode, "path") ?
                data.getDataNode("path").get<std::string>() : "";
            Transform::UnitVector spritePos(0, 0);
            Transform::UnitVector spriteSize(1, 1);
            if (data.contains(vili::NodeType::ComplexNode, "rect"))
            {
                Transform::Units rectUnit = Transform::stringToUnits(spriteUnits);
                spritePos.unit = rectUnit;
                spritePos.x = data.at<vili::DataNode>("rect", "x").get<double>();
                spritePos.y = data.at<vili::DataNode>("rect", "y").get<double>();
                spriteSize.unit = rectUnit;
                spriteSize.x = data.at<vili::DataNode>("rect", "w").get<double>();
                spriteSize.y = data.at<vili::DataNode>("rect", "h").get<double>();
                spritePos = spritePos.to<Transform::Units::WorldUnits>();
                spriteSize = spriteSize.to<Transform::Units::WorldUnits>();
            }
            double spriteRot = data.contains(vili::NodeType::DataNode, "rotation") ?
                data.getDataNode("rotation").get<double>() : 0;
            int layer = data.contains(vili::NodeType::DataNode, "layer") ?
                data.getDataNode("layer").get<int>() : 1;
            int zdepth = data.contains(vili::NodeType::DataNode, "z-depth") ?
                data.getDataNode("z-depth").get<int>() : 1;

            if (data.contains(vili::NodeType::DataNode, "xTransform"))
                spriteXTransformer = data.at<vili::DataNode>("xTransform").get<std::string>();
            else
                spriteXTransformer = "Position";
            if (data.contains(vili::NodeType::DataNode, "yTransform"))
                spriteYTransformer = data.at<vili::DataNode>("yTransform").get<std::string>();
            else
                spriteYTransformer = "Position";

            if (spritePath != "")
                this->loadTexture(spritePath);
            std::cout << "Sprite Pos : " << m_id << " is " << spritePos << std::endl;
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

        void LevelSprite::setShader(Shader* shader)
        {
            m_shader = shader;
            m_shader->setUniform("texture", sf::Shader::CurrentTexture);
        }
        
        Shader* LevelSprite::getShader()
        {
            return m_shader;
        }

        bool LevelSprite::hasShader()
        {
            return (m_shader != nullptr);
        }
    }
}
