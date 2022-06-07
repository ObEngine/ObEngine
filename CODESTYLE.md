# Codestyle

This doc defines all the conventions across ÖbEngine's codebase.

## File tree

```
📁 cmake/
  📄 clang_format.cmake # snake_case
📁 engine/
  📁 lib/ # lua libraries are snake_case
    📁 internal/
      📄 arg_mirror.lua # lua modules are snake_case
  📁 projects/
     📁 sample_project/ # project names are snake_case
       📁 scenes/ # project directories are snake_case
         📄 my_scene.vili # project elements are snake_case
  📄 config.vili # snake_case, single-word if possible
  📄 mount.vili
📁 include/
  📁 obe/ # snake_case
    📁 core/ # snake_case
      📁 animation/ # snake_case
        📄 animation_group.hpp # snake_case
                               # headers are .hpp
        📄 animation_template_stuff.inl # snake_case
                                        # template files are in include/ and are .inl
📁 src/
  📁 obe/ # snake_case
    📁 core/ # snake_case
      📄 CMakeLists.txt # PascalCase (actually enforced by CMake)
      📁 animation/ # snake_case
        📄 animation_group.cpp # snake_case
                               # source files are .cpp
```

## C++ style

See [.clang-format](.clang-format) for formatting style

### Headers

```cpp
#pragma once # use pragma instead of #ifndef

// namespaces must follow file structure folder::subfolder::subsubfolder
// use nested namespaces syntax
// in some cases, the last subnamespace can represent the file (schemas, exceptions...)
//    such as obe::animation::exceptions located in (include/obe/core/animation/exceptions.hpp)
namespace obe::animation // namespaces are snake_case::snake_case::...


{ // braces follow Allman style : https://en.wikipedia.org/wiki/Indentation_style#Allman_style

    // Use 4 spaces indentation everywhere (no tabs)

    constexpr int MAX_AMOUNT_OF_ANIMATIONS = 100; // globals / statics are SCREAMING_SNAKE_CASE

    enum class AnimationStatus // enums are PascalCase
    {
        Play, // enum elements are PascalCase
        Call
    };
    
    // use using instead of typedef
    // type aliases are PascalCase
    using AnimationStatusMeta = Types::SmartEnum<AnimationStatus>;
    

    struct AnimationConfiguration // struct are used for data-only classes exclusively
    {
        int frame_duration; // public attributes are snake_case
                            // public attributes have no prefix
    };


    class AnimationState // classes are PascalCase
    {
    // access specifiers (private / public) must be aligned with braces
    // inside a class, for access specifiers, follow order:
          // 1️⃣ private
          // 2️⃣ protected
          // 3️⃣ public
    private:
        // within an access specifier, follow order:
          // 1️⃣ attributes
          // 2️⃣ methods second
          // 3️⃣ static methods third
        std::size_t m_code_index = 0; // attributes are snake_case
                                      // (private) attributes must be prefixed with m_
    public:
        [[nodiscard]] AnimationStatus get_status() const noexcept; // methods are snake_case

        AnimationGroup& get_group(const std::string& group_id); // parameters are snake_case
                                                                // also notice that the ampersand is on the type side
                                                                // BAD: const std::string &group_id
                                                                // GOOD: const std::string& group_id
    };
    
    Animation make_animation_from_directory(System::Path path); // functions are snake_case
}

// use class rather than typename
template <class Enum> // template-type is PascalCase
                      // template-type must be proper name, avoid single letter identifier !
class SmartEnum
{
public:
    [[nodiscard]] static Enum from_string(const std::string& value); // static methods are snake_case
};
```

### Source code

```cpp
// keep includes sorted
// one line between each group (STL / external / internal)

// STL goes first
#include <string>
#include <vector>

// External libraries goes second
#include <vili/node.hpp>
#include <vili/parser.hpp>
#include <vld8/validator.hpp>

// Internal source-code goes third
#include <obe/core/animation.hpp>
#include <obe/core/animation_group.hpp>

namespace obe::Animation // use nested namespace here as well
{
    // do not hesitate to use verbose names
    std::vector<std::string> Animation::get_all_animation_groups_names() const
    {
        std::vector<std::string> animation_group_names; // variables are snake_case
        animation_group_names.reserve(m_groups.size());
        std::transform(m_groups.cbegin(), m_groups.cend(), animation_group_names.begin(),
            [](const auto& pair) { return pair.first; });
        return animation_group_names;
    }
}
```
