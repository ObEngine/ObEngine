#pragma once

#include <map>
#include <vector>

#include <Animation/Animation.hpp>
#include <System/Path.hpp>

namespace obe
{
	/**
     * \brief Various Animation Classes
     */
    namespace Animation
    {
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
            sf::Texture* m_lastTexturePointer = nullptr;
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
            void setPath(const std::string& path);
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
            Animation* getAnimation(const std::string& animationName) const;
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
            const sf::Texture& getTexture();
	        /**
             * \brief Calls Animation::getTextureAtIndex
             * \param key Name of the Animation where the Texture is located
             * \param index Index of the Texture in the Animation
             * \return A pointer to the Texture
             */
            const sf::Texture& getTextureAtKey(const std::string& key, int index) const ;
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