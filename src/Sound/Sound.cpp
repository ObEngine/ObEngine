#include <Sound/Sound.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>

namespace obe
{
    namespace Sound
    {
        std::map<std::string, sf::SoundBuffer> SoundWrapper::SoundBank = std::map<std::string, sf::SoundBuffer>();

        SoundWrapper::SoundWrapper()
        {
        }

        SoundWrapper::SoundWrapper(const std::string& filename)
        {
            this->load(filename);
        }

        void SoundWrapper::load(const std::string& filename)
        {
            if (SoundBank.find(filename) == SoundBank.end())
            {
                sf::SoundBuffer loadSound;
                System::Path(filename).loadResource(&loadSound, System::Loaders::soundLoader);
                SoundBank[filename] = loadSound;
            }
            this->setBuffer(SoundBank[filename]);
        }
    }
}
