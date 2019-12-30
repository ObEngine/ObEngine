#include <Graphics/DrawUtils.hpp>
#include <Graphics/LevelSprite.hpp>
#include <Graphics/ResourceManager.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>
#include <System/Window.hpp>
#include <Utils/MathUtils.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe::Graphics
{
    LevelSprite::LevelSprite(const std::string& id)
        : Selectable(false)
        , Component(id)
    {
        m_antiAliasing = ResourceManager::GetInstance().defaultAntiAliasing;
        m_texture = &ResourceManager::GetInstance().NullTexture;
        m_sprite.setTexture(*m_texture);

        for (Transform::Referential& ref : Transform::Referential::Referentials)
        {
            m_handlePoints.emplace_back(this, ref);
        }
        m_handlePoints.emplace_back(this);
    }

    void LevelSprite::useTextureSize()
    {
        const sf::Vector2u textureSize = this->getTexture().getSize();
        const Transform::UnitVector initialSpriteSize(
            textureSize.x, textureSize.y, Transform::Units::ScenePixels);
        this->setSize(initialSpriteSize);
    }

    void LevelSprite::draw(const Transform::UnitVector& camera)
    {
        const Transform::UnitVector position = m_positionTransformer(m_position, camera, m_layer);
        const auto toVertex
            = [](const Transform::UnitVector& uv) { return sf::Vertex(sf::Vector2f(uv.x, uv.y)); };
        std::array<sf::Vertex, 4> vertices;
        std::array<Transform::Referential, 4> referentials
            = { Transform::Referential::TopLeft, Transform::Referential::BottomLeft,
                  Transform::Referential::TopRight, Transform::Referential::BottomRight };
        unsigned int vertexIndex = 0;
        for (Transform::Referential referential : referentials)
        {
            vertices[vertexIndex++]
                = toVertex(m_positionTransformer(Rect::getPosition(referential), camera, m_layer)
                               .to<Transform::Units::ScenePixels>());
        }

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

    std::string_view LevelSprite::type() const
    {
        return ComponentType;
    }

    void LevelSprite::loadTexture(const std::string& path)
    {
        if (path != "")
        {
            m_path = path;
            const std::string fPath = System::Path(path).find();
            m_texture = ResourceManager::GetInstance().getTexture(fPath, m_antiAliasing);

            m_sprite.setTexture(*m_texture);
            m_sprite.setTextureRect(
                sf::IntRect(0, 0, m_texture->getSize().x, m_texture->getSize().y));
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

    void LevelSprite::setTextureRect(
        unsigned int x, unsigned int y, unsigned int width, unsigned int height)
    {
        m_sprite.setTextureRect(sf::IntRect(x, y, width, height));
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

    void LevelSprite::setAntiAliasing(bool antiAliasing)
    {
        if (antiAliasing != m_antiAliasing && m_texture && !m_path.empty())
        {
            m_antiAliasing = antiAliasing;
            this->loadTexture(m_path);
        }
        else
        {
            m_antiAliasing = antiAliasing;
        }
    }

    void LevelSprite::setRotation(double rotate)
    {
        Rect::setRotation(rotate, this->getPosition(Transform::Referential::Center));
    }

    void LevelSprite::rotate(double addRotate)
    {
        Rect::rotate(addRotate, this->getPosition(Transform::Referential::Center));
    }

    void LevelSprite::setScalingOrigin(int x, int y)
    {
        m_sprite.setScalingOrigin(x, y);
    }

    void LevelSprite::drawHandle(const Transform::UnitVector& camera) const
    {
        const Transform::UnitVector position = m_positionTransformer(m_position, camera, m_layer)
                                                   .to<Transform::Units::ScenePixels>();
        Rect::draw(position.x, position.y);
    }

    LevelSpriteHandlePoint* LevelSprite::getHandlePoint(
        Transform::UnitVector& cameraPosition, int posX, int posY)
    {
        const Transform::UnitVector pixelCamera
            = cameraPosition.to<Transform::Units::ScenePixels>();
        Transform::UnitVector targetPos
            = Transform::UnitVector(posX, posY, Transform::Units::ScenePixels);
        targetPos = m_positionTransformer(targetPos, -pixelCamera, m_layer);
        unsigned int i = 0;
        for (Transform::Referential& ref : Transform::Referential::Referentials)
        {
            const Transform::UnitVector refPoint
                = Rect::getPosition(ref).to<Transform::Units::ScenePixels>();
            int lowerXBound = std::min(refPoint.x - LevelSpriteHandlePoint::radius,
                refPoint.x + LevelSpriteHandlePoint::radius);
            int upperXBound = std::max(refPoint.x - LevelSpriteHandlePoint::radius,
                refPoint.x + LevelSpriteHandlePoint::radius);
            if (obe::Utils::Math::isBetween(targetPos.x, lowerXBound, upperXBound)
                && ref != Transform::Referential::Center)
            {
                int lowerYBound = std::min(refPoint.y - LevelSpriteHandlePoint::radius,
                    refPoint.y + LevelSpriteHandlePoint::radius);
                int upperYBound = std::max(refPoint.y - LevelSpriteHandlePoint::radius,
                    refPoint.y + LevelSpriteHandlePoint::radius);
                if (obe::Utils::Math::isBetween(targetPos.y, lowerYBound, upperYBound))
                    return &m_handlePoints[i];
            }
            i++;
        }

        const double radAngle = obe::Utils::Math::convertToRadian(-m_angle);
        const double cosAngle = std::cos(radAngle);
        const double sinAngle = std::sin(radAngle);
        const Transform::UnitVector topPos
            = this->getPosition(Transform::Referential::Top).to<Transform::Units::ScenePixels>();
        Transform::UnitVector rotHandle = topPos;
        Transform::UnitVector result;
        const double dy = m_size.y / 4;
        result.x = (-dy * sinAngle) * -1;
        result.y = (dy * cosAngle) * -1;
        rotHandle.add(result);

        const int lowerXBound = std::min(rotHandle.x - LevelSpriteHandlePoint::radius,
            rotHandle.x + LevelSpriteHandlePoint::radius);
        const int upperXBound = std::max(rotHandle.x - LevelSpriteHandlePoint::radius,
            rotHandle.x + LevelSpriteHandlePoint::radius);
        if (obe::Utils::Math::isBetween(targetPos.x, lowerXBound, upperXBound))
        {
            const int lowerYBound = std::min(rotHandle.y - LevelSpriteHandlePoint::radius,
                rotHandle.y + LevelSpriteHandlePoint::radius);
            const int upperYBound = std::max(rotHandle.y - LevelSpriteHandlePoint::radius,
                rotHandle.y + LevelSpriteHandlePoint::radius);
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

    bool LevelSprite::getAntiAliasing() const
    {
        return m_antiAliasing;
    }

    std::string LevelSprite::getPath() const
    {
        return m_path;
    }

    sf::FloatRect LevelSprite::getRect()
    {
        const Transform::UnitVector realPosition
            = Rect::m_position.to<Transform::Units::ScenePixels>();

        m_sprite.setPosition(realPosition.x, realPosition.y);
        sf::FloatRect mrect = sf::FloatRect(realPosition.x, realPosition.y,
            m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height);
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

    void LevelSprite::setPositionTransformer(
        const PositionTransformer transformer) // <REVISION> const ref ?
    {
        m_positionTransformer = transformer;
    }

    PositionTransformer LevelSprite::getPositionTransformer() const
    {
        return m_positionTransformer;
    }

    unsigned int LevelSpriteHandlePoint::radius = 6;
    LevelSpriteHandlePoint::LevelSpriteHandlePoint(LevelSprite* parent, Transform::Referential ref)
        : m_referential(ref)
    {
        m_sprite = parent;
        m_type = LevelSpriteHandlePointType::ScaleHandle;
    }

    LevelSpriteHandlePoint::LevelSpriteHandlePoint(LevelSprite* parent)
    {
        m_sprite = parent;
        m_type = LevelSpriteHandlePointType::RotateHandle;
    }

    void LevelSpriteHandlePoint::moveTo(
        const Transform::UnitVector& position, const Transform::UnitVector& camera)
    {
        m_dp = m_sprite->getPositionTransformer()(position, -camera, m_sprite->getLayer());
        if (m_type == LevelSpriteHandlePointType::ScaleHandle)
        {
            // std::cout << "Was at : " <<
            // m_rect->getPosition(m_referential).to<Transform::Units::ScenePixels>()
            // << std::endl; std::cout << "Set : " << x << ", " << y <<
            // std::endl;
            const Transform::UnitVector pos
                = m_sprite->getPosition(m_referential).to<Transform::Units::ScenePixels>();
            const Transform::UnitVector oppositePos
                = m_sprite->getPosition(m_referential.flip()).to<Transform::Units::ScenePixels>();

            if (m_referential.isOnCorner())
            {
                const Transform::UnitVector centerSpritePos
                    = m_sprite->getPosition(Transform::Referential::Center);
                const double spriteAngle = m_sprite->getRotation();
                const Transform::UnitVector oppositePosInRef
                    = oppositePos.rotate(spriteAngle, centerSpritePos);
                const Transform::UnitVector posInRef = pos.rotate(spriteAngle, centerSpritePos);
                const Transform::UnitVector cursorInRef = m_dp.rotate(spriteAngle, centerSpritePos);
                Transform::UnitVector scaleVector
                    = (cursorInRef - oppositePosInRef) / (posInRef - oppositePosInRef);
                const double vScale = std::max(scaleVector.x, scaleVector.y);
                Debug::Log->debug("{} / {} = {}", (cursorInRef - oppositePosInRef),
                    (posInRef - oppositePosInRef), scaleVector);
                if ((cursorInRef - oppositePosInRef).x != 0
                    && (cursorInRef - oppositePosInRef).y != 0)
                    m_sprite->scale(Transform::UnitVector(vScale, vScale, m_sprite->getSize().unit),
                        m_referential.flip());
            }
            else
            {
                const Transform::UnitVector e1 = oppositePos - pos;
                const Transform::UnitVector e2 = m_dp - pos;

                const double valDp = e1.x * e2.x + e1.y * e2.y;
                const double len = e1.x * e1.x + e1.y * e1.y;

                /*m_dp.x = pos.x + (valDp * e1.x) / len;
                m_dp.y = pos.y + (valDp * e1.y) / len;*/
                const Transform::UnitVector npp(
                    pos.x + (valDp * e1.x) / len, pos.y + (valDp * e1.y) / len, m_dp.unit);
                m_sprite->setPointPosition(npp, m_referential);
            }
        }
        else
        {
            const Transform::UnitVector center
                = m_sprite->getPosition(Transform::Referential::Center)
                      .to<Transform::Units::ScenePixels>();
            const double n = (90 + ((m_sprite->getScaleFactor().y < 0) ? 180 : 0))
                - (std::atan2(center.y - m_dp.y, center.x - m_dp.x)) * 180.0 / obe::Utils::Math::pi;

            m_sprite->setRotation(std::fmod(n, 360));
        }
    }

    Transform::Referential LevelSpriteHandlePoint::getReferential() const
    {
        return m_referential;
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
        const std::string spriteUnits = data.contains(vili::NodeType::ComplexNode, "rect")
            ? data.at<vili::DataNode>("rect", "unit").get<std::string>()
            : "SceneUnits";
        const std::string spritePath = data.contains(vili::NodeType::DataNode, "path")
            ? data.getDataNode("path").get<std::string>()
            : "";
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
            spritePos = spritePos.to<Transform::Units::SceneUnits>();
            spriteSize = spriteSize.to<Transform::Units::SceneUnits>();
        }
        const double spriteRot = data.contains(vili::NodeType::DataNode, "rotation")
            ? data.getDataNode("rotation").get<double>()
            : 0;
        const int layer = data.contains(vili::NodeType::DataNode, "layer")
            ? data.getDataNode("layer").get<int>()
            : 1;
        const int zdepth = data.contains(vili::NodeType::DataNode, "z-depth")
            ? data.getDataNode("z-depth").get<int>()
            : 1;

        const bool antiAliasing = data.contains(vili::NodeType::DataNode, "antiAliasing")
            ? data.getDataNode("antiAliasing").get<bool>()
            : ResourceManager::GetInstance().defaultAntiAliasing;

        if (data.contains(vili::NodeType::DataNode, "xTransform"))
            spriteXTransformer = data.at<vili::DataNode>("xTransform").get<std::string>();
        else
            spriteXTransformer = "Position";
        if (data.contains(vili::NodeType::DataNode, "yTransform"))
            spriteYTransformer = data.at<vili::DataNode>("yTransform").get<std::string>();
        else
            spriteYTransformer = "Position";

        this->setAntiAliasing(antiAliasing);

        if (spritePath != "")
            this->loadTexture(spritePath);
        this->setRotation(spriteRot);
        this->setPosition(spritePos);
        this->setSize(spriteSize);
        this->setWorkingUnit(Transform::stringToUnits(spriteUnits));
        const PositionTransformer positionTransformer(spriteXTransformer, spriteYTransformer);
        this->setPositionTransformer(positionTransformer);
        this->setLayer(layer);
        this->setZDepth(zdepth);
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
} // namespace obe::Graphics