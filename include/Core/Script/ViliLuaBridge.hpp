#pragma once

#include <sol/sol.hpp>
#include <vili/node.hpp>

/**
 * \brief Functions that allow the conversion of Vili elements to Lua elements
 */
namespace obe::script::vili_lua_bridge
{
    sol::lua_value vili_to_lua(const vili::node& convert);

    sol::lua_value vili_to_lua_keep_order(sol::state_view state, const vili::node& convert);

    vili::node lua_to_vili(const sol::object& convert);
    /**
     * \brief Builds a Lua Table from a Vili object
     * \param convert The Vili Node you want to convert to Lua
     */
    sol::lua_value vili_object_to_lua_table(const vili::node& convert);

    /**
     * \brief Builds a Lua Table from a Vili object and keeps the order of the keys
     * \param convert The Vili Node you want to convert to Lua
    */
    sol::lua_value vili_object_to_lua_table_keep_order(
        sol::state_view state, const vili::node& convert);

    /**
     * \brief Add a Vili BaseAttribute in a Lua Table
     *        The key of the newly converted element in the table will be the
     *        BaseAttribute's id
     * \param target The Lua Table you want to write the Vili
     *        element in
     * \param convert The Vili BaseAttribute you want to add in the
     *        Lua Table
     */
    sol::lua_value vili_primitive_to_lua_value(const vili::node& convert);
    /**
     * \brief Adds a converted Vili ListAttribute to a Lua Table.
     *        Index of the List will start at 0 (unlike default Lua lists which
     *        starts at 1). The key of the newly converted element in the table will
     *        be the ListAttribute's id
     * \param target The Lua Table you want to add the
     *        converted ListAttribute
     * \param convert The Vili ComplexAttribute you want
     *        to get the data from
     */
    sol::lua_value vili_array_to_lua_table(const vili::node& convert);
    /**
     * \brief Converts a Lua Table to a Vili ComplexAttribute
     * \param id Id of the newly created ComplexAttribute
     * \param convert The LuaTable you want to convert to a ComplexAttribute
     * \return The converted Lua Table in ComplexAttribute form
     */
    vili::node lua_table_to_vili_object(const sol::table& convert);
    /**
     * \brief Converts a Lua Variable to a Vili BaseAttribute
     * \param id Id of the newly created BaseAttribute
     * \param convert The LuaVar you want to convert to a BaseAttribute
     * \return The converted Lua Element in BaseAttribute form
     */
    vili::node lua_value_to_vili_primitive(const sol::lua_value& convert);
    /**
     * \brief Converts a Lua Table to a Vili ListAttribute
     * \param id Id of the newly created ListAttribute
     * \param convert The Lua Table you want to convert to a ListAttribute
     * \return The converted Lua Table in ListAttribute form
     */
    vili::node lua_table_to_vili_array(const sol::table& convert);
    /**
     * \proxy{obe::script::vili_lua_bridge::vili_to_lua_keep_order}
     */
    sol::lua_value vili_to_lua_keep_order_proxy(sol::this_state state, const vili::node& convert);
} // namespace obe::script::vili_lua_bridge
