#pragma once
#include <System/System.h>
#include "MonoBehaviour.h"
#include "Entity.h"
#include "BaseAuraComponent.h"
#include "DamagePipelineData.h"
#include "BaseOnPlayerMoveCallbackComponent.h"
#include <System/Collections/Generic/List.h>

using namespace UnityEngine;
using namespace BS::Player;
using namespace System::Collections::Generic;
using namespace System;
class SpellMgr : public virtual MonoBehaviour, public virtual Object
{
	public:
	static SpellMgr* getInstance();
	public:
	static void setInstance(SpellMgr* value);
	public:
	static void CastSpell(Entity* caster, int spellId, float scale);
	public:
	static void CastingFinished(Entity* caster, int spellId, float scale);
	public:
	static void UpdateAuras(BaseAuraComponent* auraComponent);
	public:
	static void OnHit(BaseAuraComponent* auraComponent, Entity* caster, Entity* target, MonoBehaviour* spell, int damage);
	public:
	static void POnBeforeDamage(BaseAuraComponent* ac, DamagePipelineData* data);
	public:
	static void OnDamageReceive(BaseAuraComponent* ac, Entity* caster, Entity* target, MonoBehaviour* spell, int damage);
	public:
	static void RemoveAurasWithGroup(BaseAuraComponent* ac, int auraGroup);
	public:
	static void CRefreshAura(BaseAuraComponent* ac, int auraId, float time);
	public:
	static void CRefreshCasterAura(BaseAuraComponent* ac, int auraId, Entity* caster, float time);
	public:
	static void CAuraAdded(BaseAuraComponent* ac, int id, float remaining, Entity* caster, uint casterGUID);
	public:
	static void CAuraRemoved(BaseAuraComponent* ac, int id);
	public:
	static void COnCastFailed(Entity* caster, int spellId);
	public:
	static void SetupOnPlayerMoves(BaseOnPlayerMoveCallbackComponent* bopmccc, List_T<int>* sspells);
	public:
	static void COnCastStarted(Entity* caster, int spellId);
	public:
	static void COnCastStateChanged(Entity* caster, int spellId);
	public:
	static void COnCastFinished(Entity* caster, int spellId);
	public:
	static void COnSpellCastSuccess(Entity* caster, int spellId);
	public:
	static String* RequestName(int spellId);
	public:
	static String* RequestDescription(int spellId, int level);
	public:
	virtual void MCastSpell(Entity* caster, int spellId, float scale);
	public:
	virtual void MCastingFinished(Entity* caster, int spellId, float scale);
	public:
	virtual void MUpdateAuras(BaseAuraComponent* ac);
	public:
	virtual void MOnHit(BaseAuraComponent* ac, Entity* caster, Entity* target, MonoBehaviour* spell, int damage);
	public:
	virtual void MPOnBeforeDamage(BaseAuraComponent* ac, DamagePipelineData* data);
	public:
	virtual void MOnDamageReceive(BaseAuraComponent* ac, Entity* caster, Entity* target, MonoBehaviour* spell, int damage);
	public:
	virtual void MRemoveAurasWithGroup(BaseAuraComponent* ac, int auraGroup);
	public:
	virtual void MCRefreshAura(BaseAuraComponent* ac, int auraId, float time);
	public:
	virtual void MCRefreshCasterAura(BaseAuraComponent* ac, int auraId, Entity* caster, float time);
	public:
	virtual void MCAuraAdded(BaseAuraComponent* ac, int id, float remaining, Entity* caster, uint casterGUID);
	public:
	virtual void MCAuraRemoved(BaseAuraComponent* ac, int id);
	public:
	virtual void MSetupOnPlayerMoves(BaseOnPlayerMoveCallbackComponent* bopmccc, List_T<int>* sspells);
	public:
	virtual void MCOnCastFailed(Entity* caster, int spellId);
	public:
	virtual void MCOnCastStarted(Entity* caster, int spellId);
	public:
	virtual void MCOnCastStateChanged(Entity* caster, int spellId);
	public:
	virtual void MCOnCastFinished(Entity* caster, int spellId);
	public:
	virtual void MCOnSpellCastSuccess(Entity* caster, int spellId);
	public:
	virtual String* MRequestName(int spellId);
	public:
	virtual String* MRequestDescription(int spellId, int level);
	private:
		void OnDestroy();
	public:
	static SpellMgr* Instance_var;
	public:
		SpellMgr();
};
