#pragma once

namespace sol { class state_view; };
namespace obe::Time::Bindings
{
void LoadClassChronometer(sol::state_view state);
void LoadClassFramerateCounter(sol::state_view state);
void LoadClassFramerateManager(sol::state_view state);
void LoadFunctionEpochAsMilliseconds(sol::state_view state);
void LoadFunctionEpochAsMicroseconds(sol::state_view state);
};