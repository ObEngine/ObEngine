#include <Bindings/tgui/tgui.hpp>

#include <TGUI/Transform.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassTransform(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::Transform> bindTransform
            = tguiNamespace.new_usertype<tgui::Transform>("Transform",
                sol::call_constructor,
                sol::constructors<tgui::Transform(),
                    tgui::Transform(
                        float, float, float, float, float, float, float, float, float)>());
        bindTransform["getMatrix"] = &tgui::Transform::getMatrix;
        bindTransform["getInverse"] = &tgui::Transform::getInverse;
        bindTransform["transformPoint"] = &tgui::Transform::transformPoint;
        bindTransform["transformRect"] = &tgui::Transform::transformRect;
        bindTransform["combine"] = &tgui::Transform::combine;
        bindTransform["translate"] = &tgui::Transform::translate;
        bindTransform["rotate"] = sol::overload(
            [](tgui::Transform* self, float angle) -> tgui::Transform& {
                return self->rotate(angle);
            },
            [](tgui::Transform* self, float angle, const tgui::Vector2f& center)
                -> tgui::Transform& { return self->rotate(angle, center); });
        bindTransform["scale"] = sol::overload(
            [](tgui::Transform* self, const tgui::Vector2f& factors) -> tgui::Transform& {
                return self->scale(factors);
            },
            [](tgui::Transform* self, const tgui::Vector2f& factors,
                const tgui::Vector2f& center) -> tgui::Transform& {
                return self->scale(factors, center);
            });
        bindTransform[sol::meta_function::multiplication] = sol::overload(
            static_cast<tgui::Transform (tgui::Transform::*)(const tgui::Transform&)
                    const>(&tgui::Transform::operator*),
            static_cast<tgui::Vector2f (tgui::Transform::*)(const tgui::Vector2f&) const>(
                &tgui::Transform::operator*));
        bindTransform["roundPosition"] = &tgui::Transform::roundPosition;
    }
};