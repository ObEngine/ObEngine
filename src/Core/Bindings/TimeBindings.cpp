#include <Bindings/TimeBindings.hpp>
#include <Time/FramerateCounter.hpp>
#include <Time/Chronometer.hpp>
#include <Time/FramerateManager.hpp>
#include <Time/TimeCheck.hpp>
#include <Time/TimeUtils.hpp>

#include <kaguya/kaguya.hpp>

namespace obe::Bindings::TimeBindings
{
    void LoadChronometer(kaguya::State* lua)
    {
        (*lua)["obe"]["Chronometer"].setClass(kaguya::UserdataMetatable<Time::Chronometer>()
            .setConstructors<Time::Chronometer()>()
            .addFunction("getTime", &Time::Chronometer::getTime)
            .addFunction("limitExceeded", &Time::Chronometer::limitExceeded)
            .addFunction("setLimit", &Time::Chronometer::setLimit)
            .addFunction("start", &Time::Chronometer::start)
            .addFunction("stop", &Time::Chronometer::stop)
        );
    }

    void LoadFPSCounter(kaguya::State* lua)
    {
        (*lua)["obe"]["FPSCounter"].setClass(kaguya::UserdataMetatable<Time::FPSCounter>()
            .addFunction("draw", &Time::FPSCounter::draw)
            .addFunction("loadFont", &Time::FPSCounter::loadFont)
            .addFunction("tick", &Time::FPSCounter::tick)
            .addFunction("uTick", &Time::FPSCounter::uTick)
        );
    }

    void LoadFramerateManager(kaguya::State* lua)
    {
        (*lua)["obe"]["FramerateManager"].setClass(kaguya::UserdataMetatable<Time::FramerateManager>()
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

    void LoadTimeCheck(kaguya::State* lua)
    {
        (*lua)["obe"]["TimeCheck"].setClass(kaguya::UserdataMetatable<Time::TimeCheck>()
            .setConstructors<Time::TimeCheck(Time::TimeUnit), Time::TimeCheck(Time::TimeUnit, bool)>()
            .addFunction("getDelay", &Time::TimeCheck::getDelay)
            .addFunction("goToOver", &Time::TimeCheck::goToOver)
            .addFunction("over", &Time::TimeCheck::over)
            .addFunction("reset", &Time::TimeCheck::reset)
            .addFunction("resetIfOver", &Time::TimeCheck::resetIfOver)
            .addFunction("setDelay", &Time::TimeCheck::setDelay)
        );
    }

    void LoadTimeUtils(kaguya::State* lua)
    {
        (*lua)["obe"]["TickSinceEpoch"] = kaguya::function(Time::getTickSinceEpoch);
        (*lua)["obe"]["TickSinceEpochMicro"] = kaguya::function(Time::getTickSinceEpochMicro);
    }
}
