#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/TreeView.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassNode(sol::state_view state)
    {
        sol::table TreeViewNamespace = state["tgui"]["TreeView"].get<sol::table>();
        sol::usertype<tgui::TreeView::Node> bindNode
            = TreeViewNamespace.new_usertype<tgui::TreeView::Node>(
                "Node", sol::call_constructor, sol::default_constructor);
        bindNode["text"] = &tgui::TreeView::Node::text;
        bindNode["depth"] = &tgui::TreeView::Node::depth;
        bindNode["expanded"] = &tgui::TreeView::Node::expanded;
        bindNode["parent"] = &tgui::TreeView::Node::parent;
        bindNode["nodes"] = &tgui::TreeView::Node::nodes;
    }
};