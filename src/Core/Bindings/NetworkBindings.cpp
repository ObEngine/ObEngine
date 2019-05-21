#include <Bindings/NetworkBindings.hpp>
#include <Network/TcpServer.hpp>

#include <kaguya/kaguya.hpp>

namespace obe::Bindings::NetworkBindings
{
	void LoadTcpServer(kaguya::State* lua)
	{
		(*lua)["obe"]["Network"]["TcpServer"].setClass(
			kaguya::UserdataMetatable<obe::Network::TcpServer>()
				.setConstructors<
					obe::Network::TcpServer(int),
					obe::Network::TcpServer(int, std::string, std::string)
				>()
				.addFunction("setBufferSize", &obe::Network::TcpServer::setBufferSize)
				.addFunction("update", &obe::Network::TcpServer::update)
		);
	}
}