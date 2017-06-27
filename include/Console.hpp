//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <thread>
#include <vili/Vili.hpp>

#include "Coordinates.hpp"
#include "Triggers.hpp"

namespace obe
{
    namespace Debug
    {
        class Console
        {
        public:
            class Message
            {
            private:
                std::string header;
                std::string message;
                sf::Color textColor;
                std::string type;
                unsigned long long int timestamp;
                bool useTimeStamp;
            public:
                Message(std::string header, std::string message, sf::Color textColor, std::string type, bool timestamped = true);
                std::string getFormatedMessage();
                std::string getHeader();
                std::string getMessage();
                sf::Color getColor();
                int getR();
                int getG();
                int getB();
                int getA();
                std::string getType();
                void setMessage(std::string newmessage);
                void setColor(int r, int g, int b, int a = 255);
            };

            class Stream
            {
            private:
                std::string streamName;
                Console* consolePointer;
                sf::Color streamColor = sf::Color(255, 255, 255);
                std::vector<std::string> queryList;
            public:
                Stream(std::string streamName, Console* consolePointer);
                Message* streamPush(std::string message, int r, int g, int b, int a);
                Message* streamPush(std::string message);
                void setColor(int r, int g, int b, int a = 255);
                sf::Color getColor();
                int getR();
                int getG();
                int getB();
                int getA();
            };

            Console();
            void handleCommands(std::string text);
            std::string getCommand();
            bool hasCommand();
            void scroll(int power);
            Message* pushMessage(std::string headerName, std::string message, int r = 255, int g = 255, int b = 255, int a = 255, std::string type = "DEFAULT", bool disableTimestamp = false);
            void inputKey(int keyCode);
            void clearInputBuffer();
            std::string getInputBufferContent();
            void setInputBufferContent(std::string content);
            void insertInputBufferContent(std::string content);
            Stream* createStream(std::string streamName, bool enabled = true);
            Stream* getStream(std::string streamName);
            void downHistory();
            void upHistory();
            void display(sf::RenderWindow* surf);
            bool isConsoleVisible();
            void setConsoleVisibility(bool enabled);
            void moveCursor(int move);

        private:
            Stream* scrEngineStream;
            Stream* scrErrorStream;
            int virtualCursor = 0;
            bool consoleVisibility = false;
            int consoleScroll = 0;
            bool consoleAutoScroll = true;
            bool consoleMuted = false;
            bool commandReady = false;
            int consoleHistoryIndex = 0;
            std::vector<std::string> consoleHistory;
            std::string currentCommand;
            std::string currentTheme;
            sf::Font font;
            std::string inputBuffer;
            std::map<std::string, Stream*> streamMap;
            std::map<std::string, std::string> aliasMap;
            std::vector<std::string> userCommandList;
            std::vector<std::string> streamList;
            std::vector<std::string> disabledStreams;
            std::vector<Message*> consoleText;
            Script::TriggerGroup::Ptr consoleTriggers;
        };
    }
}
