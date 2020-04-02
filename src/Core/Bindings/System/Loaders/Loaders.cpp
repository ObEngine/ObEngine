#include <Bindings/System/Loaders/Loaders.hpp>

#include <System/Loaders.hpp>

#include <sol/sol.hpp>

namespace obe::System::Loaders::Bindings
{
void LoadGlobalTextureLoader(sol::state_view state)
{
sol::table LoadersNamespace = state["obe"]["System"]["Loaders"].get<sol::table>();
LoadersNamespace["textureLoader"] = obe::System::Loaders::textureLoader;
}
void LoadGlobalDataLoader(sol::state_view state)
{
sol::table LoadersNamespace = state["obe"]["System"]["Loaders"].get<sol::table>();
LoadersNamespace["dataLoader"] = obe::System::Loaders::dataLoader;
}
void LoadGlobalFontLoader(sol::state_view state)
{
sol::table LoadersNamespace = state["obe"]["System"]["Loaders"].get<sol::table>();
LoadersNamespace["fontLoader"] = obe::System::Loaders::fontLoader;
}
void LoadGlobalDirPathLoader(sol::state_view state)
{
sol::table LoadersNamespace = state["obe"]["System"]["Loaders"].get<sol::table>();
LoadersNamespace["dirPathLoader"] = obe::System::Loaders::dirPathLoader;
}
void LoadGlobalFilePathLoader(sol::state_view state)
{
sol::table LoadersNamespace = state["obe"]["System"]["Loaders"].get<sol::table>();
LoadersNamespace["filePathLoader"] = obe::System::Loaders::filePathLoader;
}
void LoadGlobalLuaLoader(sol::state_view state)
{
sol::table LoadersNamespace = state["obe"]["System"]["Loaders"].get<sol::table>();
LoadersNamespace["luaLoader"] = obe::System::Loaders::luaLoader;
}
};