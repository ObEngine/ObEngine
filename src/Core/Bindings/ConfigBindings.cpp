#include <Bindings/ConfigBindings.hpp>
#include <Config/Git.hpp>

#include <kaguya/kaguya.hpp>

namespace obe::Bindings::ConfigBindings
{
    void LoadGit(kaguya::State* lua)
    {
        (*lua)["obe"]["version"] = std::string(Config::OBENGINE_VERSION);
        (*lua)["obe"]["commit"] = std::string(Config::OBENGINE_GIT_HASH);
        (*lua)["obe"]["branch"] = std::string(Config::OBENGINE_GIT_BRANCH);
    }
}