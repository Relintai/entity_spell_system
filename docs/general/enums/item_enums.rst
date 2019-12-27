.. _doc_general_item_enums:

:ref:`Item Enums <class_ItemEnums>`
===================================

Contains item-related enums.

:ref:`ItemRarity <enum_ItemEnums_ItemRarity>`
---------------------------------------------

Yout can set the visual rarity representation with this.

:ref:`ItemRarityFlag <enum_ItemEnums_ItemRarityFlag>`
-----------------------------------------------------

For generated items. You can set with it which rarities can happen.

:ref:`ItemType <enum_ItemEnums_ItemType>`
-----------------------------------------

Main item type / category.

Contains things like equipment, weapont, potion, herb, etc.

:ref:`ItemSubtype <enum_ItemEnums_ItemSubtype>`
-----------------------------------------------

Subtype. Like axe, mace, quest item etc.

:ref:`ItemSubSubtype <enum_ItemEnums_ItemSubSubtype>`
-----------------------------------------------------

SubSubtype. Like One hand, Two Hand etc.

.. note:: I don't like this setup, I'll try to make this better.

:ref:`EquipSlots <enum_ItemEnums_EquipSlots>`
---------------------------------------------

The equipslots you want for your character.

Head, Neck, Shoulders etc.

.. note:: I don't like this setup, I'll try to make this better (Somehow make it easily changeable).
          Maybe make it customiyable with a macro from a central file somehow. TODO (Same will be 
          applied, to any enum which should be customizable)

:ref:`ArmorType <enum_ItemEnums_ArmorType>`
-------------------------------------------

Armor types. Cloth, Leather, etc.

:ref:`EntityTextureLayers <enum_ItemEnums_EntityTextureLayers>`
---------------------------------------------------------------

Texture Layers for merging equipment textures, so you can color skins, eyes etc, and then merge 
(and also possibly color) equipment textures.

Think of equipment coloring in Diablo 3.
