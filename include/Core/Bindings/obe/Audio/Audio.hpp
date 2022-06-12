#pragma once

namespace sol
{
    class state_view;
};
namespace obe::audio::Bindings
{
    void LoadClassAudioManager(sol::state_view state);
    void LoadClassSound(sol::state_view state);
    void LoadEnumLoadPolicy(sol::state_view state);
    void LoadEnumSoundStatus(sol::state_view state);
};