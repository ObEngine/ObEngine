#pragma once

namespace obe::Types
{
    /**
     * \brief A Base Class that represents a tweenable object
     */
    template <size_t ComponentAmount>
    class Tweenable
    {
    public:
        virtual ~Tweenable() = default;

        using NumericalComponents = std::array<double, ComponentAmount>;
        /**
         * \brief Set the numerical components of the tweenable object
         * \param components Array containing the numerical components
         */
        virtual void setNumericalComponents(const NumericalComponents& components) = 0;

        /**
         * \brief Get the numerical components of the tweenable object
         */
        virtual NumericalComponents getNumericalComponents() = 0;
    };
} // namespace obe::Types