#include <spdlog/sinks/dist_sink.h>

#include <Debug/Logger.hpp>
#include <System/Config.hpp>
#include <System/Loaders.hpp>
#include <Utils/FileUtils.hpp>

namespace obe::Debug
{
    void InitLogger()
    {
        Utils::File::deleteFile("debug.log");
        auto dist_sink = std::make_shared<spdlog::sinks::dist_sink_st>();
        #if defined(_WIN32) || defined(_WIN64)
        const auto sink1 = std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>();
        #else
        auto sink1 = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>();
        #endif
        const auto sink2 = std::make_shared<spdlog::sinks::simple_file_sink_st>("debug.log");

        dist_sink->add_sink(sink1);
        dist_sink->add_sink(sink2);
        Log = std::make_shared<spdlog::logger>("Log", dist_sink);
        Log->set_pattern("[%H:%M:%S.%e]<%l> : %v");
        Log->set_level(spd::level::info);
        Log->info("Logger initialised");
    }

    void InitLoggerLevel()
    {
        const spdlog::level::level_enum lvle = static_cast<spdlog::level::level_enum>(System::Config.at("Debug").getDataNode("logLevel").get<int>());
        std::cout << "Debug level : " << lvle << std::endl;
        if (System::Config->contains("Debug") && System::Config.at("Debug").contains("logLevel"))
            Log->set_level(lvle);
    }
}
