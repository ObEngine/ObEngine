//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "LevelSprite.hpp"

namespace obe
{
    namespace Graphics
    {
        LevelSprite::LevelSprite(std::string id)
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
                this->update();
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
            calculateRealCoordinates();
        }

        void LevelSprite::rotate(double addRotate)
        {
            m_rotation += addRotate;
            if (m_rotation < 0) m_rotation += 360;
            m_rotation = (static_cast<int>(m_rotation) % 360) + (m_rotation - floor(m_rotation));
            m_returnSprite.setRotation(m_rotation);
            calculateRealCoordinates();
        }

        void LevelSprite::scale(double scaleX, double scaleY)
        {
            m_size.add(scaleX, scaleY);
            this->applySize();
        }

        void LevelSprite::setSize(double scaleX, double scaleY)
        {
            m_size.set(scaleX, scaleY);
            Coord::UnitVector pixelSize = m_size.to<Coord::WorldPixels>();
            std::cout << ":D Apply size : " << pixelSize << " for LevelSprite " << m_id << ", got : " << scaleX << ", " << scaleY << std::endl;
            std::cout << "Texture size : " << this->getWidth() << ", " << this->getHeight() << std::endl;
            std::cout << "It gives scale : " << double(this->getWidth()) / pixelSize.x << ", " << double(this->getWidth()) / pixelSize.y << std::endl;
            this->applySize();
        }

        void LevelSprite::u_scale(const Coord::UnitVector& vec)
        {
            Coord::UnitVector pVec = vec.to<Coord::WorldUnits>();
            this->scale(pVec.x, pVec.y);
        }

        void LevelSprite::u_setSize(const Coord::UnitVector& vec)
        {
            Coord::UnitVector pVec = vec.to<Coord::WorldUnits>();
            this->setSize(pVec.x, pVec.y);
        }

        Coord::ProtectedUnitVector& LevelSprite::getSize()
        {
            return m_size;
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
            Coord::UnitVector pixelSize = m_size.to<Coord::WorldPixels>();
            /*std::cout << "Apply size : " << pixelSize << " for LevelSprite " << m_id << std::endl;*/
            m_returnSprite.setScale(pixelSize.x / double(this->getWidth()), pixelSize.y / double(this->getHeight()));
            //std::cout << "It gives scale : " << double(this->getWidth()) / pixelSize.x << ", " << double(this->getWidth()) / pixelSize.y << std::endl;
            calculateRealCoordinates();
        }

        void LevelSprite::update()
        {
            m_returnSprite.setRotation(m_rotation);
            //this->applySize();
            m_returnSprite.setColor(m_spriteColor);
            calculateRealCoordinates();
        }

        void LevelSprite::setColor(sf::Color newColor)
        {
            m_spriteColor = newColor;
            m_returnSprite.setColor(m_spriteColor);
        }

        sfe::ComplexSprite* LevelSprite::getSprite()
        {
            this->update();
            return &m_returnSprite;
        }

        void LevelSprite::setPosition(double x, double y)
        {
            m_position.x = x;
            m_position.y = y;
        }

        void LevelSprite::setOffset(double offx, double offy)
        {
            m_offset.x = offx;
            m_offset.y = offy;
        }

        void LevelSprite::u_setPosition(const Coord::UnitVector& vec)
        {
            Coord::UnitVector pVec = vec.to<Coord::WorldUnits>();
            this->setPosition(pVec.x, pVec.y);
        }

        void LevelSprite::u_setOffset(const Coord::UnitVector& vec)
        {
            Coord::UnitVector pVec = vec.to<Coord::WorldUnits>();
            this->setOffset(pVec.x, pVec.y);
        }

        Coord::ProtectedUnitVector& LevelSprite::getPosition()
        {
            return m_position;
        }

        Coord::ProtectedUnitVector& LevelSprite::getOffset()
        {
            return m_offset;
        }

        void LevelSprite::move(double x, double y)
        {
            m_position.add(x, y);
        }

        void LevelSprite::moveOffset(double x, double y)
        {
            m_offset.add(x, y);
        }

        void LevelSprite::u_move(const Coord::UnitVector& vec)
        {
            Coord::UnitVector pVec = vec.to<Coord::WorldUnits>();
            this->move(pVec.x, pVec.y);
        }

        void LevelSprite::u_moveOffset(const Coord::UnitVector& vec)
        {
            Coord::UnitVector pVec = vec.to<Coord::WorldUnits>();
            this->moveOffset(pVec.x, pVec.y);
        }

        double LevelSprite::getX() const
        {
            return m_position.x;
        }

        double LevelSprite::getY() const
        {
            return m_position.y;
        }

        double LevelSprite::getOffsetX() const
        {
            return m_offset.x;
        }

        double LevelSprite::getOffsetY() const
        {
            return m_offset.y;
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

        int LevelSprite::getWidth() const
        {
            return m_returnSprite.getGlobalBounds().width;
        }

        int LevelSprite::getHeight() const
        {
            return m_returnSprite.getGlobalBounds().height;
        }

        void LevelSprite::calculateRealCoordinates()
        {
            m_width = m_returnSprite.getGlobalBounds().width;
            m_height = m_returnSprite.getGlobalBounds().height;
        }

        sf::FloatRect LevelSprite::getRect()
        {
            m_returnSprite.setTranslationOrigin(m_originTraX, m_originTraY);
            m_returnSprite.setRotationOrigin(m_originRotX, m_originRotY);

            Coord::UnitVector realPosition = (m_position + m_offset).to<Coord::WorldPixels>();

            m_returnSprite.setPosition(realPosition.x, realPosition.y);
            this->applySize();
            m_returnSprite.setRotation(m_rotation);
            sf::FloatRect mrect = sf::FloatRect(realPosition.x, realPosition.y, m_width, m_height);
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
    }
}
