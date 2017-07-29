#pragma once

#include <kaguya/kaguya.hpp>

#include <Types/Any.hpp>
#include <Utils/TypeUtils.hpp>

namespace obe
{
    namespace Script
    {
        void loadHook(kaguya::State* lua, std::string hookname);

        class CoreHook
        {
        private:
            std::map<std::string, std::pair<std::string, Types::Any*>> containerMap;
        public:
            template <typename T>
            void dropValue(std::string name, T val);
            void getValue(kaguya::State* lua, std::string name);
            Types::Any* getPointer(std::string name);
        };

        template <typename T>
        void CoreHook::dropValue(std::string name, T val)
        {
            containerMap[name] = std::pair<std::string, Types::Any*>(Utils::Type::getObjectType(val), new Types::Any(val));
        }

        extern CoreHook hookCore;
    }
}
