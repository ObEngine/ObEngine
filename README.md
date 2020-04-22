# ![ÖbEngine](https://raw.githubusercontent.com/Sygmei/ObWiki/master/banner.png)

[![Discord](https://img.shields.io/discord/302123079818149888.svg?style=for-the-badge&logo=discord)](https://discordapp.com/invite/HkM6zdT)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg?style=for-the-badge)](https://raw.githubusercontent.com/Sygmei/ObEngine/master/license)
[![Github All Releases](https://img.shields.io/github/downloads/sygmei/obengine/total.svg?style=for-the-badge)](https://github.com/Sygmei/ObEngine/releases)
[![Codacy Badge](https://img.shields.io/codacy/grade/81846da629d244f69f357568a2f8d690.svg?style=for-the-badge)](https://www.codacy.com/app/Sygmei/ObEngine?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Sygmei/ObEngine&amp;utm_campaign=Badge_Grade)

## CI/CD status

| CI/CD name  | Build status |
| ----------- | ------------ |
| Travis      | [![Build Status](https://img.shields.io/travis/Sygmei/ObEngine.svg?style=for-the-badge&logo=travis)](https://travis-ci.org/Sygmei/ObEngine) |
| AppVeyor    | [![Build status](https://img.shields.io/appveyor/ci/Sygmei/ObEngine.svg?style=for-the-badge&logo=appveyor)](https://ci.appveyor.com/project/Sygmei/obengine) |
| Azure Pipelines | [![Build Status](https://img.shields.io/azure-devops/build/obengine/d879c6ea-1ed9-4984-b3d1-84c5dd9b8feb/1.svg?style=for-the-badge&logo=microsoft-azure)](https://dev.azure.com/obengine/%C3%96bEngine) |

## Useful links

- [ÖbEngine's Wiki](https://github.com/Sygmei/ObEngine/wiki)
- [ÖbEngine's Website](https://www.obengine.io)
- [ÖbEngine's Documentation](https://www.obengine.io/doc.html)
- [ÖbEngine's Discord](https://discord.gg/HkM6zdT)
- [ÖbEngine's Development Boards](https://github.com/Sygmei/ObEngine/projects)

## What the hell is ÖbEngine ?
ÖbEngine (ÖbE is shorter) is a 2D Game Engine made on top of SFML ! I'm creating this engine in my spare time, it might not be really stable right now but I'm working on it.

## What do I need to build it ?
You will need SFML :
- [SFML 2.5.1](https://www.sfml-dev.org/download/sfml/2.5.1/index-fr.php) (Display, Input, Network, Sound and much more)

There are other libraries but they are included in the repository (extlibs/ folder) :

### Bundled dependencies

|Library|Description|License|
|-------|-----------|-------|
|[11zip](https://github.com/Sygmei/11Zip)|minizip wrapper based on [Vili Petek's work](http://www.vilipetek.com/2013/11/22/zippingunzipping-files-in-c/)|MIT License|
|[Catch2](https://github.com/catchorg/Catch2)|Test Framework|Boost Software License|
|[dynamicLinker](https://github.com/Marqin/dynamicLinker)|Dynamic Libs wrapper|MIT License|
|[fmt](https://github.com/fmtlib/fmt)|Formatting library|BSD 2-Clause "Simplified" License|
|[Sol](https://github.com/ThePhD/sol)|C++ binding library to Lua|MIT License|
|[Lua 5.3](http://lua-users.org/wiki/LuaBinaries)|Scripting language|zlib License|
|[RichText](https://github.com/Skyrpex/RichText)|sf::Text extension|MIT License|
|[spdlog](https://github.com/gabime/spdlog)|Logging library|MIT License|
|[Vili](https://github.com/Sygmei/ViliData)|Homemade Data language (YAML-like)|MIT License|
|[zlib & minizip](http://www.zlib.net/)|zip archives|zlib license|

## How do I build it ?
Check the following tutorial : [Building ÖbEngine](https://github.com/Sygmei/ObEngine/wiki/Building-ObEngine)

## Could you give an example of what I can do with your engine ?
Well, you can do approximatively everything with it as long as it's in 2D. ÖbEngine doesn't handle 3D (maybe partial 3D support in a future update).
You can do some platformers, RPGs, 2D racing games, visual novels, roguelikes, metroidvanias, etc..

If you want to check out games made with ÖbEngine, you can check out those [:eggplant:**open-source projects**:eggplant:](https://github.com/Sygmei/ObEngineExamples) !

## Is it free ?
Of course, you can even sell your game made with the engine, no royalties (If you want to give us some money it's okay though).
You can also modify the sources.
There's no need to write somewhere that your game is made with ÖbEngine (but it's nice if you do it !).
The engine is MIT licensed so you're free to do whatever you want with the engine.

## On which platforms can I export my game made with ÖbEngine ?

ÖbEngine has been tested on the following platforms :
- Windows XP, 7, 8, 10
- Linux (Debian, Arch)
- MacOS

ÖbEngine will have export for Android, iOS and HTML5 available in a future update.

## Give me some interesting features
Here you go :
- Neat map editor (With a grid for precise map edition)
- Animations
- Native plugins (You can extend the engine with C++)
- Canvas (You can draw stuff using a simple API)
- Network support
- Scriptable GameObjects
- Workspaces and Packages system
- Lua scripting
- Layering system
- Parallax
- Home-made data language (Vili)
- Polygonal Collisions with full collision detection support
- Developpement console with coloration and scripting support
- Custom package manager with online repository
- Extendable toolkit with a lot of functionalities
- Gamepad support

## Future features which are also really cool ?
- Normal maps
- 3D objects in 2D scene
- Skeletal animations
- Collaborative map editor
- Light & particle system
- C++ GameObjects
- Multiple windows
- Android, iOS and HTML5 export
- Tiled Map Editor support

## ObEngine's versions

Each major release will have a name based on a translation of the word "Eggplant".

ÖbEngine just follows [semver rules](https://semver.org/) which means any version will be tagged (X.Y.Z) with X: Major, Y: Minor and Z: Patch.

### Pre-alpha versions
|Version number|Version name|Word origin|Release date|Description|
|--------------|------------|-----------|------------|-----------|
|1.0.0|Melanzana|Italian|?|First production release of ÖbEngine|

## Right, can I see how does scripting looks ?
Sure, here are some simple GameObjects :
### Examples using console :
#### Hello-World object
This one is really simple, it just prints "Hello World" in the console (not the game console)
```lua
function Local.Init() -- Called when object is created
  print("Hello World");
end
```
### Examples with Sprites
Every GameObject can have a Sprite associated (it's cooler when your object appears in the game right ?).
#### Rotating goat
Let's imagine you want to create a rotating goat in your game, no problem :
```lua
function Local.Init()
  -- Set the animation for when the goat is flying to the right (You can imagine it already right ?)
  This:Animator():setKey("GOAT_FLYING_LEFT");
end

function Local.Update(dt) -- Local.Update is a function called every loop and dt is the DeltaTime
  This:Sprite():rotate(dt * 45); -- Rotate of 45 degrees each second (You multiply with the DeltaTime here)
end
```

### Drawing stuff
The engine includes a `Canvas` lib to draw stuff in real time and using it is really straightforward !

```lua
function Local.Init()
  canvas = obe.Canvas.Canvas(400, 400); -- Creating a 400x400 canvas

  canvas:Rectangle("background")({ -- Dark grey background
      layer = 2, x = 0, y = 0, width = 250, height = 100,
      color = { r = 50, g = 50, b = 50},
  });

  canvas:Text("fstPlayer")({ -- First player's score label
      text = "Player 1 : 0 points", size = 22
  });

  canvas:Text("scdPlayer")({ -- Second player's score label
      text = "Player 2 : 0 points", size = 22, y = 50
  });

  canvas:Circle("green")({ -- Small green circle
      color = "0F0", -- Green color
      radius = 7, x = 200, y = 5
  });

  canvas:Circle("yellow")({ -- Small yellow circle
      color = "FF0", -- Yellow color
      radius = 7, x = 217, y = 5
  });

  canvas:Circle("red")({ -- Small red circle
      color = "F00", -- Red color
      radius = 7, x = 234, y = 5
  });

  canvas:setTarget(This:Sprite()); -- Canvas result will render in object's Sprite
  canvas:render(); -- Drawing all the stuff !
end
```

Check the Wiki for more examples !

## Contributors / Thanks

<table>
  <tr>
    <td align="center"><a href="https://github.com/Sygmei"><img src="https://avatars1.githubusercontent.com/u/3835355?v=4" width="100px;" alt="Sygmei"/><br /><sub><b>Sygmei</b></sub></a><br /><a href="https://github.com/Sygmei/ObEngine/commits?author=Sygmei" title="Creator / Code">✍️💻</a></td>
    <td align="center"><a href="https://github.com/PierrickLP"><img src="https://avatars1.githubusercontent.com/u/19671805?v=4" width="100px;" alt="PierrickLP"/><br /><sub><b>PierrickLP</b></sub></a><br /><a href="https://github.com/Sygmei/ObEngine/commits?author=PierrickLP" title="Code">💻</a></td>
    <td align="center"><a href="https://github.com/Skealz"><img src="https://avatars3.githubusercontent.com/u/11155537?v=4" width="100px;" alt="Skealz"/><br /><sub><b>Skealz</b></sub></a><br /><a href="https://github.com/Sygmei/ObEngine/commits?author=Skealz" title="Code">💻</a></td>
    <td align="center"><a href="https://github.com/TeddyTrqt"><img src="https://avatars3.githubusercontent.com/u/25806305?v=4" width="100px;" alt="TeddyTrqt"/><br /><sub><b>TeddyTrqt</b></sub></a><br /><a href="https://github.com/Sygmei/ObEngine/commits?author=TeddyTrqt" title="Code">💻</a></td>
    <td align="center"><a href="https://github.com/Arthapz"><img src="https://avatars1.githubusercontent.com/u/27437334?v=4" width="100px;" alt="Arthapz"/><br /><sub><b>Arthapz</b></sub></a><br /><a href="https://github.com/Sygmei/ObEngine/commits?author=Arthapz" title="Help / Code">💡💻</a></td>
    <td align="center"><a href="#"><img src="https://cdn.discordapp.com/avatars/182580990068129793/900bed68729180a0076fd1a22b548139.png?size=128" width="100px;" alt="LePatissier"/><br /><sub><b>LePatissier</b></sub></a><br /><a href="https://github.com/Sygmei/ObEngine/commits?author=LePatissier" title="Code">💻</a></td>
    <td align="center"><a href="https://github.com/Tzupy"><img src="https://avatars0.githubusercontent.com/u/12645020?v=4" width="100px;" alt="Tzupy"/><br /><sub><b>Tzupy</b></sub></a><br /><a href="https://github.com/Sygmei/ObEngine/commits?author=Tzupy" title="Code">💻</a></td>
  </tr>
  <tr>
    <td align="center"><a href="https://github.com/mjopenglsdl"><img src="https://avatars1.githubusercontent.com/u/3438296?s=460&v=4" width="100px;" alt="mjopenglsdl"/><br /><sub><b>mjopenglsdl</b></sub></a><br /><a href="https://github.com/Sygmei/ObEngine/commits?author=mjopenglsdl" title="Code">💻</a></td>
    <td align="center"><a href="https://github.com/julio-b"><img src="https://avatars1.githubusercontent.com/u/16379308?v=4" width="100px;" alt="julio-b"/><br /><sub><b>julio-b</b></sub></a><br /><a href="https://github.com/Sygmei/ObEngine/commits?author=julio-b" title="Code">💻</a></td>
    <td align="center"><a href="https://github.com/ZanyMonk"><img src="https://avatars2.githubusercontent.com/u/3920186?v=4" width="100px;" alt="ZanyMonk"/><br /><sub><b>ZanyMonk</b></sub></a><br /><a href="https://github.com/Sygmei/ObEngine/commits?author=ZanyMonk" title="Code">💻</a></td>
  </tr>
</table>

## Sponsors

A big special thanks to my sponsors who are allowing me to spend more time on this project !

### Companies
<table>
  <tr>
    <td align="center"><a href="https://github.com/"><img src="https://github.githubassets.com/images/modules/logos_page/GitHub-Mark.png" width="100px;" alt="GitHub"/><br /><sub><b>GitHub</b></sub></a><br /><a href="https://github.com/" title="Sponsor">:heart::octocat:</a></td>
    <td align="center"><a href="https://www.jetbrains.com/"><img src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/1a/JetBrains_Logo_2016.svg/1200px-JetBrains_Logo_2016.svg.png" width="100px;" alt="JetBrains"/><br /><sub><b>JetBrains</b></sub></a><br /><a href="https://www.jetbrains.com" title="Sponsor">:heart:🧠</a></td>
    <td align="center"><a href="https://www.digitalocean.com/"><img src="https://opensource.nyc3.cdn.digitaloceanspaces.com/attribution/assets/SVG/DO_Logo_vertical_blue.svg" width="100px;" alt="DigitalOcean"/><br /><sub><b>DigitalOcean</b></sub></a><br /><a href="https://www.digitalocean.com/" title="Sponsor">:heart::shark:</a></td>
    <td align="center"><a href="https://www.viva64.com/en/pvs-studio/"><img src="https://www.viva64.com/media/img/logo.png" alt="PVS-Studio"/><br /><sub><b>Viva64</b></sub></a><br /><a href="https://www.viva64.com/en/pvs-studio/" title="Sponsor">:heart:🦄</a></td>
  </tr>
</table>


### Individuals
<table>
  <tr>
    <td align="center"><a href="https://github.com/Mari0nv"><img src="https://avatars3.githubusercontent.com/u/23618241?s=400&v=4" width="100px;" alt="Mari0nV"/><br /><sub><b>Mari0nV</b></sub></a><br /><a href="https://github.com/Mari0nv" title="Sponsor">:heart::heart:</a></td>
    <td align="center"><a href="https://github.com/GuillaumeCailhe"><img src="https://avatars0.githubusercontent.com/u/1500051?s=400&v=4" width="100px;" alt="GuillaumeCailhe"/><br /><sub><b>GuillaumeCailhe</b></sub></a><br /><a href="https://github.com/Sygmei/GuillaumeCailhe" title="Sponsor">:heart:🍆</a></td>
    <td align="center"><a href="https://github.com/Uriopass"><img src="https://avatars3.githubusercontent.com/u/5420739?s=460&v=4" width="100px;" alt="Uriopass"/><br /><sub><b>Uriopass</b></sub></a><br /><a href="https://github.com/Uriopass" title="Sponsor">:heart:🚗</a></td>
    <td align="center"><a href="https://github.com/Nowyce"><img src="https://avatars2.githubusercontent.com/u/1354475?s=460&v=4" width="100px;" alt="Nowyce"/><br /><sub><b>Nowyce</b></sub></a><br /><a href="https://github.com/Nowyce" title="Sponsor">:heart:🎃</a></td>
  </tr>
</table>

