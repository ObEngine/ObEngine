#pragma once

#include <sol/sol.hpp>
#include <vili/node.hpp>

/**
 * \brief Functions that allow the conversion of Vili elements to Lua elements
 */
namespace obe::Script::ViliLuaBridge
{
    sol::lua_value viliToLua(vili::node& convert);
    vili::node luaToVili(sol::object convert);
    /**
     * \brief Adds a converted Vili ComplexAttribute to a Lua Table
     *        The key of the newly converted element in the table will be the
     *        ComplexAttribute's id
     * \param target The Lua Table you want to add the
     *        converted ComplexAttribute
     * \param convert The Vili Node you
     *        want to get the data from
     */
    sol::lua_value viliObjectToLuaTable(vili::node& convert);
    /**
     * \brief Add a Vili BaseAttribute in a Lua Table
     *        The key of the newly converted element in the table will be the
     *        BaseAttribute's id
     * \param target The Lua Table you want to write the Vili
     *        element in
     * \param convert The Vili BaseAttribute you want to add in the
     *        Lua Table
     */
    sol::lua_value viliPrimitiveToLuaValue(vili::node& convert);
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
    sol::lua_value viliArrayToLuaTable(vili::node& convert);
    /**
     * \brief Converts a Lua Table to a Vili ComplexAttribute
     * \param id Id of the newly created ComplexAttribute
     * \param convert The LuaTable you want to convert to a ComplexAttribute
     * \return The converted Lua Table in ComplexAttribute form
     */
    vili::node luaTableToViliObject(sol::table convert);
    /**
     * \brief Converts a Lua Variable to a Vili BaseAttribute
     * \param id Id of the newly created BaseAttribute
     * \param convert The LuaVar you want to convert to a BaseAttribute
     * \return The converted Lua Element in BaseAttribute form
     */
    vili::node luaValueToViliPrimitive(sol::lua_value convert);
    /**
     * \brief Converts a Lua Table to a Vili ListAttribute
     * \param id Id of the newly created ListAttribute
     * \param convert The Lua Table you want to convert to a ListAttribute
     * \return The converted Lua Table in ListAttribute form
     */
    vili::node luaTableToViliArray(sol::table convert);
} // namespace obe::Script::DataBridge