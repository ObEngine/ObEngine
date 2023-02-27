#include <fmt/format.h>

#include <Exception.hpp>
#include <vector>

/**
 * \nobind
 */
namespace obe::audio::exceptions
{
    class AudioFileNotFound : public Exception<AudioFileNotFound>
    {
    public:
        using Exception::Exception;
        AudioFileNotFound(std::string_view path, std::vector<std::string> mounted_paths,
            std::source_location location = std::source_location::current())
            : Exception(location)
        {
            this->error("Impossible to find audio file at the following path : '{}'", path);
            this->hint("The file was supposed to be in one of the following paths : ({})",
                fmt::join(mounted_paths, ", "));
        }
    };
} // namespace obe::audio::exceptions
