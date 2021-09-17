#include <vili/node.hpp>

namespace obe::Config::Validators
{
    vili::node ProjectValidator()
    {
        // clang-format off
        vili::object urls = vili::object {
            {"type", vili::object_typename},
            {"optional", true},
            {"properties",
                vili::object {
                    {
                        "homepage", vili::object {
                            {"type", vili::string_typename},
                            {"optional", true}
                        },
                    },
                    {
                        "issues", vili::object {
                            {"type", vili::string_typename},
                            {"optional", true}
                        },
                    },
                    {
                        "readme", vili::object {
                            {"type", vili::string_typename},
                            {"optional", true}
                        },
                    },
                    {
                        "documentation", vili::object {
                            {"type", vili::string_typename},
                            {"optional", true}
                        },
                    },
                    {
                        "license", vili::object {
                            {"type", vili::string_typename},
                            {"optional", true}
                        },
                    },
                }
            }
        };

        vili::object mounts = vili::object {
            {"type", "union"},
            {
                "types", vili::array {
                    vili::object {
                        {"type", vili::object_typename},
                        {
                            "properties", vili::object {
                                {
                                    "path", vili::object {
                                        {"type", vili::string_typename}
                                    }
                                },
                                {
                                    "priority", vili::object {
                                        {"type", vili::integer_typename},
                                        {"optional", true}
                                    }
                                },
                                {
                                    "implicit", vili::object {
                                        {"type", vili::boolean_typename},
                                        {"optional", true}
                                    }
                                }
                            }
                        }
                    },
                    vili::object {
                        {"type", vili::string_typename},
                    }
                }
            },
            {"optional", true},

        };

        return vili::object {
            {
                "id", vili::object {
                    {"type", vili::string_typename}
                },
            },
            {
                "name", vili::object {
                    {"type", vili::string_typename}
                },
            },
            {
                "source", vili::object {
                    {"type", vili::string_typename},
                },
            },
            {
                "version", vili::object {
                    {"type", vili::string_typename},
                    {"regex", "\\d+\\.\\d+\\.\\d+"}
                },
            },
            {
                "obengine_version", vili::object {
                    {"type", vili::string_typename},
                    {"regex", "\\d+\\.\\d+\\.\\d+"}
                },
            },
            {
                "authors", vili::object {
                    {"type", vili::array_typename},
                    {"items", vili::object {
                        {"type", vili::string_typename}
                    }},
                    {"optional", true}
                },
            },
            {
                "description", vili::object {
                    {"type", vili::string_typename},
                    {"optional", true}
                },
            },
            {
                "keywords", vili::object {
                    {"type", vili::array_typename},
                    {"items", vili::object {
                        {"type", vili::string_typename}
                    }},
                    {"optional", true}
                },
            },
            {
                "categories", vili::object {
                    {"type", vili::array_typename},
                    {"items", vili::object {
                        {"type", vili::string_typename}
                    }},
                    {"optional", true}
                },
            },
            {
                "license", vili::object {
                    {"type", vili::string_typename},
                    {"optional", true}
                },
            },
            {
                "include", vili::object {
                    {"type", vili::array_typename},
                    {"items", vili::object {
                        {"type", vili::string_typename}
                    }},
                    {"optional", true}
                },
            },
            {
                "exclude", vili::object {
                    {"type", vili::array_typename},
                    {"items", vili::object {
                        {"type", vili::string_typename}
                    }},
                    {"optional", true}
                },
            },
            {
                "urls", urls
            },
            {
                "mounts", mounts
            }
        };
        // clang-format on
    }
}