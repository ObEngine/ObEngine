# Contributing to ObEngine

Hey you ! Interested in participating in the development of ObEngine ? Great !

## Asking Questions

If you want to discuss about the engine or contribute to it, 
I strongly suggest you to come in our friendly discord Server, 
here's an invitation URL, feel free to come anytime !

https://discord.gg/HkM6zdT

## Contributors

Right now I [Sygmei](https://github.com/Sygmei) work mostly alone on the project but I got a lot of help from various people 
(See "Thanks" category).

## Main files (what to check first)

- Animation : All the stuff to animate sprites in there
- Camera : The camera of the scene
- Collisions : Handles collisions / Polygonal Colliders
- Coordinates : All the coordinates operations in there
- FramerateManager : Handles time / deltatime / framerate
- Game : Plays the game
- GameObject : An Object that can contains those components : Animator, Sprite, PolygonalCollider, Script
- KeyBind : Associates keys with actions
- Sprite : Primitive drawable element
- ObEngine : main function inside
- Package & Workspace : Pretty much the same thing, works with the PathResolver
- PathResolver : Really important class that "mounts" (see wiki) folders
- Scene : Scene-like container
- Script : All the Lua binding stuff in there
- Toolkit : Nice terminal to help with project management
- Triggers : Triggers / Events for the GameObjects

## How can I contribute

### Reporting bugs

If you test the engine and encounter a bug, you can : 
- Check if the issue doesn't already exist on github
- Report it on Github (Specify OS, compiler if you compiled it yourself, version of the engine)
- Discuss it on the Discord (#issues channel)

### Ask for new features

If you feel like there is a missing feature come and discuss it with us on the Discord (#features channel)

### Create new features yourself

You're an adventurer ? Nice ! If you developped something for the engine you can do a pull request, 
I'll try to validate it quickly if everything is in order :)

### Help on `help wanted` issues

You can find all the issues I need help on right there : [Issues `help wanted`](https://github.com/Sygmei/ObEngine/issues?q=is%3Aopen+is%3Aissue+label%3A%22help+wanted%22)
