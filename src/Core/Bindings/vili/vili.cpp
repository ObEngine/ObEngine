#include <Bindings/vili/vili.hpp>

#include <System/Path.hpp>
#include <vili/config.hpp>
#include <vili/node.hpp>
#include <vili/types.hpp>

#include <Bindings/Config.hpp>

namespace vili::Bindings
{
    void LoadEnumNodeType(sol::state_view state)
    {
        sol::table viliNamespace = state["vili"].get<sol::table>();
        viliNamespace.new_enum<vili::node_type>("node_type",
            { { "null", vili::node_type::null }, { "string", vili::node_type::string },
                { "integer", vili::node_type::integer },
                { "number", vili::node_type::number },
                { "boolean", vili::node_type::boolean },
                { "array", vili::node_type::array },
                { "object", vili::node_type::object } });
    }
    void LoadClassConstNodeIterator(sol::state_view state)
    {
        sol::table viliNamespace = state["vili"].get<sol::table>();
        sol::usertype<vili::const_node_iterator> bindconst_node_iterator
            = viliNamespace.new_usertype<vili::const_node_iterator>("const_node_iterator",
                sol::call_constructor,
                sol::constructors<vili::const_node_iterator(array::const_iterator),
                    vili::const_node_iterator(object::const_iterator),
                    vili::const_node_iterator(const vili::const_node_iterator&)>());
        bindconst_node_iterator["operator++"] = &vili::const_node_iterator::operator++;
        bindconst_node_iterator[sol::meta_function::multiplication]
            = &vili::const_node_iterator::operator*;
    }
    void LoadClassNode(sol::state_view state)
    {
        sol::table viliNamespace = state["vili"].get<sol::table>();
        sol::usertype<vili::node> bindnode = viliNamespace.new_usertype<vili::node>(
            "node", sol::call_constructor,
            sol::constructors<vili::node(), vili::node(int), vili::node(vili::integer),
                vili::node(vili::number), vili::node(const vili::string&),
                vili::node(vili::boolean), vili::node(const char*),
                vili::node(const vili::array&), vili::node(const vili::object&),
                vili::node(const vili::node&), vili::node(vili::node &&)>());
        bindnode["operator="] = &vili::node::operator=;
        bindnode["type"] = &vili::node::type;
        bindnode["dump"] = sol::overload(
            [](vili::node* self) -> std::string { return self->dump(); },
            [](vili::node* self, bool root) -> std::string { return self->dump(root); });
        bindnode["is_primitive"] = &vili::node::is_primitive;
        bindnode["is_container"] = &vili::node::is_container;
        bindnode["is_null"] = &vili::node::is_null;
        bindnode["is_integer"] = &vili::node::is_integer;
        bindnode["is_number"] = &vili::node::is_number;
        bindnode["is_numeric"] = &vili::node::is_numeric;
        bindnode["is_boolean"] = &vili::node::is_boolean;
        bindnode["is_string"] = &vili::node::is_string;
        bindnode["is_array"] = &vili::node::is_array;
        bindnode["is_object"] = &vili::node::is_object;
        bindnode["as_boolean"] = &vili::node::as_boolean;
        bindnode["as_integer"] = &vili::node::as_integer;
        bindnode["as_number"] = &vili::node::as_number;
        bindnode["as_string"] = &vili::node::as_string;
        bindnode["as_array"] = &vili::node::as_array;
        bindnode["as_object"] = &vili::node::as_object;
        bindnode[sol::meta_function::index] = sol::overload(
            static_cast<vili::node& (vili::node::*)(const char*)>(
                &vili::node::operator[]),
            static_cast<vili::node& (vili::node::*)(const std::string&)>(
                &vili::node::operator[]),
            static_cast<vili::node& (vili::node::*)(size_t)>(&vili::node::operator[]));
        bindnode["push"] = &vili::node::push;
        bindnode["insert"]
            = sol::overload(static_cast<void (vili::node::*)(size_t, const vili::node&)>(
                                &vili::node::insert),
                static_cast<void (vili::node::*)(const std::string&, vili::node)>(
                    &vili::node::insert));
        bindnode["merge"] = &vili::node::merge;
        bindnode["contains"] = &vili::node::contains;
        bindnode["erase"] = sol::overload(
            static_cast<void (vili::node::*)(size_t)>(&vili::node::erase),
            static_cast<void (vili::node::*)(size_t, size_t)>(&vili::node::erase),
            static_cast<void (vili::node::*)(const std::string&)>(&vili::node::erase));
        bindnode["front"] = &vili::node::front;
        bindnode["back"] = &vili::node::back;
        bindnode["begin"] = sol::overload(
            static_cast<vili::node_iterator (vili::node::*)()>(&vili::node::begin),
            static_cast<vili::const_node_iterator (vili::node::*)() const>(
                &vili::node::begin));
        bindnode["end"] = sol::overload(
            static_cast<vili::node_iterator (vili::node::*)()>(&vili::node::end),
            static_cast<vili::const_node_iterator (vili::node::*)() const>(
                &vili::node::end));
        bindnode["items"] = sol::overload(
            static_cast<vili::object& (vili::node::*)()>(&vili::node::items),
            static_cast<const vili::object& (vili::node::*)() const>(&vili::node::items));
        bindnode["at"] = sol::overload(
            static_cast<vili::node& (vili::node::*)(const std::string&)>(&vili::node::at),
            static_cast<vili::node& (vili::node::*)(size_t)>(&vili::node::at),
            static_cast<const vili::node& (vili::node::*)(const std::string&)const>(
                &vili::node::at),
            static_cast<const vili::node& (vili::node::*)(size_t) const>(
                &vili::node::at));
        bindnode["size"] = &vili::node::size;
        bindnode["empty"] = &vili::node::empty;
        bindnode["clear"] = &vili::node::clear;
        bindnode["operator std::string_view"] = &vili::node::operator std::string_view;
        bindnode["operator const std::string &"]
            = &vili::node::operator const std::string&;
        bindnode["operator integer"] = &vili::node::operator integer;
        bindnode["operator int"] = &vili::node::operator int;
        bindnode["operator number"] = &vili::node::operator number;
        bindnode["operator boolean"] = &vili::node::operator boolean;
        bindnode["operator unsigned"] = &vili::node::operator unsigned;
        bindnode["from_type"] = &vili::node::from_type;
        state.script_file("Lib/Internal/Vili.lua"_fs);
    }
    void LoadClassNodeIterator(sol::state_view state)
    {
        sol::table viliNamespace = state["vili"].get<sol::table>();
        sol::usertype<vili::node_iterator> bindnode_iterator
            = viliNamespace.new_usertype<vili::node_iterator>("node_iterator",
                sol::call_constructor,
                sol::constructors<vili::node_iterator(array::iterator),
                    vili::node_iterator(object::iterator),
                    vili::node_iterator(const vili::node_iterator&)>());
        bindnode_iterator["operator++"] = &vili::node_iterator::operator++;
        bindnode_iterator[sol::meta_function::multiplication]
            = &vili::node_iterator::operator*;
    }
    void LoadFunctionFromString(sol::state_view state)
    {
        sol::table viliNamespace = state["vili"].get<sol::table>();
        viliNamespace.set_function("from_string", vili::from_string);
    }
    void LoadFunctionToString(sol::state_view state)
    {
        sol::table viliNamespace = state["vili"].get<sol::table>();
        viliNamespace.set_function("to_string", vili::to_string);
    }
    void LoadGlobalPERMISSIVECAST(sol::state_view state)
    {
        sol::table viliNamespace = state["vili"].get<sol::table>();
        viliNamespace["PERMISSIVE_CAST"] = vili::PERMISSIVE_CAST;
    }
    void LoadGlobalVERBOSEEXCEPTIONS(sol::state_view state)
    {
        sol::table viliNamespace = state["vili"].get<sol::table>();
        viliNamespace["VERBOSE_EXCEPTIONS"] = vili::VERBOSE_EXCEPTIONS;
    }
    void LoadGlobalTrueValue(sol::state_view state)
    {
        sol::table viliNamespace = state["vili"].get<sol::table>();
        viliNamespace["true_value"] = vili::true_value;
    }
    void LoadGlobalFalseValue(sol::state_view state)
    {
        sol::table viliNamespace = state["vili"].get<sol::table>();
        viliNamespace["false_value"] = vili::false_value;
    }
    void LoadGlobalNullType(sol::state_view state)
    {
        sol::table viliNamespace = state["vili"].get<sol::table>();
        viliNamespace["null_type"] = vili::null_type;
    }
    void LoadGlobalBoolType(sol::state_view state)
    {
        sol::table viliNamespace = state["vili"].get<sol::table>();
        viliNamespace["bool_type"] = vili::bool_type;
    }
    void LoadGlobalIntType(sol::state_view state)
    {
        sol::table viliNamespace = state["vili"].get<sol::table>();
        viliNamespace["int_type"] = vili::int_type;
    }
    void LoadGlobalFloatType(sol::state_view state)
    {
        sol::table viliNamespace = state["vili"].get<sol::table>();
        viliNamespace["float_type"] = vili::float_type;
    }
    void LoadGlobalStringType(sol::state_view state)
    {
        sol::table viliNamespace = state["vili"].get<sol::table>();
        viliNamespace["string_type"] = vili::string_type;
    }
    void LoadGlobalObjectType(sol::state_view state)
    {
        sol::table viliNamespace = state["vili"].get<sol::table>();
        viliNamespace["object_type"] = vili::object_type;
    }
    void LoadGlobalArrayType(sol::state_view state)
    {
        sol::table viliNamespace = state["vili"].get<sol::table>();
        viliNamespace["array_type"] = vili::array_type;
    }
};