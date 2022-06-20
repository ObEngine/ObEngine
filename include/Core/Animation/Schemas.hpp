#pragma once

#include <string_view>

#include <vili/parser.hpp>

namespace obe::animation::schemas
{
    constexpr std::string_view AnimationSchemaStr = R"SCHEMA(
Meta:
    type: "object"
    properties:
        name:
            type: "string"
            min_length: 1
        clock:
            type: "number"
            optional: true
            min: 0
        mode:
            type: "string"
            values: ["Once", "Loop", "Force"]
            optional: true
Images:
    type: "object"
    properties:
        images:
            type: "array"
            items:
                type: "union"
                types: ["string", "integer"]
            min_size: 1
        model:
            type: "string"
            optional: true
Groups:
    type: "object"
    items:
        type: "object"
        properties:
            content:
                type: "array"
                items:
                    type: "integer"
            clock:
                type: "number"
                optional: true
animation:
    type: "object"
    properties:
        code:
            type: "array"
            items:
                type: "object"
                properties:
                    command:
                        type: "string"
                        values: ["PlayGroup", "SetAnimation", "Wait"]
                    group:
                        type: "string"
                        optional: true
                    repeat:
                        type: "integer"
                        optional: true
                    animation:
                        type: "string"
                        optional: true
)SCHEMA";

    static vili::node AnimationSchema = vili::parser::from_string(AnimationSchemaStr);
}