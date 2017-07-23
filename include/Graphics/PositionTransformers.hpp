#pragma once

#include <functional>
#include <map>

#include <Transform/UnitVector.hpp>
#include <Types/Identifiable.hpp>

namespace obe
{
    namespace Graphics
    {
        namespace PositionTransformers
        {
            using CoordinateTransformer = std::function<double(double position, double camera, int layer)>;

            void Init();

            extern std::map<std::string, CoordinateTransformer> Transformers;
            extern CoordinateTransformer Parallax;
            extern CoordinateTransformer Camera;
            extern CoordinateTransformer Position;

            class PositionTransformer
            {
            private:
                std::string m_xTransformerName = "Camera";
                std::string m_yTransformerName = "Camera";
                CoordinateTransformer m_xTransformer;
                CoordinateTransformer m_yTransformer;
            public:
                PositionTransformer();
                PositionTransformer(const std::string& xTransformer, const std::string& yTransformer);
                Transform::UnitVector operator()(Transform::UnitVector& position, Transform::UnitVector& camera, int layer) const;
                CoordinateTransformer& getXTransformer();
                CoordinateTransformer& getYTransformer();
                std::string getXTransformerName() const;
                std::string getYTransformerName() const;
            };
        };
    }
}
