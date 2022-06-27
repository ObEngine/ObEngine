#pragma once

#include <memory>
#include <optional>

#include <dynamicLinker/dynamicLinker.hpp>

#include <Types/Identifiable.hpp>

namespace obe::engine
{
    class Engine;
}

/**
 * \additionalinclude{Engine/Engine.hpp}
 */
namespace obe::system
{
    template <class T>
    using PluginFunction
        = std::optional<std::unique_ptr<dynamicLinker::dynamicLinker::dlSymbol<T>>>;
    /**
     * \nobind
     */
    template <class T>
    PluginFunction<T> get_plugin_function(
        std::shared_ptr<dynamicLinker::dynamicLinker> dl, const std::string& function_name);

    class Plugin : public types::Identifiable
    {
    private:
        bool m_valid = false;
        std::shared_ptr<dynamicLinker::dynamicLinker> m_dl;

        PluginFunction<void(engine::Engine&)> m_on_init_fn;
        PluginFunction<void(engine::Engine&)> m_on_exit_fn;

    public:
        Plugin(const std::string& id, const std::string& path);
        void on_init(engine::Engine& engine) const;
        void on_exit(engine::Engine& engine) const;
        [[nodiscard]] bool has_on_init() const;
        [[nodiscard]] bool has_on_exit() const;
        [[nodiscard]] bool is_valid() const;
    };

    template <class T>
    PluginFunction<T> get_plugin_function(
        std::shared_ptr<dynamicLinker::dynamicLinker> dl, const std::string& function_name)
    {
        return std::move(std::make_unique<dynamicLinker::dynamicLinker::dlSymbol<T>>(
            dl->getFunction<T>(function_name)));
    }
} // namespace obe::system
