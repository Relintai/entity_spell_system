# Entity Spell System

An entity and spell system for the GODOT Engine, that is usable for both 2d, and 3d games. The main purpose of this 
module is to handle spells, auras, and most entity-related things like spawning, items, inventory, contaiers, 
vendors, interaction, targeting, equipment (+ visuals), loot, crafting, talents, pets, npcs, etc ...

The module supports networking. It is designed to be authoritative, so players shouldn't be able to cheat by design.

It is a c++ engine module, which means you will need to compile it into godot. (See compiling)

It supports both godot 3.2 and 4.0 (master). Note that since 4.0 is still in very early stages I only 
check whether it works from time to time.

## Project setup tl;dr

You need to create an `ESSResourceDB`, and an `ESSEntitySpawner` resource somewhere in you project.

Now you can either go to `ProjectSettings->Ess->Data`, and set the `ess_resource_db_path`, and the 
`ess_entity_spawner_path` properties and then tick `automatic_load`,

or you can load them yourself and set them into the `ESS` singleton either using 
`void setup(resource_db: ESSResourceDB, entity_spawner: ESSEntitySpawner)` or the `entity_spawner` and 
`resource_db` properties.

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

The module contians 2 singletons. `ESS`, and `ProfileManager`. Both are accessible from scripts.

### The ESS singleton

Contains the active `ESSResourceDB` instance, and the active `ESSEntitySpawner` instance, and also 
loads/handles/processes all of the entity and spell system related ProjectSettings, so if you need
any ESS related value from ProjectSettings, don't query it directly, get it from this singleton.

Customizable enums values are preprocessed, and you usually have multiple ways of getting them.

### The ProfileManager singleton

Contains methods to easily load/save/handle `PlayerProfile`s.

#### PlayerProfile

Contains player-related data, most notably `ClassProfile`s.

#### ClassProfile

Contains class-related data, most notably `ActionBarProfile`s, and `InputProfiles`.

#### ActionBarProfile

Contains the data for a set of actionbars.

#### InputProfileswd

Contains the keybind data for a class.

## Enums

ESS needs lots of enums to work, and to reduce complexity with includes they ended up in a few separate classes.

I'm still in the process of converting these to be customizable (`ESS` singleton / ProjectSettings).

(Only the ones that worth it will be converted.)

### EntityEnums

Constains Entity-reloated enums, like AIStates, skeleton attach points, entity flags, immunity flags,
state flags.

### ItemEnums

Contains item-related enums, like rarity, armor type, item types.

### SpellEnums

Contains spell-related enums, like aura types, damage types, spell categories, spell types, trigger types, 
and quite a few notification constants.

### Customizable enums

Open `ProjectSettings`, and then go to `ESS/Enums`.

All of the string properties are customizable enums. These require a comma-separated list.
They are essentially a godot comma separated property hint enum string.

They all have defaults.

Fer example:

If you want you game to work with the following stats: Agility,Intellect,Crit,Weapon Damage,Stamina
and you want Agility,Intellect,Stamina as you main stats.

Firstly you want to put you main stats at the beginning, because the system will take the first `main_stat_count` 
stats as main stats.

And then just enter `Agility,Intellect,Stamina,Crit,Weapon Damage` into the `stats` setting, and then 
set `main_stat_count` to 3.

When these values are expected to be used as properties, the `ESS` singleton will create snace_cased versions automatically.
`String stat_get_property_name(id: int) const` inside the ESS singleton for example.

So in the example case `ESS.stat_get_property_name(4)` would return `weapon_damage`.

## ESSResourceDB

This is a class that maps ids to resources for quick lookups.
This is necessary in order to support networking, because you don't want to send resource paths over the network 
every time somebody casts a spell for example. 

### Subclasses...

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

You can implement your spawning logic by inheriting from `ESSEntitySpawner`, and implementing `_request_entity_spawn`.

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

#### EntityClassData

`EntityClassData` holds class-related information, like specs (`CharacterSpec`), spells, start spells, start auras, 
alternative ais, `EntityResource`s (mana for example).

#### CharacterSpec

`CharacterSpec` holds spec-related information, most notably talents.

#### EntityResource

##### EntityResourceHealth

##### EntityResourceSpeed

#### EntityResourceCost

### AI

You can implement ai by extending `EntityAI`, and then assigning it to an EntityData.

When an `Entity` gets spawned it will create a copy for itself, so you can safely use class variables.

#### AIFormation

Not yet finished, it was meant as a way to calculate offset pet positions, (If an `Entity` has let's say 
4 pets you don't just want them all to stay on top of their controller).

If this functionality ends up in `EntityAI`, after pets are finished, this will be removed.

### Pets

Unfortunately pet support is not yet finished.

It is mostly done though, so you will see pet-related methods scattered around.

### Bags

Stores items. See `Bag`. It has aquite a few virtual methods, you should be able to implement most inventory types
should you want to.

Entity will send these over the network.

Also Entities have a target bag property. For example this makes vendors easily implementable.

### EntitySpeciesData

Contains data related to a species, like `SpeciesModelData`s, and species specific spells, and auras.

#### SpeciesModelData

Contains a scene of a species's body and it's customizations.

The `customizable_slots_string` and `customizable_colors_string` should be filled with a comma separated string,
they will add properties. Currently you need to click on something else, and back on the resource for these to show up,
after a change to the strings.

The body can be any scene, Entity will instance it, and set it to it's body property.

The body should handle movement based on the player's input, it should handle sending position information through the network, 
if you want networking, it might (`CharacterSkeleton`s can also do it) also drive your animations/animation players if you have it.

Bodies does not need to handle the graphics themselves (`ModelVisualEntries` for example) (you can implement your logic here 
if you want to), but the `CharacterSkeleton` classes exist for that purpose.

[Complex 3d body script](https://github.com/Relintai/broken_seals/blob/master/game/player/Body.gd) \
[Complex 3d body scene](https://github.com/Relintai/broken_seals/blob/master/game/modules/species/Human/models/HumanFemale.tscn)

[Simple 2d roguelike body script](https://github.com/Relintai/broken_seals_roguelike/blob/master/game/player/Body.gd) \
[Simple 2d roguelike body scene](https://github.com/Relintai/broken_seals_roguelike/blob/master/game/player/Body.gd)

#### SpeciesInstance

This class will handle 

### CharacterSkeletons

CharacterSkeletons handle the looks of your characters.

They come in two variants, one for 2d, one for 3d.

They have quite a few helper methods.

They can store ModelVisuals, and ModelVisualEntries.

They support attach points. For example a character's hand.
It adds properties based on the selected entity_type.
These are based on the values from `ProjectSettings->ESS->Enums->skeletons_bone_attachment_points`.

If you want to merge meshes this is where you can implement it.

#### CharacterSkeleton3D

The 3d variant.

[Complex 3d skeleton scene](https://github.com/Relintai/broken_seals/blob/master/game/modules/species/Human/models/armature_huf.tscn) \
[Complex 3d skeleton script](https://github.com/Relintai/broken_seals/blob/master/game/player/CharacterSkeletonGD.gd)

#### CharacterSkeleton2D

The 2d variant.

[Simple 2d roguelike skeleton script](https://github.com/Relintai/broken_seals_roguelike/blob/master/game/characters/SimpleCharacter.gd) \
[Simple 2d roguelike skeleton scene](https://github.com/Relintai/broken_seals_roguelike/blob/master/game/characters/SimpleCharacter.tscn)

#### ModelVisuals

##### ModelVisualEntries

#### Attachments

### VRPCs

Entities has a networked visibility system. The method itself is called `vrpc`, it works the same way as normal rpcs.
If you want to send data to every client that sees the current entity, use this. 

## Spells, Auras, Talents

Spell is the class you need to create spells, it stores the data, and also it has the ability to be scripted.

Aura is also built the same way as spells.

Talents are actually just Auras.

Talent ranks are implemented by deapplying the earlier rank, then applying the new rank.

### How to

Request casting a spell clientside: `void spell_crequest_cast(spell_id: int)`
Request to learn a spell clientside: `void spell_learn_requestc(id: int)`

Request talent learning clientside:
`void character_talent_crequest_learn(spec_index: int, character_talent_row: int, character_talent_culomn: int)` or
`void class_talent_crequest_learn(spec_index: int, class_talent_row: int, class_talent_culomn: int)` 

Apply an aura:

Note that you should only apply auras serverside, they will be sent to clients automatically.

```
# Or get it from the active ESSResourceDB, etc
export(Aura) var aura : Aura

func sapply_aura() -> void:
    var ainfo : AuraApplyInfo = AuraApplyInfo.new()
            
    ainfo.caster = info.caster
    ainfo.target = info.caster
    ainfo.spell_scale = 1
    ainfo.aura = aura

    aura.sapply(ainfo)

```

[Complete UI Implemetation](https://github.com/Relintai/broken_seals/tree/master/game/ui/player_ui) \
[Talent UI Implemetation](https://github.com/Relintai/broken_seals/tree/master/game/ui/talents) \
[Spellbook UI Implementation](https://github.com/Relintai/broken_seals/tree/master/game/ui/spellbook) 

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

## Implementing...

### Vendors

#### Limited vendor inventory items 

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
