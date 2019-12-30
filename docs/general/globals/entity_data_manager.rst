.. _doc_general_entity_data_manager:


:ref:`Entity Data Manager<class_EntityDataManager>`
===================================================

Loads / stores all the data the module needs, like classes, spells, auras, etc, also
it will have convenience methods to spawn Entities, it will also
handle :ref:`Entity<class_Entity>` spawning over the network.
:ref:`Entity<class_Entity>` spawning is only implemented in gdscript at the moment, 
will be ported soon.

All loaded data classes have an id property, also these need to be unique 
between them.

Right now you will need to populate every folder property, like
:ref:`auras_folder<class_EntityDataManager_property_auras_folder>`. 
The Manager loads everything from the given folders. If you don't use some of the
resources that has a folder property for it, switch off 
:ref:`automatic_load<class_EntityDataManager_property_automatic_load>`, and only load 
the things you need. You can use methods like 
:ref:`load_auras<class_EntityDataManager_method_load_auras>`.

ESS uses this data to spawn things over the network.

Right now you always need to have this class in the scene before spawning an 
:ref:`Entity<class_Entity>`. Later this restriction will only apply if you
want to use networking.

You can script the loading behaviours by turning off the 
:ref:`automatic_load<class_EntityDataManager_property_automatic_load>` property 
in the instector.

The manager's scripting api allows you to fully customize loading.
You can add even  dd every class one by one if you want to.
This also allows for procedurally generating data if you want to.
However if you do this, and also use networking, you need to make sure to to 
generate the same spells aswell on clients aswell.