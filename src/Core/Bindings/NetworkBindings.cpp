#include <Bindings/NetworkBindings.hpp>
#include <Network/TcpServer.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>

#include <kaguya/kaguya.hpp>

namespace obe::Bindings::NetworkBindings
{
	void LoadTcpServer(kaguya::State* lua)
	{
		(*lua)["obe"]["Network"] = kaguya::NewTable();
		(*lua)["obe"]["Network"]["TcpServer"].setClass(
			kaguya::UserdataMetatable<obe::Network::TcpServer>()
				.setConstructors<
					Network::TcpServer(int),
					Network::TcpServer(int, std::string, std::string)
				>()
				.addFunction("setBufferSize", &Network::TcpServer::setBufferSize)
				.addFunction("update", &Network::TcpServer::update)
		);
		System::Path("Lib/Internal/Network.lua").loadResource(&Script::ScriptEngine, System::Loaders::luaLoader);
	}
}