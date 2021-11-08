#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/TreeView.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassConstNode(sol::state_view state)
    {
        sol::table TreeViewNamespace = state["tgui"]["TreeView"].get<sol::table>();
        sol::usertype<tgui::TreeView::ConstNode> bindConstNode
            = TreeViewNamespace.new_usertype<tgui::TreeView::ConstNode>(
                "ConstNode", sol::call_constructor, sol::default_constructor);
        bindConstNode["expanded"] = &tgui::TreeView::ConstNode::expanded;
        bindConstNode["text"] = &tgui::TreeView::ConstNode::text;
        bindConstNode["nodes"] = &tgui::TreeView::ConstNode::nodes;
    }
};