.. _doc_general_enums:

Enums
=====

These are helper classes containing huge amounts of enums.

They exists, because if these were in their own respective classes, for example 
Entity for EntityEnums, then Entity would need to be included by pretty much almost every class,
but Entity also includes a lot of things, which means a lot of boilerplate forward declarations, and also 
this would slow down incremental compile times considerably. So for convenience, these classes were born.

.. toctree::
   :maxdepth: 1
   :caption: Enums
   :name: sec-enums

   entity_enums
   spell_enums
   item_enums