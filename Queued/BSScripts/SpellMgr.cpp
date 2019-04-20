#include "SpellMgr.h"
SpellMgr* SpellMgr::getInstance(){
	return Instance_var;
}
void SpellMgr::setInstance(SpellMgr* value)
{
	Instance_var = value;
}
void SpellMgr::CastSpell(Entity* caster, int spellId, float scale)
{
	SpellMgr::getInstance()->MCastSpell(caster, spellId, scale);
}
void SpellMgr::CastingFinished(Entity* caster, int spellId, float scale)
{
	SpellMgr::getInstance()->MCastingFinished(caster, spellId, scale);
}
void SpellMgr::UpdateAuras(BaseAuraComponent* auraComponent)
{
	SpellMgr::getInstance()->MUpdateAuras(auraComponent);
}
void SpellMgr::OnHit(BaseAuraComponent* auraComponent, Entity* caster, Entity* target, MonoBehaviour* spell, int damage)
{
	SpellMgr::getInstance()->MOnHit(auraComponent, caster, target, spell, damage);
}
void SpellMgr::POnBeforeDamage(BaseAuraComponent* ac, DamagePipelineData* data)
{
	SpellMgr::getInstance()->MPOnBeforeDamage(ac, data);
}
void SpellMgr::OnDamageReceive(BaseAuraComponent* ac, Entity* caster, Entity* target, MonoBehaviour* spell, int damage)
{
	SpellMgr::getInstance()->MOnDamageReceive(ac, caster, target, spell, damage);
}
void SpellMgr::RemoveAurasWithGroup(BaseAuraComponent* ac, int auraGroup)
{
	SpellMgr::getInstance()->MRemoveAurasWithGroup(ac, auraGroup);
}
void SpellMgr::CRefreshAura(BaseAuraComponent* ac, int auraId, float time)
{
	SpellMgr::getInstance()->MCRefreshAura(ac, auraId, time);
}
void SpellMgr::CRefreshCasterAura(BaseAuraComponent* ac, int auraId, Entity* caster, float time)
{
	SpellMgr::getInstance()->MCRefreshCasterAura(ac, auraId, caster, time);
}
void SpellMgr::CAuraAdded(BaseAuraComponent* ac, int id, float remaining, Entity* caster, uint casterGUID)
{
	SpellMgr::getInstance()->MCAuraAdded(ac, id, remaining, caster, casterGUID);
}
void SpellMgr::CAuraRemoved(BaseAuraComponent* ac, int id)
{
	SpellMgr::getInstance()->MCAuraRemoved(ac, id);
}
void SpellMgr::COnCastFailed(Entity* caster, int spellId)
{
	SpellMgr::getInstance()->MCOnCastFailed(caster, spellId);
}
void SpellMgr::SetupOnPlayerMoves(BaseOnPlayerMoveCallbackComponent* bopmccc, List_T<int>* sspells)
{
	SpellMgr::getInstance()->MSetupOnPlayerMoves(bopmccc, sspells);
}
void SpellMgr::COnCastStarted(Entity* caster, int spellId)
{
	SpellMgr::getInstance()->MCOnCastStarted(caster, spellId);
}
void SpellMgr::COnCastStateChanged(Entity* caster, int spellId)
{
	SpellMgr::getInstance()->MCOnCastStateChanged(caster, spellId);
}
void SpellMgr::COnCastFinished(Entity* caster, int spellId)
{
	SpellMgr::getInstance()->MCOnCastFinished(caster, spellId);
}
void SpellMgr::COnSpellCastSuccess(Entity* caster, int spellId)
{
	SpellMgr::getInstance()->MCOnSpellCastSuccess(caster, spellId);
}
String* SpellMgr::RequestName(int spellId)
{
	return SpellMgr::getInstance()->MRequestName(spellId);
}
String* SpellMgr::RequestDescription(int spellId, int level)
{
	return SpellMgr::getInstance()->MRequestDescription(spellId, level);
}
void SpellMgr::MCastSpell(Entity* caster, int spellId, float scale)
{
}
void SpellMgr::MCastingFinished(Entity* caster, int spellId, float scale)
{
}
void SpellMgr::MUpdateAuras(BaseAuraComponent* ac)
{
}
void SpellMgr::MOnHit(BaseAuraComponent* ac, Entity* caster, Entity* target, MonoBehaviour* spell, int damage)
{
}
void SpellMgr::MPOnBeforeDamage(BaseAuraComponent* ac, DamagePipelineData* data)
{
}
void SpellMgr::MOnDamageReceive(BaseAuraComponent* ac, Entity* caster, Entity* target, MonoBehaviour* spell, int damage)
{
}
void SpellMgr::MRemoveAurasWithGroup(BaseAuraComponent* ac, int auraGroup)
{
}
void SpellMgr::MCRefreshAura(BaseAuraComponent* ac, int auraId, float time)
{
}
void SpellMgr::MCRefreshCasterAura(BaseAuraComponent* ac, int auraId, Entity* caster, float time)
{
}
void SpellMgr::MCAuraAdded(BaseAuraComponent* ac, int id, float remaining, Entity* caster, uint casterGUID)
{
}
void SpellMgr::MCAuraRemoved(BaseAuraComponent* ac, int id)
{
}
void SpellMgr::MSetupOnPlayerMoves(BaseOnPlayerMoveCallbackComponent* bopmccc, List_T<int>* sspells)
{
}
void SpellMgr::MCOnCastFailed(Entity* caster, int spellId)
{
}
void SpellMgr::MCOnCastStarted(Entity* caster, int spellId)
{
}
void SpellMgr::MCOnCastStateChanged(Entity* caster, int spellId)
{
}
void SpellMgr::MCOnCastFinished(Entity* caster, int spellId)
{
}
void SpellMgr::MCOnSpellCastSuccess(Entity* caster, int spellId)
{
}
String* SpellMgr::MRequestName(int spellId)
{
	return new String("");
}
String* SpellMgr::MRequestDescription(int spellId, int level)
{
	return new String("");
}
void SpellMgr::OnDestroy()
{
	SpellMgr::setInstance(null);
}
SpellMgr* SpellMgr::Instance_var;
SpellMgr::SpellMgr()
{
	Instance_var = (SpellMgr*)(0);
}

