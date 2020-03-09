#pragma once

#include <functional>
#include <map>

#include <Transform/UnitVector.hpp>

namespace obe::Graphics
{
    // TODO: Make position transformer overload that take only a Sprite as argument (more
    // flexible)

    using CoordinateTransformer
        = std::function<double(double position, double camera, int layer)>;

    void InitPositionTransformer();

    extern std::map<std::string, CoordinateTransformer> Transformers;
    /**
     * \brief CoordinateTransformer which uses the layer and camera position to give a
     * parallax effect
     * \bind{PositionTransformer.Parallax}
     */
    extern CoordinateTransformer Parallax;
    /**
     * \brief CoordinateTransformer which uses the camera position
     * \bind{PositionTransformer.Camera}
     */
    extern CoordinateTransformer Camera;
    /**
     * \brief CoordinateTransformer which only uses the base position (no transformation)
     * \bind{PositionTransformer.Position}
     */
    extern CoordinateTransformer Position;

    /**
     * \brief A PositionTransformer tells how a Coordinate should be transformed
     * depending of multiple parameters
     * \bind{PositionTransformer}
     */
    class PositionTransformer
    {
    private:
        CoordinateTransformer m_xTransformer;
        std::string m_xTransformerName = "Camera";
        CoordinateTransformer m_yTransformer;
        std::string m_yTransformerName = "Camera";

    public:
        /**
         * \brief Default PositionTransformer constructor
         */
        PositionTransformer();
        /**
         * \brief Non-Default PositionTransformer constructor
         * \param xTransformer Name of the Transformer the x Coordinate should
         *        use
         * \param yTransformer Name of the Transformer the y Coordinate
         *        should use
         */
        PositionTransformer(
            const std::string& xTransformer, const std::string& yTransformer);
        /**
         * \brief Gets the CoordinateTransformer of x Coordinate
         * \return The CoordinateTransformer of x Coordinate
         */
        CoordinateTransformer& getXTransformer();
        /**
         * \brief Gets the name of the CoordinateTransformer of x Coordinate
         * \return The name of the CoordinateTransformer of x Coordinate in a
         * std::string
         */
        [[nodiscard]] std::string getXTransformerName() const;
        /**
         * \brief Gets the CoordinateTransformer of y Coordinate
         * \return The CoordinateTransformer of y Coordinate
         */
        CoordinateTransformer& getYTransformer();
        /**
         * \brief Gets the name of the CoordinateTransformer of y Coordinate
         * \return The name of the CoordinateTransformer of y Coordinate
         */
        [[nodiscard]] std::string getYTransformerName() const;
        /**
         * \brief Method used by the Sprite to get the Position once
         *        transformed
         * \param position Base Position of the element
         * \param camera Position of the Camera
         * \param layer Layer of the element
         * \return The new transformer position
         */
        Transform::UnitVector operator()(const Transform::UnitVector& position,
            const Transform::UnitVector& camera, int layer) const;
    };
} // namespace obe::Graphics