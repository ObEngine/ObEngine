#pragma once

namespace sol
{
    class state_view;
};
namespace obe::System::Loaders::Bindings
{
    void LoadGlobalTextureLoader(sol::state_view state);
    void LoadGlobalDataLoader(sol::state_view state);
    void LoadGlobalFontLoader(sol::state_view state);
    void LoadGlobalDirPathLoader(sol::state_view state);
    void LoadGlobalFilePathLoader(sol::state_view state);
};