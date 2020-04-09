#include <exception>
#include <optional>
#include <string>

#include <fmt/format.h>

namespace obe
{
    class Exception : std::exception
    {
    private:
        std::string m_id;
        std::string m_error;
        std::optional<std::string> m_hint;

    public:
        Exception(std::string id)
            : m_id(std::move(id))
        {
        }
        template <class... Args> void error(Args&&... args)
        {
            m_error = fmt::format(std::forward<Args>(args)...);
        }
        template <class... Args> void hint(Args&&... args)
        {
            m_hint = fmt::format(std::forward<Args>(args)...);
        }
        const char* what() const override;
    };

    inline const char* Exception::what() const
    {
        std::string message = fmt::format("[{}] {}", m_id, m_error);
        if (m_hint)
            message += ("\n" + m_hint.value());
        return message.c_str();
    }
}
