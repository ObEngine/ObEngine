#pragma once

namespace obe::Types
{
    /**
     * \brief A Base Class that you can enable or disable
     */
    class Togglable
    {
    private:
        void change_state(bool state);

    protected:
        bool m_enabled;
        virtual void on_state_change();

    public:
        /**
         * \brief Constructor of Togglable Class
         * \param enabled Default state of m_enabled
         */
        explicit Togglable(bool enabled);
        /**
         * \brief Set the state of the Togglable
         * \param state A boolean to set the state of the Togglable (true /
         * false)
         */
        void set_enabled(bool state);
        /**
         * \brief Togglable disables if it was enabled and enables if it wasn't
         */
        void toggle();
        /**
         * \brief Enable the Togglable
         */
        void enable();
        /**
         * \brief Disable the Togglable
         */
        void disable();
        /**
         * \brief Get if the Togglable is enabled or not
         * \return true if enabled, false otherwise
         */
        [[nodiscard]] bool is_enabled() const;
    };
} // namespace obe::Types
