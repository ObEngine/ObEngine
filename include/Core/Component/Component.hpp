#pragma once

#define INJECTABLE void inject(unsigned int envIndex) override { Script::ScriptEngine["__ENVIRONMENTS"][envIndex]["Components"][m_id] = this; }

#include <memory>
#include <vector>

namespace obe
{
    namespace Component
    {
        class ComponentBase
        {
            virtual void inject(unsigned int envIndex) = 0;
        };

        template <class T>
        class Component : public ComponentBase
        {
        public:
            static std::vector<std::unique_ptr<T>> Pool;
            static T& create(const std::string& id);
            void inject(unsigned int envIndex) override = 0;
        };

        template<class T>
        inline T& Component<T>::create(const std::string& id)
        {
            return *Pool.emplace_back(std::make_unique<T>(id)).get();
        }
    }
}