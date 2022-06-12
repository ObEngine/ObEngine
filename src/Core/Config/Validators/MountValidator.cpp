#include <vili/node.hpp>

namespace obe::config::validators
{
    vili::node mount_validator()
    {
        // clang-format off
        vili::object mount = vili::object {
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
                                    "type", vili::object {
                                        {"type", vili::string_typename},
                                        {"values", vili::array {"Path", "Project", "Package"}},
                                        {"optional", true}
                                    },
                                },
                                {
                                    "prefix", vili::object {
                                        {"type", vili::string_typename},
                                        {"optional", true}
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
            }
        };
        vili::object mounts = vili::object {
            {"type", vili::object_typename},
            {"items", mount},
            {"optional", true}
        };
        return vili::object {
            {
                "project", vili::object {
                    {"type", vili::string_typename},
                    {"optional", true}
                }
            },
            {
                "mounts", mounts
            }
        };
        // clang-format on
    }
}
