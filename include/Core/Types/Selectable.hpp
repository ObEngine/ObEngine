#pragma once

namespace obe::Types
{
    /**
     * \brief A Base Class that you can select or unselect
     */
    class Selectable
    {
    protected:
        bool m_selected;

    public:
        /**
         * \brief Constructor of Selectable Class
         * \param selected Default state of m_selected
         */
        explicit Selectable(bool selected = false);
        /**
         * \brief Set the state of the Selectable
         * \param selected A boolean to set the state of the Selectable (true / false)
         */
        void set_selected(bool selected);
        /**
         * \brief Selectable becomes unselected if it was selected and selected if it was not
         */
        void toggle_selected();
        /**
         * \brief Selects the Selectable
         */
        void select();
        /**
         * \brief Unselect the Selectable
         */
        void unselect();
        /**
         * \brief Get if the Selectable is selected or not
         * \return true if selected, false otherwise
         */
        [[nodiscard]] bool is_selected() const;
    };
} // namespace obe::Types
