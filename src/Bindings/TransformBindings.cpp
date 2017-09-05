#include <Bindings/Bindings.hpp>
#include <Bindings/TransformBindings.hpp>
#include <Transform/SceneNode.hpp>
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
            void LoadMovable(kaguya::State* lua)
            {
                Load(lua, "Core.Types.Identifiable");
                (*lua)["Core"]["Transform"]["Movable"].setClass(kaguya::UserdataMetatable<Transform::Movable, Types::Identifiable>()
                    .addFunction("getPosition", &Transform::Movable::getPosition)
                    .addFunction("getType", &Transform::Movable::getType)
                    .addFunction("move", &Transform::Movable::move)
                    .addFunction("setPosition", &Transform::Movable::setPosition)
                );
            }

            void LoadSceneNode(kaguya::State* lua)
            {
                Load(lua, "Core.Transform.Movable");
                (*lua)["Core"]["Transform"]["SceneNode"].setClass(kaguya::UserdataMetatable<Transform::SceneNode, Transform::Movable>()
                    .addFunction("addChild", &Transform::SceneNode::addChild)
                    .addFunction("move", &Transform::SceneNode::move)
                    .addFunction("setPosition", &Transform::SceneNode::setPosition)
                );
            }

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
                Rect_movePoint_uv_proxy, Transform::Rect, movePoint, 1, 2, void(Transform::Rect::*)(const Transform::UnitVector&, Transform::Referencial)
            );
            KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
                Rect_scale_uv_proxy, Transform::Rect, scale, 1, 2, void(Transform::Rect::*)(const Transform::UnitVector&, Transform::Referencial)
            );
            KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
                Rect_setPointPosition_uv_proxy, Transform::Rect, setPointPosition, 1, 2, void(Transform::Rect::*)(const Transform::UnitVector&, Transform::Referencial)
            );
            KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
                Rect_setPosition_uv_proxy, Transform::Rect, setPosition, 1, 2, void(Transform::Rect::*)(const Transform::UnitVector&, Transform::Referencial)
            );
            KAGUYA_MEMBER_FUNCTION_OVERLOADS_WITH_SIGNATURE(
                Rect_setSize_uv_proxy, Transform::Rect, setSize, 1, 2, void(Transform::Rect::*)(const Transform::UnitVector&, Transform::Referencial)
            );
            void LoadRect(kaguya::State* lua)
            {
                Load(lua, "Core.Transform.Movable");
                (*lua)["Core"]["Transform"]["Rect"].setClass(kaguya::UserdataMetatable<Transform::Rect, Transform::Movable>()
                    .addFunction("display", &Transform::Rect::display)
                    .addFunction("getPosition", Rect_getPosition_proxy())
                    .addFunction("getScaleFactor", &Transform::Rect::getScaleFactor)
                    .addFunction("getSize", &Transform::Rect::getSize)
                    .addFunction("intersects", &Transform::Rect::intersects)
                    .addFunction("move", &Transform::Rect::move)
                    .addFunction("movePoint", Rect_movePoint_uv_proxy())
                    .addFunction("scale", Rect_scale_uv_proxy())
                    .addFunction("setPointPosition", Rect_setPointPosition_uv_proxy())
                    .addFunction("setPosition", Rect_setPosition_uv_proxy())
                    .addFunction("setSize", Rect_setSize_uv_proxy())
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
                    .addFunction("equal", &Transform::UnitVector::operator==)
                    .addFunction("different", &Transform::UnitVector::operator!=)
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
