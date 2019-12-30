#pragma once

namespace obe::Types
{
    /**
     * \brief A Base Class that you can select or unselect
     * @Bind
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
         * \param selected A boolean to set the state of the Selectable (true /
         * false)
         */
        void setSelected(bool selected);
        /**
         * \brief Selectable unselects if it was selected and selects if it
         * wasn't
         */
        void toggleSelected();
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
        bool isSelected() const;
    };
} // namespace obe::Types