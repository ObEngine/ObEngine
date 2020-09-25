#include <Event/EventListener.hpp>

namespace obe::Event
{
    EventListener::EventListener(std::string id)
        : m_id(std::move(id))
    {
    }

    const std::string& EventListener::getId() const
    {
        return m_id;
    }

    CppEventListener::CppEventListener(std::string id, CppCallback callback)
        : EventListener(std::move(id))
        , m_callback(std::move(callback))
    {
    }

    void CppEventListener::operator()(const EventData& event)
    {
        m_callback(event);
    }

    LuaEventListener::LuaEventListener(std::string id, sol::protected_function callback)
        : EventListener(std::move(id))
        , m_callback(std::move(callback))
    {
    }

    void LuaEventListener::operator()(const EventData& event)
    {
        m_callback(event);
    }
}
