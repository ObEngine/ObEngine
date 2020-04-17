#include <Exception.hpp>
#include <vector>

namespace obe::Audio::Exceptions
{
    class AudioFileNotFound : public Exception
    {
    public:
        AudioFileNotFound(
            std::string_view path, std::vector<std::string> mountedPaths, DebugInfo info)
            : Exception("AudioFileNotFound", info)
        {
            this->error(
                "Impossible to find audio file at the following path : '{}'", path);
            this->hint("The file was supposed to be in one of the following paths : ({})",
                fmt::join(mountedPaths, ", "));
        }
    };
}
