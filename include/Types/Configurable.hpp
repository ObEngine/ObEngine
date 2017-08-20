#pragma once

namespace vili 
{
    class ComplexNode;
}

namespace obe
{
    namespace Types
    {
        class Configurable
        {
        public:
            virtual void configure(vili::ComplexNode& configuration) = 0;
        };
    }
}
