//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "MathExp.hpp"

namespace Light
{
	class PointLight
	{
		protected:
			std::string id;
			static sf::RectangleShape rtTex;
			sf::Shader* shader;
			sf::RenderStates states;
			double offX, offY;
			double x, y;
			double size;
			double r, g, b, a;
			bool behind = true;
			bool visible = true;

			void checkColors();
		public:
			PointLight(std::string id, sf::Vector2f screenSize, sf::Vector2f position, double size, sf::Color color, bool behind = false);
			PointLight(std::string id, int screenSizeX, int screenSizeY, int x, int y, double size, int r, int g, int b, int a, bool behind = false);

			std::string getID();
			void draw(sf::RenderWindow* surf);
			void setPosition(double x, double y);
			void move(double x, double y);
			void setOffset(double x, double y);
			void setSize(double size);
			void scale(double size);
			void setColor(int r, int g, int b, int a);
			void addColor(int r, int g, int b, int a);
			void subColor(int r, int g, int b, int a);
			void blendColor(double rB, double gB, double bB, double aB);
			void setBehind(bool behind);
			
			void show();
			void hide();
			void setVisible(bool state);
			bool isVisible();

			sf::Vector2f getPosition();
			double getX();
			double getY();
			double getSize();

			sf::Color getColor();
			double getR();
			double getG();
			double getB();
			double getA();
			bool isBehind();

			double* getX_p();
			double* getY_p();
			double* getSize_P();
			double* getR_P();
			double* getG_P();
			double* getB_P();
			double* getA_P();

			virtual std::string getType();

			void updateShader();

			friend void initLights();
	};

	class DynamicPointLight : public MathExpObject, public PointLight
	{
		public:
			DynamicPointLight(std::string id, sf::Vector2f screenSize, double precision);
			DynamicPointLight(std::string id, int screenSizeX, int screenSizeY, double precision);
			void setSizeExp(std::string size);
			void setRExp(std::string r);
			void setGExp(std::string g);
			void setBExp(std::string b);
			void setAExp(std::string a);
			void setOffsetXExp(std::string x);
			void setOffsetYExp(std::string y);

			virtual std::string getType();

			void updateLight();

			friend void initLights();
	};
}