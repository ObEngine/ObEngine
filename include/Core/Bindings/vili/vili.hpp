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
    void LoadGlobalNullType(sol::state_view state);
    void LoadGlobalBoolType(sol::state_view state);
    void LoadGlobalIntType(sol::state_view state);
    void LoadGlobalFloatType(sol::state_view state);
    void LoadGlobalStringType(sol::state_view state);
    void LoadGlobalObjectType(sol::state_view state);
    void LoadGlobalArrayType(sol::state_view state);
};