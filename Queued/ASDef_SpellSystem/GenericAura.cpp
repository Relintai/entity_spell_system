#include "GenericAura.h"
namespace BS {
	namespace AurasNS {
		namespace Generic {
			GenericAura::GenericAura(Aura* aura) : AuraScript(aura){
				if (aura->GenericAuraData->AttributeModifiers->Count > 0){
					this->hasModifiers = true;
				}
			}
			void GenericAura::Apply(WorldEntity* caster, WorldEntity* target, float spellScale)
			{
				if (this->aura->AuraGroup != 0) {
					AuraScript::RemoveActiveGroupAuras(target);
				}
				if (((this->hasModifiers && !this->aura->AuraDamageData->Enabled) && !this->aura->AuraAbsorbData->Enabled) && !this->aura->AuraHealData->Enabled) {
					if (AuraScript::ShouldApplyModifiers(target, this->aura->Time, caster, spellScale)) {
						this->ApplyModifiers(target);
					}
					return;
				}
				if (this->aura->AuraDamageData->Enabled) {
					AuraScript::AddOrRefreshDamageAuraDataToTarget(target, caster, spellScale, this->aura->Time, this->aura->AuraDamageData->Tick, AuraScript::CalculateDamage(caster, target, spellScale));
				}
				if (this->aura->AuraHealData->Enabled) {
					AuraScript::AddOrRefreshHealAuraDataToTarget(target, caster, spellScale, this->aura->Time, this->aura->AuraHealData->Tick, AuraScript::CalculateHeal(caster, target, spellScale));
				}
				if (this->aura->AuraAbsorbData->Enabled) {
					AuraScript::AddOrRefreshShieldAuraDataToTarget(target, caster, spellScale, this->aura->Time, AuraScript::CalculateAbsorb(caster, target, spellScale));
				}
			}
			void GenericAura::DeApply(WorldEntity* target, AuraData* data)
			{
				if (this->hasModifiers && AuraScript::ShouldRemoveModifiers(target)) {
					this->RemoveModifiers(target);
				}
			}
			bool GenericAura::AuraUpdate(WorldEntity* target, AuraData* data)
			{
				bool flag = false;
				if (this->aura->AuraDamageData->Enabled) {
					flag = AuraScript::UpdateDamageAura(target, data);
				}
				if (this->aura->AuraHealData->Enabled) {
					bool flag2 = AuraScript::UpdateHealAura(target, data);
					if (!flag) {
						flag = flag2;
					}
				}
				if (!this->aura->AuraDamageData->Enabled && !this->aura->AuraHealData->Enabled) {
					return AuraScript::AuraUpdate(target, data);
				}
				return flag;
			}
			void GenericAura::POnBeforeDamage(DamagePipelineData* data, AuraData* auraData)
			{
				if (this->aura->AuraAbsorbData->Enabled) {
					AuraScript::AbsorbPOnBeforeDamage(data, auraData);
				}
			}
			void GenericAura::COnAdded(WorldEntity* target, Aura* data, AuraData* auraData)
			{
				this->ApplyEffect(target);
			}
			void GenericAura::COnRemoved(WorldEntity* target, Aura* data)
			{
				this->RemoveEffect(target);
			}
			void GenericAura::ApplyEffect(WorldEntity* target)
			{
				if (!this->aura->AuraEffectData->Enabled) {
					return;
				}
				if (this->aura->AuraEffectData->EffectPoint1 != EffectPoints::NONE) {
					AuraScript::AddEffect(target, this->aura->AuraEffectData->EffectPrefab, this->aura->AuraEffectData->EffectPoint1, );
				}
				if (this->aura->AuraEffectData->EffectPoint2 != EffectPoints::NONE) {
					AuraScript::AddEffect(target, this->aura->AuraEffectData->EffectPrefab, this->aura->AuraEffectData->EffectPoint2, );
				}
			}
			void GenericAura::RemoveEffect(WorldEntity* target)
			{
				if (!this->aura->AuraEffectData->Enabled) {
					return;
				}
				if (this->aura->AuraEffectData->EffectPoint1 != EffectPoints::NONE) {
					AuraScript::RemoveEffect(target, this->aura->AuraEffectData->EffectPoint1);
				}
				if (this->aura->AuraEffectData->EffectPoint2 != EffectPoints::NONE) {
					AuraScript::RemoveEffect(target, this->aura->AuraEffectData->EffectPoint2);
				}
			}
			void GenericAura::ApplyModifiers(WorldEntity* target)
			{
				for (int i = 0; i < this->aura->GenericAuraData->AttributeModifiers->Count; i += 1) {
					GenericAuraAttributeHelper* genericAuraAttributeHelper = this->aura->GenericAuraData->AttributeModifiers->GetData(i);
					AuraScript::AddStatModifier(target, genericAuraAttributeHelper->Stat, genericAuraAttributeHelper->MaxMod, genericAuraAttributeHelper->PercentMod);
				}
			}
			void GenericAura::RemoveModifiers(WorldEntity* target)
			{
				for (int i = 0; i < this->aura->GenericAuraData->AttributeModifiers->Count; i += 1) {
					GenericAuraAttributeHelper* genericAuraAttributeHelper = this->aura->GenericAuraData->AttributeModifiers->GetData(i);
					AuraScript::RemoveStatModifier(target, genericAuraAttributeHelper->Stat);
				}
			}

		}
	}
}
