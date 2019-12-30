.. _doc_entities_crafting:

Crafting
========

The module supports crafting. In order to set it up, first you'll probably need a gui.

As a starter you can take Broken Seal's crafting window from here:
https://github.com/Relintai/broken_seals/tree/master/game/ui/crafting

Or if you want to implement one yourself, implement the ability to your window to display recipes,
and then you can just get recipes from your target entity with functions like 
:ref:`getc_craft_recipe<class_Entity_method_getc_craft_recipe>` **(** int craft_recipe **)** ,
and :ref:`getc_craft_recipe_count<class_Entity_method_getc_craft_recipe_count>` **(** **)**.

.. note:: You usually want to use the client side functions/properties for uis. The serverside
          versions will have the ability to have additional, hidden entries. This will allow
          for more effects, for example you can remove the player's ability to temporarily 
          see/craft certain things, without them actually forgeting them.
