#include <Bindings/TransformBindings.hpp>
#include <Transform/ProtectedUnitVector.hpp>
#include <Transform/Rect.hpp>
#include <Transform/UnitBasedObject.hpp>
#include <Transform/UnitVector.hpp>

namespace obe
{
    namespace Bindings
    {
        namespace TransformBindings
        {
            void LoadProtectedUnitVector(kaguya::State* lua)
            {
                (*lua)["Core"]["Transform"]["ProtectedUnitVector"].setClass(kaguya::UserdataMetatable<Transform::ProtectedUnitVector, Transform::UnitVector>()
                );
            }

            void LoadRect(kaguya::State* lua)
            {
                (*lua)["Core"]["Transform"]["Rect"].setClass(kaguya::UserdataMetatable<Transform::Rect>()
                    .addFunction("display", &Transform::Rect::display)
                    .addFunction("getHeight", &Transform::Rect::getHeight)
                    .addFunction("getPosition", &Transform::Rect::getPosition)
                    .addFunction("getScaleFactor", &Transform::Rect::getScaleFactor)
                    .addFunction("getSize", &Transform::Rect::getSize)
                    .addFunction("getWidth", &Transform::Rect::getWidth)
                    .addFunction("getX", &Transform::Rect::getX)
                    .addFunction("getY", &Transform::Rect::getY)
                    .addFunction("intersects", &Transform::Rect::intersects)
                    .addOverloadedFunctions("move",
                        static_cast<void (Transform::Rect::*)(const Transform::UnitVector&)>(&Transform::Rect::move),
                        static_cast<void (Transform::Rect::*)(double, double)>(&Transform::Rect::move)
                    )
                    .addOverloadedFunctions("movePoint",
                        static_cast<void (Transform::Rect::*)(const Transform::UnitVector&, Transform::Referencial)>(&Transform::Rect::movePoint),
                        static_cast<void (Transform::Rect::*)(double, double, Transform::Referencial)>(&Transform::Rect::movePoint)
                    )
                    .addOverloadedFunctions("scale",
                        static_cast<void (Transform::Rect::*)(const Transform::UnitVector&, Transform::Referencial)>(&Transform::Rect::scale),
                        static_cast<void (Transform::Rect::*)(double, double, Transform::Referencial)>(&Transform::Rect::scale)
                    )
                    .addFunction("setHeight", &Transform::Rect::setHeight)
                    .addOverloadedFunctions("setPointPosition",
                        static_cast<void (Transform::Rect::*)(const Transform::UnitVector&, Transform::Referencial)>(&Transform::Rect::setPointPosition),
                        static_cast<void (Transform::Rect::*)(double, double, Transform::Referencial)>(&Transform::Rect::setPointPosition)
                    )
                    .addFunction("setPointX", &Transform::Rect::setPointX)
                    .addFunction("setPointY", &Transform::Rect::setPointY)
                    .addOverloadedFunctions("setPosition",
                        static_cast<void (Transform::Rect::*)(const Transform::UnitVector&, Transform::Referencial)>(&Transform::Rect::setPosition),
                        static_cast<void (Transform::Rect::*)(double, double, Transform::Referencial)>(&Transform::Rect::setPosition)
                    )
                    .addOverloadedFunctions("setSize",
                        static_cast<void (Transform::Rect::*)(const Transform::UnitVector&, Transform::Referencial)>(&Transform::Rect::setSize),
                        static_cast<void (Transform::Rect::*)(double, double, Transform::Referencial)>(&Transform::Rect::setSize)
                    )
                    .addFunction("setWidth", &Transform::Rect::setWidth)
                    .addFunction("setX", &Transform::Rect::setX)
                    .addFunction("setY", &Transform::Rect::setY)
                    .addFunction("transformRef", &Transform::Rect::transformRef)
                );
            }

            void LoadReferencial(kaguya::State* lua)
            {
                (*lua)["Core"]["Transform"]["Referencial"] = kaguya::NewTable();
                (*lua)["Core"]["Transform"]["Referencial"]["Bottom"] = Transform::Referencial::Bottom;
                (*lua)["Core"]["Transform"]["Referencial"]["BottomLeft"] = Transform::Referencial::BottomLeft;
                (*lua)["Core"]["Transform"]["Referencial"]["BottomRight"] = Transform::Referencial::BottomRight;
                (*lua)["Core"]["Transform"]["Referencial"]["Center"] = Transform::Referencial::Center;
                (*lua)["Core"]["Transform"]["Referencial"]["Left"] = Transform::Referencial::Left;
                (*lua)["Core"]["Transform"]["Referencial"]["Right"] = Transform::Referencial::Right;
                (*lua)["Core"]["Transform"]["Referencial"]["Top"] = Transform::Referencial::Top;
                (*lua)["Core"]["Transform"]["Referencial"]["TopLeft"] = Transform::Referencial::TopLeft;
                (*lua)["Core"]["Transform"]["Referencial"]["TopRight"] = Transform::Referencial::TopRight;
            }

            void LoadUnitBasedObject(kaguya::State* lua)
            {
                (*lua)["Core"]["Transform"]["UnitBasedObject"].setClass(kaguya::UserdataMetatable<Transform::UnitBasedObject>()
                    .addFunction("getWorkingUnit", &Transform::UnitBasedObject::getWorkingUnit)
                    .addFunction("setWorkingUnit", &Transform::UnitBasedObject::setWorkingUnit)
                );
            }
            void LoadUnitVector(kaguya::State* lua)
            {
                (*lua)["Core"]["Transform"]["UnitVector"].setClass(kaguya::UserdataMetatable<Transform::UnitVector>()
                    .setConstructors<
                    Transform::UnitVector(),
                    Transform::UnitVector(Transform::Units),
                    Transform::UnitVector(double, double), 
                    Transform::UnitVector(double, double, Transform::Units)
                    >()
                    .addOverloadedFunctions("add",
                        static_cast<void (Transform::UnitVector::*)(const Transform::UnitVector&)>(&Transform::UnitVector::add),
                        static_cast<void (Transform::UnitVector::*)(double, double)>(&Transform::UnitVector::add)
                    )
                    .addFunction("__add", &Transform::UnitVector::operator+)
                    .addFunction("__sub", &Transform::UnitVector::operator-)
                    .addFunction("__div", &Transform::UnitVector::operator/)
                    .addFunction("__mul", &Transform::UnitVector::operator*)
                    .addOverloadedFunctions("set",
                        static_cast<void (Transform::UnitVector::*)(const Transform::UnitVector&)>(&Transform::UnitVector::set),
                        static_cast<void (Transform::UnitVector::*)(double, double)>(&Transform::UnitVector::set)
                    )
                    .addFunction("to", static_cast<Transform::UnitVector (Transform::UnitVector::*)(Transform::Units) const>(&Transform::UnitVector::to))
                    .addProperty("x", &Transform::UnitVector::x)
                    .addProperty("y", &Transform::UnitVector::y)
                    .addProperty("unit", &Transform::UnitVector::unit)
                );
            }

            void LoadUnits(kaguya::State* lua)
            {
                (*lua)["Core"]["Transform"]["Units"] = kaguya::NewTable();
                (*lua)["Core"]["Transform"]["Units"]["ViewPercentage"] = Transform::Units::ViewPercentage;
                (*lua)["Core"]["Transform"]["Units"]["ViewPixels"] = Transform::Units::ViewPixels;
                (*lua)["Core"]["Transform"]["Units"]["ViewUnits"] = Transform::Units::ViewUnits;
                (*lua)["Core"]["Transform"]["Units"]["WorldPixels"] = Transform::Units::WorldPixels;
                (*lua)["Core"]["Transform"]["Units"]["WorldUnits"] = Transform::Units::WorldUnits;
                (*lua)["Core"]["Transform"]["Units"]["Unknown"] = Transform::Units::Unknown;
            }
        }
    }
}