#include <string>

#ifndef ANDROID_FROMX86
#include <android/log.h>
#include <android_native_app_glue.h>
#endif
//#include <Debug/Logger.hpp>
//#include <Transform/UnitVector.hpp>

#ifdef ANDROID_FROMX86
struct android_app
{
};
#endif

void android_main(struct android_app* state)
{
    /*obe::Debug::InitLogger();
    obe::Debug::Log->set_level(spdlog::level::level_enum::trace);
    obe::Debug::Log->trace("Testing trace");
    obe::Debug::Log->debug("Testing debug");
    obe::Debug::Log->info("Testing info");
    obe::Debug::Log->warn("Testing warning");
    obe::Debug::Log->error("Testing error");
    obe::Transform::UnitVector uv(33, 55);
    obe::Debug::Log->info("Test UnitVector Coordinates : {}, {}", uv.x, uv.y);*/
}

#ifdef ANDROID_FROMX86
int main(int argc, char** argv)
{
    android_main(nullptr);
}
#endif