# Entity Spell System

An entity and spell system for the GODOT Engine, that is usable for both 2d, and 3d games. The main purpose of this 
module is to handle spells, auras, and most entity-related things like spawning, items, inventory, containers, 
vendors, interaction, targeting, equipment (+ visuals), loot, crafting, talents, pets, npcs, etc ...

The module supports networking. It is designed to be authoritative, so players shouldn't be able to cheat by design.

It is a c++ engine module, which means you will need to compile it into godot. (See compiling)

## Godot Version Support

This module is developed with the 3.x branch of godot, usually at the newest revisions.

3.2 - Will likely work, probably needs changes by now. (TODO check.)\
3.3 - Will more likely work, might need smaller changes by now. (TODO check.)\
3.4 - Should work without any issues. (TODO check.)\
3.x - Works.\
4.0 - Have been fixing support from time to time. Currently it won't build on the latest master, and it will take considerable amount of work to get it to work again after the virtual method binding rework. It will be done eventually, but it will take time. [Here](https://github.com/godotengine/godot/commit/b7e10141197fdd9b0dbc4cfa7890329510d36540)'s the last know-to-work commit.

## Project setup tl;dr

### First 

You need to create an `ESSResourceDB` resource somewhere in you project. (Or alloocate it dynamically.)

Now you can either:

-Go to `ProjectSettings->Ess->Data`, and set the `ess_resource_db_path` property also make sure that `automatic_load` is on.

-Or you can load it yourself and set it into the `ESS` singleton either using the `resource_db` property.

### Second

You need to add an `ESSEntitySpawner` somewhere into your SceneTree. I recommend that you create an autoload for it.
This is where you have to implement your spawning logic.

### What the module doesn't cover

Movement, and controls.

Unfortunately, there isn't a one-stop-shop solution for movement, especially if we throw networking into the mix,
and the same is true for targeting. This means that this module cannot really do much in this regard, but it will 
give you as much help to set everything up as possible.

## Optional Dependencies

Mesh Data Resource

https://github.com/Relintai/mesh_data_resource.git

Adds mesh (MeshDataResource) support to ModelVisuals.

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

Entity and spell system comes with quite a few settings, you can find these under `ProjectSettings->Ess`.

## Singletons

The module contains 2 singletons. `ESS`, and `ProfileManager`. Both are accessible from scripts.

### The ESS singleton

Contains the active `ESSResourceDB` instance, and for convenience a reference to the active `ESSEntitySpawner` 
instance. Also loads/handles/processes all of the entity and spell system related ProjectSettings, so if you need
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

Contains Entity-related enums, like AIStates, skeleton attach points, entity flags, immunity flags,
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

When these values are expected to be used as properties, the `ESS` singleton will create snake_cased versions automatically.
`String stat_get_property_name(id: int) const` inside the ESS singleton for example.

So in the example case `ESS.stat_get_property_name(4)` would return `weapon_damage`.

## ESSResourceDB

This is a class that maps ids to resources for quick lookups.
This is necessary in order to support networking, because you don't want to send resource paths over the network 
every time somebody casts a spell for example. 

### ESSResourceDBStatic

Simple static resource db. Just drag and drop all your data that you use into it with the inspector.

Stores the data as vectors.

Supports id remapping, which means that it can assign new ids to all added resources, so they don't clash.
The added resource's index will be set as it's id.

This is useful for modding support, as you can just collect every mod's resource dbs, and add them to a static db,
and with this option enabled the ids will not clash.

You can see an example of this [here](https://github.com/Relintai/broken_seals/blob/master/game/scripts/game_modules/DataManager.gd).

### ESSResourceDBMap

Stores everything as a vector, and a map.

#### ESSResourceDBFolders

Inherited from `ESSResourceDBMap`.

It will load everything from the folders that you set up into it's `folders` property.

## Entity

This is the main class that can be used for players/mobs/npcs and also other things like chests. 

I ended up merging subclass functionality into it, because
that way it gains a lot more utility, by sacrificing only a small amount of memory.
For example this way it is easy to make chests attack the player, or make spell that animate objects.

## Entity Body

Originally entities used to be inherited from `Spatial` or `Node2D`, so they could contain/drive their own models, 
but eventually on order to support both 2d, and 3d, bodies were separated from them. This unfortunately 
complicates the setup a bit, but the upsides overweight the downsides, as this way you don't need to create different
entities for every model/body you have.

Bodies are stored at `EntityData->EntitySpeciesData->ModelDatas (SpeciesModelData)->Body`

When an `Entity` gets initialized, it will instance it's body automatically, but if you want to intance it yourself,
you can call `void instance_body(entity_data: EntityData, model_index: int)` on an `Entity`.

The `model_index` property tell the `Entity` which one it should use.

Instancing bodies does not happen immediately, but you will probably want to set an `Entity`'s position right where 
you create it, a few helpers were added:\

`void set_transform_2d(transform: Transform2D, only_stored: bool = false)`\
`void set_transform_3d(transform: Transform, only_stored: bool = false)`

Your body implementation then can get this from an entity an set itself to the right place.

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

[Complex 3d skeleton scene](https://github.com/Relintai/broken_seals/blob/master/game/models/entities/human/models/armature_huf.tscn) \
[Complex 3d skeleton script](https://github.com/Relintai/broken_seals/blob/master/game/player/CharacterSkeletonGD.gd)

#### CharacterSkeleton2D

The 2d variant.

[Simple 2d roguelike skeleton script](https://github.com/Relintai/broken_seals_roguelike/blob/master/game/characters/SimpleCharacter.gd) \
[Simple 2d roguelike skeleton scene](https://github.com/Relintai/broken_seals_roguelike/blob/master/game/characters/SimpleCharacter.tscn)

#### ModelVisual

A collection ModelVisualEntries.

You will need to use this to define a look. For example if you have an item that will change your character's clothes,
you will use this.

##### ModelVisualEntry

Contains meshes, textures, texture tints, mesh transforms.

It has 2 modes, `Bone` and `Attachment`.

In the bone mode, you need to select an entity type, and then a concrete bone. This is the "merge this into the final character mesh" mode.

In the attachment mode, you need to select a common attach point (`ProjectSettings->Ess->enums->skeletons_bone_attachment_points`), 
and the containing mesh will be put on to that point by the CharacterSkeleton. This is how you can implement weapons for example.

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
[Complex 3d body scene](https://github.com/Relintai/broken_seals/blob/master/game/models/entities/human/models/HumanFemale.tscn)

[Simple 2d roguelike body script](https://github.com/Relintai/broken_seals_roguelike/blob/master/game/player/Body.gd) \
[Simple 2d roguelike body scene](https://github.com/Relintai/broken_seals_roguelike/blob/master/game/player/Body.gd)

#### SpeciesInstance

This class will store character model customization data. E.g. which hairstyle you want for an `Entity`.

Not yet finished!

### Spawning

Since spawning (= creating) entities is entirely dependent on the type of game you are making, ESS cannot do
everything for you. It will set up stats, equipment etc, but there is no way to set up positions for example.

You can implement your spawning logic by inheriting from `ESSEntitySpawner`, and implementing `_request_entity_spawn`.

You should only have one spawner at any given time. It will register itself into the ESS singleton automatically.

Since it is inherited from Node, I recommend that you create an autoload for it.

The ESS singleton also contains convenience methods to request spawning an Entity.

[Sample 3d spawner implementation](https://github.com/Relintai/broken_seals/blob/master/game/player/bs_entity_spawner.gd) \
[Sample 2d spawner implementation](https://github.com/Relintai/broken_seals_roguelike/blob/master/game/player/bs_entity_spawner.gd)

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

EntityResources are things like mana, health, or speed. These add greater flexibility over stats.

The resource system is quite flexible, if you add a resource serverside, it will be automatically
added clientside. (You have to add `EntityResource`s to the active `ESSResourceDB`!)

By default all entities have the build in speed and health resources, as a set index 
(`EntityEnums::ENTITY_RESOURCE_INDEX_HEALTH` and `EntityEnums::ENTITY_RESOURCE_INDEX_SPEED`).

There is also the `EntityEnums::ENTITY_RESOURCE_INDEX_RESOURCES_BEGIN` constant, so you have 
the current offset where the custom resources start.

Entity allocates these in it's  `_initialize()` virtual method, if you want to customize them.

Note that `EntityClassData` contains an array, so you can add more resources easily to classes,
these will be automatically added when the system initializes an `Entity`.

##### EntityResourceHealth

The standard health resource implementation.

##### EntityResourceSpeed

The standard speed resource implementation.

#### EntityResourceCostData

This is the class taht lets you implement resource costs. For example mana cost for a spell.

##### EntityResourceCostDataResource

The standard resource cost implementation.

##### EntityResourceCostDataHealth

The standard health resource cost implementation.

It has a resource property, so you can just assign any resource to this.

### Interactions

If you want your player to interact with it's target. For example a vendor, or loot.

First make sure that you can interact, by checking `Entity.cans_interact()` or `Entity.canc_interact()`.
If this returns true, you can call `Entity.crequest_interact()`. This will call `Entity.sinteract()` serverside.

Interactions are handled by `EntityData` by default. It has the same methods. If `EntityData` is not set, the `Entity` 
will try to call the same overridable on itself.

You can see an example implementation [here](https://github.com/Relintai/broken_seals/blob/master/game/scripts/entities/EntityDataGD.gd).

### AI

You can implement ai by extending `EntityAI`, and then assigning it to an `EntityData`.

When an `Entity` gets spawned it will create a copy for itself, so you can safely use class variables.

#### AIFormation

Not yet finished, it was meant as a way to calculate offset pet positions, (If an `Entity` has let's say 
4 pets you don't just want them all to stay on top of their controller).

If this functionality ends up in `EntityAI`, after pets are finished, this will be removed.

### Pets

Unfortunately pet support is not yet finished.

It is mostly done though, so you will see pet-related methods scattered around.

### Bags

Stores items. See `Bag`. It has quite a few virtual methods, you should be able to implement most inventory types
should you want to.

Entity will send these over the network.

Also Entities have a target bag property. For example this makes vendors easily implementable.

### VRPCs

Entities has a networked visibility system. The method itself is called `vrpc`, it works the same way as normal rpcs.
If you want to send data to every client that sees the current entity, use this. 

## Spells, Auras, Talents

Spell is the class you need to create both spells, and aura.\
It stores the data, and also it has the ability to be scripted.\
Talents are actually just spells used as Auras. Right now the system just applies them as a permanent aura.\
You don't need to worry about applying auras, cast them as spells instead. It they are set to permanent, or they have a duration set they will be applied as an aura automatically.

Talent ranks are implemented by deapplying the earlier rank first, then applying the new rank.

### How to

Request casting a spell clientside: `void spell_crequest_cast(spell_id: int)` \
Request to learn a spell clientside: `void spell_learn_requestc(id: int)`

Request talent learning clientside: \
`void character_talent_crequest_learn(spec_index: int, character_talent_row: int, character_talent_culomn: int)` or \
`void class_talent_crequest_learn(spec_index: int, class_talent_row: int, class_talent_culomn: int)` 

#### Cast a spell

Note that you should only do this serverside.

```
# Or get it from the active ESSResourceDB, etc
export(Spell) var spell : Spell

func scast_spell() -> void:
	var sci : SpellCastInfo = SpellCastInfo.new()

	sci.caster = info.caster
	sci.target = info.target
	sci.has_cast_time = spell.cast_enabled
	sci.cast_time = spell.cast_cast_time
	sci.spell_scale = info.spell_scale
	sci.set_spell(spell)

	spell.cast_starts(sci)

```

#### Apply an aura

Normally you shouldn't do this, this is for more advanced uses. Cast the aura as a spell instead.

Note that you should only apply auras serverside, they will be sent to clients automatically.

```
# Or get it from the active ESSResourceDB, etc
export(Spell) var aura : Spell

func sapply_aura() -> void:
    var ainfo : AuraApplyInfo = AuraApplyInfo.new()
            
    ainfo.caster = info.caster
    ainfo.target = info.caster
    ainfo.spell_scale = 1
    ainfo.aura = aura

    aura.sapply(ainfo)

```

#### UI

[Complete UI Implemetation](https://github.com/Relintai/broken_seals/tree/master/game/ui/player)

[Player UI Core Implemetation](https://github.com/Relintai/broken_seals/tree/master/game/ui/player/player_ui)

[Aura Frame Implementation](https://github.com/Relintai/broken_seals/tree/master/game/ui/player/auraframe) \
[Castbar Implementation](https://github.com/Relintai/broken_seals/tree/master/game/ui/player/castbar) \
[Unitframe Implementation](https://github.com/Relintai/broken_seals/tree/master/game/ui/player/unitframes)

[Actionbar Implementation](https://github.com/Relintai/broken_seals/tree/master/game/ui/player/actionbars)

[Character Window Implementation](https://github.com/Relintai/broken_seals/tree/master/game/ui/player/character) \
[Inventory Window Implementation](https://github.com/Relintai/broken_seals/tree/master/game/ui/player/bags) \
[Crafting Window Implementation](https://github.com/Relintai/broken_seals/tree/master/game/ui/player/crafting) \
[Loot Window Implementation](https://github.com/Relintai/broken_seals/tree/master/game/ui/player/loot_window) \
[Talent Window Implemetation](https://github.com/Relintai/broken_seals/tree/master/game/ui/player/talents) \
[Spellbook Window Implementation](https://github.com/Relintai/broken_seals/tree/master/game/ui/player/spellbook)  \
[Vendor Window Implementation](https://github.com/Relintai/broken_seals/tree/master/game/ui/player/vendor_window) \
[Trainer Window Implementation](https://github.com/Relintai/broken_seals/tree/master/game/ui/player/trainer)

[3D Nameplate Implementation](https://github.com/Relintai/broken_seals/tree/master/game/ui/world/nameplates) \
[2D Nameplate Implementation](https://github.com/Relintai/broken_seals_roguelike/tree/master/game/ui/nameplates)

### Infos / Pipelines

#### SpellCastInfo

Stores information about the state of a spell's cast.

#### AuraApplyInfo

Helps to apply auras

#### SpellDamageInfo, SpellHealInfo

These are used in the damage and heal calculation. For example these can be used to implement immunities, or absorb effects 
by modifying their damage values in aura callbacks.

### Projectiles

Spells support projectiles, they are created/set up inside `void handle_projectile(info: SpellCastInfo)`.

The default implementation will instance `Spell`'s projectile scene (if set), and then it will try to call a 
`void setup_projectile(info: SpellCastInfo)` on it if exists.

You can override this behaviour by implementing your own `_void handle_projectile(info: SpellCastInfo)` on `Spell`

Note that the module already adds `SpellFollowProjectile3D`, but this has not been finished yet.

## Items

Items are implemented using 2 classes, `ItemTemplate`, and `ItemInstance`.

`ItemTemplate` contains all information for a potential item. You can generate `Iteminstance`s with this,
using it's `ItemInstance create_item_instance()` method. You can also implement your custom item creation logic
using the `void _create_item_instance()` virtual.

`ItemInstance` is the actual item.

### Loot

Looting can be implemented using `Entity`'s target bag functionality.

You can see an example implementation [here](https://github.com/Relintai/broken_seals/blob/master/game/scripts/entities/EntityDataGD.gd). \
And an example ui implementation [here](https://github.com/Relintai/broken_seals/tree/master/game/ui/player/loot_window).

## XP

You can set all the xp values for your levels in `ProjectSettings->Ess->xp`.

Now you can start distributing xp, for whatever you'd like to Entities, using `Entity.xp_adds(vlaue : int)`

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

First make sure that you can compile godot. See the official docs: https://docs.godotengine.org/en/3.x/development/compiling/index.html

1. Clone the engine if you haven't already:

If you want Godot 3.x:
```git clone -b 3.x https://github.com/godotengine/godot.git godot```

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
