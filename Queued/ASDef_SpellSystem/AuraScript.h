#pragma once
#include <System/System.h>
#include "BaseAuraScript.h"
#include "DamagePipelineData.h"
#include "Aura.h"
#include "Entity.h"
#include "WorldEntity.h"
#include "AuraData.h"
#include "MonoBehaviour.h"
#include "GameObject.h"
#include "Time.h"
#include "Debug.h"
#include "AuraComponent.h"
#include "DiminishingReturnAuraData.h"
#include "DamageCountAuraData.h"
#include "BaseAuraComponent.h"
#include "DamageAuraData.h"
#include "HealAuraData.h"
#include "ShieldAuraData.h"
#include "StateData.h"
#include "AuraDamageData.h"
#include "UnityEngine.h"
#include "PlayerData.h"
#include "Stats.h"
#include "PercentStat.h"
#include "AuraHealData.h"
#include "AuraAbsorbData.h"
#include "SpellType.h"
#include "EffectPoints.h"
#include "Quaternion.h"
#include "Transform.h"
#include "IEffectPointGetter.h"
#include "Vector3.h"
#include "EffectAuraIdAttribute.h"
#include "Auras.h"
#include "Mathf.h"
#include "GenericAura.h"

using namespace BS::Player;
using namespace UnityEngine;
using namespace BS::AurasNS::Generic;
using namespace System;
//Forward Declaration
class GenericAura;

class AuraScript : public virtual BaseAuraScript, public virtual Object{
	public:
		int DIMINISHING_RETURN_ROOT_AURA_ID;
	public:
		float DIMINISHING_RETURN_TIME;
	public:
		DamagePipelineData* damagePipelineData;
	public:
		AuraScript(Aura* aura);
	public:
	virtual void Apply(Entity* caster, Entity* target, float spellScale);
	public:
	virtual bool AuraUpdate(Entity* target, AuraData* data);
	public:
	virtual void DeApply(Entity* target, AuraData* data);
	public:
	virtual void OnDamageReceive(Entity* caster, Entity* target, MonoBehaviour* spell, AuraData* aura, int damage);
	public:
	virtual void OnHit(Entity* caster, Entity* target, MonoBehaviour* spell, AuraData* aura, int damage);
	public:
	virtual void OnDispell(Entity* caster);
	public:
	virtual void OnRemove(Entity* caster);
	public:
	virtual void COnAdded(Entity* target, Aura* data, AuraData* aura);
	public:
	virtual void COnRemoved(Entity* target, Aura* data);
	public:
	virtual void COnRefresh(Entity* target, GameObject* data, AuraData* aura);
	public:
	virtual void Apply(WorldEntity* caster, WorldEntity* target, float spellScale);
	public:
	virtual bool AuraUpdate(WorldEntity* target, AuraData* data);
	public:
	virtual void DeApply(WorldEntity* target, AuraData* data);
	public:
	virtual void OnDamageReceive(WorldEntity* caster, WorldEntity* target, MonoBehaviour* spell, AuraData* aura, int damage);
	public:
	virtual void OnHit(WorldEntity* caster, WorldEntity* target, MonoBehaviour* spell, AuraData* aura, int damage);
	public:
	virtual void OnDispell(WorldEntity* caster);
	public:
	virtual void OnRemove(WorldEntity* caster);
	public:
	virtual void COnAdded(WorldEntity* target, Aura* data, AuraData* aura);
	public:
	virtual void COnRemoved(WorldEntity* target, Aura* data);
	public:
	virtual void COnRefresh(WorldEntity* target, GameObject* data, AuraData* aura);
	public:
		void RemoveAura(WorldEntity* caster);
	public:
		bool ShouldApplyModifiers(WorldEntity* target);
	public:
		bool BasicAuraUpdate(WorldEntity* target, AuraData* data);
	public:
		bool ShouldApplyModifiers(WorldEntity* target, float refreshTo);
	public:
		bool ShouldApplyModifiers(WorldEntity* target, float refreshTo, WorldEntity* caster, float spellScale);
	public:
		bool ShouldRemoveModifiers(WorldEntity* target);
	public:
		void RefreshDamageCountAuraDiminished(WorldEntity* target, float refreshTo, WorldEntity* caster, DiminishingReturnAuraData::DiminishingReturnCategory diminsihingType, DamageCountAuraData* aura);
	public:
		void AddAuraDataToTarget(WorldEntity* target, AuraData* data);
	public:
		void AddAuraDataToTarget(WorldEntity* target, WorldEntity* caster, float duration, float spellScale);
	public:
		void AddOrRefreshDamageAuraDataToTarget(WorldEntity* target, WorldEntity* caster, float spellScale, float duration, float tick, int damage);
	public:
		void AddOrRefreshHealAuraDataToTarget(WorldEntity* target, WorldEntity* caster, float spellScale, float duration, float tick, int heal);
	public:
		void AddOrRefreshShieldAuraDataToTarget(WorldEntity* target, WorldEntity* caster, float spellScale, float duration, int absorb);
	public:
		void AddOrRefreshDiminishingReturnAura(WorldEntity* target, DiminishingReturnAuraData::DiminishingReturnCategory diminishingCategory);
	public:
		void AddStatModifier(WorldEntity* target, int stat, float maxMod, float percentMod);
	public:
		void RemoveStatModifier(WorldEntity* target, int stat);
	public:
		void AddState(WorldEntity* target, StateData::StateType state);
	public:
		void RemoveState(WorldEntity* target, StateData::StateType state);
	public:
		void RemovethisAura(WorldEntity* target);
	public:
		AuraData* TargetHasCastersAura(WorldEntity* target, WorldEntity* caster);
	public:
		AuraData* TargetHasAura(WorldEntity* target);
	public:
		int CalculateDamage(WorldEntity* caster, WorldEntity* target, float spellScale);
	public:
		int CalculateHeal(WorldEntity* caster, WorldEntity* target, float spellScale);
	public:
		int CalculateAbsorb(WorldEntity* caster, WorldEntity* target, float spellScale);
	public:
		void UpdateDamageCountAura(WorldEntity* target, AuraData* aura, int damage, float breakHealthPercent);
	public:
		bool UpdateDamageAura(WorldEntity* target, AuraData* data);
	public:
		bool UpdateDamageAuraTickBool(WorldEntity* target, AuraData* data);
	public:
		bool UpdateHealAura(WorldEntity* target, AuraData* data);
	public:
		void AbsorbPOnBeforeDamage(DamagePipelineData* data, AuraData* aura);
	public:
		void DealDamage(WorldEntity* target, DamageAuraData* data);
	public:
		void DealDamage(WorldEntity* target, DamageAuraData* data, int damage);
	public:
		void DealDamage(WorldEntity* target, WorldEntity* caster, int damage);
	public:
		void DealDamageWithoutOnHit(WorldEntity* target, WorldEntity* caster, int damage);
	public:
		void Heal(WorldEntity* target, HealAuraData* data);
	public:
		void Heal(WorldEntity* target, HealAuraData* data, int heal);
	public:
		void Heal(WorldEntity* target, AuraData* data, int heal);
	public:
		DiminishingReturnAuraData* GetDiminishingReturnAuraDataFor(WorldEntity* target, DiminishingReturnAuraData::DiminishingReturnCategory type);
	public:
		float GetDiminishedTime(WorldEntity* target, DiminishingReturnAuraData::DiminishingReturnCategory diminsihingType, float time);
	public:
		void AddEffect(WorldEntity* player, EffectPoints bodyPart, Quaternion* rotation = );
	public:
		void AddEffect(WorldEntity* player, GameObject* effectPrefab, EffectPoints bodyPart, Quaternion* rotation = );
	public:
		void RemoveEffect(WorldEntity* player, EffectPoints bodyPart);
	public:
		void RemoveActiveGroupAuras(WorldEntity* target);
	public:
		float GetDiminishedTime(WorldEntity* target, DiminishingReturnAuraData* aura, float time);
	public:
		int GetAuraIdForDiminishingReturn(DiminishingReturnAuraData::DiminishingReturnCategory type);
	public:
		AuraData* getAuraData(WorldEntity* target, int pAuraId);
	public:
		void ApplyAura(int auraId, WorldEntity* caster, WorldEntity* target, float spellScale);
	public:
		bool IsZero(float x);
	public:
	static void InitFactory();
	public:
	static void SSCreateFor(Aura* aura);
};
