#pragma once

namespace obe
{
    void DOSOMETHING();
}

namespace vili
{
    class node;
}

namespace vili::parser
{
    class state;
    /**
     * \proxy{vili::parser::state::push}
     */
    void state_push_proxy(state* self, node value);
}