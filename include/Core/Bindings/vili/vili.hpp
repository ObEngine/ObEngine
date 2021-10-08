#pragma once

namespace sol
{
    class state_view;
};
namespace vili::Bindings
{
    void LoadClassConstNodeIterator(sol::state_view state);
    void LoadClassNode(sol::state_view state);
    void LoadClassNodeIterator(sol::state_view state);
    void LoadEnumNodeType(sol::state_view state);
    void LoadFunctionFromString(sol::state_view state);
    void LoadFunctionToString(sol::state_view state);
    void LoadGlobalPERMISSIVECAST(sol::state_view state);
    void LoadGlobalVERBOSEEXCEPTIONS(sol::state_view state);
    void LoadGlobalTrueValue(sol::state_view state);
    void LoadGlobalFalseValue(sol::state_view state);
    void LoadGlobalNullTypename(sol::state_view state);
    void LoadGlobalBooleanTypename(sol::state_view state);
    void LoadGlobalIntegerTypename(sol::state_view state);
    void LoadGlobalNumberTypename(sol::state_view state);
    void LoadGlobalStringTypename(sol::state_view state);
    void LoadGlobalObjectTypename(sol::state_view state);
    void LoadGlobalArrayTypename(sol::state_view state);
};
