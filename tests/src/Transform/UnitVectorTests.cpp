#include <catch/catch.hpp>

#include <Transform/Vector2.hpp>

using namespace obe::transform;

TEST_CASE("Testing value unpack of Vector2", "[obe.Transform.Vector2.unpack]")
{
    SECTION("Simple case")
    {
        const Vector2 test(12, 23);
        auto [x, y] = test.unpack();
        REQUIRE(x == 12);
        REQUIRE(y == 23);
    }
}