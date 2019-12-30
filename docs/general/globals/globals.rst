.. _doc_general_globals:

Globals
=======

These are the global classes of the module.

Right now both need to exist in the scene before you spawn entities.

I recommend adding them as autoloads.

Later both will be optional, in the case of profile manager, this is really simple, 
however in the case of data manager, this is going to be more difficult. Also for 
data manager it will only be possible if networking is disabled.


.. toctree::
   :maxdepth: 1
   :caption: Globals
   :name: sec-globals-cat

   entity_data_manager
   profile_manager
