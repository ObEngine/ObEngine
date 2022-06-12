#pragma once

#include <memory>
#include <optional>
#include <unordered_map>

#include <dynamicLinker/dynamicLinker.hpp>
#include <sol/sol.hpp>

#include <Types/Identifiable.hpp>

namespace obe::engine
{
    class Engine;
}

/**
 * \additionalinclude{Engine/Engine.hpp}
 */
namespace obe::System
{
    template <class T>
    using PluginFunction
        = std::optional<std::unique_ptr<dynamicLinker::dynamicLinker::dlSymbol<T>>>;
    /**
     * \nobind
     */
    template <class T>
    PluginFunction<T> getPluginFunction(
        std::shared_ptr<dynamicLinker::dynamicLinker> dl, const std::string& fnName);

    class Plugin : public Types::Identifiable
    {
    private:
        bool m_valid = false;
        std::shared_ptr<dynamicLinker::dynamicLinker> m_dl;

        PluginFunction<void(engine::Engine&)> m_onInitFn;
        PluginFunction<void(double)> m_onUpdateFn;
        PluginFunction<void()> m_onRenderFn;
        PluginFunction<void()> m_onExitFn;

    public:
        Plugin(const std::string& id, const std::string& path);
        void onInit(engine::Engine& engine) const;
        void onUpdate(double dt) const;
        void onRender() const;
        void onExit() const;
        [[nodiscard]] bool hasOnInit() const;
        [[nodiscard]] bool hasOnUpdate() const;
        [[nodiscard]] bool hasOnRender() const;
        [[nodiscard]] bool hasOnExit() const;
        [[nodiscard]] bool isValid() const;
    };

    template <class T>
    PluginFunction<T> getPluginFunction(
        std::shared_ptr<dynamicLinker::dynamicLinker> dl, const std::string& fnName)
    {
        return std::move(std::make_unique<dynamicLinker::dynamicLinker::dlSymbol<T>>(
            dl->getFunction<T>(fnName)));
    }
} // namespace obe::System
