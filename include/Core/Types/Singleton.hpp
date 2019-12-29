#pragma once

#include <memory>

namespace obe::Types
{
    template <class T> class Singleton
    {
    private:
        static std::unique_ptr<T> m_instance;

    protected:
        Singleton();

    public:
        static T& GetInstance();
    };

    template <class T> std::unique_ptr<T> Singleton<T>::m_instance;
    template <class T> inline Singleton<T>::Singleton()
    {
    }
    template <class T> inline T& Singleton<T>::GetInstance()
    {
        if (!m_instance)
        {
            m_instance = std::make_unique<T>();
        }
        return *m_instance.get();
    }
}