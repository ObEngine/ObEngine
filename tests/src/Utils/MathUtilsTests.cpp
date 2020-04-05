#include <catch/catch.hpp>

#include <Collision/PolygonalCollider.hpp>
#include <Utils/MathUtils.hpp>

using namespace obe::Utils::Math;

TEST_CASE("A double should be truncated to an int without data loss"
          " (including floating point precision)",
    "[obe.Utils.Math.isDoubleInt]")
{
    SECTION("Correct Positive values")
    {
        REQUIRE(isDoubleInt(0.0) == true);
        REQUIRE(isDoubleInt(42.0) == true);
        REQUIRE(isDoubleInt(7894561) == true);
        REQUIRE(isDoubleInt(2147483647) == true);
    }
    SECTION("Correct Negative values")
    {
        REQUIRE(isDoubleInt(-123456) == true);
        REQUIRE(isDoubleInt(-2147483647) == true);
    }
    SECTION("Overflow values")
    {
        REQUIRE(isDoubleInt(2147483648) == false);
        REQUIRE(isDoubleInt(-9000000000) == false);
    }
    SECTION("Floating point precision loss")
    {
        REQUIRE(isDoubleInt(4.5) == false);
        REQUIRE(isDoubleInt(-1.1) == false);
    }
}

TEST_CASE("A value should be converted from degrees to radians",
    "[obe.Utils.Math.convertToRadian]")
{
    SECTION("Positive Known Angles")
    {
        REQUIRE(convertToRadian(0) == 0);
        REQUIRE(convertToRadian(90) == Approx(pi / 2));
        REQUIRE(convertToRadian(180) == Approx(pi).margin(0.1));
        REQUIRE(convertToRadian(270) == Approx(pi + pi / 2));
    }
    SECTION("Negative Known Angles")
    {
        REQUIRE(convertToRadian(-90) == Approx(-pi / 2));
        REQUIRE(convertToRadian(-180) == Approx(-pi));
        REQUIRE(convertToRadian(-270) == Approx(-pi - pi / 2));
        REQUIRE(convertToRadian(-360) == Approx(-2 * pi));
    }
    SECTION("Random Angles")
    {
        REQUIRE(convertToRadian(22) == Approx(0.383972));
        REQUIRE(convertToRadian(42) == Approx(0.733038));
        REQUIRE(convertToRadian(-59) == Approx(-1.02974));
        REQUIRE(convertToRadian(-196) == Approx(-3.42085));
    }
}

TEST_CASE("A value should be converted from radians to degrees",
    "[obe.Utils.Math.convertToDegree]")
{
    SECTION("Positive Known Angles")
    {
        REQUIRE(convertToDegree(0) == 0);
        REQUIRE(convertToDegree(pi / 2) == Approx(90));
        REQUIRE(convertToDegree(pi) == Approx(180));
        REQUIRE(convertToDegree(pi + pi / 2) == Approx(270));
    }
    SECTION("Negative Known Angles")
    {
        REQUIRE(convertToDegree(-pi / 2) == Approx(-90));
        REQUIRE(convertToDegree(-pi) == Approx(-180));
        REQUIRE(convertToDegree(-pi - pi / 2) == Approx(-270));
        REQUIRE(convertToDegree(-2 * pi) == Approx(-360));
    }
    SECTION("Random Angles")
    {
        REQUIRE(convertToDegree(1) == Approx(57.2958));
        REQUIRE(convertToDegree(22) == Approx(1260.51));
        REQUIRE(convertToDegree(-2.5) == Approx(-143.239));
        REQUIRE(convertToDegree(0.7) == Approx(40.107));
    }
}

TEST_CASE("A value should be normalised from start to end", "[obe.Utils.Math.normalise]")
{
    SECTION("Angle normalisation")
    {
        REQUIRE(normalize(0, 0, 360) == 0);
        REQUIRE(normalize(360, 0, 360) == 0);
        REQUIRE(normalize(361, 0, 360) == 1);
        REQUIRE(normalize(720, 0, 360) == 0);
        REQUIRE(normalize(1000, 0, 360) == 280);
        REQUIRE(normalize(-650, 0, 360) == 70);
    }
}

TEST_CASE(
    "A random number should be between min and max value", "[obe.Utils.Math.randint]")
{
    SECTION("Positive bounds")
    {
        REQUIRE(randint(0, 100) >= 0);
        REQUIRE(randint(0, 100) <= 100);
    }
}

TEST_CASE("A random number should be between 0 and 1", "[obe.Utils.Math.randfloat]")
{
    SECTION("100 random float")
    {
        for (unsigned int i = 0; i < 100; i++)
        {
            float value = randfloat();
            REQUIRE(value >= 0.f);
            REQUIRE(value <= 1.f);
        }
    }
}