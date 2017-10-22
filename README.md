# ![ÖbEngine](https://raw.githubusercontent.com/Sygmei/ObWiki/master/title.png)

[![Build Status](https://travis-ci.org/Sygmei/ObEngine.svg?branch=master)](https://travis-ci.org/Sygmei/ObEngine)
[![Build Status](https://ci.appveyor.com/api/projects/status/ObEngine)](https://ci.appveyor.com/project/Sygmei/obengine)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/Sygmei/ObEngine/master/license)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/Sygmei/ObEngine/master/license)
[![Github All Releases](https://img.shields.io/github/downloads/sygmei/obengine/total.svg)]()
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/81846da629d244f69f357568a2f8d690)](https://www.codacy.com/app/Sygmei/ObEngine?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Sygmei/ObEngine&amp;utm_campaign=Badge_Grade)

## Useful links

- [ÖbEngine's Wiki](https://github.com/Sygmei/ObEngine/wiki)
- [ÖbEngine's Website](https://www.obengine.io)
- [ÖbEngine's Documentation](https://www.obengine.io/doc)
- [ÖbEngine's Discord](https://discord.gg/HkM6zdT)
- [ÖbEngine's Development Boards](https://github.com/Sygmei/ObEngine/projects)

## What the hell is ÖbEngine ?
ÖbEngine (ÖbE is shorter) is a 2D Game Engine made on top of SFML !

## What do I need to build it ?
You will need several libs :
- [SFML 2.4.2](https://www.sfml-dev.org/download/sfml/2.4.2/index-fr.php) (Display, Input, Network, Sound and much more)

There are other libraries but they are included in the repository (extlibs/ folder) :

- [clipper](http://www.angusj.com/delphi/clipper.php) (Boost Software License) (Polygons)
- (Customised code) [any](https://github.com/PaulHowes/any) (Apache 2.0 License) (Contains anything)
- [11zip](https://github.com/Sygmei/11Zip)  (MIT License) (minizip wrapper based on [Vili Peter's work](http://www.vilipetek.com/2013/11/22/zippingunzipping-files-in-c/))
- [Kaguya](https://github.com/satoren/kaguya) (Boost Software License) (Lua Binding)
- [Lua 5.3](http://lua-users.org/wiki/LuaBinaries) (zlib License) (Scripting language)
- [zlib&minizip](http://www.zlib.net/) (zlib license) (zip archives)
- [tgui](https://github.com/texus/TGUI) (zlib license) (GUI)
- [tinydir](https://github.com/cxong/tinydir) (BSD2 License) (tiny filesystem, soon replaced with C++17's filesystem)
- [Vili](https://github.com/Sygmei/ViliData) (MIT License) (Data language)

## How do I build it ?
If you want to build ÖbEngine yourself (which is perfectly fine), you'll need CMake software.

A CMakeLists.txt is provided in the project.

Just tell CMake where SFML(>= 2.4) is by providing the following CMake entriy (or Environment var) :
- SFML_ROOT (Root of SFML folder where there is include/ and lib/ folders)

Those are compiler requirements :
- If you're on Windows vc14 is required.
- If you're on Linux g++-6 is required.

You'll need a compiler with \<filesystem\> support or at least \<experimental/filesystem\>.

If your compiler doesn't support C++17 filesystem, you can disable CMake entry "USE_CPP_NEW_FS", it will use the fallback instead.

If everything is okay, CMake should generate what you want (Makefiles / VS Project / Something else).

Once ObEngine is built, place the generated executable in engine/ folder.

## Could you give an example of what I can do with your engine ?
Well, you can do approximatively everything with it as long as it's in 2D. ÖbE doesn't handle 3D.
You can do some Platformers, RPGs, 2D racing games, Visual Novels, Roguelikes, Metroidvanias, etc..

## Is it free ?
Of course, you can even sell your game made with the engine, no royalties (If you want to give us some money it's okay though).
You can also modify the sources.
There's no need to write somewhere that your game is made with ÖbE (but it's nice if you do it !)

## Give me some interesting features
Here you go :
- Neat map editor (With a grid for precise map edition)
- Spritesheet animations (with tiny animation language)
- Light system
- Particles
- Lua scripting (Object oriented with a full events system)
- Object-oriented
- Infinite amount of layers with optional parallax
- Mathematical expressions parsing
- Home-made data language
- Polygonal Collisions with full collision detection support
- Developpement console with coloration and scripting support
- Customizable cursor (whoa)
- Serial and Network events support
- Trajectory system (and you can even create your owns)
- DeltaTime handling
- Custom package manager with online repository
- Extendable toolkit with a lot of functionalities
- Gamepad support

## Future features which are also really cool ?
- Normal maps
- 3D objects in 2D scene
- Skeletal animations
- Collaborative map editor
- Better light & particle system
- C++ plugins

## ObEngine's versions

- 0.37 Aurvandil (April 2016) - First usable version of ObEngine
- 0.55 Baldur (June 2016) - Better scripting support
- 0.81 Clue (January 2017) - Big engine rework
- 0.99 Dagr (February 2017) - First released dev version of ObEngine
- 1.0 Eir (Summer 2017) - First public released version

## Right, can I have several object scripting examples now ?
Sure, here are some simple objects :
### Examples using console :
#### Hello-World object
This one is really simple, it just prints "Hello World" in the console (not the game console)
```lua
function Local.Init() -- Called when object is created
  print("Hello World");
end
```
#### Hello-World in game console
Does exactly the same thing than the first one except that it prints "Hello World" in the game console (F1 to open console)
```lua
function Local.Init()
  -- Create a new stream for the console named "HelloWorld", the "true" means the stream is directly enabled
  local consoleStream = Console:createStream("HelloWorld", true);
  -- Write "Hello World" in the game console in red using the stream (5th parameter is alpha)
  consoleStream:write("Hello World", 255, 0, 0, 255);
end
```

#### Rainbow Hello-World
Same thing that the one before except that we will change the color of the text at every frame !
```lua
math.randomseed(os.time()); -- Random seed for when we'll use math.random()

function Local.Init()
  local consoleStream = Console:createStream("HelloWorld", true);
  -- We start with the white color (255, 255, 255), the line is stored in helloWorldMessage
  helloWorldMessage = consoleStream:write("Hello World Rainbow !", 255, 255, 255, 255);
end

function Local.Update() -- This will be called at every frame
  local r = math.random(0, 255); -- Red composant
  local g = math.random(0, 255); -- Green composant
  local b = math.random(0, 255); -- Blue composant
  helloWorldMessage:setColor(r, g, b); -- Change the color of the whole line
end
```
### Examples with LevelSprites
Every LevelObject can have a LevelSprite associated (it's cooler when your object appears in the game right ?).
#### Rotating goat
Let's imagine you want to create a rotating goat in your game, no problem :
```lua
function Local.Init()
  -- Set the animation for when the goat is flying to the right (You can imagine it already right ?)
  This:Animator():setKey("GOAT_FLYING_LEFT");
end

function Local.Update(P) -- P is a table that contains every events parameters (here parameters for update)
  This:LevelSprite():rotate(P.dt * 45); -- Rotate of 45 degrees each second (You multiply with the DeltaTime here)
end
```

### Examples with Colliders
Every LevelObject can also have a Collider (solid or not).

#### A simple door
This is a simple door that you can open or close when you click it

```lua
Door = {} -- You create a table to place Door's function in

function Local.Init()
    This:Animator():setKey("Close");
    opened = false;
end

function Door.Open()
    This:Animator():setKey("Open");
    This:Collider():setSolid(false); -- Makes the character able to pass through the door
    opened = true;
end

function Door.Close()
    This:Animator():setKey("Close");
    This:Collider():setSolid(true); -- Makes the collider solid (no one can pass through)
    opened = false;
end

function Local.Click() -- Called when the object's collider is clicked
    if opened then Door.Close();
    else Door.Open();
    end
end
```

### Drawing stuff
The engine includes a `Canvas` lib to draw stuff in real time and using it is really straightforward !

```lua
function Local.Init()
  canvas = Core.Canvas.new(400, 400); -- Creating a 400x400 canvas
  
  canvas:Rectangle("background"):init({ -- Dark grey background
      layer = 2, x = 0, y = 0, width = 250, height = 100
      color = { r = 50, g = 50, b = 50, a = 255 },
  });

  canvas:Text("fstPlayer"):init({ -- First player's score label
      text = "Player 1 : 0 points", size = 22
  });

  canvas:Text("scdPlayer"):init({ -- Second player's score label
      text = "Player 2 : 0 points", size = 22, y = 50
  });

  canvas:Circle("green"):init({ -- Small green circle
      color = { r = 0, g = 255, b = 0, a = 255 }, -- Green color
      radius = 7, x = 200, y = 5
  });

  canvas:Circle("yellow"):init({ -- Small yellow circle
      color = { r = 255, g = 255, b = 0, a = 255 }, -- Yellow color
      radius = 7, x = 217, y = 5
  });

  canvas:Circle("red"):init({ -- Small red circle
      color = { r = 255, g = 0, b = 0, a = 255 }, -- Red color
      radius = 7, x = 234, y = 5
  });
  
  canvas:target(This:LevelSprite()); -- Canvas result will render in object's LevelSprite
  canvas:render(); -- Drawing all the stuff !
end
```
