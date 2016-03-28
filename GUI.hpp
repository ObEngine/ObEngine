#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <sstream>
#include <map>
#include <tuple>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <functional>
#include <typeinfo>
#include <fstream>
#include "dirent.h"
#include "DataParser.hpp"
#include "Functions.hpp"
#include <gl/GL.h>


//Finir updatePositions penser a aussi update les absolutes s'occuper de Write updatePositions et Droplist Updatepositions et les autre widget
//bien gérer le move

class Color
{
public:
	int r;
	int g;
	int b;
	int a;

	Color();
	Color(sf::Color color);
	Color& operator=(sf::Color const& color);
	sf::Color getSfColor();
};

namespace GUI
{
		enum ContainerMovement
		{
			ControlBar,
			Total,
			Fixed,
			All
		};
		enum LoadingBarDirection
		{
			Vertical,
			Horizontal
		};
		enum ButtonModeWhenPressed
		{
			StayActivated,
			NotStayingActived
		};
		enum HorizontalAlignment
		{
			Center,
			Left,
			Right
		};
		enum Display
		{
			WidgetContained,
			Text,
			Sprite,
			Shape
		};
		enum ButtonEvent
		{
			None,
			Hover,
			Clicked,
			Pressed
		};
	class Widget
	{
	protected:
		DataObject* attributes;
		static std::vector<Widget*> vectWidgets;
		static std::map<std::string, Widget*> mapWidgets;
		std::string ID;
		std::string widgetType;
		std::string widgetStyle = "DEFAULT";
		std::map<std::string, sf::Texture> widgetTextures;
		std::vector<sf::Sprite> sprites;
		std::vector<sf::Text> text;
		std::vector<Widget*> widgetsContained;
		std::vector<sf::Shape*> shapes;
		std::deque<float> posX;
		std::deque<float> posY;
		std::vector<float> absolutesX;
		std::vector<float> absolutesY;
		std::vector<Display> selector;
		int posContainerX = 0;
		int posContainerY = 0;
		int containerWidth;
		int containerHeight;

		bool LeftClickReleased = true;
		bool rightClickReleased = true;
		bool leftClicked = false;
		bool rightClicked = false;
		bool displayed = true;

		Widget(std::string ID, int posX, int posY, std::string style);
		~Widget();
		virtual void setTexture();
		//sf::Text* setTextRect(sf::Text* text);
		void addContainedItem(DataObject* containedItem);

		/*template <typename T> sf::Rect<int> createSubRect(T* drawable)
		{
			sf::Rect<float> rect = drawable->getGlobalBounds();
			sf::Rect<int> newRect;
			newRect.left = rect.left;
			newRect.width = rect.width;
			newRect.top = rect.top;
			newRect.height = rect.height;
			/*if (rect.top > posContainerY + containerHeight || rect.left > posContainerX + containerWidth)
			{
				newRect.width = 0;
				newRect.height = 0;
			}
			else
			{
				if (rect.top + rect.height > posContainerY + containerHeight)
				{
					newRect.height = rect.height - (rect.top + rect.height - (posContainerY + containerHeight));
				}
				if (rect.top < posContainerY)
				{
					newRect.top = posContainerY;
				}

				if (rect.left + rect.width > posContainerX + containerWidth)
				{
					newRect.width = rect.width - (rect.left + rect.width - (posContainerX + containerWidth));
				}
				if (rect.left < posContainerX)
				{
					newRect.left = posContainerX;
				}
			}
			return newRect;
		}*/

		template <typename T> void createAttribute(std::string name, T& attribute, std::string type)
		{
			attributes->createComplexAttribute(convertPath(ID), name);
			attributes->createBaseAttribute(convertPath(ID + "/" + name), "address", "str", pointerToString(&attribute));
			attributes->createBaseAttribute(convertPath(ID + "/" + name), "type", "str", type);

			DataParser parser = DataParser();
			parser.pushDataObject(attributes);
			parser.createBaseAttribute(ID, ID + "/" + name, "value", (attribute));
		}

	public:

		bool isClicked(sf::Event& evnt, bool leftClick, bool rightClick);
		bool isClickedOutside(sf::Event& evnt, bool leftClick, bool rightClick);
		bool isRectClicked(sf::Event& evnt, sf::Rect<float> rect, bool leftClick, bool rightClick);
		bool isRectClickedOutside(sf::Event& evnt, sf::Rect<float> rect, bool leftClick, bool righClick);
		bool isRectHovering(sf::Event& evnt, sf::Rect<float> rect);
		bool isHovering(sf::Event& evnt);

		void autoLoad();
		virtual void setPosition(int x, int y);
		virtual void updatePositions();
		void setSpritesPositions();
		virtual void move(float x, float y);
		std::string getID();
		std::string getWidgetType();
		std::string getWidgetStyle();
		virtual void update(sf::Event& evnt);
		virtual void clicked();//a virer
		sf::Rect<float> getRect();
		int getRelativePosX();
		int getRelativePosY();
		bool getDisplayed();
		virtual void setDisplayed(bool set);
		virtual void setAbsolute(int X, int Y);
		virtual void updatePosContainer(int widgetContainerX, int widgetContainerY);
		void containerChangePos(int x, int y);
		void updateAbsolute();
		virtual void updateTexture(sf::Event& evnt);
		virtual void draw(sf::RenderWindow *GUI);
		virtual void updateAttributes();
		virtual std::map<std::string, std::function<void()>> getFunctions();
		virtual DataObject* getDataObject();
		void addWidgetContained(Widget* widget);

		void setTextureMap(sf::Sprite* sprite, std::string key);

		void removeWidget();

		template <typename T>
		static T* getWidgetByID(std::string ID)
		{
			try
			{	
				return dynamic_cast<T*>(mapWidgets[ID]);
			}
			catch (const std::bad_cast& e)
			{
				std::cout << e.what() << std::endl;
				return NULL;
			}
		}

		template <typename T> static std::vector<T*> getWidgets(std::string widgetType)
		{
			std::vector<T*> vect;
			for (auto ite = vectWidgets.begin(); ite != vectWidgets.end(); ite++)
			{
				if ((*ite)->widgetType == widgetType)
					vect.push_back(dynamic_cast<T*>(*ite));
			}
			return vect;
		}

		template <typename T> static sf::Rect<float> getRectFromGroup(std::vector<T*> widgets)
		{
			//GUI::Widget first = dynamic_cast<Widget*>()
			sf::Rect<float> rect(widgets.front()->getRect().left, widgets.front()->getRect().top, widgets.front()->getRect().left, widgets.front()->getRect().top);
			int currX;
			int currXPlusWidth;

			int currY;
			int currYPlusHeight;
			for (int i = 0; i < widgets.size(); i++)
			{
				if (widgets[i]->getDisplayed())
				{
					currX = widgets[i]->getRect().left;
					currXPlusWidth = currX + widgets[i]->getRect().width;
					if (currX < rect.left)
					{
						rect.left = currX;
					}
					if (currXPlusWidth > rect.left)
					{
						rect.width = currXPlusWidth;
					}

					currY = widgets[i]->getRect().top;
					currYPlusHeight = currY + widgets[i]->getRect().height;
					if (currY < rect.top)
					{
						rect.top = currY;
					}
					if (currYPlusHeight > rect.height)
					{
						rect.height = currYPlusHeight;
					}
				}
			}
			return rect;
		}
	};

	class Label : public Widget
	{
	protected:
		std::string labelText;
		std::string previousText;
		sf::Font font;
		std::string fontString = "arial.ttf";
		int fontSize = 15;
		Color fontColor;
		sf::Text::Style fontStyle;
		virtual void updateTexture(sf::Event& evnt);
		virtual void setTexture();

	public:
		Label(std::string ID, int posX, int posY, std::string text, std::string font, int fontSize, sf::Color color, sf::Text::Style fontStyle);
		void resetFontVars(std::string text, std::string font, int fontSize, sf::Color color, sf::Text::Style fontStyle);
		void setFont(std::string font);
		void setText(std::string text);
		void setFontSize(int fontSize);
		void setFontColor(sf::Color color);
		void setFontStyle(sf::Text::Style fontStyle);
		void centerInRect(sf::Rect<float> rect);
		std::string getString();
		std::string getFontName();
		int getfontSize();
		sf::Color getColor();
		virtual void updateAttributes();
		std::string* getHook();
	};

	class NumericSlider : public Widget
	{
	protected:
		sf::Font font;
		std::string fontString;
		int number;
		int min;
		int max;
		int range;
		int currentShift;
		float valuePerMove;
		std::string nameImageSlider = "slider.png";
		std::string nameImageCursor = "cursor.png";
		int defaultCursorValue;
		bool isHoldingCursor = false;

		virtual void setTexture();
		virtual void updateTexture(sf::Event& evnt);
		virtual void updatePositions();
		void isHolding(sf::Event& evnt);

	public:
		NumericSlider(std::string ID, int posX, int posY, int minValue, int maxValue, int defaultCursorValue, std::string style);
		int getValue();
	};

	class TextInput : public Widget
	{
	protected:
		Label* labelText;
		std::string inputText;
		std::string *visibleText = &inputText;
		std::string nameImageBackground = "background.png";
		std::string nameImageBackgroundFocus = "backgroundfocus.png";
		std::string nameImageOutline = "outline.png";
		bool hasFocus = false;
		bool textLarger = false;
		bool enterJustPressed = false;
		clock_t timeBefore;
		sf::Font fontCharMove;
		sf::Text charToMove;
		int currentCursorOffset = 0;
		int cursorPosition = 0;
		int timeCursorDiplayed = 900;
		bool cursorKeyReleased = true;
		sf::Clock cursorElapsedTime;
		int previousChar = 0;
		int previousWidth;
		bool hasStartTimer = false;
		bool unlockKeyRepeater = true;

		virtual void setTexture();
		virtual void updateTexture(sf::Event& evnt);
		void setFocus();
		void loseFocus();
		void updateTextPositionX();
		virtual void updatePositions();
		void moveCursorRight();
		void moveCursorLeft();
		void moveCursorTextChanged(int enteredOrDeleted);

	public:
		TextInput(std::string ID, int posX, int posY, std::string font, int fontSize, sf::Color fontColor, std::string style, std::string defaultText);
		TextInput(std::string ID, int posX, int posY, std::string style, GUI::Label* text);

		std::string getText();
		void setText(std::string string);
		bool getEnterPressed();
		bool getHasFocus();
		Label* getLabel();
	};


	class Button : public Widget
	{
	protected:
		std::function<void(DataObject*)> function;
		std::function<void()> voidFunction;
		DataObject* parameters;
		Label* buttonLabel = NULL;
		GUI::ButtonEvent prevState = GUI::ButtonEvent::None;
		GUI::ButtonEvent currState = GUI::ButtonEvent::None;
		bool hoveringEnable = false;
		bool pushingEnable = false;
		bool idleEnable = false;
		bool hasText = false;
		bool functionBinded = false;
		bool voidFunctionBinded = false;
		bool textCentered = false;
		int posTextX;
		int posTextY;
		std::string nameImagePushed = "pushed.png";
		std::string nameImageIdle = "idle.png";
		std::string nameImageHover = "hover.png";

		virtual void updateTexture(sf::Event& evnt);
		virtual void setTexture();
		virtual void clicked();
		void setUnpushed();
		void setPushed();

	public:
		Button(std::string ID, int posX, int posY, std::string style, bool pushingEnable, bool hoveringEnable);
		void setText(std::string text, std::string font, sf::Color fontColor, int fontSize, bool centered, int relativeToButtonX = 0, int relativeToButtonY = 0, sf::Text::Style fontStyle = sf::Text::Style::Regular);
		void changeText(std::string text);
		void setDefaultText();
		void setLabelText(Label* text);
		bool getJustClicked();
		std::string getString();
		bool isPressed();
		void setTextureHover(sf::Texture& texture);
		void setTextureIdle(sf::Texture& texture);
		void setTexturePushed(sf::Texture& texture);
		virtual void setDisplayed(bool displayed);
		virtual void updatePositions();
		void bindFunction(std::function<void(DataObject*)> function, std::string parameters);
		void bindFunction(std::function<void()> function);
		void updateAttributes();
		Label* getLabel();//Return Label's button if the button has text, return NULL if not.
		GUI::ButtonEvent* getHook();
		virtual std::map<std::string, std::function<void()>> getFunctions();
	};

	class NumericInput : public Widget
	{
	protected:
		std::string inputValue;
		std::string* visibleValue = &inputValue;
		Label* labelText;
		Button* arrowTop;
		Button* arrowBot;
		int value;

		std::string nameImageBackground = "background.png";
		std::string nameImageArrowTop = "arrowTop.png";
		std::string nameImageArrowBot = "arrowBot.png";
		std::string nameImageOutline = "outline.png";
		std::string nameImageCursor = "cursor.png";
		std::string nameImageBackgroundFocus = "backgroundfocus.png";
		bool hasFocus = false;
		clock_t timeBefore;
		bool arrowUpReleased = true;
		bool arrowDownReleased = true;

		virtual void setTexture();
		virtual void updateTexture(sf::Event& evnt);
		virtual void updatePositions();
		void setFocus();
		void loseFocus();
		void checkArrowPressed(sf::Event& evnt);
		void setTextPosition();

	public:
		NumericInput(std::string ID, int posX, int posY, int defaultValue, std::string style, std::string font, sf::Color fontColor, int fontSize);
		NumericInput(std::string ID, int posX, int posY, Label* text, std::string style);

		int getValue();
		void setValue(int value);
	};

	class Checkbox : public Widget
{

	protected:
		GUI::Label* checkboxLabel = NULL;
		std::string nameImageChecked = "selected.png";
		std::string nameImageUnchecked = "unselected.png";
		bool checked = false;
		bool hasText = false;
		int posTextX;
		int posTextY;
		bool textCentered = false;
		bool previousValue = false;
		bool hasChanged = false;
		virtual void setTexture();
		virtual void clicked();
		virtual void updatePositions();

	public:
		Checkbox(std::string ID, int posX, int posY, std::string style, bool checked);
		bool isChecked();
		void setUnchecked();
		void setChecked();
		bool getToggled();
		bool* getHook();
		void setTextureChecked(sf::Texture& texture);
		void setTextureUnchecked(sf::Texture& texture);

		virtual void updateTexture(sf::Event& evnt);
		virtual void updateAttributes();
		void setText(std::string text, std::string font, sf::Color fontColor, int fontSize, bool centered, int relativeX = 0, int relativeY = 0, sf::Text::Style fontStyle = sf::Text::Regular);

	};

	class RadioButton : public Checkbox // Correction: deux radios du même groupe ne peuvent pas être initialement cochés
	{
	protected:
		std::string value;
		std::string group;
		void clicked();

	public:
		RadioButton(std::string ID, int posX, int posY, std::string value, std::string group, std::string style, bool isChecked);
		void setValue(std::string newValue);//à faire
		void setChecked();
		void setUnchecked();
		std::string getGroup();
		std::string getValue(); //à faire
		static std::string getCurrentSelected(std::string group);
		static bool getGroupToggled(std::string group);
		static std::vector<RadioButton*> getRadioButtonGroup(std::string group);
	};

	
	class WidgetContainer;

	class Tab : public Widget 
	{
	protected:
		std::vector<RadioButton*> tabCheckboxes;
		std::vector<WidgetContainer*> tabContainer;
		std::vector<std::string> tabsNames;
		std::string nameImageChecked = "tabselected.png";
		std::string nameImageUnchecked = "tabunselected.png";

		virtual void setTexture();
		virtual void updateTexture(sf::Event& evnt);
		virtual void updatePositions();

	public:
		Tab(std::string ID, int posX, int posY, int charSize, std::string font, sf::Color fontColor, std::vector<std::string> tabsNames, std::vector<WidgetContainer*> tabs, std::string style);

		void setCurrentTab(std::string tabName);
		std::string getCurrentTab();
		void addTab(std::string tabName, WidgetContainer* newTab);
		void removeTab(std::string tabName);
		virtual void setDisplayed(bool displayed);
	};

	class Movable;

	class ScrollBar : public Widget
	{
		//Compose au de deux fl�che, une haut une bas, et d'une barre dans laquelle peut glisser un rectangle
		//Gerer la taille du scroller en fonction de la taille du scrolling
	protected:
		std::string nameImageBar = "bar.png";
		int size;
		int previousScrollerX;
		int previousScrollerY;
		float movePerPixel = 1;
		int minHeightBar;
		bool hasBeenResized = false;

		int minY;
		int maxY;
		int minX;
		int maxX;

		std::vector<Button*> arrows;
		Movable* scroller;
		std::vector<Widget*> widgetsLinked;
		WidgetContainer* containerLinked;
		bool hasContainer = false;

		virtual void setTexture();
		virtual void updateTexture(sf::Event& evnt);
		
		virtual void updatePositions();
		void replaceScroller(int maxY);//
		void replaceScrollerWidgets(int maxY, int spriteHeight, int spriteTop, int scrollerHeight);
	public:
		ScrollBar(std::string ID, int posX, int posY, int size, int minHeightBar, bool needButtons, std::vector<Widget*> widgetsToMove, std::string style);
		ScrollBar(std::string ID, int posX, int posY, int size, int minHeightBar, bool needButtons, WidgetContainer* widgetContainerLinked, std::string style);

		void computeDynamicScroll();//Compute the size and the speed of the scrollbar in function of the widgets linked
		void scrollToBottom();//Scrolls to bottom
		void scrollToTop();//Scrolls to Top
		bool isMaxBot();
	};

	class LoadingBar : public Widget //Am�liorations possibles -> coins arrondis, d�grad�...
	{
	protected:
		std::string nameImageBorder = "border.png";
		std::string nameImageFiller = "filler.png";
		std::string fillingType;
		int sideBordersWidth;
		int TopBotBordersHeight;
		int pixelsInPercent;
		int fillingInPixels = 0;
		int fillingInPercentage = 0;
		double currentFillingPixels = 0;
		double delay = 0.02;
		double currentPixelsPerDraw = 0;
		double timeBefore = 0;
		double timeToFill = 0.5;
		virtual void setTexture();

	public:
		LoadingBar(std::string ID, int posX, int posY, std::string fillingType, std::string style, int sideBordersWidth, int TopBotBordersHeight);
		void fill(int percentage, double timeToFill = 0.5);//permet de remplir la barre jusqu'� un certain pourcentage
		virtual void draw(sf::RenderWindow* GUI);
		void addFilling(int percentageToAdd);//Permet d'ajouter un certain pourcentage au remplissage actuel de la barre
		int getFilling();
		bool isFilled();
	};

	class Droplist : public Widget
	{
	protected:
		std::vector<std::string> list;
		std::vector<Button*> buttons;
		std::string nameImageFirstPushed = "titlepushed.png";
		std::string nameImageFirstIdle = "titleidle.png";
		std::string nameImageFirstHover = "titlehover.png";
		std::string nameImageIdle = "elementidle.png";
		std::string nameImagePushed = "elementpushed.png";
		std::string nameImageHover = "elementhover.png";
		std::string elementClicked;
		sf::Color idle;
		sf::Color hover;
		int currentIndex;
		int previousIndex;
		bool extended = false;
		bool droplistMenu = false;
		bool isJustExtended = false;
		bool isExtendable;
		int charSize;
		std::string font;
		bool addedElement;
		virtual void updateTexture(sf::Event& evnt);
		virtual void updatePositions();
		virtual void setTexture();
		void changeTitle(std::string newTitle);

	public:
		Droplist(std::string ID, int posX, int posY, int charSize, bool dropListMenu, std::string style, std::string title, std::vector<std::string> content, std::string font, sf::Color fontColorIdle, sf::Color fontColorHover);
		Droplist(std::string ID, int posX, int posY, bool dropListMenu, std::string title, std::vector<Button*> buttons, std::string style);
		void addOption(std::string str, int position);
		void addDefaultOption();
		int getNbElement();
		void setUnfold();
		void setFoldUp();
		bool isExtended();
		std::string getCurrentSelected();
		bool hasChanged();
		bool getJustExtended();
		std::string getElementClicked();
		void setSelected(int index);
		virtual std::map<std::string, std::function<void()>> getFunctions();
		int* getHook();
	};
	class Dropbox;
	class Movable : public Widget
	{
	protected:
		Dropbox* currentContainer = NULL;
		std::string nameImage = "texture.png";
		int width;
		int height;
		int marginLeft;
		int marginTop;
		int posXText;
		int posYText;
		int currentShiftX;
		int currentShiftY;
		int marginLeftContainer;
		int marginTopContainer;

		bool isHolding = false;
		bool hasText = false;
		bool hasSprite = false;
		bool needContainer = false;
		bool textHasPos = false;

		int posXMin;
		int posXMax;
		int posYMin;
		int posYMax;
		bool hasPosConstraints = false;
		bool hasVerticalConstaint = false;
		bool hasHorizontalConstraint = false;

		std::string fullText;
		std::string displayedText;

		sf::Font font;
		//sf::Text text;
		//sf::RectangleShape rectangle;
		//sf::Color backgroundColor = sf::Color::White;
		virtual void updatePositions();

		virtual void setTexture();

	public:
		Movable(std::string ID, int posX, int posY, std::string style);
		Movable(std::string ID, Dropbox* container, int marginLeftContainer, int marginTopContainer, std::string style);

		void setPosConstraints(int posXMin, int posXMax, int posYMin, int posYMax);
		void setMovementConstraints(bool verticalConstraint, bool horizontalConstraint);
		void setText(std::string font, std::string text, int characSize, sf::Color color);
		void setTextWithPos(std::string font, std::string text, int characSize, sf::Color color, int posX, int posY, bool isResized = false);
		void setPicture(std::string texturePath, int marginLeft, int marginTop);
		void resize(int width, int height);
		void setCurrentDropboxContainer(Dropbox* dropbox);
		void containerMove(int x, int y);
		bool getHolding();
		//void scaleSprite(float scaleX, float scaleY);

		virtual void updateTexture(sf::Event& evnt);
		void holding(sf::Event& evnt);
		void releasing(sf::Event& evnt);

	};

	class Dropbox : public Widget
	{
	protected:
		Movable* currentMovable = NULL;
		bool containMovable = false;
		std::string nameImageBox = "box.png";

	public:
		Dropbox(std::string ID, int posX, int posY, std::string style);
		virtual void setTexture();
		void setCurrentMovable(Movable* movable, int posX, int posY);
		bool getContainMovable();
		void setContainMovable(bool contain);
		Movable* getMovable();
		virtual void updateTexture(sf::Event& evnt);
	};



	class WidgetContainer
	{
	protected:
		int posX;
		int posY;
		int width;
		int height;
		int widthControlBar;
		int heightControleBar;
		int currentShiftX;
		int currentShiftY;
		bool holding = false;
		bool justReleased = false;
		bool displayed = true;
		std::vector<Widget*> widgetIDContainer;
		GUI::ContainerMovement movable;
		std::string containerName;
		std::vector<std::tuple<sf::Texture, int, int>> decoTextures;
		sf::RectangleShape background;
		bool hasBackground = false;
		sf::Event* evnt;

	public:
		WidgetContainer(std::string ID, int posX, int posY, int width, int height, GUI::ContainerMovement movable, int widthControlBar, int heightControleBar, sf::Event* evnt);
		~WidgetContainer();
		void addWidget(Widget* widget);
		void addNewWidget(Widget* widget);
		bool removeWidget(std::string ID, bool freeMemory = true);
		void removeAllWidget(bool freeMemory = true);
		void remove();
		void updateAll(sf::Event& evnt);
		void updateAttributes(std::string widgetID);
		Widget* getWidgetByInt(int i);
		std::vector<Dropbox*> getDropboxes();
		void resize(int width, int height);
		int getNbWidget();
		void drawAll(sf::RenderWindow * GUI);
		bool getClicked();
		bool getReleased();
		std::vector<Widget*> getWidgets();
		sf::Rect<float> getRect();
		void setHolding();
		void move(int x, int y);
		void setPosition(int posX, int posY);
		void autoMove();
		void pushTexture(int posX, int posY, sf::Texture texture, int layer);
		void setBackground(sf::Color color);
		void setDisplayed(bool set);
		bool getDisplayed();
	};

	class Container
	{
	protected:
		std::vector<WidgetContainer*> widContainers;
		std::map<std::string, WidgetContainer*> widgetContainers;
		sf::Event* evnt;
		sf::VideoMode resolution = sf::VideoMode::getDesktopMode();
		bool alreadyClicked = false;
		bool leftClickReleased = true;
		bool rightClickReleased = true;

		void loadAttributes(ComplexAttribute* widget, std::map<std::string, int> &attributesInt, std::map<std::string, float> &attributesFloat, std::map<std::string, std::string> &attributesString, std::map<std::string, bool> &attributesBool);
		void loadBasicsAttributes(double* posX, double* posY, bool* displayed, std::string* style, ComplexAttribute* widget);
        GUI::Widget* loadWidget(std::string widgetContainerName, std::string dataObject, std::string name, std::string path, DataParser* data, bool isContained);

	public:
		Container(sf::Event* evnt, sf::RenderWindow* window, int windowWidth = 1920, int windowHeight = 1080);
		WidgetContainer* createWidgetContainer(std::string containerName, int layer, int posX, int posY, int width, int height, GUI::ContainerMovement movable, \
			int widthControlBar = 0, int heightControleBar = 0);
		WidgetContainer* getContainerByContainerName(std::string containerName);
		void resizeWidgetContainer(std::string widgetContainerName, int width, int height);
		void updateContainer(std::string containerName);
		void drawContainer(std::string containerName, sf::RenderWindow *GUI);
		void updateAllContainer();
		void drawAllContainer(sf::RenderWindow* GUI);
		void setFocus(std::string widgetContainerName);
		void setFocus(GUI::WidgetContainer* widgetContainer);
		void setLayer(std::string widgetContainerName, int layer);
		void setAlreadyClicked(bool set);
		bool hasFocus(std::string widgetContainerName);
		bool hasFocus(GUI::WidgetContainer* widgetContainer);
		bool getAlreadyClicked();
		void autoFocus();
		void autoMove();
		void setWindowSize(int windowWidth, int windowHeight);

		Label* createLabel(std::string containerName, std::string ID, int posX, int posY, std::string text, std::string font, int fontSize, sf::Color color, sf::Text::Style style = sf::Text::Regular);
		ScrollBar* createScrollBar(std::string containerName, std::string ID, int posX, int posY, int size, int minHeightBar, bool needButtons, std::vector<Widget*> widgetsLinked, std::string style = "DEFAULT");
		ScrollBar* createScrollBar(std::string containerName, std::string ID, int posX, int posY, int size, int minHeightBar, bool needButtons, WidgetContainer* widgetContainerLink, std::string style = "DEFAULT");

		LoadingBar* createLoadingBar(std::string containerName, std::string ID, int posX, int posY, std::string style = "DEFAULT", std::string fillingType = "Horizontal", \
			int sideBordersWidth = 0, int TopBotBordersHeight = 0);
		Checkbox* createCheckbox(std::string containerName, std::string ID, int posX, int posY, std::string style = "DEFAULT", bool checked = false);
		Button* createButton(std::string containerName, std::string ID, int posX, int posY, bool pushingEnable, bool hoveringEnable, std::string style = "DEFAULT");
		Droplist* createDroplist(std::string containerName, std::string ID, int posX, int posY, int charSize, std::string titleOrDefaultValue, bool dropListMenu, std::string font, std::string style = "DEFAULT",\
			std::vector<std::string> list = std::vector<std::string>(), sf::Color fontColorIdle = sf::Color::White, sf::Color fontColorHover = sf::Color::White);//Usual function to create Droplist
		Droplist* createDroplist(std::string containerName, std::string ID, int posX, int posY, bool droplistMenu, std::string titleOrDefaultValue, std::vector<Button*> buttons, std::string style = "DEFAULT");

		Tab* createTab(std::string containerName, std::string ID, int posX, int posY, int fontSize, sf::Color fontColor, std::string font, std::vector<std::string> tabsNames, std::vector<WidgetContainer*> tabs, std::string style = "DEFAULT");
		Dropbox* createDropbox(std::string containerName, std::string ID, int posX, int posY, std::string style = "DEFAULT");
		NumericInput* createNumericInput(std::string containerName, std::string ID, int posX, int posY, int defaultValue = 0, std::string font = "arial.ttf", int fontSize = 15, sf::Color fontColor = sf::Color::White, std::string style = "DEFAULT");
		NumericInput* createNumericInput(std::string containerName, std::string ID, int posX, int posY, Label* text, std::string style = "DEFAULT");
		
		RadioButton* createRadioButton(std::string containerName, std::string ID, int posX, int posY, std::string value, std::string group, bool checked = false, std::string style = "DEFAULT");
		TextInput* createTextInput(std::string containerName, std::string ID, int posX, int posY, std::string defaultText, std::string font = "arial.ttf", int fontSize = 15, sf::Color fontColor = sf::Color::White, std::string style = "DEFAULT");
		TextInput* createTextInput(std::string containerName, std::string ID, int posX, int posY, Label* text, std::string style = "DEFAULT");

		NumericSlider* createNumericSlider(std::string containerName, std::string ID, int posX, int posY, int minValue, int maxValue, int defaultValue = 0, std::string style = "DEFAULT");
		Movable* createMovable(std::string containerName, std::string ID, int posX, int posY, std::string style);
		Movable* createMovable(std::string containerName, std::string ID, Dropbox* container, int marginLeft, int marginTop, std::string style);

		void loadWidgetContainerFromFile(std::string filename, int posX, int posY);
		void loadWidContFromFileInWidCont(std::string filename, std::string widgetContainer);
		void removeWidget(std::string widgetID);
		void removeWidgetContainer(std::string widgetContainerName);
	};
}

int convertMousePosX(int mousePosX);
int convertMousePosY(int mousePosY);
DataObject* parseBind(std::string str);
template <typename T> std::string pointerToString(const T* obj)
{
	std::stringstream ss;
	ss << obj;
	return ss.str();
}

template <typename T> T* stringToPointer(std::string address)
{
	return reinterpret_cast<T*>(stol(address, NULL, 16));
}