#pragma once

#include <sfe/ComplexSprite.hpp>

#include <Transform/Rect.hpp>
#include <Transform/Referencial.hpp>
#include <Transform/UnitBasedObject.hpp>
#include <Types/Identifiable.hpp>
#include <Types/Selectable.hpp>

namespace obe
{
    namespace Graphics
    {
        /**
         * \brief An element meant to be displayed in a Scene
         */
        class LevelSprite : public Transform::UnitBasedObject, public Types::Selectable, public Transform::Rect, public Types::Identifiable
        {
        public:
            /**
             * \brief A HandlePoint to manipulate a LevelSprite Size
             */
            class HandlePoint
            {
            private:
                Transform::Rect* m_rect;
                Transform::Referencial m_referencial;
            public:
                /**
                 * \brief Creates a HandlePoint
                 * \param parentRect Rect of the parent LevelSprite
                 * \param ref Referencial of the HandlePoint
                 */
                HandlePoint(Transform::Rect* parentRect, Transform::Referencial ref);
                /**
                 * \brief Move the HandlePoint to the given Position
                 * \param x x Coordinate of the Position where to move the HandlePoint
                 * \param y y Coordinate of the Position where to move the HandlePoint
                 */
                void moveTo(int x, int y) const;
                /**
                 * \brief Get the Referencial of the HandlePoint
                 * \return The Referencial value
                 */
                Transform::Referencial getReferencial() const;
                /**
                 * \brief Get the rect of the parent LevelSprite
                 * \return The Rect of the parent LevelSprite
                 */
                Transform::Rect& getRect() const;
                /**
                 * \brief The radius of a HandlePoint
                 */
                static const int radius = 6;
            };
        private:
            std::string m_path = "";

            bool m_visible = true;

            double m_rotation = 0;

            std::vector<HandlePoint> m_handlePoints;
            std::vector<std::string> m_currentAtr = {};
            int m_layer = 1;
            int m_zdepth = 0;
            sf::Texture m_texture;
            sfe::ComplexSprite m_sprite;
            std::string m_parentID = "";

            void applySize();
            void resetUnit(Transform::Units unit) override;
        public:
            /**
             * \brief Creates a new LevelSprite with the given Id
             * \param id A std::string containing the Id of the LevelSprite
             */
            explicit LevelSprite(const std::string& id);

            //Loading
            /**
             * \brief The LevelSprite will load the sf::Texture at the given path
             * \param path A std::string containing the path of the texture to load
             */
            void load(const std::string& path);
            /**
             * \brief Get the path of the sf::Texture loaded by the Sprite
             * \return A std::string containing the path of the sf::Texture loaded by the Sprite (if any)
             */
            std::string getPath() const;

            //Texture
            void setTexture(const sf::Texture& texture);
            sf::Texture& getTexture();

            //Layers
            /**
             * \brief Set the layer of the Sprite
             * \param layer Layer where to put the sprite (Higher layer is behind lower ones)
             */
            void setLayer(int layer);
            /**
             * \brief Set the Z-Depth of the Sprite (SubLayers)
             * \param zdepth z-depth of the Sprite (Higher z-depth is behind lower ones)
             */
            void setZDepth(int zdepth);
            /**
             * \brief Get the layer of the Sprite
             * \return An int containing the Layer where the sprite is (Higher layer is behind lower ones)
             */
            int getLayer() const;
            /**
            * \brief Get the Z-depth of the Sprite
            * \return An int containing the z-depth where the sprite is (Higher z-depth is behind lower ones)
            */
            int getZDepth() const;

            //Rotation
            /**
            * \brief Rotate the sprite
            * \param addRotate The angle to add to the LevelSprite (0 -> 360 where 0 / 360 is the top)
            */
            void rotate(double addRotate);
            /**
             * \brief Set the rotation of the sprite
             * \param rotate The new angle of the LevelSprite (0 -> 360 where 0 / 360 is the top)
             */
            void setRotation(double rotate);
            /**
             * \brief 
             * \return 
             */
            double getRotation() const;
            
            //Origins
            /**
             * \brief Set the translation origin of the LevelSprite
             * \param x x Coordinate of the new translation origin of the LevelSprite
             * \param y y Coordinate of the new translation origin of the LevelSprite
             */
            void setTranslationOrigin(int x, int y);
            /**
            * \brief Set the rotation origin of the LevelSprite
            * \param x x Coordinate of the new rotation origin of the LevelSprite
            * \param y y Coordinate of the new rotation origin of the LevelSprite
            */
            void setRotationOrigin(int x, int y);
            /**
            * \brief Set the scaling origin of the LevelSprite
            * \param x x Coordinate of the new scaling origin of the LevelSprite
            * \param y y Coordinate of the new scaling origin of the LevelSprite
            */
            void setScalingOrigin(int x, int y);

            //Position
            /**
             * \brief Get the Position where the LevelSprite should be drawn depending of the Position of the Camera
             * \param cameraPosition Position of the Camera (in WorldPixels Unit)
             * \return The Screen Position at which the LevelSprite should be drawn (in ViewPixels Unit)
             */
            Transform::UnitVector getDrawPosition(Transform::UnitVector& cameraPosition) const;

            //Size
            /**
             * \brief Get the width of the LevelSprite
             * \return The width of the Sprite (Including transformations such as rotations / scaling)
             */
            double getSpriteWidth() const;
            /**
            * \brief Get the height of the LevelSprite
            * \return The height of the Sprite (Including transformations such as rotations / scaling)
            */
            double getSpriteHeight() const;
            /**
             * \brief Get the x Coordinate of the scale factor of the LevelSprite
             * \return -1 if the LevelSprite has been horizontally flipped, 1 otherwise
             */
            int getXScaleFactor() const;
            /**
            * \brief Get the y Coordinate of the scale factor of the LevelSprite
            * \return -1 if the LevelSprite has been vertically flipped, 1 otherwise
            */
            int getYScaleFactor() const;

            //Attributes
            void setAtr(std::vector<std::string> atrList);
            void addAtr(const std::string& atr);
            std::vector<std::string> getAttributes() const;
            void removeAtrByIndex(int index);
            void removeAtrByName(std::string name);
            
            //Sprite
            /**
             * \brief Get the internal Sprite of the LevelSprite
             * \return A reference to the internal Sprite of the LevelSprite
             */
            sfe::ComplexSprite& getSprite();
            
            //Colors
            /**
             * \brief Apply a blend color to the LevelSprite
             * \param newColor A sf::Color containing the color to blend (sf::Color::White is default normal color)
             */
            void setColor(sf::Color newColor);
            /**
             * \brief Get the blend color of the LevelSprite
             * \return A sf::Color containing the blend color of the LevelSprite
             */
            sf::Color getColor() const;
 
            //Rect
            /**
             * \brief Get the Bounding Rect of the internal Sprite
             * \return A sf::FloatRect representing the bounding rectangle of the internal Sprite
             */
            sf::FloatRect getRect();

            //Visibility
            /**
             * \brief Set the visibility of the LevelSprite
             * \param visible If visible is equal to true, the LevelSprite will be visible, if visible is equal to false, it won't be visible
             */
            void setVisible(bool visible);
            /**
             * \brief Get the visibility of the LevelSprite
             * \return true if the LevelSprite is visible, false otherwise
             */
            bool isVisible() const;

            //Parent
            /**
             * \brief Get the Id of the parent
             * \return A std::string containing the id of the parent
             */
            std::string getParentId() const;
            /**
             * \brief Set a new parent id
             * \param parent The id of the parent to apply to the LevelSprite
             */
            void setParentId(const std::string& parent);

            //Handle
            /**
             * \brief Draws the handle used to scale the Sprite
             * \param target Window where to draw the handle
             * \param spritePositionX x Coordinate of the Offset of the Handle
             * \param spritePositionY y Coordinate of the Offset of the Handle
             */
            void drawHandle(sf::RenderWindow& target, int spritePositionX, int spritePositionY);
            /**
             * \brief Get the HandlePoint of the LevelSprite at the given Position(x, y)
             * \param cameraPosition Position of the Scene Camera
             * \param posX x Coordinate of the Position you try to pick the HandlePoint
             * \param posY y Coordinate of the Position you try to pick the HandlePoint
             * \return The adress of the HandlePoint if the position is correct, nullptr otherwise
             */
            HandlePoint* getHandlePoint(Transform::UnitVector& cameraPosition, int posX, int posY);
        };
    }
}
