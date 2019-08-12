#pragma once

namespace kaguya { class State; }

/**
* \brief Bindings to Network
*/
namespace obe::Bindings::NetworkBindings
{
    void LoadTcpServer(kaguya::State* lua);
}
