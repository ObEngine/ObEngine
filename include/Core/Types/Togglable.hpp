#pragma once

namespace obe::Types
{
    /**
     * \brief A Base Class that you can enable or disable
     */
    class Togglable
    {
    private:
        void changeState(bool state);

    protected:
        bool m_enabled;
        virtual void onStateChange();

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
        void setEnabled(bool state);
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
        [[nodiscard]] bool isEnabled() const;
    };
} // namespace obe::Types