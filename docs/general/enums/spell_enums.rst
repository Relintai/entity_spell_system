.. _doc_general_spell_enums:

:ref:`Spell Enums <class_SpellEnums>`
=====================================

Contains Spell-related enums.

:ref:`DamageType <enum_SpellEnums_DamageType>`
----------------------------------------------

The type of damage. It's a flag, so you can combine them.

Like Melee, Holy, Shadow etc.

:ref:`SpellCategory <enum_SpellEnums_SpellCategory>`
----------------------------------------------------

Helps to filter spells when needed. Like Normal, Alchemy, Cooking etc.

:ref:`SpellType <enum_SpellEnums_SpellType>`
--------------------------------------------

At the moment contains the same entries as :ref:`DamageType <enum_SpellEnums_DamageType>`,
also a flag, can be used for interrupt lockouts.

:ref:`DiminishingReturnCategory <enum_SpellEnums_DiminishingReturnCategory>`
----------------------------------------------------------------------------

Categories for diminishing returns. Root, Stun, etc.

:ref:`TriggerEvents <enum_SpellEnums_TriggerEvents>`
----------------------------------------------------

Triggen event categories. These are not yet implemented. The ide behind these is to be able to
create some reative effects, using Aura's inspector.

Think of an aura that gives a 10% chance to stun an enemy (a.k.a apply an aura), when they (ON_HIT) hit the owner.

:ref:`AuraType <enum_SpellEnums_AuraType>`
------------------------------------------

Type of an aura. Like None, Magic, Poison etc.

You can make these show up in the ui, also some spell can operate on different types.

:ref:`ColliderType <enum_SpellEnums_ColliderType>`
--------------------------------------------------

Collider type for aoes, to intersect with.

:ref:`TargetType <enum_SpellEnums_TargetType>`
----------------------------------------------

This is used by WorldSpell, to know where to "aim".
