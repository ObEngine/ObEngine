//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "Particle.hpp"

namespace obe
{
	namespace Graphics
	{
		void Particle::init(int x, int y, int vel, int angle, int lifetime, int size, sf::Color sColor, sf::Color eColor)
		{
			this->absoluteX = x;
			this->absoluteY = y;
			this->velocity = vel;
			this->angle = angle;
			this->totalLifetime = lifetime;
			this->lifetime = lifetime;
			this->size = size;
			this->startColor = sColor;
			this->endColor = eColor;
			this->shapeInit();
			staR = startColor.r;
			staG = startColor.g;
			staB = startColor.b;
			staA = startColor.a;
			curR = startColor.r;
			curG = startColor.g;
			curB = startColor.b;
			curA = startColor.a;
			endR = endColor.r;
			endG = endColor.g;
			endB = endColor.b;
			endA = endColor.a;
		}

		void Particle::shapeInit()
		{
			particleShape = new sf::RectangleShape(sf::Vector2f(this->size, this->size));
			particleShape->setFillColor(startColor);
		}

		void Particle::setStartColor(sf::Color sColor)
		{
			this->startColor = sColor;
		}

		void Particle::setEndColor(sf::Color eColor)
		{
			this->endColor = eColor;
		}

		void Particle::setVelocity(int vel)
		{
			this->velocity = vel;
		}

		void Particle::setAngle(int angle)
		{
			this->angle = angle;
		}

		void Particle::setLifetime(int lifetime)
		{
			this->lifetime = lifetime;
		}

		int Particle::getVelocity()
		{
			return this->velocity;
		}

		int Particle::getAngle()
		{
			return this->angle;
		}

		int Particle::getLifetime()
		{
			return this->lifetime;
		}

		bool Particle::isDead()
		{
			return (this->lifetime == 0);
		}

		void Particle::update()
		{
			float currentProgress = (float)lifetime / (float)totalLifetime;
			curR = ((staR)*currentProgress + endR*(1.0 - currentProgress));
			curG = ((staG)*currentProgress + endG*(1.0 - currentProgress));
			curB = ((staB)*currentProgress + endB*(1.0 - currentProgress));
			curA = ((staA)*currentProgress + endA*(1.0 - currentProgress));
			particleShape->setFillColor(sf::Color(curR, curG, curB, curA));
			if (lifetime > 0)
				lifetime--;
			absoluteX += velocity * sin(angle);
			absoluteY += velocity * cos(angle) * -1;
			particleShape->setPosition(absoluteX, absoluteY);
		}

		sf::RectangleShape* Particle::getParticle()
		{
			return particleShape;
		}


		//MathParticle
		MathParticle::MathParticle() : MathExpObject(0)
		{
			trailTexFP.create(1920, 1080);
			this->setPrecision(0.01);
			this->registerMathExp("x", "0");
			this->registerMathExp("y", "0");
			this->registerMathExp("r", "255");
			this->registerMathExp("g", "255");
			this->registerMathExp("b", "255");
			this->registerMathExp("a", "255");
			this->registerMathExp("size", "1");
			this->registerMathExp("lifetime", "-1");
			this->registerMathExp("trailLength", "0");
			this->registerMathExp("trailAlpha", "0");
			this->trailEnabled = false;
			this->registerOutputVar("x", &this->x);
			this->registerOutputVar("y", &this->y);
			this->registerOutputVar("r", &this->r);
			this->registerOutputVar("g", &this->g);
			this->registerOutputVar("b", &this->b);
			this->registerOutputVar("a", &this->a);
			this->registerOutputVar("size", &this->size);
			this->registerOutputVar("lifetime", &this->lifetime);
			this->registerOutputVar("trailLength", &this->trailLength);
			this->registerOutputVar("trailAlpha", &this->trailAlpha);
			particleShape = new sf::RectangleShape(sf::Vector2f(1, 1));
			this->update();
		}
		MathParticle::MathParticle(std::string x, std::string y, std::string r, std::string g, std::string b, std::string a, std::string lifetime, double precision) : MathExpObject(precision)
		{
			trailTexFP.create(1920, 1080);
			this->setPrecision(precision);
			this->registerMathExp("x", x);
			this->registerMathExp("y", y);
			this->registerMathExp("r", r);
			this->registerMathExp("g", g);
			this->registerMathExp("b", b);
			this->registerMathExp("a", a);
			this->registerMathExp("size", "1");
			this->registerMathExp("lifetime", lifetime);
			this->registerMathExp("trailLength", "0");
			this->registerMathExp("trailAlpha", "0");
			this->registerOutputVar("x", &this->x);
			this->registerOutputVar("y", &this->y);
			this->registerOutputVar("r", &this->r);
			this->registerOutputVar("g", &this->g);
			this->registerOutputVar("b", &this->b);
			this->registerOutputVar("a", &this->a);
			this->registerOutputVar("size", &this->size);
			this->registerOutputVar("lifetime", &this->lifetime);
			this->registerOutputVar("trailLength", &this->trailLength);
			this->registerOutputVar("trailAlpha", &this->trailAlpha);
			particleShape = new sf::RectangleShape(sf::Vector2f(1, 1));
			trailEnabled = true;
			this->update();
		}
		MathParticle::MathParticle(std::string id) : MathExpObject(0)
		{
			trailTexFP.create(1920, 1080);
			vili::DataParser particleSet("Data/Particles/particleSet.ptc.vili");
			std::vector<std::string> attributeList = { "size", "x", "y", "lowerBound", "upperBound", "r", "g", "b"\
				, "a", "lifetime","trailLength", "trailAlpha" };
			this->setPrecision(particleSet.at("Particles", id)->getBaseAttribute("precision")->get<double>());
			for (unsigned int i = 0; i < attributeList.size(); i++)
				this->registerMathExp(attributeList[i], particleSet.at("Particles", id)->getBaseAttribute(attributeList[i])->get<std::string>());
			this->registerOutputVar("x", &this->x);
			this->registerOutputVar("y", &this->y);
			this->registerOutputVar("r", &this->r);
			this->registerOutputVar("g", &this->g);
			this->registerOutputVar("b", &this->b);
			this->registerOutputVar("a", &this->a);
			this->registerOutputVar("size", &this->size);
			this->registerOutputVar("lifetime", &this->lifetime);
			this->registerOutputVar("trailLength", &this->trailLength);
			this->registerOutputVar("trailAlpha", &this->trailAlpha);
			particleShape = new sf::RectangleShape(sf::Vector2f(1, 1));
			this->update();
		}
		void MathParticle::setExp(std::string id, std::string exp)
		{
			this->registerMathExp(id, exp);
		}
		void MathParticle::update()
		{
			if (processedOnce && trailEnabled)
			{
				for (int i = trailVector.size() - 1; i >= 0; i--)
				{
					if (i == trailVector.size() - 1)
					{
						double trailR = r;
						double trailG = g;
						double trailB = b;
						double trailA = a / trailAlpha;
						trailVector[i].setFillColor(sf::Color(trailR, trailG, trailB, trailA));
					}
					else
					{
						double trailR = trailVector[i].getFillColor().r;
						double trailG = trailVector[i].getFillColor().g;
						double trailB = trailVector[i].getFillColor().b;
						double trailA = a / std::pow(trailAlpha, trailVector.size() - i);
						trailVector[i].setFillColor(sf::Color(trailR, trailG, trailB, trailA));
					}
				}
			}
			this->processAllExp();
		}

		void MathParticle::draw(sf::RenderWindow* surf)
		{
			trailTexFP.clear(sf::Color(0, 0, 0, 0));
			if (trailEnabled)
			{
				for (unsigned int i = 0; i < trailVector.size(); i++)
					trailTexFP.draw(trailVector[i]);
			}
			trailTexFP.display();
			sf::Sprite trailSprFP;
			trailSprFP.setTexture(trailTexFP.getTexture());
			trailSprFP.setPosition(0, 0);
			surf->draw(trailSprFP);
			particleShape->setFillColor(sf::Color(r, g, b, a));
			particleShape->setSize(sf::Vector2f(size, size));
			particleShape->setPosition(x, y);
			surf->draw(*particleShape);
			if (trailVector.size() > trailLength)
			{
				trailVector.erase(trailVector.begin());
				trailVector.push_back(*particleShape);
			}
			else
				trailVector.push_back(*particleShape);
	}
}}