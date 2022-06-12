#pragma once

namespace sol
{
    class state_view;
};
namespace obe::audio::exceptions::Bindings
{
    void LoadClassAudioFileNotFound(sol::state_view state);
};