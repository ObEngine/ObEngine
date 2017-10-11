#pragma once

namespace vili 
{
    class ComplexNode;
}

namespace obe
{
    namespace Types
    {
        /**
         * \brief Abstract class that forces to implement a method to configure an object with a Vili ComplexNode
         */
        class Configurable
        {
        public:
            /**
             * \brief Configures the object with a Vili ComplexNode
             * \param configuration The ComplexNode that contains the configuration for the object
             */
            virtual void configure(vili::ComplexNode& configuration) = 0;
        };
    }
}
