//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "Console.hpp"

namespace obe
{
	namespace Console
	{
		//Console
		Console::Console::Console()
		{
			font.loadFromFile("Data/Fonts/arial.ttf");
			scrEngineStream = this->createStream("ScriptEngine", true);
			scrErrorStream = this->createStream("ScriptError", true);
			scrErrorStream->setColor(255, 0, 0);
			consoleTriggers = Script::TriggerDatabase::GetInstance()->createTriggerGroup("Global", "Console")
			                                                        ->addTrigger("UserInput")
			                                                        ->addTrigger("CursorMoved")
			                                                        ->addTrigger("ConsoleScrolled")
			                                                        ->addTrigger("NewMessage")
			                                                        ->addTrigger("ConsoleToggled")
			                                                        ->addTrigger("NewStream");
		}

		void Console::Console::scroll(int power)
		{
			if (consoleScroll + power > 0)
			{
				if (consoleScroll + power <= static_cast<int>(consoleText.size()) - 52)
					consoleScroll += power;
			}
			else
				consoleScroll = 0;
		}

		Console::Stream* Console::createStream(std::string streamName, bool enabled)
		{
			Stream* tempStream = new Stream(streamName, this);
			streamMap[streamName] = tempStream;
			streamList.push_back(streamName);
			if (!enabled)
				disabledStreams.push_back(streamName);
			/*consoleTriggers->pushParameter("NewStream", "StreamName", streamName);
			consoleTriggers->pushParameter("NewStream", "Enabled", enabled);*/
			return streamMap[streamName];
		}

		Console::Stream* Console::getStream(std::string streamName)
		{
			if (Functions::Vector::isInList(streamName, streamList))
				return streamMap[streamName];
			throw aube::ErrorHandler::Raise("ObEngine.Console.Console.UnknownStream", { {"stream", streamName} });
		}

		void Console::downHistory()
		{
			if (consoleHistoryIndex < consoleHistory.size() - 1)
				consoleHistoryIndex++;
			else
				consoleHistoryIndex = consoleHistory.size() - 1;
			if (consoleHistory.size() != 0)
			{
				inputBuffer = consoleHistory[consoleHistoryIndex];
				virtualCursor = consoleHistory[consoleHistoryIndex].size();
			}
		}

		void Console::upHistory()
		{
			if (consoleHistoryIndex > 0)
				consoleHistoryIndex--;
			else
				consoleHistoryIndex = 0;
			if (consoleHistory.size() != 0)
			{
				inputBuffer = consoleHistory[consoleHistoryIndex];
				virtualCursor = consoleHistory[consoleHistoryIndex].size();
			}
		}

		Console::Message* Console::pushMessage(std::string headerName, std::string message, int r, int g, int b, int a, std::string type, bool disableTimestamp)
		{
			Message* forgeMessage = new Message("", "", sf::Color(0, 0, 0), "", false);
			if (Functions::String::occurencesInString(message, "\n") > 0 && !consoleMuted)
			{
				std::vector<std::string> sepMessage = Functions::String::split(message, "\n");
				for (int i = 0; i < sepMessage.size(); i++)
				{
					if (i == 0)
						this->pushMessage(headerName, sepMessage[i], r, g, b, a, type);
					else
						this->pushMessage(headerName, sepMessage[i], r, g, b, a, type, false);
				}
			}
			else if (!consoleMuted)
			{
				if (!Functions::Vector::isInList(headerName, disabledStreams))
				{
					delete forgeMessage;
					forgeMessage = new Message(headerName, message, sf::Color(r, g, b, a), type, !disableTimestamp);
					consoleText.push_back(forgeMessage);
				}
				if (consoleAutoScroll)
				{
					if (consoleText.size() >= 52)
					{
						consoleScroll = consoleText.size() - 52;
					}
				}
			}
			return forgeMessage;
		}

		void Console::handleCommands(std::string text)
		{
			this->pushMessage("UserInput", text, 0, 255, 255);
			commandReady = true;
			currentCommand = text;
			if (consoleHistory.size() == 0 || currentCommand != consoleHistory[consoleHistory.size() - 1])
				consoleHistory.push_back(currentCommand);
			consoleHistoryIndex = consoleHistory.size();
		}

		std::string Console::getCommand()
		{
			commandReady = false;
			return currentCommand;
		}

		bool Console::hasCommand()
		{
			return commandReady;
		}

		void Console::inputKey(int keyCode)
		{
			std::cout << "Current Key : " << keyCode << std::endl;
			switch (keyCode)
			{
			case 8:
				if (virtualCursor > 0)
				{
					virtualCursor--;
					inputBuffer.erase(inputBuffer.begin() + virtualCursor);
				}
				break;
			case 13:
				this->handleCommands(inputBuffer);
				this->clearInputBuffer();
				virtualCursor = 0;
				break;
			case 22:
				std::cout << "PASTE" << std::endl;
				break;
			default:
				inputBuffer.insert(inputBuffer.begin() + virtualCursor, static_cast<char>(keyCode));
				virtualCursor++;
				break;
			}
		}

		void Console::moveCursor(int move)
		{
			if (virtualCursor + move <= inputBuffer.size() && virtualCursor + move >= 0)
				virtualCursor += move;
		}

		void Console::clearInputBuffer()
		{
			inputBuffer = "";
		}

		void Console::insertInputBufferContent(std::string content)
		{
			inputBuffer.insert(virtualCursor, content);
			virtualCursor += content.size();
		}

		void Console::setInputBufferContent(std::string content)
		{
			inputBuffer = content;
			inputBuffer = content.size();
		}

		std::string Console::getInputBufferContent()
		{
			return inputBuffer;
		}

		bool Console::isConsoleVisible()
		{
			return consoleVisibility;
		}

		void Console::setConsoleVisibility(bool enabled)
		{
			consoleVisibility = enabled;
		}

		void Console::display(sf::RenderWindow* surf)
		{
			//OUTPUT
			surf->clear(sf::Color(0, 0, 0, 200));
			sf::Text textOutput;
			textOutput.setFont(font);
			textOutput.setFillColor(sf::Color(255, 255, 255));
			textOutput.setCharacterSize(13);
			bool alternBackground = false;
			sf::Color backgroundColor = sf::Color(30, 30, 30, 200);
			sf::RectangleShape rectangle = sf::RectangleShape(sf::Vector2f(Coord::UnitVector::Screen.w, 20));
			int textX = 5;
			int textY = 1;
			for (unsigned int i = 0; i < 1040; i += 20)
			{
				alternBackground = !alternBackground;
				if (alternBackground)
				{
					backgroundColor = sf::Color(30, 30, 30, 200);
				}
				else
				{
					backgroundColor = sf::Color(50, 50, 50, 200);
				}
				rectangle.setPosition(0, i);
				rectangle.setFillColor(backgroundColor);
				surf->draw(rectangle);
			}
			for (unsigned int i = 0 + consoleScroll; i < consoleText.size(); i++)
			{
				textOutput.setString(consoleText[i]->getFormatedMessage());
				textOutput.setFillColor(consoleText[i]->getColor());
				textOutput.setPosition(sf::Vector2f(textX, textY));
				surf->draw(textOutput);
				textY += 20;
			}

			//FRAME
			sf::RectangleShape rectangleFrame = sf::RectangleShape(sf::Vector2f(Coord::UnitVector::Screen.w - 4, Coord::UnitVector::Screen.h - 4));
			rectangleFrame.setFillColor(sf::Color(0, 0, 0, 0));
			rectangleFrame.setOutlineColor(sf::Color(255, 255, 255, 255));
			rectangleFrame.setOutlineThickness(2);
			rectangleFrame.move(2, 2);
			surf->draw(rectangleFrame);

			//INPUT
			sf::RectangleShape rectangleInput = sf::RectangleShape(sf::Vector2f(Coord::UnitVector::Screen.w, 40));
			rectangleInput.setPosition(0, Coord::UnitVector::Screen.h - 40);
			rectangleInput.setFillColor(sf::Color(100, 100, 100));
			surf->draw(rectangleInput);
			//CURSOR
			sf::RectangleShape rectangleCursor = sf::RectangleShape(sf::Vector2f(2, 30));
			sf::Text estimate;
			estimate.setFont(font);
			estimate.setCharacterSize(26);
			estimate.setString(inputBuffer.substr(0, virtualCursor));
			int consoleCurPos = estimate.getGlobalBounds().width;
			rectangleCursor.setPosition(consoleCurPos + 2, Coord::UnitVector::Screen.h - 35);
			rectangleCursor.setFillColor(sf::Color(200, 200, 200));
			surf->draw(rectangleCursor);
			//TEXT
			sf::Text textInput;
			textInput.setFont(font);
			textInput.setFillColor(sf::Color(255, 255, 255));
			textInput.setCharacterSize(26);
			textInput.setPosition(2, Coord::UnitVector::Screen.h - 40);
			textInput.setString(inputBuffer);
			surf->draw(textInput);
		}

		//ConsoleMessage

		Console::Message::Message(std::string header, std::string message, sf::Color textColor, std::string type, bool timestamped)
		{
			this->header = header;
			this->message = message;
			this->textColor = textColor;
			this->type = type;
			this->timestamp = Time::getTickSinceEpoch();
			this->useTimeStamp = timestamped;
		}

		std::string Console::Message::getFormatedMessage()
		{
			std::string fMessage;
			if (useTimeStamp)
			{
				fMessage = "(TimeStamp:" + std::to_string(timestamp) + ")";
				fMessage += " [" + header + "]";
				if (type != "DEFAULT")
				{
					fMessage += " <" + type + ">";
				}
				fMessage += " : " + message;
			}
			else
				fMessage = message;
			return fMessage;
		}

		std::string Console::Message::getHeader()
		{
			return header;
		}

		std::string Console::Message::getMessage()
		{
			return message;
		}

		sf::Color Console::Message::getColor()
		{
			return textColor;
		}

		int Console::Message::getR()
		{
			return textColor.r;
		}

		int Console::Message::getG()
		{
			return textColor.g;
		}

		int Console::Message::getB()
		{
			return textColor.b;
		}

		int Console::Message::getA()
		{
			return textColor.a;
		}

		std::string Console::Message::getType()
		{
			return type;
		}

		void Console::Message::setMessage(std::string newmessage)
		{
			this->message = newmessage;
		}

		void Console::Message::setColor(int r, int g, int b, int a)
		{
			if (r < 0) r = 0;
			if (g < 0) g = 0;
			if (b < 0) b = 0;
			if (a < 0) a = 0;
			if (r > 255) r = 255;
			if (g > 255) g = 255;
			if (b > 255) b = 255;
			if (a > 255) a = 255;
			this->textColor.r = r;
			this->textColor.g = g;
			this->textColor.b = b;
			this->textColor.a = a;
		}


		//Stream

		Console::Stream::Stream(std::string streamName, Console* consolePointer)
		{
			this->streamName = streamName;
			this->consolePointer = consolePointer;
			streamColor = sf::Color(255, 255, 255);
		}

		Console::Message* Console::Stream::streamPush(std::string message, int r, int g, int b, int a)
		{
			return consolePointer->pushMessage(streamName, message, r, g, b, a, "DEFAULT");;
		}

		Console::Message* Console::Stream::streamPush(std::string message)
		{
			return consolePointer->pushMessage(streamName, message, streamColor.r, streamColor.g, streamColor.b, streamColor.a, "DEFAULT");;
		}

		void Console::Stream::setColor(int r, int g, int b, int a)
		{
			streamColor = sf::Color(r, g, b, a);
		}

		sf::Color Console::Stream::getColor()
		{
			return streamColor;
		}

		int Console::Stream::getR()
		{
			return streamColor.r;
		}

		int Console::Stream::getG()
		{
			return streamColor.g;
		}

		int Console::Stream::getB()
		{
			return streamColor.g;
		}

		int Console::Stream::getA()
		{
			return streamColor.a;
		}
	}
}
