#include <vili/node.hpp>

namespace obe::Config::Validators
{
    vili::node ConfigValidator()
    {
        std::string actionRe = std::string(
            "((Idle|Hold|Pressed|Released)\\s*:\\s*(Add|Backslash|Backspace|Comma|Dash|"
            "Delete|"
            "Divide|End|Equal|Escape|Home|Insert|LAlt|LBracket|LControl|LShift|Menu|"
            "Multiply|PageDown|PageUp|Pause|Period|Quote|RAlt|RBracket|RControl|Return|"
            "RShift|RSystem|Semicolon|Slash|Space|Subtract|Tab|Tilde|Left|Right|Up|Down|"
            "LMB|MMB|RMB|MouseWheelLeft|MouseWheelRight|MouseWheelUp|MouseWheelDown|"
            "NumPad[0-9]|F(1[0-2]|[1-9])|[A-Z]|[0-9]))(\\s*\\+\\s*(Idle|Hold|"
            "Pressed|Released)\\s*:\\s*(Add|Backslash|Backspace|Comma|Dash|Delete|Divide|"
            "End|"
            "Equal|Escape|Home|Insert|LAlt|LBracket|LControl|LShift|Menu|Multiply|"
            "PageDown|PageUp|Pause|Period|Quote|RAlt|RBracket|RControl|Return|RShift|"
            "RSystem|Semicolon|Slash|Space|Subtract|Tab|Tilde|Left|Right|Up|Down|LMB|MMB|"
            "RMB|MouseWheelLeft|MouseWheelRight|MouseWheelUp|MouseWheelDown|NumPad[0-9]|"
            "F(1[0-2]|[1-9])|[A-Z]|[0-9]))*");

        // clang-format off
        vili::node ResolutionDimensionValidator = vili::object {
            {"type", "union"},
            {
                "types", vili::array {
                    vili::object {
                        {"type", vili::integer_typename},
                        {"min", 0}
                    },
                    vili::object {
                        {"type", vili::string_typename},
                        {"value", "fill"}
                    }
                }
            }
        };

        vili::node WindowContext = vili::object {
            {"type", vili::object_typename},
            {
                "properties", vili::object {
                    {"width", ResolutionDimensionValidator},
                    {"height", ResolutionDimensionValidator},
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

        vili::object InputActionValidator = vili::object {
            {"type", vili::string_typename},
            {"regex", actionRe}
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
                                            InputActionValidator,
                                            vili::object {
                                                {"type", vili::array_typename},
                                                {"items", InputActionValidator}
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
                            {"Game", WindowContext},
                            {"Editor", WindowContext}
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
                                                    {"type", vili::integer_typename},
                                                    {"min", 0},
                                                    {"max", 6}
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