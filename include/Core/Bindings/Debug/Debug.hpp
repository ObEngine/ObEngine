#pragma once

namespace sol { class state_view; };
namespace obe::Debug::Bindings
{
void LoadFunctionInitLogger(sol::state_view state);
void LoadGlobalLog(sol::state_view state);
};