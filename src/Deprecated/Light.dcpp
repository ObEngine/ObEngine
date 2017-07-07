//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "Light.hpp"

namespace obe
{
    namespace Light
    {
        sf::RectangleShape PointLight::rtTex;

        void initLights()
        {
            PointLight::rtTex.setSize(sf::Vector2f(1920, 1080));
            PointLight::rtTex.setFillColor(sf::Color(0, 0, 0, 0));
            DynamicPointLight::rtTex.setSize(sf::Vector2f(1920, 1080));
            DynamicPointLight::rtTex.setFillColor(sf::Color(0, 0, 0, 0));
        }

        //PointLight
        PointLight::PointLight(std::string id, sf::Vector2f screenSize, sf::Vector2f position, double size, sf::Color color, bool behind)
        {
            this->id = id;
            this->x = position.x;
            this->y = position.y;
            this->size = size;
            this->r = color.r;
            this->g = color.g;
            this->b = color.b;
            this->a = color.a;
            this->behind = behind;
            shader = new sf::Shader;
            shader->loadFromFile("Data/Shaders/lightShader.frag", sf::Shader::Fragment);
            shader->setUniform("frag_ScreenResolution", screenSize);
            shader->setUniform("frag_LightOrigin", position);
            shader->setUniform("frag_LightColor", sf::Vector3f(color.r, color.g, color.b));
            shader->setUniform("frag_LightAlpha", color.a);
            shader->setUniform("frag_LightAttenuation", (float)size);
            states.shader = shader;
            states.blendMode = sf::BlendAdd;
        }

        PointLight::PointLight(std::string id, int screenSizeX, int screenSizeY, int x, int y, double size, int r, int g, int b, int a, bool behind)
        {
            this->id = id;
            this->x = x;
            this->y = y;
            this->size = size;
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
            this->behind = behind;
            shader = new sf::Shader;
            shader->loadFromFile("Data/Shaders/lightShader.frag", sf::Shader::Fragment);
            shader->setUniform("frag_ScreenResolution", sf::Vector2f(screenSizeX, screenSizeY));
            shader->setUniform("frag_LightOrigin", sf::Vector2f(x, y));
            shader->setUniform("frag_LightColor", sf::Vector3f(r, g, b));
            shader->setUniform("frag_LightAlpha", a);
            shader->setUniform("frag_LightAttenuation", (float)size);
            states.shader = shader;
            states.blendMode = sf::BlendAdd;
        }

        void PointLight::checkColors()
        {
            (r < 0) ? r = 0 : r = r;
            (r > 255) ? r = 255 : r = r;

            (g < 0) ? g = 0 : g = g;
            (g > 255) ? g = 255 : g = g;

            (b < 0) ? b = 0 : b = b;
            (b > 255) ? b = 255 : b = b;

            (a < 0) ? a = 0 : a = a;
            (a > 255) ? a = 255 : a = a;
        }

        std::string PointLight::getID()
        {
            return id;
        }

        void PointLight::draw(sf::RenderWindow* surf)
        {
            if (visible) surf->draw(rtTex, states);
        }

        void PointLight::setPosition(double x, double y)
        {
            this->x = x;
            this->y = y;
            shader->setUniform("frag_LightOrigin", sf::Vector2f(this->x + this->offX, this->y + this->offY));
        }

        void PointLight::move(double x, double y)
        {
            this->x += x;
            this->y += y;
            shader->setUniform("frag_LightOrigin", sf::Vector2f(this->x + this->offX, this->y + this->offY));
        }

        void PointLight::setOffset(double x, double y)
        {
            this->offX = x;
            this->offY = y;
        }

        void PointLight::setSize(double size)
        {
            this->size = size;
            shader->setUniform("frag_LightAttenuation", (float)this->size);
        }

        void PointLight::scale(double size)
        {
            this->size *= size;
            shader->setUniform("frag_LightAttenuation", (float)this->size);
        }

        void PointLight::setColor(int r, int g, int b, int a)
        {
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
            this->checkColors();
            shader->setUniform("frag_LightColor", sf::Vector3f(this->r, this->g, this->b));
            shader->setUniform("frag_LightAlpha", (float)this->a);
        }

        void PointLight::addColor(int r, int g, int b, int a)
        {
            this->r += r;
            this->g += g;
            this->b += b;
            this->a += a;
            this->checkColors();
            shader->setUniform("frag_LightColor", sf::Vector3f(this->r, this->g, this->b));
            shader->setUniform("frag_LightAlpha", (float)this->a);
        }

        void PointLight::subColor(int r, int g, int b, int a)
        {
            this->r -= r;
            this->g -= g;
            this->b -= b;
            this->a -= a;
            this->checkColors();
            shader->setUniform("frag_LightColor", sf::Vector3f(this->r, this->g, this->b));
            shader->setUniform("frag_LightAlpha", (float)this->a);
        }

        void PointLight::blendColor(double rB, double gB, double bB, double aB)
        {
            this->r *= rB;
            this->g *= gB;
            this->b *= bB;
            this->a *= aB;
            this->checkColors();
            shader->setUniform("frag_LightColor", sf::Vector3f(this->r, this->g, this->b));
            shader->setUniform("frag_LightAlpha", (float)this->a);
        }

        void PointLight::setBehind(bool behind)
        {
            this->behind = behind;
        }

        void PointLight::show()
        {
            visible = true;
        }

        void PointLight::hide()
        {
            visible = false;
        }

        void PointLight::setVisible(bool state)
        {
            visible = state;
        }

        bool PointLight::isVisible()
        {
            return visible;
        }

        sf::Vector2f PointLight::getPosition()
        {
            return sf::Vector2f(x, y);
        }

        double PointLight::getX()
        {
            return x;
        }

        double PointLight::getY()
        {
            return y;
        }

        double PointLight::getSize()
        {
            return size;
        }

        sf::Color PointLight::getColor()
        {
            return sf::Color(r, g, b, a);
        }

        double PointLight::getR()
        {
            return r;
        }

        double PointLight::getG()
        {
            return g;
        }

        double PointLight::getB()
        {
            return b;
        }

        double PointLight::getA()
        {
            return a;
        }

        bool PointLight::isBehind()
        {
            return behind;
        }

        double* PointLight::getX_p()
        {
            return &x;
        }

        double* PointLight::getY_p()
        {
            return &y;
        }

        double* PointLight::getSize_P()
        {
            return &size;
        }

        double* PointLight::getR_P()
        {
            return &r;
        }

        double* PointLight::getG_P()
        {
            return &g;
        }

        double* PointLight::getB_P()
        {
            return &b;
        }

        double* PointLight::getA_P()
        {
            return &a;
        }

        std::string PointLight::getType()
        {
            return "Static";
        }

        void PointLight::updateShader()
        {
            shader->setUniform("frag_LightOrigin", sf::Vector2f(this->x + this->offX, this->y + this->offY));
            shader->setUniform("frag_LightColor", sf::Vector3f(this->r, this->g, this->b));
            shader->setUniform("frag_LightAlpha", (float)this->a);
            shader->setUniform("frag_LightAttenuation", (float)this->size);
        }

        //DynamicPointLight
        DynamicPointLight::DynamicPointLight(std::string id, sf::Vector2f screenSize, double precision) : MathExpObject(precision), PointLight(id, screenSize, sf::Vector2f(0, 0), 0, sf::Color(0, 0, 0))
        {
            this->registerOutputVar("size", &size);
            this->registerOutputVar("r", &r);
            this->registerOutputVar("g", &g);
            this->registerOutputVar("b", &b);
            this->registerOutputVar("a", &a);
            this->registerOutputVar("offsetX", &offX);
            this->registerOutputVar("offsetY", &offY);
        }

        DynamicPointLight::DynamicPointLight(std::string id, int screenSizeX, int screenSizeY, double precision) : MathExpObject(precision), PointLight(id, sf::Vector2f(screenSizeX, screenSizeY), sf::Vector2f(0, 0), 0, sf::Color(0, 0, 0))
        {
            this->registerOutputVar("size", &size);
            this->registerOutputVar("r", &r);
            this->registerOutputVar("g", &g);
            this->registerOutputVar("b", &b);
            this->registerOutputVar("a", &a);
            this->registerOutputVar("offsetX", &offX);
            this->registerOutputVar("offsetY", &offY);
        }

        void DynamicPointLight::setSizeExp(std::string size)
        {
            this->registerMathExp("size", size);
        }

        void DynamicPointLight::setRExp(std::string r)
        {
            this->registerMathExp("r", r);
        }

        void DynamicPointLight::setGExp(std::string g)
        {
            this->registerMathExp("g", g);
        }

        void DynamicPointLight::setBExp(std::string b)
        {
            this->registerMathExp("b", b);
        }

        void DynamicPointLight::setAExp(std::string a)
        {
            this->registerMathExp("a", a);
        }

        void DynamicPointLight::setOffsetXExp(std::string x)
        {
            this->registerMathExp("offsetX", x);
        }

        void DynamicPointLight::setOffsetYExp(std::string y)
        {
            this->registerMathExp("offsetY", y);
        }

        std::string DynamicPointLight::getType()
        {
            return "Dynamic";
        }

        void DynamicPointLight::updateLight()
        {
            this->processAllExp();
            this->checkColors();
            this->updateShader();
        }
    }
}
