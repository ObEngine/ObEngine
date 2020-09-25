#include <functional>
#include <string>

#include <sol/sol.hpp>

namespace obe::Event
{
    class EventData;

    class EventListener
    {
    private:
        std::string m_id;

    public:
        EventListener(std::string id);

        const std::string& getId() const;
        virtual void operator()(const EventData& event) = 0;
    };

    using CppCallback = std::function<void(const EventData&)>;
    class CppEventListener : public EventListener
    {
    private:
        CppCallback m_callback;

    public:
        CppEventListener(std::string id, CppCallback callback);

        void operator()(const EventData& event) override;
    };

    class LuaEventListener : public EventListener
    {
    private:
        sol::protected_function m_callback;

    public:
        LuaEventListener(std::string id, sol::protected_function callback);

        void operator()(const EventData& event) override;
    };
}