#pragma once

#include <Input/InputButtonMonitor.hpp>
#include <Input/InputSourceState.hpp>
#include <Input/InputSource.hpp>
#include <Types/FlagSet.hpp>
#include <Types/Togglable.hpp>
#include <vector>

namespace obe::input
{
    using InputCombinationElement = std::pair<InputSource*, types::FlagSet<InputSourceState>>;
    using InputCombination = std::vector<InputCombinationElement>;

    /**
     * \brief A class represented the required conditions to trigger an
     *        InputAction
     */
    class InputCondition
    {
    private:
        InputCombination m_combination;
        std::vector<InputButtonMonitorPtr> m_monitors;
        bool m_enabled = false;

    protected:
        [[nodiscard]] InputSourceState get_button_state(InputSource* input_source) const;

    public:
        InputCondition() = default;
        /**
         * \brief Adds a new InputCombinationElement to the InputCondition
         * \param combination_element The InputCombinationElement to add to the
         *        InputCondition
         */
        void add_combination_element(InputCombinationElement combination_element);
        /**
         * \brief Checks if the condition is fulfilled
         * \return true if the InputCondition is fulfilled, false otherwise
         */
        [[nodiscard]] bool check() const;
        /**
         * \brief Clears the InputCondition
         */
        void clear();
        /**
         * \nobind
         * \brief Gets the InputCombination used by the InputCondition
         * \return The InputCombination used by the InputCondition
         */
        [[nodiscard]] InputCombination get_combination() const;
        /**
         * TODO: Fix this nobind
         * \nobind
         * \brief Sets the new required InputCombination to trigger the
         *        InputCondition
         * \param combination The new InputCombination
         */
        void set_combination(const InputCombination& combination);

        void enable(const std::vector<InputButtonMonitorPtr>& monitors);
        void disable();
        [[nodiscard]] bool is_enabled() const;
    };
} // namespace obe::input
