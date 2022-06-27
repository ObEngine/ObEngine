#pragma once

namespace vili
{
    class node;

    /**
     * \nobind
     */
    namespace exceptions
    {
    }
}

namespace vili::parser
{
    class state;
    /**
     * \proxy{vili::parser::state::push}
     */
    void state_push_proxy(state* self, node value);
    /**
     * \flagsurrogate{vili::node}
     * \helper{obe://Lib/Internal/Vili.lua}
     */
    class _PatchNode
    {
    };
    /**
     * \flagsurrogate{vili::node::is}
     * \nobind
     */
    class _PatchNode_is
    {
    };
    /**
     * \flagsurrogate{vili::node::as}
     * \nobind
     */
    class _PatchNode_as
    {
    };
    /**
     * \flagsurrogate{vili::node::emplace}
     * \nobind
     */
    class _PatchNode_emplace
    {
    };
    /**
     * \flagsurrogate{vili::node::data}
     * \nobind
     */
    class _PatchNode_data
    {
    };
    /**
     * \flagsurrogate{vili::parser::error_message}
     * \nobind
     */
    class _Patch_error_message
    {
    };
    /**
     * \nobind
     */
    namespace error_messages
    {
    }
}
