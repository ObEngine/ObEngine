#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Network::Bindings
{
    void LoadClassLuaPacket(sol::state_view state);
    void LoadClassNetworkHandler(sol::state_view state);
    void LoadClassTcpServer(sol::state_view state);
    void LoadClassTcpSocket(sol::state_view state);
};