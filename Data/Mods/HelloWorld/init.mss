[::]Include(self, "ModTools")
[::]Include(self, "Event")
[::]Octopus(self, "eventDB", "eventDB")

var mod = NewMod()

//Mod Informations
mod.setTitle("HelloWorld")
mod.setDescription("A Simple Hello World Mod")
mod.setIcon("icon")

//Script Loading
mod.loadScr("Scr/helloworld.mss", "helloworld")
//Ressources Loading
mod.loadRes("Res/icon.png", "icon")

//Triggers Creation
eventDB.addTrigger("GameLoaded", mod.getScr("helloworld"))

//Build Mod
mod.build()
RegisterMod(mod)