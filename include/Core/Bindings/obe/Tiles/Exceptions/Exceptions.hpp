#pragma once

namespace sol
{
    class state_view;
};
namespace obe::tiles::exceptions::bindings
{
    void load_class_tile_position_outside_layer(sol::state_view state);
    void load_class_unknown_tile_id(sol::state_view state);
    void load_class_unknown_tile_layer(sol::state_view state);
    void load_class_unknown_tileset(sol::state_view state);
};