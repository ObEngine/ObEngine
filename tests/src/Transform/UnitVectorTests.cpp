#include <catch/catch.hpp>

#include <Transform/UnitVector.hpp>

using namespace obe::Transform;

TEST_CASE(
    "Testing value unpack of UnitVectors", "[obe.Transform.UnitVector.unpack]")
{
    SECTION("Simple case")
    {
        UnitVector test(12, 23);
        auto [x, y] = test.unpack();
        REQUIRE(x == 12);
        REQUIRE(y == 23);
    }
}