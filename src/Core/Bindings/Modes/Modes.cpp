#include <Bindings/Modes/Modes.hpp>

#include <../Player/Modes/Game.hpp>

#include <sol/sol.hpp>

namespace obe::Modes::Bindings
{
void LoadFunctionStartGame(sol::state_view state)
{
sol::table ModesNamespace = state["obe"]["Modes"].get<sol::table>();
ModesNamespace.set_function("startGame", obe::Modes::startGame);}
};