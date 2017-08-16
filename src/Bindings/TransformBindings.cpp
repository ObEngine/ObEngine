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
                );
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