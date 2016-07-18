# Melting Saga Engine

## What the hell is Melting Saga Engine ?
Melting Saga Engine (MSE is shorter) is a 2D Game Engine made on the top of SFML !

## What do I need to build it ?
You will need several libs :
- [SFML 2.3](http://www.sfml-dev.org/download/sfml/2.3/index-fr.php) (Display, Keys, Network, and much more)
- [Kaguya](https://github.com/satoren/kaguya) (Lua Binding)
- [Lua 5.3](http://lua-users.org/wiki/LuaBinaries) (Scripting language)
- [ClipperLib](https://sourceforge.net/projects/polyclipping/files/) (Polygonal Intersection Resolution)

## Could you give an example of what I can do with your engine ?
Well, you can do approximatively everything with it as long as it's in 2D. MSE doesn't handle 3D.
You can do some Platformers, RPGs, 2D racing games, Visual Novels, Roguelikes, Metroidvanias, etc..

## Is it free ?
Of course, you can even sell your game made with the engine, no royalties (If you want to give us some money it's okay though).
You can also modify the sources.
There's no need to write somewhere that your game is made with MSE (but it's nice if you do it !)

## Give me some interesting features
Here you go :
- Neat map editor (With a grid for precise map edition)
- Spritesheet animations (with tiny animation language)
- Skeletal animations (Planned)
- Light system
- Particles
- Normal maps (Planned)
- Lua scripting (Object oriented with a full events system)
- Object-oriented
- VisualNovel system included
- Infinite amount of layers with optional parallax
- Mathematical expressions parsing
- Home-made data language
- Polygonal Collisions with full collision detection support
- Developpement console with coloration and scripting support
- Customizable cursor (whoa)
- Serial and Network events support
- Trajectory system (and you can even create your owns)

## Right, can I have several object examples now ?
Sure, here are some simple objects :
### Examples using console :
#### Hello-World object
This one is really simple, it just prints "Hello World" in the console (not the game console)
```lua
This:useLocalTrigger("Init"); -- Tells the engine that this object will execute Local.Init when created

function Local.Init() -- Called when object is created
  print("Hello World");
end
```
#### Hello-World is game console
Does exactly the same thing than the first one except that it prints "Hello World" is the game console (F1 to open console)
```lua
Import("Core.Console") -- Import Console API from C++

GetHook("Console"); -- Place the Game's Console pointer in Hook.Console

This:useLocalTrigger("Init");

function Local.Init()
  -- Create a new stream for the console named "HelloWorld"
  local consoleStream = Hook.Console:createStream("HelloWorld", true);
  -- Write "Hello World" in the game console in red using the stream
  consoleStream:write("Hello World", 255, 0, 0, 255);
end
```

#### Rainbow Hello-World


Please check https://www.meltingsaga.xyz/doc/doc.php for some documentation.
