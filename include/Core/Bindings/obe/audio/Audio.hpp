#pragma once

namespace sol
{
    class state_view;
};
namespace obe::audio::bindings
{
    void load_class_audio_manager(sol::state_view state);
    void load_class_sound(sol::state_view state);
    void load_enum_load_policy(sol::state_view state);
    void load_enum_sound_status(sol::state_view state);
};