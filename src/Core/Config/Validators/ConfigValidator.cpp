#include <vili/node.hpp>

#include <Utils/VectorUtils.hpp>

namespace obe::config::validators
{
    vili::node config_validator()
    {
        // clang-format off
        std::vector<std::string> input_list = {
            "Add",
            "Backslash",
            "Backspace",
            "Comma",
            "Dash",
            "Delete",
            "Divide",
            "End",
            "Equal",
            "Escape",
            "Home",
            "Insert",
            "LAlt",
            "LBracket",
            "LControl",
            "LShift",
            "Menu",
            "Multiply",
            "PageDown",
            "PageUp",
            "Pause",
            "Period",
            "Quote",
            "RAlt",
            "RBracket",
            "RControl",
            "Return",
            "RShift",
            "RSystem",
            "Semicolon",
            "Slash",
            "Space",
            "Subtract",
            "Tab",
            "Tilde",
            "Left",
            "Right",
            "Up",
            "Down",
            "LMB",
            "MMB",
            "RMB",
            "MouseWheelLeft",
            "MouseWheelRight",
            "MouseWheelUp",
            "MouseWheelDown"
            "NumPad[0-9]",
            "F(1[0-2]|[1-9])",
            "[A-Z]",
            "[0-9]",
            "GP_[0-9]+_BTN_[0-9]+",
            "GP_[0-9]+_AXIS_(X|Y|Z|R|U|PovX|PovY)_(LEFT|UP|RIGHT|DOWN)"
        };
        std::string all_inputs = utils::vector::join(input_list, "|");
        // clang-format on
        std::string action_re = fmt::format("((Idle|Hold|Pressed|Released)"
                                            "\\s*:\\s*({0}))(\\s*\\+\\s*"
                                            "(Idle|Hold|Pressed|Released)"
                                            "\\s*:\\s*({0}))*",
            all_inputs);

        // clang-format off
        vili::node resolution_dimension_validator = vili::object {
            {"type", "union"},
            {
                "types", vili::array {
                    vili::object {
                        {"type", vili::integer_typename},
                        {"min", 0}
                    },
                    vili::object {
                        {"type", vili::string_typename},
                        {"value", "Screen"}
                    }
                }
            }
        };

        vili::node render_resolution_dimension_validator = vili::object {
            {"type", "union"},
            {
                "types", vili::array {
                    vili::object {
                        {"type", vili::integer_typename},
                        {"min", 0}
                    },
                    vili::object {
                        {"type", vili::string_typename},
                        {"values", vili::array {
                            "Screen", "Window"
                        }}
                    }
                }
            }
        };

        vili::node render_validator = vili::object {
            {"type", vili::object_typename},
            {"optional", true},
            {
                "properties", vili::object {
                    {"width", render_resolution_dimension_validator},
                    {"height", render_resolution_dimension_validator},
                    {"stretch", vili::object {
                        {"type", vili::string_typename},
                        {"values", vili::array {
                            "None", "Center", "Stretch", "Fit"
                        }}
                    }}
                }
            }
        };

        vili::node window_context = vili::object {
            {"type", vili::object_typename},
            {
                "properties", vili::object {
                    {"width", resolution_dimension_validator},
                    {"height", resolution_dimension_validator},
                    {"render", render_validator},
                    {
                        "fullscreen", vili::object {
                            {"type", vili::boolean_typename}
                        }
                    },
                    {
                        "closeable", vili::object {
                            {"type", vili::boolean_typename},
                            {"optional", true}
                        }
                    },
                    {
                        "resizeable", vili::object {
                            {"type", vili::boolean_typename},
                            {"optional", true}
                        }
                    },
                    {
                        "titlebar", vili::object {
                            {"type", vili::boolean_typename},
                            {"optional", true}
                        }
                    },
                    {
                        "title", vili::object {
                            {"type", vili::string_typename},
                            {"optional", true}
                        }
                    }
                }
            }
        };

        vili::object input_action_validator = vili::object {
            {"type", vili::string_typename},
            {"regex", action_re}
        };

        return vili::object {
            {
                "Input", vili::object {
                    {"type", vili::object_typename},
                    {"optional", true},
                    {
                        "items", vili::object {
                            {"type", vili::object_typename},
                            {
                                "items", vili::object {
                                    {"type", "union"},
                                    {
                                        "types", vili::array {
                                            input_action_validator,
                                            vili::object {
                                                {"type", vili::array_typename},
                                                {"items", input_action_validator}
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                },
            },
            {
                "Window", vili::object {
                    {"type", vili::object_typename},
                    {
                        "properties", vili::object {
                            {"Game", window_context},
                            {"Editor", window_context}
                        }
                    }
                }
            },
            {
                "Framerate", vili::object {
                    {"type", vili::object_typename},
                    {
                        "properties", vili::object {
                            {
                                "framerateTarget", vili::object {
                                    {"type", vili::integer_typename},
                                    {"min", 0},
                                    {"optional", true}
                                },
                            },
                            {
                                "vsync", vili::object {
                                    {"type", vili::boolean_typename},
                                    {"optional", true}
                                }
                            },
                            {
                                "syncUpdateToRender", vili::object {
                                    {"type", vili::boolean_typename},
                                    {"optional", true}
                                }
                            }
                        }
                    }
                }
            },
            {
                "GameConfig", vili::object {
                    {"type", vili::object_typename},
                    {
                        "properties", vili::object {
                            {
                                "antiAliasing", vili::object {
                                    {"type", vili::boolean_typename},
                                    {"optional", true}
                                }
                            }
                        }
                    }
                }
            },
            {
                "Debug", vili::object {
                    {"type", vili::object_typename},
                    {
                        "properties", vili::object {
                            {
                                "Logging", vili::object {
                                    {"type", vili::object_typename},
                                    {
                                        "properties", vili::object {
                                            {
                                                "level", vili::object {
                                                    {"type", vili::string_typename},
                                                    {"values", vili::array {"Trace", "Debug", "Info", "Warn", "Error", "Critical", "Off"}},
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            },
            {
                "Script", vili::object {
                    {"type", vili::object_typename},
                    {
                        "properties", vili::object {
                            {
                                "Lua", vili::object {
                                    {"type", vili::object_typename},
                                    {
                                        "properties", vili::object {
                                            {
                                                "patchIO", vili::object {
                                                    {"type", vili::boolean_typename},
                                                }
                                            },
                                            {
                                                "garbageCollector", vili::object {
                                                    {"type", vili::string_typename},
                                                    {"values", vili::array {"stop", "incremental", "generational"}},
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
