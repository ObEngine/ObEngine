#include <Bindings/Bindings.hpp>
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
                Load(lua, "Core.Transform.UnitVector");
                (*lua)["Core"]["Transform"]["ProtectedUnitVector"].setClass(kaguya::UserdataMetatable<Transform::ProtectedUnitVector, Transform::UnitVector>()
                );
            }

            KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
                Rect_getPosition_proxy, Transform::Rect, getPosition, 0, 1, Transform::UnitVector(Transform::Rect::*)(Transform::Referencial)
            );
            KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
                Rect_getX_proxy, Transform::Rect, getX, 0, 1, double(Transform::Rect::*)(Transform::Referencial)
            );
            KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
                Rect_getY_proxy, Transform::Rect, getY, 0, 1, double(Transform::Rect::*)(Transform::Referencial)
            );
            KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
                Rect_movePoint_uv_proxy, Transform::Rect, movePoint, 1, 2, void(Transform::Rect::*)(const Transform::UnitVector&, Transform::Referencial)
            );
            KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
                Rect_movePoint_dd_proxy, Transform::Rect, movePoint, 2, 3, void(Transform::Rect::*)(double, double, Transform::Referencial)
            );
            KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
                Rect_scale_uv_proxy, Transform::Rect, scale, 1, 2, void(Transform::Rect::*)(const Transform::UnitVector&, Transform::Referencial)
            );
            KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
                Rect_scale_dd_proxy, Transform::Rect, scale, 2, 3, void(Transform::Rect::*)(double, double, Transform::Referencial)
            );
            KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
                Rect_setHeight_proxy, Transform::Rect, setHeight, 1, 2, void(Transform::Rect::*)(double, Transform::Referencial)
            );
            KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
                Rect_setPointPosition_uv_proxy, Transform::Rect, setPointPosition, 1, 2, void(Transform::Rect::*)(const Transform::UnitVector&, Transform::Referencial)
            );
            KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
                Rect_setPointPosition_dd_proxy, Transform::Rect, setPointPosition, 2, 3, void(Transform::Rect::*)(double, double, Transform::Referencial)
            );
            KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
                Rect_setPosition_uv_proxy, Transform::Rect, setPosition, 1, 2, void(Transform::Rect::*)(const Transform::UnitVector&, Transform::Referencial)
            );
            KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
                Rect_setPosition_dd_proxy, Transform::Rect, setPosition, 2, 3, void(Transform::Rect::*)(double, double, Transform::Referencial)
            );
            KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
                Rect_setPointX_proxy, Transform::Rect, setPointX, 1, 2, void(Transform::Rect::*)(double, Transform::Referencial)
            );
            KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
                Rect_setPointY_proxy, Transform::Rect, setPointY, 1, 2, void(Transform::Rect::*)(double, Transform::Referencial)
            );
            KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
                Rect_setWidth_proxy, Transform::Rect, setWidth, 1, 2, void(Transform::Rect::*)(double, Transform::Referencial)
            );
            KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
                Rect_setSize_uv_proxy, Transform::Rect, setSize, 1, 2, void(Transform::Rect::*)(const Transform::UnitVector&, Transform::Referencial)
            );
            KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
                Rect_setSize_dd_proxy, Transform::Rect, setSize, 2, 3, void(Transform::Rect::*)(double, double, Transform::Referencial)
            );
            KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
                Rect_setX_proxy, Transform::Rect, setX, 1, 2, void(Transform::Rect::*)(double, Transform::Referencial)
            );
            KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
                Rect_setY_proxy, Transform::Rect, setY, 1, 2, void(Transform::Rect::*)(double, Transform::Referencial)
            );
            void LoadRect(kaguya::State* lua)
            {
                (*lua)["Core"]["Transform"]["Rect"].setClass(kaguya::UserdataMetatable<Transform::Rect>()
                    .addFunction("display", &Transform::Rect::display)
                    .addFunction("getHeight", &Transform::Rect::getHeight)
                    .addFunction("getPosition", Rect_getPosition_proxy())
                    .addFunction("getScaleFactor", &Transform::Rect::getScaleFactor)
                    .addFunction("getSize", &Transform::Rect::getSize)
                    .addFunction("getWidth", &Transform::Rect::getWidth)
                    .addFunction("getX", Rect_getX_proxy())
                    .addFunction("getY", Rect_getY_proxy())
                    .addFunction("intersects", &Transform::Rect::intersects)
                    .addOverloadedFunctions("move",
                        static_cast<void (Transform::Rect::*)(const Transform::UnitVector&)>(&Transform::Rect::move),
                        static_cast<void (Transform::Rect::*)(double, double)>(&Transform::Rect::move)
                    )
                    .addOverloadedFunctions("movePoint",
                        static_cast<void (Transform::Rect::*)(const Transform::UnitVector&, Transform::Referencial)>(&Transform::Rect::movePoint),
                        static_cast<void (Transform::Rect::*)(double, double, Transform::Referencial)>(&Transform::Rect::movePoint),
                        Rect_movePoint_uv_proxy(),
                        Rect_movePoint_dd_proxy()
                    )
                    .addOverloadedFunctions("scale",
                        static_cast<void (Transform::Rect::*)(const Transform::UnitVector&, Transform::Referencial)>(&Transform::Rect::scale),
                        static_cast<void (Transform::Rect::*)(double, double, Transform::Referencial)>(&Transform::Rect::scale),
                        Rect_scale_uv_proxy(),
                        Rect_scale_dd_proxy()
                    )
                    .addFunction("setHeight", Rect_setHeight_proxy())
                    .addOverloadedFunctions("setPointPosition",
                        static_cast<void (Transform::Rect::*)(const Transform::UnitVector&, Transform::Referencial)>(&Transform::Rect::setPointPosition),
                        static_cast<void (Transform::Rect::*)(double, double, Transform::Referencial)>(&Transform::Rect::setPointPosition),
                        Rect_setPointPosition_uv_proxy(),
                        Rect_setPointPosition_dd_proxy()
                    )
                    .addFunction("setPointX", Rect_setPointX_proxy())
                    .addFunction("setPointY", Rect_setPointY_proxy())
                    .addOverloadedFunctions("setPosition",
                        static_cast<void (Transform::Rect::*)(const Transform::UnitVector&, Transform::Referencial)>(&Transform::Rect::setPosition),
                        static_cast<void (Transform::Rect::*)(double, double, Transform::Referencial)>(&Transform::Rect::setPosition),
                        Rect_setPosition_uv_proxy(),
                        Rect_setPosition_dd_proxy()
                    )
                    .addOverloadedFunctions("setSize",
                        static_cast<void (Transform::Rect::*)(const Transform::UnitVector&, Transform::Referencial)>(&Transform::Rect::setSize),
                        static_cast<void (Transform::Rect::*)(double, double, Transform::Referencial)>(&Transform::Rect::setSize),
                        Rect_setSize_uv_proxy(),
                        Rect_setSize_dd_proxy()
                    )
                    .addFunction("setWidth", Rect_setWidth_proxy())
                    .addFunction("setX", Rect_setX_proxy())
                    .addFunction("setY", Rect_setY_proxy())
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