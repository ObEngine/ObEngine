//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Functions.hpp"
#include "DataParser.hpp"
#include "TimeManager.hpp"
#include "PathResolver.hpp"

namespace mse
{
	namespace Animation
	{
		class AnimationGroup //A group containing an Image List
		{
		private:
			std::string groupName;
			int groupClock;
			signed long long int startDelayClock = 0;
			std::vector<sf::Texture*> groupList;
			sf::Texture spriteSheet;
			std::vector<sf::IntRect*> texturePos;
			sf::Sprite currentSprite;
			unsigned int groupIndex = 0;
			int groupSize = 0;
			bool groupOver = false;
			int currentLoop = 0;
			int loopTime = 0;

		public:
			AnimationGroup(std::string pgroupname);
			void build();
			void setGroupClock(int clock); //Set the clock of the group
			void setGroupLoop(int loops); //Set the number of times the group will repeat
			std::string getGroupName(); //Return the group name
			int getGroupClock(); //Return clock of the group
			int getGroupIndex(); //Return current group index
			int getGroupSize(); //Return group size (number of images)
			bool isGroupOver(); //Return true if all images have been displayed
			void pushTexture(sf::Texture* texture); //Add image to the groupe
			void removeTextureByIndex(int index); //Delete an image from the group with the given Index
			sf::Sprite* returnSprite(); //Return Total Sprite
			sf::IntRect* getSpriteRect();
			void updateSprite(); //Update the Sprite
			void reset(); //Reset the group
			void next(); //Increment index and go back to 0 if > groupSize
			void previous(); //Decrement index and go back to groupSize if < 0
			void forcePrevious(); //Force index decrement (ignoring clock)
			void forceNext(); //Force index increment (ignoring clock)
		};

		class RessourceManager
		{
		private:
			std::map<std::string, sf::Texture*> textureDatabase;
			static RessourceManager* instance;
			RessourceManager();
		public:
			static RessourceManager* GetInstance();
			~RessourceManager();
			sf::Texture* getTexture(std::string path);
		};

		class Animation //An animation containing an AnimationGroup list
		{
		private:
			std::string animationName;
			unsigned long long int lastTick = 0;
			int animationClock;
			std::string animationPlaymode;
			std::map<int, sf::Texture *> animationTextures;
			sf::Texture* currentTexture;
			std::map<std::string, AnimationGroup*> animationGroupMap;
			std::ifstream animationFile;
			std::vector<std::vector<std::string>> animationCode;
			std::string currentGroupName = "NONE";
			std::string currentStatus = "PLAY";
			RessourceManager* animatorRsHook;
			bool askCommand = true;
			unsigned int codeIndex = 0;
			int loopTime = 0;
			int currentDelay;
			unsigned long long int startDelay = 0;
			bool isOver = false;
			int sprOffsetX = 0;
			int sprOffsetY = 0;
			int priority = 0;

		public:
			std::string getAnimationName(); //Return animation name
			void attachRessourceManager(RessourceManager* rsMan); //Hook a RessourceManager
			void deleteRessourceManager(); //Delete the RessourceManager
			float getAnimationClock(); //Return Animation Clock
			AnimationGroup* getAnimationGroup(std::string groupname);
			std::string getCurrentAnimationGroup(); //Return current AnimationGroup
			std::vector<std::string> getAllAnimationGroupName();
			std::string getAnimationPlayMode(); //Return PlayMode
			std::string getAnimationStatus(); //Return AnimationStatus
			void loadAnimation(System::Path path, std::string filename); //Load Code File
			void applyParameters(Data::ComplexAttribute* parameters);
			void playAnimation(); //Execute next line
			void resetAnimation(); //Unselect group and restart code execution
			sf::IntRect* getSpriteRect();
			sf::Sprite* getSprite(); //Return actual texture
			sf::Texture* getTextureAtIndex(int index); //Return a specific texture
			bool isAnimationOver(); //Is animation over ?
			int getSpriteOffsetX();
			int getSpriteOffsetY();
			int getPriority();
		};

		class DirtyAnimation //Same as Animation but without any code
		{
		private:
			std::string animationName;
			signed long long int lastTick = 0;
			unsigned int textureIndex = 0;
			int oldTextureIndex = -1;
			int animationClock = 80;
			bool noTextureReturned = true;
			std::vector<sf::Texture*> animationTextures;
			sf::Texture* currentTexture;
			RessourceManager* animatorRsHook;

		public:
			~DirtyAnimation();
			void attachRessourceManager(RessourceManager* rsMan);
			void deleteRessourceManager();
			void setAnimationClock(int animClock);
			float getAnimationClock();
			void loadAnimation(System::Path path);
			void update();
			void setIndex(int index);
			int getIndex();
			bool indexChanged();
			sf::Texture* getTexture();
			sf::Texture* getNormal();
			sf::Texture* getTextureAtIndex(int index);
			sf::Texture* getNormalAtIndex(int index);
		};

		class Animator //A set of animations
		{
		private:
			std::map<std::string, Animation*> fullAnimSet;
			float globalClock;
			Animation* currentAnimation = nullptr;
			std::string currentAnimationName = "NONE";
			std::string animationBehaviour;
			System::Path animationPath;
			std::vector<std::string> allAnimationNames;
			int currentNameIndex = 0;
			sf::Sprite* lastSpriteAddress = nullptr;
			sf::IntRect lastRect;
			RessourceManager* ressourceManagerHook = nullptr;

		public:
			Animator();
			Animator(System::Path path);
			void setPath(System::Path path);
			void setPath(std::string path);
			void clear(bool clearMemory = true);
			Animation* getAnimation(std::string animationName);
			std::vector<std::string> getAllAnimationName();
			void attachRessourceManager(RessourceManager* rsMan); //Hook a RessourceManager
			void deleteRessourceManager(); //Delete the RessourceManager
			std::string getKey(); //Return current Animation name
			void setKey(std::string key); //Set current Animation
			void loadAnimator(); //Load Animator (And all Animations)
			void update(); //Update current animation
			sf::Sprite* getSprite();
			sf::Texture* getTextureAtKey(std::string key, int index); //Return specific texture in specific animation
			bool textureChanged(); //Return true if texture have changed since last call of getTexture()
			int getSpriteOffsetX();
			int getSpriteOffsetY();
		};
	}
}
