#include <vili/node.hpp>

#include <Utils/VectorUtils.hpp>

namespace obe::config::validators
{
    vili::node config_validator()
    {
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
                                "framerate", vili::object {
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
                                "anti_aliasing", vili::object {
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
