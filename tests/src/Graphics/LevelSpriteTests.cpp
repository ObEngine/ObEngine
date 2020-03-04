#include <catch/catch.hpp>
#include <SFML/Graphics/Image.hpp>
#include <System/Path.hpp>
#include <Graphics/LevelSprite.hpp>
#include <Graphics/ResourceManager.hpp>
#include <Utils/FileUtils.hpp>

using namespace obe;


TEST_CASE(
    "Testing resource manager", "[obe.Grahics.ResourceManager]")
{
    // Initializing game engine and resource manager
    Debug::InitLogger();
    System::Path::Mount(System::MountablePath(System::MountablePathType::Path, ".", 1));
    Graphics::ResourceManager resourceManager;

    SECTION("Get texture")
    {
        // Creating fake image to apply texture
        sf::Image fakeImage;
        fakeImage.create(1,1);
        std::string fPath = "image.png";
        fakeImage.saveToFile(fPath);

        // Calling get texture twice with antiAliasing at true.
        // Checking if they have the same address allows to verify if caching works fine.
        bool antiAliasing = true;
        sf::Texture* texture1 = resourceManager.getTexture(fPath, antiAliasing);
        sf::Texture* texture2 = resourceManager.getTexture(fPath, antiAliasing);
    
        // Calling get texture twice with antiAliasing at false.
        // Their address must be different from the previous textures applied.
        antiAliasing = false;
        sf::Texture* texture3 = resourceManager.getTexture(fPath, antiAliasing);
        sf::Texture* texture4 = resourceManager.getTexture(fPath, antiAliasing);

        Utils::File::deleteFile(fPath);

        REQUIRE((texture1 == texture2 && texture2 != texture3 && texture3 == texture4));
    }
    SECTION("Get font")
    {
        // Creating fake font
        sf::Font fakeFont;
        fakeFont.loadFromFile("");
        std::string fPath = "../";
        fakeFont.saveToFile(fPath);

        // Calling get font twice to check correct caching.
        sf::Font* font1 = resourceManager.getFont(fPath);
        sf::Font* font2 = resourceManager.getFont(fPath);

        Utils::File::deleteFile(fPath);

        REQUIRE(font1 == font2);
    }

}