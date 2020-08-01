# Entity Spell System

An entity and spell system for the GODOT Engine, that is usable for both 2d, and 3d games. The main purpose of this 
module is to handle spells, auras, and most entity-related things like spawning, items, inventory, contaiers, 
vendors, interaction, targeting, equipment (+ visuals), loot, crafting, talents, pets, npcs, etc ...

The module supports networking. It is designed to be authoritative, so players shouldn't be able to cheat by design.

It is a c++ engine module, which means you will need to compile it into godot. (See compiling)

It supports both godot 3.2 and 4.0 (master). Note that since 4.0 is still in very early stages I only 
check whether it works from time to time.

### What the module doesn't cover

Movement, and controls.

Unfortunately, there isn't a one-stop-shop solution for movement, especially if we throw networking into the mix,
and the same is true for targeting. This means that this module cannot really do much in this regard, but it will 
give you as much help to set everything up as possible.

## Optional Dependencies

Mesh Data Resource

https://github.com/Relintai/mesh_data_resource.git

Adds mesh support to ModelVisuals. This is exists because in gles2 mesh data cannot be accessed directly from ArrayMeshes.

## Pre-built binaries

You can grab a pre-built editor binary from the [Broken Seals](https://github.com/Relintai/broken_seals/releases) 
repo, should you want to. It contains all my modules.

## Overview

The module provides a huge number of script callbacks, usually as virtual methods they usually start with an underscore.

Do not call methods with underscores, all of them has a normal counterpart, always call that.

For example entity has `crafts(int id)` and `_crafts(int id)` (virtual). Always use `crafts(int id)`, it will
call `_crafts(int id)`.

For networked classes, every variable is broken up into clientside, and serverside. This makes it easier to 
develop games that can also run locally, with less overhead and simpler logic. 
E.g. this makes it easy to use the visibility system even when you play locally on the server, because you just use the clientside variables,
and your logic will work the same way.

## Settings

## Singletons

## Enums

### Customizable enums

## ResourceDB

### ResourceDB Classes

## Entity

This is the main class that can be used for players/mobs/npcs and also other things like chests. 

I ended up merging subclass functionality into it, because
that way it gains a lot more utility, by sacrificing only a small amount of memory.
For example this way it is easy to make chests attack the player, or make spell that animate objects.

## Entity Body

model index

### EntitySkeleton

### Spawning

Since spawning (= creating) entities is entirely dependant on the type of game you are making, ESS cannot do
everything for you. It will set up stats, equipment etc, but there is no way to set up positions for example.

You can implement your spawning logic by inheriting from ESSEntitySpawner, and implementing `_request_entity_spawn`.

You will need to register this spawner into the ESS singleton, either by using `setup(resource_db, entity_spawner)`, or 
by using the provided property/setter `entity_spawner`/`set_entity_spawner()`. 

The ESS singleton also contains convenience methods to request spawning an Entity.

#### EntityCreateInfo

Entity spawning usually requires a lot of complexity and hassle, this helper class aims to make it painless.

All methods that deal with spawning will take this as a parameter.

### EntityData

Since setting up Entities as scenes is usually quite the hassle, `EntityData` had to be created.

It stores everything an entity needs.

In order to spawn an entity you need it.

### Vendors

#### Limited vendor inventory items 

### AI

You can implement ai by extending `EntityAI`, and then assigning it to an EntityData.

When an `Entity` gets spawned it will create a copy for itself, so you can safely use class variables.

### Pets

### Bags

Stores item. See `Bag`. It has aquite a few virtual methods, you should be able to implement most inventory types
should you want to.

Entity will send these over the network.

Also Entities have a target bag property. For example this makes vendors easily implementable.

### SpeciesInstance

### CharacterSkeletons

#### Visuals

#### Attachments

#### ItemVisuals

### VRPCs

Entities has a networked visibility system. The method itself is called `vrpc`, it works the same way as normal rpcs.
If you want to send data to every client that sees the current entity, use this. 

## Spells, Auras

Spell is the class you need to create spells, it stores the data, and also it has the ability to be scripted.

Aura is also built the same way as spells.

### Talents

### Infos / Pipelines

SpellCastInfo

Stores information about the state of a spell's cast.

AuraApplyInfo

Helps to apply auras

SpellDamageInfo, SpellHealInfo

These are used in the damage and heal calculation. For example these can be used to implement immunities, or absorb effects 
by modifying their damage values in aura callbacks.

### Projectiles

## Items

### Loot

## XP

After you set 

## Profiles

## Examples

Eventually I'll create a separate repository with a few examples/demos, but for now you can check the game 
I've been working on for examples.

3d:
https://github.com/Relintai/broken_seals.git

2d turn based:
https://github.com/Relintai/broken_seals_roguelike

2d: 
https://github.com/Relintai/broken_seals_2d.git

## Compiling

First make sure that you can compile godot. See the official docs: https://docs.godotengine.org/en/3.2/development/compiling/index.html

1. Clone the engine if you haven't already:

If you want Godot 3.2:
```git clone -b 3.2 https://github.com/godotengine/godot.git godot```

If you want Godot 4.0:
```git clone https://github.com/godotengine/godot.git godot```

2. go into the modules folder inside the engine's directory"

```cd godot```
```cd modules```

3. clone this repository

```git clone https://github.com/Relintai/entity_spell_system.git entity_spell_system```

(the folder needs to be named entity_spell_system!)

4. Go up one folder

```cd ..```

5. Compile godot.

For example:

```scons p=x11 t=release_debug tools=yes```
