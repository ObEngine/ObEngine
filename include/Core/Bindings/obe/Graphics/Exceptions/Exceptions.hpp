#pragma once

namespace sol
{
    class state_view;
};
namespace obe::graphics::exceptions::Bindings
{
    void LoadClassCanvasElementAlreadyExists(sol::state_view state);
    void LoadClassImageFileNotFound(sol::state_view state);
    void LoadClassInvalidColorName(sol::state_view state);
    void LoadClassInvalidHexFormat(sol::state_view state);
    void LoadClassInvalidHsvFormat(sol::state_view state);
    void LoadClassInvalidRgbFormat(sol::state_view state);
    void LoadClassInvalidSpriteColorType(sol::state_view state);
    void LoadClassReadOnlyTexture(sol::state_view state);
};