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
                    .addOverloadedFunctions("add",
                        static_cast<void (Transform::UnitVector::*)(const Transform::UnitVector&)>(&Transform::UnitVector::add),
                        static_cast<void (Transform::UnitVector::*)(double, double)>(&Transform::UnitVector::add)
                    )
                    .addOverloadedFunctions("operator*",
                        static_cast<Transform::UnitVector(Transform::UnitVector::*)(const Transform::UnitVector&) const>(&Transform::UnitVector::operator*),
                        static_cast<Transform::UnitVector(Transform::UnitVector::*)(double) const>(&Transform::UnitVector::operator*)
                    )
                    .addFunction("operator*=", &Transform::UnitVector::operator*=)
                    .addFunction("operator+", &Transform::UnitVector::operator+)
                    .addFunction("operator+=", &Transform::UnitVector::operator+=)
                    .addFunction("operator-", &Transform::UnitVector::operator-)
                    .addFunction("operator-=", &Transform::UnitVector::operator-=)
                    .addFunction("operator/", &Transform::UnitVector::operator/)
                    .addFunction("operator/=", &Transform::UnitVector::operator/=)
                    .addOverloadedFunctions("set",
                        static_cast<void (Transform::UnitVector::*)(const Transform::UnitVector&)>(&Transform::UnitVector::set),
                        static_cast<void (Transform::UnitVector::*)(double, double)>(&Transform::UnitVector::set)
                    )
                    .addFunction("to", static_cast<Transform::UnitVector (Transform::UnitVector::*)(Transform::Units) const>(&Transform::UnitVector::to))
                );
            }
        }
    }
}