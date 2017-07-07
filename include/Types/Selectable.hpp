#pragma once

namespace obe
{
    namespace Types
    {
        class Selectable
        {
        protected:
            bool m_selected;
        public:
            Selectable(bool selected);
            void setSelected(bool selected);
            void toggleSelected();
            void select();
            void unselect();
            bool isSelected() const;
        };
    }
}
