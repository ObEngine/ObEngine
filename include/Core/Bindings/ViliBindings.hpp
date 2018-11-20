#pragma once

namespace kaguya { class State; }

/**
* \brief Bindings to Vili related classes and functions
*/
namespace obe::Bindings::ViliBindings
{
    void LoadViliDataType(kaguya::State* lua);
    void LoadViliNodeType(kaguya::State* lua);
    void LoadViliNode(kaguya::State* lua);
    void LoadViliContainerNode(kaguya::State* lua);
    void LoadViliDataNode(kaguya::State* lua);
    void LoadViliLinkNode(kaguya::State* lua);
    void LoadViliArrayNode(kaguya::State* lua);
    void LoadViliComplexNode(kaguya::State* lua);
    void LoadViliViliParser(kaguya::State* lua);
    void LoadViliNodeIterator(kaguya::State* lua);
    void LoadViliNodeTemplate(kaguya::State* lua);
    void LoadViliNodeConstraintManager(kaguya::State* lua);
    void LoadViliErrorHandler(kaguya::State* lua);
}