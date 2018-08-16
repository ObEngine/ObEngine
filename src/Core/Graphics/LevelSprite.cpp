#include <Graphics/LevelSprite.hpp>
#include <Graphics/ResourceManager.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>
#include <System/Window.hpp>
#include <Graphics/DrawUtils.hpp>
#include <Utils/MathUtils.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe::Graphics
{
    LevelSprite::LevelSprite(const std::string& id) : Selectable(false), Rect(Transform::MovableType::LevelSprite), Component(id)
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
        const sf::Vector2u textureSize = this->getTexture().getSize();
        const Transform::UnitVector initialSpriteSize(textureSize.x, textureSize.y, Transform::Units::WorldPixels);
        this->setSize(initialSpriteSize);
    }

    void LevelSprite::draw(const Transform::UnitVector& camera)
    {
        const auto toVertex = [](const Transform::UnitVector& uv)
        {
            return sf::Vertex(sf::Vector2f(uv.x, uv.y));
        };
        std::array<sf::Vertex, 4> vertices;
        vertices[0] = toVertex(Rect::getPosition(Transform::Referencial::TopLeft).to<Transform::Units::WorldPixels>() - camera);
        vertices[1] = toVertex(Rect::getPosition(Transform::Referencial::BottomLeft).to<Transform::Units::WorldPixels>() - camera);
        vertices[2] = toVertex(Rect::getPosition(Transform::Referencial::TopRight).to<Transform::Units::WorldPixels>() - camera);
        vertices[3] = toVertex(Rect::getPosition(Transform::Referencial::BottomRight).to<Transform::Units::WorldPixels>() - camera);

        m_sprite.setVertices(vertices);

        if (m_shader)
            System::MainWindow.draw(m_sprite, m_shader);
        else
            System::MainWindow.draw(m_sprite);

        if (m_selected)
        {
            this->drawHandle(camera);
        }
    }

    void LevelSprite::loadTexture(const std::string& path)
    {
        if (path != "")
        {
            m_path = path;
            const std::string fPath = System::Path(path).find();
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
    }

    void LevelSprite::rotate(double addRotate)
    {
        Rect::rotate(addRotate, this->getPosition(Transform::Referencial::Center));
    }

    void LevelSprite::setScalingOrigin(int x, int y)
    {
        m_sprite.setScalingOrigin(x, y);
    }

    void LevelSprite::drawHandle(const Transform::UnitVector& camera) const
    {
        const Transform::UnitVector position = m_positionTransformer(m_position, camera, m_layer).to<Transform::Units::WorldPixels>();
        Rect::draw(position.x, position.y);
    }

    LevelSpriteHandlePoint* LevelSprite::getHandlePoint(Transform::UnitVector& cameraPosition, int posX, int posY)
    {
        const Transform::UnitVector pixelCamera = cameraPosition.to<Transform::Units::WorldPixels>();
        Transform::UnitVector targetPos = Transform::UnitVector(posX, posY, Transform::Units::WorldPixels);
        targetPos = m_positionTransformer(targetPos, -pixelCamera, m_layer);
        for (int i = 0; i < 9; i++)
        {
            const Transform::Referencial refIndex = static_cast<Transform::Referencial>(i);
            const Transform::UnitVector refPoint = Rect::getPosition(refIndex).to<Transform::Units::WorldPixels>();
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

        const double radAngle = obe::Utils::Math::convertToRadian(-m_angle);
        const double cosAngle = std::cos(radAngle);
        const double sinAngle = std::sin(radAngle);
        const Transform::UnitVector topPos = this->getPosition(Transform::Referencial::Top).to<Transform::Units::WorldPixels>();
        Transform::UnitVector rotHandle = topPos;
        Transform::UnitVector result;
        const double dy = m_size.y / 4;
        result.x = (-dy * sinAngle) * -1;
        result.y = (dy * cosAngle) * -1;
        rotHandle.add(result);

        const int lowerXBound = std::min(rotHandle.x - LevelSpriteHandlePoint::radius, rotHandle.x + LevelSpriteHandlePoint::radius);
        const int upperXBound = std::max(rotHandle.x - LevelSpriteHandlePoint::radius, rotHandle.x + LevelSpriteHandlePoint::radius);
        if (obe::Utils::Math::isBetween(targetPos.x, lowerXBound, upperXBound))
        {
            const int lowerYBound = std::min(rotHandle.y - LevelSpriteHandlePoint::radius, rotHandle.y + LevelSpriteHandlePoint::radius);
            const int upperYBound = std::max(rotHandle.y - LevelSpriteHandlePoint::radius, rotHandle.y + LevelSpriteHandlePoint::radius);
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
        const Transform::UnitVector realPosition = Rect::m_position.to<Transform::Units::WorldPixels>();

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

    void LevelSprite::setPositionTransformer(const PositionTransformer transformer) // <REVISION> const ref ?
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
            const Transform::UnitVector pos = m_sprite->getPosition(m_referencial).to<Transform::Units::WorldPixels>();
            const Transform::UnitVector oppositePos = m_sprite->getPosition(Transform::reverseReferencial(m_referencial)).to<Transform::Units::WorldPixels>();

            if (Transform::isOnCorner(m_referencial))
            {
                const Transform::UnitVector baseDist = oppositePos - m_dp;
                Transform::UnitVector scaleVector = baseDist / m_sprite->getSize().to<Transform::Units::WorldPixels>();
                scaleVector.set((isOnRightSide(m_referencial)) ? -scaleVector.x : scaleVector.x, (isOnBottomSide(m_referencial)) ? -scaleVector.y : scaleVector.y);
                const double vScale = std::max(scaleVector.x, scaleVector.y);
                if (baseDist.x != 0 && baseDist.y != 0)
                    m_sprite->scale(Transform::UnitVector(vScale, vScale, m_sprite->getSize().unit), Transform::reverseReferencial(m_referencial));
            }
            else
            {
                const float e1_x = oppositePos.x - pos.x;
                const float e1_y = oppositePos.y - pos.y;
                const float e2_x = m_dp.x - pos.x;
                const float e2_y = m_dp.y - pos.y;

                const float valDp = e1_x * e2_x + e1_y * e2_y;
                const float len = e1_x * e1_x + e1_y * e1_y;

                m_dp.x = pos.x + (valDp * e1_x) / len;
                m_dp.y = pos.y + (valDp * e1_y) / len;

                m_sprite->setPointPosition(m_dp, m_referencial);
            }
        }
        else
        {
            m_dp = m_sprite->getPositionTransformer()(position, -camera, m_sprite->getLayer());

            const Transform::UnitVector center = m_sprite->getPosition(Transform::Referencial::Center).to<Transform::Units::WorldPixels>();
            const double n = (90 + ((m_sprite->getScaleFactor().y < 0) ? 180 : 0)) - 
                (std::atan2(center.y - m_dp.y, center.x - m_dp.x)) * 180.0 / obe::Utils::Math::pi;

            m_sprite->setRotation(std::fmod(n, 360));
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
        const Transform::UnitVector spritePositionRect = this->getPosition().to(m_unit);
        ser.at("rect").createDataNode("x", spritePositionRect.x);
        ser.at("rect").createDataNode("y", spritePositionRect.y);
        const Transform::UnitVector spriteSizeRect = this->getSize().to(m_unit);
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
        const std::string spriteUnits = data.contains(vili::NodeType::ComplexNode, "rect") ?
            data.at<vili::DataNode>("rect", "unit").get<std::string>() : "WorldUnits";
        const std::string spritePath = data.contains(vili::NodeType::DataNode, "path") ?
            data.getDataNode("path").get<std::string>() : "";
        Transform::UnitVector spritePos(0, 0);
        Transform::UnitVector spriteSize(1, 1);
        if (data.contains(vili::NodeType::ComplexNode, "rect"))
        {
            const Transform::Units rectUnit = Transform::stringToUnits(spriteUnits);
            spritePos.unit = rectUnit;
            spritePos.x = data.at<vili::DataNode>("rect", "x").get<double>();
            spritePos.y = data.at<vili::DataNode>("rect", "y").get<double>();
            spriteSize.unit = rectUnit;
            spriteSize.x = data.at<vili::DataNode>("rect", "w").get<double>();
            spriteSize.y = data.at<vili::DataNode>("rect", "h").get<double>();
            spritePos = spritePos.to<Transform::Units::WorldUnits>();
            spriteSize = spriteSize.to<Transform::Units::WorldUnits>();
        }
        const double spriteRot = data.contains(vili::NodeType::DataNode, "rotation") ?
            data.getDataNode("rotation").get<double>() : 0;
        const int layer = data.contains(vili::NodeType::DataNode, "layer") ?
            data.getDataNode("layer").get<int>() : 1;
        const int zdepth = data.contains(vili::NodeType::DataNode, "z-depth") ?
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
        const PositionTransformer positionTransformer(spriteXTransformer, spriteYTransformer);
        this->setPositionTransformer(positionTransformer);
        this->setLayer(layer);
        this->setZDepth(zdepth);
        this->setRotation(spriteRot);
    }

    void LevelSprite::setShader(Shader* shader)
    {
        m_shader = shader;
        m_shader->setUniform("texture", sf::Shader::CurrentTexture);
    }
        
    Shader* LevelSprite::getShader() const
    {
        return m_shader;
    }

    bool LevelSprite::hasShader() const
    {
        return (m_shader != nullptr);
    }
}