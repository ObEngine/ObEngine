#pragma once

#include <kaguya/kaguya.hpp>

#include <Types/Any.hpp>
#include <Utils/TypeUtils.hpp>

namespace obe
{
    namespace Script
    {
        void loadLib(kaguya::State* lua, std::string lib);
        void loadHook(kaguya::State* lua, std::string hookname);
        void loadCoreLib(kaguya::State* lua, std::vector<std::string> lib, bool alreadyImportedWarning = true);
        void registerLib(kaguya::State* lua, std::string lib);
        void loadBaseLib(kaguya::State* lua);
        bool checkIfAlreadyImported(kaguya::State* lua, std::string lib);

        namespace CoreLib
        {
            void loadAnimation(kaguya::State* lua, std::vector<std::string> args);
            void loadCamera(kaguya::State* lua, std::vector<std::string> args);
            void loadCanvas(kaguya::State* lua, std::vector<std::string> args);
            void loadCollision(kaguya::State* lua, std::vector<std::string> args);
            void loadConsole(kaguya::State* lua, std::vector<std::string> args);
            void loadConstants(kaguya::State* lua, std::vector<std::string> args);
            void loadCoordinates(kaguya::State* lua, std::vector<std::string> args);
            void loadCursor(kaguya::State* lua, std::vector<std::string> args);
            void loadFilesystem(kaguya::State* lua, std::vector<std::string> args);
            void loadKeyBind(kaguya::State* lua, std::vector<std::string> args);
            void loadLevelSprite(kaguya::State* lua, std::vector<std::string> args);
            void loadPackage(kaguya::State* lua, std::vector<std::string> args);
            void loadPath(kaguya::State* lua, std::vector<std::string> args);
            void loadSelectable(kaguya::State* lua, std::vector<std::string> args);
            void loadSFML(kaguya::State* lua, std::vector<std::string> args);
            void loadSound(kaguya::State* lua, std::vector<std::string> args);
            void loadSTD(kaguya::State* lua, std::vector<std::string> args);
            void loadTrigger(kaguya::State* lua, std::vector<std::string> args);
            void loadUtils(kaguya::State* lua, std::vector<std::string> args);
            void loadVili(kaguya::State* lua, std::vector<std::string> args);
        }

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
