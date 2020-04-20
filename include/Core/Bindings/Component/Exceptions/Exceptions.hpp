#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Component::Exceptions::Bindings
{
    void LoadClassComponentIdAlreadyTaken(sol::state_view state);
};