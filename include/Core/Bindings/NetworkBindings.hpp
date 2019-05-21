#pragma once

namespace kaguya { class State; }

/**
* \brief Bindings to Network
*/
namespace obe::Bindings::Network
{
	void LoadTcpServer(kaguya::State* lua);
}
