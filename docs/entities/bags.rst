.. _doc_entities_bags:

Bags
====

For implementing inventories use the :ref:`Bag<class_Bag>` base class.

Right now :ref:`Bags<class_Bag>` implements a really simple system (think of Skyrim).
Later more implementations will be added (as subclasses).
If you need a Diablo-like inventory grid, this is a work-in-progress version:
https://github.com/Relintai/entity_spell_system/blob/master/inventory/grid_bag.h
It's not in the build right now, but at least you won't start from scratch, if you want to create one
like this. The item size properties were removed from items, they'll be added back.

Every :ref:`Entity<class_Entity>` contains a :ref:`Bags<class_Bag>` property, both server, and clientside.
See :ref:`Entity.sbag<class_Entity_property_sbag>`, and :ref:`Entity.cbag<class_Entity_property_cbag>`.

For networked players, whenever the contents of an :ref:`Entity<class_Entity>`'s bag changes, the 
system automatically sends a message to the :ref:`Entity<class_Entity>`'s owner, thus keeping the
state consistent on both server and client.

The system can also send a bag's contents all at once, for example this happens whenever you replace an
:ref:`Entity<class_Entity>`'s bags, using the serverside properties.

By default Entities won't actually create their own bags, because for example mobs don't need bags by default.

.. note:: Right now for the player the :ref:`setup_actionbars<class_Entity_method_setup_actionbars>` will allocate bags.
          This will be changed. Also since the module needs the ability to easily switch bag implementations, bag
          allocation will probably be pushed into a virtual function, like setup_bags() -> _setup_bags() (virtual).

Target Bags
===========

See :ref:`starget_bag<class_Entity_property_starget_bag>`, and :ref:`ctarget_bag<class_Entity_property_ctarget_bag>`.

With these it becomes possible to implement checsts, bank, loot, with minimal code.

For example when a mob dies, loot is generated into their bags, then when you click their corpse, that bag gets set
as you player's target bag. When you do this, the system sends the contents to that player, and they can manipulate
the contents, based on what the server allows.

If you want to see how to setup loot interaction, check the _son_death method here:
https://github.com/Relintai/broken_seals/blob/master/game/player/Mob.gd

It you want to see how to setup loot, check the _sinteract method here:
https://github.com/Relintai/broken_seals/blob/master/game/scripts/entities/EntityDataGD.gd
