#pragma once

#include <any>
#include <array>
#include <iostream>
#include <memory>
#include <unordered_map>

#include <Types/Identifiable.hpp>
#include <Config.hpp>

namespace obe::Types
{
    namespace Globals
    {
        constexpr size_t MaxGlobals = 3;
        using GlobalMap = std::array<void*, MaxGlobals>;
        inline GlobalMap Index;
        void Synchronize(Globals::GlobalMap* OtherIndex);
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
        T* GLOBE_SYM _ref;
    public:
        Types::TypeStorage<T, id> TagType;
        Global(T* GLOBE_SYM ref);
        operator T&();
        T& get();
        void reset(T* ptr);
        T* operator->();
        T* ptr();
    };

    template <unsigned short id>
    Global <id, decltype(TypeDecl(tag<id>{}))>& GetGlobal();

    template <unsigned short id>
    Global <id, decltype(TypeDecl(tag<id>{}))>& GetGlobal(Globals::GlobalMap* OtherGlobals);

    

    template <unsigned short id, class T>
    Global<id, T>::Global(T* GLOBE_SYM ref)
    {
        std::cout << "Creating Global " << id << " with ptr " << ref << std::endl;
        _ref = ref;
        std::cout << "Creating global on " << static_cast<void*>(this) << " underlying " << static_cast<void*>(_ref) << std::endl;
        Globals::Index[id] = this;
    }

    template <unsigned short id, class T>
    Global<id, T>::operator T&()
    {
        std::cout << "Casting value on " << static_cast<void*>(this) << " underlying " << static_cast<void*>(_ref) << std::endl;
        return this->get();
    }

    template <unsigned short id, class T>
    T& Global<id, T>::get()
    {
        std::cout << "Getting value on " << static_cast<void*>(this) << " underlying " << static_cast<void*>(_ref) << std::endl;
        return *ptr();
    }

    template <unsigned short id, class T>
    void Global<id, T>::reset(T* ptr)
    {
        std::cout << "Resetting value on " << static_cast<void*>(this) << " underlying " << static_cast<void*>(_ref) << std::endl;
        std::cout << "RESET VALUE FROM " << _ref << " TO " << ptr << std::endl;
        GLOBE_SYM _ref = ptr;
    }

    template <unsigned short id, class T>
    T* Global<id, T>::operator->()
    {
        std::cout << "Accessing operator-> value on " << static_cast<void*>(this) << " underlying " << static_cast<void*>(_ref) << std::endl;
        std::cout << "Access operator -> underlying value : " << _ref << std::endl;
        return this->ptr();
    }

    template <unsigned short id, class T>
    T* Global<id, T>::ptr()
    {
        std::cout << "Accessing ptr on " << static_cast<void*>(this) << " underlying " << static_cast<void*>(_ref) << std::endl;
        return GLOBE_SYM _ref; // Problem here
    }

    template <unsigned short id>
    Global<id, decltype(TypeDecl(tag<id>{}))>& GetGlobal()
    {
        return *static_cast<Global<id, decltype(TypeDecl(tag<id>{}))>*>(Globals::Index[id]);
    }

    template <unsigned short id>
    Global<id, decltype(TypeDecl(tag<id>{}))>& GetGlobal(Globals::GlobalMap* OtherGlobals)
    {
        std::cout << "Size of remote : " << OtherGlobals->size() << std::endl;
        return *static_cast<Global<id, decltype(TypeDecl(tag<id>{}))>*>(OtherGlobals->at(id));
    }

    namespace Globals
    {
        template <unsigned short I> struct int_ {};

        template <unsigned short I, unsigned short N>
        struct Loop {
            template <class F>
            static void run(F f) {
                f(int_<I>()); // pass an templated struct to the eval method
                std::cout << "Synchronizing index " << I << std::endl;
                Loop<I + 1, N>::run(f);
            }
        };

        template <unsigned short N>
        struct Loop<N, N> { template <class F> static void run(F) {} };
    }
}
