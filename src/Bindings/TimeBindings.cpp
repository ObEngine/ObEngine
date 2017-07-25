#include <Bindings/TimeBindings.hpp>
#include <Time/FramerateCounter.hpp>
#include <Time/Chronometer.hpp>
#include <Time/FramerateManager.hpp>

namespace obe
{
    namespace Bindings
    {
        namespace TimeBindings
        {
            void LoadChronometer(kaguya::State* lua)
            {
                (*lua)["Core"]["Time"]["Chronometer"].setClass(kaguya::UserdataMetatable<Time::Chronometer>()
                    .addFunction("getTime", &Time::Chronometer::getTime)
                    .addFunction("limitExceeded", &Time::Chronometer::limitExceeded)
                    .addFunction("setLimit", &Time::Chronometer::setLimit)
                    .addFunction("start", &Time::Chronometer::start)
                    .addFunction("stop", &Time::Chronometer::stop)
                );
            }
            void LoadFPSCounter(kaguya::State* lua)
            {
                (*lua)["Core"]["Time"]["FPSCounter"].setClass(kaguya::UserdataMetatable<Time::FPSCounter>()
                    .addFunction("draw", &Time::FPSCounter::draw)
                    .addFunction("loadFont", &Time::FPSCounter::loadFont)
                    .addFunction("tick", &Time::FPSCounter::tick)
                    .addFunction("uTick", &Time::FPSCounter::uTick)
                );
            }
            void LoadFramerateManager(kaguya::State* lua)
            {
                (*lua)["Core"]["Time"]["FramerateManager"].setClass(kaguya::UserdataMetatable<Time::FramerateManager>()
                    .addFunction("doRender", &Time::FramerateManager::doRender)
                    .addFunction("getDeltaTime", &Time::FramerateManager::getDeltaTime)
                    .addFunction("getFramerateTarget", &Time::FramerateManager::getFramerateTarget)
                    .addFunction("getGameSpeed", &Time::FramerateManager::getGameSpeed)
                    .addFunction("getSpeedCoeff", &Time::FramerateManager::getSpeedCoeff)
                    .addFunction("isFramerateLimited", &Time::FramerateManager::isFramerateLimited)
                    .addFunction("isVSyncEnabled", &Time::FramerateManager::isVSyncEnabled)
                    .addFunction("limitFramerate", &Time::FramerateManager::limitFramerate)
                    .addFunction("setFramerateTarget", &Time::FramerateManager::setFramerateTarget)
                    .addFunction("setSpeedCoeff", &Time::FramerateManager::setSpeedCoeff)
                    .addFunction("setVSyncEnabled", &Time::FramerateManager::setVSyncEnabled)
                    .addFunction("update", &Time::FramerateManager::update)
                );
            }
        }
    }
}
