#include <Engine/ResourceManager.hpp>
#include <Graphics/DrawUtils.hpp>
#include <Graphics/Exceptions.hpp>
#include <Graphics/Sprite.hpp>
#include <System/Path.hpp>
#include <System/Window.hpp>
#include <Utils/MathUtils.hpp>

namespace obe::graphics
{
    static sf::Image NullImage;
    static graphics::Texture NullTexture;
    void make_null_texture()
    {
        NullImage.create(100, 100, sf::Color::Transparent);
        for (unsigned int i = 0; i < NullImage.getSize().x; i++)
        {
            for (unsigned int j = 0; j < NullImage.getSize().y; j++)
            {
                if (i == 0 || j == 0 || i == NullImage.getSize().x - 1
                    || j == NullImage.getSize().y - 1 || i == j
                    || i == ((NullImage.getSize().x - 1) - j))
                    NullImage.setPixel(i, j, sf::Color::Red);
            }
        }
        NullTexture.loadFromImage(NullImage);
    }

    sf::Vertex to_sf_vertex(const Transform::UnitVector& uv)
    {
        return sf::Vertex(sf::Vector2f(uv.x, uv.y));
    }

    void Sprite::refresh_vector_texture(
        const Transform::UnitVector& surface_size, const std::array<sf::Vertex, 4>& vertices)
    {
        const Transform::UnitVector px_size = m_size.to<Transform::Units::ScenePixels>();
        const unsigned int new_width = static_cast<unsigned int>(px_size.x);
        const unsigned int new_height = static_cast<unsigned int>(px_size.y);

        const Transform::UnitVector texture_size = m_texture.getSize();

        if (new_width != static_cast<unsigned int>(texture_size.x)
            || new_height != static_cast<unsigned int>(texture_size.y))
        {
            m_sprite.setTextureRect(sf::IntRect(0, 0, px_size.x, px_size.y));
            const auto [min_vx, max_vx] = std::minmax_element(vertices.begin(), vertices.end(),
                [](const sf::Vertex& vert1, const sf::Vertex& vert2) -> float {
                    return vert1.position.x < vert2.position.x;
                });
            const auto [min_vy, max_vy] = std::minmax_element(vertices.begin(), vertices.end(),
                [](const sf::Vertex& vert1, const sf::Vertex& vert2) -> float {
                    return vert1.position.y < vert2.position.y;
                });
            const float min_x = min_vx->position.x;
            const float max_x = max_vx->position.x;
            const float min_y = min_vy->position.y;
            const float max_y = max_vy->position.y;
            if (((min_x >= 0 && min_x <= surface_size.x) || (max_x >= 0 && max_x <= surface_size.x))
                && ((min_y >= 0 && min_y <= surface_size.y) || (max_y >= 0 && max_y <= surface_size.y)))
            {
                m_texture.setSizeHint(new_width, new_height);
            }
        }
    }

    Sprite::Sprite(const std::string& id)
        : Selectable(false)
        , Component(id)
    {
        this->set_texture(NullTexture);

        m_position_transformer = PositionTransformer("Camera", "Camera");
    }

    void Sprite::use_texture_size()
    {
        const Transform::UnitVector texture_size = this->get_texture().getSize();
        const Transform::UnitVector initial_sprite_size(
            texture_size.x, texture_size.y, Transform::Units::ScenePixels);
        this->setSize(initial_sprite_size);
    }

    void Sprite::draw(RenderTarget& surface, const Scene::Camera& camera)
    {
        const Transform::UnitVector pixel_camera
            = camera.getPosition().to<Transform::Units::ScenePixels>();
        std::array<sf::Vertex, 4> vertices;

        /*auto size = Rect::getSize();
        if (m_position_transformer.get_x_transformer_name() == "Parallax" && m_position_transformer.get_y_transformer_name() == "Parallax")
        {
            Rect::setSize(size * camera.getSize().y * (m_layer * 0.1), Transform::Referential::TopLeft);
        }*/

        vertices[0] = to_sf_vertex(m_position_transformer(
            Rect::getPosition(Transform::Referential::TopLeft), pixel_camera, m_layer)
                                     .to<Transform::Units::ScenePixels>());
        vertices[1] = to_sf_vertex(m_position_transformer(
            Rect::getPosition(Transform::Referential::BottomLeft), pixel_camera, m_layer)
                                     .to<Transform::Units::ScenePixels>());
        vertices[2] = to_sf_vertex(m_position_transformer(
            Rect::getPosition(Transform::Referential::TopRight), pixel_camera, m_layer)
                                     .to<Transform::Units::ScenePixels>());
        vertices[3] = to_sf_vertex(m_position_transformer(
            Rect::getPosition(Transform::Referential::BottomRight), pixel_camera, m_layer)
                                     .to<Transform::Units::ScenePixels>());

        /*if (m_position_transformer.get_x_transformer_name() == "Parallax"
            && m_position_transformer.get_y_transformer_name() == "Parallax")
        {
            Rect::setSize(size, Transform::Referential::TopLeft);
        }*/

        if (m_texture.getAutoscaling())
        {
            const Transform::UnitVector surface_size = surface.get_size();
            refresh_vector_texture(surface_size, vertices);
        }

        m_sprite.setVertices(vertices);

        if (m_shader)
            surface.draw(m_sprite, m_shader);
        else
            surface.draw(m_sprite);

        if (m_selected)
        {
            this->draw_handle(surface, camera);
        }
    }

    void Sprite::attach_resource_manager(engine::ResourceManager& resources)
    {
        this->set_anti_aliasing(resources.default_anti_aliasing);
        ResourceManagedObject::attach_resource_manager(resources);
    }

    std::string_view Sprite::type() const
    {
        return ComponentType;
    }

    void Sprite::load_texture(const std::string& path)
    {
        if (!path.empty() and path != m_path)
        {
            m_path = path;
            if (m_resources)
            {
                m_texture = m_resources->get_texture(System::Path(path), m_antiAliasing);
            }
            else
            {
                m_texture.reset();
                m_texture.loadFromFile(System::Path(path).find());
                m_texture.setAntiAliasing(m_antiAliasing);
            }

            m_sprite.setTexture(m_texture);
            m_sprite.setTextureRect(
                sf::IntRect(0, 0, m_texture.getSize().x, m_texture.getSize().y));
        }
    }

    void Sprite::reset_unit(Transform::Units unit)
    {
    }

    void Sprite::set_texture(const Texture& texture)
    {
        // m_texture = std::shared_ptr<Texture>(std::shared_ptr<Texture>(), texture);
        m_sprite.setTexture(texture);
        m_sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
    }

    void Sprite::set_texture_rect(
        unsigned int x, unsigned int y, unsigned int width, unsigned int height)
    {
        m_sprite.setTextureRect(sf::IntRect(x, y, width, height));
    }

    const graphics::Texture& Sprite::get_texture() const
    {
        return m_texture;
    }

    graphics::Texture& Sprite::get_texture()
    {
        return m_texture;
    }

    void Sprite::set_anti_aliasing(bool anti_aliasing)
    {
        if (anti_aliasing != m_antiAliasing && !m_path.empty())
        {
            m_antiAliasing = anti_aliasing;
            this->load_texture(m_path);
        }
        else
        {
            m_antiAliasing = anti_aliasing;
        }
    }

    void Sprite::set_rotation(double rotate)
    {
        Rect::setRotation(rotate, this->getPosition(Transform::Referential::Center));
    }

    void Sprite::rotate(double angle)
    {
        Rect::rotate(angle, this->getPosition(Transform::Referential::Center));
    }

    void Sprite::set_scaling_origin(int x, int y)
    {
        m_sprite.setScalingOrigin(x, y);
    }

    void Sprite::draw_handle(RenderTarget& surface, const Scene::Camera& camera) const
    {
        const Transform::UnitVector pixel_camera
            = camera.getPosition().to<Transform::Units::ScenePixels>();
        const Transform::UnitVector position
            = m_position_transformer(m_position, pixel_camera, m_layer)
                  .to<Transform::Units::ScenePixels>();
        Rect::draw(surface, position.x, position.y);
    }

    void Sprite::set_translation_origin(int x, int y)
    {
        m_sprite.setTranslationOrigin(x, y);
    }

    void Sprite::set_rotation_origin(int x, int y)
    {
        m_sprite.setRotationOrigin(x, y);
    }

    void Sprite::set_color(const Color& color)
    {
        m_sprite.setColor(color);
    }

    Color Sprite::get_color() const
    {
        return m_sprite.getColor();
    }

    sfe::ComplexSprite& Sprite::get_internal_sprite()
    {
        return m_sprite;
    }

    double Sprite::get_width() const
    {
        return m_sprite.getGlobalBounds().width;
    }

    double Sprite::get_height() const
    {
        return m_sprite.getGlobalBounds().height;
    }

    bool Sprite::get_anti_aliasing() const
    {
        return m_antiAliasing;
    }

    std::string Sprite::get_filesystem_path() const
    {
        return m_path;
    }

    Transform::Rect Sprite::get_rect()
    {
        const Transform::UnitVector px_position
            = Rect::m_position.to<Transform::Units::ScenePixels>();
        const Transform::UnitVector px_size(m_sprite.getGlobalBounds().width,
            m_sprite.getGlobalBounds().height, Transform::Units::ScenePixels);

        m_sprite.setPosition(px_position.x, px_position.y);
        Transform::Rect rect = Transform::Rect(px_position, px_size);
        rect.set_position(Transform::UnitVector(m_sprite.getGlobalBounds().left,
            m_sprite.getGlobalBounds().top, Transform::Units::ScenePixels));
        return rect;
    }

    std::string Sprite::get_parent_id() const
    {
        return m_parentId;
    }

    void Sprite::set_parent_id(const std::string& parent)
    {
        m_parentId = parent;
    }

    int Sprite::get_x_scale_factor() const
    {
        return obe::Utils::Math::sign(m_sprite.getScale().x);
    }

    int Sprite::get_y_scale_factor() const
    {
        return obe::Utils::Math::sign(m_sprite.getScale().y);
    }

    void Sprite::set_position_transformer(const PositionTransformer& transformer)
    {
        m_position_transformer = transformer;
    }

    PositionTransformer Sprite::get_position_transformer() const
    {
        return m_position_transformer;
    }

    unsigned int SpriteHandlePoint::radius = 6;
    SpriteHandlePoint::SpriteHandlePoint(Sprite& parent, Transform::Referential ref)
        : m_sprite(parent)
        , m_referential(ref)
    {
        m_type = SpriteHandlePointType::ScaleHandle;
    }

    SpriteHandlePoint::SpriteHandlePoint(Sprite& parent)
        : m_sprite(parent)
    {
        m_type = SpriteHandlePointType::RotateHandle;
    }

    void SpriteHandlePoint::set_position(
        const Transform::UnitVector& position, const Transform::UnitVector& camera)
    {
        m_dp = m_sprite.get_position_transformer()(position, -camera, m_sprite.get_layer());
        if (m_type == SpriteHandlePointType::ScaleHandle)
        {
            const Transform::UnitVector pos
                = m_sprite.getPosition(m_referential).to<Transform::Units::ScenePixels>();
            const Transform::UnitVector opposite_pos
                = m_sprite.getPosition(m_referential.flip()).to<Transform::Units::ScenePixels>();

            if (m_referential.isOnCorner())
            {
                const Transform::UnitVector center_sprite_pos
                    = m_sprite.getPosition(Transform::Referential::Center);
                const double sprite_angle = m_sprite.getRotation();
                const Transform::UnitVector opposite_pos_in_ref
                    = opposite_pos.rotate(sprite_angle, center_sprite_pos);
                const Transform::UnitVector pos_in_ref = pos.rotate(sprite_angle, center_sprite_pos);
                const Transform::UnitVector cursor_in_ref = m_dp.rotate(sprite_angle, center_sprite_pos);
                const Transform::UnitVector scale_vector
                    = (cursor_in_ref - opposite_pos_in_ref) / (pos_in_ref - opposite_pos_in_ref);
                const double v_scale = std::max(scale_vector.x, scale_vector.y);
                if ((cursor_in_ref - opposite_pos_in_ref).x != 0
                    && (cursor_in_ref - opposite_pos_in_ref).y != 0)
                    m_sprite.scale(Transform::UnitVector(v_scale, v_scale, m_sprite.getSize().unit),
                        m_referential.flip());
            }
            else
            {
                const Transform::UnitVector e1 = opposite_pos - pos;
                const Transform::UnitVector e2 = m_dp - pos;

                const double val_dp = e1.x * e2.x + e1.y * e2.y;
                const double len = e1.x * e1.x + e1.y * e1.y;

                /*m_dp.x = pos.x + (valDp * e1.x) / len;
                m_dp.y = pos.y + (valDp * e1.y) / len;*/
                const Transform::UnitVector npp(
                    pos.x + (val_dp * e1.x) / len, pos.y + (val_dp * e1.y) / len, m_dp.unit);
                m_sprite.setPointPosition(npp, m_referential);
            }
        }
        else
        {
            const Transform::UnitVector center
                = m_sprite.getPosition(Transform::Referential::Center)
                      .to<Transform::Units::ScenePixels>();
            const double n = (90 + ((m_sprite.getScaleFactor().y < 0) ? 180 : 0))
                - (std::atan2(center.y - m_dp.y, center.x - m_dp.x)) * 180.0 / obe::Utils::Math::pi;

            m_sprite.set_rotation(std::fmod(n, 360));
        }
    }

    Transform::Referential SpriteHandlePoint::get_referential() const
    {
        return m_referential;
    }

    SpriteHandlePointType SpriteHandlePoint::get_type() const
    {
        return m_type;
    }

    Transform::Rect& SpriteHandlePoint::get_rect() const
    {
        return m_sprite;
    }

    vili::node Sprite::dump() const
    {
        vili::node result = vili::object {};
        result.emplace("path", m_path);

        const Transform::UnitVector sprite_position_rect = this->getPosition().to(m_unit);
        const Transform::UnitVector sprite_size_rect = this->getSize().to(m_unit);
        result.emplace("rect",
            vili::object { { "x", sprite_position_rect.x }, { "y", sprite_position_rect.y },
                { "width", sprite_size_rect.x }, { "height", sprite_size_rect.y },
                { "unit", Transform::UnitsMeta::toString(m_unit) } });

        result.emplace("rotation", m_angle);
        result.emplace("layer", m_layer);
        result.emplace("sublayer", m_sublayer);
        result.emplace("transform",
            vili::object { { "x", m_position_transformer.get_x_transformer_name() },
                { "y", m_position_transformer.get_y_transformer_name() } });
        if (!m_visible)
        {
            result.emplace("visible", m_visible);
        }
        const Color& color = m_sprite.getColor();
        if (color != Color::White)
        {
            result.emplace("color", color.dump());
        }
        return result;
    }

    void Sprite::load(const vili::node& data)
    {
        if (data.contains("path"))
        {
            this->load_texture(data.at("path"));
        }

        if (data.contains("rect"))
        {
            obe::Transform::Referential referential_pos;
            Transform::UnitVector sprite_pos(0, 0);
            Transform::UnitVector sprite_size(1, 1);
            const vili::node& rect = data.at("rect");
            if (rect.contains("unit"))
            {
                this->setWorkingUnit(Transform::UnitsMeta::fromString(rect.at("unit")));
            }
            sprite_pos.unit = m_unit;
            sprite_pos.x = rect.at("x");
            sprite_pos.y = rect.at("y");
            sprite_size.unit = m_unit;
            sprite_size.x = rect.at("width");
            sprite_size.y = rect.at("height");
            sprite_pos = sprite_pos.to<Transform::Units::SceneUnits>();
            sprite_size = sprite_size.to<Transform::Units::SceneUnits>();
            if (rect.contains("referential"))
                referential_pos = obe::Transform::Referential::FromString(rect.at("referential"));
            this->setPosition(sprite_pos, referential_pos);
            this->setSize(sprite_size, referential_pos);
        }

        if (data.contains("rotation"))
        {
            this->set_rotation(data.at("rotation"));
        }

        if (data.contains("layer"))
        {
            this->set_layer(data.at("layer"));
        }

        if (data.contains("sublayer"))
        {
            this->set_sublayer(data.at("sublayer"));
        }

        if (data.contains("antiAliasing"))
        {
            this->set_anti_aliasing(data.at("antiAliasing"));
        }

        if (data.contains("transform"))
        {
            std::string sprite_x_transformer = "Camera";
            std::string sprite_y_transformer = "Camera";
            const vili::node& transform = data.at("transform");
            if (transform.contains("x"))
            {
                sprite_x_transformer = transform.at("x");
            }
            if (transform.contains("y"))
            {
                sprite_y_transformer = transform.at("y");
            }
            const PositionTransformer position_transformer(sprite_x_transformer, sprite_y_transformer);
            this->set_position_transformer(position_transformer);
        }

        if (data.contains("color"))
        {
            Color sprite_color;
            sprite_color.load(data.at("color"));
            this->set_color(sprite_color);
        }

        if (data.contains("visible"))
        {
            this->set_visible(data.at("visible"));
        }
    }

    void Sprite::set_shader(Shader* shader)
    {
        m_shader = shader;
        m_shader->setUniform("texture", sf::Shader::CurrentTexture);
    }

    Shader& Sprite::get_shader() const
    {
        return *m_shader;
    }

    bool Sprite::has_shader() const
    {
        return (m_shader != nullptr);
    }

    vili::node Sprite::schema() const
    {
        return vili::object {};
    }

    EditorSprite::EditorSprite(const std::string& id)
        : Sprite(id)
    {
        for (Transform::Referential& ref : Transform::Referential::Referentials)
        {
            m_handlePoints.emplace_back(*this, ref);
        }
        m_handlePoints.emplace_back(*this);
    }

    SpriteHandlePoint* EditorSprite::get_handle_point(
        const Transform::UnitVector& camera_position, int x, int y)
    {
        const Transform::UnitVector pixel_camera
            = camera_position.to<Transform::Units::ScenePixels>();
        Transform::UnitVector target_pos
            = Transform::UnitVector(x, y, Transform::Units::ScenePixels);
        target_pos = m_position_transformer(target_pos, -pixel_camera, m_layer);
        unsigned int i = 0;
        for (Transform::Referential& ref : Transform::Referential::Referentials)
        {
            const Transform::UnitVector ref_point
                = Rect::getPosition(ref).to<Transform::Units::ScenePixels>();
            int lower_x_bound = std::min(
                ref_point.x - SpriteHandlePoint::radius, ref_point.x + SpriteHandlePoint::radius);
            int upper_x_bound = std::max(
                ref_point.x - SpriteHandlePoint::radius, ref_point.x + SpriteHandlePoint::radius);
            if (obe::Utils::Math::isBetween(target_pos.x, lower_x_bound, upper_x_bound)
                && ref != Transform::Referential::Center)
            {
                int lower_y_bound = std::min(
                    ref_point.y - SpriteHandlePoint::radius, ref_point.y + SpriteHandlePoint::radius);
                int upper_y_bound = std::max(
                    ref_point.y - SpriteHandlePoint::radius, ref_point.y + SpriteHandlePoint::radius);
                if (obe::Utils::Math::isBetween(target_pos.y, lower_y_bound, upper_y_bound))
                    return &m_handlePoints[i];
            }
            i++;
        }

        const double rad_angle = obe::Utils::Math::convertToRadian(-m_angle);
        const double cos_angle = std::cos(rad_angle);
        const double sin_angle = std::sin(rad_angle);
        const Transform::UnitVector top_pos
            = this->getPosition(Transform::Referential::Top).to<Transform::Units::ScenePixels>();
        Transform::UnitVector rot_handle = top_pos;
        Transform::UnitVector result;
        const double dy = m_size.y / 4;
        result.x = (-dy * sin_angle) * -1;
        result.y = (dy * cos_angle) * -1;
        rot_handle.add(result);

        const int lower_x_bound = std::min(
            rot_handle.x - SpriteHandlePoint::radius, rot_handle.x + SpriteHandlePoint::radius);
        const int upper_x_bound = std::max(
            rot_handle.x - SpriteHandlePoint::radius, rot_handle.x + SpriteHandlePoint::radius);
        if (obe::Utils::Math::isBetween(target_pos.x, lower_x_bound, upper_x_bound))
        {
            const int lower_y_bound = std::min(
                rot_handle.y - SpriteHandlePoint::radius, rot_handle.y + SpriteHandlePoint::radius);
            const int upper_y_bound = std::max(
                rot_handle.y - SpriteHandlePoint::radius, rot_handle.y + SpriteHandlePoint::radius);
            if (obe::Utils::Math::isBetween(target_pos.y, lower_y_bound, upper_y_bound))
                return &m_handlePoints.back();
        }
        return nullptr;
    }
} // namespace obe::graphics
