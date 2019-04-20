#include "SpellSystem.h"
void SpellSystem::Awake(){
	SpellScript::InitFactory();
	AuraScript::InitFactory();
}

