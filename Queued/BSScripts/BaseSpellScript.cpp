#include "BaseSpellScript.h"
//Delegate declaration moved to header file
BaseSpellScript::CreateSpellScriptForAction* BaseSpellScript::CreateSpellScriptFor;
BaseSpellScript::BaseSpellScript(Spell* spell){
	this->spellId = spell->SpellID;
	this->spell = spell;
	spell->SpellScript = this;
}
void BaseSpellScript::StartCasting(Entity* caster, float spellScale)
{
}
void BaseSpellScript::CastingFinished(Entity* caster, float spellScale)
{
}
void BaseSpellScript::CastingFailed(Entity* caster)
{
}
void BaseSpellScript::SpellHit(Entity* caster, Entity* target, BaseWorldSpell* worldSpell, Spell* spell, float spellScale)
{
}
void BaseSpellScript::OnPlayerMove(Entity* caster)
{
}
void BaseSpellScript::COnSpellCastStarted(Entity* player)
{
}
void BaseSpellScript::COnSpellCastSuccess(Entity* player)
{
}
void BaseSpellScript::COnSpellCastFailed(Entity* player)
{
}
void BaseSpellScript::COnSpellCastEnded(Entity* player)
{
}
void BaseSpellScript::OnCastStateChanged(Entity* caster)
{
}

