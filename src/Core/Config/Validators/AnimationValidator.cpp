#include <magic_enum/magic_enum.hpp>
#include <vili/node.hpp>

#include <Animation/Animation.hpp>
#include <Graphics/Spritesheet.hpp>

namespace obe::config::validators
{
    vili::node animation_validator()
    {
        // clang-format off
        return vili::object {
            {
                "name", vili::object {
                    {"type", vili::string_typename},
                    {"min_length", 1}
                }
            },
            {
                "framerate", vili::object {
                    {"type", vili::number_typename},
                    {"optional", true},
                    {"min", 0.f}
                }
            },
            {
                "mode", vili::object {
                    {"type", vili::string_typename},
                    {"values", vili::array {"OneTime", "Loop", "Force"}},
                    {"optional", true}
                }
            },
            {
                "source", vili::object {
                    {"type", "union"},
                    {"types", vili::array {
                        vili::object {
                            {"type", vili::object_typename},
                            {"properties", vili::object {
                                {"spritesheet", graphics::Spritesheet::Schema() }
                            }}
                        },
                        vili::object {
                            {"type", vili::object_typename},
                            {"properties", vili::object {
                                {"images", vili::object {
                                    {"type", vili::array_typename},
                                    {"items", vili::object {
                                        {"type", vili::string_typename}
                                    }}
                                }}
                            }}
                        }
                    }},
                }
            },
            {
                "groups", vili::object {
                    {"type", vili::object_typename},
                    {
                        "items", vili::object {
                            {"type", vili::object_typename},
                            {
                                "properties", vili::object {
                                    {
                                        "content", vili::object {
                                            {"type", vili::array_typename},
                                            {
                                                "items", vili::object {
                                                    {"type", vili::integer_typename}
                                                }
                                            }
                                        }
                                    },
                                    {
                                        "framerate", vili::object {
                                            {"type", vili::number_typename},
                                            {"optional", true}
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            },
            {
                "code", vili::object {
                    {"type", vili::array_typename},
                    {
                        "items", vili::object {
                            {"type", vili::object_typename},
                            {
                                "properties", vili::object {
                                    {
                                        "command", vili::object {
                                            {"type", vili::string_typename},
                                            {
                                                "values", vili::array {
                                                    magic_enum::enum_name(animation::AnimationCommand::PlayGroup),
                                                    magic_enum::enum_name(animation::AnimationCommand::SetAnimation),
                                                    magic_enum::enum_name(animation::AnimationCommand::Wait)
                                                }
                                            }
                                        },
                                    },
                                    {
                                        "group", vili::object {
                                            {"type", vili::string_typename},
                                            {"optional", true}
                                        }
                                    },
                                    {
                                        "repeat", vili::object {
                                            {"type", vili::integer_typename},
                                            {"optional", true}
                                        }
                                    },
                                    {
                                        "animation", vili::object {
                                            {"type", vili::string_typename},
                                            {"optional", true}
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        };
        // clang-format on
    }
}
