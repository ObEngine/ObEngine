#pragma once

#include <kaguya/kaguya.hpp>
#include <vili/Vili.hpp>

#include "Functions.hpp"

namespace obe
{
    namespace Script
    {
        /**
         * \brief Functions that allow the conversion of Vili elements to Lua elements
         */
        namespace DataBridge
        {
            void dataToLua(kaguya::LuaTable& target, vili::Attribute& convert);
            vili::Attribute* luaToData(kaguya::LuaRef& convert);
            /**
             * \brief Adds a converted Vili ComplexAttribute to a Lua Table
             *        The key of the newly converted element in the table will be the ComplexAttribute's id
             * \param target The Lua Table you want to add the converted ComplexAttribute
             * \param convert The Vili ComplexAttribute you want to get the data from
             */
            void complexAttributeToLuaTable(kaguya::LuaTable& target, vili::ComplexAttribute& convert);
            /**
             * \brief Add a Vili BaseAttribute in a Lua Table
             *        The key of the newly converted element in the table will be the BaseAttribute's id
             * \param target The Lua Table you want to write the Vili element in
             * \param convert The Vili BaseAttribute you want to add in the Lua Table
             */
            void baseAttributeToLuaElement(kaguya::LuaTable& target, vili::BaseAttribute& convert);
            /**
            * \brief Adds a converted Vili ListAttribute to a Lua Table. \n
            *        Index of the List will start at 0 (unlike default Lua lists which starts at 1). \n
            *        The key of the newly converted element in the table will be the ListAttribute's id
            * \param target The Lua Table you want to add the converted ListAttribute
            * \param convert The Vili ComplexAttribute you want to get the data from
            */
            void listAttributeToLuaTable(kaguya::LuaTable& target, vili::ListAttribute& convert);
            /**
             * \brief Converts a Lua Table to a Vili ComplexAttribute
             * \param id Id of the newly created ComplexAttribute
             * \param convert The LuaTable you want to convert to a ComplexAttribute
             * \return The converted Lua Table in ComplexAttribute form
             */
            vili::ComplexAttribute* luaTableToComplexAttribute(std::string id, kaguya::LuaRef& convert);
            /**
             * \brief Converts a Lua Variable to a Vili BaseAttribute
             * \param id Id of the newly created BaseAttribute
             * \param convert The LuaVar you want to convert to a BaseAttribute
             * \return The converted Lua Element in BaseAttribute form
             */
            vili::BaseAttribute* luaElementToBaseAttribute(std::string id, kaguya::LuaRef& convert);
            /**
             * \brief Converts a Lua Table to a Vili ListAttribute
             * \param id Id of the newly created ListAttribute
             * \param convert The Lua Table you want to convert to a ListAttribute
             * \return The converted Lua Table in ListAttribute form
             */
            vili::ListAttribute* luaTableToListAttribute(std::string id, kaguya::LuaTable& convert);
        }
    }
}
