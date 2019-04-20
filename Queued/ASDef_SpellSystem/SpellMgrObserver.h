#pragma once
#include <System/System.h>
#include "SpellMgr.h"
#include "Entity.h"
#include "Spells.h"
#include "Debug.h"
#include "Spell.h"
#include "SpellScript.h"
#include "WorldEntity.h"
#include "BaseAuraComponent.h"
#include "AuraComponent.h"
#include "AuraData.h"
#include "AuraScript.h"
#include "MonoBehaviour.h"
#include "DamagePipelineData.h"
#include "Auras.h"
#include "Aura.h"
#include "BaseOnPlayerMoveCallbackComponent.h"
#include <System/Collections/Generic/List.h>
#include "OnPlayerMoveCallbackComponent.h"

using namespace BS::Player;
using namespace UnityEngine;
using namespace System::Collections::Generic;
using namespace System;
class SpellMgrObserver : public virtual SpellMgr, public virtual Object
{
	public:
		void Awake();
	private:
		void OnDestroy();
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
};
