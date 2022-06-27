#include <catch/catch.hpp>

#include <Transform/Referential.hpp>

using namespace obe::transform;

TEST_CASE("Flipping Referentials should give correct results",
    "[obe.Transform.Referential.flip]")
{
    SECTION("Flipping both axis of known referentials")
    {
        REQUIRE(Referential::TopLeft.flip() == Referential::BottomRight);
        REQUIRE(Referential::Top.flip() == Referential::Bottom);
        REQUIRE(Referential::TopRight.flip() == Referential::BottomLeft);
        REQUIRE(Referential::Left.flip() == Referential::Right);
        REQUIRE(Referential::Center.flip() == Referential::Center);
        REQUIRE(Referential::Right.flip() == Referential::Left);
        REQUIRE(Referential::BottomLeft.flip() == Referential::TopRight);
        REQUIRE(Referential::Bottom.flip() == Referential::Top);
        REQUIRE(Referential::BottomRight.flip() == Referential::TopLeft);
    }
    SECTION("Flipping only horizontal axis of known referentials")
    {
        REQUIRE(Referential::TopLeft.flip(FlipAxis::Horizontal) == Referential::TopRight);
        REQUIRE(Referential::Top.flip(FlipAxis::Horizontal) == Referential::Top);
        REQUIRE(Referential::TopRight.flip(FlipAxis::Horizontal) == Referential::TopLeft);
        REQUIRE(Referential::Left.flip(FlipAxis::Horizontal) == Referential::Right);
        REQUIRE(Referential::Center.flip(FlipAxis::Horizontal) == Referential::Center);
        REQUIRE(Referential::Right.flip(FlipAxis::Horizontal) == Referential::Left);
        REQUIRE(Referential::BottomLeft.flip(FlipAxis::Horizontal)
            == Referential::BottomRight);
        REQUIRE(Referential::Bottom.flip(FlipAxis::Horizontal) == Referential::Bottom);
        REQUIRE(Referential::BottomRight.flip(FlipAxis::Horizontal)
            == Referential::BottomLeft);
    }
    SECTION("Flipping only vertical axis of known referentials")
    {
        REQUIRE(Referential::TopLeft.flip(FlipAxis::Vertical) == Referential::BottomLeft);
        REQUIRE(Referential::Top.flip(FlipAxis::Vertical) == Referential::Bottom);
        REQUIRE(
            Referential::TopRight.flip(FlipAxis::Vertical) == Referential::BottomRight);
        REQUIRE(Referential::Left.flip(FlipAxis::Vertical) == Referential::Left);
        REQUIRE(Referential::Center.flip(FlipAxis::Vertical) == Referential::Center);
        REQUIRE(Referential::Right.flip(FlipAxis::Vertical) == Referential::Right);
        REQUIRE(Referential::BottomLeft.flip(FlipAxis::Vertical) == Referential::TopLeft);
        REQUIRE(Referential::Bottom.flip(FlipAxis::Vertical) == Referential::Top);
        REQUIRE(
            Referential::BottomRight.flip(FlipAxis::Vertical) == Referential::TopRight);
    }
    SECTION("Flipping both axis of random referentials")
    {
        REQUIRE(Referential(0.1, 0.4).flip() == Referential(0.9, 0.6));
        REQUIRE(Referential(0.4, 0.6).flip() == Referential(0.6, 0.4));
        REQUIRE(Referential(0.2, 0.2).flip() == Referential(0.8, 0.8));
        REQUIRE(Referential(0.3, 0.5).flip() == Referential(0.7, 0.5));
    }
}

TEST_CASE("We should be able to test the position of referentials based on criterias",
    "[obe.Transform.Referential.isOn...]")
{
    SECTION("Testing if known referentials are on a corner")
    {
        REQUIRE(Referential::TopLeft.is_on_corner());
        REQUIRE(Referential::TopRight.is_on_corner());
        REQUIRE(Referential::BottomLeft.is_on_corner());
        REQUIRE(Referential::BottomRight.is_on_corner());
        REQUIRE_FALSE(Referential::Top.is_on_corner());
        REQUIRE_FALSE(Referential::Left.is_on_corner());
        REQUIRE_FALSE(Referential::Center.is_on_corner());
        REQUIRE_FALSE(Referential::Right.is_on_corner());
        REQUIRE_FALSE(Referential::Bottom.is_on_corner());
    }
    SECTION("Testing if known referentials are on a side")
    {
        REQUIRE_FALSE(Referential::TopLeft.is_on_side());
        REQUIRE_FALSE(Referential::TopRight.is_on_side());
        REQUIRE_FALSE(Referential::BottomLeft.is_on_side());
        REQUIRE_FALSE(Referential::BottomRight.is_on_side());
        REQUIRE(Referential::Top.is_on_side());
        REQUIRE(Referential::Left.is_on_side());
        REQUIRE_FALSE(Referential::Center.is_on_side());
        REQUIRE(Referential::Right.is_on_side());
        REQUIRE(Referential::Bottom.is_on_side());
    }
    SECTION("Testing if known referentials are on the left")
    {
        REQUIRE(Referential::TopLeft.is_on_left_side());
        REQUIRE_FALSE(Referential::Top.is_on_left_side());
        REQUIRE_FALSE(Referential::TopRight.is_on_left_side());
        REQUIRE(Referential::Left.is_on_left_side());
        REQUIRE_FALSE(Referential::Center.is_on_left_side());
        REQUIRE_FALSE(Referential::Right.is_on_left_side());
        REQUIRE(Referential::BottomLeft.is_on_left_side());
        REQUIRE_FALSE(Referential::Bottom.is_on_left_side());
        REQUIRE_FALSE(Referential::BottomRight.is_on_left_side());
    }
    SECTION("Testing if known referentials are on the right")
    {
        REQUIRE_FALSE(Referential::TopLeft.is_on_right_side());
        REQUIRE_FALSE(Referential::Top.is_on_right_side());
        REQUIRE(Referential::TopRight.is_on_right_side());
        REQUIRE_FALSE(Referential::Left.is_on_right_side());
        REQUIRE_FALSE(Referential::Center.is_on_right_side());
        REQUIRE(Referential::Right.is_on_right_side());
        REQUIRE_FALSE(Referential::BottomLeft.is_on_right_side());
        REQUIRE_FALSE(Referential::Bottom.is_on_right_side());
        REQUIRE(Referential::BottomRight.is_on_right_side());
    }
    SECTION("Testing if known referentials are on the top")
    {
        REQUIRE(Referential::TopLeft.is_on_top_side());
        REQUIRE(Referential::Top.is_on_top_side());
        REQUIRE(Referential::TopRight.is_on_top_side());
        REQUIRE_FALSE(Referential::Left.is_on_top_side());
        REQUIRE_FALSE(Referential::Center.is_on_top_side());
        REQUIRE_FALSE(Referential::Right.is_on_top_side());
        REQUIRE_FALSE(Referential::BottomLeft.is_on_top_side());
        REQUIRE_FALSE(Referential::Bottom.is_on_top_side());
        REQUIRE_FALSE(Referential::BottomRight.is_on_top_side());
    }
    SECTION("Testing if known referentials are on the bottom")
    {
        REQUIRE_FALSE(Referential::TopLeft.is_on_bottom_side());
        REQUIRE_FALSE(Referential::Top.is_on_bottom_side());
        REQUIRE_FALSE(Referential::TopRight.is_on_bottom_side());
        REQUIRE_FALSE(Referential::Left.is_on_bottom_side());
        REQUIRE_FALSE(Referential::Center.is_on_bottom_side());
        REQUIRE_FALSE(Referential::Right.is_on_bottom_side());
        REQUIRE(Referential::BottomLeft.is_on_bottom_side());
        REQUIRE(Referential::Bottom.is_on_bottom_side());
        REQUIRE(Referential::BottomRight.is_on_bottom_side());
    }
    SECTION("Testing random referentials and their positions")
    {
        REQUIRE(Referential(1, 0.33).is_on_right_side());
        REQUIRE(Referential(0, 0.66).is_on_left_side());
        REQUIRE(Referential(0.22, 1).is_on_bottom_side());
        REQUIRE(Referential(-0.11, 0).is_on_top_side());
        REQUIRE(Referential(0.99, 1).is_on_side());
        REQUIRE(Referential(0, 0).is_on_corner());
        REQUIRE_FALSE(Referential(0.999, 0.33).is_on_right_side());
        REQUIRE_FALSE(Referential(1, 0.66).is_on_left_side());
        REQUIRE_FALSE(Referential(0.22, 0).is_on_bottom_side());
        REQUIRE_FALSE(Referential(0.11, 1).is_on_top_side());
        REQUIRE_FALSE(Referential(0.99, 0.99).is_on_side());
        REQUIRE_FALSE(Referential(0.4, 0).is_on_corner());
    }
}

TEST_CASE("We should be able to represent a Referential as a string",
    "[obe.Transform.Referential.to_string]")
{
    SECTION("Transforming known referentials to string with default formatter")
    {
        REQUIRE(Referential::TopLeft.to_string() == "TopLeft");
        REQUIRE(Referential::Top.to_string() == "Top");
        REQUIRE(Referential::TopRight.to_string() == "TopRight");
        REQUIRE(Referential::Left.to_string() == "Left");
        REQUIRE(Referential::Center.to_string() == "Center");
        REQUIRE(Referential::Right.to_string() == "Right");
        REQUIRE(Referential::BottomLeft.to_string() == "BottomLeft");
        REQUIRE(Referential::Bottom.to_string() == "Bottom");
        REQUIRE(Referential::BottomRight.to_string() == "BottomRight");
    }
    SECTION("Transforming random referentials to string with default formatter")
    {
        REQUIRE(Referential(0.123, 0.456).to_string() == "0.123, 0.456");
        REQUIRE(Referential(0.6666, 0.9999).to_string() == "0.6666, 0.9999");
    }
}

TEST_CASE("We should be able to load a Referential from a string",
    "[obe.Transform.Referential.from_string]")
{
    SECTION("Loading known referentials from a string")
    {
        REQUIRE(Referential::from_string("TopLeft") == Referential::TopLeft);
        REQUIRE(Referential::from_string("Top") == Referential::Top);
        REQUIRE(Referential::from_string("TopRight") == Referential::TopRight);
        REQUIRE(Referential::from_string("Left") == Referential::Left);
        REQUIRE(Referential::from_string("Center") == Referential::Center);
        REQUIRE(Referential::from_string("Right") == Referential::Right);
        REQUIRE(Referential::from_string("BottomLeft") == Referential::BottomLeft);
        REQUIRE(Referential::from_string("Bottom") == Referential::Bottom);
        REQUIRE(Referential::from_string("BottomRight") == Referential::BottomRight);
    }
    SECTION("Loading random referentials from a string")
    {
        REQUIRE(Referential::from_string("0.1, 0.666")
            == Referential(0.1, 0.666));
        REQUIRE(
            Referential::from_string("-0.55, -1") == Referential(-0.55, -1));
        REQUIRE_THROWS(Referential::from_string("?"));
    }
}