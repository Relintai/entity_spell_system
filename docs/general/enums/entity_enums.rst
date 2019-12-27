.. _doc_general_entity_enums:

:ref:`Entity Enums <class_EntityEnums>`
=======================================

Contains common Entity-related enums.

It has an unnamed enum containing the following values:

MAX_LEVEL = 50,
BASE_XP = 50,
GENDER_COUNT = 2

Unfortunately, to chenge these, you will need to recompile the engine. 
This will be fixed later.

:ref:`EntityType <enum_EntityEnums_EntityType>`
-----------------------------------------------

Entity type, like beast, creature, object, humanoind, etc.

See :ref:`Entity.sentity_flags <class_Entity_property_sentity_type>`, and :ref:`Entity.centity_flags <class_Entity_property_centity_type>`.


:ref:`EntityController <enum_EntityEnums_EntityController>`
-----------------------------------------------------------

Is the entity controlled by a player, or an ai. Will be used for pets, can be used for 
narrative things aswell, also mind control like effects.

See :ref:`Entity.sentity_flags <class_Entity_property_sentity_flags>`, and :ref:`Entity.centity_flags <class_Entity_property_centity_flags>`.


:ref:`EntityFlags <enum_EntityEnums_EntityFlags>`
-------------------------------------------------

Contains generic flags, like untargetable, hidden, interactable, etc.

See :ref:`Entity.sentity_flags <class_Entity_property_sentity_flags>`, and 
:ref:`Entity.centity_flags <class_Entity_property_centity_flags>`.


:ref:`EntityStateTypeFlags <enum_EntityEnums_EntityStateTypeFlags>`
-------------------------------------------------------------------

Contains flags for effects. For example Stun, Root, Fear etc. Use these to check if 
an entity has a particular effect.

.. note:: Don't set flags directly with the :ref:`Entity.sentity_flags <class_Entity_property_sentity_flags>` 
          property, because the flags are calculated (refcount). Seen the (EntityStateTypeIndexes) 
          section below.

This is how you can check serverside if an entity is stunned:

.. code-block:: gdscript

    if entity.gets_state() & EntityEnums.ENTITY_STATE_TYPE_FLAG_STUN != 0:
        print('stunned')

See :ref:`Entity.sentity_flags <class_Entity_property_sentity_flags>`, 
and :ref:`Entity.centity_flags <class_Entity_property_centity_flags>`.

:ref:`EntityStateTypeIndexes <enum_EntityEnums_EntityStateTypeIndexes>`
-----------------------------------------------------------------------

For ease of use, Entity refcounts states, this is the enum, used to do it. When you want to add a state to an 
entity, you need to use See :ref:`Entity.sadd_state_ref() <class_Entity_method_sadd_state_ref>`, 
when you want to remove states use :ref:`Entity.sremove_state_ref() <class_Entity_method_sremove_state_ref>`.

.. note:: This in only available serverside.

For exmaple let's add a stun to an Entity:

.. code-block:: gdscript

    entity.sadd_state_ref(EntityEnums.ENTITY_STATE_TYPE_INDEX_STUN)

Let's remove it:

.. code-block:: gdscript

    entity.sremove_state_ref(EntityEnums.ENTITY_STATE_TYPE_INDEX_STUN)

Since these states are refcounted, everything will work, even if you have multiple sources stunning an entity.

.. note:: add, and remove_ref will recalculate, and set the :ref:`Entity.sentity_flags <class_Entity_property_sentity_flags>`
          whenever needed. Also note, that :ref:`Entity.sentity_flags <class_Entity_property_sentity_flags>` will 
          syncronize itself over the network, into :ref:`Entity.centity_flags <class_Entity_property_centity_flags>`.

:ref:`EntityImmunityFlags <enum_EntityEnums_EntityImmunityFlags>`
-----------------------------------------------------------------

You can set entity immunities with this. 

See :ref:`Entity.simmunity_flags <class_Entity_property_simmunity_flags>`. (Serverside only).

Let's make an entity immune to stun, and root:

.. code-block:: gdscript

    entity.simmunity_flags = EntityEnums.ENTITY_IMMUNITY_FLAG_STUN | ENTITY_IMMUNITY_FLAG_ROOT

:ref:`CharacterSkeletonPoints <enum_EntityEnums_CharacterSkeletonPoints>`
-------------------------------------------------------------------------

Contains all the points/bones of the standard skeleton. With the current implementation, these are the bones,
that you can apply equipments to, add effects to, etc.

Of course it's up to each skeleton setup, to determine what to implement, and how to handle these in the end,
so even though this has it's limitations, there is still a lot of flexility. For example if you create a beast 
skeleton, that class can just ignore any equipment's visuals.

.. note:: I do have some issues with this solution, because you will need to change, and recompile to add your own bones,
          I'm thinking about a better solution. The main reason it's not that easy, is because this gives huge amounts 
          of convenience when creating equipment for example. You can check :ref:`ItemVisual <class_ItemVisual>` to see why.

:ref:`AIStates <enum_EntityEnums_AIStates>`
-------------------------------------------

The run of the mill AI FSM states.

:ref:`PetStates <enum_EntityEnums_PetStates>`
---------------------------------------------

Will be merged into AIStates, because it will make pet support a lot simpler.

:ref:`EntityInteractionType <enum_EntityEnums_EntityInteractionType>`
---------------------------------------------------------------------

How an entity should interact when an another one wants to :ref:`interact <class_Entity_method_sinteract>` with it.

Speak, Loot, Use, etc.

:ref:`EntityClassPlaystyleType <enum_EntityEnums_EntityClassPlaystyleType>`
---------------------------------------------------------------------------

For ai scripts. So they can tell whether a class is ranged or not.

:ref:`EntityGender <enum_EntityEnums_EntityGender>`
---------------------------------------------------

Well. gender. It's an enum, because it saves work on bindings. Look at the c++ code of 
:ref:`ItemVisualEntry <class_ItemVisualEntry>` if you want to see why.

:ref:`EntityWindows <enum_EntityEnums_EntityWindows>`
-----------------------------------------------------

Allows the server to open different windows on the client. For example loot window, interaction windows, etc.

.. note:: The bindings in entity for this are using ints, so you can implement you own windows really easily.
          The ide is similar to NOTIFICATION-s in Node, and derived types.

