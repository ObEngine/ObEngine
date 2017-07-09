#include <Sound/Music.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>

namespace obe
{
    namespace Sound
    {
        MusicWrapper::MusicWrapper()
        {
        }

        MusicWrapper::MusicWrapper(const std::string& filename)
        {
            this->load(filename);
        }

        void MusicWrapper::load(const std::string& filename)
        {
            System::Path(filename).loadResource(static_cast<sf::Music*>(this), System::Loaders::musicLoader);
        }
    }
}