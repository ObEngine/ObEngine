# Changelog

## 0.2.0

### Notes

v0.2.0 most major change is the new Audio backend. 

Leaving SFML-Audio was not very hard as the only piece of code that used the audio were the Lua bindings.
This means, ÖbEngine doesn't rely on OpenAL anymore and doesn't have any LGPL contraints anymore.

Every ÖbEngine dependency can now be statically linked without any restriction.

This release also brings easier setup on Windows as you won't have to copy dll by hand anymore, this process is now automated.

The UI also supports high-dpi screens now, no more tiny window in the center of your screen where you have to use a magnifier to see on what button you are clicking.

Overall, this is a small release before the next bigger release : 0.3.0.

### Major changes

- :hammer: Automated build / release jobs with GitHub Actions
- :sound: New Audio API / Backend (from SFML-Audio to Soloud)
- :book: DLL are now copied on the execution directory on Windows
- :tv: UI now support high-dpi screens

### Minor changes

- :mute: Vili files are now silently parsed by default
- :no_entry_sign: Animation, LevelSprite and ResourceManager now support anti-aliasing parameter
- :octocat: Git variables (OBENGINE_COMMIT, OBENGINE_VERSION) are now configured as a file instead of a define
- :gear: Config is now part of Config namespace instead of System namespace
- :checkered_flag: InputCombinationElement now uses a FlagSet instead of a std::vector
- :rocket: ObEngineCore now has a InitEngine function which initialize most of the engine components
- :computer: Simplified GameObject components code
- :left_right_arrow: Added UnitVector::distance method
- :heavy_multiplication_x: GameObject cache is now cleared when the MapEditor is closed, no need to restart engine anymore

### Bugfixes
- :black_nib: Retrieving an id from a Canvas Element in Lua now works
- :bug: Fixed ProtectedIdentifiable bindings
- :bug: Fixed UI anti-aliasing
- :red_circle: Added error message when [Component]Script::source/sources had the wrong Vili type
- :black_nib: Fixed wrong alignment of Text in Canvas

## v0.1.0

### Notes

First semver release of ÖbEngine
