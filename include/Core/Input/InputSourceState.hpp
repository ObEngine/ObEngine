#pragma once

#include <Types/SmartEnum.hpp>

namespace obe::input
{
    /**
     * \brief Possible states of InputSource
     */
    enum class InputSourceState
    {
        /**
         * \brief InputSource is not pressed
         */
        Idle,
        /**
         * \brief InputSource is being hold
         */
        Hold,
        /**
         * \brief InputSource is just being pressed
         */
        Pressed,
        /**
         * \brief InputSource is just being released
         */
        Released,
    };

    using InputButtonStateMeta = types::SmartEnum<InputSourceState>;
} // namespace obe::input
