.. _doc_ui_srag_and_drop:

Drag and Drop
=============

Implement drag & drops using :ref:`ESDragAndDrop<class_ESDragAndDrop>`.

ESS uses this as it's drag & drop helper class. You can easily set up item, and spell
drag & drops with this.

The meaning of the :ref:`item_id<class_ESDragAndDrop_property_item_id>` property changes, based
on the value of the :ref:`type<class_ESDragAndDrop_property_type>` property. It can mean, spell, itemid, 
item slot, and equip slot.

Don't forget to set the :ref:`origin<class_ESDragAndDrop_property_origin>` property.
