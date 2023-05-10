#include <limits>

#include <Types/UniqueIdentifiable.hpp>
#include <Utils/MathUtils.hpp>

namespace obe::types
{
    constexpr std::string_view BASE58_ALPHABET
        = "123456789abcdefghijkmnopqrstuvwxyzABCDEFGHJKLMNPQRSTUVWXYZ";
    // uint64_t::max / 42 still makes 11 chars identifiers
    constexpr uint64_t RANDOM_U64_LOWER_BOUND = std::numeric_limits<uint64_t>::max() / 42;
    constexpr uint64_t RANDOM_U64_UPPER_BOUND = std::numeric_limits<uint64_t>::max();

    UniqueIdentifiable::UniqueIdentifiable()
    {
        size_t char_index = 0;

        uint64_t random_number
            = utils::math::randint(RANDOM_U64_LOWER_BOUND, RANDOM_U64_UPPER_BOUND);
        std::array<char, 24> output = {};

        while (random_number > 0)
        {

            const uint64_t num = random_number / 58;
            const uint64_t remainder = random_number % 58;

            output[char_index++] = BASE58_ALPHABET[remainder];

            random_number = num;
        }

        m_uuid = std::string(output.begin(), output.begin() + char_index);
    }

    UniqueIdentifiable::UniqueIdentifiable(UniqueIdentifiable&& other) noexcept
        : m_uuid(std::move(other.m_uuid))
    {
    }

    std::string UniqueIdentifiable::get_unique_id() const
    {
        return m_uuid;
    }
} // namespace obe::types
