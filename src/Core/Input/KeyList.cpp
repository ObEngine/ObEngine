#include <vili/ErrorHandler.hpp>

#include <Input/KeyList.hpp>
#include <SFML/Window/Joystick.hpp>

namespace obe::Input
{
    std::unordered_map<std::string, std::unique_ptr<InputButton>> AllKeys;

    void InitKeyList()
    {
        AllKeys["A"] = std::make_unique<InputButton>(sf::Keyboard::A, "A", "A", InputType::Alpha);
        AllKeys["Z"] = std::make_unique<InputButton>(sf::Keyboard::Z, "Z", "Z", InputType::Alpha);
        AllKeys["E"] = std::make_unique<InputButton>(sf::Keyboard::E, "E", "E", InputType::Alpha);
        AllKeys["R"] = std::make_unique<InputButton>(sf::Keyboard::R, "R", "E", InputType::Alpha);
        AllKeys["T"] = std::make_unique<InputButton>(sf::Keyboard::T, "T", "T", InputType::Alpha);
        AllKeys["Y"] = std::make_unique<InputButton>(sf::Keyboard::Y, "Y", "Y", InputType::Alpha);
        AllKeys["U"] = std::make_unique<InputButton>(sf::Keyboard::U, "U", "U", InputType::Alpha);
        AllKeys["I"] = std::make_unique<InputButton>(sf::Keyboard::I, "I", "I", InputType::Alpha);
        AllKeys["O"] = std::make_unique<InputButton>(sf::Keyboard::O, "O", "O", InputType::Alpha);
        AllKeys["P"] = std::make_unique<InputButton>(sf::Keyboard::P, "P", "P", InputType::Alpha);
        AllKeys["Q"] = std::make_unique<InputButton>(sf::Keyboard::Q, "Q", "Q", InputType::Alpha);
        AllKeys["S"] = std::make_unique<InputButton>(sf::Keyboard::S, "S", "S", InputType::Alpha);
        AllKeys["D"] = std::make_unique<InputButton>(sf::Keyboard::D, "D", "D", InputType::Alpha);
        AllKeys["F"] = std::make_unique<InputButton>(sf::Keyboard::F, "F", "F", InputType::Alpha);
        AllKeys["G"] = std::make_unique<InputButton>(sf::Keyboard::G, "G", "G", InputType::Alpha);
        AllKeys["H"] = std::make_unique<InputButton>(sf::Keyboard::H, "H", "H", InputType::Alpha);
        AllKeys["J"] = std::make_unique<InputButton>(sf::Keyboard::J, "J", "J", InputType::Alpha);
        AllKeys["K"] = std::make_unique<InputButton>(sf::Keyboard::K, "K", "K", InputType::Alpha);
        AllKeys["L"] = std::make_unique<InputButton>(sf::Keyboard::L, "L", "L", InputType::Alpha);
        AllKeys["M"] = std::make_unique<InputButton>(sf::Keyboard::M, "M", "M", InputType::Alpha);
        AllKeys["W"] = std::make_unique<InputButton>(sf::Keyboard::W, "W", "W", InputType::Alpha);
        AllKeys["X"] = std::make_unique<InputButton>(sf::Keyboard::X, "X", "W", InputType::Alpha);
        AllKeys["C"] = std::make_unique<InputButton>(sf::Keyboard::C, "C", "C", InputType::Alpha);
        AllKeys["V"] = std::make_unique<InputButton>(sf::Keyboard::V, "V", "V", InputType::Alpha);
        AllKeys["B"] = std::make_unique<InputButton>(sf::Keyboard::B, "B", "B", InputType::Alpha);
        AllKeys["N"] = std::make_unique<InputButton>(sf::Keyboard::N, "N", "N", InputType::Alpha);
        // Numeric
        AllKeys["0"]
            = std::make_unique<InputButton>(sf::Keyboard::Num0, "0", "0", InputType::Numeric);
        AllKeys["1"]
            = std::make_unique<InputButton>(sf::Keyboard::Num1, "1", "1", InputType::Numeric);
        AllKeys["2"]
            = std::make_unique<InputButton>(sf::Keyboard::Num2, "2", "2", InputType::Numeric);
        AllKeys["3"]
            = std::make_unique<InputButton>(sf::Keyboard::Num3, "3", "3", InputType::Numeric);
        AllKeys["4"]
            = std::make_unique<InputButton>(sf::Keyboard::Num4, "4", "4", InputType::Numeric);
        AllKeys["5"]
            = std::make_unique<InputButton>(sf::Keyboard::Num5, "5", "5", InputType::Numeric);
        AllKeys["6"]
            = std::make_unique<InputButton>(sf::Keyboard::Num6, "6", "6", InputType::Numeric);
        AllKeys["7"]
            = std::make_unique<InputButton>(sf::Keyboard::Num7, "7", "7", InputType::Numeric);
        AllKeys["8"]
            = std::make_unique<InputButton>(sf::Keyboard::Num8, "8", "8", InputType::Numeric);
        AllKeys["9"]
            = std::make_unique<InputButton>(sf::Keyboard::Num9, "9", "9", InputType::Numeric);
        // Numpad
        AllKeys["NumPad0"] = std::make_unique<InputButton>(
            sf::Keyboard::Numpad0, "NumPad0", "0", InputType::NumericNP);
        AllKeys["NumPad1"] = std::make_unique<InputButton>(
            sf::Keyboard::Numpad1, "NumPad1", "1", InputType::NumericNP);
        AllKeys["NumPad2"] = std::make_unique<InputButton>(
            sf::Keyboard::Numpad2, "NumPad2", "2", InputType::NumericNP);
        AllKeys["NumPad3"] = std::make_unique<InputButton>(
            sf::Keyboard::Numpad3, "NumPad3", "3", InputType::NumericNP);
        AllKeys["NumPad4"] = std::make_unique<InputButton>(
            sf::Keyboard::Numpad4, "NumPad4", "4", InputType::NumericNP);
        AllKeys["NumPad5"] = std::make_unique<InputButton>(
            sf::Keyboard::Numpad5, "NumPad5", "5", InputType::NumericNP);
        AllKeys["NumPad6"] = std::make_unique<InputButton>(
            sf::Keyboard::Numpad6, "NumPad6", "6", InputType::NumericNP);
        AllKeys["NumPad7"] = std::make_unique<InputButton>(
            sf::Keyboard::Numpad7, "NumPad7", "7", InputType::NumericNP);
        AllKeys["NumPad8"] = std::make_unique<InputButton>(
            sf::Keyboard::Numpad8, "NumPad8", "8", InputType::NumericNP);
        AllKeys["NumPad9"] = std::make_unique<InputButton>(
            sf::Keyboard::Numpad9, "NumPad9", "9", InputType::NumericNP);
        // Arrows
        AllKeys["Left"]
            = std::make_unique<InputButton>(sf::Keyboard::Left, "Left", "", InputType::Arrows);
        AllKeys["Right"]
            = std::make_unique<InputButton>(sf::Keyboard::Right, "Right", "", InputType::Arrows);
        AllKeys["Up"]
            = std::make_unique<InputButton>(sf::Keyboard::Up, "Up", "", InputType::Arrows);
        AllKeys["Down"]
            = std::make_unique<InputButton>(sf::Keyboard::Down, "Down", "", InputType::Arrows);
        // Functions
        AllKeys["F1"]
            = std::make_unique<InputButton>(sf::Keyboard::F1, "F1", "", InputType::Functions);
        AllKeys["F2"]
            = std::make_unique<InputButton>(sf::Keyboard::F2, "F2", "", InputType::Functions);
        AllKeys["F3"]
            = std::make_unique<InputButton>(sf::Keyboard::F3, "F3", "", InputType::Functions);
        AllKeys["F4"]
            = std::make_unique<InputButton>(sf::Keyboard::F4, "F4", "", InputType::Functions);
        AllKeys["F5"]
            = std::make_unique<InputButton>(sf::Keyboard::F5, "F5", "", InputType::Functions);
        AllKeys["F6"]
            = std::make_unique<InputButton>(sf::Keyboard::F6, "F6", "", InputType::Functions);
        AllKeys["F7"]
            = std::make_unique<InputButton>(sf::Keyboard::F7, "F7", "", InputType::Functions);
        AllKeys["F8"]
            = std::make_unique<InputButton>(sf::Keyboard::F8, "F8", "", InputType::Functions);
        AllKeys["F9"]
            = std::make_unique<InputButton>(sf::Keyboard::F9, "F9", "", InputType::Functions);
        AllKeys["F10"]
            = std::make_unique<InputButton>(sf::Keyboard::F10, "F10", "", InputType::Functions);
        AllKeys["F11"]
            = std::make_unique<InputButton>(sf::Keyboard::F11, "F11", "", InputType::Functions);
        AllKeys["F12"]
            = std::make_unique<InputButton>(sf::Keyboard::F12, "F12", "", InputType::Functions);
        // Gamepad
        SetGamepadList();
        // Mouse
        AllKeys["LMB"] = std::make_unique<InputButton>(sf::Mouse::Left, "LMB");
        AllKeys["RMB"] = std::make_unique<InputButton>(sf::Mouse::Right, "RMB");
        AllKeys["MMB"] = std::make_unique<InputButton>(sf::Mouse::Middle, "MMB");
        // Others
        AllKeys["Add"]
            = std::make_unique<InputButton>(sf::Keyboard::Add, "Add", "+", InputType::Others);
        AllKeys["Backslash"] = std::make_unique<InputButton>(
            sf::Keyboard::BackSlash, "Backslash", "\\", InputType::Others);
        AllKeys["Backspace"] = std::make_unique<InputButton>(
            sf::Keyboard::BackSpace, "Backspace", "", InputType::Others);
        AllKeys["Comma"]
            = std::make_unique<InputButton>(sf::Keyboard::Comma, "Comma", ",", InputType::Others);
        AllKeys["Dash"]
            = std::make_unique<InputButton>(sf::Keyboard::Dash, "Dash", "-", InputType::Others);
        AllKeys["Delete"]
            = std::make_unique<InputButton>(sf::Keyboard::Delete, "Delete", "", InputType::Others);
        AllKeys["Divide"]
            = std::make_unique<InputButton>(sf::Keyboard::Divide, "Divide", "/", InputType::Others);
        AllKeys["End"]
            = std::make_unique<InputButton>(sf::Keyboard::End, "End", "", InputType::Others);
        AllKeys["Equal"]
            = std::make_unique<InputButton>(sf::Keyboard::Equal, "Equal", "=", InputType::Others);
        AllKeys["Escape"]
            = std::make_unique<InputButton>(sf::Keyboard::Escape, "Escape", "", InputType::Others);
        AllKeys["Home"]
            = std::make_unique<InputButton>(sf::Keyboard::Home, "Home", "", InputType::Others);
        AllKeys["Insert"]
            = std::make_unique<InputButton>(sf::Keyboard::Insert, "Insert", "", InputType::Others);
        AllKeys["LAlt"]
            = std::make_unique<InputButton>(sf::Keyboard::LAlt, "LAlt", "", InputType::Others);
        AllKeys["LBracket"] = std::make_unique<InputButton>(
            sf::Keyboard::LBracket, "LBracket", "[", InputType::Others);
        AllKeys["LControl"] = std::make_unique<InputButton>(
            sf::Keyboard::LControl, "LControl", "", InputType::Others);
        AllKeys["LShift"]
            = std::make_unique<InputButton>(sf::Keyboard::LShift, "LShift", "", InputType::Others);
        AllKeys["Menu"]
            = std::make_unique<InputButton>(sf::Keyboard::Menu, "Menu", "", InputType::Others);
        AllKeys["Multiply"] = std::make_unique<InputButton>(
            sf::Keyboard::Multiply, "Multiply", "*", InputType::Others);
        AllKeys["PageDown"] = std::make_unique<InputButton>(
            sf::Keyboard::PageDown, "PageDown", "", InputType::Others);
        AllKeys["PageUp"]
            = std::make_unique<InputButton>(sf::Keyboard::PageUp, "PageUp", "", InputType::Others);
        AllKeys["Pause"]
            = std::make_unique<InputButton>(sf::Keyboard::Pause, "Pause", "", InputType::Others);
        AllKeys["Period"]
            = std::make_unique<InputButton>(sf::Keyboard::Period, "Period", ".", InputType::Others);
        AllKeys["Quote"]
            = std::make_unique<InputButton>(sf::Keyboard::Quote, "Quote", "\"", InputType::Others);
        AllKeys["RAlt"]
            = std::make_unique<InputButton>(sf::Keyboard::RAlt, "RAlt", "", InputType::Others);
        AllKeys["RBracket"] = std::make_unique<InputButton>(
            sf::Keyboard::RBracket, "RBracket", "]", InputType::Others);
        AllKeys["RControl"] = std::make_unique<InputButton>(
            sf::Keyboard::RControl, "RControl", "", InputType::Others);
        AllKeys["Return"]
            = std::make_unique<InputButton>(sf::Keyboard::Return, "Return", "", InputType::Others);
        AllKeys["RShift"]
            = std::make_unique<InputButton>(sf::Keyboard::RShift, "RShift", "", InputType::Others);
        AllKeys["RSystem"] = std::make_unique<InputButton>(
            sf::Keyboard::RSystem, "RSystem", "", InputType::Others);
        AllKeys["Semicolon"] = std::make_unique<InputButton>(
            sf::Keyboard::SemiColon, "Semicolon", ";", InputType::Others);
        AllKeys["Slash"]
            = std::make_unique<InputButton>(sf::Keyboard::Slash, "Slash", "/", InputType::Others);
        AllKeys["Space"]
            = std::make_unique<InputButton>(sf::Keyboard::Space, "Space", " ", InputType::Others);
        AllKeys["Substract"] = std::make_unique<InputButton>(
            sf::Keyboard::Subtract, "Substract", "-", InputType::Others);
        AllKeys["Tab"]
            = std::make_unique<InputButton>(sf::Keyboard::Tab, "Tab", "    ", InputType::Others);
        AllKeys["Tilde"]
            = std::make_unique<InputButton>(sf::Keyboard::Tilde, "Tilde", "~", InputType::Others);
    }

    void SetGamepadList()
    {
        auto cKey = AllKeys.begin();
        while (cKey != AllKeys.end())
        {
            if (cKey->first.rfind("GP_", 0) == 0)
                cKey = AllKeys.erase(cKey);
            else
                ++cKey;
        }
        sf::Joystick::update();
        for (int gamepadIndex = 0; gamepadIndex < sf::Joystick::Count; gamepadIndex++)
        {
            for (unsigned int buttonIndex = 0;
                 buttonIndex < sf::Joystick::getButtonCount(gamepadIndex); buttonIndex++)
            {
                std::string gamepadButtonName
                    = "GP_" + std::to_string(gamepadIndex) + "_BTN_" + std::to_string(buttonIndex);
                AllKeys[gamepadButtonName]
                    = std::make_unique<InputButton>(gamepadIndex, buttonIndex, gamepadButtonName);
            }
            auto addHorizontalAxis
                = [&gamepadIndex](sf::Joystick::Axis axis, const std::string& axisName) {
                      if (sf::Joystick::hasAxis(gamepadIndex, axis))
                      {
                          std::string gamepadAxisName
                              = "GP_" + std::to_string(gamepadIndex) + "_AXIS_" + axisName;
                          std::pair<AxisCompareType, float> leftX(AxisCompareType::LESS, -80);
                          std::pair<AxisCompareType, float> rightX(AxisCompareType::MORE, 80);
                          AllKeys[gamepadAxisName + "_LEFT"] = std::make_unique<InputButton>(
                              gamepadIndex, axis, leftX, gamepadAxisName + "_LEFT");
                          AllKeys[gamepadAxisName + "_RIGHT"] = std::make_unique<InputButton>(
                              gamepadIndex, axis, rightX, gamepadAxisName + "_RIGHT");
                      }
                  };
            auto addVerticalAxis
                = [&gamepadIndex](sf::Joystick::Axis axis, const std::string& axisName) {
                      if (sf::Joystick::hasAxis(gamepadIndex, axis))
                      {
                          std::string gamepadAxisName
                              = "GP_" + std::to_string(gamepadIndex) + "_AXIS_" + axisName;
                          std::pair<AxisCompareType, float> upY(AxisCompareType::LESS, -80);
                          std::pair<AxisCompareType, float> downY(AxisCompareType::MORE, 80);
                          AllKeys[gamepadAxisName + "_UP"] = std::make_unique<InputButton>(
                              gamepadIndex, axis, upY, gamepadAxisName + "_UP");
                          AllKeys[gamepadAxisName + "_DOWN"] = std::make_unique<InputButton>(
                              gamepadIndex, axis, downY, gamepadAxisName + "_DOWN");
                      }
                  };
            addHorizontalAxis(sf::Joystick::Axis::X, "X");
            addVerticalAxis(sf::Joystick::Axis::Y, "Y");
            addHorizontalAxis(sf::Joystick::Axis::PovX, "PovX");
            addVerticalAxis(sf::Joystick::Axis::PovY, "PovY");
            addHorizontalAxis(sf::Joystick::Axis::U, "U");
            addVerticalAxis(sf::Joystick::Axis::R, "R");
            if (sf::Joystick::hasAxis(gamepadIndex, sf::Joystick::Axis::Z))
            {
                const std::string gamepadAxisName
                    = "GP_" + std::to_string(gamepadIndex) + "_AXIS_Z";
                std::pair<AxisCompareType, float> leftT(AxisCompareType::MORE, 80);
                std::pair<AxisCompareType, float> rightT(AxisCompareType::LESS, -80);
                AllKeys[gamepadAxisName + "_LEFT"] = std::make_unique<InputButton>(
                    gamepadIndex, sf::Joystick::Axis::Z, leftT, gamepadAxisName + "_LEFT");
                AllKeys[gamepadAxisName + "_RIGHT"] = std::make_unique<InputButton>(
                    gamepadIndex, sf::Joystick::Axis::Z, rightT, gamepadAxisName + "_RIGHT");
            }
        }
    }

    InputButton* GetKey(const std::string& keyId)
    {
        if (AllKeys.find(keyId) != AllKeys.end())
            return AllKeys[keyId].get();
        throw aube::ErrorHandler::Raise(
            "ObEngine.Input.KeyList.UnknownButton", { { "button", keyId } });
    }

    std::vector<InputButton*> GetAllPressedButtons()
    {
        std::vector<InputButton*> allPressedButtons;
        for (auto& keyIterator : AllKeys)
        {
            if (keyIterator.second->isPressed())
            {
                allPressedButtons.push_back(keyIterator.second.get());
            }
        }
        return allPressedButtons;
    }
} // namespace obe::Input