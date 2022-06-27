#include <Bindings/Config.hpp>
#include <Bindings/Exceptions.hpp>
#include <Bindings/Patches.hpp>
#include <Bindings/obe/Component/Component.hpp>
#include <Bindings/obe/Component/Exceptions/Exceptions.hpp>
#include <Bindings/obe/Obe.hpp>
#include <Bindings/obe/Types/Types.hpp>
#include <Bindings/obe/animation/Animation.hpp>
#include <Bindings/obe/animation/easing/Easing.hpp>
#include <Bindings/obe/animation/schemas/Schemas.hpp>
#include <Bindings/obe/audio/Audio.hpp>
#include <Bindings/obe/bindings/Bindings.hpp>
#include <Bindings/obe/collision/Collision.hpp>
#include <Bindings/obe/config/Config.hpp>
#include <Bindings/obe/config/validators/Validators.hpp>
#include <Bindings/obe/debug/Debug.hpp>
#include <Bindings/obe/debug/render/Render.hpp>
#include <Bindings/obe/engine/Engine.hpp>
#include <Bindings/obe/event/Event.hpp>
#include <Bindings/obe/events/Actions/Actions.hpp>
#include <Bindings/obe/events/Cursor/Cursor.hpp>
#include <Bindings/obe/events/Game/Game.hpp>
#include <Bindings/obe/events/Keys/Keys.hpp>
#include <Bindings/obe/events/Network/Network.hpp>
#include <Bindings/obe/events/Scene/Scene.hpp>
#include <Bindings/obe/graphics/Graphics.hpp>
#include <Bindings/obe/graphics/canvas/Canvas.hpp>
#include <Bindings/obe/graphics/shapes/Shapes.hpp>
#include <Bindings/obe/graphics/utils/Utils.hpp>
#include <Bindings/obe/input/Input.hpp>
#include <Bindings/obe/network/Network.hpp>
#include <Bindings/obe/scene/Scene.hpp>
#include <Bindings/obe/script/Helpers/Helpers.hpp>
#include <Bindings/obe/script/Script.hpp>
#include <Bindings/obe/script/vili_lua_bridge/ViliLuaBridge.hpp>
#include <Bindings/obe/system/System.hpp>
#include <Bindings/obe/system/constraints/Constraints.hpp>
#include <Bindings/obe/system/package/Package.hpp>
#include <Bindings/obe/system/prefixes/Prefixes.hpp>
#include <Bindings/obe/system/priorities/Priorities.hpp>
#include <Bindings/obe/system/project/Prefixes/Prefixes.hpp>
#include <Bindings/obe/system/project/Project.hpp>
#include <Bindings/obe/tiles/Tiles.hpp>
#include <Bindings/obe/time/Time.hpp>
#include <Bindings/obe/transform/Transform.hpp>
#include <Bindings/obe/utils/Utils.hpp>
#include <Bindings/obe/utils/exec/Exec.hpp>
#include <Bindings/obe/utils/file/File.hpp>
#include <Bindings/obe/utils/math/Math.hpp>
#include <Bindings/obe/utils/string/String.hpp>
#include <Bindings/obe/utils/vector/Vector.hpp>
#include <Bindings/vili/Vili.hpp>
#include <Bindings/vili/parser/Parser.hpp>
#include <Bindings/vili/parser/rules/Rules.hpp>
#include <Bindings/vili/utils/string/String.hpp>
#include <Bindings/vili/writer/Writer.hpp>
#include <sol/sol.hpp>
namespace obe::bindings
{
    void index_core_bindings(sol::state_view state)
    {
        state["obe"].get_or_create<sol::table>();
        state["vili"].get_or_create<sol::table>();
        state["obe"]["Component"].get_or_create<sol::table>();
        state["obe"]["types"].get_or_create<sol::table>();
        state["obe"]["animation"].get_or_create<sol::table>();
        state["obe"]["audio"].get_or_create<sol::table>();
        state["obe"]["collision"].get_or_create<sol::table>();
        state["obe"]["config"].get_or_create<sol::table>();
        state["obe"]["engine"].get_or_create<sol::table>();
        state["obe"]["event"].get_or_create<sol::table>();
        state["obe"]["graphics"].get_or_create<sol::table>();
        state["obe"]["input"].get_or_create<sol::table>();
        state["obe"]["network"].get_or_create<sol::table>();
        state["obe"]["scene"].get_or_create<sol::table>();
        state["obe"]["script"].get_or_create<sol::table>();
        state["obe"]["system"].get_or_create<sol::table>();
        state["obe"]["tiles"].get_or_create<sol::table>();
        state["obe"]["time"].get_or_create<sol::table>();
        state["obe"]["transform"].get_or_create<sol::table>();
        state["obe"]["utils"].get_or_create<sol::table>();
        state["vili"]["parser"].get_or_create<sol::table>();
        state["vili"]["writer"].get_or_create<sol::table>();
        state["obe"]["debug"].get_or_create<sol::table>();
        state["obe"]["bindings"].get_or_create<sol::table>();
        state["obe"]["events"].get_or_create<sol::table>();
        state["vili"]["utils"].get_or_create<sol::table>();
        state["obe"]["Component"]["Exceptions"].get_or_create<sol::table>();
        state["obe"]["graphics"]["canvas"].get_or_create<sol::table>();
        state["obe"]["graphics"]["shapes"].get_or_create<sol::table>();
        state["obe"]["system"]["project"].get_or_create<sol::table>();
        state["obe"]["utils"]["exec"].get_or_create<sol::table>();
        state["obe"]["events"]["Actions"].get_or_create<sol::table>();
        state["obe"]["events"]["Cursor"].get_or_create<sol::table>();
        state["obe"]["events"]["Game"].get_or_create<sol::table>();
        state["obe"]["events"]["Keys"].get_or_create<sol::table>();
        state["obe"]["events"]["Network"].get_or_create<sol::table>();
        state["obe"]["events"]["Scene"].get_or_create<sol::table>();
        state["obe"]["graphics"]["utils"].get_or_create<sol::table>();
        state["vili"]["parser"]["rules"].get_or_create<sol::table>();
        state["obe"]["animation"]["easing"].get_or_create<sol::table>();
        state["obe"]["config"]["validators"].get_or_create<sol::table>();
        state["obe"]["debug"]["render"].get_or_create<sol::table>();
        state["obe"]["script"]["Helpers"].get_or_create<sol::table>();
        state["obe"]["script"]["vili_lua_bridge"].get_or_create<sol::table>();
        state["obe"]["system"]["package"].get_or_create<sol::table>();
        state["obe"]["utils"]["file"].get_or_create<sol::table>();
        state["obe"]["utils"]["math"].get_or_create<sol::table>();
        state["obe"]["utils"]["string"].get_or_create<sol::table>();
        state["obe"]["utils"]["vector"].get_or_create<sol::table>();
        state["vili"]["utils"]["string"].get_or_create<sol::table>();
        state["obe"]["animation"]["schemas"].get_or_create<sol::table>();
        state["obe"]["system"]["constraints"].get_or_create<sol::table>();
        state["obe"]["system"]["prefixes"].get_or_create<sol::table>();
        state["obe"]["system"]["priorities"].get_or_create<sol::table>();
        state["obe"]["system"]["project"]["Prefixes"].get_or_create<sol::table>();

        obe::system::bindings::load_class_mountable_path(state);
        obe::system::bindings::load_class_find_result(state);
        obe::system::bindings::load_class_path(state);
        obe::bindings::load_class_base_exception(state);
        obe::bindings::load_class_debug_info(state);
        obe::bindings::load_function_get_type_name(state);
        obe::bindings::load_function_init_engine(state);
        obe::Component::bindings::load_class_component_base(state);
        obe::Component::Exceptions::bindings::load_class_component_id_already_taken(state);
        obe::Component::Exceptions::bindings::load_class_unknown_component_type(state);
        obe::types::bindings::load_class_identifiable(state);
        obe::types::bindings::load_class_protected_identifiable(state);
        obe::types::bindings::load_class_selectable(state);
        obe::types::bindings::load_class_serializable(state);
        obe::types::bindings::load_class_togglable(state);
        obe::types::bindings::load_class_unknown_enum_entry(state);
        obe::animation::bindings::load_class_animation(state);
        obe::animation::bindings::load_class_animation_group(state);
        obe::animation::bindings::load_class_animation_state(state);
        obe::animation::bindings::load_class_animator(state);
        obe::animation::bindings::load_class_animator_state(state);
        obe::animation::bindings::load_class_color_tweening(state);
        obe::animation::bindings::load_class_unit_vector_tweening(state);
        obe::animation::bindings::load_class_rect_tweening(state);
        obe::animation::bindings::load_class_trajectory_tweening(state);
        obe::animation::bindings::load_class_int_tweening(state);
        obe::animation::bindings::load_class_double_tweening(state);
        obe::animation::bindings::load_enum_animation_play_mode(state);
        obe::animation::bindings::load_enum_animation_command(state);
        obe::animation::bindings::load_enum_animation_status(state);
        obe::animation::bindings::load_enum_animator_target_scale_mode(state);
        obe::animation::bindings::load_function_template_specialization_exists_impl(state);
        obe::animation::bindings::load_function_tween(state);
        obe::audio::bindings::load_class_audio_manager(state);
        obe::audio::bindings::load_class_sound(state);
        obe::audio::bindings::load_enum_load_policy(state);
        obe::audio::bindings::load_enum_sound_status(state);
        obe::collision::bindings::load_class_collision_data(state);
        obe::collision::bindings::load_class_polygonal_collider(state);
        obe::collision::bindings::load_class_trajectory(state);
        obe::collision::bindings::load_class_trajectory_node(state);
        obe::collision::bindings::load_enum_collider_tag_type(state);
        obe::config::bindings::load_class_configuration_manager(state);
        obe::config::bindings::load_class_version(state);
        obe::engine::bindings::load_class_engine(state);
        obe::engine::bindings::load_class_resource_managed_object(state);
        obe::engine::bindings::load_class_resource_manager(state);
        obe::event::bindings::load_class_callback_scheduler(state);
        obe::event::bindings::load_class_event_base(state);
        obe::event::bindings::load_class_event_group(state);
        obe::event::bindings::load_class_event_group_view(state);
        obe::event::bindings::load_class_event_manager(state);
        obe::event::bindings::load_class_event_namespace(state);
        obe::event::bindings::load_class_event_namespace_view(state);
        obe::event::bindings::load_class_lua_event_listener(state);
        obe::event::bindings::load_enum_callback_scheduler_state(state);
        obe::event::bindings::load_enum_listener_change_state(state);
        obe::graphics::bindings::load_class_color(state);
        obe::graphics::bindings::load_class_editor_sprite(state);
        obe::graphics::bindings::load_class_font(state);
        obe::graphics::bindings::load_class_position_transformer(state);
        obe::graphics::bindings::load_class_render_target(state);
        obe::graphics::bindings::load_class_renderable(state);
        obe::graphics::bindings::load_class_rich_text(state);
        obe::graphics::bindings::load_class_shader(state);
        obe::graphics::bindings::load_class_sprite(state);
        obe::graphics::bindings::load_class_sprite_handle_point(state);
        obe::graphics::bindings::load_class_svg_texture(state);
        obe::graphics::bindings::load_class_text(state);
        obe::graphics::bindings::load_class_texture(state);
        obe::graphics::bindings::load_class_hsv(state);
        obe::graphics::bindings::load_enum_color_type(state);
        obe::graphics::bindings::load_enum_sprite_handle_point_type(state);
        obe::graphics::bindings::load_function_init_position_transformers(state);
        obe::graphics::bindings::load_function_make_null_texture(state);
        obe::graphics::bindings::load_global_transformers(state);
        obe::graphics::bindings::load_global_parallax(state);
        obe::graphics::bindings::load_global_camera(state);
        obe::graphics::bindings::load_global_position(state);
        obe::graphics::canvas::bindings::load_class_bezier(state);
        obe::graphics::canvas::bindings::load_class_canvas(state);
        obe::graphics::canvas::bindings::load_class_canvas_element(state);
        obe::graphics::canvas::bindings::load_class_canvas_positionable(state);
        obe::graphics::canvas::bindings::load_class_circle(state);
        obe::graphics::canvas::bindings::load_class_line(state);
        obe::graphics::canvas::bindings::load_class_polygon(state);
        obe::graphics::canvas::bindings::load_class_rectangle(state);
        obe::graphics::canvas::bindings::load_class_text(state);
        obe::graphics::canvas::bindings::load_enum_canvas_element_type(state);
        obe::graphics::canvas::bindings::load_enum_text_horizontal_align(state);
        obe::graphics::canvas::bindings::load_enum_text_vertical_align(state);
        obe::graphics::shapes::bindings::load_class_circle(state);
        obe::graphics::shapes::bindings::load_class_polygon(state);
        obe::graphics::shapes::bindings::load_class_rectangle(state);
        obe::graphics::shapes::bindings::load_class_text(state);
        obe::input::bindings::load_class_input_action(state);
        obe::input::bindings::load_class_input_button(state);
        obe::input::bindings::load_class_input_button_monitor(state);
        obe::input::bindings::load_class_input_condition(state);
        obe::input::bindings::load_class_input_manager(state);
        obe::input::bindings::load_enum_mouse_wheel_scroll_direction(state);
        obe::input::bindings::load_enum_axis_threshold_direction(state);
        obe::input::bindings::load_enum_input_button_state(state);
        obe::input::bindings::load_enum_input_type(state);
        obe::network::bindings::load_class_lua_packet(state);
        obe::network::bindings::load_class_network_handler(state);
        obe::network::bindings::load_class_tcp_server(state);
        obe::network::bindings::load_class_tcp_socket(state);
        obe::scene::bindings::load_class_camera(state);
        obe::scene::bindings::load_class_scene(state);
        obe::scene::bindings::load_class_scene_node(state);
        obe::scene::bindings::load_class_scene_render_options(state);
        obe::script::bindings::load_class_game_object(state);
        obe::script::bindings::load_class_game_object_database(state);
        obe::script::bindings::load_class_lua_state(state);
        obe::script::bindings::load_enum_environment_target(state);
        obe::script::bindings::load_function_sol_call_status_to_string(state);
        obe::script::bindings::load_function_safe_lua_call(state);
        obe::system::bindings::load_class_contextual_path_factory(state);
        obe::system::bindings::load_class_cursor(state);
        obe::system::bindings::load_class_cursor_model(state);
        obe::system::bindings::load_class_plugin(state);
        obe::system::bindings::load_class_window(state);
        obe::system::bindings::load_enum_cursor_type(state);
        obe::system::bindings::load_enum_mountable_path_type(state);
        obe::system::bindings::load_enum_same_prefix_policy(state);
        obe::system::bindings::load_enum_path_type(state);
        obe::system::bindings::load_enum_window_context(state);
        obe::system::bindings::load_enum_stretch_mode(state);
        obe::system::bindings::load_enum_window_size(state);
        obe::system::bindings::load_enum_render_size(state);
        obe::system::bindings::load_function_split_path_and_prefix(state);
        obe::system::project::bindings::load_class_project(state);
        obe::system::project::bindings::load_class_project_ur_ls(state);
        obe::system::project::bindings::load_function_get_project_location(state);
        obe::system::project::bindings::load_function_project_exists(state);
        obe::system::project::bindings::load_function_load(state);
        obe::system::project::bindings::load_function_list_projects(state);
        obe::tiles::bindings::load_class_animated_tile(state);
        obe::tiles::bindings::load_class_tile_layer(state);
        obe::tiles::bindings::load_class_tile_scene(state);
        obe::tiles::bindings::load_class_tileset(state);
        obe::tiles::bindings::load_class_tileset_collection(state);
        obe::tiles::bindings::load_class_texture_quads_index(state);
        obe::tiles::bindings::load_class_tile_info(state);
        obe::tiles::bindings::load_function_get_tile_info(state);
        obe::tiles::bindings::load_function_strip_tile_flags(state);
        obe::tiles::bindings::load_function_apply_texture_quads_transforms(state);
        obe::time::bindings::load_class_chronometer(state);
        obe::time::bindings::load_class_framerate_counter(state);
        obe::time::bindings::load_class_framerate_manager(state);
        obe::time::bindings::load_function_epoch(state);
        obe::time::bindings::load_global_seconds(state);
        obe::time::bindings::load_global_milliseconds(state);
        obe::time::bindings::load_global_microseconds(state);
        obe::time::bindings::load_global_minutes(state);
        obe::time::bindings::load_global_hours(state);
        obe::time::bindings::load_global_days(state);
        obe::time::bindings::load_global_weeks(state);
        obe::transform::bindings::load_class_matrix2_d(state);
        obe::transform::bindings::load_class_movable(state);
        obe::transform::bindings::load_class_polygon(state);
        obe::transform::bindings::load_class_polygon_point(state);
        obe::transform::bindings::load_class_polygon_segment(state);
        obe::transform::bindings::load_class_rect(state);
        obe::transform::bindings::load_class_referential(state);
        obe::transform::bindings::load_class_unit_based_object(state);
        obe::transform::bindings::load_class_unit_vector(state);
        obe::transform::bindings::load_class_screen_struct(state);
        obe::transform::bindings::load_class_view_struct(state);
        obe::transform::bindings::load_enum_referential_conversion_type(state);
        obe::transform::bindings::load_enum_flip_axis(state);
        obe::transform::bindings::load_enum_units(state);
        obe::transform::bindings::load_enum_relative_position_from(state);
        obe::utils::exec::bindings::load_class_run_args_parser(state);
        vili::bindings::load_class_const_node_iterator(state);
        vili::bindings::load_class_node(state);
        vili::bindings::load_class_node_iterator(state);
        vili::bindings::load_enum_node_type(state);
        vili::bindings::load_function_from_string(state);
        vili::bindings::load_function_to_string(state);
        vili::bindings::load_global_permissive_cast(state);
        vili::bindings::load_global_verbose_exceptions(state);
        vili::bindings::load_global_true_value(state);
        vili::bindings::load_global_false_value(state);
        vili::bindings::load_global_null_typename(state);
        vili::bindings::load_global_boolean_typename(state);
        vili::bindings::load_global_integer_typename(state);
        vili::bindings::load_global_number_typename(state);
        vili::bindings::load_global_string_typename(state);
        vili::bindings::load_global_object_typename(state);
        vili::bindings::load_global_array_typename(state);
        vili::bindings::load_global_unknown_typename(state);
        vili::bindings::load_global_container_typename(state);
        vili::parser::bindings::load_class_node_in_stack(state);
        vili::parser::bindings::load_class_state(state);
        vili::parser::bindings::load_function_from_string(state);
        vili::parser::bindings::load_function_from_file(state);
        obe::events::Actions::bindings::load_class_action(state);
        obe::events::Cursor::bindings::load_class_hold(state);
        obe::events::Cursor::bindings::load_class_move(state);
        obe::events::Cursor::bindings::load_class_press(state);
        obe::events::Cursor::bindings::load_class_release(state);
        obe::events::Game::bindings::load_class_end(state);
        obe::events::Game::bindings::load_class_render(state);
        obe::events::Game::bindings::load_class_start(state);
        obe::events::Game::bindings::load_class_update(state);
        obe::events::Keys::bindings::load_class_state_changed(state);
        obe::events::Network::bindings::load_class_connected(state);
        obe::events::Network::bindings::load_class_data_received(state);
        obe::events::Network::bindings::load_class_disconnected(state);
        obe::events::Scene::bindings::load_class_loaded(state);
        obe::graphics::utils::bindings::load_class_draw_polygon_options(state);
        obe::graphics::utils::bindings::load_function_draw_point(state);
        obe::graphics::utils::bindings::load_function_draw_line(state);
        obe::graphics::utils::bindings::load_function_draw_polygon(state);
        vili::parser::rules::bindings::load_class_affectation(state);
        vili::parser::rules::bindings::load_class_affectation_separator(state);
        vili::parser::rules::bindings::load_class_array(state);
        vili::parser::rules::bindings::load_class_array_elements(state);
        vili::parser::rules::bindings::load_class_array_separator(state);
        vili::parser::rules::bindings::load_class_block(state);
        vili::parser::rules::bindings::load_class_boolean(state);
        vili::parser::rules::bindings::load_class_brace_based_object(state);
        vili::parser::rules::bindings::load_class_char_(state);
        vili::parser::rules::bindings::load_class_close_array(state);
        vili::parser::rules::bindings::load_class_close_object(state);
        vili::parser::rules::bindings::load_class_comment(state);
        vili::parser::rules::bindings::load_class_data(state);
        vili::parser::rules::bindings::load_class_digits(state);
        vili::parser::rules::bindings::load_class_element(state);
        vili::parser::rules::bindings::load_class_empty_line(state);
        vili::parser::rules::bindings::load_class_endline(state);
        vili::parser::rules::bindings::load_class_escaped(state);
        vili::parser::rules::bindings::load_class_escaped_char(state);
        vili::parser::rules::bindings::load_class_false_(state);
        vili::parser::rules::bindings::load_class_floating_point(state);
        vili::parser::rules::bindings::load_class_full_node(state);
        vili::parser::rules::bindings::load_class_grammar(state);
        vili::parser::rules::bindings::load_class_identifier(state);
        vili::parser::rules::bindings::load_class_indent(state);
        vili::parser::rules::bindings::load_class_indent_based_object(state);
        vili::parser::rules::bindings::load_class_inline_comment(state);
        vili::parser::rules::bindings::load_class_inline_element(state);
        vili::parser::rules::bindings::load_class_inline_node(state);
        vili::parser::rules::bindings::load_class_integer(state);
        vili::parser::rules::bindings::load_class_multiline_comment(state);
        vili::parser::rules::bindings::load_class_multiline_comment_block(state);
        vili::parser::rules::bindings::load_class_node(state);
        vili::parser::rules::bindings::load_class_number(state);
        vili::parser::rules::bindings::load_class_object(state);
        vili::parser::rules::bindings::load_class_object_elements(state);
        vili::parser::rules::bindings::load_class_object_separator(state);
        vili::parser::rules::bindings::load_class_open_array(state);
        vili::parser::rules::bindings::load_class_open_object(state);
        vili::parser::rules::bindings::load_class_sign(state);
        vili::parser::rules::bindings::load_class_space_or_comment(state);
        vili::parser::rules::bindings::load_class_string(state);
        vili::parser::rules::bindings::load_class_string_content(state);
        vili::parser::rules::bindings::load_class_string_delimiter(state);
        vili::parser::rules::bindings::load_class_true_(state);
        vili::parser::rules::bindings::load_class_unescaped(state);
        vili::parser::rules::bindings::load_class_unicode(state);
        vili::parser::rules::bindings::load_class_vili_grammar(state);
        vili::parser::rules::bindings::load_class_xdigit(state);
        vili::writer::bindings::load_class_dump_options(state);
        vili::writer::bindings::load_class__array(state);
        vili::writer::bindings::load_class__items_per_line(state);
        vili::writer::bindings::load_class__object(state);
        vili::writer::bindings::load_class_dump_state(state);
        vili::writer::bindings::load_enum_delimiter_newline_policy(state);
        vili::writer::bindings::load_enum_object_style(state);
        vili::writer::bindings::load_function_dump_integer(state);
        vili::writer::bindings::load_function_dump_number(state);
        vili::writer::bindings::load_function_dump_boolean(state);
        vili::writer::bindings::load_function_dump_string(state);
        vili::writer::bindings::load_function_dump_array(state);
        vili::writer::bindings::load_function_dump_object(state);
        vili::writer::bindings::load_function_dump(state);
        obe::animation::easing::bindings::load_enum_easing_type(state);
        obe::animation::easing::bindings::load_function_linear(state);
        obe::animation::easing::bindings::load_function_in_sine(state);
        obe::animation::easing::bindings::load_function_out_sine(state);
        obe::animation::easing::bindings::load_function_in_out_sine(state);
        obe::animation::easing::bindings::load_function_in_quad(state);
        obe::animation::easing::bindings::load_function_out_quad(state);
        obe::animation::easing::bindings::load_function_in_out_quad(state);
        obe::animation::easing::bindings::load_function_in_cubic(state);
        obe::animation::easing::bindings::load_function_out_cubic(state);
        obe::animation::easing::bindings::load_function_in_out_cubic(state);
        obe::animation::easing::bindings::load_function_in_quart(state);
        obe::animation::easing::bindings::load_function_out_quart(state);
        obe::animation::easing::bindings::load_function_in_out_quart(state);
        obe::animation::easing::bindings::load_function_in_quint(state);
        obe::animation::easing::bindings::load_function_out_quint(state);
        obe::animation::easing::bindings::load_function_in_out_quint(state);
        obe::animation::easing::bindings::load_function_in_expo(state);
        obe::animation::easing::bindings::load_function_out_expo(state);
        obe::animation::easing::bindings::load_function_in_out_expo(state);
        obe::animation::easing::bindings::load_function_in_circ(state);
        obe::animation::easing::bindings::load_function_out_circ(state);
        obe::animation::easing::bindings::load_function_in_out_circ(state);
        obe::animation::easing::bindings::load_function_in_back(state);
        obe::animation::easing::bindings::load_function_out_back(state);
        obe::animation::easing::bindings::load_function_in_out_back(state);
        obe::animation::easing::bindings::load_function_in_elastic(state);
        obe::animation::easing::bindings::load_function_out_elastic(state);
        obe::animation::easing::bindings::load_function_in_out_elastic(state);
        obe::animation::easing::bindings::load_function_in_bounce(state);
        obe::animation::easing::bindings::load_function_out_bounce(state);
        obe::animation::easing::bindings::load_function_in_out_bounce(state);
        obe::animation::easing::bindings::load_function_get(state);
        obe::debug::bindings::load_enum_log_level(state);
        obe::debug::bindings::load_function_init_logger(state);
        obe::debug::bindings::load_function_trace(state);
        obe::debug::bindings::load_function_debug(state);
        obe::debug::bindings::load_function_info(state);
        obe::debug::bindings::load_function_warn(state);
        obe::debug::bindings::load_function_error(state);
        obe::debug::bindings::load_function_critical(state);
        obe::debug::bindings::load_global_log(state);
        obe::bindings::bindings::load_function_index_core_bindings(state);
        obe::config::validators::bindings::load_function_animation_validator(state);
        obe::config::validators::bindings::load_function_config_validator(state);
        obe::config::validators::bindings::load_function_mount_validator(state);
        obe::config::validators::bindings::load_function_project_validator(state);
        obe::debug::render::bindings::load_function_draw_polygon(state);
        obe::script::Helpers::bindings::load_function_make_all_helpers(state);
        obe::script::Helpers::bindings::load_function_fetch_from_one_of(state);
        obe::script::Helpers::bindings::load_function_rawget_from(state);
        obe::script::Helpers::bindings::load_function_len_from(state);
        obe::script::Helpers::bindings::load_function_pairs_from(state);
        obe::script::vili_lua_bridge::bindings::load_function_vili_to_lua(state);
        obe::script::vili_lua_bridge::bindings::load_function_lua_to_vili(state);
        obe::script::vili_lua_bridge::bindings::load_function_vili_object_to_lua_table(state);
        obe::script::vili_lua_bridge::bindings::load_function_vili_primitive_to_lua_value(state);
        obe::script::vili_lua_bridge::bindings::load_function_vili_array_to_lua_table(state);
        obe::script::vili_lua_bridge::bindings::load_function_lua_table_to_vili_object(state);
        obe::script::vili_lua_bridge::bindings::load_function_lua_value_to_vili_primitive(state);
        obe::script::vili_lua_bridge::bindings::load_function_lua_table_to_vili_array(state);
        obe::system::package::bindings::load_function_get_package_location(state);
        obe::system::package::bindings::load_function_package_exists(state);
        obe::system::package::bindings::load_function_list_packages(state);
        obe::system::package::bindings::load_function_install(state);
        obe::system::package::bindings::load_function_load(state);
        obe::utils::file::bindings::load_function_get_directory_list(state);
        obe::utils::file::bindings::load_function_get_file_list(state);
        obe::utils::file::bindings::load_function_file_exists(state);
        obe::utils::file::bindings::load_function_directory_exists(state);
        obe::utils::file::bindings::load_function_create_directory(state);
        obe::utils::file::bindings::load_function_create_file(state);
        obe::utils::file::bindings::load_function_copy(state);
        obe::utils::file::bindings::load_function_delete_file(state);
        obe::utils::file::bindings::load_function_delete_directory(state);
        obe::utils::file::bindings::load_function_get_current_directory(state);
        obe::utils::file::bindings::load_function_separator(state);
        obe::utils::file::bindings::load_function_get_executable_directory(state);
        obe::utils::file::bindings::load_function_get_executable_path(state);
        obe::utils::file::bindings::load_function_normalize_path(state);
        obe::utils::file::bindings::load_function_canonical_path(state);
        obe::utils::file::bindings::load_function_join(state);
        obe::utils::math::bindings::load_function_randint(state);
        obe::utils::math::bindings::load_function_randfloat(state);
        obe::utils::math::bindings::load_function_get_min(state);
        obe::utils::math::bindings::load_function_get_max(state);
        obe::utils::math::bindings::load_function_is_between(state);
        obe::utils::math::bindings::load_function_is_double_int(state);
        obe::utils::math::bindings::load_function_sign(state);
        obe::utils::math::bindings::load_function_convert_to_radian(state);
        obe::utils::math::bindings::load_function_convert_to_degrees(state);
        obe::utils::math::bindings::load_function_normalize(state);
        obe::utils::math::bindings::load_global_pi(state);
        obe::utils::string::bindings::load_function_split(state);
        obe::utils::string::bindings::load_function_occurences_in_string(state);
        obe::utils::string::bindings::load_function_is_string_alpha(state);
        obe::utils::string::bindings::load_function_is_string_alpha_numeric(state);
        obe::utils::string::bindings::load_function_is_string_numeric(state);
        obe::utils::string::bindings::load_function_is_string_int(state);
        obe::utils::string::bindings::load_function_is_string_float(state);
        obe::utils::string::bindings::load_function_replace(state);
        obe::utils::string::bindings::load_function_is_surrounded_by(state);
        obe::utils::string::bindings::load_function_get_random_key(state);
        obe::utils::string::bindings::load_function_contains(state);
        obe::utils::string::bindings::load_function_starts_with(state);
        obe::utils::string::bindings::load_function_ends_with(state);
        obe::utils::string::bindings::load_function_distance(state);
        obe::utils::string::bindings::load_function_sort_by_distance(state);
        obe::utils::string::bindings::load_function_quote(state);
        obe::utils::string::bindings::load_function_titleize(state);
        obe::utils::string::bindings::load_global_alphabet(state);
        obe::utils::string::bindings::load_global_numbers(state);
        obe::utils::vector::bindings::load_function_contains(state);
        obe::utils::vector::bindings::load_function_join(state);
        vili::utils::string::bindings::load_function_replace(state);
        vili::utils::string::bindings::load_function_is_int(state);
        vili::utils::string::bindings::load_function_is_float(state);
        vili::utils::string::bindings::load_function_truncate_float(state);
        vili::utils::string::bindings::load_function_quote(state);
        vili::utils::string::bindings::load_function_to_double(state);
        vili::utils::string::bindings::load_function_to_long(state);
        vili::utils::string::bindings::load_function_indent(state);
        vili::utils::string::bindings::load_function_distance(state);
        vili::utils::string::bindings::load_function_sort_by_distance(state);
        obe::animation::schemas::bindings::load_global_animation_schema_str(state);
        obe::animation::schemas::bindings::load_global_animation_schema(state);
        obe::system::constraints::bindings::load_global_default(state);
        obe::system::prefixes::bindings::load_global_obe(state);
        obe::system::prefixes::bindings::load_global_cwd(state);
        obe::system::prefixes::bindings::load_global_exe(state);
        obe::system::prefixes::bindings::load_global_cfg(state);
        obe::system::prefixes::bindings::load_global_mount(state);
        obe::system::prefixes::bindings::load_global_extlibs(state);
        obe::system::prefixes::bindings::load_global_root(state);
        obe::system::prefixes::bindings::load_global_game(state);
        obe::system::priorities::bindings::load_global_high(state);
        obe::system::priorities::bindings::load_global_projectmount(state);
        obe::system::priorities::bindings::load_global_project(state);
        obe::system::priorities::bindings::load_global_mount(state);
        obe::system::priorities::bindings::load_global_defaults(state);
        obe::system::priorities::bindings::load_global_low(state);
        obe::system::project::Prefixes::bindings::load_global_objects(state);
        obe::system::project::Prefixes::bindings::load_global_scenes(state);
    }
}