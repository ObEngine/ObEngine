#pragma once

#include <functional>
#include <map>

#include <Transform/UnitVector.hpp>

namespace obe::Graphics
{
    using CoordinateTransformer
        = std::function<double(double position, double camera, int layer)>;

    void InitPositionTransformer();

    extern std::map<std::string, CoordinateTransformer> Transformers;
    extern CoordinateTransformer Parallax;
    extern CoordinateTransformer Camera;
    extern CoordinateTransformer Position;

    /**
     * \brief A PositionTransformer tells how a Coordinate should be transformed
     * depending of multiple parameters
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
         * use \param yTransformer Name of the Transformer the y Coordinate
         * should use
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
        std::string getXTransformerName() const;
        /**
         * \brief Gets the CoordinateTransformer of y Coordinate
         * \return The CoordinateTransformer of y Coordinate
         */
        CoordinateTransformer& getYTransformer();
        /**
         * \brief Gets the name of the CoordinateTransformer of y Coordinate
         * \return The name of the CoordinateTransformer of y Coordinate in a
         * std::string
         */
        std::string getYTransformerName() const;
        /**
         * \brief Method used by the LevelSprite to get the Position once
         * transformed \param position Base Position of the element \param
         * camera Position of the Camera \param layer Layer of the element
         * \return The new transformer position
         */
        Transform::UnitVector operator()(const Transform::UnitVector& position,
            const Transform::UnitVector& camera, int layer) const;
    };
} // namespace obe::Graphics