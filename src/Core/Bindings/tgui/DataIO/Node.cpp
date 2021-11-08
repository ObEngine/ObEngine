#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Loading/DataIO.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassNode(sol::state_view state)
    {
        sol::table DataIONamespace = state["tgui"]["DataIO"].get<sol::table>();
        sol::usertype<tgui::DataIO::Node> bindNode
            = DataIONamespace.new_usertype<tgui::DataIO::Node>(
                "Node", sol::call_constructor, sol::default_constructor);
        bindNode["parent"] = &tgui::DataIO::Node::parent;
        bindNode["children"] = &tgui::DataIO::Node::children;
        bindNode["propertyValuePairs"] = &tgui::DataIO::Node::propertyValuePairs;
        bindNode["name"] = &tgui::DataIO::Node::name;
    }
};