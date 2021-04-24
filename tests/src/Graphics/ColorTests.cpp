#include <catch/catch.hpp>

#include <Graphics/Color.hpp>
#include <vili/node.hpp>
#include <vili/parser/parser.hpp>
#include <fmt/format.h>


using namespace obe::Graphics;

std::string expectedHsv(std::string_view H, std::string_view S, std::string_view V)
{
    return fmt::format("color:\n\tH:{}\n\tS:{}\n\tV:{}\n", H, S, V);
}

std::string expectedRgba(
    std::string_view r, std::string_view g, std::string_view b, std::string_view a)
{
    return fmt::format("color:\n\tr:{}\n\tg:{}\n\tb:{}\n\ta:{}\n", r, g, b, a);
}

std::string expectedHex(std::string_view hex)
{
    return fmt::format("color: \"{}\"\n", hex);
}

std::string expectedColorName(std::string_view colorName)
{
    return fmt::format("color: \"{}\"\n", colorName);
}


TEST_CASE("Color dump should change based on the ColorType provided", "[obe.Graphics.Color.dump]")
{
    Color color(123, 104, 238, 220);
    SECTION("Default ColorType")
    {
        vili::node node = vili::object { { "color", color.dump() } };
        std::string expectedResult = expectedRgba("123.0", "104.0", "238.0", "220.0");
        REQUIRE(node.dump(true) == expectedResult);
    }
    SECTION("ColorType is Rgba")
    {
        vili::node node = vili::object { { "color", color.dump(ColorType::Rgba) } };
        std::string expectedResult = expectedRgba("123.0", "104.0", "238.0", "220.0");
        REQUIRE(node.dump(true) == expectedResult);
    }
    color.a = 255;
    SECTION("ColorType is Hsv")
    {
        vili::node node = vili::object { { "color", color.dump(ColorType::Hsv) } };
        std::string expectedResult = expectedHsv("248.507463", "0.563025", "0.933333");
        REQUIRE(node.dump(true) == expectedResult);
    }
    SECTION("ColorType is Hex")
    {
        vili::node node = vili::object { { "color", color.dump(ColorType::Hex) } };
        std::string expectedResult = expectedHex("#7b68ee");
        REQUIRE(node.dump(true) == expectedResult);
    }
    SECTION("ColorType is ColorName")
    {
        vili::node node = vili::object { { "color", color.dump(ColorType::ColorName) } };
        std::string expectedResult = expectedColorName("mediumslateblue");
        REQUIRE(node.dump(true) == expectedResult);
    }
}

TEST_CASE("Color load should be able to load different ColorTypes", "[obe.Graphics.Color.load]")
{
    Color expectedColor(123, 104, 238, 220);
    SECTION("ColorType is Rgba")
    {
        vili::node node
            = vili::parser::from_string(expectedRgba("123.0", "104.0", "238.0", "220.0"));
        Color color;
        color.load(node.at("color"));
        REQUIRE(color == expectedColor);
    }
    expectedColor.a = 255;
    SECTION("ColorType is Hsv")
    {
        vili::node node = vili::parser::from_string(expectedHsv("248.507463", "0.563025", "0.933333"));
        Color color;
        color.load(node.at("color"));
        REQUIRE(color == expectedColor);
    }
    SECTION("ColorType is Hex")
    {
        vili::node node = vili::parser::from_string(expectedHex("#7b68ee"));
        Color color;
        color.load(node.at("color"));
        REQUIRE(color == expectedColor);
    }
    SECTION("ColorType is ColorName")
    {
        vili::node node = vili::parser::from_string(expectedHex("mediumslateblue"));
        Color color;
        color.load(node.at("color"));
        REQUIRE(color == expectedColor);
    }
}

TEST_CASE("Color dump should be able to infer the desired ColorType from the last Color.fromXXX method used", "[obe.Graphics.Color.fromXXX]")
{
    SECTION("ColorType is Rgba")
    {
        Color color;
        color.fromRgb(123, 104, 238, 220);
        vili::node node = vili::object { { "color", color.dump() } };
        std::string expectedResult = expectedRgba("123.0", "104.0", "238.0", "220.0");
        REQUIRE(node.dump(true) == expectedResult);
    }
    SECTION("ColorType is Hsv")
    {
        Color color;
        color.fromHsv(248.507463, 0.563025, 0.933333);
        vili::node node = vili::object { { "color", color.dump() } };
        std::string expectedResult = expectedHsv("248.507463", "0.563025", "0.933333");
        REQUIRE(node.dump(true) == expectedResult);
    }
    SECTION("ColorType is Hex")
    {
        Color color;
        color.fromHex("#7b68ee");
        vili::node node = vili::object { { "color", color.dump() } };
        std::string expectedResult = expectedHex("#7b68ee");
        REQUIRE(node.dump(true) == expectedResult);
    }
    SECTION("ColorType is Hex using generic fromString method")
    {
        Color color;
        color.fromString("#7b68ee");
        vili::node node = vili::object { { "color", color.dump() } };
        std::string expectedResult = expectedHex("#7b68ee");
        REQUIRE(node.dump(true) == expectedResult);
    }
    SECTION("ColorType is ColorName")
    {
        Color color;
        color.fromName("MediumSlateBlue");
        vili::node node = vili::object { { "color", color.dump() } };
        std::string expectedResult = expectedColorName("mediumslateblue");
        REQUIRE(node.dump(true) == expectedResult);
    }
    SECTION("ColorType is ColorName using generic fromString method")
    {
        Color color;
        color.fromString("MediumSlateBlue");
        vili::node node = vili::object { { "color", color.dump() } };
        std::string expectedResult = expectedColorName("mediumslateblue");
        REQUIRE(node.dump(true) == expectedResult);
    }
}