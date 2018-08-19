#pragma once

#include <any>
#include <memory>
#include <unordered_map>

#include <Types/Identifiable.hpp>

namespace obe::Types
{
    namespace Globals
    {
        using GlobalMap = std::unordered_map<unsigned short, void*>;
        static GlobalMap Index;

        inline void Synchronize(const GlobalMap& OtherIndex)
        {

        }
    }

    template<int N> struct tag {};

    template<typename T, int N>
    class TypeStorage
    {
        friend auto TypeDecl(tag<N>) { return T{}; }
    };
    
    template <unsigned short id, class T>
    class Global
    {
    private:
        std::unique_ptr<T> _underlying;
    public:
        Types::TypeStorage<T, id> TagType;
        template <class... Args>
        Global(Args... args);
        operator T&();
        T& get();
    };

    template <unsigned short id>
    Global <id, decltype(TypeDecl(tag<id>{}))>& GetGlobal();

    template <unsigned short id, class T>
    template <class ... Args>
    ::obe::Types::Global<id, T>::Global(Args... args)
    {
        
        _underlying = std::make_unique<T>(std::forward<Args>(args)...);
        Globals::Index[id] = this;
    }

    template <unsigned short id, class T>
    Global<id, T>::operator T&()
    {
        return *_underlying.get();
    }

    template <unsigned short id, class T>
    T& Global<id, T>::get()
    {
        return *_underlying.get();
    }

    template <unsigned short id>
    Global<id, decltype(TypeDecl(tag<id>{}))>& GetGlobal()
    {
        return *static_cast<Global<id, decltype(TypeDecl(tag<id>{}))>*>(Globals::Index[id]);
    }
}
