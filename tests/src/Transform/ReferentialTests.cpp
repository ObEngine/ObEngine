#include <catch/catch.hpp>

#include <Transform/Referential.hpp>

using namespace obe::Transform;
using Axis = Referential::Axis;

TEST_CASE(
    "Flipping Referentials should give correct results", 
    "[obe.Transform.Referential.flip]"
) 
{
    SECTION("Flipping both axis of known referentials")
    {
        REQUIRE( Referential::TopLeft.flip() == Referential::BottomRight );
        REQUIRE( Referential::Top.flip() == Referential::Bottom );
        REQUIRE( Referential::TopRight.flip() == Referential::BottomLeft );
        REQUIRE( Referential::Left.flip() == Referential::Right );
        REQUIRE( Referential::Center.flip() == Referential::Center );
        REQUIRE( Referential::Right.flip() == Referential::Left );
        REQUIRE( Referential::BottomLeft.flip() == Referential::TopRight );
        REQUIRE( Referential::Bottom.flip() == Referential::Top );
        REQUIRE( Referential::BottomRight.flip() == Referential::TopLeft );
    }
    SECTION("Flipping only horizontal axis of known referentials")
    {
        REQUIRE( Referential::TopLeft.flip(Axis::Horizontal) == Referential::TopRight );
        REQUIRE( Referential::Top.flip(Axis::Horizontal) == Referential::Top );
        REQUIRE( Referential::TopRight.flip(Axis::Horizontal) == Referential::TopLeft );
        REQUIRE( Referential::Left.flip(Axis::Horizontal) == Referential::Right );
        REQUIRE( Referential::Center.flip(Axis::Horizontal) == Referential::Center );
        REQUIRE( Referential::Right.flip(Axis::Horizontal) == Referential::Left );
        REQUIRE( Referential::BottomLeft.flip(Axis::Horizontal) == Referential::BottomRight );
        REQUIRE( Referential::Bottom.flip(Axis::Horizontal) == Referential::Bottom );
        REQUIRE( Referential::BottomRight.flip(Axis::Horizontal) == Referential::BottomLeft );
    }
    SECTION("Flipping only vertical axis of known referentials")
    {
        REQUIRE( Referential::TopLeft.flip(Axis::Vertical) == Referential::BottomLeft );
        REQUIRE( Referential::Top.flip(Axis::Vertical) == Referential::Bottom );
        REQUIRE( Referential::TopRight.flip(Axis::Vertical) == Referential::BottomRight );
        REQUIRE( Referential::Left.flip(Axis::Vertical) == Referential::Left );
        REQUIRE( Referential::Center.flip(Axis::Vertical) == Referential::Center );
        REQUIRE( Referential::Right.flip(Axis::Vertical) == Referential::Right );
        REQUIRE( Referential::BottomLeft.flip(Axis::Vertical) == Referential::TopLeft );
        REQUIRE( Referential::Bottom.flip(Axis::Vertical) == Referential::Top );
        REQUIRE( Referential::BottomRight.flip(Axis::Vertical) == Referential::TopRight );
    }
    SECTION("Flipping both axis of random referentials")
    {
        REQUIRE( Referential(0.1, 0.4).flip() == Referential(0.9, 0.6) );
        REQUIRE( Referential(0.4, 0.6).flip() == Referential(0.6, 0.4) );
        REQUIRE( Referential(0.2, 0.2).flip() == Referential(0.8, 0.8) );
        REQUIRE( Referential(0.3, 0.5).flip() == Referential(0.7, 0.5) );
    }
}

TEST_CASE(
    "We should be able to test the position of referentials based on criterias", 
    "[obe.Transform.Referential.isOn...]"
)
{
    SECTION("Testing if known referentials are on a corner")
    {
        REQUIRE( Referential::TopLeft.isOnCorner() );
        REQUIRE( Referential::TopRight.isOnCorner() );
        REQUIRE( Referential::BottomLeft.isOnCorner() );
        REQUIRE( Referential::BottomRight.isOnCorner() );
        REQUIRE_FALSE( Referential::Top.isOnCorner() );
        REQUIRE_FALSE( Referential::Left.isOnCorner() );
        REQUIRE_FALSE( Referential::Center.isOnCorner() );
        REQUIRE_FALSE( Referential::Right.isOnCorner() );
        REQUIRE_FALSE( Referential::Bottom.isOnCorner() );
    }
    SECTION("Testing if known referentials are on a side")
    {
        REQUIRE_FALSE( Referential::TopLeft.isOnSide() );
        REQUIRE_FALSE( Referential::TopRight.isOnSide() );
        REQUIRE_FALSE( Referential::BottomLeft.isOnSide() );
        REQUIRE_FALSE( Referential::BottomRight.isOnSide() );
        REQUIRE( Referential::Top.isOnSide() );
        REQUIRE( Referential::Left.isOnSide() );
        REQUIRE_FALSE( Referential::Center.isOnSide() );
        REQUIRE( Referential::Right.isOnSide() );
        REQUIRE( Referential::Bottom.isOnSide() );
    }
    SECTION("Testing if known referentials are on the left")
    {
        REQUIRE( Referential::TopLeft.isOnLeftSide() );
        REQUIRE_FALSE( Referential::Top.isOnLeftSide() );
        REQUIRE_FALSE( Referential::TopRight.isOnLeftSide() );
        REQUIRE( Referential::Left.isOnLeftSide() );
        REQUIRE_FALSE( Referential::Center.isOnLeftSide() );
        REQUIRE_FALSE( Referential::Right.isOnLeftSide() );
        REQUIRE( Referential::BottomLeft.isOnLeftSide() );
        REQUIRE_FALSE( Referential::Bottom.isOnLeftSide() );
        REQUIRE_FALSE( Referential::BottomRight.isOnLeftSide() );
    }
    SECTION("Testing if known referentials are on the right")
    {
        REQUIRE_FALSE( Referential::TopLeft.isOnRightSide() );
        REQUIRE_FALSE( Referential::Top.isOnRightSide() );
        REQUIRE( Referential::TopRight.isOnRightSide() );
        REQUIRE_FALSE( Referential::Left.isOnRightSide() );
        REQUIRE_FALSE( Referential::Center.isOnRightSide() );
        REQUIRE( Referential::Right.isOnRightSide() );
        REQUIRE_FALSE( Referential::BottomLeft.isOnRightSide() );
        REQUIRE_FALSE( Referential::Bottom.isOnRightSide() );
        REQUIRE( Referential::BottomRight.isOnRightSide() );
    }
    SECTION("Testing if known referentials are on the top")
    {
        REQUIRE( Referential::TopLeft.isOnTopSide() );
        REQUIRE( Referential::Top.isOnTopSide() );
        REQUIRE( Referential::TopRight.isOnTopSide() );
        REQUIRE_FALSE( Referential::Left.isOnTopSide() );
        REQUIRE_FALSE( Referential::Center.isOnTopSide() );
        REQUIRE_FALSE( Referential::Right.isOnTopSide() );
        REQUIRE_FALSE( Referential::BottomLeft.isOnTopSide() );
        REQUIRE_FALSE( Referential::Bottom.isOnTopSide() );
        REQUIRE_FALSE( Referential::BottomRight.isOnTopSide() );
    }
    SECTION("Testing if known referentials are on the bottom")
    {
        REQUIRE_FALSE( Referential::TopLeft.isOnBottomSide() );
        REQUIRE_FALSE( Referential::Top.isOnBottomSide() );
        REQUIRE_FALSE( Referential::TopRight.isOnBottomSide() );
        REQUIRE_FALSE( Referential::Left.isOnBottomSide() );
        REQUIRE_FALSE( Referential::Center.isOnBottomSide() );
        REQUIRE_FALSE( Referential::Right.isOnBottomSide() );
        REQUIRE( Referential::BottomLeft.isOnBottomSide() );
        REQUIRE( Referential::Bottom.isOnBottomSide() );
        REQUIRE( Referential::BottomRight.isOnBottomSide() );
    }
    SECTION("Testing random referentials and their positions")
    {
        REQUIRE( Referential(1, 0.33).isOnRightSide() );
        REQUIRE( Referential(0, 0.66).isOnLeftSide() );
        REQUIRE( Referential(0.22, 1).isOnBottomSide() );
        REQUIRE( Referential(-0.11, 0).isOnTopSide() );
        REQUIRE( Referential(0.99, 1).isOnSide() );
        REQUIRE( Referential(0, 0).isOnCorner() );
        REQUIRE_FALSE( Referential(0.999, 0.33).isOnRightSide() );
        REQUIRE_FALSE( Referential(1, 0.66).isOnLeftSide() );
        REQUIRE_FALSE( Referential(0.22, 0).isOnBottomSide() );
        REQUIRE_FALSE( Referential(0.11, 1).isOnTopSide() );
        REQUIRE_FALSE( Referential(0.99, 0.99).isOnSide() );
        REQUIRE_FALSE( Referential(0.4, 0).isOnCorner() );
    }
}

TEST_CASE(
    "We should be able to represent a Referential as a string", 
    "[obe.Transform.Referential.toString]"
)
{
    SECTION("Transforming known referentials to string with default formatter")
    {
        REQUIRE( Referential::TopLeft.toString() == "Referential<TopLeft>" );
        REQUIRE( Referential::Top.toString() == "Referential<Top>" );
        REQUIRE( Referential::TopRight.toString() == "Referential<TopRight>" );
        REQUIRE( Referential::Left.toString() == "Referential<Left>" );
        REQUIRE( Referential::Center.toString() == "Referential<Center>" );
        REQUIRE( Referential::Right.toString() == "Referential<Right>" );
        REQUIRE( Referential::BottomLeft.toString() == "Referential<BottomLeft>" );
        REQUIRE( Referential::Bottom.toString() == "Referential<Bottom>" );
        REQUIRE( Referential::BottomRight.toString() == "Referential<BottomRight>" );
    }
    SECTION("Transforming known referentials to string with custom formatter")
    {
        REQUIRE( Referential::TopLeft.toString("A({})") == "A(TopLeft)" );
        REQUIRE( Referential::Top.toString("+{}") == "+Top" );
        REQUIRE( Referential::TopRight.toString("/{}/") == "/TopRight/" );
        REQUIRE( Referential::Left.toString("Why did you {} me") == "Why did you Left me" );
        REQUIRE( Referential::Center.toString("{} of the Earth") == "Center of the Earth" );
        REQUIRE( Referential::Right.toString("You were actually {}") == "You were actually Right" );
        REQUIRE( Referential::BottomLeft.toString("1+2={}") == "1+2=BottomLeft" );
        REQUIRE( Referential::Bottom.toString("Bikini {}") == "Bikini Bottom" );
        REQUIRE( Referential::BottomRight.toString("{0} == {0}") == "BottomRight == BottomRight" );
    }
    SECTION("Transforming random referentials to string with default formatter")
    {
        REQUIRE( Referential(0.123, 0.456).toString() == "Referential<0.123, 0.456>" );
        REQUIRE( Referential(0.6666, 0.9999).toString() == "Referential<0.6666, 0.9999>" );
    }
    SECTION("Transforming random referentials to string with custom formatter")
    {
        REQUIRE( Referential(0.9, 0.1).toString("{}") == "0.9, 0.1" );
        REQUIRE( Referential(0.1234, 0.5678).toString("Referential => {}") == "Referential => 0.1234, 0.5678" );
        REQUIRE( Referential(0.666, 1).toString("The devil is == {1}") == "The devil is == 0.666" );
        REQUIRE( Referential(0.1, 0.42).toString("I wonder why {2} is the answer") == "I wonder why 0.42 is the answer" );
        REQUIRE( Referential(0.456, 0.123).toString("y = {2}, x = {1}") == "y = 0.123, x = 0.456" );
    }
}

TEST_CASE(
    "We should be able to load a Referential from a string", 
    "[obe.Transform.Referential.FromString]"
)
{
    SECTION("Loading known referentials from a string")
    {
        REQUIRE( Referential::FromString("TopLeft") == Referential::TopLeft );
        REQUIRE( Referential::FromString("Top") == Referential::Top );
        REQUIRE( Referential::FromString("TopRight") == Referential::TopRight );
        REQUIRE( Referential::FromString("Left") == Referential::Left );
        REQUIRE( Referential::FromString("Center") == Referential::Center );
        REQUIRE( Referential::FromString("Right") == Referential::Right );
        REQUIRE( Referential::FromString("BottomLeft") == Referential::BottomLeft );
        REQUIRE( Referential::FromString("Bottom") == Referential::Bottom );
        REQUIRE( Referential::FromString("BottomRight") == Referential::BottomRight );
    }
    SECTION("Loading random referentials from a string")
    {
        REQUIRE( Referential::FromString("Referential<0.1, 0.666>") == Referential(0.1, 0.666) );
        REQUIRE( Referential::FromString("Referential<-0.55, -1>") == Referential(-0.55, -1) );
        REQUIRE_THROWS( Referential::FromString("?") );
    }
}