/*
Copyright (c) 2019-2020 Péter Magyar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "entity_enums.h"

const String EntityEnums::BINDING_STRING_ENTITY_PLAYER_TYPES = "None,Player,Networked,AI,Display";
const String EntityEnums::BINDING_STRING_ENTITY_CONTOLLER = "None,Player,AI";
const String EntityEnums::BINDING_STRING_ENTITY_FLAGS = "Untargetable,Hidden,Interactable,Hostile";
const String EntityEnums::BINDING_STRING_ENTITY_STATE_TYPES = "None,Stun,Root,Frozen,Silenced,Disoriented,Feared,Burning,Cold,Cursed,Pacified";
const String EntityEnums::BINDING_STRING_COMMON_CHARCATER_SKELETON_POINTS = "Root,Pelvis,Spine,Spine 1,Spine 2,Neck,Head,Torso,Right Hip,Left Hip,Back,Left Hand,Right Hand,Weapon Left,Weapon Right,Weapon Left Back,Weapon Right Back,Weapon Left Shield,Weapon Right Shield";
const String EntityEnums::BINDING_STRING_AI_STATES = "Off,Rest,Patrol,Follow Path,Regenerate,Attack,Pet Follow,Pet Stop,Pet Attack";
const String EntityEnums::BINDING_STRING_ENTITY_IMMUNITY_FLAGS = "Stun,Root,Freeze,Silence,Disorient,Fear,Burning,Cold,Pacify,Magic,Poison,Physical,Curse,Bleed,Melee,Holy,Shadow,Nature,Fire,Frost,Lightning,Chaos,Slow,Crit,AOE,Damage,Fall Damage,Projectile,Debuff,Attacks";
const String EntityEnums::BINDING_STRING_ENTITY_RELATION_TYPE = "Neutral,Friendly,Hostile";
const String EntityEnums::BINDING_STRING_ENTITY_INTERACTION_TYPE = "Normal,Speak,Loot,Train,Use,None";
const String EntityEnums::BINDING_STRING_ENTITY_PLAYSTYLE_TYPE = "Melee,Spell,Hybrid,None";
const String EntityEnums::BINDING_STRING_ENTITY_WINDOWS = "Loot,Container,Vendor,Trainer";
const String EntityEnums::BINDING_STRING_ENTITY_ENTITY_RESOURCE_INDICES = "Health,Speed,Resources Begin";

void EntityEnums::_bind_methods() {
	BIND_ENUM_CONSTANT(ENTITY_PLAYER_TYPE_NONE);
	BIND_ENUM_CONSTANT(ENTITY_PLAYER_TYPE_PLAYER);
	BIND_ENUM_CONSTANT(ENTITY_PLAYER_TYPE_NETWORKED);
	BIND_ENUM_CONSTANT(ENTITY_PLAYER_TYPE_AI);
	BIND_ENUM_CONSTANT(ENTITY_PLAYER_TYPE_DISPLAY);

	BIND_ENUM_CONSTANT(ENITIY_CONTROLLER_NONE);
	BIND_ENUM_CONSTANT(ENITIY_CONTROLLER_PLAYER);
	BIND_ENUM_CONSTANT(ENITIY_CONTROLLER_AI);

	BIND_ENUM_CONSTANT(ENITIY_FLAGS_NONE);
	BIND_ENUM_CONSTANT(ENTITY_FLAGS_UNTARGETALBE);
	BIND_ENUM_CONSTANT(ENTITY_FLAGS_HIDDEN);
	BIND_ENUM_CONSTANT(ENTITY_FLAGS_INTERACTABLE);
	BIND_ENUM_CONSTANT(ENTITY_FLAGS_HOSTILE);

	BIND_ENUM_CONSTANT(ENTITY_STATE_TYPE_FLAG_NONE);
	BIND_ENUM_CONSTANT(ENTITY_STATE_TYPE_FLAG_STUN);
	BIND_ENUM_CONSTANT(ENTITY_STATE_TYPE_FLAG_ROOT);
	BIND_ENUM_CONSTANT(ENTITY_STATE_TYPE_FLAG_FROZEN);
	BIND_ENUM_CONSTANT(ENTITY_STATE_TYPE_FLAG_SILENCED);
	BIND_ENUM_CONSTANT(ENTITY_STATE_TYPE_FLAG_DISORIENTED);
	BIND_ENUM_CONSTANT(ENTITY_STATE_TYPE_FLAG_FEARED);
	BIND_ENUM_CONSTANT(ENTITY_STATE_TYPE_FLAG_BURNING);
	BIND_ENUM_CONSTANT(ENTITY_STATE_TYPE_FLAG_COLD);
	BIND_ENUM_CONSTANT(ENTITY_STATE_TYPE_FLAG_CURSED);
	BIND_ENUM_CONSTANT(ENTITY_STATE_TYPE_FLAG_PACIFIED);

	BIND_ENUM_CONSTANT(ENTITY_STATE_TYPE_INDEX_NONE);
	BIND_ENUM_CONSTANT(ENTITY_STATE_TYPE_INDEX_STUN);
	BIND_ENUM_CONSTANT(ENTITY_STATE_TYPE_INDEX_ROOT);
	BIND_ENUM_CONSTANT(ENTITY_STATE_TYPE_INDEX_FROZEN);
	BIND_ENUM_CONSTANT(ENTITY_STATE_TYPE_INDEX_SILENCED);
	BIND_ENUM_CONSTANT(ENTITY_STATE_TYPE_INDEX_DISORIENTED);
	BIND_ENUM_CONSTANT(ENTITY_STATE_TYPE_INDEX_FEARED);
	BIND_ENUM_CONSTANT(ENTITY_STATE_TYPE_INDEX_BURNING);
	BIND_ENUM_CONSTANT(ENTITY_STATE_TYPE_INDEX_COLD);
	BIND_ENUM_CONSTANT(ENTITY_STATE_TYPE_INDEX_CURSED);
	BIND_ENUM_CONSTANT(ENTITY_STATE_TYPE_INDEX_PACIFIED);
	BIND_ENUM_CONSTANT(ENTITY_STATE_TYPE_INDEX_MAX);

	BIND_ENUM_CONSTANT(COMMON_SKELETON_POINT_ROOT);
	BIND_ENUM_CONSTANT(COMMON_SKELETON_POINT_PELVIS);
	BIND_ENUM_CONSTANT(COMMON_SKELETON_POINT_SPINE);
	BIND_ENUM_CONSTANT(COMMON_SKELETON_POINT_SPINE_1);
	BIND_ENUM_CONSTANT(COMMON_SKELETON_POINT_SPINE_2);
	BIND_ENUM_CONSTANT(COMMON_SKELETON_POINT_NECK);
	BIND_ENUM_CONSTANT(COMMON_SKELETON_POINT_HEAD);
	BIND_ENUM_CONSTANT(COMMON_SKELETON_POINT_TORSO);
	BIND_ENUM_CONSTANT(COMMON_SKELETON_POINT_RIGHT_HIP);
	BIND_ENUM_CONSTANT(COMMON_SKELETON_POINT_LEFT_HIP);
	BIND_ENUM_CONSTANT(COMMON_SKELETON_POINT_BACK);
	BIND_ENUM_CONSTANT(COMMON_SKELETON_POINT_LEFT_HAND);
	BIND_ENUM_CONSTANT(COMMON_SKELETON_POINT_RIGHT_HAND);

	BIND_ENUM_CONSTANT(COMMON_SKELETON_POINT_WEAPON_LEFT);
	BIND_ENUM_CONSTANT(COMMON_SKELETON_POINT_WEAPON_RIGHT);
	BIND_ENUM_CONSTANT(COMMON_SKELETON_POINT_WEAPON_LEFT_BACK);
	BIND_ENUM_CONSTANT(COMMON_SKELETON_POINT_WEAPON_RIGHT_BACK);
	BIND_ENUM_CONSTANT(COMMON_SKELETON_POINT_WEAPON_LEFT_SHIELD);
	BIND_ENUM_CONSTANT(COMMON_SKELETON_POINT_WEAPON_RIGHT_SHIELD);

	BIND_CONSTANT(COMMON_SKELETON_POINTS_MAX);

	BIND_ENUM_CONSTANT(AI_STATE_OFF);
	BIND_ENUM_CONSTANT(AI_STATE_REST);
	BIND_ENUM_CONSTANT(AI_STATE_PATROL);
	BIND_ENUM_CONSTANT(AI_STATE_FOLLOW_PATH);
	BIND_ENUM_CONSTANT(AI_STATE_REGENERATE);
	BIND_ENUM_CONSTANT(AI_STATE_ATTACK);
	BIND_ENUM_CONSTANT(AI_STATE_PET_FOLLOW);
	BIND_ENUM_CONSTANT(AI_STATE_PET_STOP);
	BIND_ENUM_CONSTANT(AI_STATE_PET_ATTACK);
	BIND_CONSTANT(AI_STATE_MAX);

	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_NONE);

	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_STUN);
	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_ROOT);
	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_FREEZE);
	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_SILENCE);
	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_DISORIENT);
	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_FEAR);
	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_BURNING);
	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_COLD);
	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_PACIFY);

	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_MAGIC);
	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_POISON);
	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_PHYSICAL);
	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_CURSE);
	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_BLEED);

	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_MELEE);
	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_HOLY);
	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_SHADOW);
	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_NATURE);
	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_FIRE);
	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_FROST);
	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_LIGHTNING);
	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_CHAOS);

	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_SLOW);
	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_CRIT);
	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_AOE);
	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_DAMAGE);
	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_FALL_DAMAGE);
	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_PROJECTILE);
	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_DEBUFF);
	BIND_ENUM_CONSTANT(ENTITY_IMMUNITY_FLAG_ATTACKS);

	BIND_ENUM_CONSTANT(ENTITY_RELATION_TYPE_NEUTRAL);
	BIND_ENUM_CONSTANT(ENTITY_RELATION_TYPE_FRIENDLY);
	BIND_ENUM_CONSTANT(ENTITY_RELATION_TYPE_HOSTILE);

	BIND_ENUM_CONSTANT(ENITIY_INTERACTION_TYPE_NORMAL);
	BIND_ENUM_CONSTANT(ENITIY_INTERACTION_TYPE_SPEAK);
	BIND_ENUM_CONSTANT(ENITIY_INTERACTION_TYPE_LOOT);
	BIND_ENUM_CONSTANT(ENITIY_INTERACTION_TYPE_TRAIN);
	BIND_ENUM_CONSTANT(ENITIY_INTERACTION_TYPE_USE);
	BIND_ENUM_CONSTANT(ENITIY_INTERACTION_TYPE_NONE);

	BIND_ENUM_CONSTANT(ENTITY_CLASS_PLAYSTYLE_TYPE_MELEE);
	BIND_ENUM_CONSTANT(ENTITY_CLASS_PLAYSTYLE_TYPE_SPELL);
	BIND_ENUM_CONSTANT(ENTITY_CLASS_PLAYSTYLE_TYPE_HYBRID);
	BIND_ENUM_CONSTANT(ENTITY_CLASS_PLAYSTYLE_TYPE_NONE);

	BIND_ENUM_CONSTANT(ENTITY_WINDOW_LOOT);
	BIND_ENUM_CONSTANT(ENTITY_WINDOW_CONTAINER);
	BIND_ENUM_CONSTANT(ENTITY_WINDOW_VENDOR);
	BIND_ENUM_CONSTANT(ENTITY_WINDOW_TRAINER);

	BIND_ENUM_CONSTANT(ENTITY_RESOURCE_INDEX_HEALTH);
	BIND_ENUM_CONSTANT(ENTITY_RESOURCE_INDEX_SPEED);
	BIND_ENUM_CONSTANT(ENTITY_RESOURCE_INDEX_RESOURCES_BEGIN);

	BIND_CONSTANT(BASE_XP);
}
