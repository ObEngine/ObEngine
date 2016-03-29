//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "Dialog.hpp"

TextRenderer::TextRenderer()
{
	absoluteX = 0;
	absoluteY = 0;
	dialogLine.loadFromFile("Sprites/Dialog/textbox.png");
	arrowTex.loadFromFile("Sprites/Dialog/arrow.png");
	dialogLineSpr.setTexture(dialogLine);
	dialogLineSpr.setPosition(0, 760);
	arrowSpr.setTexture(arrowTex);
	dialogFont.loadFromFile("Data/Fonts/TravelingTypewriter.ttf");
	dialogText.setFont(dialogFont);
	dialogText.setCharacterSize(32);
	dialogText.setColor(sf::Color(255, 255, 255, 255));
	speakerText.setFont(dialogFont);
	speakerText.setCharacterSize(48);
	speakerText.setColor(sf::Color(255, 255, 255, 255));
	renTex.create(1920, 1080);
}

void TextRenderer::setPos(int x, int y)
{
	absoluteX = x;
	absoluteY = y;
}

void TextRenderer::appendText(std::string speaker, std::string text)
{
	std::vector<std::string> spTxt;
	spTxt.push_back(speaker);
	spTxt.push_back(text);
	textList.push_back(spTxt);
}

bool TextRenderer::textRemaining()
{
	if (textList.size() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void TextRenderer::next()
{
	if (textList.size() > 0)
	{
		textList.erase(textList.begin());
		needToRender = true;
	}
}

void TextRenderer::render(sf::RenderWindow* surf)
{	
	if (textList.size() > 0)
	{

		if (needToRender)
		{
			renTex.clear(sf::Color(0, 0, 0, 200));
			
			renTex.draw(dialogLineSpr);
			std::string speaker = textList[0][0];
			std::string textToSay = textList[0][1];
			speakerText.setString(speaker);
			speakerText.setPosition((90 + (12 * (11 - speaker.size()))), 760);
			renTex.draw(speakerText);
			int letterCounter = 0;
			int indexCounter = 0;
			int letterMax = 109;
			int lignAlign = 0;
			std::string currentPhr;
			std::vector<std::string> currentTextList;
			if (fn::String::occurencesInString(textToSay, " ") >= 1)
				currentTextList = fn::String::split(textToSay, " ");
			else
				currentTextList = { textToSay };
			for (unsigned int i = 0; i < currentTextList.size(); i++)
			{
				currentPhr += currentTextList[i] + " ";
				letterCounter += currentTextList[i].size();
				if (letterCounter >= letterMax || indexCounter == currentTextList.size() - 1)
				{
					dialogText.setPosition(30, 840 + (lignAlign * 50));
					dialogText.setString(currentPhr);
					currentPhr = "";
					letterCounter += currentTextList[i].size() + 1;
					lignAlign++;
					renTex.draw(dialogText);
				}
				indexCounter++;
			}
			needToRender = false;

			renTex.display();
			renGetTex = renTex.getTexture();
			dispSpr.setTexture(renGetTex);
			dispSpr.scale(sf::Vector2f(fn::Coord::width / 1920, fn::Coord::height / 1080));
			surf->draw(dispSpr);
		}
		else
		{
			surf->draw(dispSpr);
		}
	}
}
