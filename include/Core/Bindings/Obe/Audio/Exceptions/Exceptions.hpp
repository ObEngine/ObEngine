#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Audio::Exceptions::Bindings
{
    void LoadClassAudioFileNotFound(sol::state_view state);
};