# Entity Spell System

An entity and spell system for the GODOT Engine.

The actual player, mob etc implementations are still in the main game's repository (https://github.com/Relintai/broken_seals). (As GDScript)
Also there is a data editor addon for this module. The main game should have it.

This module have dependencies to some of my other engine modules, these will be made optional later, for now you will need to install them as well.

The main class that can be used for players/mobs is Entity. I ended up merging subclass functionality into it, because
that way it gains a lot more utility, by sacrificing only a small amount of memory.

For example this way it is easy to make chests attack the player, or make spell that animate objects.

Spell is the class you need to create spells, it stores the data, and also it has the ability to be scripted.

Aura is also built the same way.

The module provides a huge number of script callbacks, usually as vmethods.

The main data class is EntityData. You will need this to properly initialize an entity.

The module can do multiplayer, but it's not finished, and at the moment not safe to use. It should mostly work though.
Also it supports entity visibility. If you need rpcs that use this, use vrpc. (Implemented inside Entity).

Every variable is broken up into clientside, and serverside ones, when applicable. This makes it easy to 
develop games, that can also run locally, with less overhead. And simpler logic. 
E.g. this makes it easy to use the visibility system even on the server, because you just use the clientside variables,
and the logic will work the same way.

Right now everything wokrs authoritatively, except for movement. FYI Movement is handled in GDScript int the game's repo right now.
(I plan to implement authoritative movement later.)

Everything is called the remotesync way, but instead of remotesync, I have c++ macros, which sends the rpc, and then calls the given function directly aswell.

For usage check the main game's repo.

## 2D games

The modules uses 3D by default, however it can be compiled to work with 2D games, you need to add `entities_2d=yes` to your scons command.

For example

```scons -j2 platform=x11 target=release_debug entities_2d=yes```

