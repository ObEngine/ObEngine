#include <Exception.hpp>
#include <vector>

#include <fmt/format.h>

namespace obe::audio::exceptions
{
    class AudioFileNotFound : public Exception<AudioFileNotFound>
    {
    public:
        using Exception::Exception;
        AudioFileNotFound(
            std::string_view path, std::vector<std::string> mounted_paths, DebugInfo info)
            : Exception(info)
        {
            this->error("Impossible to find audio file at the following path : '{}'", path);
            this->hint("The file was supposed to be in one of the following paths : ({})",
                fmt::join(mounted_paths, ", "));
        }
    };
}
