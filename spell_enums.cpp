/*
Copyright (c) 2019-2022 Péter Magyar

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

#include "spell_enums.h"

const String SpellEnums::BINDING_STRING_SPELL_TYPES = "Melee,Holy,Shadow,Nature,Fire,Frost,Lightning,Chaos";
const String SpellEnums::BINDING_STRING_SPELL_CATEGORY = "Normal,Alchemy,Cooking,Engineering,Crafting,Hidden,Development";
const String SpellEnums::BINDING_STRING_TRIGGER_EVENTS = "None,S On Before Damage,S On Damage Receive,S On Hit,S On Damage Dealt,S Aura Remove,S Aura Dispell,S On Before Aura Applied,S On After Aura Applied,C On Aura Added,C On Aura Removed,C On Aura Refreshed";
const String SpellEnums::BINDING_STRING_DAMAGE_TYPES = "Melee,Holy,Shadow,Nature,Fire,Frost,Lightning,Chaos";
const String SpellEnums::BINDING_STRING_AURA_TYPES = "None,Magic,Poison,Physical,Curse,Bleed,Talent,Skill";
const String SpellEnums::BINDING_STRING_AURA_FLAG_TYPES = "Magic,Poison,Physical,Curse,Bleed,Talent,Skill";
const String SpellEnums::BINDING_STRING_COLLIDER_TYPE = "None,Sphere,Box";
const String SpellEnums::BINDING_STRING_TARGET_TYPE = "None,Node,Bone ID,Coords";
const String SpellEnums::BINDING_STRING_TRIGGER_TYPE = "None,Percent,PPM";
const String SpellEnums::BINDING_STRING_TRIGGER_NOTIFICATION_TYPE = "Aura,Damage,Heal,Cast,Death,Cooldown Added,Cooldown Removed,Category CooldownAdded,Category CooldownRemoved,GCD Started,GCD Removed,XP Gained,Class Levelup,Character Levelup,Entity Resource Added,Entity Resource Removed,Aura Custom,Damage Custom,Heal Custom,Cast Custom,Custom";

const String SpellEnums::BINDING_STRING_NOTIFICATION_AURAS = "Before Applied,After Applied,Applied,Added,Removed,Refreshed";
const String SpellEnums::BINDING_STRING_NOTIFICATION_DAMAGES = "Before Hit,Hit,Before Damage,Receive,Dealt Damage,Damage Dealt,Damage";
const String SpellEnums::BINDING_STRING_NOTIFICATION_HEALS = "Heal Hit,Before Heal,Receive,Dealt Heal,Heal Dealt";
const String SpellEnums::BINDING_STRING_NOTIFICATION_CASTS = "Before,Before Cast Target,Finished Target,Finished,Started,Failed,Success,Interrupted,Delayed";
