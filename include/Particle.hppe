//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <SFML/Graphics.hpp>
#include <vili/Vili.hpp>

#include "MathExp.hpp"

namespace obe
{
	namespace Graphics
	{
		class Particle
		{
			private:
				float velocity;
				int angle;
				int totalLifetime;
				int lifetime;
				int size;
				double absoluteX, absoluteY;
				int staR, staG, staB, staA;
				int curR, curG, curB, curA;
				int endR, endG, endB, endA;
				sf::Color startColor;
				sf::Color endColor;
				sf::RectangleShape* particleShape;
			public:
				void init(int x, int y, int vel, int angle, int lifetime, int size, sf::Color sColor, sf::Color eColor);
				void shapeInit();
				void setPos(int x, int y);
				void setStartColor(sf::Color sColor);
				void setEndColor(sf::Color eColor);
				void setVelocity(int vel);
				void setAngle(int angle);
				void setLifetime(int lifetime);
				double getX();
				double getY();
				int getVelocity();
				int getAngle();
				int getLifetime();
				bool isDead();
				void update();
				sf::RectangleShape* getParticle();
		};

		class MathParticle : public Math::MathExpObject
		{
			private:
				sf::RenderTexture trailTexFP;
				sf::RectangleShape* particleShape;
				std::vector<sf::RectangleShape> trailVector;
				bool trailEnabled = false;
				double r, g, b, a;
				double x, y;
				double lifetime;
				double size;
				double trailLength, trailAlpha;
			public:
				MathParticle();
				MathParticle(std::string x, std::string y, std::string r, std::string g, std::string b, std::string a, std::string lifetime, double precision);
				MathParticle(std::string id);
				void setExp(std::string id, std::string exp);
				void update();
				void draw(sf::RenderWindow* surf);
		};

		class ParticleSystem
		{
			private:
				std::vector<Particle*> particleArray;
			public:
		};

		class ParticleEmitter
		{
			private:
				ParticleSystem* paSystemHook;
				int emitterX;
				int emitterY;
			public:
				void emitParticles();
		};
	}
}

