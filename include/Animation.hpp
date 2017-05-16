//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <fstream>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>
#include <vili/Vili.hpp>
#include <vili/ErrorHandler.hpp>

#include "Functions.hpp"
#include "TimeManager.hpp"
#include "PathResolver.hpp"

namespace obe
{
	namespace Animation
	{
		class AnimationGroup //A group containing an Image List
		{
		private:
			std::string m_groupName;
			int m_groupClock = 0;
			signed long long int m_startDelayClock = 0;
			std::vector<sf::Texture*> m_groupList;
			sf::Sprite m_currentSprite;
			int m_groupIndex = 0;
			int m_groupSize = 0;
			bool m_groupOver = false;
			int m_currentLoop = 0;
			int m_loopTime = 0;

		public:
			explicit AnimationGroup(std::string pgroupname);
			void build();
			void setGroupClock(const int& clock); //Set the clock of the group
			void setGroupLoop(const int& loops); //Set the number of times the group will repeat
			std::string getGroupName() const; //Return the group name
			int getGroupClock() const; //Return clock of the group
			int getGroupIndex() const; //Return current group index
			int getGroupSize() const; //Return group size (number of images)
			bool isGroupOver() const; //Return true if all images have been displayed
			void pushTexture(sf::Texture* texture); //Add image to the groupe
			void removeTextureByIndex(const int& index); //Delete an image from the group with the given Index
			sf::Sprite* returnSprite(); //Return Total Sprite
			void updateSprite(); //Update the Sprite
			void reset(); //Reset the group
			void next(); //Increment index and go back to 0 if > groupSize
			void previous(); //Decrement index and go back to groupSize if < 0
			void forcePrevious(); //Force index decrement (ignoring clock)
			void forceNext(); //Force index increment (ignoring clock)
		};

		class RessourceManager //Class that caches textures
		{
		private:
			std::map<std::string, std::unique_ptr<sf::Texture>> textureDatabase;
			static RessourceManager* instance;
		public:
			static RessourceManager* GetInstance();
			sf::Texture* getTexture(std::string path);
		};

		class Animation //An animation contains multiple AnimationGroup
		{
		private:
			std::string animationName;
			unsigned long long int lastTick = 0;
			int animationClock = 0;
			std::string animationPlaymode;
			sf::Texture* currentTexture = nullptr;
			std::map<int, sf::Texture*> animationTextures;
			std::map<std::string, std::unique_ptr<AnimationGroup>> animationGroupMap;
			std::ifstream animationFile;
			std::vector<std::vector<std::string>> animationCode;
			std::string currentGroupName = "NONE";
			std::string currentStatus = "PLAY";
			bool askCommand = true;
			unsigned int codeIndex = 0;
			int loopTime = 0;
			int currentDelay = 0;
			unsigned long long int startDelay = 0;
			bool isOver = false;
			int sprOffsetX = 0;
			int sprOffsetY = 0;
			int priority = 0;

		public:
			std::string getAnimationName() const; //Return animation name
			float getAnimationClock() const; //Return Animation Clock
			AnimationGroup* getAnimationGroup(std::string groupname);
			std::string getCurrentAnimationGroup() const; //Return current AnimationGroup
			std::vector<std::string> getAllAnimationGroupName();
			std::string getAnimationPlayMode() const; //Return PlayMode
			std::string getAnimationStatus() const; //Return AnimationStatus
			void loadAnimation(System::Path path, std::string filename); //Load Code File
			void applyParameters(vili::ComplexAttribute* parameters);
			void playAnimation(); //Execute next line
			void resetAnimation(); //Unselect group and restart code execution
			sf::Sprite* getSprite(); //Return actual texture
			sf::Texture* getTextureAtIndex(int index); //Return a specific texture
			bool isAnimationOver() const; //Is animation over ?
			int getSpriteOffsetX() const;
			int getSpriteOffsetY() const;
			int getPriority() const;
		};

		class Animator //A set of animations
		{
		private:
			std::map<std::string, std::unique_ptr<Animation>> fullAnimSet;
			float globalClock = 0;
			Animation* currentAnimation = nullptr;
			std::string currentAnimationName = "NONE";
			std::string animationBehaviour;
			System::Path animationPath;
			std::vector<std::string> allAnimationNames;
			int currentNameIndex = 0;
			sf::Sprite* lastSpriteAddress = nullptr;
			sf::IntRect lastRect;

		public:
			Animator();
			Animator(System::Path path);
			void setPath(System::Path path);
			void setPath(std::string path);
			void clear(bool clearMemory = true);
			Animation* getAnimation(std::string animationName); //Return a pointer to the current animation
			std::vector<std::string> getAllAnimationName() const; //Return a vector of all animation names
			std::string getKey() const; //Return current Animation name
			void setKey(std::string key); //Set current Animation
			void loadAnimator(); //Load Animator (And all Animations)
			void update(); //Update current animation
			sf::Sprite* getSprite(); //Returns the Sprite of the current animation
			sf::Texture* getTextureAtKey(std::string key, int index); //Return specific texture in specific animation
			bool textureChanged() const; //Return true if texture have changed since last call of getTexture()
			int getSpriteOffsetX() const; //Returns offset of current sprite
			int getSpriteOffsetY() const; //Returns offset of current sprite
		};
	}
}
