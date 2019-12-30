#include <cmath>
#include <unordered_map>

#include <Editor/MapEditorTools.hpp>
#include <Scene/Scene.hpp>
#include <Script/GameObject.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>
#include <Transform/UnitVector.hpp>
#include <Utils/StringUtils.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe::Editor
{
    Thumbnailer* Thumbnailer::m_instance = nullptr;

    Thumbnailer::Thumbnailer()
    {
        System::Path("Data/Fonts/arial.ttf").load(System::Loaders::fontLoader, m_font);
        m_renderer.create(246, 246);
        System::Path("Sprites/Others/folder.png")
            .load(System::Loaders::textureLoader, m_folderTexture);
    }

    sf::Texture* Thumbnailer::GetSpriteThumbnail(const std::string& path)
    {
        if (m_instance == nullptr)
            m_instance = new Thumbnailer();
        if (m_instance->m_cache.find(path) != m_instance->m_cache.end())
            return m_instance->m_cache[path];
        sf::Texture sprTexture;
        System::Path("Sprites/LevelSprites/" + path)
            .load(System::Loaders::textureLoader, sprTexture);
        sf::Sprite sprite;
        sprite.setTexture(sprTexture);
        const double texW = sprTexture.getSize().x;
        const double texH = sprTexture.getSize().y;
        const double scale = (texW >= texH) ? m_size / texW : m_size / texH;
        sprite.setScale(scale, scale);
        sprite.setPosition(sf::Vector2f((m_size / 2) - (sprite.getGlobalBounds().width / 2),
            (m_size / 2) - (sprite.getGlobalBounds().height / 2)));
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
        m_instance->m_cache[path]->setSmooth(true);
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
        m_instance->m_cache[path]->setSmooth(true);
        return m_instance->m_cache[path];
    }

    void buildObjectTab(Scene::Scene& scene, tgui::Panel::Ptr& objectPanel,
        tgui::Panel::Ptr& requiresPanel, tgui::Theme& baseTheme,
        tgui::Scrollbar::Ptr objectsScrollbar)
    {
        std::vector<std::string> allGameObjects;
        System::Path("Data/GameObjects").loadAll(System::Loaders::dirPathLoader, allGameObjects);
        const unsigned int panelWidth = objectPanel->getSize().x;
        const int btnSize = float(panelWidth) * 0.115;
        const unsigned int btnOff = 10;
        const unsigned int maxElementsPerRow = float(panelWidth) / (float(btnSize) + float(btnOff));
        const unsigned int xOff = 15;
        const unsigned int yOff = 70;
        unsigned int xpos;
        unsigned int ypos = xpos = 0;

        const auto getBtnPos = [&btnSize, &btnOff, &xOff, &panelWidth, &yOff, &maxElementsPerRow](
                                   unsigned int& index) {
            unsigned int ixPos = (index % maxElementsPerRow) * (btnSize + btnOff) + xOff;
            unsigned int iyPos = index / maxElementsPerRow * (btnSize + btnOff) + yOff;
            return std::pair<unsigned int, unsigned int>(ixPos, iyPos);
        };

        for (unsigned int i = 0; i < allGameObjects.size(); i++)
        {
            std::string currentObjName = allGameObjects[i];
            std::tie(xpos, ypos) = getBtnPos(i);
            tgui::Button::Ptr currentObj = tgui::Button::create();
            currentObj->setRenderer(baseTheme.getRenderer("ObjectButton"));
            currentObj->setTextSize(18);
            currentObj->setText(currentObjName);
            currentObj->setPosition(xpos, ypos);
            currentObj->setSize(btnSize, btnSize);
            objectPanel->add(currentObj);
            currentObj->connect("pressed", [&scene, &requiresPanel, &baseTheme, currentObjName]() {
                buildRequiresObjectTab(scene, requiresPanel, baseTheme, currentObjName);
            });
        }

        objectsScrollbar->setMaximum(ypos + btnSize + yOff + 30);
    }

    void buildRequiresObjectTab(Scene::Scene& scene, tgui::Panel::Ptr& requiresPanel,
        tgui::Theme& baseTheme, const std::string& objName)
    {
        vili::ComplexNode* requires
            = Script::GameObjectDatabase::GetRequirementsForGameObject(objName);
        const std::string key
            = Utils::String::getRandomKey(Utils::String::Alphabet + Utils::String::Numbers, 8);
        vili::ComplexNode* requireCopy = new vili::ComplexNode(key);
        if (requires != nullptr)
        {
            requires->getComplexNode("Input").copy(requireCopy, "Input");
            requires->getComplexNode("Output").copy(requireCopy, "Output");
            vili::ComplexNode& requireInput = requires->at("Input");
            requiresPanel->show();
            tgui::Panel::Ptr content = requiresPanel->get<tgui::Panel>("content");
            content->removeAllWidgets();

            tgui::Label::Ptr newObjectTitleLabel = tgui::Label::create();
            newObjectTitleLabel->setPosition(10, 10);
            newObjectTitleLabel->setTextSize(32);
            newObjectTitleLabel->setRenderer(baseTheme.getRenderer("Label"));
            newObjectTitleLabel->setText("<" + objName + "> Instance Creator");

            content->add(newObjectTitleLabel);

            std::unordered_map<std::string, tgui::ComboBox::Ptr> requireComboBoxes;
            std::unordered_map<std::string, tgui::EditBox::Ptr> requireEditBoxes;

            int widgetVerticalPosition = 70;
            for (vili::ComplexNode* complexRequire : requireInput.getAll<vili::ComplexNode>())
            {
                const std::string requireItem = complexRequire->getId();
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
                    currentRequirementInput->setSize("33%", "32");
                    currentRequirementInput->setPosition(200, widgetVerticalPosition + 5);
                    content->add(currentRequirementInput, requireItem + "_input");
                    requireEditBoxes[requireItem] = currentRequirementInput;
                }
                else if (requireInput.at(requireItem)
                             .contains(vili::NodeType::ArrayNode, "choices"))
                {
                    tgui::ComboBox::Ptr currentRequirementList = tgui::ComboBox::create();
                    currentRequirementList->setSize(200, 32);
                    currentRequirementList->setPosition(200, widgetVerticalPosition);
                    currentRequirementList->setTextSize(20);
                    currentRequirementList->setItemsToDisplay(4);
                    currentRequirementList->setRenderer(baseTheme.getRenderer("ComboBox"));
                    content->add(currentRequirementList, requireItem + "_input");
                    for (int reqI = 0;
                         reqI < requireInput.at(requireItem).getArrayNode("choices").size(); reqI++)
                        currentRequirementList->addItem(requireInput.at(requireItem)
                                                            .getArrayNode("choices")
                                                            .get(reqI)
                                                            .get<std::string>());
                    currentRequirementList->setSelectedItem(currentRequirementList->getItems()[0]);
                    requireComboBoxes[requireItem] = currentRequirementList;
                }
                widgetVerticalPosition += 50;
            }

            tgui::Button::Ptr createObjectButton = tgui::Button::create();

            createObjectButton->setPosition(10, "100% - 60");
            createObjectButton->setSize("100% - 20", 50);
            createObjectButton->setRenderer(baseTheme.getRenderer("Button"));
            createObjectButton->setTextSize(20);
            createObjectButton->setText("Create Object");

            createObjectButton->connect("pressed",
                [objName, requireComboBoxes, requireEditBoxes, key, requireCopy, &scene,
                    &requiresPanel]() mutable {
                    for (auto& cReq : requireComboBoxes)
                    {
                        requireCopy->at("Input", cReq.first)
                            .createDataNode("value", cReq.second->getSelectedItem());
                    }
                    for (auto& cReq : requireEditBoxes)
                    {
                        requireCopy->at("Input", cReq.first)
                            .createDataNode("value", cReq.second->getText());
                    }
                    buildObjectThroughRequire(scene, objName, requireCopy);
                    requiresPanel->hide();
                });

            requiresPanel->add(createObjectButton);
        }
        else
        {
            Script::GameObject* newGameObject = scene.createGameObject(objName, key);
            newGameObject->initialize();
        }
    }

    void buildObjectThroughRequire(
        Scene::Scene& scene, const std::string& objName, vili::ComplexNode* requires)
    {
        const std::string key
            = Utils::String::getRandomKey(Utils::String::Alphabet + Utils::String::Numbers, 8);
        Script::GameObject* newGameObject = scene.createGameObject(objName, key);

        requires->at("Output").walk([](vili::NodeIterator& node) {
            for (vili::LinkNode* link : node->getAll<vili::LinkNode>())
            {
                node->createDataNode("__linkroot__", "Input");
                link->apply();
                node->remove("__linkroot__");
            }
        });

        Script::GameObjectDatabase::ApplyRequirements(newGameObject, requires->at("Output"));
        newGameObject->exec("LuaCore.InjectInitInjectionTable()");
        newGameObject->initialize();
    }

    void loadSpriteFolder(Scene::Scene& scene, tgui::Panel::Ptr spritesPanel,
        tgui::Label::Ptr spritesCatLabel, const std::string& path,
        tgui::Scrollbar::Ptr spritesScrollbar)
    {
        spritesPanel->removeAllWidgets();
        spritesPanel->add(spritesCatLabel);

        std::vector<std::string> fileList;
        std::vector<std::string> folderList;
        System::Path("Sprites/LevelSprites" + path)
            .loadAll(System::Loaders::dirPathLoader, folderList);
        System::Path("Sprites/LevelSprites" + path)
            .loadAll(System::Loaders::filePathLoader, fileList);

        const int sprSize = spritesPanel->getSize().x * 0.115;
        const int panelWidth = spritesPanel->getSize().x;

        const int sprOff = 10;
        const int xOff = 15;
        const int yOff = 70;
        unsigned int maxElementsPerRow = float(panelWidth) / (float(sprSize) + float(sprOff));
        unsigned int elemIndex = 0;
        const auto getSpritePos = [&sprSize, &sprOff, &xOff, &panelWidth, &yOff,
                                      &maxElementsPerRow](unsigned int& index) {
            unsigned int ixPos = (index % maxElementsPerRow) * (sprSize + sprOff) + xOff;
            unsigned int iyPos = index / maxElementsPerRow * (sprSize + sprOff) + yOff;
            index++;

            return std::pair<unsigned int, unsigned int>(ixPos, iyPos);
        };
        unsigned int xpos;
        unsigned ypos = xpos = 0;
        std::tie(xpos, ypos) = getSpritePos(elemIndex);
        tgui::Button::Ptr backButton = tgui::Button::create();
        spritesPanel->add(backButton, "LS_ELEM_BACK");
        sf::Texture sprback;
        System::Path("Sprites/Others/back.png").load(System::Loaders::textureLoader, sprback);
        sprback.setSmooth(true);
        backButton->getRenderer()->setTexture(sprback);
        backButton->setSize(sprSize, sprSize);
        backButton->setPosition(xpos, ypos);

        backButton->connect(
            "pressed", [spritesPanel, spritesCatLabel, path, spritesScrollbar, &scene] {
                std::vector<std::string> splittedPath = Utils::String::split(path, "/");
                loadSpriteFolder(scene, spritesPanel, spritesCatLabel,
                    "/" + Utils::Vector::join(splittedPath, "/", 0, 1), spritesScrollbar);
            });

        for (std::string element : folderList)
        {
            std::tie(xpos, ypos) = getSpritePos(elemIndex);
            tgui::Button::Ptr currentFolder = tgui::Button::create();
            spritesPanel->add(currentFolder, "LS_FOLDER_" + element);
            currentFolder->setSize(sprSize, sprSize);
            currentFolder->setPosition(xpos, ypos);
            currentFolder->getRenderer()->setTexture(
                *Thumbnailer::GetFolderThumbnail(path + "/" + element));
            currentFolder->connect("pressed",
                [spritesPanel, spritesCatLabel, path, element, spritesScrollbar, &scene]() {
                    loadSpriteFolder(scene, spritesPanel, spritesCatLabel, path + "/" + element,
                        spritesScrollbar);
                });
        }

        for (std::string element : fileList)
        {
            sf::Texture textureLoadChecker;
            System::Path("Sprites/LevelSprites")
                .add(path)
                .add(element)
                .load(System::Loaders::textureLoader, textureLoadChecker, true);
            if (textureLoadChecker.getSize().x != 0)
            {
                std::tie(xpos, ypos) = getSpritePos(elemIndex);

                tgui::Button::Ptr currentSprite = tgui::Button::create();
                spritesPanel->add(currentSprite, "LS_FILE_" + element);
                currentSprite->setPosition(xpos, ypos);
                currentSprite->getRenderer()->setTexture(
                    *Thumbnailer::GetSpriteThumbnail(path + "/" + element));
                currentSprite->setSize(sprSize, sprSize);
                currentSprite->connect("pressed",
                    [path, element, &scene] { addSpriteToScene(scene, path + "/" + element); });
            }
        }

        spritesScrollbar->setMaximum(ypos + sprSize + yOff + 30);
    }

    void addSpriteToScene(Scene::Scene& scene, const std::string& spritePath)
    {
        int i = 0;
        std::string testId = "sprite" + std::to_string(scene.getLevelSpriteAmount() + i);
        while (scene.doesLevelSpriteExists(testId))
        {
            testId = "sprite" + std::to_string(scene.getLevelSpriteAmount() + i++);
        }
        Graphics::LevelSprite* sprToAdd = scene.createLevelSprite(testId);
        const Transform::UnitVector pixelCamera
            = scene.getCamera()->getPosition().to<Transform::Units::ScenePixels>();
        sprToAdd->loadTexture("Sprites/LevelSprites/" + spritePath);
        sprToAdd->setPosition(pixelCamera);

        sprToAdd->setRotation(0);
        // ADD SPRITE SIZE
        sprToAdd->useTextureSize();
        sprToAdd->setLayer(1);
        sprToAdd->setZDepth(1);
    }
} // namespace obe::Editor