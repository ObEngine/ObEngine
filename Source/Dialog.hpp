//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <functional>

#include "any.hpp"
#include "Functions.hpp"
#include "Animation.hpp"
#include "TimeManager.hpp"

extern sf::RenderTexture renTex;

class Renderer
{
	protected:
		std::map<std::string, emorph::any> locals;
		std::vector<std::map<std::string, std::string>> vtdb;
	public:
		std::string name;
		virtual void load() = 0;
		virtual void unload() = 0;
		virtual void render() = 0;
		virtual void draw(sf::RenderWindow* surf) = 0;
		void addTDB(std::map<std::string, std::string> tdb);
};

class TextRenderer
{
	private:
		std::map<std::string, Renderer*> rendererDB;
		std::vector<std::string> rendererCalls;
		Renderer* currentRenderer;
		bool needToRender = true;

	public:
		TextRenderer();
		void createRenderer(std::string rendererType, std::string id);
		void sendToRenderer(std::string id, std::map<std::string, std::string> tdb);
		bool textRemaining();
		void next();
		void render(sf::RenderWindow* surf);
};

namespace Renderers
{
	class VisualNovel : public Renderer { void load(); void unload(); void render(); void draw(sf::RenderWindow* surf); };
	class Shade : public Renderer { void load(); void unload(); void render(); void draw(sf::RenderWindow* surf); };
}
