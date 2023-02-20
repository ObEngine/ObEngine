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

    constexpr int MAX_AMOUNT_OF_ANIMATIONS = 100; // const globals are SCREAMING_SNAKE_CASE
    extern Logger Log; // global statics / externs are PascalCase

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
          // 1️⃣ static attributes
          // 2️⃣ static methods second
          // 3️⃣ attributes third
          // 4️⃣ methods fourth
        std::size_t m_code_index = 0; // attributes are snake_case
                                      // (private) attributes must be prefixed with m_
    public:
        [[nodiscard]] constexpr std::string_view ComponentType = "AnimationState"; // static attributes are PascalCase

        [[nodiscard]] AnimationStatus get_status() const noexcept; // methods are snake_case

        AnimationGroup& get_group(const std::string& group_id); // parameters are snake_case
                                                                // also notice that the ampersand is on the type side
                                                                // BAD: const std::string &group_id
                                                                // GOOD: const std::string& group_id
        
        [[nodiscard]] bool is_paused() const; // methods returning booleans should be named is_xxx rather than get_xxx
        
        void set_static(bool static_); // when a variable name clashes with a C++ keywork
                                       // add a trailing underscore to fix the collision
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

namespace obe::animation // use nested namespace here as well
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

## Lua style

See [.clang-format](.lua-format) for formatting style

### General purpose code

```lua
-- top-level variables are snake_case
local my_toplevel_variable = 10;

-- globals are SCREAMING_SNAKE_CASE
MY_GLOBAL = 20;

-- functions are snake_case
function cool_function()
  -- always use local
  -- variables are snake_case
  local my_variable = 3; -- all statements ends-with semi-colon
end

local MyClass = class(); -- classes are PascalCase

function MyClass:init() -- class constructor
  self.things = {};
end

-- methods are defined using colon
-- methods are snake_case
function MyClass:get_thing(thing_name)
  return self.things[thing_name];
end

-- private methods / implementation details are prefixed with underscore
function MyClass:_set_private_thing_name(private_thing_name)
  -- private attributes are prefixed with underscore
  self._private_thing_name = private_thing_name;
end

-- use dot notation for module paths
-- always use parenthesis for requires
local canvas_module = require("obe://lib.internal.canvas");

-- fetching an element directly from a module is allowed and encouraged
local CanvasClass = require("obe://lib.internal.canvas").Canvas;

-- modules should always return table
-- never return value / class directly
return {
  MyClass = MyClass
};
```

### Events and Tasks

```lua
-- Events are PascalCase.PascalCase.PascalCase
-- Event parameter should always be named evt
function Event.Game.Update(evt)
  print(evt.dt); -- Event data is snake_case
end

-- Tasks are PascalCase.PascalCase
-- Task parameter should always be named ctx
function Task.ParentTask(ctx)
    local start_epoch = obe.time.epoch();
    ctx:wait_for(3);
    local end_epoch = obe.time.epoch();
    print("Took", end_epoch - start_epoch, "seconds");
end
```

### Other elements

Engine's global instances are provided to the Lua VM through the `Engine` (`class Engine`) object.

```lua
-- Global instances are PascalCase
Engine.Audio:load("cwd://sounds/my_sound.ogg");
Engine.Scene:load("cwd://scenes/my_scene.vili");
```

Game globals are shared using the `Global` table

```lua
-- Game globals are snake_case
Global.total_lives = 3;
```

GameObject structure is the following one

```lua
-- ALWAYS annotate GameObjects like this so you can reference the type everywhere in your project
---@class SampleObject : GameObjectCls
local SampleObject = GameObject();

local my_local_variable = 3;  -- local variables are snake_case
                              -- local variables are defined as module-local variable
                              -- local variables are useful for GameObject internal stuff you do not want to expose
                              -- try to keep them either on the top of the file / top of the function where they are used

public_variable = 10;         -- global variables are NOT recommended
                              -- they will not be shared across GameObjects (scoped to the GameObject environment)
                              -- if you want other GameObjects to access a value, either :
                                  -- make it a GameObject attribute / public method
                                  -- put it in the Global object (recommended for debugging purpose only)
                                  -- create a GameObject dedicated to value sharing
                                  -- do you really need to share the value in the first place ? (see events)

local my_variable_used_only_in_do_something_function = 0;

-- private function is snake_case
-- used for GameObject mechanisms you do not want to expose
-- try to keep them on top of the file / close to the place where they are useful
local function do_something()
  my_variable_used_only_in_do_something_function = my_variable_used_only_in_do_something_function + 1;
  -- if you need to access a GameObject attribute in a function that is not a method, just use the GameObject handle (here SampleObject)
  return my_local_variable + SampleObject.a;
end

function SampleObject:init(a, b)
  -- internal variable, won't be able to be read from outside
  my_local_variable = a + b;
  -- public attribute, will be accessible as SampleObject.a
  self.a = a;
  -- private attribute, still accessible as SampleObject._b but private "by convention"
  self._b = b;
end

-- public functions are NOT recommended
-- see global variables comments above for more details
function do_something_in_public()
  return a + b;
end

function Event.Game.Update(evt)
  -- Like in non-method functions, to access SampleObject attributes, just use its handle
  SampleObject._b = SampleObject._b + evt.dt;
end
```
