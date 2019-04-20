CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(ASDef_SpellSystemProj CXX)

##################################################
#Precompiled headers
##################################################
#SET (CMAKE_MODULE_PATH "$ENV{ALTERNATIVE_TOOLS_PATH}/CMake")
#INCLUDE($ENV{ALTERNATIVE_TOOLS_PATH}/Cotire/CMake/cotire.cmake)

##################################################
#Enable C++11 mode
##################################################
INCLUDE($ENV{ALTERNATIVE_TOOLS_PATH}/Code/CMAKE-CXX11.cmake)

SET_PROPERTY(GLOBAL PROPERTY GL_IS_RELEASE 0)
SET(EXECPATH AuraScript.cpp AuraScript.h SpellMgrObserver.cpp SpellMgrObserver.h GenericSpell.cpp GenericSpell.h SpellScript.cpp SpellScript.h SpellEffectStartPosition.cpp SpellEffectStartPosition.h SpellProjectileComponent.cpp SpellProjectileComponent.h StraightSpellProjectileComponent.cpp StraightSpellProjectileComponent.h SpellSystem.cpp SpellSystem.h WorldSpellFollowBehaviour.cpp WorldSpellFollowBehaviour.h WorldSpellHitCallbackBehaviour.cpp WorldSpellHitCallbackBehaviour.h WorldSpellStraightBehaiour.cpp WorldSpellStraightBehaiour.h WorldSpellTimeDestroyBehaviour.cpp WorldSpellTimeDestroyBehaviour.h WorldSpell.cpp WorldSpell.h GenericAOESpell.cpp GenericAOESpell.h SpellScriptFactory.cpp SpellScriptFactory.h GameObjectSpellMgr.cpp GameObjectSpellMgr.h GenericAura.cpp GenericAura.h AuraScriptFactory.cpp AuraScriptFactory.h AuraScript.cpp AuraScript.h SpellMgrObserver.cpp SpellMgrObserver.h GenericSpell.cpp GenericSpell.h SpellScript.cpp SpellScript.h SpellEffectStartPosition.cpp SpellEffectStartPosition.h SpellProjectileComponent.cpp SpellProjectileComponent.h StraightSpellProjectileComponent.cpp StraightSpellProjectileComponent.h SpellSystem.cpp SpellSystem.h WorldSpellFollowBehaviour.cpp WorldSpellFollowBehaviour.h WorldSpellHitCallbackBehaviour.cpp WorldSpellHitCallbackBehaviour.h WorldSpellStraightBehaiour.cpp WorldSpellStraightBehaiour.h WorldSpellTimeDestroyBehaviour.cpp WorldSpellTimeDestroyBehaviour.h WorldSpell.cpp WorldSpell.h GenericAOESpell.cpp GenericAOESpell.h SpellScriptFactory.cpp SpellScriptFactory.h GameObjectSpellMgr.cpp GameObjectSpellMgr.h GenericAura.cpp GenericAura.h AuraScriptFactory.cpp AuraScriptFactory.h)

ADD_LIBRARY(ASDef_SpellSystem ${EXECPATH})
INCLUDE_DIRECTORIES(C:/Users/Relintai/Projects/Alter-Native/Lib/src/private)
INCLUDE_DIRECTORIES(C:/Users/Relintai/Projects/Alter-Native/Lib/src/public)

IF(UNIX)
IF(NOT ANDROID)
TARGET_LINK_LIBRARIES(ASDef_SpellSystem pthread)
ENDIF()
ENDIF(UNIX)
IF(WIN32)
TARGET_LINK_LIBRARIES(ASDef_SpellSystem Ws2_32.lib)
ENDIF(WIN32)

#COTIRE(ASDef_SpellSystem)
SET(PROJ_NAME ASDef_SpellSystem)

##################################################
#Find boost libraries
##################################################
INCLUDE($ENV{ALTERNATIVE_TOOLS_PATH}/Code/CMAKE-BOOST.cmake)
