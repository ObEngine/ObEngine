#pragma once

#include <sfe/ComplexSprite.hpp>

#include <Component/Component.hpp>
#include <Engine/ResourceManager.hpp>
#include <Graphics/Color.hpp>
#include <Graphics/PositionTransformers.hpp>
#include <Graphics/Shader.hpp>
#include <Transform/Rect.hpp>
#include <Transform/Referential.hpp>
#include <Transform/UnitBasedObject.hpp>
#include <Types/Selectable.hpp>

namespace obe::Graphics
{
    void MakeNullTexture();
    /**
     * \brief Type of the handle point of a Sprite (either scale or rotate)
     */
    enum class SpriteHandlePointType
    {
        /**
         * \brief Handle point used to scale the sprite (located on 8 points around the
         *        sprite rect)
         */
        ScaleHandle,
        /**
         * \brief Handle point used to rotate the sprite (single point located outside of
         *        the sprite rect)
         */
        RotateHandle
    };

    class Sprite;

    /**
     * \brief A HandlePoint to manipulate a Sprite Size
     */
    class SpriteHandlePoint
    {
    private:
        Sprite& m_sprite;
        Transform::Referential m_referential;
        SpriteHandlePointType m_type;

    public:
        Transform::UnitVector m_dp;
        /**
         * \brief The radius of a HandlePoint
         */
        static unsigned int radius;
        /**
         * \brief Creates a Scale HandlePoint
         * \param parent Rect of the parent Sprite
         * \param ref Referential of the HandlePoint
         */
        SpriteHandlePoint(Sprite& parent, Transform::Referential ref);
        /**
         * \brief Creates a Rotate HandlePoint
         * \param parent Rect of the parent Sprite
         */
        explicit SpriteHandlePoint(Sprite& parent);
        /**
         * \brief Get the rect of the parent Sprite
         * \return The Rect of the parent Sprite
         */
        [[nodiscard]] Transform::Rect& getRect() const;
        /**
         * \brief Get the Referential of the HandlePoint
         * \return The Referential value
         */
        [[nodiscard]] Transform::Referential getReferential() const;
        /**
         * \brief Gets the type of the SpriteHandlePoint (either Rotate or
         * Scale) \return An enum value from SpriteHandlePointType
         * representing the type of the Handle Point
         */
        [[nodiscard]] SpriteHandlePointType getType() const;
        /**
         * \brief Move the HandlePoint to the given Position
         * \param position Position where the HandlePoint should move to
         * \param camera Camera used to manipulate PositionTransformers
         */
        void moveTo(
            const Transform::UnitVector& position, const Transform::UnitVector& camera);
    };

    /**
     * \brief An element meant to be displayed in a Scene
     * \bind{Sprite}
     */
    class Sprite : public Transform::UnitBasedObject,
                   public Types::Selectable,
                   public Transform::Rect,
                   public Component::Component<Sprite>,
                   public Engine::ResourceManagedObject
    {
    private:
        std::vector<SpriteHandlePoint> m_handlePoints {};
        int m_layer = 1;
        std::string m_parentId = "";
        std::string m_path = "";
        PositionTransformer m_positionTransformer;
        Shader* m_shader = nullptr;
        sfe::ComplexSprite m_sprite;
        Graphics::Texture m_texture;
        bool m_visible = true;
        int m_zdepth = 0;
        bool m_antiAliasing = true;

        void resetUnit(Transform::Units unit) override;

    public:
        /**
         * \nobind
         */
        static constexpr std::string_view ComponentType = "Sprite";
        bool m_layerChanged = false;
        /**
         * \brief Creates a new Sprite with the given Id
         * \param id A std::string containing the Id of the Sprite
         */
        explicit Sprite(const std::string& id);
        /**
         * \brief Draws the handle used to scale the Sprite
         * \param surface RenderSurface where to render the handle
         * \param camera contains the offset for drawing the handle
         */
        void drawHandle(RenderTarget surface, const Transform::UnitVector& camera) const;
        /**
         * \brief Dumps the content of the Sprite to a ComplexNode
         * \param target ComplexNode where to serialize the Sprite
         */
        vili::node dump() const override;
        /**
         * \brief Get the blend color of the Sprite
         * \return A Color containing the blend color of the Sprite
         */
        [[nodiscard]] Color getColor() const;
        /**
         * \brief Get the HandlePoint of the Sprite at the given
         *        Position(x, y)
         * \param cameraPosition Position of the Scene Camera
         * \param posX x Coordinate of the Position you try to pick the
         *        HandlePoint
         * \param posY y Coordinate of the Position you try to pick
         *        the HandlePoint
         * \return The address of the HandlePoint if the position
         *         is correct, nullptr otherwise
         */
        SpriteHandlePoint* getHandlePoint(
            Transform::UnitVector& cameraPosition, int posX, int posY);
        /**
         * \brief Get the layer of the Sprite
         * \return An int containing the Layer where the sprite is (Higher layer
         *         is behind lower ones)
         */
        [[nodiscard]] int getLayer() const;
        /**
         * \brief Get the Id of the parent
         * \return A std::string containing the id of the parent
         */
        [[nodiscard]] std::string getParentId() const;
        /**
         * \brief Get the path of the Texture loaded by the Sprite
         * \return A std::string containing the path of the Texture loaded
         *         by the Sprite (if any)
         */
        [[nodiscard]] std::string getPath() const;
        /**
         * \brief Gets the PositionTransformer used by the Sprite
         * \return The PositionTransformer used by the Sprite
         */
        [[nodiscard]] PositionTransformer getPositionTransformer() const;
        /**
         * \brief Get the Bounding Rect of the internal Sprite
         * \return A Rect representing the bounding rectangle of the
         *         internal Sprite
         */
        Transform::Rect getRect();
        [[nodiscard]] Shader& getShader() const;
        /**
         * \brief Get the internal Sprite of the Sprite
         * \return A reference to the internal Sprite of the Sprite
         */
        sfe::ComplexSprite& getSprite();
        /**
         * \brief Get the height of the Sprite
         * \return The height of the Sprite (Including transformations such as
         *         rotations / scaling)
         */
        [[nodiscard]] double getSpriteHeight() const;
        /**
         * \brief Get the width of the Sprite
         * \return The width of the Sprite (Including transformations such as
         *         rotations / scaling)
         */
        [[nodiscard]] double getSpriteWidth() const;
        /**
         * \brief Gets a reference to the texture of the Sprite
         * \return A reference to the current texture of the Sprite
         */
        [[nodiscard]] const Graphics::Texture& getTexture() const;
        /**
         * \brief Get the x Coordinate of the scale factor of the Sprite
         * \return -1 if the Sprite has been horizontally flipped, 1
         *         otherwise
         */
        [[nodiscard]] int getXScaleFactor() const;
        /**
         * \brief Get the y Coordinate of the scale factor of the Sprite
         * \return -1 if the Sprite has been vertically flipped, 1
         *         otherwise
         */
        [[nodiscard]] int getYScaleFactor() const;
        /**
         * \brief Get the Z-depth of the Sprite
         * \return An int containing the z-depth where the sprite is (Higher
         *         z-depth is behind lower ones)
         */
        [[nodiscard]] int getZDepth() const;
        [[nodiscard]] bool getAntiAliasing() const;
        [[nodiscard]] bool hasShader() const;
        /**
         * \brief Get the visibility of the Sprite
         * \return true if the Sprite is visible, false otherwise
         */
        [[nodiscard]] bool isVisible() const;
        /**
         * \brief Loads the Sprite from a ComplexNode
         * \param data ComplexNode containing the data of the Sprite
         */
        void load(vili::node& data) override;
        /**
         * \brief The Sprite will load the Texture at the given path
         * \param path A std::string containing the path of the texture to load
         */
        void loadTexture(const std::string& path);
        /**
         * \brief Rotate the sprite
         * \param addRotate The angle to add to the Sprite (0 -> 360 where
         *        0 / 360 is the top)
         */
        void rotate(double addRotate);
        /**
         * \brief Apply a blend color to the Sprite
         * \param color A Color containing the color to blend
         *        (Color::White is default normal color)
         */
        void setColor(const Color& color);
        /**
         * \brief Set the layer of the Sprite
         * \param layer Layer where to put the sprite (Higher layer is behind
         * lower ones)
         */
        void setLayer(int layer);
        /**
         * \brief Set a new parent id
         * \param parent The id of the parent to apply to the Sprite
         */
        void setParentId(const std::string& parent);
        /**
         * \brief Sets the new Position Transform of the Sprite
         * \param transformer New PositionTransformer of the Sprite
         */
        void setPositionTransformer(const PositionTransformer& transformer);
        /**
         * \brief Set the rotation of the sprite
         * \param rotate The new angle of the Sprite (0 -> 360 where 0 /
         *        360 is the top)
         */
        void setRotation(double rotate);
        /**
         * \brief Set the rotation origin of the Sprite
         * \param x x Coordinate of the new rotation origin of the Sprite
         * \param y y Coordinate of the new rotation origin of the Sprite
         */
        void setRotationOrigin(int x, int y);
        /**
         * \brief Set the scaling origin of the Sprite
         * \param x x Coordinate of the new scaling origin of the Sprite
         * \param y y Coordinate of the new scaling origin of the Sprite
         */
        void setScalingOrigin(int x, int y);
        void setShader(Shader* shader);
        /**
         * \brief Sets the Texture of the Sprite
         * \param texture Texture to set
         */
        void setTexture(const Texture& texture);
        void setTextureRect(
            unsigned int x, unsigned int y, unsigned int width, unsigned int height);
        /**
         * \brief Set the translation origin of the Sprite
         * \param x x Coordinate of the new translation origin of the Sprite
         * \param y y Coordinate of the new translation origin of
         *        the Sprite
         */
        void setTranslationOrigin(int x, int y);
        /**
         * \brief Set the visibility of the Sprite
         * \param visible If visible is equal to true, the Sprite will be
         *        visible, if visible is equal to false, it won't be visible
         */
        void setVisible(bool visible);
        /**
         * \brief Set the Z-Depth of the Sprite (SubLayers)
         * \param zdepth z-depth of the Sprite (Higher z-depth is behind lower
         *        ones)
         */
        void setZDepth(int zdepth);
        void setAntiAliasing(bool antiAliasing);
        /**
         * \brief Reset internal Sprite Rect using texture size
         */
        void useTextureSize();

        void draw(RenderTarget surface, const Transform::UnitVector& camera);
        void attachResourceManager(Engine::ResourceManager& resources) override;
        [[nodiscard]] std::string_view type() const override;
    };
} // namespace obe::Graphics