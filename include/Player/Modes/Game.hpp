#pragma once

namespace obe::modes
{
    /**
     * \brief Start the game by loading the boot.lua file in one of the
     * MountedPaths
     */
    void start_game(const vili::node& arguments);
} // namespace obe::modes