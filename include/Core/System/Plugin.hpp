#pragma once

#include <memory>
#include <unordered_map>

#include <dynamicLinker/dynamicLinker.hpp>
#include <kaguya/kaguya.hpp>

#include <Types/Identifiable.hpp>

namespace obe::System
{
    void IndexPlugins();

    template <class T>
    using PluginFunction
        = std::unique_ptr<dynamicLinker::dynamicLinker::dlSymbol<T>>;
    template <class T>
    PluginFunction<T> getPluginFunction(
        std::shared_ptr<dynamicLinker::dynamicLinker> dl,
        const std::string& fnName);

    class Plugin : public Types::Identifiable
    {
    private:
        std::shared_ptr<dynamicLinker::dynamicLinker> m_dl;
        bool m_hasOnInitFn;
        PluginFunction<void()> m_onInitFn;
        bool m_hasOnLoadBindingsFn;
        PluginFunction<void(kaguya::State*)> m_onLoadBindingsFn;
        bool m_hasOnUpdateFn;
        PluginFunction<void(double)> m_onUpdateFn;
        bool m_hasOnRenderFn;
        PluginFunction<void()> m_onRenderFn;
        bool m_hasOnExitFn;
        PluginFunction<void()> m_onExitFn;

    public:
        Plugin(const std::string& id, const std::string& path);
        void onLoadBindings(kaguya::State* lua) const;
        void onUpdate(double dt) const;
        void onRender() const;
        void onExit() const;
        bool hasOnInit() const;
        bool hasOnLoadBindings() const;
        bool hasOnUpdate() const;
        bool hasOnRender() const;
        bool hasOnExit() const;
    };

    extern std::vector<std::unique_ptr<Plugin>> Plugins;

    template <class T>
    PluginFunction<T> getPluginFunction(
        std::shared_ptr<dynamicLinker::dynamicLinker> dl,
        const std::string& fnName)
    {
        return std::move(
            std::make_unique<dynamicLinker::dynamicLinker::dlSymbol<T>>(
                dl->getFunction<T>(fnName)));
    }
} // namespace obe::System
