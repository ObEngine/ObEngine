#include <cmath>

#include <Editor/MapEditorTools.hpp>
#include <Scene/Scene.hpp>
#include <Script/GameObject.hpp>
#include <Script/Script.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>
#include <Transform/UnitVector.hpp>
#include <Utils/StringUtils.hpp>

namespace obe
{
    namespace Editor
    {
        Thumbnailer* Thumbnailer::m_instance = nullptr;

        Thumbnailer::Thumbnailer()
        {
            System::Path("Data/Fonts/arial.ttf").loadResource(&m_font, System::Loaders::fontLoader);
            m_renderer.create(246, 246);
            System::Path("Sprites/Others/folder.png").loadResource(&m_folderTexture, System::Loaders::textureLoader);
        }

        sf::Texture* Thumbnailer::GetSpriteThumbnail(const std::string& path)
        {
            if (m_instance == nullptr)
                m_instance = new Thumbnailer();
            if (m_instance->m_cache.find(path) != m_instance->m_cache.end())
                return m_instance->m_cache[path];
            sf::Texture sprTexture;
            System::Path("Sprites/LevelSprites/" + path).loadResource(&sprTexture, System::Loaders::textureLoader);
            sf::Sprite sprite;
            sprite.setTexture(sprTexture);
            double texW = sprTexture.getSize().x;
            double texH = sprTexture.getSize().y;
            double scale = (texW >= texH) ? m_size / texW : m_size / texH;
            sprite.setScale(scale, scale);
            sprite.setPosition(sf::Vector2f((m_size / 2) - (sprite.getGlobalBounds().width / 2), (m_size / 2) - (sprite.getGlobalBounds().height / 2)));
            m_instance->m_renderer.clear(sf::Color(0, 0, 0, 0));
            sf::RectangleShape sprRec(sf::Vector2f(m_size, m_size));
            sprRec.setFillColor(sf::Color(100, 100, 100));
            sprRec.setPosition(0, 0);
            m_instance->m_renderer.draw(sprRec);
            m_instance->m_renderer.draw(sprite);
            sf::RectangleShape titleRec(sf::Vector2f(m_size, 20));
            titleRec.setPosition(0, 0);
            titleRec.setFillColor(sf::Color(0, 0, 0, 200));
            m_instance->m_renderer.draw(titleRec);
            sf::Text sprNameText;
            sprNameText.setFont(m_instance->m_font);
            std::vector<std::string> splittedPath = Utils::String::split(path, "/");
            sprNameText.setString(splittedPath[splittedPath.size() - 1]);
            sprNameText.setCharacterSize(16);
            sprNameText.setFillColor(sf::Color(255, 255, 255));
            m_instance->m_renderer.draw(sprNameText);
            m_instance->m_renderer.display();
            m_instance->m_cache[path] = new sf::Texture(m_instance->m_renderer.getTexture());
            return m_instance->m_cache[path];
        }

        sf::Texture* Thumbnailer::GetFolderThumbnail(const std::string& path)
        {
            if (m_instance == nullptr)
                m_instance = new Thumbnailer();
            if (m_instance->m_cache.find(path) != m_instance->m_cache.end())
                return m_instance->m_cache[path];
            sf::Sprite baseSpr;
            baseSpr.setTexture(m_instance->m_folderTexture);
            baseSpr.setPosition(0, 0);
            m_instance->m_renderer.clear(sf::Color(0, 0, 0, 0));
            m_instance->m_renderer.draw(baseSpr);
            sf::Text folderText;
            folderText.setFont(m_instance->m_font);
            folderText.setCharacterSize(16);
            std::vector<std::string> splittedPath = Utils::String::split(path, "/");
            folderText.setString(splittedPath[splittedPath.size() - 1]);
            folderText.setPosition(10, 45);
            m_instance->m_renderer.draw(folderText);
            m_instance->m_renderer.display();
            m_instance->m_cache[path] = new sf::Texture(m_instance->m_renderer.getTexture());
            return m_instance->m_cache[path];
        }

        void buildObjectTab(tgui::Panel::Ptr& objectTab, tgui::Panel::Ptr& requiresPanel, tgui::Theme& baseTheme)
        {
            std::vector<std::string> allGameObjects;
            System::Path("Data/GameObjects").loadResource(&allGameObjects, System::Loaders::dirPathLoader);
            const int btnSize = 256;
            const int btnOff = 10;
            const int xOff = 15;
            const int yOff = 40;
            for (int i = 0; i < allGameObjects.size(); i++)
            {
                std::string currentObjName = allGameObjects[i];
                int xpos = (i * (btnSize + btnOff));
                int ypos = floor((double)xpos / (double)(1920 - (btnSize + btnOff))) * (btnSize + btnOff) + yOff;
                while (xpos > (1920 - (btnSize + btnOff + xOff)))
                    xpos -= (1920 - (btnSize + btnOff + xOff));
                xpos = floor((double)xpos / (double)(btnSize + btnOff)) * (btnSize + btnOff);
                xpos += xOff;
                ypos += yOff;
                tgui::Button::Ptr currentObj = tgui::Button::create();
                currentObj->setRenderer(baseTheme.getRenderer("ObjectButton"));
                currentObj->setTextSize(18);
                currentObj->setText(currentObjName);
                currentObj->setPosition(xpos, ypos);
                currentObj->setSize(256, 256);
                objectTab->add(currentObj);
                currentObj->connect("pressed", [&requiresPanel, &baseTheme, currentObjName]()
                                {
                                    std::cout << "Trying to build : " << currentObjName << std::endl;
                                    buildRequiresObjectTab(requiresPanel, baseTheme, currentObjName);
                                });
            }
        }

        void buildRequiresObjectTab(tgui::Panel::Ptr& requiresPanel, tgui::Theme& baseTheme, std::string objName)
        {
            std::cout << "Call Require Creation for : " << objName << std::endl;
            vili::ComplexNode* requires = Script::GameObjectRequires::getInstance()->getRequiresForObjectType(objName);
            vili::ComplexNode& requireInput = requires->at("Input");
            std::cout << "Requires is : " << requires << std::endl;
            if (requires != nullptr)
            {
                std::cout << "Show Requires Panel !" << std::endl;
                requiresPanel->show();
                tgui::Panel::Ptr content = requiresPanel->get<tgui::Panel>("content");
                content->removeAllWidgets();

                tgui::Label::Ptr newObjectTitleLabel = tgui::Label::create();
                newObjectTitleLabel->setPosition(10, 10);
                newObjectTitleLabel->setTextSize(32);
                newObjectTitleLabel->setRenderer(baseTheme.getRenderer("Label"));
                newObjectTitleLabel->setText("<" + objName + "> Instance Creator");

                content->add(newObjectTitleLabel);

                int widgetVerticalPosition = 70;
                for (std::string& requireItem : requireInput.getAll(vili::NodeType::ComplexNode))
                {
                    std::cout << "Require item is : " << requireItem << std::endl;
                    std::cout << requires->contains(vili::NodeType::ComplexNode, "Color") << std::endl;

                    tgui::Label::Ptr currentRequirementLabel = tgui::Label::create();
                    currentRequirementLabel->setPosition(50, widgetVerticalPosition);
                    currentRequirementLabel->setTextSize(18);
                    currentRequirementLabel->setRenderer(baseTheme.getRenderer("Label"));
                    currentRequirementLabel->setText(requireItem);
                    content->add(currentRequirementLabel, requireItem + "_label");


                    if (requireInput.at(requireItem).contains(vili::NodeType::DataNode, "type"))
                    {
                        tgui::EditBox::Ptr currentRequirementInput = tgui::EditBox::create();
                        currentRequirementInput->setRenderer(baseTheme.getRenderer("TextBox"));
                        currentRequirementInput->setSize("&.width / 3", "32");
                        currentRequirementInput->setPosition(200, widgetVerticalPosition + 5);
                        content->add(currentRequirementInput, requireItem + "_input");
                    }
                    else if (requireInput.at(requireItem).contains(vili::NodeType::ArrayNode, "choices"))
                    {
                        tgui::ComboBox::Ptr currentRequirementList = tgui::ComboBox::create();
                        currentRequirementList->setSize(200, 32);
                        currentRequirementList->setPosition(200, widgetVerticalPosition);
                        currentRequirementList->setTextSize(20);
                        currentRequirementList->setItemsToDisplay(4);
                        currentRequirementList->setRenderer(baseTheme.getRenderer("ComboBox"));
                        content->add(currentRequirementList, requireItem + "_input");
                        for (int reqI = 0; reqI < requireInput.at(requireItem).getArrayNode("choices").size(); reqI++)
                            currentRequirementList->addItem(requireInput.at(requireItem).getArrayNode("choices").get(reqI).get<std::string>());
                        currentRequirementList->setSelectedItem(currentRequirementList->getItems()[0]);
                    }
                    widgetVerticalPosition += 50;
                }
                tgui::Button::Ptr createObjectButton = tgui::Button::create();

                createObjectButton->setPosition(10, "&.height - 60");
                createObjectButton->setSize("&.w - 20", 50);
                createObjectButton->setRenderer(baseTheme.getRenderer("Button"));
                createObjectButton->setText("Sprites");
                createObjectButton->setTextSize(22);
                createObjectButton->setText("Create Object");

                createObjectButton->connect("pressed", [objName]()
                                        {
                                            buildObjectThroughRequire(objName);
                                        });

                requiresPanel->add(createObjectButton);
            }
            else
            {
                std::string key = Utils::String::getRandomKey("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 8);
                Script::hookCore.getPointer("Scene")->as<Scene::Scene*>()->createGameObject(key, objName);
            }
        }

        void buildObjectThroughRequire(std::string objName)
        {
            /*vili::ComplexAttribute* requires = Script::GameObjectRequires::getInstance()->getRequiresForObjectType(objName);
            GUI::Container* gui = Script::hookCore.getPointer("GUI")->as<GUI::Container*>();
            Cursor::Cursor* cursor = Script::hookCore.getPointer("Cursor")->as<Cursor::Cursor*>();
            Scene::World* world = Script::hookCore.getPointer("World")->as<Scene::World*>();
            GUI::WidgetContainer* requireGUI = gui->getContainerByContainerName("Requires");
            std::string key = Utils::String::getRandomKey("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 8);
            Script::GameObject* newGameObject = world->createGameObject(key, objName);
                
            for (std::string& requireItem : requires->getAll(vili::Types::ComplexAttribute))
            {
                std::string requirementName = requires->getPath(requireItem)->getBaseAttribute("name")->get<std::string>();
                bool optionalRequirement = requires->getPath(requireItem)->contains(vili::Types::BaseAttribute, "optional");
                if (optionalRequirement)
                    optionalRequirement = requires->getPath(requireItem)->getBaseAttribute("optional")->get<bool>();
                if (objName + "_" + requireItem + "_Input" != "" || optionalRequirement)
                {
                    if (requires->getPath(requireItem)->contains(vili::Types::ListAttribute, "choices"))
                        newGameObject->sendRequireArgumentFromCPP(requirementName, GUI::Widget::getWidgetByID<GUI::Droplist>(objName + "_" + requireItem + "_Input")->getCurrentSelected());
                }
            }
            if (newGameObject->doesHaveCollider()) {
                std::cout << "Position of GO set !" << std::endl;
                //FIX CURSOR POS
            }
            else if (newGameObject->doesHaveLevelSprite()) {
                std::cout << "Position of GO::LS set !" << std::endl;
            }*/
        }

        void loadSpriteFolder(tgui::Panel::Ptr spritesPanel, tgui::Label::Ptr spritesCatLabel, std::string path)
        {
            spritesPanel->removeAllWidgets();
            spritesPanel->add(spritesCatLabel);

            std::vector<std::string> fileList;
            std::vector<std::string> folderList;
            System::Path("Sprites/LevelSprites" + path).loadResource(&folderList, System::Loaders::dirPathLoader);
            System::Path("Sprites/LevelSprites" + path).loadResource(&fileList, System::Loaders::filePathLoader);

            const int sprSize = 246;
            const int sprOff = 10;
            const int xOff = 15;
            const int yOff = 40;
            int elemIndex = 0;
            int xpos = (0 * (sprSize + sprOff)) + xOff;
            int ypos = floor(static_cast<double>(xpos) / static_cast<double>(1920 - (sprSize + sprOff))) * (sprSize + sprOff) + yOff;
            tgui::Button::Ptr backButton = tgui::Button::create();
            spritesPanel->add(backButton, "LS_ELEM_BACK");
            sf::Texture sprback;
            sprback.loadFromFile("Sprites/Others/back.png");
            backButton->getRenderer()->setTexture(sprback);
            backButton->setSize(sprSize, sprSize);
            backButton->setPosition(xpos, ypos);

            backButton->connect("pressed", [spritesPanel, spritesCatLabel, path]
            {
                std::vector<std::string> splittedPath = Utils::String::split(path, "/");
                loadSpriteFolder(spritesPanel, spritesCatLabel, "/" + Utils::Vector::join(splittedPath, "/", 0, 1));
            });

            for (std::string element : folderList)
            {
                int xpos = (++elemIndex * (sprSize + sprOff)) + xOff;
                int ypos = floor(static_cast<double>(xpos) / static_cast<double>(1920 - (sprSize + sprOff))) * (sprSize + sprOff);
                while (xpos > (1920 - (sprSize + sprOff)))
                    xpos -= (1920 - (sprSize + sprOff));
                xpos = floor(static_cast<double>(xpos) / static_cast<double>(sprSize + sprOff)) * (sprSize + sprOff);
                xpos += xOff;
                ypos += yOff;
                tgui::Button::Ptr currentFolder = tgui::Button::create();
                spritesPanel->add(currentFolder, "LS_FOLDER_" + element);
                currentFolder->setPosition(xpos, ypos);
                currentFolder->setSize(sprSize, sprSize);
                currentFolder->getRenderer()->setTexture(*Thumbnailer::GetFolderThumbnail(path + "/" + element));
                currentFolder->connect("pressed", [spritesPanel, spritesCatLabel, path, element]()
                {
                    loadSpriteFolder(spritesPanel, spritesCatLabel, path + "/" + element);
                });
            }

            for (std::string element : fileList)
            {
                sf::Texture textureLoadChecker;
                System::Path("Sprites/LevelSprites").add(path).add(element).loadResource(&textureLoadChecker, System::Loaders::textureLoader);
                if (textureLoadChecker.getSize().x != 0)
                {
                    int xpos = (++elemIndex * (sprSize + sprOff)) + xOff;
                    int ypos = floor(static_cast<double>(xpos) / static_cast<double>(1920 - (sprSize + sprOff))) * (sprSize + sprOff);
                    while (xpos > (1920 - (sprSize + sprOff)))
                        xpos -= (1920 - (sprSize + sprOff));
                    xpos = floor(static_cast<double>(xpos) / static_cast<double>(sprSize + sprOff)) * (sprSize + sprOff);
                    xpos += xOff;
                    ypos += yOff;
                    std::cout << "MAMIA1 : " << xpos << ", " << ypos << std::endl;
                    tgui::Button::Ptr currentSprite = tgui::Button::create();
                    spritesPanel->add(currentSprite, "LS_FILE_" + element);
                    currentSprite->setPosition(xpos, ypos);
                    currentSprite->getRenderer()->setTexture(*Thumbnailer::GetSpriteThumbnail(path + "/" + element));
                    currentSprite->setSize(sprSize, sprSize);
                    currentSprite->connect("pressed", [path, element] { addSpriteToWorld(path + "/" + element); });
                }
            }
        }

        void addSpriteToWorld(std::string geid)
        {
            std::cout << "Recv geid : " << geid << std::endl;
            Scene::Scene* world = Script::hookCore.getPointer("World")->as<Scene::Scene*>();
            int i = 0;
            std::string testId = "sprite" + std::to_string(world->getLevelSpriteAmount() + i);
            while (world->doesLevelSpriteExists(testId))
            {
                testId = "sprite" + std::to_string(world->getLevelSpriteAmount() + i++);
            }
            Graphics::LevelSprite* sprToAdd = world->createLevelSprite(testId);
            Transform::UnitVector pixelCamera = world->getCamera()->getPosition().to<Transform::Units::WorldPixels>();
            sprToAdd->load("Sprites/LevelSprites/" + geid);
            sprToAdd->getPosition() += Transform::UnitVector(960 + pixelCamera.x, 540 + pixelCamera.y, Transform::Units::WorldPixels);
            sprToAdd->setRotation(0);
            //ADD SPRITE SIZE
            sf::Vector2u textureSize = sprToAdd->getTexture().getSize();
            Transform::UnitVector initialSpriteSize(textureSize.x, textureSize.y, Transform::Units::WorldPixels);
            sprToAdd->setSize(initialSpriteSize);
            sprToAdd->setLayer(1);
            sprToAdd->setZDepth(1);
        }
    }
}
