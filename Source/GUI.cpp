//Author : Theo Cevaer
//Key : 86d27c754f2ed9d671e7caf0a4cbb2ddb0c193631280bf65ffaddcb33e3949b8227c3161d8fd3326c541db064c98835f3eae6584d4bba3b8aaee57abea1448f2

#include "GUI.hpp"

namespace GUI
{
	int windowWidth = 0;
	int windowHeight = 0;
	sf::RenderWindow* window = NULL;
	GUI::Container* container = NULL;
}


std::vector<GUI::Widget*> GUI::Widget::vectWidgets = std::vector<GUI::Widget*>();
std::map<std::string, GUI::Widget*> GUI::Widget::mapWidgets = std::map<std::string, GUI::Widget*>();

//Gérer la superposition des textures de l'inventaire
void GUI::Widget::autoLoad()
{
	sf::Texture texture;

	if (widgetStyle != "None")
	{
		std::string textureGUIPath = "Sprites/GUI/" + widgetType + "/" + widgetStyle;
		std::cout << "Loading textures : " << textureGUIPath << std::endl;
		std::vector<std::string> listFile = fn::File::listFileInDir(textureGUIPath);
		for (int i = 0; i < listFile.size(); i++)
		{
			if (!texture.loadFromFile(textureGUIPath + "/" + listFile[i]))
			{
				texture.loadFromFile("Sprites/GUI/default.png");
			}
			else
			{
				std::cout << "Load success : " << listFile[i] << std::endl;
				texture.setSmooth(true);
				widgetTextures[listFile[i]] = texture;
			}
		}
	}
	texture.loadFromFile("Sprites/GUI/default.png");
	widgetTextures["default"] = texture;
	std::cout << ID << " textures successfully loaded" << std::endl;
}

GUI::Widget::~Widget()
{
	for (int i = 0; i < widgetsContained.size(); i++)
	{
		widgetsContained[i]->removeWidget();
	}
}

GUI::Widget::Widget(std::string ID, int posX, int posY, std::string style)
{
	ID.erase(std::remove(ID.begin(), ID.end(), '/'), ID.end());
	this->ID = ID;
	this->posX.push_back(posX);
	this->posY.push_back(posY);
	this->widgetStyle = style;

	this->mapWidgets[ID] = this;
	this->vectWidgets.push_back(this);

	this->attributes = new DataObject(ID);
	attributes->createComplexAttribute(convertPath(""), this->ID);
	attributes->createBaseAttribute(convertPath(ID), "style", "str", this->widgetStyle);
	createAttribute("posX", (this->posX[0]), "float");
	createAttribute("posY", (this->posY[0]), "float");
	createAttribute("displayed", displayed, "bool");
}

void GUI::Widget::draw(sf::RenderWindow *GUI)
{
	int j = 0;
	int k = 0;
	int l = 0;
	int m = 0;

	for (int i = 0; i < selector.size(); i++)
	{
		if (selector[i] == Display::Sprite)
		{
			GUI->draw(sprites[j]);
			j++;
		}
		else if (selector[i] == Display::Text)
		{
			GUI->draw(text[k]);

			k++;
		}
		else if (selector[i] == Display::WidgetContained)
		{
			if (widgetsContained[l]->getDisplayed())
			{
				widgetsContained[l]->draw(GUI);
			}
			l++;
		}
		else if (selector[i] == Display::Shape)
		{
			GUI->draw(*shapes[m]);
			m++;
		}
	}
}

void GUI::Widget::setAbsolute(int X, int Y)
{
	posContainerX = X;
	posContainerY = Y;
	for (int i = 0; i < posX.size(); i++)
	{
		absolutesX.push_back(posX[i] + X);
		absolutesY.push_back(posY[i] + Y);
	}
 	for (int i = 0; i < widgetsContained.size(); i++)
	{
		widgetsContained[i]->updatePosContainer(posContainerX, posContainerY);
	}
	setTexture();
}

void GUI::Widget::updatePosContainer(int widgetContainerX, int widgetContainerY)
{
	posContainerX = widgetContainerX;
	posContainerY = widgetContainerY;

	for (int i = 0; i < widgetsContained.size(); i++)
	{
		widgetsContained[i]->updatePosContainer(posContainerX, posContainerY);
	}

	updateAbsolute();
}

void GUI::Widget::containerChangePos(int x, int y)
{
	posContainerX = x;
	posContainerY = y;
	for (int i = 0; i < widgetsContained.size(); i++)
	{
		widgetsContained[i]->containerChangePos(x, y);
	}

	posX[0] = absolutesX[0] - x;
	posY[0] = absolutesY[0] - y;
	updatePositions();
}

bool GUI::Widget::getDisplayed()
{
	return displayed;
}

void GUI::Widget::setDisplayed(bool set)
{
	displayed = set;
	for (int i = 0; i < widgetsContained.size(); i++)
	{
		widgetsContained[i]->setDisplayed(set);
	}
}

int GUI::Widget::getRelativePosX()
{
	return posX[0];
}

int GUI::Widget::getRelativePosY()
{
	return posY[0];
}

void GUI::Widget::setTexture()
{
	sprites.clear();
	sprites.resize(1);
	sprites[0].setTexture(widgetTextures.begin()->second);

	updatePositions();
}

void GUI::Widget::updateAttributes()
{
	absolutesX[0] = posContainerX + posX[0];
	absolutesY[0] = posContainerY + posY[0];
	for (int i = 0; i < widgetsContained.size(); i++)
	{
		widgetsContained[i]->updateAttributes();
	}
}

void GUI::Widget::update(sf::Event& evnt)
{
	for (int i = 0; i < widgetsContained.size(); i++)
	{
		if (widgetsContained[i]->getDisplayed())
			widgetsContained[i]->update(evnt);
	}
	if (!LeftClickReleased && evnt.type == sf::Event::MouseButtonReleased && evnt.mouseButton.button == sf::Mouse::Left)
	{
		LeftClickReleased = true;
	}
	if (!rightClickReleased && evnt.type == sf::Event::MouseButtonReleased && evnt.mouseButton.button == sf::Mouse::Right)
	{
		rightClickReleased = true;
	}
	leftClicked = false;
	rightClicked = false;
	updateTexture(evnt);
}

bool GUI::Widget::isClicked(sf::Event& evnt, bool leftClick, bool rightClick)
{
	return isRectClicked(evnt, this->getRect(), leftClick, rightClick);
}

bool GUI::Widget::isClickedOutside(sf::Event& evnt, bool leftClick, bool rightClick)
{
	return isRectClickedOutside(evnt, this->getRect(), leftClick, rightClick);
}

bool GUI::Widget::isRectClicked(sf::Event& evnt, sf::Rect<float> rect, bool leftClick, bool rightClick)
{

	bool childClicked = false;
	for (int i = 0; i < widgetsContained.size(); i++)
	{
		if (widgetsContained[i]->isRectClicked(evnt, rect, leftClick, rightClick))
		{
			childClicked = true;
		}
	}
	if (childClicked && evnt.mouseButton.button == sf::Mouse::Left && leftClick)
	{
		leftClicked = true;
	}
	if (childClicked && evnt.mouseButton.button == sf::Mouse::Right && rightClick)
	{
		rightClicked = true;
	}

	if (rightClicked && rightClick)
	{
		rightClickReleased = false;
		return true;
	}
	if (leftClicked && leftClick)
	{
		LeftClickReleased = false;
		return true;
	}
	if (evnt.type == sf::Event::MouseButtonPressed)
	{
		if (!LeftClickReleased || !rightClickReleased)
		{
			if (convertMousePosX(evnt.mouseButton.x) > rect.left && convertMousePosX(evnt.mouseButton.x) < rect.left + rect.width && convertMousePosY(evnt.mouseButton.y) > rect.top && convertMousePosY(evnt.mouseButton.y) < rect.top + rect.height)
			{
				GUI::container->setAlreadyClicked(true);
				if (evnt.mouseButton.button == sf::Mouse::Left)
				{
					leftClicked = true;
					LeftClickReleased = false;
					if (leftClick && !LeftClickReleased)
					{
						return true;
					}
				}

				if (evnt.mouseButton.button == sf::Mouse::Right)
				{
					rightClickReleased = false;
					rightClicked = true;
					if (rightClick && !rightClickReleased)
					{
						return true;
					}
				}
			}
		}
		else if (!GUI::container->getAlreadyClicked())
		{
			if (convertMousePosX(evnt.mouseButton.x) > rect.left && convertMousePosX(evnt.mouseButton.x) < rect.left + rect.width && convertMousePosY(evnt.mouseButton.y) > rect.top && convertMousePosY(evnt.mouseButton.y) < rect.top + rect.height)
			{
				GUI::container->setAlreadyClicked(true);
				if (evnt.mouseButton.button == sf::Mouse::Left)
				{
					leftClicked = true;
					LeftClickReleased = false;
					if (leftClick)
					{
						return true;
					}
				}

				if (evnt.mouseButton.button == sf::Mouse::Right)
				{
					rightClickReleased = false;
					rightClicked = true;
					if (rightClick)
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool GUI::Widget::isRectClickedOutside(sf::Event& evnt, sf::Rect<float> rect, bool leftClick, bool righClick)
{
	if (evnt.type == sf::Event::MouseButtonPressed)
	{
		if (!isRectClicked(evnt, rect, leftClick, righClick))
		{
			return true;
		}
	}
	return false;
}

bool GUI::Widget::isRectHovering(sf::Event& evnt, sf::Rect<float> rect)
{
	sf::Vector2i pos = sf::Mouse::getPosition(*GUI::window);
	if (convertMousePosX(pos.x) > rect.left && convertMousePosX(pos.x)  < rect.left + rect.width && convertMousePosY(pos.y)  > rect.top && convertMousePosY(pos.y)  < rect.top + rect.height)
	{
		return true;
	}
	return false;
}

bool GUI::Widget::isHovering(sf::Event& evnt)
{
	return isRectHovering(evnt, this->getRect());
}

void GUI::Widget::updateTexture(sf::Event& evnt)
{
	if (LeftClickReleased)
	{
		if (isRectClicked(evnt, sprites[0].getGlobalBounds(), true, false))
		{
			clicked();
		}
	}
	if (evnt.type == sf::Event::MouseButtonReleased && evnt.mouseButton.button == sf::Mouse::Left)
	{
		LeftClickReleased = true;
	}
}

void GUI::Widget::move(float x, float y)
{
	for (int i = 0; i < absolutesX.size(); i++)
	{
		posX[i] += x;
		posY[i] += y;
	}

	for (int i = 0; i < widgetsContained.size(); i++)
	{
		widgetsContained[i]->move(x, y);
	}
	updateAbsolute();
}

std::string GUI::Widget::getWidgetType()
{
	return widgetType;
}

std::string GUI::Widget::getWidgetStyle()
{
	return widgetStyle;
}

std::vector<sfe::RichText>* GUI::Widget::getTexts()
{
	return &text;
}

std::string GUI::Widget::getID()
{
	return ID;
}

DataObject* GUI::Widget::getDataObject()
{
	return attributes;
}

void GUI::Widget::removeWidget()
{
	std::map<std::string, Widget*>::iterator itemap = mapWidgets.find(ID);
	std::vector<Widget*>::iterator itevect = std::find(vectWidgets.begin(), vectWidgets.end(), this);
	mapWidgets.erase(itemap);
	vectWidgets.erase(itevect);
	delete this;
}

void GUI::Widget::setPosition(int x, int y)
{
	posX[0] = x;
	posY[0] = y;
	updatePositions();
}

void GUI::Widget::setSpritesPositions()
{
	int j = 0;
	int k = 0;
	int l = 0;
	int m = 0;
	for (int i = 0; i < absolutesX.size(); i++)
	{
		if (selector[i] == GUI::Display::Sprite)
		{
			sprites[j].setPosition(absolutesX[i], absolutesY[i]);
			j++;
		}
		else if (selector[i] == GUI::Display::Text)
		{
			text[k].setPosition(absolutesX[i], absolutesY[i]);
			k++;
		}
		else if (selector[i] == GUI::Display::WidgetContained)
		{
			widgetsContained[l]->setPosition(posX[i], posY[i]);
			l++;
		}
		else if (selector[i] == GUI::Display::Shape)
		{
			shapes[m]->setPosition(absolutesX[i], absolutesY[i]);
			m++;
		}
	}
}

void GUI::Widget::updatePositions()
{
	updateAbsolute();
	for (int i = 0; i < widgetsContained.size(); i++)
	{
		widgetsContained[i]->updatePositions();
	}
}

void GUI::Widget::updateAbsolute()
{
	for (int i = 0; i < absolutesX.size(); i++)
	{
		absolutesX[i] = posContainerX + posX[i];
		absolutesY[i] = posContainerY + posY[i];
	}
	setSpritesPositions();
}

void GUI::Widget::addWidgetContained(Widget* widget)
{
	widgetsContained.push_back(widget);
}

std::vector<GUI::Widget*> GUI::Widget::getWidgetsContained()
{
	return widgetsContained;
}

sf::Rect<float> GUI::Widget::getRect()
{
	sf::Rect<float> rect;
	int j = 0;
	int k = 0;
	int m = 0;
	bool rectDefined = false;
	updatePositions();
	
	for (int l = 0; l < selector.size(); l++)
	{
		if (sprites.size() > 0)
		{
			rect = sprites[0].getGlobalBounds();
			rectDefined = true;
			if (selector[l] == GUI::Display::Sprite)
			{
				if (sprites[j].getGlobalBounds().left < rect.left)
				{
					rect.left = sprites[j].getGlobalBounds().left;
				}
				if (sprites[j].getGlobalBounds().top < rect.top)
				{
					rect.top = sprites[j].getGlobalBounds().top;
				}
				if (sprites[j].getGlobalBounds().width > rect.width)
				{
					rect.width = sprites[j].getGlobalBounds().width;
				}
				if (sprites[j].getGlobalBounds().height > rect.height)
				{
					rect.height = sprites[j].getGlobalBounds().height;
				}
				j++;
			}
		}
		if (text.size() > 0)
		{
			if (!rectDefined)
			{
				rect = text[0].getGlobalBounds();
				rectDefined = true;
			}
			if (selector[l] == GUI::Display::Text)
			{
				if (text[k].getGlobalBounds().left < rect.left)
				{
					rect.left = text[k].getGlobalBounds().left;
				}
				if (text[k].getGlobalBounds().top < rect.top)
				{
					rect.top = text[k].getGlobalBounds().top;
				}
				if (text[k].getGlobalBounds().width > rect.width)
				{
					rect.width = text[k].getGlobalBounds().width;
				}
				if (text[k].getGlobalBounds().height > rect.height)
				{
					rect.height = text[k].getGlobalBounds().height;
				}
				k++;
			}
		}
		if (widgetsContained.size() > 0)
		{
			if (!rectDefined) rect = widgetsContained[0]->getRect();
			if (selector[l] == GUI::Display::Text)
			{
				if (widgetsContained[m]->getRect().left < rect.left)
				{
					rect.left = widgetsContained[m]->getRect().left;
				}
				if (widgetsContained[m]->getRect().top < rect.top)
				{
					rect.top = widgetsContained[m]->getRect().top;
				}
				if (widgetsContained[m]->getRect().width > rect.width)
				{
					rect.width = widgetsContained[m]->getRect().width;
				}
				if (widgetsContained[m]->getRect().height > rect.height)
				{
					rect.height = widgetsContained[m]->getRect().height;
				}
				m++;
			}
		}
	}
	return rect;
}

void GUI::Widget::setTextureMap(sf::Sprite* sprite, std::string key)
{
	sf::Sprite cleanSprite;
	std::map<std::string, sf::Texture>::iterator it = widgetTextures.find(key);
	if (it != widgetTextures.end())
	{
		cleanSprite.setTexture(widgetTextures[key]);
	}
	else
	{
		cleanSprite.setTexture(widgetTextures["default.png"]);
	}

	*sprite = cleanSprite;
	setSpritesPositions();
}

std::map<std::string, std::function<void()>> GUI::Widget::getFunctions()
{
	return std::map<std::string, std::function<void()>>();
}

GUI::WidgetContainer::WidgetContainer(std::string containerName, int posX, int posY, int width, int height, GUI::ContainerMovement movable, int widthControlBar, int heightControleBar, sf::Event* evnt)
{
	this->containerName = containerName;
	this->posX = posX;
	this->posY = posY;
	this->width = width;
	this->height = height;
	this->widthControlBar = widthControlBar;
	this->heightControleBar = heightControleBar;
	this->movable = movable;
	this->evnt = evnt;
	this->background.setFillColor(sf::Color(0, 0, 0, 0));
}

/*GUI::NumericSlider* GUI::Container::createNumericSlider(std::string containerName, std::string ID, int posX, int posY, int minValue, int maxValue, int defaultValue, std::string style)
{
	if (widgetContainers.find(containerName) == widgetContainers.end())
	{
		std::cout << "GUI Error: Widget " << ID << " container's doesn't exist, widget not created" << std::endl;
		return NULL;
	}
	else
	{
		NumericSlider* numericSlider = new NumericSlider(ID, posX, posY, minValue, maxValue, defaultValue, style);
		numericSlider->autoLoad();
		widgetContainers[containerName]->addNewWidget(numericSlider);
		return numericSlider;
	}
}*/


GUI::TextInput* GUI::Container::createTextInput(std::string containerName, std::string ID, int posX, int posY, std::string defaultText, std::string font, int fontSize, sf::Color fontColor, std::string style)
{
	if (widgetContainers.find(containerName) == widgetContainers.end())
	{
		std::cout << "GUI Error: Widget " << ID << " container's doesn't exist, widget not created" << std::endl;
		return NULL;
	}
	else
	{
		TextInput* textInput = new TextInput(ID, posX, posY, font, fontSize, fontColor, style, defaultText);
		textInput->autoLoad();
		widgetContainers[containerName]->addNewWidget(textInput);
		return textInput;
	}
}

GUI::TextInput* GUI::Container::createTextInput(std::string containerName, std::string ID, int posX, int posY, Label* text, std::string style)
{
	if (widgetContainers.find(containerName) == widgetContainers.end())
	{
		std::cout << "GUI Error: Widget " << ID << " container's doesn't exist, widget not created" << std::endl;
		return NULL;
	}
	else
	{
		TextInput* textInput = new TextInput(ID, posX, posY, style, text);
		textInput->autoLoad();
		widgetContainers[containerName]->addNewWidget(textInput);
		return textInput;
	}

}


GUI::RadioButton* GUI::Container::createRadioButton(std::string containerName, std::string ID, int posX, int posY, std::string value, std::string group, bool checked, std::string style)
{
	if (widgetContainers.find(containerName) == widgetContainers.end())
	{
		std::cout << "GUI Error: Widget " << ID << " container's doesn't exist, widget not created" << std::endl;
		return NULL;
	}
	else
	{
		RadioButton* radiobutton = new RadioButton(ID, posX, posY, value, group, style, checked);
		radiobutton->autoLoad();
		widgetContainers[containerName]->addNewWidget(radiobutton);
		return radiobutton;
	}
}

/*GUI::NumericInput* GUI::Container::createNumericInput(std::string containerName, std::string ID, int posX, int posY, int defaultValue, std::string font, \
	int fontSize, sf::Color fontColor, std::string style)
{
	if (widgetContainers.find(containerName) == widgetContainers.end())
	{
		std::cout << "GUI Error: Widget " << ID << " container's doesn't exist, widget not created" << std::endl;
		return NULL;
	}
	else
	{
		NumericInput* numericInput = new NumericInput(ID, posX, posY, defaultValue, style, font, fontColor, fontSize);
		numericInput->autoLoad();
		widgetContainers[containerName]->addNewWidget(numericInput);
		return numericInput;
	}
}

GUI::NumericInput* GUI::Container::createNumericInput(std::string containerName, std::string ID, int posX, int posY, GUI::Label* text, std::string style)
{
	if (widgetContainers.find(containerName) == widgetContainers.end())
	{
		std::cout << "GUI Error: Widget " << ID << " container's doesn't exist, widget not created" << std::endl;
		return NULL;
	}
	else
	{
		NumericInput* numericInput = new NumericInput(ID, posX, posY, text, style);
		numericInput->autoLoad();
		widgetContainers[containerName]->addNewWidget(numericInput);
		return numericInput;
	}
}*/


GUI::Checkbox* GUI::Container::createCheckbox(std::string containerName, std::string ID, int posX, int posY, std::string style, bool checked)
{
	if (widgetContainers.find(containerName) == widgetContainers.end())
	{
		std::cout << "GUI Error: Widget " << ID << " container's doesn't exist, widget not created" << std::endl;
		return NULL;
	}
	else
	{
		Checkbox* checkbox = new Checkbox(ID, posX, posY, style, checked);
		checkbox->autoLoad();
		widgetContainers[containerName]->addNewWidget(checkbox);
		return checkbox;
	}
}

GUI::Button* GUI::Container::createButton(std::string containerName, std::string ID, int posX, int posY, bool pushingEnable, bool hoveringEnable, std::string style)
{
	if (widgetContainers.find(containerName) == widgetContainers.end())
	{
		std::cout << "GUI Error: Widget " << ID << " container's doesn't exist, widget not created" << std::endl;
		return NULL;
	}
	else
	{
		Button* button = new Button(ID, posX, posY, style, pushingEnable, hoveringEnable);
		button->autoLoad();
		widgetContainers[containerName]->addNewWidget(button);

		return button;
	}
}

GUI::Droplist* GUI::Container::createDroplist(std::string containerName, std::string ID, int posX, int posY, int charSize, std::string titleOrDefaultValue, bool dropListMenu, std::string font, std::string style, std::vector<std::string> list, sf::Color fontColorIdle, sf::Color fontColorHover)
{
	if (widgetContainers.find(containerName) == widgetContainers.end())
	{
		std::cout << "GUI Error: Widget " << ID << " container's doesn't exist, widget not created" << std::endl;
		return NULL;
	}
	else
	{
		Droplist* droplist = NULL;
		if (list.size() > 0)
		{
			droplist = new Droplist(ID, posX, posY, charSize, dropListMenu, style, titleOrDefaultValue, list, font, fontColorIdle, fontColorHover);
			droplist->autoLoad();
			widgetContainers[containerName]->addNewWidget(droplist);
		}
		else
		{
			std::cout << "GUI Error: Droplist's (" << ID << ")vector is void" << std::endl;
		}
		return droplist;
	}
}

GUI::Droplist* GUI::Container::createDroplist(std::string containerName, std::string ID, int posX, int posY, bool droplistMenu, std::string titleOrDefaultValue, std::vector<Button*> buttons, std::string style)
{
	if (widgetContainers.find(containerName) == widgetContainers.end())
	{
		std::cout << "GUI Error: Widget " << ID << " container's doesn't exist, widget not created" << std::endl;
		return NULL;
	}
	else
	{
		Droplist* droplist = NULL;
		if (buttons.size() > 0)
		{
			droplist = new Droplist(ID, posX, posY, droplistMenu, titleOrDefaultValue, buttons, style);
			droplist->autoLoad();
			widgetContainers[containerName]->addNewWidget(droplist);
		}
		else
		{
			std::cout << "GUI Error: Droplist's (" << ID << ")vector is void" << std::endl;
		}
		return droplist;
	}
}

GUI::Tab* GUI::Container::createTab(std::string containerName, std::string ID, int posX, int posY, int fontSize, sf::Color fontColor, std::string font, std::vector<std::string> tabsNames, std::vector<GUI::WidgetContainer*> tabs, std::string style)

{
	if (widgetContainers.find(containerName) == widgetContainers.end())
	{
		std::cout << "GUI Error: Widget " << ID << " container's doesn't exist, widget not created" << std::endl;
		return NULL;
	}
	else
	{
		Tab* tab = new Tab(ID, posX, posY, fontSize, font, fontColor, tabsNames, tabs, style);
		tab->autoLoad();
		widgetContainers[containerName]->addNewWidget(tab);
		return tab;
	}
}

GUI::Dropbox* GUI::Container::createDropbox(std::string containerName, std::string ID, int posX, int posY, std::string style)
{
	if (widgetContainers.find(containerName) == widgetContainers.end())
	{
		std::cout << "GUI Error: Widget " << ID << " container's doesn't exist, widget not created" << std::endl;
		return NULL;
	}
	else
	{
		Dropbox* dropbox = new Dropbox(ID, posX, posY, style);
		dropbox->autoLoad();
		widgetContainers[containerName]->addNewWidget(dropbox);
		return dropbox;
	}
}

GUI::Label* GUI::Container::createLabel(std::string containerName, std::string ID, int posX, int posY, std::string text, std::string font, int fontSize, sf::Color color, sf::Text::Style style)
{
	if (widgetContainers.find(containerName) == widgetContainers.end())
	{
		std::cout << "GUI Error: Widget " << ID << " container's doesn't exist, widget not created" << std::endl;
		return NULL;
	}
	else
	{
		Label* label = new Label(ID, posX, posY, text, font, fontSize, color, style);
		widgetContainers[containerName]->addNewWidget(label);
		return label;
	}
}

GUI::ScrollBar* GUI::Container::createScrollBar(std::string containerName, std::string ID, int posX, int posY, int size, int minHeightBar, bool needButtons, WidgetContainer* widgetContainerLink, std::string style)
{
	if (widgetContainers.find(containerName) == widgetContainers.end())
	{
		std::cout << "GUI Error: Widget " << ID << " container's doesn't exist, widget not created" << std::endl;
		return NULL;
	}
	else
	{
		ScrollBar* scrollbar = new ScrollBar(ID, posX, posY, size, minHeightBar, needButtons, widgetContainerLink, style);
		scrollbar->autoLoad();
		widgetContainers[containerName]->addNewWidget(scrollbar);
		return scrollbar;
	}
}

GUI::ScrollBar* GUI::Container::createScrollBar(std::string containerName, std::string ID, int posX, int posY, int size, int minHeightBar, bool needButtons, std::vector<Widget*> widgetsLinked, std::string style)
{
	if (widgetContainers.find(containerName) == widgetContainers.end())
	{
		std::cout << "GUI Error: Widget " << ID << " container's doesn't exist, widget not created" << std::endl;
		return NULL;
	}
	else
	{
		ScrollBar* scrollbar = new ScrollBar(ID, posX, posY, size, minHeightBar, needButtons, widgetsLinked, style);
		scrollbar->autoLoad();
		widgetContainers[containerName]->addNewWidget(scrollbar);
		return scrollbar;
	}
}

GUI::LoadingBar* GUI::Container::createLoadingBar(std::string containerName, std::string ID, int posX, int posY, std::string style, std::string fillingType, int sideBordersWidth, int TopBotBordersHeight)
{
	if (widgetContainers.find(containerName) == widgetContainers.end())
	{
		std::cout << "GUI Error: Widget " << ID << " container's doesn't exist, widget not created" << std::endl;
		return NULL;
	}
	else
	{
		LoadingBar* loadingBar = new LoadingBar(ID, posX, posY, fillingType, style, sideBordersWidth, TopBotBordersHeight);
		loadingBar->autoLoad();
		widgetContainers[containerName]->addNewWidget(loadingBar);
		return loadingBar;
	}
}

GUI::Movable* GUI::Container::createMovable(std::string containerName, std::string ID, int posX, int posY, std::string style)
{
	if (widgetContainers.find(containerName) == widgetContainers.end())
	{
		std::cout << "GUI Error: Widget " << ID << " container's doesn't exist, widget not created" << std::endl;
		return NULL;
	}
	else
	{
		Movable* movable = new Movable(ID, posX, posY, style);
		movable->autoLoad();
		widgetContainers[containerName]->addNewWidget(movable);
		return movable;
	}
}
GUI::Movable* GUI::Container::createMovable(std::string containerName, std::string ID, Dropbox* container, int marginLeft, int marginTop, std::string style)
{
	if (widgetContainers.find(containerName) == widgetContainers.end())
	{
		std::cout << "GUI Error: Widget " << ID << " container's doesn't exist, widget not created" << std::endl;
		return NULL;
	}
	else
	{
		Movable* movable = new Movable(ID, container, marginLeft, marginTop, style);
		movable->autoLoad();
		return movable;
	}
}

int GUI::WidgetContainer::getNbWidget()
{
	return widgetIDContainer.size();
}

void GUI::WidgetContainer::updateAll(sf::Event& evnt)
{
	if (displayed)
	{
		if (scroll != NULL)
			scroll->computeDynamicScroll();
		for (int i = 0; i < widgetIDContainer.size(); i++)
		{
			sf::Rect<float> rect = widgetIDContainer[i]->getRect();
			if(widgetIDContainer[i]->getDisplayed() && !(rect.left + rect.width < posX || rect.left > posX + width || rect.top + rect.height < posY || rect.top > posY + height))
			{
				widgetIDContainer[i]->update(evnt);
			}
		}
	}
}

void GUI::WidgetContainer::updateAttributes(std::string widgetID)
{
	GUI::Widget::getWidgetByID<Widget>(widgetID)->updateAttributes();
}

void GUI::WidgetContainer::move(int x, int y)
{
	setPosition(posX + x, posY + y);
}

bool GUI::WidgetContainer::getClicked()
{
	if (movable == GUI::ContainerMovement::All)
	{
		if (evnt->type == sf::Event::MouseButtonPressed)
		{
			if (evnt->mouseButton.button == sf::Mouse::Left)
			{
				if (evnt->mouseButton.x > posX && evnt->mouseButton.x < posX + width && evnt->mouseButton.y > posY && evnt->mouseButton.y < posY + height)
				{
					currentShiftX = evnt->mouseButton.x - posX;
					currentShiftY = evnt->mouseButton.y - posY;
					holding = true;
					return true;
				}
			}
		}
	}
	if (movable == GUI::ContainerMovement::Total)
	{
		bool widgetClicked = false;

		for (std::vector<Widget*>::iterator ite = widgetIDContainer.begin(); ite != widgetIDContainer.end(); ite++)
		{
			if ((*ite)->isClicked(*evnt, true, false))
			{
				widgetClicked = true;
			}
		}
		if (!widgetClicked && evnt->type == sf::Event::MouseButtonPressed)
		{
			if (evnt->mouseButton.button == sf::Mouse::Left)
			{
				if (evnt->mouseButton.x > posX && evnt->mouseButton.x < posX + width && evnt->mouseButton.y > posY && evnt->mouseButton.y < posY + height)
				{
					currentShiftX = evnt->mouseButton.x - posX;
					currentShiftY = evnt->mouseButton.y - posY;
					holding = true;
					return true;
				}
			}
		}
	}
	else if (movable == GUI::ContainerMovement::ControlBar)
	{
		if (evnt->type == sf::Event::MouseButtonPressed)
		{
			if (evnt->mouseButton.button == sf::Mouse::Left)
			{
				if (evnt->mouseButton.x > posX && evnt->mouseButton.x < posX + widthControlBar && evnt->mouseButton.y > posY && evnt->mouseButton.y < posY + heightControleBar)
				{
					currentShiftX = evnt->mouseButton.x - posX;
					currentShiftY = evnt->mouseButton.y - posY;
					holding = true;
					return true;
				}
			}
		}
	}
	return false;
}

void GUI::WidgetContainer::setHolding()
{
	holding = true;
}

void GUI::WidgetContainer::autoMove()
{
	justReleased = false;
	getClicked();
	if (!(sf::Mouse::isButtonPressed(sf::Mouse::Left)) && holding)
	{
		holding = false;
		justReleased = true;
	}
	if (holding && evnt->type == sf::Event::MouseMoved)
	{
		move(convertMousePosX(evnt->mouseMove.x) - posX - currentShiftX, convertMousePosX(evnt->mouseMove.y) - posY - currentShiftY);
	}
}

void GUI::WidgetContainer::setPosition(int posX, int posY)
{
	for (std::vector<Widget*>::iterator ite = widgetIDContainer.begin(); ite != widgetIDContainer.end(); ite++)
	{
		(*ite)->updatePosContainer(posX, posY);
	}
	this->posX = posX;
	this->posY = posY;
}

GUI::Widget * GUI::WidgetContainer::getWidgetByInt(int i)
{
	return widgetIDContainer[i];
}

std::vector<GUI::Widget*> GUI::WidgetContainer::getWidgets()
{
	return widgetIDContainer;
}

void GUI::WidgetContainer::addNewWidget(Widget* widget)
{
	widgetIDContainer.push_back(widget);
	widget->setAbsolute(posX, posY);
}

void GUI::WidgetContainer::addWidget(Widget* widget)
{
	widgetIDContainer.push_back(widget);
	widget->containerChangePos(posX, posY);
}

bool GUI::WidgetContainer::removeWidget(std::string ID, bool freeMemory)
{
	if (freeMemory)
	{
		std::vector<Widget*>::iterator itvec;
		itvec = std::find(widgetIDContainer.begin(), widgetIDContainer.end(), GUI::Widget::getWidgetByID<Widget>(ID));
		if (itvec != widgetIDContainer.end())
		{
			(*itvec)->removeWidget();
			widgetIDContainer.erase(itvec);
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		std::vector<Widget*>::iterator itvec;
		itvec = std::find(widgetIDContainer.begin(), widgetIDContainer.end(), GUI::Widget::getWidgetByID<Widget>(ID));
		if (itvec != widgetIDContainer.end())
		{
			widgetIDContainer.erase(itvec);
		}
	}
}

void GUI::WidgetContainer::removeAllWidget(bool freeMemory)
{
	if (freeMemory)
	{
		for (int i = 0; i < widgetIDContainer.size(); i++)
		{
			removeWidget(widgetIDContainer[i]->getID());
		}
		widgetIDContainer.clear();
	}
	else
	{
		widgetIDContainer.clear();
	}
}

GUI::WidgetContainer::~WidgetContainer()
{
	remove();
}

void GUI::WidgetContainer::remove()
{
	for (auto ite = widgetIDContainer.begin(); ite != widgetIDContainer.end(); ite++)
	{
		(*ite)->removeWidget();
	}
}

void GUI::WidgetContainer::setBackground(sf::Color color)
{
	background.setPosition(posX, posY);
	background.setSize(sf::Vector2f(width, height));
	background.setFillColor(color);
	hasBackground = true;
}

void GUI::WidgetContainer::pushTexture(int posX, int posY, sf::Texture texture, int layer)
{
	std::tuple<sf::Texture, int, int> tuple;
	std::get<0>(tuple) = texture;
	std::get<1>(tuple) = posX;
	std::get<2>(tuple) = posY;
	if (layer > decoTextures.size() && decoTextures.size() != 0)
	{
		layer = decoTextures.size();
	}
	else if (decoTextures.size() == 0)
	{
		layer = 1;
	}
	else if (layer < 1)
	{
		layer = 1;
	}
	decoTextures.insert(decoTextures.begin() + layer - 1, tuple);
}

void GUI::WidgetContainer::setDisplayed(bool set)
{
	if (!displayed && set)
	{
		displayed = true;
		for (std::vector<GUI::Widget*>::iterator ite = widgetIDContainer.begin(); ite != widgetIDContainer.end(); ite++)
		{
			(*ite)->setDisplayed(true);
		}
	}
	else if (displayed && !set)
	{
		displayed = false;
		for (std::vector<GUI::Widget*>::iterator ite = widgetIDContainer.begin(); ite != widgetIDContainer.end(); ite++)
			{
				(*ite)->setDisplayed(false);
		}
	}
}

void GUI::WidgetContainer::drawAll(sf::RenderWindow * GUI)
{
	if (displayed)
	{
		GUI->draw(background);
		glEnable(GL_SCISSOR_TEST);
		glScissor(posX, windowHeight - posY - height, width, height);
		if (decoTextures.size() > 0)
		{
			for (std::vector<std::tuple<sf::Texture, int, int>>::reverse_iterator ite = decoTextures.rbegin(); ite != decoTextures.rend(); ite++)
			{
				sf::Sprite decoSprite;
				decoSprite.setTexture(std::get<0>(*ite));
				decoSprite.setPosition(std::get<1>(*ite)+ this->posX, std::get<2>(*ite) + this->posY);
				GUI->draw(decoSprite);
			}
		}
		for (int i = 0; i < widgetIDContainer.size(); i++)
		{
			sf::Rect<float> rect = widgetIDContainer[i]->getRect();
			if (widgetIDContainer[i]->getDisplayed()&& !(rect.left + rect.width < posX || rect.left > posX + width || rect.top + rect.height < posY || rect.top > posY + height))
			{
				widgetIDContainer[i]->draw(GUI);
			}
		}
		std::vector<Dropbox*> dropboxes = this->getDropboxes();
		for (int i = 0; i < dropboxes.size(); i++)
		{
			if (dropboxes[i]->getDisplayed() && dropboxes[i]->getContainMovable() && !dropboxes[i]->getMovable()->getHolding())
			{
				dropboxes[i]->getMovable()->draw(GUI);
			}
		}
		glDisable(GL_SCISSOR_TEST);
		background.setPosition(posX, posY);
	}
}

std::vector<GUI::Dropbox*> GUI::WidgetContainer::getDropboxes()
{
	std::vector<Dropbox*> dropboxes;
	for (std::vector<GUI::Widget*>::iterator ite = widgetIDContainer.begin(); ite != widgetIDContainer.end(); ite++)
	{
		if ((*ite)->getWidgetType() == "Dropbox")
		{
			dropboxes.push_back(dynamic_cast<Dropbox*>((*ite)));
		}
	}
	return dropboxes;
}

void GUI::WidgetContainer::resize(int width, int height)
{
	this->width = width;
	this->height = height;
	if (hasBackground)
		background.setSize(sf::Vector2f(width, height));
}


GUI::LoadingBar::LoadingBar(std::string ID, int posX, int posY, std::string fillingType, std::string style, int sideBordersWidth, int TopBotBordersHeight) : Widget(ID, posX, posY, style)
{
	this->widgetType = "LoadingBar";
	this->fillingType = fillingType;
	this->sideBordersWidth = sideBordersWidth;
	this->TopBotBordersHeight = TopBotBordersHeight;
	selector.push_back(Display::Sprite);
	selector.push_back(Display::Sprite);
	attributes->createBaseAttribute(convertPath(this->ID), "type", "str", widgetType);
}

void GUI::LoadingBar::setTexture()
{
	sprites.resize(2);
	setTextureMap(&sprites[0], nameImageBorder);
	if (fillingType == "Horizontal")
		pixelsPerPercent = sprites[0].getGlobalBounds().width / 100.0;
	else if (fillingType == "Vertical")
		pixelsPerPercent = sprites[0].getGlobalBounds().height / 100.0;
	setTextureMap(&sprites[1], nameImageFiller);
}

void GUI::LoadingBar::fill(int percentage, double timeToFill)
{
	this->timeToFill = timeToFill;
	if (percentage > fillingInPercentage)
	{
		if (percentage >= 100)
		{
			currentPixelsPerDraw = (100 * pixelsPerPercent - fillingInPixels) / (this->timeToFill / delay);
			fillingInPercentage = 100;
			fillingInPixels = sprites[0].getGlobalBounds().width;
		}
		else
		{
			currentPixelsPerDraw = (percentage * pixelsPerPercent - fillingInPixels) / (this->timeToFill / delay);
			fillingInPercentage = percentage;
			fillingInPixels = percentage * pixelsPerPercent;
		}
	}
}

void GUI::LoadingBar::addFilling(int percentageToAdd)
{
	if (fillingInPercentage + percentageToAdd >= 100)
	{
		fillingInPercentage = 100;
		fillingInPixels = sprites[0].getGlobalBounds().width;
		currentFillingPixels = fillingInPixels;
	}
	else
	{
		fillingInPercentage += percentageToAdd;
		fillingInPixels += percentageToAdd * pixelsPerPercent;
		currentFillingPixels = fillingInPixels;
	}
}

bool GUI::LoadingBar::isFilled()
{
	if (fillingInPercentage == 100)
		return 1;
	else
		return 0;
}

int GUI::LoadingBar::getFilling()
{
	return fillingInPercentage;
}

void GUI::LoadingBar::draw(sf::RenderWindow* GUI)
{

	if (double(std::clock()) / CLOCKS_PER_SEC - timeBefore > delay && currentFillingPixels < fillingInPixels)
	{
		currentFillingPixels += currentPixelsPerDraw;
		timeBefore = double(std::clock()) / CLOCKS_PER_SEC;
	}
	if (fillingType == "Horizontal")
	{
		absolutesX[1] = absolutesX[0] + sideBordersWidth;
		absolutesY[1] = absolutesY[0] + TopBotBordersHeight;
		for (int i = 0; i < currentFillingPixels; i++)
		{
			sprites[1].setPosition(absolutesX[1], absolutesY[1]);
			GUI->draw(sprites[1]);
			absolutesX[1] += 1;
		}
	}
	else if (fillingType == "Vertical")
	{
		absolutesX[1] = absolutesX[0] + sideBordersWidth - 1;
		absolutesY[1] = absolutesY[0] + sprites[0].getGlobalBounds().height - TopBotBordersHeight - 1;

		for (int i = 0; i < currentFillingPixels; i++)
		{
			sprites[1].setPosition(absolutesX[1], absolutesY[1]);
			GUI->draw(sprites[1]);
			absolutesY[1] -= 1;
		}
	}

	sprites[0].setPosition(absolutesX[0], absolutesY[0]);
	GUI->draw(sprites[0]);
}

GUI::ScrollBar::ScrollBar(std::string ID, int posX, int posY, int size, int minHeightBar, bool needButtons, std::vector<Widget*> widgetsToMove, std::string style) : Widget(ID, posX, posY, style)
{
	this->widgetType = "ScrollBar";
	this->size = size;
	widgetsLinked = widgetsToMove;
	previousScrollerX = posX;
	previousScrollerY = posY;
	this->minHeightBar = minHeightBar;

	selector.push_back(Display::Sprite);
	selector.push_back(Display::WidgetContained);

	scroller = new Movable(ID + "movable", posX, posY, "SCROLLER");
	scroller->autoLoad();
	scroller->setAbsolute(posContainerX, posContainerY);
	widgetsContained.push_back(scroller);
	scroller->setMovementConstraints(false, true);
	

	attributes->createBaseAttribute(convertPath(this->ID), "type", "str", widgetType);
}

GUI::ScrollBar::ScrollBar(std::string ID, int posX, int posY, int size, int minHeightBar, bool needButtons, WidgetContainer* widgetContainerLinked, std::string style) : Widget(ID, posX, posY, style)
{
	this->widgetType = "ScrollBar";
	this->size = size;
	this->containerLinked = widgetContainerLinked;
	widgetsLinked = widgetContainerLinked->getWidgets();
	hasContainer = true;
	previousScrollerX = posX;
	previousScrollerY = posY;
	this->minHeightBar = minHeightBar;

	selector.push_back(Display::Sprite);
	selector.push_back(Display::WidgetContained);

	scroller = new Movable(ID + "movable", posX, posY, "SCROLLER");
	scroller->autoLoad();
	scroller->setAbsolute(posContainerX, posContainerY);
	widgetsContained.push_back(scroller);
	scroller->setMovementConstraints(false, true);


	attributes->createBaseAttribute(convertPath(this->ID), "type", "str", widgetType);
}

void GUI::ScrollBar::setTexture()
{
	posX.resize(2);
	posY.resize(2);
	sprites.clear();
	sprites.resize(1);
	posY[1] = posY[0];
	setTextureMap(&sprites[0], nameImageBar);
	sprites[0].scale(1, size / (float)(sprites[0].getGlobalBounds().height));
	computeDynamicScroll();
	scroller->setPosConstraints(posContainerX + posX[0], posContainerX + posX[0], posContainerY + posY[0], posContainerY + posY[0] + sprites[0].getGlobalBounds().height - scroller->getRect().height);
	updatePositions();
}

void GUI::ScrollBar::updatePositions()
{
	posX[1] = posX[0];

	updateAbsolute();
}

void GUI::ScrollBar::updateTexture(sf::Event& evnt)
{
	minY = widgetsLinked[0]->getRect().top;
	maxY = widgetsLinked[0]->getRect().top;
	minX = widgetsLinked[0]->getRect().left;
	maxX = widgetsLinked[0]->getRect().left;
	int currY;
	int currYPlusHeight;
	int currX;
	int currXPlusWidth;
	for (int i = 0; i < widgetsLinked.size(); i++)//Cette boucle calcul la position absolue minimale et maximale des widgets qui sont liés à la scrollBar
	{
		if (widgetsLinked[i]->getDisplayed())
		{
			currY = widgetsLinked[i]->getRect().top;
			currYPlusHeight = currY + widgetsLinked[i]->getRect().height;

			currX = widgetsLinked[i]->getRect().left;
			currXPlusWidth = currX + widgetsLinked[i]->getRect().width;

			if (currY < minY)
			{
				minY = currY;
			}

			if (currYPlusHeight > maxY)
			{
				maxY = currYPlusHeight;
			}

			if (currX < minX)
			{
				minX = currX;
			}

			if (currYPlusHeight > maxY)
			{
				maxX = currXPlusWidth;
			}
		}
	}

	if (evnt.type == sf::Event::MouseWheelScrolled)
	{
		if (evnt.mouseWheelScroll.x > minX && evnt.mouseWheelScroll.x < sprites[0].getGlobalBounds().left + sprites[0].getGlobalBounds().width && evnt.mouseWheelScroll.y > minY && \
			evnt.mouseWheelScroll.y < sprites[0].getGlobalBounds().top + sprites[0].getGlobalBounds().height)
		{
			if (scroller->getRelativePosY() - evnt.mouseWheelScroll.delta * 15 < posY[0])
			{
				scroller->setPosition(posX[0], posY[0]);
			}
			else if (scroller->getRelativePosY() + scroller->getRect().height - evnt.mouseWheelScroll.delta * 15 > posY[0] + sprites[0].getGlobalBounds().height)
			{
				scroller->setPosition(posX[0], posY[0] + sprites[0].getGlobalBounds().height - scroller->getRect().height);
			}
			else
			{
				scroller->move(0, -evnt.mouseWheelScroll.delta * 15);
				evnt.mouseWheelScroll.delta = 0;
			}
		}
	}
	if (posY[1] != scroller->getRelativePosY())
	{
		if (hasContainer)
		{
			containerLinked->move(0, (-scroller->getRelativePosY() + posY[1]) * movePerPixel);
		}
		else
		{
			for (int i = 0; i < widgetsLinked.size(); i++)
			{
				widgetsLinked[i]->move(0, (-scroller->getRelativePosY() + posY[1]) * movePerPixel);
			}
		}
		posY[1] = scroller->getRelativePosY();
	}
}

void GUI::ScrollBar::computeDynamicScroll()
{
	int spriteHeight = sprites[0].getGlobalBounds().height;
	int spriteTop = sprites[0].getGlobalBounds().top;
	int scrollerHeight = scroller->getRect().height;
	int scrollerTop = scroller->getRect().top;
	minY = widgetsLinked[0]->getRect().top;
	maxY = widgetsLinked[0]->getRect().top;
	int currY;
	int currYPlusHeight;

	for (int i = 0; i < widgetsLinked.size(); i++)//Cette boucle calcul la position absolue minimale et maximale des widgets qui sont liés à la scrollBar
	{
		if (widgetsLinked[i]->getDisplayed())
		{
			currY = widgetsLinked[i]->getRect().top;
			currYPlusHeight = currY + widgetsLinked[i]->getRect().height;

			if (currY < minY)
			{
				minY = currY;
			}

			if (currYPlusHeight > maxY)
			{
				maxY = currYPlusHeight;
			}
		}
	}
	if (maxY - minY > spriteHeight)//Si la taille totale des widget linked est plus grande que la taille de la scrollbar, il faut la redimensionner
	{
		if (spriteHeight - (maxY - minY - spriteHeight) < minHeightBar)//Si on atteint la taille minimale on modifie aussi le nombre de déplacements par pixels
		{
			scroller->resize(scroller->getRect().width, minHeightBar);
			scrollerHeight = scroller->getRect().height;
			movePerPixel = float(((maxY - minY) - spriteHeight)) / (spriteHeight - scrollerHeight);
			hasBeenResized = true;

			replaceScroller(maxY);
			replaceScrollerWidgets(maxY, spriteHeight, spriteTop, scrollerHeight);
		}
		else//On redimensionne juste la scrollbar
		{
			scroller->resize(scroller->getRect().width, spriteHeight - (maxY - minY - spriteHeight));
			scrollerHeight = scroller->getRect().height;
			hasBeenResized = true;

			if (movePerPixel != 1)//Si le déplacement par pixel a été modifié il faut, avant de le remettre à 1, replacer les widgets en bas et la scrollabar en bas s'ils sont plus haut que le bas de la scrollbar
			{
				replaceScrollerWidgets(maxY, spriteHeight, spriteTop, scrollerHeight);
			}

			movePerPixel = 1;
			replaceScroller(maxY);
		}

		if (maxY < spriteTop + spriteHeight)//Si la scrollbar dépasse sa limite du bas on la remonte
		{
			scrollToBottom();
		}
		scroller->setPosConstraints(posContainerX + posX[0], posContainerX + posX[0], posContainerY + posY[0], posContainerY + posY[0] + spriteHeight - scrollerHeight);
	}
	else//On remet la scrollbar à sa taille normale
	{
		scroller->resize(scroller->getRect().width, sprites[0].getGlobalBounds().height);
		scrollerHeight = scroller->getRect().height;

		scroller->setPosConstraints(posContainerX + posX[0], posContainerX + posX[0], posContainerY + posY[0], posContainerY + posY[0] + spriteHeight - scrollerHeight);
		if (hasBeenResized)
		{
			scrollToTop();
			hasBeenResized = false;
		}
	}
}

void GUI::ScrollBar::replaceScroller(int maxY)
{
	if (maxY > sprites[0].getGlobalBounds().top + sprites[0].getGlobalBounds().height)
	{
		int distanceToDo = maxY - (sprites[0].getGlobalBounds().top + sprites[0].getGlobalBounds().height);
		posY[1] = (posY[0] + sprites[0].getGlobalBounds().height - scroller->getRect().height) - distanceToDo / movePerPixel;
		scroller->setPosition(posX[0], posY[1]);
	}
}

void GUI::ScrollBar::replaceScrollerWidgets(int maxY, int spriteHeight, int spriteTop, int scrollerHeight)
{
	if (maxY < spriteHeight + spriteTop)
	{
		int distance = spriteHeight + spriteTop - maxY;
		for (int i = 0; i < widgetsLinked.size(); i++)
		{
			widgetsLinked[i]->move(0, distance);
		}
		posY[1] = posY[0] + spriteHeight  - scrollerHeight;
		scroller->setPosition(posX[0], posY[1]);
	}
}

void GUI::ScrollBar::scrollToBottom()
{
	int distance = sprites[0].getGlobalBounds().top + sprites[0].getGlobalBounds().height - (scroller->getRect().top + scroller->getRect().height);
	for (int i = 0; i < widgetsLinked.size(); i++)
	{
		widgetsLinked[i]->move(0, -distance * movePerPixel);
	}
	posY[1] = posY[0] + sprites[0].getGlobalBounds().height - scroller->getRect().height;
	scroller->setPosition(posX[0], posY[1]);
}

void GUI::ScrollBar::scrollToTop()
{
	int distance = scroller->getRect().top - sprites[0].getGlobalBounds().top;
	for (int i = 0; i < widgetsLinked.size(); i++)
	{
		widgetsLinked[i]->move(0, distance * movePerPixel);
	}
	posY[1] = posY[0];
	scroller->setPosition(posX[0], posY[1]);
	updatePositions();
}

bool GUI::ScrollBar::isMaxBot()
{
	if (scroller->getRelativePosY() + scroller->getRect().height == posY[0] + sprites[0].getGlobalBounds().height)
	{
		return true;
	}
	return false;
}

GUI::Label::Label(std::string ID, int posX, int posY, std::string text, std::string font, int fontSize, sf::Color color, sf::Text::Style fontStyle) : Widget(ID, posX, posY, "NONE")
{
	this->widgetType = "Label";
	this->fontSize = fontSize;

	this->labelText = text;
	previousText = labelText;
	if (!this->font.loadFromFile("Data/Fonts/" + font))
	{
		std::cout << "Error opening font while creating " << this->ID << std::endl;
	}
	selector.push_back(Display::Text);
	this->text.push_back(sfe::RichText(this->font));
	this->text[0].setCharacterSize(fontSize);
	this->text[0] << color << fontStyle << text;

	setTexture();
}

GUI::Label::Label(std::string ID, int posX, int posY, std::string font, int fontSize) : Widget(ID, posX, posY, "NONE")
{
	this->widgetType = "Label";
	this->fontSize = fontSize;

	this->labelText = "";
	previousText = labelText;
	if (!this->font.loadFromFile("Data/Fonts/" + font))
	{
		std::cout << "Error opening font while creating " << this->ID << std::endl;
	}
	selector.push_back(Display::Text);
	this->text[0] = sfe::RichText(this->font);

	attributes->createBaseAttribute(convertPath(this->ID), "type", "str", widgetType);

	createAttribute("text", this->labelText, "string");
	createAttribute("font", fontString, "string");
	createAttribute("fontSize", this->fontSize, "int");
}

void GUI::Label::resetFontVars(std::string text, std::string font, int fontSize, sf::Color color, sf::Text::Style fontStyle)
{
	setFont(font);
	setFontSize(fontSize);
	setText(text, color, fontStyle);
	updatePositions();
}

void GUI::Label::setFont(std::string font)
{
	font.erase(std::remove(font.begin(), font.end(), '\n'), font.end());
	if (!this->font.loadFromFile("Data/Fonts/" + font))
	{
		std::cout << "Error opening font while creating " << ID << std::endl;
	}
	text[0].setFont(this->font);
}

void GUI::Label::setText(std::string text, sf::Color color, sf::Text::Style style)
{
	labelText = text;
	previousText = text;
	this->text[0].clear();
	this->text[0] << color << style << text;
}

void GUI::Label::setComplexText(std::string complexText)
{
	text[0].clear();
	sf::Color currColor = sf::Color::Black;
	sf::Text::Style currStyle = sf::Text::Regular;
	std::vector<std::string> markups = fn::String::extractBetween(complexText, '<', '>');
	fn::String::removeCharFromString(complexText, "<");
	std::vector<std::string> texts = fn::String::split(complexText, ">");

	for (int i = 0; i < markups.size(); i++)
	{
		std::vector<std::string> splitMarkups = fn::String::split(markups[i], ";");
		for (int j = 0; j < splitMarkups.size(); j++)
		{
			std::vector<std::string> splitProp = fn::String::split(splitMarkups[j], ":");
			if (splitProp[0] == "color")
			{
				std::vector<std::string> splitColor = fn::String::split(splitProp[1], ",");
				if (splitColor.size() == 4)
					currColor = sf::Color(std::stoi(splitColor[0]), std::stoi(splitColor[1]), std::stoi(splitColor[2]), std::stoi(splitColor[3]));
				else if(splitColor.size() == 3)
					currColor = sf::Color(std::stoi(splitColor[0]), std::stoi(splitColor[1]), std::stoi(splitColor[2]));
			}
			else if (splitProp[0] == "style")
			{
				std::vector<std::string> splitProp = fn::String::split(splitMarkups[j], ":");
				if(splitProp[1] == "regular")
				{
					currStyle = sf::Text::Regular;
				}
				else if (splitProp[1] == "underlined")
				{
					currStyle = sf::Text::Underlined;
				}
				else if (splitProp[1] == "bold")
				{
					currStyle = sf::Text::Bold;
				}
				else if (splitProp[1] == "italic")
				{
					currStyle = sf::Text::Italic;
				}
				else if(splitProp[1] == "strikeThrough")
				{
					currStyle = sf::Text::StrikeThrough;
				}
			}
		}
		if(texts.size() >= i + 1)
			text[0] << currColor << currStyle << texts[i];
	}
}

void GUI::Label::addText(std::string text, sf::Color color, sf::Text::Style style)
{
	labelText += text;
	previousText = labelText;
	this->text[0] << color << style << text;
}

void GUI::Label::setFontSize(int fontSize)
{
	this->fontSize = fontSize;
	this->text[0].setCharacterSize(fontSize);
}

std::string GUI::Label::getFontName()
{
	return fontString;
}

int GUI::Label::getfontSize()
{
	return fontSize;
}

void GUI::Label::centerInRect(sf::Rect<float> rect)
{
	int newAbsX = rect.left + rect.width / 2 - text[0].getGlobalBounds().width / 2;
	int newAbsY = rect.top + rect.height / 2 - text[0].getGlobalBounds().height / 2;
	this->setPosition(newAbsX - posContainerX, newAbsY - posContainerY);
}

void GUI::Label::setTexture()
{
	updatePositions();
}

void GUI::Label::updateTexture(sf::Event& evnt)
{
	if (labelText != previousText)
	{
		this->text[0] << labelText;
		previousText = labelText;
	}
}

std::string GUI::Label::getString()
{
	return labelText;
}

std::string* GUI::Label::getHook()
{
	return &labelText;
}

sfe::RichText * GUI::Label::getRichText()
{
	return &text[0];
}

void GUI::Label::updateAttributes()
{
	/*sf::Text empty;
	text[0] = empty;
	setFont(fontString);
	text[0].setString(labelText);
	text[0].setCharacterSize(fontSize);
	text[0].setColor(fontColor.getSfColor());
	text[0].setStyle(sf::Text::Regular);
	updatePositions();*/
}

void GUI::Checkbox::setTexture()
{
	sprites.clear();
	sprites.resize(1);

	if (checked)
	{
		setTextureMap(&sprites[0], nameImageChecked);
	}
	else
	{
		setTextureMap(&sprites[0], nameImageUnchecked);
	}
	updatePositions();
}

void GUI::Checkbox::updateTexture(sf::Event& evnt)
{
	hasChanged = false;
	if (previousValue != checked)
	{
		clicked();
	}
	if (LeftClickReleased)
	{
		if (isRectClicked(evnt, sprites[0].getGlobalBounds(), true, false))
		{
			clicked();
		}
	}
	if (evnt.type == sf::Event::MouseButtonReleased && evnt.mouseButton.button == sf::Mouse::Left)
	{
		LeftClickReleased = true;
	}
}

void GUI::Checkbox::updateAttributes()
{
	if (checked)
	{
		setChecked();
	}
	else
	{
		setUnchecked();
	}
}

void GUI::Checkbox::clicked()
{
	hasChanged = true;
	if (checked)
	{
		setUnchecked();
	}
	else
	{
		setChecked();
	}
}

void GUI::Checkbox::setChecked()
{
	hasChanged = true;
	checked = true;
	previousValue = true;
	setTextureMap(&sprites[0], nameImageChecked);
}

void GUI::Checkbox::setUnchecked()
{
	hasChanged = true;
	checked = false;
	previousValue = false;
	setTextureMap(&sprites[0], nameImageUnchecked);
}

bool GUI::Checkbox::isChecked()
{
	return checked;
}

bool GUI::Checkbox::getToggled()
{
	return hasChanged;
}

bool* GUI::Checkbox::getHook()
{
	return &checked;
}

void GUI::Checkbox::setText(std::string text, std::string font, sf::Color fontColor, int fontSize, bool centered, int relativeX, int relativeY, sf::Text::Style fontStyle)
{

	if (!hasText)
	{
		absolutesX.resize(2);
		absolutesY.resize(2);
		posX.resize(2);
		posY.resize(2);

		selector.push_back(Display::WidgetContained);
		checkboxLabel = new Label(ID + "text", 0, 0, text, font, fontSize, fontColor, fontStyle);
		checkboxLabel->setAbsolute(posContainerX, posContainerY);
		checkboxLabel->setSpritesPositions();
		addContainedItem(checkboxLabel->getDataObject());
		hasText = true;
		widgetsContained.push_back(checkboxLabel);
	}
	else
	{
		checkboxLabel->resetFontVars(text, font, fontSize, fontColor, fontStyle);
	}
	posTextX = relativeX;
	posTextY = relativeY;
	textCentered = centered;
	updatePositions();
}

void GUI::Checkbox::updatePositions()
{
	if (hasText)
	{
		if (!textCentered)
		{
			posX[1] = posX[0] + posTextX;
			posY[1] = posY[0] + posTextY;
		}
		else
		{
			posX[1] = posX[0] + sprites[0].getGlobalBounds().width / 2 - checkboxLabel->getRect().width / 2;
			posY[1] = posY[0] + sprites[0].getGlobalBounds().height / 2 - checkboxLabel->getRect().height / 2;
		}
	}
	updateAbsolute();
}

void GUI::Checkbox::setTextureChecked(sf::Texture& texture)
{
	widgetTextures[nameImageChecked] = texture;
	setTexture();
}
void GUI::Checkbox::setTextureUnchecked(sf::Texture& texture)
{
	widgetTextures[nameImageUnchecked] = texture;
	setTexture();
}

GUI::Checkbox::Checkbox(std::string ID, int posX, int posY, std::string style, bool checked) : Widget(ID, posX, posY, style)
{
	this->widgetType = "Checkbox";	
	this->checked = checked;
	previousValue = checked;
	selector.push_back(Display::Sprite);

	attributes->createBaseAttribute(convertPath(this->ID), "type", "str", widgetType);
	createAttribute("checked", this->checked, "bool");
}

GUI::Droplist::Droplist(std::string ID, int posX, int posY, int charSize, bool droplistMenu, std::string style, std::string title, std::vector<std::string> list, std::string font, sf::Color fontColorIdle, sf::Color fontColorHover) : Widget(ID, posX, posY, style)
{
	this->widgetType = "Droplist";
	this->droplistMenu = droplistMenu;
	this->list = list;
	if (droplistMenu)
	{
		this->list.insert(this->list.begin(), title);
	}
	else if (find(this->list.begin(), this->list.end(), title) != this->list.end())
	{
		std::vector<std::string>::iterator it = find(this->list.begin(), this->list.end(), title);
		this->list.insert(this->list.begin(), title);
		currentIndex = it - this->list.begin();
		previousIndex = currentIndex;
	}
	else if (!droplistMenu)
	{
		this->list.insert(this->list.begin(), this->list[0]);
		currentIndex = 0;
		previousIndex = currentIndex;
	}
	this->font = font;
	this->idle = fontColorIdle;
	this->hover = fontColorHover;
	this->charSize = charSize;

	attributes->createBaseAttribute(convertPath(ID), "type", "str", widgetType);

	buttons.resize(this->list.size());

	if (this->list.size() > 0)
	{
		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i] = new Button(ID + "button" + std::to_string(i), 0, 0, "DEFAULT", true, true);
			buttons[i]->autoLoad();
			buttons[i]->setAbsolute(posContainerX, posContainerY);

			buttons[i]->setText(this->list[i], font, fontColorIdle, charSize, true);
			widgetsContained.push_back(buttons[i]);
			if (i != 0) buttons[i]->setDisplayed(true);
			addContainedItem(buttons[i]->getDataObject());
		}
	}
}

GUI::Droplist::Droplist(std::string ID, int posX, int posY, bool dropListMenu, std::string title, std::vector<GUI::Button*> buttons, std::string style) : Widget(ID, posX, posY, style)
{
	this->widgetType = "Droplist";
	this->droplistMenu = droplistMenu;
	this->buttons = buttons;
	attributes->createBaseAttribute(convertPath(ID), "type", "str", widgetType);
	for (int i = 0; i < this->buttons.size(); i++)
	{
		buttons[i]->updatePosContainer(posContainerX, posContainerY);
		if (i == 0)
		{
			buttons[i]->setTextureIdle(widgetTextures[nameImageFirstIdle]);
			buttons[i]->setTexturePushed(widgetTextures[nameImageFirstPushed]);
			buttons[i]->setTextureHover(widgetTextures[nameImageFirstHover]);
		}
		else
		{
			buttons[i]->setTextureIdle(widgetTextures[nameImageIdle]);
			buttons[i]->setTexturePushed(widgetTextures[nameImagePushed]);
			buttons[i]->setTextureHover(widgetTextures[nameImageHover]);
		}

		widgetsContained.push_back(buttons[i]);
		list.push_back(buttons[i]->getString());
		if (i != 0) buttons[i]->setDisplayed(false);
	}

	if (droplistMenu)
	{
		this->list.insert(this->list.begin(), title);
	}
	else if (find(this->list.begin(), this->list.end(), title) != this->list.end())
	{
		std::vector<std::string>::iterator it = find(this->list.begin(), this->list.end(), title);
		this->list.insert(this->list.begin(), title);
		currentIndex = it - this->list.begin();
		previousIndex = currentIndex;
	}

	for (int i = 0; i < this->buttons.size(); i++)
	{
		buttons[i]->changeText(list[i], sf::Color::Black, sf::Text::Regular);
		addContainedItem(buttons[i]->getDataObject());
	}
	this->font = "arial.ttf";
	this->charSize = 12;
	this->idle = sf::Color::Black;
	this->hover = sf::Color::Black;
}

void GUI::Droplist::setTexture()
{
	this->posX.resize(this->list.size());
	this->posY.resize(this->list.size());
	absolutesX.resize(1);
	absolutesY.resize(1);
	for (int i = 0; i < buttons.size(); i++)
	{
		if (i == 0)
		{
			buttons[i]->setTextureIdle(widgetTextures[nameImageFirstIdle]);
			buttons[i]->setTexturePushed(widgetTextures[nameImageFirstPushed]);
			buttons[i]->setTextureHover(widgetTextures[nameImageFirstHover]);
		}
		else
		{
			buttons[i]->setTextureIdle(widgetTextures[nameImageIdle]);
			buttons[i]->setTexturePushed(widgetTextures[nameImagePushed]);
			buttons[i]->setTextureHover(widgetTextures[nameImageHover]);
		}
	}
	selector.resize(1);
	selector[0] = Display::WidgetContained;
	updatePositions();
}

void GUI::Droplist::setUnfold()
{
	extended = false;
	selector.resize(1);
	absolutesX.resize(1);
	absolutesY.resize(1);
	for (int i = 1; i < buttons.size(); i++)
	{
		buttons[i]->setDisplayed(false);
	}
}

void GUI::Droplist::setFoldUp()
{
	selector.resize(widgetsContained.size());
	absolutesX.resize(widgetsContained.size());
	absolutesY.resize(widgetsContained.size());
	extended = true;
	for (int i = 1; i < selector.size(); i++)
	{
		selector[i] = Display::WidgetContained;
		buttons[i]->setDisplayed(true);
	}
	updatePositions();
}

void GUI::Droplist::addOption(std::string str, int position)
{
	if (position >= 0 && position < list.size())
	{

	}
}

void GUI::Droplist::addDefaultOption()
{
	list.push_back("default");
	this->posX.resize(this->list.size());
	this->posY.resize(this->list.size());
	absolutesX.resize(this->list.size());
	absolutesY.resize(this->list.size());
	buttons.push_back(new Button(ID + "button" + std::to_string(list.size() - 1), 0, 0, "DEFAULT", true, true));
	buttons.back()->autoLoad();
	buttons.back()->setAbsolute(posContainerX, posContainerY);
	buttons.back()->setText(this->list.back(), font, sf::Color::Black, charSize, true);
	buttons.back()->setTextureIdle(widgetTextures[nameImageIdle]);
	buttons.back()->setTexturePushed(widgetTextures[nameImagePushed]);
	buttons.back()->setTextureHover(widgetTextures[nameImageHover]);
	widgetsContained.push_back(buttons.back());
	if (!extended)
	{
		buttons.back()->setDisplayed(false);
	}
	else
	{
		buttons.back()->setDisplayed(true);
		selector.push_back(Display::WidgetContained);
	}

	addContainedItem(buttons.back()->getDataObject());
	updatePositions();
}

std::map<std::string, std::function<void()>> GUI::Droplist::getFunctions()
{
	std::map<std::string, std::function<void()>> functions;
	functions["Add option"] = std::bind(&GUI::Droplist::addDefaultOption, this);
	return functions;
}

int* GUI::Droplist::getHook()
{
	return &currentIndex;
}


void GUI::Droplist::updateTexture(sf::Event& evnt)
{
	elementClicked = "NONE";
	if (addedElement)
	{
		setTexture();
	}
	if (previousIndex != currentIndex)
	{
		changeTitle(buttons[currentIndex + 1]->getString());
		previousIndex = currentIndex;
	}

	if (extended)
	{
		for (int i = 1; i < buttons.size(); i++)
		{
			if (buttons[i]->getJustClicked())
			{
				if (!droplistMenu)
				{
					changeTitle(buttons[i]->getString());
					currentIndex = i - 1;
					previousIndex = currentIndex;
				}
				elementClicked = buttons[i]->getString();
				setUnfold();
			}
		}
	}
	if (LeftClickReleased && buttons[0]->getJustClicked())
	{
		if (extended)
		{
			setUnfold();
		}
		else
		{
			setFoldUp();
		}
	}
	if (evnt.type == sf::Event::MouseButtonReleased && evnt.mouseButton.button == sf::Mouse::Left)
	{
		LeftClickReleased = true;
	}
}


void GUI::Droplist::changeTitle(std::string newTitle)
{
	list[0] = newTitle;
	buttons[0]->changeText(newTitle, this->idle, sf::Text::Regular);
}

std::string GUI::Droplist::getCurrentSelected()
{
	return list[0];
}

std::string GUI::Droplist::getElementClicked()
{
	return elementClicked;
}

void GUI::Droplist::setSelected(int index)
{
	currentIndex = index;
	previousIndex = currentIndex;
	changeTitle(list[index + 1]);
}

bool GUI::Droplist::isExtended()
{
	return extended;
}


void GUI::Droplist::updatePositions()
{
	sf::Rect<float> rect;
	sf::Rect<float> textrect;
	for (int i = 1; i < selector.size(); i++)
	{
		posX[i] = posX[0];
		posY[i] = posY[i - 1] + widgetsContained[i - 1]->getRect().height;
	}
	updateAbsolute();
}

int GUI::Droplist::getNbElement()
{
	return buttons.size();
}

GUI::Tab::Tab(std::string ID, int posX, int posY, int charSize, std::string font, sf::Color fontColor, std::vector<std::string> tabsNames, std::vector<WidgetContainer*> tabs, std::string style) : Widget(ID, posX, posY, style)
{
	this->widgetType = "Tab";
	this->tabsNames = tabsNames;
	this->tabContainer = tabs;
	if (tabsNames.size() != tabs.size())
	{
		std::cout << "GUI Error : Tab " << ID << " tabsNames and widgetContainer vector are not the same size" << std::endl;
		delete this;
		return;
	}
	for (int i = 0; i < tabsNames.size(); i++)
	{
		if (i == 0)
			tabCheckboxes.push_back(new RadioButton(ID + "checkbox" + tabsNames[i], 0, 0, tabsNames[i], ID, "DEFAULT", true));
		else
		{
			tabCheckboxes.push_back(new RadioButton(ID + "checkbox" + tabsNames[i], 0, 0, tabsNames[i], ID, "DEFAULT", false));
		}

		tabCheckboxes[i]->autoLoad();
		tabCheckboxes[i]->setAbsolute(posContainerX, posContainerY);

		tabCheckboxes[i]->setText(tabsNames[i], font, fontColor, charSize, true);

		widgetsContained.push_back(tabCheckboxes[i]);
		selector.push_back(GUI::Display::WidgetContained);
	}

	for (int i = 1; i < tabs.size(); i++)
	{
		tabs[i]->setDisplayed(false);
	}
}

void GUI::Tab::setTexture()
{
	posX.resize(tabCheckboxes.size());
	posY.resize(tabCheckboxes.size());
	absolutesX.resize(tabCheckboxes.size());
	absolutesY.resize(tabCheckboxes.size());
	for (int i = 0; i < tabCheckboxes.size(); i++)
	{
		tabCheckboxes[i]->setTextureChecked(widgetTextures[nameImageChecked]);
		tabCheckboxes[i]->setTextureUnchecked(widgetTextures[nameImageUnchecked]);
	}
	updatePositions();
}

void GUI::Tab::updatePositions()
{
	tabCheckboxes[0]->setSpritesPositions();
	for (int i = 1; i < tabCheckboxes.size(); i++)
	{
		posX[i] = posX[i - 1] + tabCheckboxes[i - 1]->getRect().width;
		posY[i] = posY[0];
	}
	updateAbsolute();
}

void GUI::Tab::updateTexture(sf::Event& evnt)
{
	for (int i = 0; i < tabCheckboxes.size(); i++)
	{
		if (tabCheckboxes[i]->getToggled())
		{
			if (tabCheckboxes[i]->isChecked())
			{
				tabContainer[i]->setDisplayed(true);
				break;
			}
		}
	}

	for (int i = 0; i < tabCheckboxes.size(); i++)
	{
		if (tabContainer[i]->getDisplayed() && !tabCheckboxes[i]->isChecked())
		{
			tabContainer[i]->setDisplayed(false);
		}
	}
}

void GUI::Tab::addTab(std::string tabName, WidgetContainer* newTab)
{
	tabContainer.push_back(newTab);
	tabsNames.push_back(tabName);
}

void GUI::Tab::removeTab(std::string tabName)
{
	std::vector<std::string>::iterator position = std::find(tabsNames.begin(), tabsNames.end(), tabName);
	tabsNames.erase(std::remove(tabsNames.begin(), tabsNames.end(), tabName), tabsNames.end());
	tabContainer.erase(tabContainer.begin() + int(position - tabsNames.begin()));
}

void GUI::Tab::setDisplayed(bool displayed)
{
	for (int i = 0; i < tabContainer.size(); i++)
	{
		tabCheckboxes[i]->setDisplayed(displayed);
		tabContainer[i]->setDisplayed(displayed);
	}
}

std::string GUI::Tab::getCurrentTab()
{
	return GUI::RadioButton::getCurrentSelected(tabCheckboxes.front()->getGroup());
}

void GUI::Tab::setCurrentTab(std::string tabName)
{
	int pos = std::find(tabsNames.begin(), tabsNames.end(), tabName) - tabsNames.begin();
	tabCheckboxes[pos]->setChecked();
	for (int i = 0; i < tabContainer.size(); i++)
	{
		if (tabContainer[i]->getDisplayed())
		{
			tabContainer[i]->setDisplayed(false);
		}
	}
	tabContainer[pos]->setDisplayed(true);
}


GUI::Dropbox::Dropbox(std::string ID, int posX, int posY, std::string style) : Widget(ID, posX, posY, style)
{
	this->widgetType = "Dropbox";
	selector.push_back(GUI::Display::Sprite);
	attributes->createBaseAttribute(convertPath(this->ID), "type", "str", widgetType);
}

void GUI::Dropbox::setTexture()
{
	sprites.resize(1);
	setTextureMap(&sprites[0], nameImageBox);
}

bool GUI::Dropbox::getContainMovable()
{
	return containMovable;
}

GUI::Movable* GUI::Dropbox::getMovable()
{
	return currentMovable;
}

void GUI::Dropbox::setCurrentMovable(Movable* movable, int posX, int posY)
{
	currentMovable = movable;
	containMovable = true;

	currentMovable->setAbsolute(posContainerX, posContainerY);
	widgetsContained.resize(1);
	widgetsContained[0] = movable;
	absolutesX.resize(2);
	absolutesY.resize(2);
	this->posX.resize(2);
	this->posY.resize(2);

	this->posX[1] = this->posX[0] + posX;
	this->posY[1] = this->posY[0] + posY;
}

void GUI::Dropbox::updateTexture(sf::Event& evnt)
{

}

void GUI::Dropbox::setContainMovable(bool contain)
{
	if (!contain)
	{
		containMovable = false;
		currentMovable = NULL;
		widgetsContained.resize(0);
	}
}

GUI::Movable::Movable(std::string ID, int posX, int posY, std::string style) : Widget(ID, posX, posY, style)
{
	this->widgetType = "Movable";
	this->needContainer = false;
	selector.push_back(GUI::Display::Sprite);

	attributes->createBaseAttribute(convertPath(this->ID), "type", "str", widgetType);
}

GUI::Movable::Movable(std::string ID, Dropbox* container, int marginLeftContainer, int marginTopContainer, std::string style) : Widget(ID, container->getRelativePosX() + marginLeftContainer, container->getRelativePosY() + marginTopContainer, style)
{
	this->widgetType = "Movable";
	this->needContainer = true;
	container->setCurrentMovable(this, marginLeftContainer, marginTopContainer);
	this->marginLeftContainer = marginLeftContainer;
	this->marginTopContainer = marginTopContainer;
	this->currentContainer = container;
	selector.push_back(GUI::Display::Sprite);

	attributes->createBaseAttribute(convertPath(this->ID), "type", "str", widgetType);
}


void GUI::Movable::setTexture()
{
	posX.resize(1);
	posY.resize(1);
	sprites.resize(1);
	setTextureMap(&sprites[0], nameImage);

	updatePositions();
}

void GUI::Movable::setPosConstraints(int posXMin, int posXMax, int posYMin, int posYMax)
{
	hasPosConstraints = true;

	this->posXMin = posXMin;
	this->posXMax = posXMax;

	this->posYMin = posYMin;
	this->posYMax = posYMax;
}


void GUI::Movable::setMovementConstraints(bool verticalConstraint, bool horizontalConstraint)
{
	this->hasVerticalConstaint = verticalConstraint;
	this->hasHorizontalConstraint = horizontalConstraint;
}

void GUI::Movable::setTextWithPos(std::string font, std::string text, int characSize, sf::Color color, int posX, int posY, bool isResized)
{
	if (posX < absolutesX[0] + width && posY < absolutesY[0] + height)
	{
		posXText = posX;
		posYText = posY;
		textHasPos = true;
		if (!hasText)
		{
			selector.resize(3);
			selector[2] = GUI::Display::WidgetContained;
			labelText = new GUI::Label(ID + "textLabel", 0, 0, font, characSize);
			labelText->setAbsolute(posContainerX, posContainerY);
			widgetsContained.push_back(labelText);
			absolutesX.resize(3);
			absolutesY.resize(3);
			this->posX.resize(3);
			this->posY.resize(3);
		}

		labelText->setText(text, color, sf::Text::Regular);

		int i = 0;
		hasText = true;
		fullText = text;
		displayedText = fullText;

		this->posX[2] = this->posX[0] + posX;
		this->posY[2] = this->posY[0] + posY;
		labelText->setPosition(this->posX[2], this->posY[2]);

		labelText->setSpritesPositions();
		sf::Rect<float> rect = labelText->getRect();
		if (isResized)
		{
			while (rect.left + rect.width > absolutesX[0] + width)
			{
				i++;
				labelText->setFontSize(characSize - i);
				rect = labelText->getRect();
			}
		}
		else
		{
			while (rect.left + rect.width > absolutesX[0] + width)
			{
				displayedText.erase(displayedText.end() - 1);
				labelText->setText(displayedText, color, sf::Text::Regular);
				rect = labelText->getRect();
			}
		}
	}
	updatePositions();
}


void GUI::Movable::setText(std::string font, std::string text, int characSize, sf::Color color)
{
	if (!hasText && !hasSprite)
	{
		selector.resize(3);
		selector[2] = GUI::Display::WidgetContained;
		labelText = new GUI::Label(ID + "textLabel", 0, 0, font, characSize);
		labelText->setAbsolute(posContainerX, posContainerY);
		widgetsContained.push_back(labelText);
		absolutesX.resize(3);
		absolutesY.resize(3);
		this->posX.resize(3);
		this->posY.resize(3);
	}
	else if (!hasText)
	{
		selector[1] = GUI::Display::WidgetContained;
		labelText = new GUI::Label(ID + "textLabel", 0, 0, font, characSize);
		labelText->setAbsolute(posContainerX, posContainerY);
		widgetsContained.push_back(labelText);
	}

	labelText->setText(text, color, sf::Text::Regular);
	hasText = true;

	if (hasSprite)
	{
		sprites[1] = sf::Sprite();
		setTextureMap(&sprites[1], "texture");
		sprites[1].setPosition(absolutesX[1], absolutesY[1]);
		sprites[1].setScale(static_cast<float>(height - marginTop * 2) / sprites[1].getGlobalBounds().height, static_cast<float>((height - marginTop * 2)) / sprites[1].getGlobalBounds().height);

		posX[2] = posX[1] + sprites[1].getGlobalBounds().width + 5;
		posY[2] = posY[0] + height / 2 - labelText->getRect().height / 2;
		//adapter automatiquement la taille de la police..
	}
	else
	{
		posX[2] = posX[0] + width / 2 - labelText->getRect().width / 2;
		posY[2] = posY[0] + height / 2 - labelText->getRect().height / 2;
	}
}

void GUI::Movable::setPicture(std::string texturePath, int marginLeft, int marginTop)
{
	if (!hasSprite || !hasText)
	{
		absolutesX.resize(2);
		absolutesY.resize(2);
		sprites.resize(2);
		selector.resize(2);
		this->posX.resize(2);
		this->posY.resize(2);
		selector[1] = GUI::Display::Sprite;
	}
	hasSprite = true;
	this->marginLeft = marginLeft;
	this->marginTop = marginTop;
	widgetTextures["texture"].loadFromFile(texturePath);
	setTextureMap(&sprites[1], "texture");
	posX[1] = posX[0] + marginLeft;
	posY[1] = posY[0] + marginTop;
	updatePositions();
	sprites[1].setPosition(absolutesX[1], absolutesY[1]);
	if (hasText)
	{
		sprites[1].setScale(static_cast<float>((height - marginLeft * 2)) / sprites[1].getGlobalBounds().height, static_cast<float>((height - marginTop * 2)) / sprites[1].getGlobalBounds().height);

		posX[2] = posX[1] + sprites[1].getGlobalBounds().width + 5;
		posY[2] = posY[0] + height / 2 - labelText->getRect().height / 2;
	}
	else
	{
		sprites[1].setScale(static_cast<float>((width - marginLeft * 2)) / sprites[1].getGlobalBounds().width, static_cast<float>((height - marginTop * 2)) / sprites[1].getGlobalBounds().height);
	}
}

void GUI::Movable::resize(int width, int height)
{
	this->width = width;
	this->height = height;
	if (hasText && hasSprite)
	{
		sprites[1].setScale(static_cast<float>((height - marginLeft * 2)) / sprites[1].getGlobalBounds().height, static_cast<float>((height - marginTop * 2)) / sprites[1].getGlobalBounds().height);

		posX[2] = posX[1] + sprites[1].getGlobalBounds().width + 5;
		posY[2] = posY[0] + height / 2 - labelText->getRect().height / 2;
	}
	else if (hasText)
	{
		posX[2] = posX[0] + width / 2 - labelText->getRect().width / 2;
		posY[2] = posY[0] + height / 2 - labelText->getRect().height / 2;
	}
	else if (hasSprite)
	{
		sprites[1].setScale(static_cast<float>((width - marginLeft * 2)) / sprites[1].getGlobalBounds().width, static_cast<float>((height - marginTop * 2)) / sprites[1].getGlobalBounds().height);
	}
	sprites[0].scale(width / sprites[0].getGlobalBounds().width, height / sprites[0].getGlobalBounds().height);
}

void GUI::Movable::updateTexture(sf::Event& evnt)
{
		sf::Rect<float> rect;
		if (LeftClickReleased && isRectClicked(evnt, sprites[0].getGlobalBounds(), true, false))
		{
			isHolding = true;
			currentShiftX = (convertMousePosX(evnt.mouseButton.x) - absolutesX[0]);
			currentShiftY = (convertMousePosY(evnt.mouseButton.y) - absolutesY[0]);
		}

		if (isHolding && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			LeftClickReleased = true;
			isHolding = false;
			releasing(evnt);
		}
		if (isHolding && evnt.type == sf::Event::MouseMoved)
		{
			holding(evnt);
		}
		if (hasPosConstraints)
		{
			if (absolutesY[0] < posYMin)
			{
				absolutesY[0] = posYMin;
			}
			else if (absolutesY[0] > posYMax)
			{
				absolutesY[0] = posYMax;
			}
			if (absolutesX[0] < posXMin)
			{
				absolutesX[0] = posXMin;
			}
			else if(absolutesX[0] > posXMax)
			{
				absolutesX[0] = posXMax;
			}
			posX[0] = absolutesX[0] - posContainerX;
			posY[0] = absolutesY[0] - posContainerY;
		}
		updatePositions();
}

void GUI::Movable::updatePositions()
{

	if (hasText && hasSprite)
	{
		posX[1] = posX[0] + marginLeft;
		posY[1] = posY[0] + marginTop;
		updateAbsolute();

		posX[2] = posX[1] + sprites[1].getGlobalBounds().width + 5;
		posY[2] = posY[0] + height / 2 - labelText->getRect().height / 2;
	}
	else if (hasText)
	{
		if (textHasPos)
		{
			posX[2] = posX[0] + posXText;
			posY[2] = posY[0] + posYText;
		}
		else
		{
			posX[2] = posX[0] + width / 2 - labelText->getRect().width / 2;
			posY[2] = posY[0] + height / 2 - labelText->getRect().height / 2;
		}
	}
	else if (hasSprite)
	{
		posX[1] = posX[0] + marginLeft;
		posY[1] = posY[0] + marginTop;
	}
	updateAbsolute();
}

void GUI::Movable::holding(sf::Event& evnt)
{
	if (!hasVerticalConstaint)
	{
		int y = convertMousePosY(evnt.mouseMove.y) - currentShiftY;
		if (hasPosConstraints)
		{
			if (y < posYMin)
			{
				absolutesY[0] = posYMin;
			}
			else if (y > posYMax)
			{
				absolutesY[0] = posYMax;
			}
			else
			{
				absolutesY[0] = y;
			}
		}
		else
			absolutesY[0] = y;

	}

	if (!hasHorizontalConstraint)
	{
		int x = convertMousePosX(evnt.mouseMove.x) - currentShiftX;
		if (hasPosConstraints)
		{
			if (x < posXMin)
			{
				absolutesX[0] = posXMin;
			}
			else if (x > posXMax)
			{
				absolutesX[0] = posXMax;
			}
			else
			{
				absolutesX[0] = x;
			}
		}
		else
			absolutesX[0] = x;
	}

	posX[0] = absolutesX[0] - posContainerX;
	posY[0] = absolutesY[0] - posContainerY;
}

void GUI::Movable::releasing(sf::Event& evnt)
{
	if (needContainer)
	{
		sf::Rect<float> rect;
		std::vector<Dropbox*> dropboxes = GUI::Widget::getWidgets<Dropbox>("Dropbox");
		bool hasPos = 0;
		for (int i = 0; i < dropboxes.size(); i++)
		{
			if (dropboxes[i]->getDisplayed())
			{
				rect = dropboxes[i]->getRect();
				if (absolutesX[0] + width / 2 > rect.left && absolutesX[0] + width / 2 < rect.left + rect.width && absolutesY[0] + height / 2 > rect.top && absolutesY[0] + height / 2 < rect.top + rect.height)
				{
					currentContainer->setContainMovable(false);
					dropboxes[i]->setCurrentMovable(this, marginLeftContainer, marginTopContainer);
					currentContainer = dropboxes[i];
					absolutesX[0] = currentContainer->getRect().left + marginLeftContainer;
					absolutesY[0] = currentContainer->getRect().top + marginTopContainer;
					hasPos = 1;
				}
			}
		}
		if (!hasPos)
		{
			absolutesX[0] = currentContainer->getRect().left + marginLeftContainer;
			absolutesY[0] = currentContainer->getRect().top + marginTopContainer;
		}
	}
	posX[0] = absolutesX[0] - posContainerX;
	posY[0] = absolutesY[0] - posContainerY;
	updatePositions();
}

void GUI::Movable::containerMove(int x, int y)
{
	posX[0] = x + marginLeft;
	posY[0] = y + marginTop;
	absolutesX[0] = posX[0];
	absolutesY[0] = posY[0];
	updatePositions();
}

bool GUI::Movable::getHolding()
{
	return isHolding;
}

GUI::Button::Button(std::string ID, int posX, int posY, std::string style, bool pushingEnable, bool hoveringEnable) : Widget(ID, posX, posY, style)
{
	this->widgetType = "Button";
	this->widgetStyle = style;
	selector.push_back(Display::Sprite);

	this->pushingEnable = pushingEnable;
	this->hoveringEnable = hoveringEnable;
	this->idleEnable = true;

	this->nameImagePushed = "pushed.png";
	this->nameImageIdle = "idle.png";
	this->nameImageHover = "hover.png";

	attributes->createBaseAttribute(convertPath(this->ID), "type", "str", widgetType);
	createAttribute("pushingEnable", this->pushingEnable, "bool");
	createAttribute("hoveringEnable", this->hoveringEnable, "bool");

}

void GUI::Button::setDefaultText()
{
	setText("default", "arial.ttf", sf::Color::Black, 12, true);
}

std::map<std::string, std::function<void()>> GUI::Button::getFunctions()
{
	std::map<std::string, std::function<void()>> functions;
	functions["addText"] = std::bind(&GUI::Button::setDefaultText, this);
	return functions;
}

void GUI::Button::setText(std::string text, std::string font, sf::Color fontColor, int fontSize, bool centered, int relativeToButtonX, int relativeToButtonY, sf::Text::Style fontStyle)
{
	if (!hasText)
	{
		absolutesX.resize(2);
		absolutesY.resize(2);
		posX.resize(2);
		posY.resize(2);

		selector.push_back(Display::WidgetContained);
		buttonLabel = new Label(ID + "text", 0, 0, text, font, fontSize, fontColor, fontStyle);
		buttonLabel->setAbsolute(posContainerX, posContainerY);
		buttonLabel->setSpritesPositions();
		addContainedItem(buttonLabel->getDataObject());
		hasText = true;
		widgetsContained.push_back(buttonLabel);
	}
	else
	{
		buttonLabel->resetFontVars(text, font, fontSize, fontColor, fontStyle);
	}
	posTextX = relativeToButtonX;
	posTextY = relativeToButtonY;
	textCentered = centered;
	updatePositions();
}

void GUI::Button::changeText(std::string text, sf::Color color, sf::Text::Style style)
{
	buttonLabel->setText(text, color, style);
}

void GUI::Button::setLabelText(GUI::Label* text)
{
	if (hasText)
	{
		buttonLabel->removeWidget();
		attributes->deleteComplexAttribute(convertPath(ID), "containedItem", true);
	}

	buttonLabel = text;
	buttonLabel->setAbsolute(posContainerX, posContainerY);
	buttonLabel->setSpritesPositions();
	addContainedItem(buttonLabel->getDataObject());
	if (!hasText)
	{
		absolutesX.resize(2);
		absolutesY.resize(2);
		posX.resize(2);
		posY.resize(2);
		widgetsContained.push_back(buttonLabel);
		selector.push_back(GUI::Display::WidgetContained);
	}
	hasText = true;

	textCentered = true;
	updatePositions();
}

void GUI::Button::setDisplayed(bool displayed)
{
	this->displayed = displayed;
	if (hasText)
		buttonLabel->setDisplayed(displayed);
	if (!displayed)
	{
		currState = GUI::ButtonEvent::None;
		prevState = GUI::ButtonEvent::None;
		setUnpushed();
		LeftClickReleased = true;
	}
}

void GUI::Button::setTextureAll(const sf::Texture& texture)
{
	setTextureHover(texture);
	setTextureIdle(texture);
	setTexturePushed(texture);
}

void GUI::Button::setTextureHover(const sf::Texture& texture)
{
	widgetTextures[nameImageHover] = texture;
	hoveringEnable = true;
	setTexture();
}

void GUI::Button::setTextureIdle(const sf::Texture& texture)
{
	widgetTextures[nameImageIdle] = texture;
	idleEnable = true;
	setTexture();
}

void GUI::Button::setTexturePushed(const sf::Texture& texture)
{
	widgetTextures[nameImagePushed] = texture;
	pushingEnable = true;
	setTexture();
}

void GUI::Button::setPushed()
{
	currState = GUI::ButtonEvent::Clicked;
	prevState = GUI::ButtonEvent::Clicked;
	if(pushingEnable)
	{
		setTextureMap(&sprites[0], nameImagePushed);
	}
	if (functionBinded)
	{
		function(parameters);
	}
	if (voidFunctionBinded)
	{
		voidFunction();
	}

}

void GUI::Button::setUnpushed()
{
	currState = GUI::ButtonEvent::None;
	prevState = GUI::ButtonEvent::None;
	setTextureMap(&sprites[0], nameImageIdle);
}

void GUI::Button::updateTexture(sf::Event& evnt)
{
	if (currState == GUI::ButtonEvent::Clicked)
	{
		currState = GUI::ButtonEvent::Pressed;
		prevState = GUI::ButtonEvent::Pressed;
	}

	if (LeftClickReleased && isClicked(evnt, true, false))
	{
		setPushed();
	}
	else
	{
		if (currState == GUI::ButtonEvent::Pressed)
		{	
			if (!isClicked(evnt, true, false) && LeftClickReleased)
			{
				setUnpushed();
			}
		}
		
		if (currState != GUI::ButtonEvent::Pressed && hoveringEnable)
		{
			if (currState != GUI::ButtonEvent::Hover && isRectHovering(evnt, sprites[0].getGlobalBounds()))
			{
				currState = GUI::ButtonEvent::Hover;
				prevState = GUI::ButtonEvent::Hover;
				setTextureMap(&sprites[0], nameImageHover);
			}
			else if (currState == GUI::ButtonEvent::Hover && !isRectHovering(evnt, sprites[0].getGlobalBounds()))
			{
				currState = GUI::ButtonEvent::None;
				prevState = GUI::ButtonEvent::None;
				setTextureMap(&sprites[0], nameImageIdle);
			}
		}
	}

	if (prevState != currState)
	{
		if (currState == GUI::ButtonEvent::Pressed)
		{
			setPushed();
			currState = GUI::ButtonEvent::Pressed;
			prevState = GUI::ButtonEvent::Pressed;
		}
		else if (currState == GUI::ButtonEvent::Clicked)
		{
			setPushed();
		}
	}
}

void GUI::Button::updateAttributes()
{
	if (currState == GUI::ButtonEvent::Pressed)
	{
		setTextureMap(&sprites[0], nameImagePushed);
	}
	else
	{
		setTextureMap(&sprites[0], nameImageIdle);
	}
	for (int i = 0; i < widgetsContained.size(); i++)
	{
		widgetsContained[i]->updateAttributes();
	}
	updatePositions();
}

void GUI::Button::updatePositions()
{
	if (hasText)
	{
		if (!textCentered)
		{
			posX[1] = posX[0] + posTextX;
			posY[1] = posY[0] + posTextY;
		}
		else
		{
			posX[1] = posX[0] + sprites[0].getGlobalBounds().width / 2 - buttonLabel->getRect().width / 2;
			posY[1] = posY[0] + sprites[0].getGlobalBounds().height / 2 - buttonLabel->getRect().height / 2;
		}
	}
	updateAbsolute();
}

void GUI::Button::clicked()
{
	if (currState == GUI::ButtonEvent::Pressed)
	{
		setUnpushed();
	}
	else
	{
		setPushed();
	}
}

bool GUI::Button::isPressed()
{
	return currState == GUI::ButtonEvent::Pressed;
}


bool GUI::Button::getJustClicked()
{
	return currState == GUI::ButtonEvent::Clicked;
}

GUI::ButtonEvent* GUI::Button::getHook()
{
	return &currState;
}

std::string GUI::Button::getString()
{
	if (hasText)
	{
		return buttonLabel->getString();
	}
	else
	{
		return "";
	}
}

GUI::Label* GUI::Button::getLabel()
{
	return buttonLabel;
}

void GUI::Button::setTexture()
{
	sprites.clear();
	sprites.resize(1);
	setTextureMap(&sprites[0], nameImageIdle);
}

void GUI::Button::bindFunction(std::function<void(DataObject*)> function, std::string parameters)
{
	this->parameters = parseBind(parameters);
	this->function = function;
	functionBinded = true;
}

void GUI::Button::bindFunction(std::function<void()> function)
{
	this->voidFunction = function;
	voidFunctionBinded = true;
}

/*GUI::NumericInput::NumericInput(std::string ID, int posX, int posY, int defaultValue, std::string style, std::string font, sf::Color fontColor, int fontSize) : Widget(ID, posX, posY, style)
{
	this->widgetType = "NumericInput";

	this->inputValue = std::to_string(defaultValue);

	this->fontColor = fontColor;

	this->posX.push_back(posX + 15);
	this->posY.push_back(posY + 15);

	this->posX.push_back(posX);
	this->posY.push_back(posY);

	this->posX.push_back(posX);
	this->posY.push_back(posY);

	this->posX.push_back(posX);
	this->posY.push_back(posY);

	selector.push_back(Display::Sprite);
	selector.push_back(Display::WidgetContained);
	selector.push_back(Display::Sprite);
	selector.push_back(Display::WidgetContained);
	selector.push_back(Display::WidgetContained);

	attributes->createBaseAttribute(convertPath(this->ID), "type", "str", widgetType);

	createAttribute("value", this->inputValue, "string");

	labelText = new Label(ID + "text", 0, 0, inputValue, font, fontSize, fontColor, sf::Text::Regular);
	labelText->setAbsolute(posContainerX, posContainerY);
	widgetsContained.push_back(labelText);
	addContainedItem(labelText->getDataObject());

	visibleValue = labelText->getHook();

	arrowTop = new Button(ID + "arrowTop", 0, 0, "ARROWUP", true, false);
	arrowTop->autoLoad();
	arrowTop->setAbsolute(posContainerX, posContainerY);
	widgetsContained.push_back(arrowTop);
	addContainedItem(arrowTop->getDataObject());

	arrowBot = new Button(ID + "arrowBot", 0, 0, "ARROWDOWN", true, false);
	arrowBot->autoLoad();
	arrowBot->setAbsolute(posContainerX, posContainerY);
	widgetsContained.push_back(arrowBot);
	addContainedItem(arrowBot->getDataObject());
}

GUI::NumericInput::NumericInput(std::string ID, int posX, int posY, Label* text, std::string style) : Widget(ID, posX, posY, style)
{
	this->widgetType = "NumericInput";

	this->inputValue = text->getString();

	this->posX.push_back(posX + 15);
	this->posY.push_back(posY + 15);

	this->posX.push_back(posX);
	this->posY.push_back(posY);

	this->posX.push_back(posX);
	this->posY.push_back(posY);

	this->posX.push_back(posX);
	this->posY.push_back(posY);

	selector.push_back(Display::Sprite);
	selector.push_back(Display::WidgetContained);
	selector.push_back(Display::Sprite);
	selector.push_back(Display::WidgetContained);
	selector.push_back(Display::WidgetContained);

	attributes->createBaseAttribute(convertPath(this->ID), "type", "str", widgetType);

	createAttribute("value", this->inputValue, "string");

	labelText = text;
	labelText->setAbsolute(posContainerX, posContainerY);
	widgetsContained.push_back(labelText);
	addContainedItem(labelText->getDataObject());

	visibleValue = labelText->getHook();

	arrowTop = new Button(ID + "arrowTop", 0, 0, "ARROWUP", true, false);
	arrowTop->autoLoad();
	arrowTop->setAbsolute(posContainerX, posContainerY);
	widgetsContained.push_back(arrowTop);
	addContainedItem(arrowTop->getDataObject());

	arrowBot = new Button(ID + "arrowBot", 0, 0, "ARROWDOWN", true, false);
	arrowBot->autoLoad();
	arrowBot->setAbsolute(posContainerX, posContainerY);
	widgetsContained.push_back(arrowBot);
	addContainedItem(arrowBot->getDataObject());
}

int GUI::NumericInput::getValue()
{
	return atoi(inputValue.c_str());
}

void GUI::NumericInput::setValue(int value)
{
	this->inputValue = std::to_string(value);
	updatePositions();
}

void GUI::NumericInput::setTexture()
{
	sprites.resize(2);
	setTextureMap(&sprites[0], nameImageBackground);
	setTextureMap(&sprites[1], nameImageOutline);

	updatePositions();
}


void GUI::NumericInput::updatePositions()
{
	posX[2] = posX[0];
	posY[2] = posY[0];

	setSpritesPositions();
	arrowTop->setSpritesPositions();

	posX[3] = posX[0] + sprites[0].getGlobalBounds().width - arrowTop->getRect().width - 5;
	posY[3] = posY[0] + 5;

	posX[4] = posX[0] + sprites[0].getGlobalBounds().width - arrowBot->getRect().width - 5;
	posY[4] = posY[0] + sprites[0].getGlobalBounds().height - arrowBot->getRect().height - 5;

	setTextPosition();
	updateAbsolute();
}

void GUI::NumericInput::setFocus()
{
	hasFocus = true;
	setTextureMap(&sprites[0], nameImageBackgroundFocus);
}

void GUI::NumericInput::loseFocus()
{
	hasFocus = false;
	setTextureMap(&sprites[0], nameImageBackground);
}

void GUI::NumericInput::setTextPosition()
{
	*visibleValue = inputValue;
	labelText->setText(*visibleValue, fontColor, sf::Text::Regular);
	labelText->setSpritesPositions();
	this->posX[1] = posX[0] + sprites[0].getGlobalBounds().width / 2 - labelText->getRect().width;
	while (posX[1] < posX[0])
	{
		(*visibleValue).erase(0, 1);
		labelText->setText(*visibleValue, fontColor, sf::Text::Regular);
		labelText->setSpritesPositions();
		this->posX[1] = posX[0] + sprites[0].getGlobalBounds().width / 2 - labelText->getRect().width;
	}
	posY[1] = posY[0] + sprites[0].getGlobalBounds().height / 2 - labelText->getRect().height / 2;
}

void GUI::NumericInput::checkArrowPressed(sf::Event& evnt)
{
	bool hasChanged = false;
	if (LeftClickReleased)
	{
		if (arrowTop->getJustClicked())
		{

			int numericInputValue = atoi(inputValue.c_str());
			numericInputValue++;
			inputValue = std::to_string(numericInputValue);
			hasChanged = true;
		}
		else if (arrowBot->getJustClicked())
		{
			int numericInputValue = atoi(inputValue.c_str());
			numericInputValue--;
			inputValue = std::to_string(numericInputValue);
			hasChanged = true;
		}
	}
	if (evnt.type == sf::Event::KeyPressed)
	{
		if (evnt.key.code == sf::Keyboard::Up && arrowUpReleased)
		{
			int numericInputValue = atoi(inputValue.c_str());
			numericInputValue++;
			inputValue = std::to_string(numericInputValue);
			hasChanged = true;
			arrowUpReleased = false;
		}
		else if (evnt.key.code == sf::Keyboard::Down && arrowDownReleased)
		{
			int numericInputValue = atoi(inputValue.c_str());
			numericInputValue--;
			inputValue = std::to_string(numericInputValue);
			hasChanged = true;
			arrowDownReleased = false;
		}
	}

	if (hasChanged)
	{
		setTextPosition();
	}
}

void GUI::NumericInput::updateTexture(sf::Event& evnt)
{
	if (!hasFocus)
	{
		if (isClicked(evnt, true, false))
		{
			setFocus();
		}
	}
	else if (hasFocus && static_cast<double>(clock()) / CLOCKS_PER_SEC - static_cast<double>(timeBefore) / CLOCKS_PER_SEC > 0.2)
	{
		checkArrowPressed(evnt);
		if (isRectClickedOutside(evnt, sprites[0].getGlobalBounds(), true, false))
		{
			loseFocus();
		}
		if (evnt.type == sf::Event::TextEntered && evnt.text.unicode >= 48 && evnt.text.unicode <= 57)
		{
			timeBefore = static_cast<float>(clock());
			inputValue.push_back(static_cast<char>(evnt.text.unicode));
			(*visibleValue).push_back(static_cast<char>(evnt.text.unicode));
			setTextPosition();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && inputValue.size() > 0)
		{
			timeBefore = static_cast<float>(clock());
			inputValue.erase(inputValue.size() - 1);
			setTextPosition();
		}
	}

	if (evnt.type == sf::Event::MouseButtonReleased && evnt.mouseButton.button == sf::Mouse::Left)
	{
		LeftClickReleased = true;
	}
	if (evnt.type == sf::Event::KeyReleased)
	{
		if (evnt.key.code == sf::Keyboard::Up)
			arrowUpReleased = true;
		if (evnt.key.code == sf::Keyboard::Down)
			arrowDownReleased = true;
	}
}*/

GUI::RadioButton::RadioButton(std::string ID, int posX, int posY, std::string value, std::string group, std::string style, bool isChecked) : Checkbox(ID, posX, posY, style, isChecked)
{
	this->widgetType = "RadioButton";

	this->group = group;
	this->value = value;

	attributes->createBaseAttribute(convertPath(this->ID), "type", "str", widgetType);

	createAttribute("value", this->value, "string");
	createAttribute("group", this->group, "string");
}

void GUI::RadioButton::clicked()
{
	if (!checked)
	{
		setChecked();
	}
}

std::string GUI::RadioButton::getGroup()
{
	return group;
}

std::vector<GUI::RadioButton*> GUI::RadioButton::getRadioButtonGroup(std::string group)
{
	std::vector<RadioButton*> radioButs = GUI::Widget::getWidgets<RadioButton>("RadioButton");
	std::vector<RadioButton*> radioGroup;
	for (int i = 0; i < radioButs.size(); i++)
	{
		if (radioButs[i]->group == group)
		{
			radioGroup.push_back(radioButs[i]);
		}
	}
	return radioGroup;
}

std::string GUI::RadioButton::getCurrentSelected(std::string group)
{
	std::vector<RadioButton*> radioButs = GUI::RadioButton::getRadioButtonGroup(group);

	for (int i = 0; i < radioButs.size(); i++)
	{
		if (radioButs[i]->isChecked())
		{
			return radioButs[i]->value;
		}
	}
}

bool GUI::RadioButton::getGroupToggled(std::string group)
{
	std::vector<RadioButton*> radioButs = GUI::RadioButton::getRadioButtonGroup(group);

	for (int i = 0; i < radioButs.size(); i++)
	{
		if (radioButs[i]->isChecked())
		{
			return true;
		}
	}
}

void GUI::RadioButton::setChecked()
{
	hasChanged = true;
	std::vector<RadioButton*> vectRadioButtons = GUI::Widget::getWidgets<RadioButton>("RadioButton");
	for (std::vector<RadioButton*>::iterator ite = vectRadioButtons.begin(); ite != vectRadioButtons.end(); ite++)
	{
		if ((*ite)->getGroup() == group && *ite != this)
		{
			(*ite)->setUnchecked();
		}
	}
	this->checked = true;
	this->previousValue = true;
	setTextureMap(&sprites[0], nameImageChecked);
}

void GUI::RadioButton::setUnchecked()
{
	hasChanged = true;
	this->checked = false;
	this->previousValue = false;
	setTextureMap(&sprites[0], nameImageUnchecked);
}

/*GUI::NumericSlider::NumericSlider(std::string ID, int posX, int posY, int minValue, int maxValue, int defaultCursorValue, std::string style) : Widget(ID, posX, posY, style)
{
	this->widgetType = "NumericSlider";
	selector.push_back(Display::Sprite);

	this->posX.push_back(posX);
	this->posY.push_back(posY);
	selector.push_back(Display::Sprite);

	this->posX.push_back(posX);
	this->posY.push_back(posY);
	selector.push_back(Display::Text);

	

	this->defaultCursorValue = defaultCursorValue;
	this->min = minValue;
	this->max = maxValue;
	this->range = this->max - this->min;

	if (this->font.loadFromFile("Data/Fonts/arial.ttf"))
	{
		std::cout << "Error opening font" << std::endl;
	}
	attributes->createBaseAttribute(convertPath(this->ID), "type", "str", widgetType);

	createAttribute("font", fontString, "string");
	createAttribute("max", max, "int");
	createAttribute("min", min, "int");
	createAttribute("range", range, "int");
	createAttribute("defaultCursorValue", this->defaultCursorValue, "int");
}

 void GUI::NumericSlider::updatePositions()
{
	setTexture();
}

void GUI::NumericSlider::setTexture()
{
	sf::Text returnNumber;
	returnNumber.setCharacterSize(18);
	returnNumber.setFont(font);
	returnNumber.setColor(sf::Color::Black);

	sprites.resize(2);
	setTextureMap(&sprites[0], nameImageSlider);
	setTextureMap(&sprites[1], nameImageCursor);

	valuePerMove = static_cast<float>(range) / sprites[0].getGlobalBounds().width;
	int posContainerX = absolutesX[0] - posX[0];
	int posContainerY = absolutesY[0] - posY[0];
	if (defaultCursorValue >= min && defaultCursorValue <= max)
	{
		posX[1] = defaultCursorValue / valuePerMove + posX[0] - min / valuePerMove;
		absolutesX[1] = posX[1] + posContainerX;
		posX[2] = posX[1];
		absolutesX[2] = posX[2] + posContainerX;
		number = defaultCursorValue;
		returnNumber.setString(std::to_string(number));
	}
	else
	{
		number = (min + max) / 2;
	}
	posY[2] = posY[1] - sprites[1].getGlobalBounds().height - returnNumber.getGlobalBounds().height;
	absolutesY[2] = posY[2] + posContainerY;

	text.resize(1);
	text[0]  returnNumber;
}

void GUI::NumericSlider::updateTexture(sf::Event& evnt)
{
	if (LeftClickReleased && isRectClicked(evnt, sprites[1].getGlobalBounds(), true, false))
	{
		isHoldingCursor = true;
		currentShift = convertMousePosX(evnt.mouseButton.x) - posX[1];
	}

	if (isHoldingCursor && !LeftClickReleased)
	{
		isHolding(evnt);
	}

	if (evnt.type == sf::Event::MouseButtonReleased && evnt.mouseButton.button == sf::Mouse::Left)
	{
		LeftClickReleased = true;
		isHoldingCursor = false;
	}
}

int GUI::NumericSlider::getValue()
{
	return number;
}

void GUI::NumericSlider::isHolding(sf::Event& evnt)
{
	if (evnt.type == sf::Event::MouseMoved)
	{
		int previousPos = posX[1];
		int posXContainer = absolutesX[1] - posX[1];
		if (convertMousePosX(evnt.mouseMove.x) - currentShift <= posX[0] + sprites[0].getGlobalBounds().width && convertMousePosX(evnt.mouseMove.x) - currentShift >= posX[0])
		{
			posX[1] = convertMousePosX(evnt.mouseMove.x) - currentShift;
			if (posX[1] - previousPos != 0)
				number = (posX[1] - posX[0]) * valuePerMove + min;
			text[0].setString(std::to_string(number));
			absolutesX[1] = posX[1] + posXContainer;
			posX[2] = posX[1];
			absolutesX[2] = posX[2] + posXContainer;
		}
	}
}*/

GUI::TextInput::TextInput(std::string ID, int posX, int posY, std::string font, int fontSize, sf::Color fontColor, std::string style, std::string defaultText) : Widget(ID, posX, posY, style)
{
	this->widgetType = "TextInput";
	this->fontColor = fontColor;
	selector.push_back(Display::Sprite);
	selector.push_back(Display::WidgetContained);
	selector.push_back(Display::Sprite);
	selector.push_back(Display::Shape);

	this->posX.push_back(posX);
	this->posY.push_back(posY);

	this->posX.push_back(posX);
	this->posY.push_back(posY);

	this->inputText = defaultText;

	fontCharMove.loadFromFile("Data/Fonts/" + font);
	charToMove.setFont(fontCharMove);
	charToMove.setCharacterSize(fontSize);
	charToMove.setStyle(sf::Text::Regular);
	charToMove.setPosition(0, 0);

	attributes->createBaseAttribute(convertPath(this->ID), "type", "str", widgetType);

	createAttribute("Text", this->inputText, "string");

	labelText = new Label(ID + "text", 0, 0, defaultText, font, fontSize, fontColor, sf::Text::Regular);
	labelText->setAbsolute(posContainerX, posContainerY);
	widgetsContained.push_back(labelText);
	addContainedItem(labelText->getDataObject());

	visibleText = labelText->getHook();
}

GUI::TextInput::TextInput(std::string ID, int posX, int posY, std::string style, GUI::Label* text) : Widget(ID, posX, posY, style)
{
	this->widgetType = "TextInput";

	selector.push_back(Display::Sprite);
	selector.push_back(Display::WidgetContained);
	selector.push_back(Display::Sprite);
	selector.push_back(Display::Shape);

	this->posX.push_back(posX);
	this->posY.push_back(posY);

	this->posX.push_back(posX);
	this->posY.push_back(posY);

	this->inputText = text->getString();

	attributes->createBaseAttribute(convertPath(this->ID), "type", "str", widgetType);
	createAttribute("Text", this->inputText, "string");

	labelText = text;
	labelText->setAbsolute(posContainerX, posContainerY);
	widgetsContained.push_back(labelText);
	addContainedItem(labelText->getDataObject());

	visibleText = labelText->getHook();
}

void GUI::TextInput::setTexture()
{
	sprites.resize(2);
	posX.resize(4);
	posY.resize(4);
	absolutesX.resize(4);
	absolutesY.resize(4);

	shapes.resize(1);
	shapes[0] = new sf::RectangleShape(sf::Vector2f(1, labelText->getfontSize() + 2));
	shapes[0]->setFillColor(sf::Color::Red);
	currentCursorOffset = labelText->getRect().width - 1;
	cursorPosition = inputText.size();

	setTextureMap(&sprites[0], nameImageBackground);
	setTextureMap(&sprites[1], nameImageOutline);

	updatePositions();
	previousWidth = labelText->getRect().width;
}

void GUI::TextInput::updatePositions()
{
	posX[2] = posX[0];
	posY[2] = posY[0];
	setSpritesPositions();
	//set text position
	updateTextPositionX();
	posY[1] = posY[0] + sprites[0].getGlobalBounds().height / 2 - labelText->getRect().height / 2;

	//set Cursor position
	posX[3] = posX[1] + currentCursorOffset;
	posY[3] = posY[1];
	//std::cout << posY[3] << " " << posX[3] << std::endl;
	//labelText->updatePositions();

	updateAbsolute();
}

void GUI::TextInput::updateTextPositionX()
{
	if (!textLarger)
		textWasLarger = false;
	textLarger = false;
	*visibleText = inputText;
	labelText->setText(*visibleText, fontColor, sf::Text::Regular);
	labelText->setSpritesPositions();
	this->posX[1] = posX[0] + 5;
	while (posX[1] + labelText->getRect().width >= posX[0] + sprites[0].getGlobalBounds().width - 5)
	{
		(*visibleText).erase(0, 1);
		labelText->setText(*visibleText, fontColor, sf::Text::Regular);
		labelText->setSpritesPositions();
		this->posX[1] = posX[0] + 5;
		textWasLarger = true;
		textLarger = true;
	}
}

void GUI::TextInput::setFocus()
{
	setTextureMap(&sprites[0], nameImageBackgroundFocus);
	hasFocus = true;
}

bool GUI::TextInput::getHasFocus()
{
	return hasFocus;
}

GUI::Label* GUI::TextInput::getLabel()
{
	return labelText;
}

void GUI::TextInput::loseFocus()
{
	setTextureMap(&sprites[0], nameImageBackground);
	hasFocus = false;
}

void GUI::TextInput::moveCursorTextChanged(int enteredOrDeleted)
{
	updateTextPositionX();
	charToMove.setString(inputText);
	int currentWidth = charToMove.getGlobalBounds().width;
	cursorPosition += enteredOrDeleted;
	if (!textWasLarger)
	{
		currentCursorOffset += (currentWidth - previousWidth);
	}

	previousWidth = currentWidth;
}

bool GUI::TextInput::checkFilters(int c)
{
	bool isOk = true;
	for (int i = 0; i < filters.size(); i++)
	{
		if (filters[i] == TextInputFilters::Integer && c < 48 || c > 57)
		{
			isOk = false;
		}
		if (filters[i] == TextInputFilters::Alphabetic && c < 65 || c > 90 && c < 97 || c > 122 && c != 32)
		{
			isOk = false;
		}
		if (filters[i] == TextInputFilters::AlphaNumeric && c < 65 || c > 90 && c < 97 || c > 122 && c < 48 || c > 57 && c != 32)
		{
			isOk = false;
		}
		if (filters[i] == TextInputFilters::Uppercase && c < 65 || c > 90 && c != 32 && c < 48 || c > 57)
		{
			isOk = false;
		}
		if (filters[i] == TextInputFilters::Lowercase && c < 97 || c > 122 && c != 32 && c < 48 || c > 57)
		{
			isOk = false;
		}
	}
	return isOk;
}

void GUI::TextInput::moveCursorRight()
{
	if (cursorPosition < inputText.size() && inputText.size() >= 1)
	{
		std::string charMoved(1, inputText[cursorPosition]);
		charToMove.setString(charMoved);

		cursorPosition++;

		currentCursorOffset += charToMove.getGlobalBounds().width;
	}
	updatePositions();
}

void GUI::TextInput::moveCursorLeft()
{
	if (cursorPosition > 0)
	{
		std::string charMoved(1, inputText[cursorPosition - 1]);
		charToMove.setString(charMoved);

		if (!(currentCursorOffset + posX[1] - charToMove.getGlobalBounds().width < posX[0]))
		{
			cursorPosition--;
			currentCursorOffset -= charToMove.getGlobalBounds().width;
		}
	}
	updatePositions();
}

void GUI::TextInput::updateTexture(sf::Event& evnt)
{
	enterJustPressed = false;
	if (hasFocus)
	{
		if (selector.size() == 4 && cursorElapsedTime.getElapsedTime().asMilliseconds() >= timeCursorDiplayed)
		{
			selector.resize(3);
			cursorElapsedTime.restart();
		}
		else if (selector.size() == 3 && cursorElapsedTime.getElapsedTime().asMilliseconds() >= timeCursorDiplayed)
		{
			selector.push_back(Display::Shape);
			cursorElapsedTime.restart();
		}
		if (evnt.type == sf::Event::KeyPressed)
		{
			if (cursorKeyReleased && evnt.key.code == sf::Keyboard::Right)
			{
				moveCursorRight();
				cursorKeyReleased = false;
			}
			else if (cursorKeyReleased && evnt.key.code == sf::Keyboard::Left)
			{
				moveCursorLeft();
				cursorKeyReleased = false;
			}
		}
		if (evnt.type == sf::Event::KeyReleased)
		{
			if (evnt.key.code == sf::Keyboard::Right || evnt.key.code == sf::Keyboard::Left)
				cursorKeyReleased = true;
		}
	}

	if (!hasFocus)
	{
		if (isClicked(evnt, true, false))
		{
			setFocus();
		}
	}
	else if (evnt.type == sf::Event::TextEntered && evnt.text.unicode == 13)
	{
		enterJustPressed = true;
	}
	else
	{
		if (hasStartTimer && !unlockKeyRepeater && evnt.type == sf::Event::KeyReleased)
		{
			unlockKeyRepeater = true;
			hasStartTimer = false;
			previousChar = 0;
		}
		if (isRectClickedOutside(evnt, sprites[0].getGlobalBounds(), true, false))
		{
			loseFocus();
		}
		if (evnt.type == sf::Event::TextEntered)
		{
			if (evnt.text.unicode == previousChar && !hasStartTimer && unlockKeyRepeater)
			{
				timeBefore = static_cast<float>(clock());
				hasStartTimer = true;
				unlockKeyRepeater = false;
			}
			else if (!unlockKeyRepeater && evnt.text.unicode == previousChar && static_cast<double>(clock()) / CLOCKS_PER_SEC - static_cast<double>(timeBefore) / CLOCKS_PER_SEC > 0.45 || previousChar != evnt.text.unicode)
			{
				unlockKeyRepeater = true;
			}
			if (unlockKeyRepeater)
			{
				if (unlockKeyRepeater && previousChar != evnt.text.unicode)
					hasStartTimer = false;
				if (evnt.text.unicode == 8)
				{
					if (inputText.size() > 0 && cursorPosition - 1 >= 0)
					{
						timeBefore = static_cast<float>(clock());
						inputText.erase(cursorPosition - 1, 1);
						moveCursorTextChanged(-1);
						updatePositions();
					}
				}
				else if (evnt.text.unicode < 128 && checkFilters(evnt.text.unicode))
				{
					timeBefore = static_cast<float>(clock());
					std::string s(1, static_cast<char>(evnt.text.unicode));
					inputText.insert(cursorPosition, s);
					moveCursorTextChanged(1);
					updatePositions();
				}
				previousChar = evnt.text.unicode;

			}
		}
	}
}

bool GUI::TextInput::getEnterPressed()
{
	return enterJustPressed;
}

void GUI::TextInput::setText(std::string string)
{
	inputText = string;
	updatePositions();
}

void GUI::TextInput::addFilter(GUI::TextInputFilters filter)
{
	filters.push_back(filter);
}

std::string GUI::TextInput::getText()
{
	return inputText;
}

void GUI::Widget::clicked()
{
}

GUI::Container::Container(sf::Event* evnt, sf::RenderWindow* window, int windowWidth, int windowHeight)
{
	this->evnt = evnt;
	GUI::windowHeight = windowHeight;
	GUI::windowWidth = windowWidth;
	GUI::window = window;
	GUI::container = this;
}

GUI::WidgetContainer* GUI::Container::createWidgetContainer(std::string containerName, int layer, int posX, int posY, int width,\
	int height, GUI::ContainerMovement movable, int widthControlBar, int heightControleBar)
{
	if (layer > widContainers.size() && widContainers.size() != 0)
	{
		layer = widContainers.size() + 1;
	}
	else if (widContainers.size() == 0)
	{
		layer = 1;
	}
	else if (layer < 1)
	{
		layer = 1;
	}
	WidgetContainer* newWidgetContainer = new WidgetContainer(containerName, posX, posY, width, height, movable, widthControlBar, heightControleBar, this->evnt);
	widgetContainers[containerName] = newWidgetContainer;

	widContainers.insert(widContainers.begin() + layer - 1, newWidgetContainer);

	return newWidgetContainer;
}

bool GUI::WidgetContainer::getReleased()
{
	return justReleased;
}

void GUI::WidgetContainer::addScrollBar()
{
	scroll = container->createScrollBar(containerName, containerName + "scrollbar", width, 0, height, 100, false, widgetIDContainer, "V2");
	scroll->setPosition(width - scroll->getRect().width, 0);
}

sf::Rect<float> GUI::WidgetContainer::getRect()
{
	sf::Rect<float> rect = sf::Rect<float>(posX, posY, width, height);
	return rect;
}

bool GUI::WidgetContainer::getDisplayed()
{
	return displayed;
}

GUI::WidgetContainer* GUI::Container::getContainerByContainerName(std::string containerName)
{
	return widgetContainers[containerName];
}

void GUI::Container::drawContainer(std::string containerName, sf::RenderWindow *GUI)
{
	widgetContainers[containerName]->drawAll(GUI);
}

void GUI::Container::updateContainer(std::string containerName)
{
	widgetContainers[containerName]->updateAll(*evnt);
}

void GUI::Container::drawAllContainer(sf::RenderWindow* GUI)
{
	if (!leftClickReleased && evnt->type == sf::Event::MouseButtonReleased && evnt->mouseButton.button == sf::Mouse::Left)
	{
		leftClickReleased = true;
	}
	if (!rightClickReleased && evnt->type == sf::Event::MouseButtonReleased && evnt->mouseButton.button == sf::Mouse::Right)
	{
		rightClickReleased = true;
	}
	if (evnt->type == sf::Event::MouseButtonPressed && evnt->mouseButton.button == sf::Mouse::Left)
	{
		leftClickReleased = false;
	}
	if (evnt->type == sf::Event::MouseButtonPressed && evnt->mouseButton.button == sf::Mouse::Right)
	{
		rightClickReleased = false;
	}

	for (std::vector<WidgetContainer*>::reverse_iterator ite = widContainers.rbegin(); ite != widContainers.rend(); ite++)
	{
		(*ite)->drawAll(GUI);
	}
	std::vector<Movable*> movables = GUI::Widget::getWidgets<Movable>("Movable");
	for (int i = 0; i < movables.size(); i++)
	{
		if (movables[i]->getDisplayed() && movables[i]->getHolding())
		{
			movables[i]->draw(GUI);
		}
	}
}

void GUI::Container::updateAllContainer()
{

	if (leftClickReleased && rightClickReleased)
		alreadyClicked = false;

	for (std::vector<WidgetContainer*>::iterator ite = widContainers.begin(); ite != widContainers.end(); ite++)
	{
		(*ite)->updateAll(*evnt);
	}
}

void GUI::Container::setFocus(std::string widgetContainerName)
{
	GUI::WidgetContainer* widcont = widgetContainers[widgetContainerName];
	for (std::vector<WidgetContainer*>::iterator ite = widContainers.begin(); ite != widContainers.end(); ite++)
	{
		if (*ite == widgetContainers[widgetContainerName])
		{
			widContainers.erase(ite);
			break;
		}
	}
	widContainers.insert(widContainers.begin(), widcont);
}

void GUI::Container::setFocus(GUI::WidgetContainer* widgetContainer)
{
	for (std::vector<WidgetContainer*>::iterator ite = widContainers.begin(); ite != widContainers.end(); ite++)
	{
		if (*ite == widgetContainer)
		{
			widContainers.erase(ite);
			break;
		}
	}
	widContainers.insert(widContainers.begin(), widgetContainer);
}

void GUI::Container::setLayer(std::string widgetContainerName, int layer)
{
	if (widContainers.size() == 0)
	{
		layer = 1;
	}
	else if (layer < 1)
	{
		layer = 1;
	}
	else if (layer > widContainers.size())
	{
		layer = widContainers.size();
	}
	for (std::vector<WidgetContainer*>::iterator ite = widContainers.begin(); ite != widContainers.end(); ite++)
	{
		if (*ite == widgetContainers[widgetContainerName])
		{
			widContainers.erase(ite);
			break;
		}
	}
	widContainers.insert(widContainers.begin() + layer - 1, widgetContainers[widgetContainerName]);

}

bool GUI::Container::getAlreadyClicked()
{
	return alreadyClicked;
}

void GUI::Container::setAlreadyClicked(bool set)
{
	alreadyClicked = set;
}

void GUI::Container::autoMove()
{
	for (std::vector<WidgetContainer*>::reverse_iterator ite = widContainers.rbegin(); ite != widContainers.rend(); ite++)
	{
		autoFocus();
		if (hasFocus(*ite))
		{
			(*ite)->autoMove();
			break;
		}
	}
}

void GUI::Container::autoFocus()
{
	for (std::vector<WidgetContainer*>::reverse_iterator ite = widContainers.rbegin(); ite != widContainers.rend(); ite++)
	{
		if ((*ite)->getClicked())
		{
			setFocus(*ite);
		}
	}
}

bool GUI::Container::hasFocus(GUI::WidgetContainer* widgetContainer)
{
	if (widContainers.front() == widgetContainer)
		return true;
	else
		return false;
}

bool GUI::Container::hasFocus(std::string widgetContainerName)
{
	if (widContainers.front() == widgetContainers[widgetContainerName])
		return true;
	else
		return false;
}

void GUI::Container::removeWidget(std::string widgetID)
{
	for (std::vector<WidgetContainer*>::iterator ite = widContainers.begin(); ite != widContainers.end(); ite++)
	{
		if ((*ite)->removeWidget(widgetID))
		{
			break;
		}
	}
}

void GUI::Container::removeWidgetContainer(std::string widgetContainerName)
{
	WidgetContainer* w = widgetContainers[widgetContainerName];
	widContainers.erase(std::find(widContainers.begin(), widContainers.end(), widgetContainers[widgetContainerName]));
	widgetContainers.erase(widgetContainerName);
	delete w;
}

void GUI::Container::resizeWidgetContainer(std::string widgetContainerName, int width, int height)
{
	widgetContainers[widgetContainerName]->resize(width, height);
}

void GUI::Container::setWindowSize(int windowWidth, int windowHeight)
{
	GUI::windowHeight = windowHeight;
	GUI::windowWidth = windowWidth;
}

void GUI::Container::loadWidgetContainerFromFile(std::string filename, int posX, int posY)
{
	WidgetContainer* newWContainer = createWidgetContainer(filename, 1, posX, posY, 0, 0, GUI::ContainerMovement::Fixed);
	DataParser data;

	data.parseFile(filename);
	std::vector<std::string> dataObj = data.getAllDataObjects();
	for (auto ite = dataObj.begin(); ite != dataObj.end(); ite++)
	{
		loadWidget(filename, *ite, *ite, "", &data, false);
	}
}

GUI::Widget* GUI::Container::loadWidget(std::string widgetContainerName, std::string dataObject, std::string name, std::string path, DataParser* data, bool isContained)
{
	std::string getType;
	ComplexAttribute* widget = data->accessDataObject(dataObject)->getComplexAttribute(convertPath(path), name);
	int posX, posY;
	bool displayed;
	std::string style;
	widget->getAttribute("style")->getData(&style);

	std::map<std::string, float> attributesFloat;
	std::map<std::string, int> attributesInt;
	std::map<std::string, std::string> attributesString;
	std::map<std::string, bool> attributesBool;

	loadAttributes(widget, attributesInt, attributesFloat, attributesString, attributesBool);
	widget->getAttribute("type")->getData(&getType);
	if (getType == "Checkbox")
	{
		this->createCheckbox(widgetContainerName, name, attributesFloat["posX"], attributesFloat["posY"], style, attributesBool["checked"]);
	}
	else if (getType == "RadioButton")
	{
		this->createRadioButton(widgetContainerName, name, attributesFloat["posX"], attributesFloat["posY"], attributesString["value"]\
			, attributesString["group"], attributesBool["checked"], style);
	}
	else if (getType == "Label")
	{
		std::string text, font;
		int fontSize;
		sf::Color fontColor;
		fontColor.r = attributesInt["fontColorR"];
		fontColor.g = attributesInt["fontColorG"];
		fontColor.b = attributesInt["fontColorB"];

		if (!isContained)
		{
			this->createLabel(widgetContainerName, name, attributesFloat["posX"], attributesFloat["posY"], attributesString["text"]\
				, attributesString["font"], attributesInt["fontSize"], fontColor, sf::Text::Regular);
		}
		else
		{
			return new Label(name, attributesFloat["posX"], attributesFloat["posY"], attributesString["text"]\
				, attributesString["font"], attributesInt["fontSize"], fontColor, sf::Text::Regular);
		}

	}
	else if (getType == "Button")
	{
		bool hasText = false;
		Label* label = NULL;
		if (widget->complexExists("containedItem"))
		{
			ComplexAttribute* containedItems = widget->getComplexAttribute("containedItem");
			label = dynamic_cast<Label*>(loadWidget(widgetContainerName, dataObject, containedItems->getAllComplex()[0], path + "/" + name + "/" + "containedItem", data, true));
			hasText = true;
		}
		if (!isContained)
		{
			Button* button = this->createButton(widgetContainerName, name, attributesFloat["posX"], attributesFloat["posY"], attributesBool["pushingEnable"], \
				attributesBool["hoveringEnable"], style);
			if (hasText)
			{
				button->setLabelText(label);
			}
		}
		else
		{
			Button* button = new Button(name, attributesFloat["posX"], attributesFloat["posY"], style, attributesBool["pushingEnable"], \
				attributesBool["hoveringEnable"]);
			button->autoLoad();
			button->setAbsolute(0, 0);
			if (hasText)
			{
				button->setLabelText(label);
			}
			return button;
		}

	}
	else if (getType == "Droplist")
	{
		if (widget->complexExists("containedItem"))
		{
			ComplexAttribute* containedItems = widget->getComplexAttribute("containedItem");
			std::vector<std::string> buttonsComplex = containedItems->getAllComplex();
			std::vector<Button*> buttons;
			for (int i = 0; i < buttonsComplex.size(); i++)
			{
				buttons.push_back(dynamic_cast<Button*>(loadWidget(widgetContainerName, dataObject, buttonsComplex[i], name + "/containedItem", data, true)));
			}
			this->createDroplist(widgetContainerName, name, attributesFloat["posX"], attributesFloat["posY"], true, buttons[0]->getString(), buttons, style);

		}
	}
	else if (getType == "TextInput")
	{
		Label* label;
		ComplexAttribute* containedItems = widget->getComplexAttribute("containedItem");
		label = dynamic_cast<Label*>(loadWidget(widgetContainerName, dataObject, containedItems->getAllComplex()[0], path + "/" + name + "/" + "containedItem", data, true));
		this->createTextInput(widgetContainerName, name, attributesFloat["posX"], attributesFloat["posY"], label, style);
	}
	/*else if (getType == "NumericInput")
	{
		ComplexAttribute* containedItems = widget->getComplexAttribute("containedItem");
		Label* label = dynamic_cast<Label*>(loadWidget(widgetContainerName, dataObject, containedItems->getAllComplex()[0], path + "/" + name + "/" + "containedItem", data, true));;

		this->createNumericInput(widgetContainerName, name, attributesFloat["posX"], attributesFloat["posY"], label, style);
	}*/
	else if (getType == "Dropbox")
	{
		this->createDropbox(widgetContainerName, name, attributesFloat["posX"], attributesFloat["posY"], style);
	}
	return NULL;
}


void GUI::Container::loadAttributes(ComplexAttribute* widget, std::map<std::string, int> &attributesInt, std::map<std::string, float> &attributesFloat, std::map<std::string, std::string> &attributesString, std::map<std::string, bool> &attributesBool)
{
	std::vector<std::string> attributes = widget->getAllComplex();
	for (std::vector<std::string>::iterator ite = attributes.begin(); ite != attributes.end(); ite++)
	{
		if (*ite != "containedItem")
		{
			std::string type;
			ComplexAttribute* attribute = widget->getComplexAttribute(*ite);
			attribute->getAttribute("type")->getData(&type);
			if (type == "int")
			{
				attribute->getAttribute("value")->getData(&attributesInt[*ite]);
			}
			else if (type == "float")
			{
				double inter;
				attribute->getAttribute("value")->getData(&inter);
				attributesFloat[*ite] = inter;
			}
			else if (type == "bool")
			{
				attribute->getAttribute("value")->getData(&attributesBool[*ite]);
			}
			else if (type == "string")
			{
				attribute->getAttribute("value")->getData(&attributesString[*ite]);
			}
		}
	}
}

void GUI::Container::loadBasicsAttributes(double* posX, double* posY, bool* displayed, std::string* style, ComplexAttribute* widget)
{
	widget->getAttribute("style")->getData(style);
	widget->getComplexAttribute("posX")->getAttribute("value")->getData(posX);
	widget->getComplexAttribute("posY")->getAttribute("value")->getData(posY);
	widget->getComplexAttribute("displayed")->getAttribute("value")->getData(displayed);
}

void GUI::Container::loadWidContFromFileInWidCont(std::string filename, std::string widgetContainer)
{
	DataParser data;
	data.parseFile(filename);
	std::vector<std::string> dataObj = data.getAllDataObjects();
	for (auto ite = dataObj.begin(); ite != dataObj.end(); ite++)
	{
		loadWidget(widgetContainer, *ite, *ite, "", &data, false);
	}
}

int convertMousePosX(int mousePosX)
{
	return static_cast<double>(fn::Coord::baseWidth) / GUI::windowWidth * mousePosX;
}

int convertMousePosY(int mousePosY)
{
	return static_cast<double>(fn::Coord::baseHeight) / GUI::windowHeight * mousePosY;
}

Color::Color(sf::Color color)
{
	this->r = color.r;
	this->g = color.g;
	this->b = color.b;
	this->a = color.a;
}

Color& Color::operator=(sf::Color const& color)
{
	this->r = color.r;
	this->g = color.g;
	this->b = color.b;
	this->a = color.a;
	return *this;
}

sf::Color Color::getSfColor()
{
	sf::Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return color;
}

Color::Color()
{

}

DataObject* parseBind(std::string str)
{
	int k = 0;
	DataObject* parameters = new DataObject("parameters");
	std::vector<std::string> strings = fn::String::extractBetween(str, '\'', '\'');
	std::vector<std::string> splitParameters = fn::String::split(str, ",");
	std::map<std::string, std::string> vars;
	for (int i = 0; i < splitParameters.size(); i++)
	{
		std::vector<std::string> splitVars = fn::String::split(splitParameters[i], "=");
		std::vector<std::string> typeAndName = fn::String::split(splitVars[0], " ");
		if (splitVars[1][0] == ' ')
			splitVars[1].erase(splitVars[1].begin());
		fn::String::replaceStringInPlace(splitVars[1], "'", "");
		if (typeAndName[0] == "string" || typeAndName[0] == "std::string")
		{
			typeAndName[0] = "str";
			splitVars[1] = strings[k];
			k++;
		}
		parameters->createBaseAttribute(convertPath(""), typeAndName[1], typeAndName[0], splitVars[1]);
	}
	return parameters;
}

void GUI::Widget::addContainedItem(DataObject* containedItem)
{
	std::vector<std::string> complexAttributesID = containedItem->getAllComplex(convertPath(""));
	if (!attributes->complexExists(convertPath(ID), "containedItem"))
	{
		attributes->createComplexAttribute(convertPath(ID), "containedItem");
	}

	for (std::vector<std::string>::iterator ite = complexAttributesID.begin(); ite != complexAttributesID.end(); ite++)
	{
		attributes->pushComplexAttribute(convertPath(ID + "/containedItem"), containedItem->getComplexAttribute(convertPath(""), *ite));
	}
}
