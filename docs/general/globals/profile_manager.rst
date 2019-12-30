.. _doc_general_profile_manager:


:ref:`Profile Manager<class_ProfileManager>`
============================================

Saves/loads player profiles.

A Player profile pretty much is an array of :ref:`ClassProfiles<class_ClassProfile>`.

Every :ref:`ClassProfile<class_ClassProfile>` contains actionbar information, class level information,
and it will (right now there is one placeholder class for this) contain keybind information.

Right now having this class inside the SceneTree is required before spawning entities.
This will change in the future.

In the future the data it saves will be more customizable by scripts.
