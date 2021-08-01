#include <Bindings/Patches.hpp>

#include <vili/parser/parser_state.hpp>


namespace vili::parser
{
    void state_push_proxy(state* self, node value)
    {
        self->push(std::move(value));
    }
}
