#include <vili/node.hpp>

#include <Config/Validators.hpp>

namespace obe::config::validators
{
    vili::node project_validator()
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

        vili::node mountValidator = mount_validator();
        vili::object mounts = mountValidator.at("mounts").as<vili::object>();

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
                "standalone", vili::object {
                    {"type", vili::boolean_typename},
                    {"optional", true}
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
