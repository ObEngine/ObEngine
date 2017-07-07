//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <any/any.hpp>

#include "PathResolver.hpp"

namespace obe
{
    namespace Graphics
    {
        extern sf::RenderTexture renTex;

        enum RendererState
        {
            FadeIn = 0x001,
            Draw = 0x002,
            FadeOut = 0x003,
            End = 0x004
        };

        class Renderer
        {
        protected:
            std::map<std::string, Types::any> locals;
            std::vector<std::map<std::string, std::string>> vtdb;
            int fadeState = 0;
        public:
            std::string name;
            Renderer(std::string name);
            virtual void load() = 0;
            virtual void unload() = 0;
            virtual void render() = 0;
            virtual void draw(sf::RenderWindow* surf) = 0;
            virtual void fadeIn(sf::RenderWindow* surf);
            virtual void fadeOut(sf::RenderWindow* surf);
            virtual void update(double dt);
            void setFadeState(int state);
            int getFadeState() const;
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
            bool textRemaining() const;
            void next() const;
            void update(double dt);
            void render(sf::RenderWindow* surf);
        };

        namespace Renderers
        {
            class VisualNovel : public Renderer
            {
            public:
                VisualNovel();
            private:
                void load() override;
                void unload() override;
                void render() override;
                void draw(sf::RenderWindow* surf) override;
            };

            class Shade : public Renderer
            {
            public:
                Shade();
            private:
                void load() override;
                void unload() override;
                void render() override;
                void draw(sf::RenderWindow* surf) override;
                void fadeOut(sf::RenderWindow* surf) override;
                void update(double dt) override;
            };

            class Choice : public Renderer
            {
            public:
                Choice();
            private:
                void load() override;
                void unload() override;
                void render() override;
                void draw(sf::RenderWindow* surf) override;
            };
        }
    }
}
