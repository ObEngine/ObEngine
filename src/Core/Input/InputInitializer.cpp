#include <thread>

#include <Input/InputManager.hpp>

namespace obe::Input
{
    void InputManager::createInputMap()
    {
        // Gamepad
        std::thread gamepadLoaderThr([this]() { this->initializeGamepads(); });

        // Letters
        m_inputs["A"] = std::make_unique<InputButton>(sf::Keyboard::A, "A", "A", InputType::Alpha);
        m_inputs["Z"] = std::make_unique<InputButton>(sf::Keyboard::Z, "Z", "Z", InputType::Alpha);
        m_inputs["E"] = std::make_unique<InputButton>(sf::Keyboard::E, "E", "E", InputType::Alpha);
        m_inputs["R"] = std::make_unique<InputButton>(sf::Keyboard::R, "R", "E", InputType::Alpha);
        m_inputs["T"] = std::make_unique<InputButton>(sf::Keyboard::T, "T", "T", InputType::Alpha);
        m_inputs["Y"] = std::make_unique<InputButton>(sf::Keyboard::Y, "Y", "Y", InputType::Alpha);
        m_inputs["U"] = std::make_unique<InputButton>(sf::Keyboard::U, "U", "U", InputType::Alpha);
        m_inputs["I"] = std::make_unique<InputButton>(sf::Keyboard::I, "I", "I", InputType::Alpha);
        m_inputs["O"] = std::make_unique<InputButton>(sf::Keyboard::O, "O", "O", InputType::Alpha);
        m_inputs["P"] = std::make_unique<InputButton>(sf::Keyboard::P, "P", "P", InputType::Alpha);
        m_inputs["Q"] = std::make_unique<InputButton>(sf::Keyboard::Q, "Q", "Q", InputType::Alpha);
        m_inputs["S"] = std::make_unique<InputButton>(sf::Keyboard::S, "S", "S", InputType::Alpha);
        m_inputs["D"] = std::make_unique<InputButton>(sf::Keyboard::D, "D", "D", InputType::Alpha);
        m_inputs["F"] = std::make_unique<InputButton>(sf::Keyboard::F, "F", "F", InputType::Alpha);
        m_inputs["G"] = std::make_unique<InputButton>(sf::Keyboard::G, "G", "G", InputType::Alpha);
        m_inputs["H"] = std::make_unique<InputButton>(sf::Keyboard::H, "H", "H", InputType::Alpha);
        m_inputs["J"] = std::make_unique<InputButton>(sf::Keyboard::J, "J", "J", InputType::Alpha);
        m_inputs["K"] = std::make_unique<InputButton>(sf::Keyboard::K, "K", "K", InputType::Alpha);
        m_inputs["L"] = std::make_unique<InputButton>(sf::Keyboard::L, "L", "L", InputType::Alpha);
        m_inputs["M"] = std::make_unique<InputButton>(sf::Keyboard::M, "M", "M", InputType::Alpha);
        m_inputs["W"] = std::make_unique<InputButton>(sf::Keyboard::W, "W", "W", InputType::Alpha);
        m_inputs["X"] = std::make_unique<InputButton>(sf::Keyboard::X, "X", "W", InputType::Alpha);
        m_inputs["C"] = std::make_unique<InputButton>(sf::Keyboard::C, "C", "C", InputType::Alpha);
        m_inputs["V"] = std::make_unique<InputButton>(sf::Keyboard::V, "V", "V", InputType::Alpha);
        m_inputs["B"] = std::make_unique<InputButton>(sf::Keyboard::B, "B", "B", InputType::Alpha);
        m_inputs["N"] = std::make_unique<InputButton>(sf::Keyboard::N, "N", "N", InputType::Alpha);

        // Numeric
        m_inputs["0"]
            = std::make_unique<InputButton>(sf::Keyboard::Num0, "0", "0", InputType::Numeric);
        m_inputs["1"]
            = std::make_unique<InputButton>(sf::Keyboard::Num1, "1", "1", InputType::Numeric);
        m_inputs["2"]
            = std::make_unique<InputButton>(sf::Keyboard::Num2, "2", "2", InputType::Numeric);
        m_inputs["3"]
            = std::make_unique<InputButton>(sf::Keyboard::Num3, "3", "3", InputType::Numeric);
        m_inputs["4"]
            = std::make_unique<InputButton>(sf::Keyboard::Num4, "4", "4", InputType::Numeric);
        m_inputs["5"]
            = std::make_unique<InputButton>(sf::Keyboard::Num5, "5", "5", InputType::Numeric);
        m_inputs["6"]
            = std::make_unique<InputButton>(sf::Keyboard::Num6, "6", "6", InputType::Numeric);
        m_inputs["7"]
            = std::make_unique<InputButton>(sf::Keyboard::Num7, "7", "7", InputType::Numeric);
        m_inputs["8"]
            = std::make_unique<InputButton>(sf::Keyboard::Num8, "8", "8", InputType::Numeric);
        m_inputs["9"]
            = std::make_unique<InputButton>(sf::Keyboard::Num9, "9", "9", InputType::Numeric);

        // Numeric pad
        m_inputs["NumPad0"] = std::make_unique<InputButton>(
            sf::Keyboard::Numpad0, "NumPad0", "0", InputType::NumericNP);
        m_inputs["NumPad1"] = std::make_unique<InputButton>(
            sf::Keyboard::Numpad1, "NumPad1", "1", InputType::NumericNP);
        m_inputs["NumPad2"] = std::make_unique<InputButton>(
            sf::Keyboard::Numpad2, "NumPad2", "2", InputType::NumericNP);
        m_inputs["NumPad3"] = std::make_unique<InputButton>(
            sf::Keyboard::Numpad3, "NumPad3", "3", InputType::NumericNP);
        m_inputs["NumPad4"] = std::make_unique<InputButton>(
            sf::Keyboard::Numpad4, "NumPad4", "4", InputType::NumericNP);
        m_inputs["NumPad5"] = std::make_unique<InputButton>(
            sf::Keyboard::Numpad5, "NumPad5", "5", InputType::NumericNP);
        m_inputs["NumPad6"] = std::make_unique<InputButton>(
            sf::Keyboard::Numpad6, "NumPad6", "6", InputType::NumericNP);
        m_inputs["NumPad7"] = std::make_unique<InputButton>(
            sf::Keyboard::Numpad7, "NumPad7", "7", InputType::NumericNP);
        m_inputs["NumPad8"] = std::make_unique<InputButton>(
            sf::Keyboard::Numpad8, "NumPad8", "8", InputType::NumericNP);
        m_inputs["NumPad9"] = std::make_unique<InputButton>(
            sf::Keyboard::Numpad9, "NumPad9", "9", InputType::NumericNP);

        // Arrows
        m_inputs["Left"]
            = std::make_unique<InputButton>(sf::Keyboard::Left, "Left", "", InputType::Arrows);
        m_inputs["Right"]
            = std::make_unique<InputButton>(sf::Keyboard::Right, "Right", "", InputType::Arrows);
        m_inputs["Up"]
            = std::make_unique<InputButton>(sf::Keyboard::Up, "Up", "", InputType::Arrows);
        m_inputs["Down"]
            = std::make_unique<InputButton>(sf::Keyboard::Down, "Down", "", InputType::Arrows);

        // Functions
        m_inputs["F1"]
            = std::make_unique<InputButton>(sf::Keyboard::F1, "F1", "", InputType::Functions);
        m_inputs["F2"]
            = std::make_unique<InputButton>(sf::Keyboard::F2, "F2", "", InputType::Functions);
        m_inputs["F3"]
            = std::make_unique<InputButton>(sf::Keyboard::F3, "F3", "", InputType::Functions);
        m_inputs["F4"]
            = std::make_unique<InputButton>(sf::Keyboard::F4, "F4", "", InputType::Functions);
        m_inputs["F5"]
            = std::make_unique<InputButton>(sf::Keyboard::F5, "F5", "", InputType::Functions);
        m_inputs["F6"]
            = std::make_unique<InputButton>(sf::Keyboard::F6, "F6", "", InputType::Functions);
        m_inputs["F7"]
            = std::make_unique<InputButton>(sf::Keyboard::F7, "F7", "", InputType::Functions);
        m_inputs["F8"]
            = std::make_unique<InputButton>(sf::Keyboard::F8, "F8", "", InputType::Functions);
        m_inputs["F9"]
            = std::make_unique<InputButton>(sf::Keyboard::F9, "F9", "", InputType::Functions);
        m_inputs["F10"]
            = std::make_unique<InputButton>(sf::Keyboard::F10, "F10", "", InputType::Functions);
        m_inputs["F11"]
            = std::make_unique<InputButton>(sf::Keyboard::F11, "F11", "", InputType::Functions);
        m_inputs["F12"]
            = std::make_unique<InputButton>(sf::Keyboard::F12, "F12", "", InputType::Functions);

        // Mouse
        m_inputs["LMB"] = std::make_unique<InputButton>(sf::Mouse::Left, "LMB");
        m_inputs["RMB"] = std::make_unique<InputButton>(sf::Mouse::Right, "RMB");
        m_inputs["MMB"] = std::make_unique<InputButton>(sf::Mouse::Middle, "MMB");

        // Scroll Wheel
        m_inputs["MouseWheelLeft"] = std::make_unique<InputButton>(
            Input::MouseWheelScrollDirection::Left, "MouseWheelLeft");
        m_inputs["MouseWheelRight"] = std::make_unique<InputButton>(
            Input::MouseWheelScrollDirection::Left, "MouseWheelRight");
        m_inputs["MouseWheelUp"]
            = std::make_unique<InputButton>(Input::MouseWheelScrollDirection::Left, "MouseWheelUp");
        m_inputs["MouseWheelDown"] = std::make_unique<InputButton>(
            Input::MouseWheelScrollDirection::Left, "MouseWheelDown");

        // Others
        m_inputs["Add"]
            = std::make_unique<InputButton>(sf::Keyboard::Add, "Add", "+", InputType::Others);
        m_inputs["Backslash"] = std::make_unique<InputButton>(
            sf::Keyboard::BackSlash, "Backslash", "\\", InputType::Others);
        m_inputs["Backspace"] = std::make_unique<InputButton>(
            sf::Keyboard::BackSpace, "Backspace", "", InputType::Others);
        m_inputs["Comma"]
            = std::make_unique<InputButton>(sf::Keyboard::Comma, "Comma", ",", InputType::Others);
        m_inputs["Dash"]
            = std::make_unique<InputButton>(sf::Keyboard::Dash, "Dash", "-", InputType::Others);
        m_inputs["Delete"]
            = std::make_unique<InputButton>(sf::Keyboard::Delete, "Delete", "", InputType::Others);
        m_inputs["Divide"]
            = std::make_unique<InputButton>(sf::Keyboard::Divide, "Divide", "/", InputType::Others);
        m_inputs["End"]
            = std::make_unique<InputButton>(sf::Keyboard::End, "End", "", InputType::Others);
        m_inputs["Equal"]
            = std::make_unique<InputButton>(sf::Keyboard::Equal, "Equal", "=", InputType::Others);
        m_inputs["Escape"]
            = std::make_unique<InputButton>(sf::Keyboard::Escape, "Escape", "", InputType::Others);
        m_inputs["Home"]
            = std::make_unique<InputButton>(sf::Keyboard::Home, "Home", "", InputType::Others);
        m_inputs["Insert"]
            = std::make_unique<InputButton>(sf::Keyboard::Insert, "Insert", "", InputType::Others);
        m_inputs["LAlt"]
            = std::make_unique<InputButton>(sf::Keyboard::LAlt, "LAlt", "", InputType::Others);
        m_inputs["LBracket"] = std::make_unique<InputButton>(
            sf::Keyboard::LBracket, "LBracket", "[", InputType::Others);
        m_inputs["LControl"] = std::make_unique<InputButton>(
            sf::Keyboard::LControl, "LControl", "", InputType::Others);
        m_inputs["LShift"]
            = std::make_unique<InputButton>(sf::Keyboard::LShift, "LShift", "", InputType::Others);
        m_inputs["Menu"]
            = std::make_unique<InputButton>(sf::Keyboard::Menu, "Menu", "", InputType::Others);
        m_inputs["Multiply"] = std::make_unique<InputButton>(
            sf::Keyboard::Multiply, "Multiply", "*", InputType::Others);
        m_inputs["PageDown"] = std::make_unique<InputButton>(
            sf::Keyboard::PageDown, "PageDown", "", InputType::Others);
        m_inputs["PageUp"]
            = std::make_unique<InputButton>(sf::Keyboard::PageUp, "PageUp", "", InputType::Others);
        m_inputs["Pause"]
            = std::make_unique<InputButton>(sf::Keyboard::Pause, "Pause", "", InputType::Others);
        m_inputs["Period"]
            = std::make_unique<InputButton>(sf::Keyboard::Period, "Period", ".", InputType::Others);
        m_inputs["Quote"]
            = std::make_unique<InputButton>(sf::Keyboard::Quote, "Quote", "\"", InputType::Others);
        m_inputs["RAlt"]
            = std::make_unique<InputButton>(sf::Keyboard::RAlt, "RAlt", "", InputType::Others);
        m_inputs["RBracket"] = std::make_unique<InputButton>(
            sf::Keyboard::RBracket, "RBracket", "]", InputType::Others);
        m_inputs["RControl"] = std::make_unique<InputButton>(
            sf::Keyboard::RControl, "RControl", "", InputType::Others);
        m_inputs["Return"]
            = std::make_unique<InputButton>(sf::Keyboard::Return, "Return", "", InputType::Others);
        m_inputs["RShift"]
            = std::make_unique<InputButton>(sf::Keyboard::RShift, "RShift", "", InputType::Others);
        m_inputs["RSystem"] = std::make_unique<InputButton>(
            sf::Keyboard::RSystem, "RSystem", "", InputType::Others);
        m_inputs["Semicolon"] = std::make_unique<InputButton>(
            sf::Keyboard::SemiColon, "Semicolon", ";", InputType::Others);
        m_inputs["Slash"]
            = std::make_unique<InputButton>(sf::Keyboard::Slash, "Slash", "/", InputType::Others);
        m_inputs["Space"]
            = std::make_unique<InputButton>(sf::Keyboard::Space, "Space", " ", InputType::Others);
        m_inputs["Subtract"] = std::make_unique<InputButton>(
            sf::Keyboard::Subtract, "Subtract", "-", InputType::Others);
        m_inputs["Tab"]
            = std::make_unique<InputButton>(sf::Keyboard::Tab, "Tab", "    ", InputType::Others);
        m_inputs["Tilde"]
            = std::make_unique<InputButton>(sf::Keyboard::Tilde, "Tilde", "~", InputType::Others);
        gamepadLoaderThr.join();
    }

    void InputManager::initializeGamepad(unsigned int gamepadIndex)
    {
        auto gamepadInfo = sf::Joystick::getIdentification(gamepadIndex);
        Debug::Log->debug("[InputManager] Initializing Gamepad {} : {}", gamepadIndex,
            gamepadInfo.name.toAnsiString());
        bool useEveryAxis = true;
        unsigned int buttonCount = sf::Joystick::ButtonCount;
        if (sf::Joystick::isConnected(gamepadIndex))
        {
            useEveryAxis = false;
            buttonCount = sf::Joystick::getButtonCount(gamepadIndex);
        }

        auto setOrResetButton = [this](const std::string& name, const InputButton& button)
        {
            if (m_inputs.find(name) == m_inputs.end())
            {
                m_inputs[name] = std::make_unique<InputButton>(button);
            }
            else
            {
                m_inputs.at(name)->reload(button);
            }
        };

        for (unsigned int buttonIndex = 0; buttonIndex < buttonCount; buttonIndex++)
        {
            std::string gamepadButtonName
                = "GP_" + std::to_string(gamepadIndex) + "_BTN_" + std::to_string(buttonIndex);
            setOrResetButton(
                gamepadButtonName, InputButton(gamepadIndex, buttonIndex, gamepadButtonName));
        }

        auto addHorizontalAxis
            = [&gamepadIndex, useEveryAxis, setOrResetButton, this](
                  sf::Joystick::Axis axis, const std::string& axisName, bool invertAxis = false)
        {
            if (useEveryAxis || sf::Joystick::hasAxis(gamepadIndex, axis))
            {
                const std::string gamepadAxisName
                    = "GP_" + std::to_string(gamepadIndex) + "_AXIS_" + axisName;
                std::pair<AxisThresholdDirection, float> leftX(AxisThresholdDirection::Less, -80);
                std::pair<AxisThresholdDirection, float> rightX(AxisThresholdDirection::More, 80);
                std::string leftAxisName
                    = (!invertAxis) ? gamepadAxisName + "_LEFT" : gamepadAxisName + "_RIGHT";
                std::string rightAxisName
                    = (!invertAxis) ? gamepadAxisName + "_RIGHT" : gamepadAxisName + "_LEFT";
                setOrResetButton(
                    leftAxisName, InputButton(gamepadIndex, axis, leftX, leftAxisName));
                setOrResetButton(
                    rightAxisName, InputButton(gamepadIndex, axis, rightX, rightAxisName));
            }
        };
        auto addVerticalAxis
            = [&gamepadIndex, useEveryAxis, setOrResetButton, this](
                  sf::Joystick::Axis axis, const std::string& axisName, bool invertAxis = false)
        {
            if (useEveryAxis || sf::Joystick::hasAxis(gamepadIndex, axis))
            {
                const std::string gamepadAxisName
                    = "GP_" + std::to_string(gamepadIndex) + "_AXIS_" + axisName;
                std::pair<AxisThresholdDirection, float> upY(AxisThresholdDirection::Less, -80);
                std::pair<AxisThresholdDirection, float> downY(AxisThresholdDirection::More, 80);
                std::string upAxisName
                    = (!invertAxis) ? gamepadAxisName + "_UP" : gamepadAxisName + "_DOWN";
                std::string downAxisName
                    = (!invertAxis) ? gamepadAxisName + "_DOWN" : gamepadAxisName + "_UP";
                setOrResetButton(upAxisName, InputButton(gamepadIndex, axis, upY, upAxisName));
                setOrResetButton(
                    downAxisName, InputButton(gamepadIndex, axis, downY, downAxisName));
            }
        };
        addHorizontalAxis(sf::Joystick::Axis::X, "X");
        addVerticalAxis(sf::Joystick::Axis::Y, "Y");
        addHorizontalAxis(sf::Joystick::Axis::PovX, "PovX");
        addVerticalAxis(sf::Joystick::Axis::PovY, "PovY", true);
        addHorizontalAxis(sf::Joystick::Axis::U, "U");
        addVerticalAxis(sf::Joystick::Axis::V, "V");
        addVerticalAxis(sf::Joystick::Axis::R, "R");
        addHorizontalAxis(sf::Joystick::Axis::Z, "Z", true);
    }

    void InputManager::initializeGamepads()
    {
        // TODO: Improve this mechanism, we can't remove existing input due to orphan InputButton pointers
        /*auto cKey = m_inputs.begin();
        while (cKey != m_inputs.end())
        {
            if (cKey->first.rfind("GP_", 0) == 0)
                cKey = m_inputs.erase(cKey);
            else
                ++cKey;
        }*/
        sf::Joystick::update();
        for (int gamepadIndex = 0; gamepadIndex < sf::Joystick::Count; gamepadIndex++)
        {
            if (sf::Joystick::isConnected(gamepadIndex))
            {
                this->initializeGamepad(gamepadIndex);
            }
        }
        this->createEvents();
    }

    void InputManager::createEvents()
    {
        for (auto const& [key, val] : m_inputs)
        {
            Input::InputButton* button = val.get();

            if (!e_inputs->contains(button->getName()))
            {
                e_inputs->add<Events::Keys::StateChanged>(button->getName());
                e_inputs->onAddListener(button->getName(),
                    [button, this](Event::ListenerChangeState, const std::string&)
                    { m_key_monitors.push_back(this->monitor(*button)); });
                e_inputs->onRemoveListener(button->getName(),
                    [button, this](Event::ListenerChangeState, const std::string&)
                    {
                        const auto position
                            = std::find_if(m_key_monitors.begin(), m_key_monitors.end(),
                                [button](const auto& monitor)
                                { return &monitor->getButton() == button; });
                        if (position != m_key_monitors.end())
                            m_key_monitors.erase(position);
                    });
            }
        }
    }

    std::vector<std::string> InputManager::getAllInputButtonNames() const
    {
        std::vector<std::string> buttonsNames;
        buttonsNames.reserve(m_inputs.size());
        for (const auto& button : m_inputs)
        {
            buttonsNames.push_back(button.second->getName());
        }
        return buttonsNames;
    }
} // namespace obe::Input
