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
            {"type", vili::object_typename},
            {"optional", true},
            {
                "items", vili::object {
                    {"type", vili::string_typename}
                }
            }
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
                "obengine_version", vili::object {
                    {"type", vili::string_typename},
                    {"regex", "\\d+\\.\\d+\\.\\d+"}
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
                "source", vili::object {
                    {"type", vili::string_typename},
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