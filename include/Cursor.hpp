#pragma once

#include <SFML/Graphics.hpp>

#include "Animation.hpp"
#include "Triggers.hpp"

namespace obe
{
    namespace System
    {
        enum class CursorButton
        {
            Left,
            Right
        };

        class Cursor
        {
        private:
            int m_x = 0;
            int m_y = 0;
            int m_constrainedX = 0;
            int m_constrainedY = 0;
            sf::RenderWindow* m_window = nullptr;
            bool m_leftclicked = false;
            bool m_rightclicked = false;
            bool m_leftfirstclic = false;
            bool m_rightfirstclic = false;
            bool m_leftReleased = false;
            bool m_rightReleased = false;
            bool m_doesUpdateOutsideWindow = false;
            Script::TriggerGroup::Ptr m_cursorTriggers;
            Animation::Animator m_cursorAnim;
            sf::Sprite* m_cursorSprite = nullptr;
            std::function<std::pair<int, int>(Cursor*)> m_constraint;
            friend class CoreHook;
        public:
            Cursor(sf::RenderWindow* window);
            ~Cursor();
            void selectCursor(std::string cursor);
            void selectKey(std::string key);
            int getX() const;
            int getY() const;
            int getRawX() const;
            int getRawY() const;
            void setX(int newx);
            void setY(int newy);
            void setPosition(int newx, int newy);
            void update();
            void handleTriggers() const;
            void updateOutsideWindow(bool state);
            bool getPressed(CursorButton button) const;
            bool getClicked(CursorButton button) const;
            bool getReleased(CursorButton button) const;
            void setConstraint(std::function<std::pair<int, int>(Cursor*)> constraint);
            sf::Sprite* getSprite() const;
        };

        namespace Constraints
        {
            extern std::function<std::pair<int, int>(Cursor*)> Default;
        }
    }
}
