#include <TGUI/TGUI.hpp>
#include <sol/sol.hpp>

#include <iostream>

void login(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password)
{
    std::cout << "Username: " << username->getText() << std::endl;
    std::cout << "Password: " << password->getText() << std::endl;
}

void updateTextSize(tgui::GuiBase& gui)
{
    // Update the text size of all widgets in the gui, based on the current window height
    const float windowHeight = gui.getView().getRect().height;
    gui.setTextSize(static_cast<unsigned int>(0.07f * windowHeight)); // 7% of height
}

void loadWidgets(tgui::GuiBase& gui, sol::state_view state)
{
    // Specify an initial text size instead of using the default value
    updateTextSize(gui);

    // We want the text size to be updated when the window is resized
    gui.onViewChange([&gui] { updateTextSize(gui); });

    // Create the username edit box
    // Similar to the picture, we set a relative position and size
    // In case it isn't obvious, the default text is the text that is displayed when the edit box is empty

    state["gui"] = &gui;
    auto result = state.do_file("ui.lua");
    if (!result.valid())
    {
        auto lua_error = result.get<sol::error>();
        std::string error_str = lua_error.what();
        std::cerr << error_str << std::endl;
    }
    /*auto editBoxUsername = tgui::EditBox::create();
    editBoxUsername->setSize({ "66.67%", "12.5%" });
    editBoxUsername->setPosition({ "16.67%", "16.67%" });
    editBoxUsername->setDefaultText("Username");
    gui.add(editBoxUsername);*/

    // Create the password edit box
    // We copy the previous edit box here and keep the same size
    /*auto editBoxPassword = tgui::EditBox::copy(editBoxUsername);
    editBoxPassword->setPosition({ "16.67%", "41.6%" });
    editBoxPassword->setPasswordCharacter('*');
    editBoxPassword->setDefaultText("Password");
    gui.add(editBoxPassword);*/

    // Create the login button
    /*auto button = tgui::Button::create("Login");
    button->setSize({ "50%", "16.67%" });
    button->setPosition({ "25%", "70%" });
    gui.add(button);*/

    // Call the login function when the button is pressed and pass the edit boxes that we created as parameters
    // The "&" in front of "login" can be removed on newer compilers, but is kept here for compatibility with GCC < 8.
    //button->onPress(&login, editBoxUsername, editBoxPassword);
}

bool runExample(tgui::GuiBase& gui, sol::state_view state)
{
    try
    {
        loadWidgets(gui, state);
        return true;
    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
        return false;
    }
}

namespace obe::Bindings
{
    void IndexDevBindings(sol::state_view state);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "TGUI window");
    sol::state state;
    state.open_libraries(sol::lib::base, sol::lib::string, sol::lib::table,
        sol::lib::package, sol::lib::os, sol::lib::coroutine, sol::lib::math,
        sol::lib::count, sol::lib::debug, sol::lib::io, sol::lib::bit32);
    std::cout << "Loading dev bindings" << std::endl;
    obe::Bindings::IndexDevBindings(state);
    std::cout << "Starting UI" << std::endl;

    tgui::Gui gui(window);
    if (!runExample(gui, state))
        return EXIT_FAILURE;

    gui.mainLoop();
    return EXIT_SUCCESS;
}
