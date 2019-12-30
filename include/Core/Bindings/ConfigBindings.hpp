#pragma once

namespace kaguya
{
    class State;
}

namespace obe::Bindings::ConfigBindings
{
    void LoadGit(kaguya::State* lua);
}