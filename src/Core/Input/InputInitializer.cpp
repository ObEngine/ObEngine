#include <thread>

#include <Input/InputManager.hpp>
#include <Input/InputSourceGamepad.hpp>
#include <Input/InputSourceKeyboard.hpp>
#include <Input/InputSourceMouse.hpp>

namespace obe::input
{
    void InputManager::create_input_map()
    {
        // Gamepad
        std::thread gamepad_loader_thr([this]() { this->initialize_gamepads(); });

        // Letters
        m_inputs["A"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::A, "A");
        m_inputs["Z"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Z, "Z");
        m_inputs["E"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::E, "E");
        m_inputs["R"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::R, "E");
        m_inputs["T"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::T, "T");
        m_inputs["Y"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Y, "Y");
        m_inputs["U"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::U, "U");
        m_inputs["I"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::I, "I");
        m_inputs["O"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::O, "O");
        m_inputs["P"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::P, "P");
        m_inputs["Q"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Q, "Q");
        m_inputs["S"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::S, "S");
        m_inputs["D"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::D, "D");
        m_inputs["F"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::F, "F");
        m_inputs["G"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::G, "G");
        m_inputs["H"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::H, "H");
        m_inputs["J"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::J, "J");
        m_inputs["K"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::K, "K");
        m_inputs["L"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::L, "L");
        m_inputs["M"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::M, "M");
        m_inputs["W"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::W, "W");
        m_inputs["X"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::X, "W");
        m_inputs["C"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::C, "C");
        m_inputs["V"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::V, "V");
        m_inputs["B"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::B, "B");
        m_inputs["N"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::N, "N");

        // Numeric
        m_inputs["0"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Num0, "0");
        m_inputs["1"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Num1, "1");
        m_inputs["2"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Num2, "2");
        m_inputs["3"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Num3, "3");
        m_inputs["4"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Num4, "4");
        m_inputs["5"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Num5, "5");
        m_inputs["6"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Num6, "6");
        m_inputs["7"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Num7, "7");
        m_inputs["8"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Num8, "8");
        m_inputs["9"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Num9, "9");

        // Numeric pad
        m_inputs["NumPad0"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Numpad0, "0");
        m_inputs["NumPad1"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Numpad1, "1");
        m_inputs["NumPad2"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Numpad2, "2");
        m_inputs["NumPad3"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Numpad3, "3");
        m_inputs["NumPad4"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Numpad4, "4");
        m_inputs["NumPad5"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Numpad5, "5");
        m_inputs["NumPad6"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Numpad6, "6");
        m_inputs["NumPad7"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Numpad7, "7");
        m_inputs["NumPad8"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Numpad8, "8");
        m_inputs["NumPad9"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Numpad9, "9");

        // Arrows
        m_inputs["Left"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Left, "");
        m_inputs["Right"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Right, "");
        m_inputs["Up"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Up, "");
        m_inputs["Down"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Down, "");

        // Functions
        m_inputs["F1"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::F1, "");
        m_inputs["F2"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::F2, "");
        m_inputs["F3"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::F3, "");
        m_inputs["F4"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::F4, "");
        m_inputs["F5"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::F5, "");
        m_inputs["F6"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::F6, "");
        m_inputs["F7"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::F7, "");
        m_inputs["F8"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::F8, "");
        m_inputs["F9"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::F9, "");
        m_inputs["F10"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::F10, "");
        m_inputs["F11"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::F11, "");
        m_inputs["F12"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::F12, "");

        // Mouse
        m_inputs["MouseButtonLeft"] = std::make_unique<InputSourceMouseButton>(sf::Mouse::Left);
        m_inputs["MouseButtonRight"] = std::make_unique<InputSourceMouseButton>(sf::Mouse::Right);
        m_inputs["MouseButtonMiddle"] = std::make_unique<InputSourceMouseButton>(sf::Mouse::Middle);
        m_inputs["MouseButtonXButton1"] = std::make_unique<InputSourceMouseButton>(sf::Mouse::XButton1);
        m_inputs["MouseButtonXButton2"] = std::make_unique<InputSourceMouseButton>(sf::Mouse::XButton2);

        // Scroll Wheel
        m_inputs["MouseWheelScrollLeft"] = std::make_unique<InputSourceMouseWheelScroll>(
            input::MouseWheelScrollDirection::Left);
        m_inputs["MouseWheelScrollRight"]
            = std::make_unique<InputSourceMouseWheelScroll>(
            input::MouseWheelScrollDirection::Right);
        m_inputs["MouseWheelScrollUp"] = std::make_unique<InputSourceMouseWheelScroll>(
            input::MouseWheelScrollDirection::Up);
        m_inputs["MouseWheelScrollDown"] = std::make_unique<InputSourceMouseWheelScroll>(
            input::MouseWheelScrollDirection::Down);

        // Others
        m_inputs["Add"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Add, "+");
        m_inputs["Backslash"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::BackSlash, "\\");
        m_inputs["Backspace"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::BackSpace, "");
        m_inputs["Comma"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Comma, ",");
        m_inputs["Dash"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Dash, "-");
        m_inputs["Delete"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Delete, "");
        m_inputs["Divide"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Divide, "/");
        m_inputs["End"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::End, "");
        m_inputs["Equal"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Equal, "=");
        m_inputs["Escape"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Escape, "");
        m_inputs["Home"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Home, "");
        m_inputs["Insert"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Insert, "");
        m_inputs["LAlt"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::LAlt, "");
        m_inputs["LBracket"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::LBracket, "[");
        m_inputs["LControl"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::LControl, "");
        m_inputs["LShift"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::LShift, "");
        m_inputs["Menu"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Menu, "");
        m_inputs["Multiply"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Multiply, "*");
        m_inputs["PageDown"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::PageDown, "");
        m_inputs["PageUp"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::PageUp, "");
        m_inputs["Pause"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Pause, "");
        m_inputs["Period"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Period, ".");
        m_inputs["Quote"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Quote, "");
        m_inputs["RAlt"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::RAlt, "");
        m_inputs["RBracket"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::RBracket, "]");
        m_inputs["RControl"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::RControl, "");
        m_inputs["Return"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Return, "");
        m_inputs["RShift"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::RShift, "");
        m_inputs["RSystem"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::RSystem, "");
        m_inputs["Semicolon"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::SemiColon, ";");
        m_inputs["Slash"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Slash, "/");
        m_inputs["Space"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Space, " ");
        m_inputs["Subtract"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Subtract, "-");
        m_inputs["Tab"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Tab, "    ");
        m_inputs["Tilde"] = std::make_unique<InputSourceKeyboardKey>(sf::Keyboard::Tilde, "~");
        gamepad_loader_thr.join();
    }

    void InputManager::initialize_gamepad(unsigned int gamepad_index)
    {
        const auto gamepad_info = sf::Joystick::getIdentification(gamepad_index);
        debug::Log->debug("[InputManager] Initializing Gamepad {} : {}", gamepad_index,
            gamepad_info.name.toAnsiString());
        bool use_every_axis = true;
        unsigned int button_count = sf::Joystick::ButtonCount;
        if (sf::Joystick::isConnected(gamepad_index))
        {
            use_every_axis = false;
            button_count = sf::Joystick::getButtonCount(gamepad_index);
        }

        auto set_or_reset_button = [this] (const std::string& name, const InputSourceGamepadButton& button) {
            if (!m_inputs.contains(name))
            {
                m_inputs[name] = std::make_unique<InputSourceGamepadButton>(button);
            }
            else
            {
                *m_inputs.at(name) = button;
            }
        };
        auto set_or_reset_axis
            = [this](const std::string& name, const InputSourceGamepadAxis& axis)
        {
            if (!m_inputs.contains(name))
            {
                m_inputs[name] = std::make_unique<InputSourceGamepadAxis>(axis);
            }
            else
            {
                *m_inputs.at(name) = axis;
            }
        };

        for (unsigned int button_index = 0; button_index < button_count; button_index++)
        {
            std::string gamepad_button_name
                = "GP_" + std::to_string(gamepad_index) + "_BTN_" + std::to_string(button_index);
            set_or_reset_button(gamepad_button_name,
                InputSourceGamepadButton(gamepad_index, button_index, gamepad_button_name));
        }

        auto add_horizontal_axis
            = [&gamepad_index, use_every_axis, set_or_reset_axis, this](
                                       sf::Joystick::Axis axis, const std::string& axis_name,
                                       bool invert_axis = false) {
            if (use_every_axis || sf::Joystick::hasAxis(gamepad_index, axis))
            {
                const std::string gamepad_axis_name
                    = "GP_" + std::to_string(gamepad_index) + "_AXIS_" + axis_name;
                std::pair<AxisThresholdDirection, float> left_x(AxisThresholdDirection::Less, -80);
                std::pair<AxisThresholdDirection, float> right_x(AxisThresholdDirection::More, 80);
                const std::string left_axis_name
                    = (!invert_axis) ? gamepad_axis_name + "_LEFT" : gamepad_axis_name + "_RIGHT";
                const std::string right_axis_name
                    = (!invert_axis) ? gamepad_axis_name + "_RIGHT" : gamepad_axis_name + "_LEFT";
                set_or_reset_axis(
                    left_axis_name, InputSourceGamepadAxis(gamepad_index, axis, left_x, left_axis_name));
                set_or_reset_axis(
                    right_axis_name, InputSourceGamepadAxis(gamepad_index, axis, right_x, right_axis_name));
            }
        };
        auto add_vertical_axis
            = [&gamepad_index, use_every_axis, set_or_reset_axis, this](
                                     sf::Joystick::Axis axis, const std::string& axis_name,
                                     bool invert_axis = false) {
            if (use_every_axis || sf::Joystick::hasAxis(gamepad_index, axis))
            {
                const std::string gamepad_axis_name
                    = "GP_" + std::to_string(gamepad_index) + "_AXIS_" + axis_name;
                std::pair<AxisThresholdDirection, float> up_y(AxisThresholdDirection::Less, -80);
                std::pair<AxisThresholdDirection, float> down_y(AxisThresholdDirection::More, 80);
                const std::string up_axis_name
                    = (!invert_axis) ? gamepad_axis_name + "_UP" : gamepad_axis_name + "_DOWN";
                const std::string down_axis_name
                    = (!invert_axis) ? gamepad_axis_name + "_DOWN" : gamepad_axis_name + "_UP";
                set_or_reset_axis(
                    up_axis_name, InputSourceGamepadAxis(gamepad_index, axis, up_y, up_axis_name));
                set_or_reset_axis(down_axis_name,
                    InputSourceGamepadAxis(gamepad_index, axis, down_y, down_axis_name));
            }
        };
        add_horizontal_axis(sf::Joystick::Axis::X, "X");
        add_vertical_axis(sf::Joystick::Axis::Y, "Y");
        add_horizontal_axis(sf::Joystick::Axis::PovX, "PovX");
        add_vertical_axis(sf::Joystick::Axis::PovY, "PovY", true);
        add_horizontal_axis(sf::Joystick::Axis::U, "U");
        add_vertical_axis(sf::Joystick::Axis::V, "V");
        add_vertical_axis(sf::Joystick::Axis::R, "R");
        add_horizontal_axis(sf::Joystick::Axis::Z, "Z", true);
    }

    void InputManager::initialize_gamepads()
    {
        // TODO: Improve this mechanism, we can't remove existing input due to orphan InputSource pointers
        /*auto cKey = m_inputs.begin();
        while (cKey != m_inputs.end())
        {
            if (cKey->first.rfind("GP_", 0) == 0)
                cKey = m_inputs.erase(cKey);
            else
                ++cKey;
        }*/
        sf::Joystick::update();
        for (int gamepad_index = 0; gamepad_index < sf::Joystick::Count; gamepad_index++)
        {
            if (sf::Joystick::isConnected(gamepad_index))
            {
                this->initialize_gamepad(gamepad_index);
            }
        }
        this->create_events();
    }

    void InputManager::create_events()
    {
        for (auto const& [key, val] : m_inputs)
        {
            input::InputSource* input_source = val.get();

            if (!e_inputs->contains(input_source->get_name()))
            {
                e_inputs->add<events::Keys::StateChanged>(input_source->get_name());
                e_inputs->on_add_listener(input_source->get_name(),
                    [input_source, this](event::ListenerChangeState, const std::string&)
                    { m_key_monitors.push_back(this->monitor(*input_source));
                    });
                e_inputs->on_remove_listener(input_source->get_name(),
                    [input_source, this](event::ListenerChangeState, const std::string&)
                    {
                        const auto position = std::find_if(m_key_monitors.begin(), m_key_monitors.end(),
                                [input_source](const auto& monitor)
                                { return &monitor->get_input_source() == input_source;
                            });
                        if (position != m_key_monitors.end())
                            m_key_monitors.erase(position);
                    });
            }
        }
    }

    std::vector<std::string> InputManager::get_all_input_button_names() const
    {
        std::vector<std::string> buttons_names;
        buttons_names.reserve(m_inputs.size());
        for (const auto& button : m_inputs)
        {
            buttons_names.push_back(button.second->get_name());
        }
        return buttons_names;
    }
} // namespace obe::input
