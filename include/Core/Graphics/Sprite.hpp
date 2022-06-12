#pragma once

#include <sfe/ComplexSprite.hpp>

#include <Component/Component.hpp>
#include <Engine/ResourceManager.hpp>
#include <Graphics/Color.hpp>
#include <Graphics/PositionTransformers.hpp>
#include <Graphics/Renderable.hpp>
#include <Graphics/Shader.hpp>
#include <Scene/Camera.hpp>
#include <Transform/Rect.hpp>
#include <Transform/Referential.hpp>
#include <Transform/UnitBasedObject.hpp>
#include <Types/Selectable.hpp>

namespace obe::graphics
{
    void make_null_texture();

    /**
     * \brief An element meant to be displayed in a Scene
     */
    class Sprite : public Transform::UnitBasedObject,
                   public Types::Selectable,
                   public Transform::Rect,
                   public Renderable,
                   public Component::Component<Sprite>,
                   public engine::ResourceManagedObject
    {
    protected:
        
        std::string m_parentId;
        std::string m_path;
        PositionTransformer m_position_transformer;
        Shader* m_shader = nullptr;
        sfe::ComplexSprite m_sprite;
        graphics::Texture m_texture;
        bool m_antiAliasing = true;

        void reset_unit(Transform::Units unit) override;
        void refresh_vector_texture(
            const Transform::UnitVector& surface_size, const std::array<sf::Vertex, 4>& vertices);

    public:
        /**
         * \nobind
         */
        static constexpr std::string_view ComponentType = "Sprite";
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
        void draw_handle(RenderTarget& surface, const Scene::Camera& camera) const;
        /**
         * \brief Get the blend color of the Sprite
         * \return A Color containing the blend color of the Sprite
         */
        [[nodiscard]] Color get_color() const;
        /**
         * \brief Get the Id of the parent
         * \return A std::string containing the id of the parent
         */
        [[nodiscard]] std::string get_parent_id() const;
        /**
         * \brief Get the path of the Texture loaded by the Sprite
         * \return A std::string containing the path of the Texture loaded
         *         by the Sprite (if any)
         */
        [[nodiscard]] std::string get_filesystem_path() const;
        /**
         * \brief Gets the PositionTransformer used by the Sprite
         * \return The PositionTransformer used by the Sprite
         */
        [[nodiscard]] PositionTransformer get_position_transformer() const;
        /**
         * \brief Get the Bounding Rect of the internal Sprite
         * \return A Rect representing the bounding rectangle of the
         *         internal Sprite
         */
        [[nodiscard]] Transform::Rect get_rect();
        [[nodiscard]] Shader& get_shader() const;
        /**
         * \brief Get the internal Sprite of the Sprite
         * \return A reference to the internal Sprite of the Sprite
         */
        sfe::ComplexSprite& get_internal_sprite();
        /**
         * \brief Get the height of the Sprite
         * \return The height of the Sprite (Including transformations such as
         *         rotations / scaling)
         */
        [[nodiscard]] double get_height() const;
        /**
         * \brief Get the width of the Sprite
         * \return The width of the Sprite (Including transformations such as
         *         rotations / scaling)
         */
        [[nodiscard]] double get_width() const;
        /**
         * \brief Gets a reference to the texture of the Sprite
         * \return A reference to the current texture of the Sprite
         */
        [[nodiscard]] const graphics::Texture& get_texture() const;

        /**
         * \brief Gets a reference to the texture of the Sprite
         * \return A reference to the current texture of the Sprite
         */
        [[nodiscard]] graphics::Texture& get_texture();
        /**
         * \brief Get the x Coordinate of the scale factor of the Sprite
         * \return -1 if the Sprite has been horizontally flipped, 1
         *         otherwise
         */
        [[nodiscard]] int get_x_scale_factor() const;
        /**
         * \brief Get the y Coordinate of the scale factor of the Sprite
         * \return -1 if the Sprite has been vertically flipped, 1
         *         otherwise
         */
        [[nodiscard]] int get_y_scale_factor() const;
        [[nodiscard]] bool get_anti_aliasing() const;
        [[nodiscard]] bool has_shader() const;
        [[nodiscard]] vili::node schema() const override;
        /**
         * \brief Dumps the content of the Sprite to a ComplexNode
         * \return vili::node containing the Sprite details
         */
        vili::node dump() const override;
        /**
         * \brief Loads the Sprite from a ComplexNode
         * \param data ComplexNode containing the data of the Sprite
         */
        void load(const vili::node& data) override;
        /**
         * \brief The Sprite will load the Texture at the given path
         * \param path A std::string containing the path of the texture to load
         */
        void load_texture(const std::string& path);
        /**
         * \brief Rotate the sprite
         * \param angle The angle to add to the Sprite (0 -> 360 where
         *        0 / 360 is the top)
         */
        void rotate(double angle);
        /**
         * \brief Apply a blend color to the Sprite
         * \param color A Color containing the color to blend
         *        (Color::White is default normal color)
         */
        void set_color(const Color& color);
        /**
         * \brief Set a new parent id
         * \param parent The id of the parent to apply to the Sprite
         */
        void set_parent_id(const std::string& parent);
        /**
         * \brief Sets the new Position Transform of the Sprite
         * \param transformer New PositionTransformer of the Sprite
         */
        void set_position_transformer(const PositionTransformer& transformer);
        /**
         * \brief Set the rotation of the sprite
         * \param rotate The new angle of the Sprite (0 -> 360 where 0 /
         *        360 is the top)
         */
        void set_rotation(double rotate);
        /**
         * \brief Set the rotation origin of the Sprite
         * \param x x Coordinate of the new rotation origin of the Sprite
         * \param y y Coordinate of the new rotation origin of the Sprite
         */
        void set_rotation_origin(int x, int y);
        /**
         * \brief Set the scaling origin of the Sprite
         * \param x x Coordinate of the new scaling origin of the Sprite
         * \param y y Coordinate of the new scaling origin of the Sprite
         */
        void set_scaling_origin(int x, int y);
        void set_shader(Shader* shader);
        /**
         * \brief Sets the Texture of the Sprite
         * \param texture Texture to set
         */
        void set_texture(const Texture& texture);
        void set_texture_rect(
            unsigned int x, unsigned int y, unsigned int width, unsigned int height);
        /**
         * \brief Set the translation origin of the Sprite
         * \param x x Coordinate of the new translation origin of the Sprite
         * \param y y Coordinate of the new translation origin of
         *        the Sprite
         */
        void set_translation_origin(int x, int y);
        void set_anti_aliasing(bool anti_aliasing);
        /**
         * \brief Reset internal Sprite Rect using texture size
         */
        void use_texture_size();

        void draw(RenderTarget& surface, const Scene::Camera& camera) override;
        void attach_resource_manager(engine::ResourceManager& resources) override;
        [[nodiscard]] std::string_view type() const override;
    };

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
     * \todo Move to Editor/Dev project
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
        [[nodiscard]] Transform::Rect& get_rect() const;
        /**
         * \brief Get the Referential of the HandlePoint
         * \return The Referential value
         */
        [[nodiscard]] Transform::Referential get_referential() const;
        /**
         * \brief Gets the type of the SpriteHandlePoint (either Rotate or
         * Scale) \return An enum value from SpriteHandlePointType
         * representing the type of the Handle Point
         */
        [[nodiscard]] SpriteHandlePointType get_type() const;
        /**
         * \brief Move the HandlePoint to the given Position
         * \param position Position where the HandlePoint should move to
         * \param camera Camera used to manipulate PositionTransformers
         */
        void set_position(
            const Transform::UnitVector& position, const Transform::UnitVector& camera);
    };

    /**
     * \todo Move to Editor/Dev project
     */
    class EditorSprite : public Sprite
    {
    private:
        std::vector<SpriteHandlePoint> m_handlePoints {};
    public:
        explicit EditorSprite(const std::string& id);
        /**
         * \brief Get the HandlePoint of the Sprite at the given
         *        Position(x, y)
         * \param camera_position Position of the Scene Camera
         * \param x x Coordinate of the Position you try to pick the
         *        HandlePoint
         * \param y y Coordinate of the Position you try to pick
         *        the HandlePoint
         * \return The address of the HandlePoint if the position
         *         is correct, nullptr otherwise
         */
        SpriteHandlePoint* get_handle_point(
            const Transform::UnitVector& camera_position, int x, int y);
    };
} // namespace obe::graphics
