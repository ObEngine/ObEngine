#pragma once

#include <string_view>

#include <vili/parser/parser_state.hpp>

namespace obe::Config::Templates
{
    constexpr std::string_view wait_command = "wait";
    constexpr std::string_view play_group_command = "play_group";
    constexpr std::string_view set_animation_command = "set_animation";
    vili::parser::state getAnimationTemplates();
}