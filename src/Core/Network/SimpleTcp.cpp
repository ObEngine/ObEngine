#include <atomic>
#include <brynet/base/AppStatus.hpp>
#include <brynet/net/EventLoop.hpp>
#include <brynet/net/TcpService.hpp>
#include <brynet/net/wrapper/ServiceBuilder.hpp>
#include <iostream>
#include <mutex>
#include <Network/SimpleTcp.hpp>

using namespace brynet;
using namespace brynet::net;

std::atomic_llong TotalRecvSize = ATOMIC_VAR_INIT(0);
std::atomic_llong total_client_num = ATOMIC_VAR_INIT(0);
std::atomic_llong total_packet_num = ATOMIC_VAR_INIT(0);

int run_server()
{
    auto service = IOThreadTcpService::Create();
    service->startWorkerThread(1);

    auto enterCallback = [](const TcpConnection::Ptr& session)
    {
        total_client_num++;

        session->setDataCallback(
            [session](brynet::base::BasePacketReader& reader)
            {
                std::string_view data = std::string_view(reader.begin(), reader.size());
                std::cout << "Received " << data << std::endl;
                reader.consumeAll();
            });

        session->setDisConnectCallback(
            [](const TcpConnection::Ptr& session)
            {
                (void)session;
                total_client_num--;
            });
    };

    wrapper::ListenerBuilder listener;
    listener.WithService(service)
        .AddSocketProcess({ [](TcpSocket& socket) { socket.setNodelay(); } })
        .WithMaxRecvBufferSize(1024)
        .AddEnterCallback(enterCallback)
        .WithAddr(false, "0.0.0.0", 16789)
        .asyncRun();

    EventLoop mainLoop;
    while (true)
    {
        mainLoop.loop(1000);

        std::cout << "total recv : " << TotalRecvSize
                    << " bytes/s, of client num:" << total_client_num << std::endl;


        std::cout << "packet num:" << total_packet_num << std::endl;
        total_packet_num = 0;
        TotalRecvSize = 0;

        if (brynet::base::app_kbhit())
        {
            break;
        }
    }

    return 0;
}
