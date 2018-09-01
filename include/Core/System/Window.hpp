#pragma once

#include <string>

#include <SFML/Graphics/RenderWindow.hpp>

#include <Config.hpp>
#include <Types/Global.hpp>

namespace obe::System
{
    enum class WindowContext
    {
        GameWindow,
        EditorWindow
    };

    GLOBE(8, MainWindow, sf::RenderWindow);

    void InitWindow(WindowContext context);
    void setTitle(const std::string& title);
    void setSize(unsigned int width, unsigned int height);
}