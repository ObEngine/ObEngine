#include <kaguya/kaguya.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include <Modes/Toolkit.hpp>
#include <Script/Script.hpp>

namespace obe
{
    namespace Modes
    {
        void startToolkitMode()
        {
            bool continueToolkit = true;
            sf::RenderWindow window({636, 636}, "ObEngine Toolkit", sf::Style::None);
            sf::Color inputColor(255, 255, 255);

            tgui::Gui gui(window);
            gui.setFont("Data/Fonts/weblysleekuil.ttf");
            tgui::Theme baseTheme;
            baseTheme.load("Data/GUI/obe.style");
            std::string currentMap = "";

            tgui::Panel::Ptr mainPanel = tgui::Panel::create();
            tgui::ChatBox::Ptr content = tgui::ChatBox::create();
            tgui::Scrollbar::Ptr scrollbar = tgui::Scrollbar::create();
            tgui::Label::Ptr titleLabel = tgui::Label::create();
            tgui::Button::Ptr closeButton = tgui::Button::create();
            tgui::EditBox::Ptr toolkitInput = tgui::EditBox::create();

            gui.add(mainPanel, "mainPanel");

            mainPanel->setRenderer(baseTheme.getRenderer("Panel"));
            mainPanel->setSize(window.getSize().x, window.getSize().y);
            mainPanel->setPosition("0", "0");

            content->setRenderer(baseTheme.getRenderer("ChatBox"));
            content->setSize("&.width", "534");
            content->setPosition("0", "70");
            content->setLinesStartFromTop();
            mainPanel->add(content, "contentPanel");

            titleLabel->setRenderer(baseTheme.getRenderer("Label"));
            titleLabel->setText("ObEngine Toolkit");
            titleLabel->setTextSize(34);
            titleLabel->setPosition("10", "10");
            mainPanel->add(titleLabel);

            closeButton->setRenderer(baseTheme.getRenderer("CloseButton"));
            closeButton->setSize("32", "32");
            closeButton->setPosition("&.width - width - (&.&.width / 40)", "&.&.height / 40");
            closeButton->connect("pressed", [&window]()
                             {
                                 window.close();
                             });
            mainPanel->add(closeButton);

            toolkitInput->setRenderer(baseTheme.getRenderer("TextBox"));
            toolkitInput->setSize("&.width", "32");
            toolkitInput->setPosition("0", "&.height - height");
            mainPanel->add(toolkitInput);

            kaguya::State toolkitEngine;
            toolkitInput->connect("returnkeypressed", [&content, &toolkitInput, inputColor, &toolkitEngine]()
                              {
                                  content->addLine("> " + toolkitInput->getText(), inputColor);
                                  toolkitEngine["evaluate"](toolkitInput->getText().toAnsiString());
                                  toolkitInput->setText("");
                              });


            toolkitEngine["This"] = &toolkitEngine;
            toolkitEngine.dofile("Lib/GameLib/WScrInit.lua");
            Script::loadLib(&toolkitEngine, "Core.*");
            Script::loadBaseLib(&toolkitEngine);
            toolkitEngine["_term_set_input_color"] = kaguya::function([&inputColor](unsigned int r, unsigned int g, unsigned b)
            {
                inputColor.r = r;
                inputColor.g = g;
                inputColor.b = b;
            });
            toolkitEngine["_term_display"] = kaguya::function([&content](const std::string& string, unsigned int r, unsigned int g, unsigned int b)
            {
                content->addLine(string, sf::Color(r, g, b));
            });
            toolkitEngine["_term_clear"] = kaguya::function([&toolkitInput]()
            {
                toolkitInput->setText("");
            });
            toolkitEngine["_term_write"] = kaguya::function([&toolkitInput](const std::string& string)
            {
                toolkitInput->setText(toolkitInput->getText() + string);
            });
            toolkitEngine["_term_last"] = kaguya::function([&toolkitInput]()
            {
                toolkitInput->setCaretPosition(toolkitInput->getText().getSize());
            });
            toolkitEngine["_term_get"] = kaguya::function([&toolkitInput]() -> std::string
            {
                return toolkitInput->getText().toAnsiString();
            });
            toolkitEngine["_term_close"] = kaguya::function([&continueToolkit]()
            {
                continueToolkit = false;
            });
            toolkitEngine.dofile("Lib/Toolkit/Toolkit.lua");

            sf::Vector2i grabbedOffset;
            bool grabbedWindow = false;

            gui.focusWidget(toolkitInput);

            while (window.isOpen() && continueToolkit)
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tab)
                        toolkitEngine["autocomplete"](toolkitInput->getText().toAnsiString());
                    else if (event.type == sf::Event::MouseButtonPressed)
                    {
                        if (sf::Mouse::getPosition().y - window.getPosition().y < 70 && sf::Mouse::getPosition().x - window.getPosition().x < 580)
                        {
                            if (event.mouseButton.button == sf::Mouse::Left)
                            {
                                grabbedOffset = window.getPosition() - sf::Mouse::getPosition();
                                grabbedWindow = true;
                            }
                        }
                    }
                    else if (event.type == sf::Event::MouseButtonReleased)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                            grabbedWindow = false;
                    }
                    else if (event.type == sf::Event::MouseMoved)
                    {
                        if (grabbedWindow)
                            window.setPosition(sf::Mouse::getPosition() + grabbedOffset);
                    }
                    gui.handleEvent(event);
                }

                window.clear();
                gui.draw();
                window.display();
            }
        }
    }
}
