#include <magic_enum/magic_enum.hpp>
#include <vili/node.hpp>

#include <Animation/Animation.hpp>

namespace obe::Config::Validators
{
    vili::node AnimationValidator()
    {
        // clang-format off
        return vili::object {
            {
                "Meta", vili::object {
                    {"type", vili::object_typename},
                    {
                        "properties", vili::object {
                            {
                                "name", vili::object {
                                    {"type", vili::string_typename},
                                    {"min_length", 1}
                                }
                            },
                            {
                                "clock", vili::object {
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
                            }
                        }
                    }
                },
            },
            {
                "Images", vili::object {
                    {"type", vili::object_typename},
                    {
                        "properties", vili::object {
                            {
                                "images", vili::object {
                                    {"type", vili::array_typename},
                                    {
                                        "items", vili::object {
                                            {"type", "union"},
                                            {
                                                "types", vili::array {
                                                    vili::object {{"type", vili::integer_typename}},
                                                    vili::object {{"type", vili::string_typename}},
                                                }
                                            }
                                        }
                                    },
                                    {"min_size", 1}
                                }
                            },
                            {
                                "model", vili::object {
                                    {"type", vili::string_typename},
                                    {"optional", true}
                                }
                            }
                        }
                    }
                }
            },
            {
                "Groups", vili::object {
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
                                        "clock", vili::object {
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
                "Animation", vili::object {
                    {"type", vili::object_typename},
                    {
                        "properties", vili::object {
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
                                                                    magic_enum::enum_name(Animation::AnimationCommand::PlayGroup),
                                                                    magic_enum::enum_name(Animation::AnimationCommand::SetAnimation),
                                                                    magic_enum::enum_name(Animation::AnimationCommand::Wait)
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
                        }
                    }
                }
            }
        };
        // clang-format on
    }
}
