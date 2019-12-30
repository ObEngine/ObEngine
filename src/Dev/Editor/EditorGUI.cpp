#include <Config/Config.hpp>
#include <Editor/EditorGUI.hpp>
#include <Editor/MapEditorTools.hpp>
#include <Input/InputCondition.hpp>
#include <System/Loaders.hpp>
#include <System/Window.hpp>
#include <Utils/StringUtils.hpp>

namespace obe::Editor::GUI
{
    tgui::Theme baseTheme;

    void init()
    {
        calculateFontSize();
        baseTheme = tgui::Theme();
        baseTheme.load("Data/GUI/obe.style");
    }

    void calculateFontSize()
    {
        double wCoeff;
        const sf::Vector2u windowSize = System::MainWindow.getSize();
        const unsigned int screenWidth = sf::VideoMode::getDesktopMode().width;

        if (windowSize.x < screenWidth)
            wCoeff
                = (double(screenWidth - System::MainWindow.getSize().x) / double(screenWidth)) * 0.5
                + 1.0;
        else
            wCoeff = 1
                - (double(windowSize.x - sf::VideoMode::getDesktopMode().width)
                      / double(System::MainWindow.getSize().x));
        bigFontSize = double(windowSize.x) / double(64.0 / wCoeff);
        mediumFontSize = double(bigFontSize) / 1.3;
        smallFontSize = double(bigFontSize) / 2.0;
    }

    void applyFontSize(tgui::Panel::Ptr& mainPanel)
    {
        mainPanel->get<tgui::Label>("titleLabel")->setTextSize(bigFontSize);
        mainPanel->get<tgui::Label>("infoLabel")->setTextSize(mediumFontSize);
        mainPanel->get<tgui::ComboBox>("editMode")->setTextSize(mediumFontSize);
        mainPanel->get<tgui::Button>("editorButton")->setTextSize(mediumFontSize);
        mainPanel->get<tgui::Label>("savedLabel")->setTextSize(smallFontSize);
        mainPanel->get<tgui::Button>("mapButton")->setTextSize(mediumFontSize);
        mainPanel->get<tgui::Button>("settingsButton")->setTextSize(mediumFontSize);
        mainPanel->get<tgui::Button>("keybindingButton")->setTextSize(mediumFontSize);
        mainPanel->get<tgui::Button>("spritesButton")->setTextSize(mediumFontSize);
        mainPanel->get<tgui::Button>("objectsButton")->setTextSize(mediumFontSize);
        mainPanel->get<tgui::Label>("mapCatLabel")->setTextSize(bigFontSize);
        mainPanel->get<tgui::Label>("mapNameLabel")->setTextSize(mediumFontSize);
        mainPanel->get<tgui::EditBox>("mapNameInput")->setSize("8.3%", mediumFontSize + 4);
        mainPanel->get<tgui::Label>("settingsCatLabel")->setTextSize(bigFontSize);
        mainPanel->get<tgui::CheckBox>("displayFramerateCheckbox")->setTextSize(mediumFontSize);
        mainPanel->get<tgui::CheckBox>("enableGridCheckbox")->setTextSize(mediumFontSize);
        mainPanel->get<tgui::Label>("gridDimensionLabel")->setTextSize(mediumFontSize);
        mainPanel->get<tgui::EditBox>("gridDimensionXInput")->setSize("8.3%", mediumFontSize + 4);
        mainPanel->get<tgui::EditBox>("gridDimensionYInput")->setSize("8.3%", mediumFontSize + 4);
        mainPanel->get<tgui::Label>("gridOffsetLabel")->setTextSize(mediumFontSize);
        mainPanel->get<tgui::EditBox>("gridOffsetXInput")->setSize("8.3%", mediumFontSize + 4);
        mainPanel->get<tgui::EditBox>("gridOffsetYInput")->setSize("8.3%", mediumFontSize + 4);
        mainPanel->get<tgui::CheckBox>("snapGridCheckbox")->setTextSize(mediumFontSize);
        mainPanel->get<tgui::Label>("cameraPositionLabel")->setTextSize(mediumFontSize);
        mainPanel->get<tgui::EditBox>("cameraPositionXInput")->setSize("8.3%", mediumFontSize + 4);
        mainPanel->get<tgui::EditBox>("cameraPositionYInput")->setSize("8.3%", mediumFontSize + 4);
        mainPanel->get<tgui::Label>("cameraSizeLabel")->setTextSize(mediumFontSize);
        mainPanel->get<tgui::EditBox>("cameraSizeInput")->setSize("8.3%", mediumFontSize + 4);
        mainPanel->get<tgui::CheckBox>("saveCameraPositionCheckbox")->setTextSize(mediumFontSize);

        tgui::Panel::Ptr keybindingPanel = mainPanel->get<tgui::Panel>("keybindingPanel");
        tgui::Scrollbar::Ptr keybindingScrollbar
            = mainPanel->get<tgui::Scrollbar>("keybindingScrollbar");
        buildKeyBindingMenu(keybindingPanel, keybindingScrollbar);
    }

    void applyScrollbarMaxValue(tgui::Panel::Ptr& mainPanel)
    {
        mainPanel->get<tgui::Scrollbar>("keybindingScrollbar")
            ->setLowValue(mainPanel->get<tgui::Panel>("keybindingPanel")->getSize().y);
        mainPanel->get<tgui::Scrollbar>("spritesScrollbar")
            ->setLowValue(mainPanel->get<tgui::Panel>("spritesPanel")->getSize().y);
        mainPanel->get<tgui::Scrollbar>("objectsScrollbar")
            ->setLowValue(mainPanel->get<tgui::Panel>("objectsPanel")->getSize().y);
        // mainPanel->get<tgui::Scrollbar>("inspectorScrollbar")->setLowValue(mainPanel->get<tgui::Panel>("inspectorPanel")->getSize().y);
    }

    void scrollPanel(tgui::Panel::Ptr panel, tgui::Scrollbar::Ptr scrollbar)
    {
        static int previousScrolbarValue = 0;
        const int distanceToMove = previousScrolbarValue - scrollbar->getValue();

        for (auto& widget : panel->getWidgets())
            widget->setPosition(widget->getPosition().x, widget->getPosition().y + distanceToMove);

        previousScrolbarValue = scrollbar->getValue();
    }

    void buildToolbar(
        tgui::Panel::Ptr& mainPanel, tgui::Panel::Ptr& editorPanel, Scene::Scene& scene)
    {
        tgui::Panel::Ptr titlePanel = tgui::Panel::create();
        tgui::Label::Ptr titleLabel = tgui::Label::create();
        tgui::Label::Ptr infoLabel = tgui::Label::create();
        tgui::Label::Ptr savedLabel = tgui::Label::create();
        tgui::Button::Ptr editorButton = tgui::Button::create();
        tgui::CheckBox::Ptr updateStateCheckbox = tgui::CheckBox::create();
        tgui::ComboBox::Ptr editMode = tgui::ComboBox::create();

        mainPanel->add(titlePanel, "titlePanel");

        titlePanel->add(titleLabel, "titleLabel");
        titlePanel->add(infoLabel, "infoLabel");
        titlePanel->add(savedLabel, "savedLabel");
        titlePanel->add(editorButton, "editorButton");
        titlePanel->add(updateStateCheckbox, "updateStateCheckbox");
        titlePanel->add(editMode, "editMode");

        titlePanel->setRenderer(baseTheme.getRenderer("TransparentPanel"));
        titlePanel->setSize("100%", tgui::bindHeight(titleLabel) + 10);
        titlePanel->setPosition(0, 0);

        titleLabel->setPosition(0, "(&.height - height) / 2");
        titleLabel->setTextSize(bigFontSize);
        titleLabel->setRenderer(baseTheme.getRenderer("Label"));
        titleLabel->setText("ObEngine Map Editor");

        infoLabel->setPosition(
            tgui::bindRight(titleLabel) + tgui::Layout("5%"), "(&.height - height) / 2");
        infoLabel->setTextSize(mediumFontSize);
        infoLabel->setRenderer(baseTheme.getRenderer("Label"));
        infoLabel->setText("<>");

        editMode->addItem("LevelSprites");
        editMode->addItem("Collisions");
        editMode->addItem("Play");
        editMode->addItem("SceneNodes");
        editMode->addItem("None");
        editMode->setSelectedItem("None");
        editMode->setSize("10.5%", "100% - 1");
        editMode->setPosition(tgui::bindWidth(titlePanel) - tgui::bindWidth(editMode) - 1, 0);
        editMode->setTextSize(mediumFontSize);
        editMode->setRenderer(baseTheme.getRenderer("ComboBox"));
        editMode->getRenderer()->getTextureArrowUp().setSmooth(true);
        editMode->getRenderer()->getTextureArrowDown().setSmooth(true);

        updateStateCheckbox->setSize(128, "100% - 1");
        updateStateCheckbox->setPosition(
            tgui::bindLeft(editMode) - tgui::bindWidth(updateStateCheckbox) - 1, 0);
        updateStateCheckbox->setRenderer(baseTheme.getRenderer("StateCheckBox"));
        updateStateCheckbox->getRenderer()->getTextureChecked().setSmooth(true);
        updateStateCheckbox->getRenderer()->getTextureUnchecked().setSmooth(true);
        updateStateCheckbox->check();

        editorButton->setSize("9.8%", "100%");
        editorButton->setPosition(
            tgui::bindLeft(updateStateCheckbox) - tgui::bindWidth(editorButton) - 1, 0);
        editorButton->setText("Editor Menu");
        editorButton->setTextSize(mediumFontSize);
        editorButton->setRenderer(baseTheme.getRenderer("Button"));

        savedLabel->setPosition(tgui::bindLeft(editorButton) - 50, 5);
        savedLabel->setTextSize(smallFontSize);
        savedLabel->setRenderer(baseTheme.getRenderer("GreenLabel"));
        savedLabel->setText("Saved");
        savedLabel->hide();

        editorButton->connect("pressed", [editorPanel]() {
            editorPanel->isVisible() ? editorPanel->hide() : editorPanel->show();
        });

        updateStateCheckbox->connect("checked", [&scene]() { scene.setUpdateState(true); });

        updateStateCheckbox->connect("unchecked", [&scene]() { scene.setUpdateState(false); });
    }

    void buildEditorMenu(tgui::Panel::Ptr& mainPanel)
    {
        tgui::Panel::Ptr editorPanel = tgui::Panel::create();
        tgui::Panel::Ptr mapPanel = tgui::Panel::create();
        tgui::Panel::Ptr settingsPanel = tgui::Panel::create();
        tgui::Panel::Ptr keybindingPanel = tgui::Panel::create();
        tgui::Scrollbar::Ptr keybindingScrollbar = tgui::Scrollbar::create();
        tgui::Panel::Ptr spritesPanel = tgui::Panel::create();
        tgui::Scrollbar::Ptr spritesScrollbar = tgui::Scrollbar::create();
        tgui::Panel::Ptr objectsPanel = tgui::Panel::create();
        tgui::Scrollbar::Ptr objectsScrollbar = tgui::Scrollbar::create();
        tgui::Button::Ptr mapButton = tgui::Button::create();
        tgui::Button::Ptr settingsButton = tgui::Button::create();
        tgui::Button::Ptr keybindingButton = tgui::Button::create();
        tgui::Button::Ptr spritesButton = tgui::Button::create();
        tgui::Button::Ptr objectsButton = tgui::Button::create();

        mainPanel->add(editorPanel, "editorPanel");
        editorPanel->setRenderer(baseTheme.getRenderer("DarkTransparentPanel"));
        editorPanel->setSize("100% - 100", "100% - 100");
        editorPanel->setPosition(50, 70);
        editorPanel->hide();

        editorPanel->add(mapPanel, "mapPanel");
        editorPanel->add(settingsPanel, "settingsPanel");
        editorPanel->add(keybindingPanel, "keybindingPanel");
        editorPanel->add(keybindingScrollbar, "keybindingScrollbar");
        editorPanel->add(spritesPanel, "spritesPanel");
        editorPanel->add(spritesScrollbar, "spritesScrollbar");
        editorPanel->add(objectsPanel, "objectsPanel");
        editorPanel->add(objectsScrollbar, "objectsScrollbar");
        editorPanel->add(mapButton, "mapButton");
        editorPanel->add(settingsButton, "settingsButton");
        editorPanel->add(keybindingButton, "keybindingButton");
        editorPanel->add(spritesButton, "spritesButton");
        editorPanel->add(objectsButton, "objectsButton");

        mapButton->setSize("20%", 30);
        mapButton->setPosition(0, 0);
        mapButton->setRenderer(baseTheme.getRenderer("Button"));
        mapButton->setText("Map");
        mapButton->setTextSize(mediumFontSize);

        settingsButton->setPosition(tgui::bindRight(mapButton), 0);
        settingsButton->setSize("20%", 30);
        settingsButton->setRenderer(baseTheme.getRenderer("Button"));
        settingsButton->setText("Settings");
        settingsButton->setTextSize(mediumFontSize);

        keybindingButton->setPosition(tgui::bindRight(settingsButton), 0);
        keybindingButton->setSize("20%", 30);
        keybindingButton->setRenderer(baseTheme.getRenderer("Button"));
        keybindingButton->setText("Keybinding");
        keybindingButton->setTextSize(mediumFontSize);

        spritesButton->setPosition(tgui::bindRight(keybindingButton), 0);
        spritesButton->setSize("20%", 30);
        spritesButton->setRenderer(baseTheme.getRenderer("Button"));
        spritesButton->setText("Sprites");
        spritesButton->setTextSize(mediumFontSize);

        objectsButton->setPosition(tgui::bindRight(spritesButton), 0);
        objectsButton->setSize("20%", 30);
        objectsButton->setRenderer(baseTheme.getRenderer("Button"));
        objectsButton->setText("Objects");
        objectsButton->setTextSize(mediumFontSize);

        mapPanel->setRenderer(baseTheme.getRenderer("DarkTransparentPanel"));
        mapPanel->setSize("100%", "100% - 30");
        mapPanel->setPosition(0, 30);

        settingsPanel->setRenderer(baseTheme.getRenderer("DarkTransparentPanel"));
        settingsPanel->setSize("100%", "100% - 30");
        settingsPanel->setPosition(0, 30);

        keybindingPanel->setRenderer(baseTheme.getRenderer("DarkTransparentPanel"));
        keybindingPanel->setSize("100%", "100% - 30");
        keybindingPanel->setPosition(0, 30);

        keybindingScrollbar->setPosition("&.width - width", tgui::bindBottom(objectsButton));
        keybindingScrollbar->setSize(
            "16", tgui::bindHeight(editorPanel) - tgui::bindHeight(objectsButton));
        keybindingScrollbar->connect(
            "ValueChanged", scrollPanel, keybindingPanel, keybindingScrollbar);
        keybindingScrollbar->setLowValue(keybindingPanel->getSize().y);

        spritesPanel->setRenderer(baseTheme.getRenderer("DarkTransparentPanel"));
        spritesPanel->setSize("100%", "100% - 30");
        spritesPanel->setPosition(0, 30);

        spritesScrollbar->setPosition("100% - 16", "30");
        spritesScrollbar->setSize("16", "100% - 30");
        spritesScrollbar->connect("ValueChanged", scrollPanel, spritesPanel, spritesScrollbar);
        spritesScrollbar->setLowValue(spritesPanel->getSize().y);

        objectsPanel->setRenderer(baseTheme.getRenderer("DarkTransparentPanel"));
        objectsPanel->setSize("100%", "100% - 30");
        objectsPanel->setPosition(0, 30);

        objectsScrollbar->setPosition("&.width - width", tgui::bindBottom(objectsButton));
        objectsScrollbar->setSize(
            "16", tgui::bindHeight(editorPanel) - tgui::bindHeight(objectsButton));
        objectsScrollbar->connect("ValueChanged", scrollPanel, objectsPanel, objectsScrollbar);
        objectsScrollbar->setLowValue(objectsPanel->getSize().y);

        mapButton->setRenderer(baseTheme.getRenderer("SelectedButton"));
        settingsPanel->hide();
        keybindingPanel->hide();
        spritesPanel->hide();
        objectsPanel->hide();

        mapButton->connect(
            "pressed", [mainPanel, spritesScrollbar, objectsScrollbar, keybindingScrollbar]() {
                mainPanel->get<tgui::Panel>("mapPanel")->show();
                mainPanel->get<tgui::Panel>("settingsPanel")->hide();
                mainPanel->get<tgui::Panel>("keybindingPanel")->hide();
                mainPanel->get<tgui::Panel>("spritesPanel")->hide();
                mainPanel->get<tgui::Panel>("objectsPanel")->hide();
                mainPanel->get<tgui::Button>("mapButton")
                    ->setRenderer(baseTheme.getRenderer("SelectedButton"));
                mainPanel->get<tgui::Button>("settingsButton")
                    ->setRenderer(baseTheme.getRenderer("Button"));
                mainPanel->get<tgui::Button>("keybindingButton")
                    ->setRenderer(baseTheme.getRenderer("Button"));
                mainPanel->get<tgui::Button>("spritesButton")
                    ->setRenderer(baseTheme.getRenderer("Button"));
                mainPanel->get<tgui::Button>("objectsButton")
                    ->setRenderer(baseTheme.getRenderer("Button"));
                spritesScrollbar->hide();
                objectsScrollbar->hide();
                keybindingScrollbar->hide();
            });

        settingsButton->connect(
            "pressed", [mainPanel, spritesScrollbar, objectsScrollbar, keybindingScrollbar]() {
                mainPanel->get<tgui::Panel>("mapPanel")->hide();
                mainPanel->get<tgui::Panel>("settingsPanel")->show();
                mainPanel->get<tgui::Panel>("keybindingPanel")->hide();
                mainPanel->get<tgui::Panel>("spritesPanel")->hide();
                mainPanel->get<tgui::Panel>("objectsPanel")->hide();
                mainPanel->get<tgui::Button>("mapButton")
                    ->setRenderer(baseTheme.getRenderer("Button"));
                mainPanel->get<tgui::Button>("settingsButton")
                    ->setRenderer(baseTheme.getRenderer("SelectedButton"));
                mainPanel->get<tgui::Button>("keybindingButton")
                    ->setRenderer(baseTheme.getRenderer("Button"));
                mainPanel->get<tgui::Button>("spritesButton")
                    ->setRenderer(baseTheme.getRenderer("Button"));
                mainPanel->get<tgui::Button>("objectsButton")
                    ->setRenderer(baseTheme.getRenderer("Button"));
                spritesScrollbar->hide();
                objectsScrollbar->hide();
                keybindingScrollbar->hide();
            });

        keybindingButton->connect("pressed", [mainPanel, spritesScrollbar, objectsScrollbar]() {
            tgui::Panel::Ptr keybindingPanel = mainPanel->get<tgui::Panel>("keybindingPanel");
            tgui::Scrollbar::Ptr keybindingScrollbar
                = mainPanel->get<tgui::Scrollbar>("keybindingScrollbar");
            buildKeyBindingMenu(keybindingPanel, keybindingScrollbar);
            mainPanel->get<tgui::Panel>("mapPanel")->hide();
            mainPanel->get<tgui::Panel>("settingsPanel")->hide();
            mainPanel->get<tgui::Panel>("keybindingPanel")->show();
            mainPanel->get<tgui::Panel>("spritesPanel")->hide();
            mainPanel->get<tgui::Panel>("objectsPanel")->hide();
            mainPanel->get<tgui::Button>("mapButton")->setRenderer(baseTheme.getRenderer("Button"));
            mainPanel->get<tgui::Button>("settingsButton")
                ->setRenderer(baseTheme.getRenderer("Button"));
            mainPanel->get<tgui::Button>("keybindingButton")
                ->setRenderer(baseTheme.getRenderer("SelectedButton"));
            mainPanel->get<tgui::Button>("spritesButton")
                ->setRenderer(baseTheme.getRenderer("Button"));
            mainPanel->get<tgui::Button>("objectsButton")
                ->setRenderer(baseTheme.getRenderer("Button"));
            spritesScrollbar->hide();
            objectsScrollbar->hide();
            keybindingScrollbar->show();
        });

        spritesButton->connect(
            "pressed", [mainPanel, spritesScrollbar, objectsScrollbar, keybindingScrollbar]() {
                mainPanel->get<tgui::Panel>("mapPanel")->hide();
                mainPanel->get<tgui::Panel>("settingsPanel")->hide();
                mainPanel->get<tgui::Panel>("keybindingPanel")->hide();
                mainPanel->get<tgui::Panel>("spritesPanel")->show();
                mainPanel->get<tgui::Panel>("objectsPanel")->hide();
                mainPanel->get<tgui::Button>("mapButton")
                    ->setRenderer(baseTheme.getRenderer("Button"));
                mainPanel->get<tgui::Button>("settingsButton")
                    ->setRenderer(baseTheme.getRenderer("Button"));
                mainPanel->get<tgui::Button>("keybindingButton")
                    ->setRenderer(baseTheme.getRenderer("Button"));
                mainPanel->get<tgui::Button>("spritesButton")
                    ->setRenderer(baseTheme.getRenderer("SelectedButton"));
                mainPanel->get<tgui::Button>("objectsButton")
                    ->setRenderer(baseTheme.getRenderer("Button"));
                spritesScrollbar->show();
                objectsScrollbar->hide();
                keybindingScrollbar->hide();
            });

        objectsButton->connect(
            "pressed", [mainPanel, spritesScrollbar, objectsScrollbar, keybindingScrollbar]() {
                mainPanel->get<tgui::Panel>("mapPanel")->hide();
                mainPanel->get<tgui::Panel>("settingsPanel")->hide();
                mainPanel->get<tgui::Panel>("keybindingPanel")->hide();
                mainPanel->get<tgui::Panel>("spritesPanel")->hide();
                mainPanel->get<tgui::Panel>("objectsPanel")->show();
                mainPanel->get<tgui::Button>("mapButton")
                    ->setRenderer(baseTheme.getRenderer("Button"));
                mainPanel->get<tgui::Button>("settingsButton")
                    ->setRenderer(baseTheme.getRenderer("Button"));
                mainPanel->get<tgui::Button>("keybindingButton")
                    ->setRenderer(baseTheme.getRenderer("Button"));
                mainPanel->get<tgui::Button>("spritesButton")
                    ->setRenderer(baseTheme.getRenderer("Button"));
                mainPanel->get<tgui::Button>("objectsButton")
                    ->setRenderer(baseTheme.getRenderer("SelectedButton"));
                spritesScrollbar->hide();
                objectsScrollbar->show();
                keybindingScrollbar->hide();
            });
    }

    void buildEditorMapMenu(tgui::Panel::Ptr& mapPanel, Scene::Scene& scene)
    {
        tgui::Label::Ptr mapNameLabel = tgui::Label::create();
        tgui::EditBox::Ptr mapNameInput = tgui::EditBox::create();
        tgui::Button::Ptr mapNameButton = tgui::Button::create();
        tgui::Label::Ptr mapCatLabel = tgui::Label::create();
        tgui::Label::Ptr inspectorLabel = tgui::Label::create();
        tgui::Panel::Ptr inspectorPanel = tgui::Panel::create();
        tgui::Panel::Ptr inspectorLeftPanel = tgui::Panel::create();
        tgui::Panel::Ptr inspectorRightPanel = tgui::Panel::create();
        tgui::Button::Ptr inspectorRefreshButton = tgui::Button::create();
        // tgui::Scrollbar::Ptr inspectorScrollbar = tgui::Scrollbar::create();

        mapPanel->add(mapCatLabel, "mapCatLabel");
        mapPanel->add(mapNameLabel, "mapNameLabel");
        mapPanel->add(mapNameInput, "mapNameInput");
        mapPanel->add(mapNameButton, "mapNameButton");
        mapPanel->add(inspectorLabel, "inspectorLabel");
        mapPanel->add(inspectorRefreshButton, "inspectorRefreshButton");
        mapPanel->add(inspectorPanel, "inspectorPanel");

        inspectorPanel->add(inspectorLeftPanel, "inspectorLeftPanel");
        inspectorPanel->add(inspectorRightPanel, "inspectorRightPanel");

        mapCatLabel->setPosition(20, 20);
        mapCatLabel->setTextSize(bigFontSize);
        mapCatLabel->setRenderer(baseTheme.getRenderer("Label"));
        mapCatLabel->setText("[ Map Settings ]");

        mapNameLabel->setPosition(60, tgui::bindBottom(mapCatLabel) + 20);
        mapNameLabel->setTextSize(mediumFontSize);
        mapNameLabel->setRenderer(baseTheme.getRenderer("Label"));
        mapNameLabel->setText("Map Name : ");

        auto changeMapNameLambda = [&scene, mapPanel]() {
            tgui::EditBox::Ptr mapNameInput = mapPanel->get<tgui::EditBox>("mapNameInput");
            if (mapNameInput->getText() != "")
            {
                scene.setLevelName(mapNameInput->getText());
                mapNameInput->setRenderer(baseTheme.getRenderer("TextBox"));
            }
            else
            {
                mapNameInput->setRenderer(baseTheme.getRenderer("InvalidTextBox"));
            }
        };

        auto getSceneContent = [&scene, inspectorLeftPanel]() {
            inspectorLeftPanel->removeAllWidgets();
            vili::ViliParser* sceneDump = scene.dump(false);
            int i = 0;
            for (vili::ComplexNode* spr :
                sceneDump->root().at("LevelSprites").getAll<vili::ComplexNode>())
            {
                tgui::Panel::Ptr inspectorSprPanel = tgui::Panel::create();
                inspectorLeftPanel->add(inspectorSprPanel);
                inspectorSprPanel->setRenderer(baseTheme.getRenderer("DarkTransparentPanel"));
                inspectorSprPanel->setSize("100%", "10%");
                inspectorSprPanel->setPosition(0, i++ * 100);
                tgui::Label::Ptr inspectorSprLabel = tgui::Label::create();
                inspectorSprPanel->add(inspectorSprLabel);
                inspectorSprLabel->setPosition(0, 0);
                inspectorSprLabel->setTextSize(bigFontSize);
                inspectorSprLabel->setRenderer(baseTheme.getRenderer("Label"));
                inspectorSprLabel->setText(spr->getId());
            }
        };

        mapNameInput->setPosition(tgui::bindRight(mapNameLabel) + 20, tgui::bindTop(mapNameLabel));
        mapNameInput->setSize("8.3%", mediumFontSize + 4);
        mapNameInput->setRenderer(baseTheme.getRenderer("TextBox"));
        mapNameInput->connect("returnkeypressed", changeMapNameLambda);

        mapNameButton->setSize(16, 16);
        mapNameButton->setPosition(tgui::bindRight(mapNameInput) + 20,
            tgui::bindTop(mapNameInput) + tgui::bindHeight(mapNameInput) / 2
                - tgui::bindHeight(mapNameButton) / 2);
        mapNameButton->setRenderer(baseTheme.getRenderer("ApplyButton"));
        mapNameButton->connect("pressed", changeMapNameLambda);

        inspectorLabel->setPosition(40, tgui::bindBottom(mapNameLabel) + 20);
        inspectorLabel->setTextSize(bigFontSize);
        inspectorLabel->setRenderer(baseTheme.getRenderer("Label"));
        inspectorLabel->setText("Inspector: ");

        inspectorRefreshButton->setSize(16, 16);
        inspectorRefreshButton->setPosition(
            tgui::bindRight(inspectorLabel) + 20, tgui::bindTop(inspectorLabel));
        inspectorRefreshButton->setRenderer(baseTheme.getRenderer("ApplyButton"));
        inspectorRefreshButton->connect("pressed", getSceneContent);

        inspectorPanel->setRenderer(baseTheme.getRenderer("DarkTransparentPanel"));
        inspectorPanel->setSize("100%", "100% - 30");
        inspectorPanel->setPosition(0, tgui::bindBottom(inspectorLabel) + 30);

        inspectorLeftPanel->setRenderer(baseTheme.getRenderer("DarkTransparentPanel"));
        inspectorLeftPanel->setSize("50%", "100%");
        inspectorLeftPanel->setPosition(0, 0);

        inspectorRightPanel->setRenderer(baseTheme.getRenderer("DarkTransparentPanel"));
        inspectorRightPanel->setSize("50%", "100%");
        inspectorRightPanel->setPosition(tgui::bindRight(inspectorLeftPanel), 0);

        /*inspectorScrollbar->setPosition("&.width - width",
        tgui::bindTop(inspectorPanel)); inspectorScrollbar->setSize("16",
        tgui::bindHeight(inspectorPanel) - tgui::bindHeight(mapNameButton));
        inspectorScrollbar->connect("ValueChanged", scrollPanel, inspectorPanel,
        inspectorScrollbar);
        inspectorScrollbar->setLowValue(inspectorPanel->getSize().y);*/
    }

    void buildEditorSettingsMenu(tgui::Panel::Ptr& settingsPanel, EditorGrid& editorGrid,
        System::Cursor& cursor, tgui::ComboBox::Ptr& editMode, Scene::Scene& scene)
    {
        tgui::Label::Ptr settingsCatLabel = tgui::Label::create();
        tgui::CheckBox::Ptr displayFramerateCheckbox = tgui::CheckBox::create();
        tgui::CheckBox::Ptr enableGridCheckbox = tgui::CheckBox::create();
        tgui::Label::Ptr gridDimensionLabel = tgui::Label::create();
        tgui::EditBox::Ptr gridDimensionXInput = tgui::EditBox::create();
        tgui::EditBox::Ptr gridDimensionYInput = tgui::EditBox::create();
        tgui::Button::Ptr gridDimensionButton = tgui::Button::create();
        tgui::Label::Ptr gridOffsetLabel = tgui::Label::create();
        tgui::EditBox::Ptr gridOffsetXInput = tgui::EditBox::create();
        tgui::EditBox::Ptr gridOffsetYInput = tgui::EditBox::create();
        tgui::Button::Ptr gridOffsetButton = tgui::Button::create();
        tgui::CheckBox::Ptr snapGridCheckbox = tgui::CheckBox::create();
        tgui::Label::Ptr cameraPositionLabel = tgui::Label::create();
        tgui::EditBox::Ptr cameraPositionXInput = tgui::EditBox::create();
        tgui::EditBox::Ptr cameraPositionYInput = tgui::EditBox::create();
        tgui::Button::Ptr cameraPositionBtn = tgui::Button::create();
        tgui::Label::Ptr cameraSizeLabel = tgui::Label::create();
        tgui::EditBox::Ptr cameraSizeInput = tgui::EditBox::create();
        tgui::Button::Ptr cameraSizeBtn = tgui::Button::create();
        tgui::CheckBox::Ptr saveCameraPositionCheckbox = tgui::CheckBox::create();

        settingsPanel->add(settingsCatLabel, "settingsCatLabel");

        settingsPanel->add(displayFramerateCheckbox, "displayFramerateCheckbox");
        settingsPanel->add(enableGridCheckbox, "enableGridCheckbox");
        settingsPanel->add(gridDimensionLabel, "gridDimensionLabel");
        settingsPanel->add(gridDimensionXInput, "gridDimensionXInput");
        settingsPanel->add(gridDimensionYInput, "gridDimensionYInput");
        settingsPanel->add(gridDimensionButton, "gridDimensionButton");
        settingsPanel->add(gridOffsetLabel, "gridOffsetLabel");
        settingsPanel->add(gridOffsetXInput, "gridOffsetXInput");
        settingsPanel->add(gridOffsetYInput, "gridOffsetYInput");
        settingsPanel->add(gridOffsetButton, "gridOffsetButton");
        settingsPanel->add(snapGridCheckbox, "snapGridCheckbox");
        settingsPanel->add(cameraPositionLabel, "cameraPositionLabel");
        settingsPanel->add(cameraPositionXInput, "cameraPositionXInput");
        settingsPanel->add(cameraPositionYInput, "cameraPositionYInput");
        settingsPanel->add(cameraPositionBtn, "cameraPositionBtn");
        settingsPanel->add(cameraSizeLabel, "cameraSizeLabel");
        settingsPanel->add(cameraSizeInput, "cameraSizeInput");
        settingsPanel->add(cameraSizeBtn, "cameraSizeBtn");
        settingsPanel->add(saveCameraPositionCheckbox, "saveCameraPositionCheckbox");

        settingsCatLabel->setPosition(20, 20);
        settingsCatLabel->setTextSize(bigFontSize);
        settingsCatLabel->setRenderer(baseTheme.getRenderer("Label"));
        settingsCatLabel->setText("[ Global Settings ]");

        displayFramerateCheckbox->setPosition(60, tgui::bindBottom(settingsCatLabel) + 20);
        displayFramerateCheckbox->setRenderer(baseTheme.getRenderer("CheckBox"));
        displayFramerateCheckbox->setSize(16, 16);
        displayFramerateCheckbox->setTextSize(mediumFontSize);
        displayFramerateCheckbox->setText("Display Framerate ?");

        enableGridCheckbox->setPosition(60, tgui::bindBottom(displayFramerateCheckbox) + 20);
        enableGridCheckbox->setRenderer(baseTheme.getRenderer("CheckBox"));
        enableGridCheckbox->setSize(16, 16);
        enableGridCheckbox->setTextSize(mediumFontSize);
        enableGridCheckbox->setText("Enabled Grid ?");

        enableGridCheckbox->connect("checked", [&editorGrid, snapGridCheckbox]() {
            editorGrid.enable();
            snapGridCheckbox->enable();
            snapGridCheckbox->getRenderer()->setTextColor(sf::Color(255, 255, 255));
        });

        enableGridCheckbox->connect("unchecked", [&editorGrid, snapGridCheckbox]() {
            editorGrid.disable();
            snapGridCheckbox->getRenderer()->setTextColor(sf::Color(100, 100, 100));
            snapGridCheckbox->uncheck();
            snapGridCheckbox->disable();
        });

        gridDimensionLabel->setPosition(60, tgui::bindBottom(enableGridCheckbox) + 20);
        gridDimensionLabel->setTextSize(mediumFontSize);
        gridDimensionLabel->setRenderer(baseTheme.getRenderer("Label"));
        gridDimensionLabel->setText("Grid Cell Size : ");

        gridDimensionXInput->setPosition(
            tgui::bindRight(gridDimensionLabel) + 20, tgui::bindTop(gridDimensionLabel));
        gridDimensionXInput->setSize(80, mediumFontSize + 4);
        gridDimensionXInput->setRenderer(baseTheme.getRenderer("TextBox"));
        gridDimensionXInput->setText(std::to_string(editorGrid.getCellWidth()));
        gridDimensionXInput->setInputValidator(tgui::EditBox::Validator::UInt);

        gridDimensionYInput->setPosition(
            tgui::bindRight(gridDimensionXInput) + 20, tgui::bindTop(gridDimensionLabel));
        gridDimensionYInput->setSize(80, mediumFontSize + 4);
        gridDimensionYInput->setRenderer(baseTheme.getRenderer("TextBox"));
        gridDimensionYInput->setText(std::to_string(editorGrid.getCellHeight()));
        gridDimensionYInput->setInputValidator(tgui::EditBox::Validator::UInt);

        gridDimensionButton->setPosition(tgui::bindRight(gridDimensionYInput) + 20,
            tgui::bindTop(gridDimensionYInput) + tgui::bindHeight(gridDimensionYInput) / 2
                - tgui::bindHeight(gridDimensionButton) / 2);
        gridDimensionButton->setRenderer(baseTheme.getRenderer("ApplyButton"));
        gridDimensionButton->setSize(16, 16);

        gridDimensionButton->connect(
            "pressed", [gridDimensionXInput, gridDimensionYInput, &editorGrid]() {
                gridDimensionXInput->setRenderer(baseTheme.getRenderer("TextBox"));
                gridDimensionYInput->setRenderer(baseTheme.getRenderer("TextBox"));
                if (Utils::String::isStringInt(gridDimensionXInput->getText().toAnsiString())
                    && Utils::String::isStringInt(gridDimensionYInput->getText().toAnsiString()))
                {
                    std::string xGridSize = gridDimensionXInput->getText().toAnsiString();
                    std::string yGridSize = gridDimensionYInput->getText().toAnsiString();
                    if (stoi(xGridSize) < 2 || stoi(yGridSize) < 2)
                    {
                        editorGrid.setSize(2, 2);
                        gridDimensionXInput->setText("2");
                        gridDimensionYInput->setText("2");
                    }
                    else
                        editorGrid.setSize(stoi(xGridSize), stoi(yGridSize));
                    gridDimensionXInput->setRenderer(baseTheme.getRenderer("TextBox"));
                    gridDimensionYInput->setRenderer(baseTheme.getRenderer("TextBox"));
                    return;
                }
                if (!Utils::String::isStringInt(gridDimensionXInput->getText().toAnsiString()))
                {
                    gridDimensionXInput->setRenderer(baseTheme.getRenderer("InvalidTextBox"));
                }
                if (!Utils::String::isStringInt(gridDimensionYInput->getText().toAnsiString()))
                {
                    gridDimensionYInput->setRenderer(baseTheme.getRenderer("InvalidTextBox"));
                }
            });

        gridOffsetLabel->setPosition(60, tgui::bindBottom(gridDimensionLabel) + 20);
        gridOffsetLabel->setTextSize(mediumFontSize);
        gridOffsetLabel->setRenderer(baseTheme.getRenderer("Label"));
        gridOffsetLabel->setText("Grid Cell Offset : ");

        gridOffsetXInput->setPosition(
            tgui::bindRight(gridOffsetLabel) + 20, tgui::bindTop(gridOffsetLabel));
        gridOffsetXInput->setSize(80, mediumFontSize + 4);
        gridOffsetXInput->setRenderer(baseTheme.getRenderer("TextBox"));
        gridOffsetXInput->setText(std::to_string(editorGrid.getOffsetX()));
        gridOffsetXInput->setInputValidator(tgui::EditBox::Validator::Int);

        gridOffsetYInput->setPosition(
            tgui::bindRight(gridOffsetXInput) + 20, tgui::bindTop(gridOffsetLabel));
        gridOffsetYInput->setSize(80, mediumFontSize + 4);
        gridOffsetYInput->setRenderer(baseTheme.getRenderer("TextBox"));
        gridOffsetYInput->setText(std::to_string(editorGrid.getOffsetY()));
        gridOffsetYInput->setInputValidator(tgui::EditBox::Validator::Int);

        gridOffsetButton->setPosition(tgui::bindRight(gridOffsetYInput) + 20,
            tgui::bindTop(gridOffsetYInput) + tgui::bindHeight(gridOffsetYInput) / 2
                - tgui::bindHeight(gridOffsetButton) / 2);
        gridOffsetButton->setRenderer(baseTheme.getRenderer("ApplyButton"));
        gridOffsetButton->setSize(16, 16);

        gridOffsetButton->connect("pressed", [gridOffsetXInput, gridOffsetYInput, &editorGrid]() {
            if (Utils::String::isStringInt(gridOffsetXInput->getText().toAnsiString())
                && Utils::String::isStringInt(gridOffsetYInput->getText().toAnsiString()))
            {
                std::string xGridOffset = gridOffsetXInput->getText().toAnsiString();
                std::string yGridOffset = gridOffsetYInput->getText().toAnsiString();
                editorGrid.setOffset(stoi(xGridOffset), stoi(yGridOffset));
                gridOffsetXInput->setRenderer(baseTheme.getRenderer("TextBox"));
                gridOffsetYInput->setRenderer(baseTheme.getRenderer("TextBox"));
                return;
            }
            if (!Utils::String::isStringInt(gridOffsetXInput->getText().toAnsiString()))
            {
                gridOffsetXInput->setRenderer(baseTheme.getRenderer("InvalidTextBox"));
            }
            if (!Utils::String::isStringInt(gridOffsetYInput->getText().toAnsiString()))
            {
                gridOffsetYInput->setRenderer(baseTheme.getRenderer("InvalidTextBox"));
            }
        });

        snapGridCheckbox->setPosition(60, tgui::bindBottom(gridOffsetLabel) + 20);
        snapGridCheckbox->setRenderer(baseTheme.getRenderer("DisabledCheckBox"));
        snapGridCheckbox->setSize(16, 16);
        snapGridCheckbox->setTextSize(mediumFontSize);
        snapGridCheckbox->setText("Snap to Grid ?");
        snapGridCheckbox->disable();

        snapGridCheckbox->connect("checked", [&editorGrid, &cursor, editMode, &scene]() {
            cursor.setConstraint(
                [editMode, &editorGrid, &scene](System::Cursor* cursor) {
                    if (editMode->getSelectedItem() == "LevelSprites"
                        || editMode->getSelectedItem() == "Collisions"
                        || editMode->getSelectedItem() == "SceneNodes")
                    {
                        Transform::UnitVector pixelCamera
                            = scene.getCamera()->getPosition().to<Transform::Units::ScenePixels>();
                        return editorGrid.getClosestIntersection(
                            cursor->getX(), cursor->getY(), pixelCamera.x, pixelCamera.y);
                    }
                    else
                    {
                        return System::Constraints::Default(cursor);
                    }
                },
                [&cursor]() { return cursor.isPressed(sf::Mouse::Button::Left); });
        });

        snapGridCheckbox->connect(
            "unchecked", [&cursor]() { cursor.setConstraint(System::Constraints::Default); });

        cameraPositionLabel->setPosition(60, tgui::bindBottom(snapGridCheckbox) + 20);
        cameraPositionLabel->setTextSize(mediumFontSize);
        cameraPositionLabel->setRenderer(baseTheme.getRenderer("Label"));
        cameraPositionLabel->setText("Camera Position : ");

        cameraPositionXInput->setPosition(
            tgui::bindRight(cameraPositionLabel) + 20, tgui::bindTop(cameraPositionLabel));
        cameraPositionXInput->setSize(80, mediumFontSize + 4);
        cameraPositionXInput->setRenderer(baseTheme.getRenderer("TextBox"));
        cameraPositionXInput->setText(std::to_string(scene.getCamera()->getPosition().x));
        cameraPositionXInput->setInputValidator(tgui::EditBox::Validator::Float);

        cameraPositionYInput->setPosition(
            tgui::bindRight(cameraPositionXInput) + 20, tgui::bindTop(cameraPositionLabel));
        cameraPositionYInput->setSize(80, mediumFontSize + 4);
        cameraPositionYInput->setRenderer(baseTheme.getRenderer("TextBox"));
        cameraPositionYInput->setText(std::to_string(scene.getCamera()->getPosition().y));
        cameraPositionYInput->setInputValidator(tgui::EditBox::Validator::Float);

        cameraPositionBtn->setPosition(tgui::bindRight(cameraPositionYInput) + 20,
            tgui::bindTop(cameraPositionYInput) + tgui::bindHeight(cameraPositionYInput) / 2
                - tgui::bindHeight(cameraPositionBtn) / 2);
        cameraPositionBtn->setRenderer(baseTheme.getRenderer("ApplyButton"));
        cameraPositionBtn->setSize(16, 16);

        cameraSizeLabel->setPosition(60, tgui::bindBottom(cameraPositionLabel) + 20);
        cameraSizeLabel->setTextSize(mediumFontSize);
        cameraSizeLabel->setRenderer(baseTheme.getRenderer("Label"));
        cameraSizeLabel->setText("Camera Size : ");

        cameraSizeInput->setPosition(
            tgui::bindRight(cameraSizeLabel) + 20, tgui::bindTop(cameraSizeLabel));
        cameraSizeInput->setSize(80, mediumFontSize + 4);
        cameraSizeInput->setRenderer(baseTheme.getRenderer("TextBox"));
        cameraSizeInput->setText(std::to_string(scene.getCamera()->getSize().y / 2));
        cameraSizeInput->setInputValidator(tgui::EditBox::Validator::Float);

        cameraSizeBtn->setPosition(tgui::bindRight(cameraSizeInput) + 20,
            tgui::bindTop(cameraSizeInput) + tgui::bindHeight(cameraSizeInput) / 2
                - tgui::bindHeight(cameraSizeBtn) / 2);
        cameraSizeBtn->setRenderer(baseTheme.getRenderer("ApplyButton"));
        cameraSizeBtn->setSize(16, 16);

        cameraPositionBtn->connect(
            "pressed", [cameraPositionXInput, cameraPositionYInput, &scene]() {
                float camX = std::stof(cameraPositionXInput->getText().toAnsiString());
                float camY = std::stof(cameraPositionYInput->getText().toAnsiString());
                scene.getCamera()->setPosition(Transform::UnitVector(camX, camY));
            });

        cameraSizeBtn->connect("pressed", [cameraSizeInput, &scene]() {
            float camSize = std::stof(cameraSizeInput->getText().toAnsiString());
            scene.getCamera()->setSize(camSize);
        });

        saveCameraPositionCheckbox->setPosition(60, tgui::bindBottom(cameraSizeInput) + 20);
        saveCameraPositionCheckbox->setRenderer(baseTheme.getRenderer("CheckBox"));
        saveCameraPositionCheckbox->setSize(16, 16);
        saveCameraPositionCheckbox->setTextSize(mediumFontSize);
        saveCameraPositionCheckbox->setText("Save Camera Position ?");
    }

    void buildEditorSpritesMenu(
        tgui::Panel::Ptr& spritesPanel, tgui::Scrollbar::Ptr& spritesScrollbar, Scene::Scene& scene)
    {
        tgui::Label::Ptr spritesCatLabel = tgui::Label::create();

        spritesPanel->add(spritesCatLabel, "spritesCatLabel");

        spritesCatLabel->setPosition(20, 20);
        spritesCatLabel->setTextSize(bigFontSize);
        spritesCatLabel->setRenderer(baseTheme.getRenderer("Label"));
        spritesCatLabel->setText("[ Sprites Settings ]");

        loadSpriteFolder(scene, spritesPanel, spritesCatLabel, "", spritesScrollbar);
    }

    void buildEditorObjectsMenu(tgui::Panel::Ptr& objectsPanel, tgui::Panel::Ptr& requiresPanel,
        tgui::Scrollbar::Ptr& objectsScrollbar, Scene::Scene& scene)
    {
        tgui::Label::Ptr objectsCatLabel = tgui::Label::create();

        objectsPanel->add(objectsCatLabel, "objectsCatLabel");

        objectsCatLabel->setPosition(20, 20);
        objectsCatLabel->setTextSize(bigFontSize);
        objectsCatLabel->setRenderer(baseTheme.getRenderer("Label"));
        objectsCatLabel->setText("[ Objects Settings ]");

        buildObjectTab(scene, objectsPanel, requiresPanel, baseTheme, objectsScrollbar);
    }

    void buildObjectCreationMenu(tgui::Panel::Ptr& mainPanel)
    {
        tgui::Panel::Ptr requiresPanel = tgui::Panel::create();
        tgui::Button::Ptr requiresCloseButton = tgui::Button::create();
        tgui::Label::Ptr requiresTitleLabel = tgui::Label::create();
        tgui::Panel::Ptr requiresPanelContent = tgui::Panel::create();

        mainPanel->add(requiresPanel, "requiresPanel");
        requiresPanel->add(requiresPanelContent, "content");
        requiresPanel->add(requiresTitleLabel, "label");
        requiresPanel->setRenderer(baseTheme.getRenderer("DarkTransparentPanel"));
        requiresPanel->setSize("33%", "66%");
        requiresPanel->setPosition("33%", "17%");
        requiresPanel->hide();

        requiresCloseButton->setRenderer(baseTheme.getRenderer("CloseButton"));
        requiresCloseButton->setSize("32", "32");
        requiresCloseButton->setPosition("100% - 40", "8");
        requiresCloseButton->connect("pressed", [requiresPanel]() { requiresPanel->hide(); });
        requiresPanel->add(requiresCloseButton, "requiresCloseButton");

        requiresTitleLabel->setPosition(30, 15);
        requiresTitleLabel->setTextSize(bigFontSize);
        requiresTitleLabel->setRenderer(baseTheme.getRenderer("Label"));
        requiresTitleLabel->setText("Object builder Window");

        requiresPanelContent->setRenderer(baseTheme.getRenderer("TransparentPanel"));
        requiresPanelContent->setSize("100% - 2", "100% - 62");
        requiresPanelContent->setPosition(0, 60);
    }

    std::vector<Input::InputButtonState> bitsetToInputStates(
        Types::FlagSet<Input::InputButtonState> states)
    {
        std::vector<Input::InputButtonState> returnStates;
        for (auto state : { Input::InputButtonState::Hold, Input::InputButtonState::Idle,
                 Input::InputButtonState::Pressed, Input::InputButtonState::Released })
        {
            if (states & state)
                returnStates.push_back(state);
        }
        return returnStates;
    }
    void buildKeyBindingMenu(
        tgui::Panel::Ptr& keybindingPanel, tgui::Scrollbar::Ptr& keybindingScrollbar)
    {
        keybindingPanel->removeAllWidgets();

        tgui::Label::Ptr keybindingCatLabel = tgui::Label::create();

        keybindingPanel->add(keybindingCatLabel, "keybindingCatLabel");

        keybindingCatLabel->setPosition(20, 20);
        keybindingCatLabel->setTextSize(bigFontSize);
        keybindingCatLabel->setRenderer(baseTheme.getRenderer("Label"));
        keybindingCatLabel->setText("[ Keybinding Settings ]");

        vili::ComplexNode& keybinding = Config::Config.at("KeyBinding");
        unsigned int yPos = 80;
        for (vili::ComplexNode* context : keybinding.getAll<vili::ComplexNode>())
        {
            tgui::Label::Ptr contextLbl = tgui::Label::create();
            keybindingPanel->add(contextLbl);
            contextLbl->setPosition(20, yPos);
            contextLbl->setTextSize(bigFontSize);
            contextLbl->setRenderer(baseTheme.getRenderer("Label"));
            contextLbl->setText(context->getId());

            yPos += 70;

            for (vili::DataNode* action : keybinding.at(context->getId()).getAll<vili::DataNode>())
            {
                tgui::Button::Ptr actionBtn = tgui::Button::create();
                keybindingPanel->add(actionBtn);
                actionBtn->setPosition(60, yPos);
                actionBtn->setSize("20%", 30);
                actionBtn->setRenderer(baseTheme.getRenderer("Button"));
                actionBtn->setText(action->getId());
                actionBtn->setTextSize(mediumFontSize);

                Input::InputCondition keyGen;
                keyGen.setCombinationCode(action->get<std::string>());
                tgui::Layout xPos = tgui::bindRight(actionBtn) + 30;
                unsigned int kIndex = 0;
                for (auto& key : keyGen.getCombination())
                {
                    std::string keyName = key.first->getButton()->getName();
                    const std::string stateName
                        = Input::inputButtonStateToString(bitsetToInputStates(key.second)[0]);
                    if (Utils::String::contains(keyName, "NumPad"))
                    {
                        System::Path numImgPath("Sprites/Keys/Keyboard/Key_Num.png");
                        keyName = Utils::String::replace(keyName, "NumPad", "");
                        if (numImgPath.find() != "")
                        {
                            tgui::Picture::Ptr numImg = tgui::Picture::create();
                            numImg->setTexture(numImgPath.find());
                            numImg->setPosition(xPos, yPos - 35);
                            keybindingPanel->add(numImg);
                            xPos = xPos + 100;
                        }
                        else
                        {
                            tgui::Label::Ptr numLbl = tgui::Label::create();
                            numLbl->setPosition(xPos, yPos);
                            numLbl->setTextSize(mediumFontSize);
                            numLbl->setRenderer(baseTheme.getRenderer("Label"));
                            numLbl->setText("(NumPad)");
                            keybindingPanel->add(numLbl);
                            xPos = xPos + 100;
                        }
                    }
                    System::Path keyImgPath("Sprites/Keys/Keyboard/Key_" + keyName + ".png");
                    System::Path stateImgPath("Sprites/Keys/Keyboard/" + stateName + ".png");
                    if (kIndex > 0)
                    {
                        const tgui::Label::Ptr addSymbol = tgui::Label::create();
                        keybindingPanel->add(addSymbol);
                        contextLbl->setPosition(xPos - 50, yPos - 40);
                        contextLbl->setTextSize(bigFontSize * 3);
                        contextLbl->setRenderer(baseTheme.getRenderer("Label"));
                        contextLbl->setText("+");
                    }
                    if (keyImgPath.find() != "")
                    {
                        tgui::Picture::Ptr keyImg = tgui::Picture::create();
                        keyImg->setTexture(keyImgPath.find());
                        keyImg->setPosition(xPos, yPos - 35);

                        keybindingPanel->add(keyImg);
                    }
                    else
                    {
                        tgui::Label::Ptr keyLbl = tgui::Label::create();
                        keybindingPanel->add(keyLbl);
                        keyLbl->setPosition(xPos + ((kIndex > 0) ? 15 : 0), yPos);
                        keyLbl->setTextSize(bigFontSize);
                        keyLbl->setRenderer(baseTheme.getRenderer("Label"));
                        keyLbl->setText(keyName);
                    }
                    if (stateImgPath.find() != "")
                    {
                        tgui::Picture::Ptr stateImg = tgui::Picture::create();
                        stateImg->setTexture(stateImgPath.find());
                        stateImg->setPosition(xPos, yPos - 35);

                        keybindingPanel->add(stateImg);
                    }
                    else
                    {
                        tgui::Label::Ptr stateLbl = tgui::Label::create();
                        keybindingPanel->add(stateLbl);
                        stateLbl->setPosition(xPos + ((kIndex > 0) ? 15 : 0), yPos - 20);
                        stateLbl->setTextSize(mediumFontSize);
                        stateLbl->setRenderer(baseTheme.getRenderer("GreenLabel"));
                        stateLbl->setText(stateName);
                    }
                    kIndex += 1;
                    xPos = xPos + 150;
                }
                yPos += 100;
            }
        }

        keybindingScrollbar->setMaximum(yPos + 10);
    }
} // namespace obe::Editor::GUI
