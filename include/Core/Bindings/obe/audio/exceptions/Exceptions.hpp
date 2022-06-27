#pragma once

namespace sol
{
    class state_view;
};
namespace obe::audio::exceptions::bindings
{
    void load_class_audio_file_not_found(sol::state_view state);
};