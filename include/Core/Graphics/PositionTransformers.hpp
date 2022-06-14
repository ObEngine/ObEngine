#pragma once

#include <functional>
#include <map>

#include <Transform/UnitVector.hpp>

namespace obe::graphics
{
    // TODO: Make position transformer overload that take only a Sprite as argument (more
    // flexible)

    using CoordinateTransformer = std::function<double(double position, double camera, int layer)>;

    void init_position_transformers();

    extern std::map<std::string, CoordinateTransformer> Transformers;
    /**
     * \brief CoordinateTransformer which uses the layer and camera position to give a
     * parallax effect
     */
    extern CoordinateTransformer Parallax;
    /**
     * \brief CoordinateTransformer which uses the camera position
     */
    extern CoordinateTransformer Camera;
    /**
     * \brief CoordinateTransformer which only uses the base position (no transformation)
     */
    extern CoordinateTransformer Position;

    /**
     * \brief A PositionTransformer tells how a Coordinate should be transformed
     * depending of multiple parameters
     */
    class PositionTransformer
    {
    private:
        CoordinateTransformer m_x_transformer;
        std::string m_x_transformer_name = "Camera";
        CoordinateTransformer m_y_transformer;
        std::string m_y_transformer_name = "Camera";

    public:
        /**
         * \brief Default PositionTransformer constructor
         */
        PositionTransformer();
        /**
         * \brief Non-Default PositionTransformer constructor
         * \param x_transformer Name of the Transformer the x Coordinate should
         *        use
         * \param y_transformer Name of the Transformer the y Coordinate
         *        should use
         */
        PositionTransformer(const std::string& x_transformer, const std::string& y_transformer);
        /**
         * \brief Gets the CoordinateTransformer of x Coordinate
         * \return The CoordinateTransformer of x Coordinate
         */
        CoordinateTransformer& get_x_transformer();
        /**
         * \brief Gets the name of the CoordinateTransformer of x Coordinate
         * \return The name of the CoordinateTransformer of x Coordinate in a
         * std::string
         */
        [[nodiscard]] std::string get_x_transformer_name() const;
        /**
         * \brief Gets the CoordinateTransformer of y Coordinate
         * \return The CoordinateTransformer of y Coordinate
         */
        CoordinateTransformer& get_y_transformer();
        /**
         * \brief Gets the name of the CoordinateTransformer of y Coordinate
         * \return The name of the CoordinateTransformer of y Coordinate
         */
        [[nodiscard]] std::string get_y_transformer_name() const;
        /**
         * \brief Method used by the Sprite to get the Position once
         *        transformed
         * \param position Base Position of the element
         * \param camera Position of the Camera
         * \param layer Layer of the element
         * \return The new transformer position
         */
        transform::UnitVector operator()(const transform::UnitVector& position,
            const transform::UnitVector& camera, int layer) const;
    };
} // namespace obe::graphics
