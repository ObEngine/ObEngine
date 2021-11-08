#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Loading/DataIO.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassValueNode(sol::state_view state)
    {
        sol::table DataIONamespace = state["tgui"]["DataIO"].get<sol::table>();
        sol::usertype<tgui::DataIO::ValueNode> bindValueNode
            = DataIONamespace.new_usertype<tgui::DataIO::ValueNode>("ValueNode",
                sol::call_constructor,
                sol::constructors<tgui::DataIO::ValueNode(),
                    tgui::DataIO::ValueNode(const tgui::String&)>());
        bindValueNode["value"] = &tgui::DataIO::ValueNode::value;
        bindValueNode["listNode"] = &tgui::DataIO::ValueNode::listNode;
        bindValueNode["valueList"] = &tgui::DataIO::ValueNode::valueList;
    }
};