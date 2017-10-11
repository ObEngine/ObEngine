#include <SFML/Window/WindowStyle.hpp>
#include <vili/Vili.hpp>

#include <System/Path.hpp>
#include <System/Window.hpp>
#include <Transform/UnitVector.hpp>

namespace obe
{
    namespace System
    {
        sf::RenderWindow MainWindow;

        void InitWindow(WindowContext context)
        {
            vili::ViliParser windowConfig;
            std::reverse(Path::MountedPaths.begin(), Path::MountedPaths.end());
            Path("Data/window.cfg.vili").loadResource(&windowConfig, [](vili::ViliParser* obj, std::string path) -> int { obj->parseFile(path); return 0x002; });
            std::reverse(Path::MountedPaths.begin(), Path::MountedPaths.end());

            unsigned int width = 1280;
            unsigned int height = 720;

            vili::ComplexNode* wconf;
            if (context == WindowContext::GameWindow)
            {
                if (windowConfig->contains("Game"))
                    wconf = &windowConfig.at("Game");
                else
                    wconf = &windowConfig.root();
            }
            else if (context == WindowContext::EditorWindow)
            {
                if (windowConfig->contains("Editor"))
                    wconf = &windowConfig.at("Editor");
                else
                    wconf = &windowConfig.root();
            }

            if (wconf->getDataNode("width").getDataType() == vili::DataType::Int)
                width = wconf->getDataNode("width").get<int>();
            else if (wconf->getDataNode("width").getDataType() == vili::DataType::String)
            {
                if (wconf->getDataNode("width").get<std::string>() == "Fill")
                    width = Transform::UnitVector::Screen.w;
            }
            if (wconf->getDataNode("height").getDataType() == vili::DataType::Int)
                height = wconf->getDataNode("height").get<int>();
            else if (wconf->getDataNode("height").getDataType() == vili::DataType::String)
            {
                if (wconf->getDataNode("height").get<std::string>() == "Fill")
                {
                    height = Transform::UnitVector::Screen.h;
                }
            }

            auto wStyle = sf::Style::None;
            bool fullscreen = true;
            bool closeable = true;
            bool resizeable = true;
            bool titlebar = true;

            if (wconf->contains("fullscreen"))
                fullscreen = wconf->getDataNode("fullscreen").get<bool>();
            if (wconf->contains("closeable"))
                closeable = wconf->getDataNode("closeable").get<bool>();
            if (wconf->contains("resizeable"))
                resizeable = wconf->getDataNode("resizeable").get<bool>();
            if (wconf->contains("titlebar"))
                titlebar = wconf->getDataNode("titlebar").get<bool>();

            if (fullscreen)
                wStyle = sf::Style::Fullscreen;
            else
            {
                if (closeable)
                    wStyle |= sf::Style::Close;
                if (resizeable)
                    wStyle |= sf::Style::Resize;
                if (titlebar)
                    wStyle |= sf::Style::Titlebar;
            }

            std::string title = "ObEngine";
            if (wconf->contains("title"))
                title = wconf->getDataNode("title").get<std::string>();

            System::MainWindow.create(sf::VideoMode(width, height), title, wStyle);
            System::MainWindow.setKeyRepeatEnabled(false);
        }
    }
}