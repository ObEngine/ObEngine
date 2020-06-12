#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Engine::Exceptions::Bindings
{
    void LoadClassBootScriptExecutionError(sol::state_view state);
    void LoadClassBootScriptLoadingError(sol::state_view state);
    void LoadClassBootScriptMissing(sol::state_view state);
    void LoadClassFontNotFound(sol::state_view state);
    void LoadClassTextureNotFound(sol::state_view state);
    void LoadClassUnitializedEngine(sol::state_view state);
};