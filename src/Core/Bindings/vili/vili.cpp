#include <Bindings/vili/Vili.hpp>

#include <System/Path.hpp>
#include <vili/config.hpp>
#include <vili/node.hpp>
#include <vili/types.hpp>

#include <Bindings/Config.hpp>

namespace vili::bindings
{
    void load_enum_node_type(sol::state_view state)
    {
        sol::table vili_namespace = state["vili"].get<sol::table>();
        vili_namespace.new_enum<vili::node_type>("node_type",
            { { "null", vili::node_type::null }, { "string", vili::node_type::string },
                { "integer", vili::node_type::integer }, { "number", vili::node_type::number },
                { "boolean", vili::node_type::boolean }, { "array", vili::node_type::array },
                { "object", vili::node_type::object } });
    }
    void load_class_const_node_iterator(sol::state_view state)
    {
        sol::table vili_namespace = state["vili"].get<sol::table>();
        sol::usertype<vili::const_node_iterator> bind_const_node_iterator
            = vili_namespace.new_usertype<vili::const_node_iterator>("const_node_iterator",
                sol::call_constructor,
                sol::constructors<vili::const_node_iterator(array::const_iterator),
                    vili::const_node_iterator(object::const_iterator),
                    vili::const_node_iterator(const vili::const_node_iterator&)>());
        bind_const_node_iterator["operator++"] = &vili::const_node_iterator::operator++;
        bind_const_node_iterator[sol::meta_function::multiplication]
            = &vili::const_node_iterator::operator*;
    }
    void load_class_node(sol::state_view state)
    {
        sol::table vili_namespace = state["vili"].get<sol::table>();
        sol::usertype<vili::node> bind_node
            = vili_namespace.new_usertype<vili::node>("node", sol::call_constructor,
                sol::constructors<vili::node(), vili::node(int), vili::node(vili::integer),
                    vili::node(vili::number), vili::node(const vili::string&),
                    vili::node(std::string_view), vili::node(vili::boolean),
                    vili::node(const char*), vili::node(const vili::array&),
                    vili::node(const vili::object&), vili::node(const vili::node&)>());
        bind_node["type"] = &vili::node::type;
        bind_node["dump"]
            = sol::overload([](vili::node* self) -> std::string { return self->dump(); },
                [](vili::node* self, bool root) -> std::string { return self->dump(root); });
        bind_node["is_primitive"] = &vili::node::is_primitive;
        bind_node["is_container"] = &vili::node::is_container;
        bind_node["is_null"] = &vili::node::is_null;
        bind_node["is_integer"] = &vili::node::is_integer;
        bind_node["is_number"] = &vili::node::is_number;
        bind_node["is_numeric"] = &vili::node::is_numeric;
        bind_node["is_boolean"] = &vili::node::is_boolean;
        bind_node["is_string"] = &vili::node::is_string;
        bind_node["is_array"] = &vili::node::is_array;
        bind_node["is_object"] = &vili::node::is_object;
        bind_node["as_boolean"] = &vili::node::as_boolean;
        bind_node["as_integer"] = &vili::node::as_integer;
        bind_node["as_number"] = &vili::node::as_number;
        bind_node["as_string"] = &vili::node::as_string;
        bind_node["as_array"] = &vili::node::as_array;
        bind_node["as_object"] = &vili::node::as_object;
        bind_node[sol::meta_function::index] = sol::overload(
            static_cast<vili::node& (vili::node::*)(const char*)>(&vili::node::operator[]),
            static_cast<vili::node& (vili::node::*)(const std::string&)>(&vili::node::operator[]),
            static_cast<vili::node& (vili::node::*)(size_t)>(&vili::node::operator[]),
            static_cast<vili::node& (vili::node::*)(unsigned int)>(&vili::node::operator[]),
            static_cast<const vili::node& (vili::node::*)(const char*) const>(
                &vili::node::operator[]),
            static_cast<const vili::node& (vili::node::*)(const std::string&) const>(
                &vili::node::operator[]),
            static_cast<const vili::node& (vili::node::*)(size_t) const>(&vili::node::operator[]));
        bind_node["push"] = &vili::node::push;
        bind_node["insert"] = sol::overload(
            static_cast<void (vili::node::*)(size_t, const vili::node&)>(&vili::node::insert),
            static_cast<void (vili::node::*)(const std::string&, vili::node)>(&vili::node::insert));
        bind_node["merge"] = &vili::node::merge;
        bind_node["contains"] = &vili::node::contains;
        bind_node["erase"]
            = sol::overload(static_cast<void (vili::node::*)(size_t)>(&vili::node::erase),
                static_cast<void (vili::node::*)(size_t, size_t)>(&vili::node::erase),
                static_cast<void (vili::node::*)(const std::string&)>(&vili::node::erase));
        bind_node["front"] = &vili::node::front;
        bind_node["back"] = &vili::node::back;
        bind_node["begin"]
            = sol::overload(static_cast<vili::node_iterator (vili::node::*)()>(&vili::node::begin),
                static_cast<vili::const_node_iterator (vili::node::*)() const>(&vili::node::begin));
        bind_node["end"]
            = sol::overload(static_cast<vili::node_iterator (vili::node::*)()>(&vili::node::end),
                static_cast<vili::const_node_iterator (vili::node::*)() const>(&vili::node::end));
        bind_node["items"]
            = sol::overload(static_cast<vili::object& (vili::node::*)()>(&vili::node::items),
                static_cast<const vili::object& (vili::node::*)() const>(&vili::node::items));
        bind_node["at"] = sol::overload(
            static_cast<vili::node& (vili::node::*)(const std::string&)>(&vili::node::at),
            static_cast<vili::node& (vili::node::*)(size_t)>(&vili::node::at),
            static_cast<const vili::node& (vili::node::*)(const std::string&) const>(
                &vili::node::at),
            static_cast<const vili::node& (vili::node::*)(size_t) const>(&vili::node::at));
        bind_node["data"] = &vili::node::data;
        bind_node["size"] = &vili::node::size;
        bind_node["empty"] = &vili::node::empty;
        bind_node["clear"] = &vili::node::clear;
        bind_node[sol::meta_function::equal_to] = &vili::node::operator==;
        bind_node["from_type"] = &vili::node::from_type;
        state.script_file("obe://Lib/Internal/Vili.lua"_fs);
    }
    void load_class_node_iterator(sol::state_view state)
    {
        sol::table vili_namespace = state["vili"].get<sol::table>();
        sol::usertype<vili::node_iterator> bind_node_iterator
            = vili_namespace.new_usertype<vili::node_iterator>("node_iterator",
                sol::call_constructor,
                sol::constructors<vili::node_iterator(array::iterator),
                    vili::node_iterator(object::iterator),
                    vili::node_iterator(const vili::node_iterator&)>());
        bind_node_iterator["operator++"] = &vili::node_iterator::operator++;
        bind_node_iterator[sol::meta_function::multiplication] = &vili::node_iterator::operator*;
    }
    void load_function_from_string(sol::state_view state)
    {
        sol::table vili_namespace = state["vili"].get<sol::table>();
        vili_namespace.set_function("from_string", &vili::from_string);
    }
    void load_function_to_string(sol::state_view state)
    {
        sol::table vili_namespace = state["vili"].get<sol::table>();
        vili_namespace.set_function("to_string", &vili::to_string);
    }
    void load_global_permissive_cast(sol::state_view state)
    {
        sol::table vili_namespace = state["vili"].get<sol::table>();
        vili_namespace["PERMISSIVE_CAST"] = vili::PERMISSIVE_CAST;
    }
    void load_global_verbose_exceptions(sol::state_view state)
    {
        sol::table vili_namespace = state["vili"].get<sol::table>();
        vili_namespace["VERBOSE_EXCEPTIONS"] = vili::VERBOSE_EXCEPTIONS;
    }
    void load_global_true_value(sol::state_view state)
    {
        sol::table vili_namespace = state["vili"].get<sol::table>();
        vili_namespace["true_value"] = vili::true_value;
    }
    void load_global_false_value(sol::state_view state)
    {
        sol::table vili_namespace = state["vili"].get<sol::table>();
        vili_namespace["false_value"] = vili::false_value;
    }
    void load_global_null_typename(sol::state_view state)
    {
        sol::table vili_namespace = state["vili"].get<sol::table>();
        vili_namespace["null_typename"] = vili::null_typename;
    }
    void load_global_boolean_typename(sol::state_view state)
    {
        sol::table vili_namespace = state["vili"].get<sol::table>();
        vili_namespace["boolean_typename"] = vili::boolean_typename;
    }
    void load_global_integer_typename(sol::state_view state)
    {
        sol::table vili_namespace = state["vili"].get<sol::table>();
        vili_namespace["integer_typename"] = vili::integer_typename;
    }
    void load_global_number_typename(sol::state_view state)
    {
        sol::table vili_namespace = state["vili"].get<sol::table>();
        vili_namespace["number_typename"] = vili::number_typename;
    }
    void load_global_string_typename(sol::state_view state)
    {
        sol::table vili_namespace = state["vili"].get<sol::table>();
        vili_namespace["string_typename"] = vili::string_typename;
    }
    void load_global_object_typename(sol::state_view state)
    {
        sol::table vili_namespace = state["vili"].get<sol::table>();
        vili_namespace["object_typename"] = vili::object_typename;
    }
    void load_global_array_typename(sol::state_view state)
    {
        sol::table vili_namespace = state["vili"].get<sol::table>();
        vili_namespace["array_typename"] = vili::array_typename;
    }
    void load_global_unknown_typename(sol::state_view state)
    {
        sol::table vili_namespace = state["vili"].get<sol::table>();
        vili_namespace["unknown_typename"] = vili::unknown_typename;
    }
    void load_global_container_typename(sol::state_view state)
    {
        sol::table vili_namespace = state["vili"].get<sol::table>();
        vili_namespace["container_typename"] = vili::container_typename;
    }
};