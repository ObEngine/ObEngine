#include <Animation/Animator.hpp>
#include <System/Loaders.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe
{
    namespace Animation
    {
        Animator::Animator()
        {
        }

        Animator::Animator(System::Path path)
        {
            m_animatorPath = path;
        }

        void Animator::setPath(System::Path path)
        {
            m_animatorPath = path;
        }

        void Animator::setPath(const std::string& path)
        {
            m_animatorPath = System::Path(path);
        }

        void Animator::clear(bool clearMemory)
        {
            Debug::Log->trace("<Animator> Clearing Animator at {0}", m_animatorPath.toString());
            m_animationSet.clear();
            m_currentAnimation = nullptr;
            m_currentAnimationName = "NONE";
            m_animatorPath = System::Path("");
            m_lastTexturePointer = nullptr;
        }

        Animation* Animator::getAnimation(const std::string& animationName) const
        {
            if (m_animationSet.find(animationName) != m_animationSet.end())
                return m_animationSet.at(animationName).get();
            throw aube::ErrorHandler::Raise("ObEngine.Animation.Animator.AnimationNotFound",
                {{"function", "getAnimation"}, {"animation", animationName}, {"%animator", m_animatorPath.toString()}
            });
        }

        std::vector<std::string> Animator::getAllAnimationName() const
        {
            std::vector<std::string> allAnimationsNames;
            for (auto& animationPair : m_animationSet)
                allAnimationsNames.push_back(animationPair.first);
            return allAnimationsNames;
        }

        std::string Animator::getKey() const
        {
            return m_currentAnimationName;
        }

        void Animator::setKey(const std::string& key)
        {
            Debug::Log->trace("<Animator> Set Animation Key {0} for Animator at {1}", key, m_animatorPath.toString());
            if (m_animationSet.find(key) == m_animationSet.end())
            {
                throw aube::ErrorHandler::Raise("ObEngine.Animation.Animator.AnimationNotFound", {
                    {"function", "setKey"},{"animation", key},{"%animator", m_animatorPath.toString()}
                });
            }

            if (key != m_currentAnimationName)
            {
                bool changeAnim = false;
                if (m_currentAnimation != nullptr)
                {
                    if (m_currentAnimation->isAnimationOver())
                        changeAnim = true;
                    else if (m_animationSet[key]->getPriority() >= m_currentAnimation->getPriority())
                        changeAnim = true;
                }
                else
                    changeAnim = true;
                if (changeAnim)
                {
                    if (m_currentAnimationName != "NONE")
                        m_animationSet[m_currentAnimationName]->reset();
                    m_currentAnimationName = key;
                    m_currentAnimation = m_animationSet[m_currentAnimationName].get();
                }
            }
        }

        void Animator::setPaused(bool pause)
        {
            m_paused = pause;
        }

        void Animator::loadAnimator()
        {
            Debug::Log->trace("<Animator> Loading Animator at {0}", m_animatorPath.toString());
            std::vector<std::string> listDir;
            m_animatorPath.loadResource(&listDir, System::Loaders::dirPathLoader);
            std::vector<std::string> allFiles;
            m_animatorPath.loadResource(&allFiles, System::Loaders::filePathLoader);
            vili::ViliParser animatorCfgFile;
            std::map<std::string, vili::ComplexNode*> animationParameters;
            if (Utils::Vector::isInList(std::string("animator.cfg.vili"), allFiles))
            {
                System::Path(m_animatorPath.toString() + "/" + "animator.cfg.vili").loadResource(&animatorCfgFile, System::Loaders::dataLoader);
                for (vili::ComplexNode* currentAnim : animatorCfgFile.at("Animator").getAll<vili::ComplexNode>())
                    animationParameters[currentAnim->getId()] = &animatorCfgFile.at("Animator", currentAnim->getId());
            }
            for (unsigned int i = 0; i < listDir.size(); i++)
            {
                std::unique_ptr<Animation> tempAnim = std::make_unique<Animation>();
                tempAnim->loadAnimation(m_animatorPath.add(listDir[i]));
                if (animationParameters.find(listDir[i]) != animationParameters.end() && animationParameters.find("all") != animationParameters.end())
                {
                    tempAnim->applyParameters(*animationParameters["all"]);
                    tempAnim->applyParameters(*animationParameters[listDir[i]]);
                }
                else if (animationParameters.find(listDir[i]) != animationParameters.end())
                    tempAnim->applyParameters(*animationParameters[listDir[i]]);
                else if (animationParameters.find("all") != animationParameters.end())
                    tempAnim->applyParameters(*animationParameters["all"]);
                m_animationSet[tempAnim->getAnimationName()] = move(tempAnim);
            }
        }

        void Animator::update()
        {
            if (!m_paused)
            {
                Debug::Log->trace("<Animator> Updating Animator at {0}", m_animatorPath.toString());
                if (m_currentAnimation == nullptr)
                    throw aube::ErrorHandler::Raise("ObEngine.Animator.Animator.UpdateNullAnimation", { { "animator", m_animatorPath.toString() } });
                if (m_currentAnimation->getAnimationStatus() == AnimationStatus::Call)
                {
                    m_currentAnimation->reset();
                    m_currentAnimationName = m_currentAnimation->getCalledAnimation();
                    m_currentAnimation = m_animationSet[m_currentAnimationName].get();
                }
                if (m_currentAnimation->getAnimationStatus() == AnimationStatus::Play)
                    m_currentAnimation->update();
            }
        }

        const sf::Texture& Animator::getTexture()
        {
            m_lastTexturePointer = &const_cast<sf::Texture&>(m_currentAnimation->getTexture());
            return m_currentAnimation->getTexture();
        }

        const sf::Texture& Animator::getTextureAtKey(const std::string& key, int index) const
        {
            return this->getAnimation(key)->getTextureAtIndex(index);
        }

        bool Animator::textureChanged() const
        {
            return (&m_currentAnimation->getTexture() != m_lastTexturePointer);
        }

        int Animator::getSpriteOffsetX() const
        {
            return m_currentAnimation->getSpriteOffsetX();
        }

        int Animator::getSpriteOffsetY() const
        {
            return m_currentAnimation->getSpriteOffsetY();
        }
    }
}
