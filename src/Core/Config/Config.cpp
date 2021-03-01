#include <vili/parser/parser.hpp>
#include <vld8/validator.hpp>

#include <Config/Config.hpp>
#include <Config/Templates/Config.hpp>
#include <Debug/Logger.hpp>
#include <System/Path.hpp>

namespace obe::Config
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
                        {"type", "integer"},
                        {"min", 0}
                    },
                    vili::object {
                        {"type", "string"},
                        {"value", "fill"}
                    }
                }
            }
        };

        vili::node WindowContext = vili::object {
            {"type", "object"},
            {
                "properties", vili::object {
                    {"width", ResolutionDimensionValidator},
                    {"height", ResolutionDimensionValidator},
                    {
                        "fullscreen", vili::object {
                            {"type", "boolean"}
                        }
                    },
                    {
                        "closeable", vili::object {
                            {"type", "boolean"},
                            {"optional", true}
                        }
                    },
                    {
                        "resizeable", vili::object {
                            {"type", "boolean"},
                            {"optional", true}
                        }
                    },
                    {
                        "titlebar", vili::object {
                            {"type", "boolean"},
                            {"optional", true}
                        }
                    },
                    {
                        "title", vili::object {
                            {"type", "string"},
                            {"optional", true}
                        }
                    }
                }
            }
        };

        vili::object InputActionValidator = vili::object {
            {"type", "string"},
            {"regex", actionRe}
        };

        return vili::object {
            {
                "Input", vili::object {
                    {"type", "object"},
                    {"optional", true},
                    {
                        "items", vili::object {
                            {"type", "object"},
                            {
                                "items", vili::object {
                                    {"type", "union"},
                                    {
                                        "types", vili::array {
                                            InputActionValidator,
                                            vili::object {
                                                {"type", "array"},
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
                    {"type", "object"},
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
                    {"type", "object"},
                    {
                        "properties", vili::object {
                            {
                                "framerateTarget", vili::object {
                                    {"type", "integer"},
                                    {"min", 0},
                                    {"optional", true}
                                },
                            },
                            {
                                "vsync", vili::object {
                                    {"type", "boolean"},
                                    {"optional", true}
                                }
                            },
                            {
                                "syncUpdateToRender", vili::object {
                                    {"type", "boolean"},
                                    {"optional", true}
                                }
                            }
                        }
                    }
                }
            },
            {
                "GameConfig", vili::object {
                    {"type", "object"},
                    {
                        "properties", vili::object {
                            {
                                "antiAliasing", vili::object {
                                    {"type", "boolean"},
                                    {"optional", true}
                                }
                            }
                        }
                    }
                }
            },
            {
                "Debug", vili::object {
                    {"type", "object"},
                    {
                        "properties", vili::object {
                            {
                                "Logging", vili::object {
                                    {"type", "object"},
                                    {
                                        "properties", vili::object {
                                            {
                                                "level", vili::object {
                                                    {"type", "integer"},
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

    ConfigurationManager::ConfigurationManager()
        : vili::node(vili::object {})
    {
    }
    void ConfigurationManager::load()
    {
        // TODO: Do not modify MountedPaths directly
        auto mountPoints = System::MountablePath::Paths();
        std::reverse(mountPoints.begin(), mountPoints.end());
        const auto loadResult
            = System::Path(mountPoints).set("Data/config.cfg.vili").findAll();
        for (const std::string path : loadResult)
        {
            Debug::Log->info("Loading config file from {}", path);
            vili::node conf
                = vili::parser::from_file(path, Templates::getConfigTemplates());
            this->merge(conf);
        }
        vili::validator::validate_tree(ConfigValidator(), *this);
    }
} // namespace obe::System