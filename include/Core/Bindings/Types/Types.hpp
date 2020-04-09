#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Types::Bindings
{
    void LoadClassIdentifiable(sol::state_view state);
    void LoadClassProtectedIdentifiable(sol::state_view state);
    void LoadClassSelectable(sol::state_view state);
    void LoadClassSerializable(sol::state_view state);
    void LoadClassTogglable(sol::state_view state);
};