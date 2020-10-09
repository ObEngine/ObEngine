#include <Animation/AnimationValidator.hpp>
#include <Config/Templates/Animation.hpp>

namespace obe::Animation
{
    vili::node AnimationValidator()
    {
        // clang-format off
        return vili::object {
            {
                "Meta", vili::object {
                    {"type", "object"},
                    {
                        "properties", vili::object {
                            {
                                "name", vili::object {
                                    {"type", "string"},
                                    {"min_length", 1}
                                }
                            },
                            {
                                "clock", vili::object {
                                    {"type", "number"},
                                    {"optional", true},
                                    {"min", 0.f}
                                }
                            },
                            {
                                "mode", vili::object {
                                    {"type", "string"},
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
                    {"type", "object"},
                    {
                        "properties", vili::object {
                            {
                                "images", vili::object {
                                    {"type", "array"},
                                    {
                                        "items", vili::object {
                                            {"type", "union"},
                                            {
                                                "types", vili::array {
                                                    vili::object {{"type", "integer"}},
                                                    vili::object {{"type", "string"}},
                                                }
                                            }
                                        }
                                    },
                                    {"min_size", 1}
                                }
                            },
                            {
                                "model", vili::object {
                                    {"type", "string"},
                                    {"optional", true}
                                }
                            }
                        }
                    }
                }
            },
            {
                "Groups", vili::object {
                    {"type", "object"},
                    {
                        "items", vili::object {
                            {"type", "object"},
                            {
                                "properties", vili::object {
                                    {
                                        "content", vili::object {
                                            {"type", "array"},
                                            {
                                                "items", vili::object {
                                                    {"type", "integer"}
                                                }
                                            }
                                        }
                                    },
                                    {
                                        "clock", vili::object {
                                            {"type", "float"},
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
                    {"type", "object"},
                    {
                        "properties", vili::object {
                            {
                                "code", vili::object {
                                    {"type", "array"},
                                    {
                                        "items", vili::object {
                                            {"type", "object"},
                                            {
                                                "properties", vili::object {
                                                    {
                                                        "command", vili::object {
                                                            {"type", "string"},
                                                            {
                                                                "values", vili::array {
                                                                    vili::string { Config::Templates::play_group_command },
                                                                    vili::string { Config::Templates::set_animation_command },
                                                                    vili::string { Config::Templates::wait_command }
                                                                }
                                                            }
                                                        },
                                                    },
                                                    {
                                                        "group", vili::object {
                                                            {"type", "string"},
                                                            {"optional", true}
                                                        }
                                                    },
                                                    {
                                                        "repeat", vili::object {
                                                            {"type", "integer"},
                                                            {"optional", true}
                                                        }
                                                    },
                                                    {
                                                        "animation", vili::object {
                                                            {"type", "string"},
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