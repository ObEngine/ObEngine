#include <catch/catch.hpp>

#include <Utils/MathUtils.hpp>

using namespace obe::Utils::Math;

TEST_CASE("A double should be truncated to an int without data loss (including floating point precision)", "[obe.Utils.Math.isDoubleInt]") 
{
    SECTION("Correct Positive values")
    {
        REQUIRE( isDoubleInt(0.0) == true );
        REQUIRE( isDoubleInt(42.0) == true );
        REQUIRE( isDoubleInt(7894561) == true );
        REQUIRE( isDoubleInt(2147483647) == true );
    }
    SECTION("Correct Negative values")
    {
        REQUIRE( isDoubleInt(-123456) == true );
        REQUIRE( isDoubleInt(-2147483647) == true );
    }
    SECTION("Overflow values")
    {
        REQUIRE( isDoubleInt(2147483648) == false );
        REQUIRE( isDoubleInt(-9000000000) == false );
    }
    SECTION("Floating point precision loss")
    {
        REQUIRE( isDoubleInt(4.5) == false );
        REQUIRE( isDoubleInt(-1.1) == false );
    }
}

TEST_CASE("A value should be converted from degrees to radians", "[obe.Utils.Math.convertToRadian]") 
{
    REQUIRE( convertToRadian(0) == 0 );
    REQUIRE( convertToRadian(90) == Approx(1.57) );
    REQUIRE( convertToRadian(0) == 0 );
    REQUIRE( convertToRadian(0) == 0 );
    REQUIRE( convertToRadian(0) == 0 );
    REQUIRE( convertToRadian(0) == 0 );
    REQUIRE( convertToRadian(0) == 0 );
    REQUIRE( convertToRadian(0) == 0 );
    REQUIRE( convertToRadian(0) == 0 );
    REQUIRE( convertToRadian(0) == 0 );
}