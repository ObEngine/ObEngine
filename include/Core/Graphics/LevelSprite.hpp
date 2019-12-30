#pragma once

#include <sfe/ComplexSprite.hpp>

#include <Component/Component.hpp>
#include <Graphics/PositionTransformers.hpp>
#include <Graphics/Shader.hpp>
#include <Script/GlobalState.hpp>
#include <Transform/Movable.hpp>
#include <Transform/Rect.hpp>
#include <Transform/Referential.hpp>
#include <Transform/UnitBasedObject.hpp>
#include <Types/Selectable.hpp>
#include <Types/Serializable.hpp>

namespace obe::Graphics
{
    enum class LevelSpriteHandlePointType
    {
        ScaleHandle,
        RotateHandle
    };

    class LevelSprite;

    /**
     * \brief A HandlePoint to manipulate a LevelSprite Size
     * @Bind
     */
    class LevelSpriteHandlePoint
    {
    private:
        LevelSprite* m_sprite;
        Transform::Referential m_referential;
        LevelSpriteHandlePointType m_type;

    public:
        Transform::UnitVector m_dp;
        /**
         * \brief The radius of a HandlePoint
         */
        static unsigned int radius;
        /**
         * \brief Creates a Scale HandlePoint
         * \param parent Rect of the parent LevelSprite
         * \param ref Referential of the HandlePoint
         */
        LevelSpriteHandlePoint(LevelSprite* parent, Transform::Referential ref);
        /**
         * \brief Creates a Rotate HandlePoint
         * \param parent Rect of the parent LevelSprite
         */
        LevelSpriteHandlePoint(LevelSprite* parent);
        /**
         * \brief Get the rect of the parent LevelSprite
         * \return The Rect of the parent LevelSprite
         */
        Transform::Rect& getRect() const;
        /**
         * \brief Get the Referential of the HandlePoint
         * \return The Referential value
         */
        Transform::Referential getReferential() const;
        /**
         * \brief Gets the type of the LevelSpriteHandlePoint (either Rotate or
         * Scale) \return An enum value from LevelSpriteHandlePointType
         * representing the type of the Handle Point
         */
        LevelSpriteHandlePointType getType() const;
        /**
         * \brief Move the HandlePoint to the given Position
         * \param position Position where the HandlePoint should move to
         * \param camera Camera used to manipulate PositionTransformers
         */
        void moveTo(const Transform::UnitVector& position,
            const Transform::UnitVector& camera);
    };

    /**
     * \brief An element meant to be displayed in a Scene
     * @Bind
     */
    class LevelSprite : public Transform::UnitBasedObject,
                        public Types::Selectable,
                        public Transform::Rect,
                        public Component::Component<LevelSprite>
    {
    private:
        std::vector<LevelSpriteHandlePoint> m_handlePoints;
        int m_layer = 1;
        std::string m_parentId = "";
        std::string m_path = "";
        PositionTransformer m_positionTransformer;
        Shader* m_shader = nullptr;
        sfe::ComplexSprite m_sprite;
        const sf::Texture* m_texture;
        bool m_visible = true;
        int m_zdepth = 0;
        bool m_antiAliasing = true;

        void resetUnit(Transform::Units unit) override;

    public:
        static constexpr std::string_view ComponentType = "LevelSprite";
        bool m_layerChanged = false;
        /**
         * \brief Creates a new LevelSprite with the given Id
         * \param id A std::string containing the Id of the LevelSprite
         */
        explicit LevelSprite(const std::string& id);
        /**
         * \brief Draws the handle used to scale the Sprite
         * \param spritePositionX x Coordinate of the Offset of the Handle
         * \param spritePositionY y Coordinate of the Offset of the Handle
         */
        void drawHandle(const Transform::UnitVector& camera) const;
        /**
         * \brief Dumps the content of the LevelSprite to a ComplexNode
         * \param target ComplexNode where to serialize the LevelSprite
         */
        void dump(vili::ComplexNode& target) const override;
        /**
         * \brief Get the blend color of the LevelSprite
         * \return A sf::Color containing the blend color of the LevelSprite
         */
        sf::Color getColor() const;
        /**
         * \brief Get the HandlePoint of the LevelSprite at the given
         * Position(x, y) \param cameraPosition Position of the Scene Camera
         * \param posX x Coordinate of the Position you try to pick the
         * HandlePoint \param posY y Coordinate of the Position you try to pick
         * the HandlePoint \return The adress of the HandlePoint if the position
         * is correct, nullptr otherwise
         */
        LevelSpriteHandlePoint* getHandlePoint(
            Transform::UnitVector& cameraPosition, int posX, int posY);
        /**
         * \brief Get the layer of the Sprite
         * \return An int containing the Layer where the sprite is (Higher layer
         * is behind lower ones)
         */
        int getLayer() const;
        /**
         * \brief Get the Id of the parent
         * \return A std::string containing the id of the parent
         */
        std::string getParentId() const;
        /**
         * \brief Get the path of the sf::Texture loaded by the Sprite
         * \return A std::string containing the path of the sf::Texture loaded
         * by the Sprite (if any)
         */
        std::string getPath() const;
        /**
         * \brief Gets the PositionTransformer used by the LevelSprite
         * \return The PositionTransformer used by the LevelSprite
         */
        PositionTransformer getPositionTransformer() const;
        /**
         * \brief Get the Bounding Rect of the internal Sprite
         * \return A sf::FloatRect representing the bounding rectangle of the
         * internal Sprite
         */
        sf::FloatRect getRect();
        Shader* getShader() const;
        /**
         * \brief Get the internal Sprite of the LevelSprite
         * \return A reference to the internal Sprite of the LevelSprite
         */
        sfe::ComplexSprite& getSprite();
        /**
         * \brief Get the height of the LevelSprite
         * \return The height of the Sprite (Including transformations such as
         * rotations / scaling)
         */
        double getSpriteHeight() const;
        /**
         * \brief Get the width of the LevelSprite
         * \return The width of the Sprite (Including transformations such as
         * rotations / scaling)
         */
        double getSpriteWidth() const;
        /**
         * \brief Gets a reference to the texture of the LevelSprite
         * \return A reference to the current texture of the LevelSprite
         */
        const sf::Texture& getTexture() const;
        /**
         * \brief Get the x Coordinate of the scale factor of the LevelSprite
         * \return -1 if the LevelSprite has been horizontally flipped, 1
         * otherwise
         */
        int getXScaleFactor() const;
        /**
         * \brief Get the y Coordinate of the scale factor of the LevelSprite
         * \return -1 if the LevelSprite has been vertically flipped, 1
         * otherwise
         */
        int getYScaleFactor() const;
        /**
         * \brief Get the Z-depth of the Sprite
         * \return An int containing the z-depth where the sprite is (Higher
         * z-depth is behind lower ones)
         */
        int getZDepth() const;
        bool getAntiAliasing() const;
        bool hasShader() const;
        /**
         * \brief Get the visibility of the LevelSprite
         * \return true if the LevelSprite is visible, false otherwise
         */
        bool isVisible() const;
        /**
         * \brief Loads the LevelSprite from a ComplexNode
         * \param data ComplexNode containing the data of the LevelSprite
         */
        void load(vili::ComplexNode& data) override;
        /**
         * \brief The LevelSprite will load the sf::Texture at the given path
         * \param path A std::string containing the path of the texture to load
         */
        void loadTexture(const std::string& path);
        /**
         * \brief Rotate the sprite
         * \param addRotate The angle to add to the LevelSprite (0 -> 360 where
         * 0 / 360 is the top)
         */
        void rotate(double addRotate);
        /**
         * \brief Apply a blend color to the LevelSprite
         * \param newColor A sf::Color containing the color to blend
         * (sf::Color::White is default normal color)
         */
        void setColor(sf::Color newColor);
        /**
         * \brief Set the layer of the Sprite
         * \param layer Layer where to put the sprite (Higher layer is behind
         * lower ones)
         */
        void setLayer(int layer);
        /**
         * \brief Set a new parent id
         * \param parent The id of the parent to apply to the LevelSprite
         */
        void setParentId(const std::string& parent);
        /**
         * \brief Sets the new Position Transform of the LevelSprite
         * \param transformer New PositionTransformer of the LevelSprite
         */
        void setPositionTransformer(PositionTransformer transformer);
        /**
         * \brief Set the rotation of the sprite
         * \param rotate The new angle of the LevelSprite (0 -> 360 where 0 /
         * 360 is the top)
         */
        void setRotation(double rotate);
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
        void setShader(Shader* shader);
        /**
         * \brief Sets the Texture of the LevelSprite
         * \param texture Texture to set
         */
        void setTexture(const sf::Texture& texture);
        void setTextureRect(unsigned int x, unsigned int y, unsigned int width,
            unsigned int height);
        /**
         * \brief Set the translation origin of the LevelSprite
         * \param x x Coordinate of the new translation origin of the
         * LevelSprite \param y y Coordinate of the new translation origin of
         * the LevelSprite
         */
        void setTranslationOrigin(int x, int y);
        /**
         * \brief Set the visibility of the LevelSprite
         * \param visible If visible is equal to true, the LevelSprite will be
         * visible, if visible is equal to false, it won't be visible
         */
        void setVisible(bool visible);
        /**
         * \brief Set the Z-Depth of the Sprite (SubLayers)
         * \param zdepth z-depth of the Sprite (Higher z-depth is behind lower
         * ones)
         */
        void setZDepth(int zdepth);
        void setAntiAliasing(bool antiAliasing);
        /**
         * \brief Reset internal LevelSprite Rect using texture size
         */
        void useTextureSize();

        void draw(const Transform::UnitVector& camera);
        std::string_view type() const override;
    };
} // namespace obe::Graphics