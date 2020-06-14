#pragma once

namespace sol
{
    class state_view;
};
namespace vili::exceptions::Bindings
{
    void LoadClassArrayIndexOverflow(sol::state_view state);
    void LoadClassBaseException(sol::state_view state);
    void LoadClassDebugInfo(sol::state_view state);
    void LoadClassInconsistentIndentation(sol::state_view state);
    void LoadClassInvalidCast(sol::state_view state);
    void LoadClassInvalidDataType(sol::state_view state);
    void LoadClassInvalidMerge(sol::state_view state);
    void LoadClassInvalidNodeType(sol::state_view state);
    void LoadClassParsingError(sol::state_view state);
    void LoadClassTooMuchIndentation(sol::state_view state);
    void LoadClassUnknownChildNode(sol::state_view state);
    void LoadClassUnknownTemplate(sol::state_view state);
};