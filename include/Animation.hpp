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


/**
 * \file Animation.hpp
 * \brief Various Animation Classes
 * \author Sygmei
 * \version 1.0
 **/

namespace obe
{
	/**
     * \brief Various Animation Classes
     */
    namespace Animation
    {
	    /**
         * \brief A subpart of an Animation containing the Textures to display
         */
        class AnimationGroup
        {
        private:
	        /**
             * \brief The name of the AnimationGroup
             */
            std::string m_groupName;
	        /**
             * \brief The delay between each frame of the AnimationGroup
             */
            unsigned int m_groupDelay = 0;
	        /**
             * \brief Stores the last epoch to wait until the AnimationGroup delay
             */
            Time::TimeUnit m_groupClock = 0;
	        /**
             * \brief The list that contains pointers to all textures in the AnimationGroup
             */
            std::vector<sf::Texture*> m_groupList;
	        /**
             * \brief The current sprite of the AnimationGroup
             */
            sf::Sprite m_currentSprite;
	        /**
             * \brief The current index of the AnimationGroup
             */
            unsigned int m_groupIndex = 0;
	        /**
             * \brief Does the AnimationGroup reached the end
             */
            bool m_groupOver = false;
	        /**
             * \brief The amount of times the AnimationGroup has been repeated
             */
            int m_loopIndex = 0;
			/**
			* \brief The amount of times the AnimationGroup will be repeated
			*/
            int m_loopAmount = 0;

        public:
            explicit AnimationGroup(const std::string& groupName);
	        /**
             * \brief Initialize animation (Set image at index 0)
             */
            void build();
	        /**
             * \brief Set the delay between each frame of the AnimationGroup
             * \param delay Delay in milliseconds
             */
            void setGroupDelay(unsigned int delay);
	        /**
             * \brief Set how many times the AnimationGroup should be replayed before end
             * \param loops Amount of loops to do
             */
            void setGroupLoop(int loops);
	        /**
             * \brief Get the name of the AnimationGroup
             * \return A std::string containing the AnimationGroup's name
             */
            std::string getGroupName() const;
	        /**
             * \brief Get the delay between each frame of the AnimationGroup
             * \return The delay between each frame in milliseconds
             */
            unsigned int getGroupDelay() const;
	        /**
             * \brief Get the current index of AnimationGroup
             * \return The index of the texture in the AnimationGroup currently displayed
             */
            unsigned int getGroupIndex() const;
	        /**
             * \brief Get the AnimationGroup size
             * \return The number of textures in the AnimationGroup
             */
            unsigned int getGroupSize() const;
	        /**
             * \brief Get if the AnimationGroup is done playing
             * \return A boolean which is true if the AnimationGroup's Animation is over
             */
            bool isGroupOver() const;
	        /**
             * \brief Adds a new texture to the AnimationGroup
             * \param texture A pointer of a sf::Texture to add to the AnimationGroup
             */
            void pushTexture(sf::Texture* texture);
	        /**
             * \brief Removes the texture at the given index in the AnimationGroup
             * \param index Removes the texture at index
             */
            void removeTextureByIndex(unsigned int index);
	        /**
             * \brief Get the current Sprite of the AnimationGroup
             * \return A pointer of the sf::Texture currently played by the AnimationGroup
             */
            sf::Sprite* returnSprite();
	        /**
             * \brief Updates the Sprite to display (Done automatically after previous / next)
             */
            void updateSprite();
	        /**
             * \brief Resets the AnimationGroup (Index to 0, Loops to 0, Delay to 0)
             */
            void reset();
	        /**
             * \brief Decrement index of the current texture to be displayed.\n
             *		  If index reach 0 and no more loops, the AnimationGroup index will stay at 0.\n
             *		  If index reach 0 and there is some loops left, index will go at getGroupSize() - 1.
             */
            void previous();
			/**
			* \brief Increment index of the current texture to be displayed.\n
			*		  If max index is reached and no more loops, the AnimationGroup will be over.\n
			*		  If max index is reached but there is some loops left, index will go back to 0.\n
			*/
			void next();
	        /**
             * \brief Just like AnimationGroup::previous without any checks
             */
            void forcePrevious();
	        /**
             * \brief Just like AnimationGroup::next without any checks
             */
            void forceNext();
        };

	    /**
         * \brief Singleton Class that manages sf::Texture used in AnimationGroup
         */
        class RessourceManager
        {
        private:
            std::map<std::string, std::unique_ptr<sf::Texture>> m_textureDatabase;
            static RessourceManager* m_instance;
        public:
	        /**
             * \brief Access the Instance of the RessourceManager
             * \return A pointer to the Instance of the RessourceManager
             */
            static RessourceManager* GetInstance();
	        /**
             * \brief Get the texture at the given path.\n 
             *		  If it's already in cache it returns the cached version.\n
             *		  Otherwise it loads the texture and caches it.
             * \param path Relative of absolute path to the texture, it uses the obe::System::Path loading system
             * \return A pointer to the texture stored in the cache
             */
            sf::Texture* getTexture(const std::string& path);
        };

	    /**
		 * \brief The Play Mode of an Animation.\n
		 *        It indicates whether an Animation can be interrupted or not and what to do when the Animation is over.
		 */
		enum AnimationPlayMode
		{
			/**
			 * \brief The Animation will play once and stay at last texture
			 */
			OneTime,
			/**
			 * \brief The Animation will play in loop and can be interrupted at any time
			 */
			Loop,
			/**
			 * \brief The Animation will be played Once and can't be interrupted
			 */
			Force
		};

	    /**
		 * \brief Converts a std::string containing an AnimationPlayMode in string form to an AnimationPlayMode enum value.
		 * \param animationPlayMode The std::string containing the AnimationPlayMode in string form.
		 * \return The converted value which is an AnimationPlayMode enum value.
		 */
		AnimationPlayMode stringToAnimationPlayMode(const std::string& animationPlayMode);

	    /**
		 * \brief The AnimationStatus indicates whether the current Animation should continue to play or call another one.
		 */
		enum AnimationStatus
		{
			/**
			 * \brief The Animation continues to play.
			 */
			Play,
			/**
			 * \brief The Animation will call another one.\n
			 *	      The name of the Animation to call is stored in m_animationToCall.\n
			 *	      You can also get the Animation name to call by using Animation::getCalledAnimation().
			 */
			Call
		};

	    /**
         * \brief A whole Animation that contains one or more AnimationGroup.
         */
        class Animation
        {
        private:
            std::string m_animationName;
            unsigned int m_animationDelay = 0;
            AnimationPlayMode m_animationPlayMode = OneTime;
            std::map<int, sf::Texture*> m_animationTextures;
            std::map<std::string, std::unique_ptr<AnimationGroup>> m_animationGroupMap;
            std::vector<std::vector<std::string>> m_animationCode;
            std::string m_currentGroupName = "NONE";
            AnimationStatus m_currentStatus = Play;
			std::string m_animationToCall = "";
            bool m_askCommand = true;
            unsigned int m_codeIndex = 0;
            int m_loopAmount = 0;
            int m_currentDelay = 0;
			Time::TimeUnit m_animationClock = 0;
            bool m_isOver = false;
            int m_sprOffsetX = 0;
            int m_sprOffsetY = 0;
            int m_priority = 0;

        public:
	        /**
             * \brief Get the Animation name
             * \return A std::string containing the name of the Animation
             */
            std::string getAnimationName() const;
	        /**
             * \brief Get the default delay of the Animation.\n 
             *		  The delay will be transfered to AnimationGroup children if not specified.
             * \return The default delay of the Animation in milliseconds.
             */
            unsigned int getAnimationDelay() const;
	        /**
             * \brief Get AnimationGroup pointer by groupName.\n
             *		  It will throws a ObEngine.Animation.Animation.AnimationGroupNotFound if the AnimationGroup is not found.
             * \param groupName The name of the AnimationGroup to return
             * \return A pointer to the AnimationGroup
             */
            AnimationGroup* getAnimationGroup(const std::string& groupName);
	        /**
             * \brief Get the name of the current AnimationGroup
             * \return A std::string containing the name of the current AnimationGroup
             */
            std::string getCurrentAnimationGroup() const;
	        /**
             * \brief Get the name of all contained AnimationGroup of the Animation
             * \return A std::vector of std::string with all the names of the AnimationGroup
             */
            std::vector<std::string> getAllAnimationGroupName();
	        /**
             * \brief Get the Animation Play Mode
             * \return An enum value containing the AnimationPlayMode, it can be one of these modes :\n
             *		   - AnimationPlayMode::OneTime\n
             *		   - AnimationPlayMode::Loop\n
             *		   - AnimationPlayMode::Force\n
             */
            AnimationPlayMode getAnimationPlayMode() const;
	        /**
             * \brief Get the Animation Status
             * \return An enum value containing the AnimationStatus, it can be one of these modes ;\n
             *		   - AnimationStatus::Play\n
             *		   - AnimationStatus::Call\n
             */
            AnimationStatus getAnimationStatus() const;
	        /**
			 * \brief Get the name of the Animation to call when the AnimationStatus of the Animation is equal to AnimationStatus::Call
			 * \return A std::string containing the name of the Animation that will be called.
			 */
			std::string getCalledAnimation() const;
	        /**
             * \brief Configure an Animation using the Animation configuration file (Vili file)
             * \param path System::Path to the Animation config file (.ani.vili file extension)
             */
            void loadAnimation(const System::Path& path);
	        /**
             * \brief Apply global Animation parameters (Sprite offset and priority)
             * \param parameters A vili::ComplexAttribute that contains the following facultative parameters :\n
             *					 - spriteOffsetX : x Coordinate of the Sprite Offset in the Animation in pixels.\n
             *					 - spriteOffsetY : y Coordinate of the Sprite Offset in the Animation in pixels.\n
             *					 - priority : Priority of the Animation (A higher Animation priority can't be interrupted by an Animation with a lower one).
             */
            void applyParameters(vili::ComplexAttribute& parameters);
	        /**
             * \brief Updates the Animation (Updates the current AnimationGroup, executes the AnimationCode)
             */
            void update();
	        /**
             * \brief Resets the Animation (Unselect current AnimationGroup and restart AnimationCode)
             */
            void reset();
	        /**
             * \brief Get the Sprite containing the current texture in the Animation
             * \return A pointer to the currently displayed Sprite
             */
            sf::Sprite* getSprite();
	        /**
             * \brief Get the texture used in the Animation at the specified index
             * \param index Index of the texture to return.
             * \return A pointer to the sf::Texture at the given index
             */
            sf::Texture* getTextureAtIndex(int index);
	        /**
             * \brief Return whether the Animation is over or not
             * \return true if the Animation is over, false otherwise
             */
            bool isAnimationOver() const;
	        /**
             * \brief Get the x Coordinate of the Sprite Offset (0 if not defined)
             * \return an int containing the x Coordinate of the Sprite offset
             */
            int getSpriteOffsetX() const;
	        /**
             * \brief Get the y Coordinate of the Sprite Offset (0 if not defined)
             * \return an int containing the y Coordinate of the Sprite offset
             */
            int getSpriteOffsetY() const;
	        /**
             * \brief Returns the Animation priority
             * \return an int containing the priority of the Animation.\n
             *		   Higher int is higher priority = Can't be interrupted by lower priority.
             */
            int getPriority() const;
        };

	    /**
         * \brief A Class that will manage a set of Animation.\n
         * Example :
         * \code
         * using obe::Animation::Animator;
         * Animator animator;
         * animator.setPath("Path/To/Animator");
         * animator.loadAnimator();
         * for (std::string& animationName : animator.getAllAnimationName())
         *     std::cout << "Animator contains Animation : " << animationName << std::endl;
         * animator.setKey("Running");
         * while (True)
         * {
         *     animator.update();
         *     window.draw(*animator.getSprite());
         * }
         * \endcode
         * 
         * The root folder of an Animator is just a simple folder with multiple Animations folders inside. \n
         * Example : \n
         * "Path/To/Animator" : \n
         * - Walking/
         *	- walking_01.png
         *	- walking_02.png
         *	- Walking.ani.vili
         * - Running/
         *  - running_01.png
         *  - running_02.png
         *  - running_03.png
         *  - Running.ani.vili
         */
        class Animator
        {
        private:
            std::map<std::string, std::unique_ptr<Animation>> m_animationSet;
            Animation* m_currentAnimation = nullptr;
            std::string m_currentAnimationName = "NONE";
            System::Path m_animatorPath;
            sf::Sprite* m_lastSpritePointer = nullptr;
        public:
	        /**
             * \brief Animator Class default constructor
             */
            Animator();
	        /**
             * \brief Animator Class Path constructor (Equivalent to default constructor + Animation::setPath())
             * \param path Path to the Animator root
             */
            Animator(System::Path path);
	        /**
             * \brief Sets the path of the Animator root
             * \param path System::Path pointing to the Animator root
             */
            void setPath(System::Path path);
	        /**
             * \brief Sets the path of the Animator root
             * \param path std::string pointing to the Animator root (later converted to System::Path)
             */
            void setPath(std::string path);
	        /**
             * \brief Clears the Animator of all Animation
             * \param clearMemory Delete the contained Animation in memory
             */
            void clear(bool clearMemory = true);
	        /**
             * \brief Get the contained Animation pointer by Animation name
             * \param animationName Name of the Animation to get
             * \return A pointer to the wanted Animation.\n
             *		   Throws a ObEngine.Animation.Animator.AnimationNotFound if the Animation is not found
             */
            Animation* getAnimation(std::string animationName);
	        /**
             * \brief Get the name of all contained Animation
             * \return A std::vector of std::string containing the name of all contained Animation
             */
            std::vector<std::string> getAllAnimationName() const; 
	        /**
             * \brief Get the name of the currently played Animation
             * \return A std::string containing the name of the currently played Animation
             */
            std::string getKey() const;
	        /**
             * \brief Set the Animation to play by name
             * \param key A std::string containing the name of the Animation to play.\n
             *			  Throws a ObEngine.Animation.Animator.AnimationNotFound exception if the Animation key is not found.
             */
            void setKey(const std::string& key);
	        /**
             * \brief Loads the Animator (Using the Animator root path).\n
             *        It will also load all the Animation contained in the Animator.
             *        If an Animator configuration file is found it will load it.
             */
            void loadAnimator();
	        /**
             * \brief Updates the Animator and the currently played Animation
             */
            void update();
	        /**
             * \brief Get the current sf::Sprite of the current Animation
             * \return A pointer of the sf::Sprite currently played by the current Animation
             */
            sf::Sprite* getSprite();
	        /**
             * \brief Calls Animation::getTextureAtIndex
             * \param key Name of the Animation where the Texture is located
             * \param index Index of the Texture in the Animation
             * \return A pointer to the Texture
             */
            sf::Texture* getTextureAtKey(const std::string& key, int index);
	        /**
             * \brief Return if the Texture changed since the last call to getTexture()
             * \return true if the Texture has changed, false otherwise
             */
            bool textureChanged() const;
	        /**
             * \brief Get the x Coordinate of the current offset of the current Sprite
             * \return The x Coordinate of the current offset of the current Sprite (in pixels)
             */
            int getSpriteOffsetX() const;
			/**
			* \brief Get the y Coordinate of the current offset of the current Sprite
			* \return The y Coordinate of the current offset of the current Sprite (in pixels)
			*/
            int getSpriteOffsetY() const;
        };
    }
}