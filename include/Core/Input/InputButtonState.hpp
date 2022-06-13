#pragma once

#include <Types/SmartEnum.hpp>

namespace obe::input
{
    /**
     * \brief Possible states of InputButton
     */
    enum class InputButtonState
    {
        /**
         * \brief InputButton is not pressed
         */
        Idle,
        /**
         * \brief InputButton is being hold
         */
        Hold,
        /**
         * \brief InputButton is just being pressed
         */
        Pressed,
        /**
         * \brief InputButton is just being released
         */
        Released,
        LAST__
    };

    using InputButtonStateMeta = Types::SmartEnum<InputButtonState>;
} // namespace obe::input
