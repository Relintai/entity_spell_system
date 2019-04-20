#include "GenericSpell.h"
GenericSpell::GenericSpell(Spell* spell) : SpellScript(spell){
	if (!Mathf::Approximately(spell->CastTime, (float)0)){
		this->hasCastTime = true;
	}
	if (!Mathf::Approximately(spell->Cooldown, (float)0)) {
		this->hasCooldown = true;
	}
	if ((spell->DamageMin > 0) && (spell->DamageMax > 0)) {
		this->damage = true;
	}
}
void GenericSpell::StartCasting(WorldEntity* caster, float spellScale)
{
	if ((this->spell->GenericSpellData->NeedsTarget || this->damage) && !this->hasCastTime) {
		if (!SpellScript::CanCastTarget(caster, 0)) {
			return;
		}
	}
	else {
		if (!SpellScript::CanCast(caster, 0)) {
			return;
		}
	}
	WorldEntity* worldEntity = null;
	if (this->spell->GenericSpellData->NeedsTarget || this->damage) {
		worldEntity = SpellScript::GetTarget(caster);
	}
	if (!this->hasCastTime) {
		if (this->spell->SpellRangeData->Enabled && !SpellScript::isInRange(caster, worldEntity)) {
			return;
		}
		this->HandleSpellEffect(caster, worldEntity, spellScale);
		return;
	}
	else {
		if (!SpellScript::SpellCostCheck(caster)) {
			return;
		}
		SpellScript::DoStartCasting(caster, this->spellId, this->spell->SpellName, this->spell->CastTime, !this->spell->GenericSpellData->CanMoveWhileCasting, spellScale);
		return;
	}
}
void GenericSpell::CastingFinished(WorldEntity* caster, float spellScale)
{
	WorldEntity* worldEntity = null;
	if (this->spell->GenericSpellData->NeedsTarget || this->damage) {
		worldEntity = SpellScript::GetTarget(caster);
	}
	if (this->spell->GenericSpellData->NeedsTarget && (worldEntity == null)) {
		return;
	}
	if (this->spell->SpellRangeData->Enabled && !SpellScript::isInRange(caster, worldEntity)) {
		return;
	}
	this->HandleSpellEffect(caster, worldEntity, spellScale);
	if (this->hasCastTime && !this->spell->GenericSpellData->CanMoveWhileCasting) {
		SpellScript::RemoveOnMoveHook(caster);
	}
}
void GenericSpell::SpellHit(WorldEntity* caster, WorldEntity* target, WorldSpell* worldSpell, Spell* spellGO, float spellScale)
{
	if (target->CompareTag(new String("Player"))) {
		if (this->damage) {
			SpellScript::DealDamage(caster, target, spellScale);
		}
		if (this->spell->SpellHealData->Enabled) {
			SpellScript::Heal(caster, caster, spellScale);
		}
		if (this->spell->CasterAuraApply != 0) {
			SpellScript::ApplyAura(this->spell->CasterAuraApply, caster, spellScale);
		}
		if (this->spell->CasterAuraApply2 != 0) {
			SpellScript::ApplyAura(this->spell->CasterAuraApply2, caster, spellScale);
		}
		if (this->spell->TargetAuraApply != 0) {
			SpellScript::ApplyAura(this->spell->TargetAuraApply, target, spellScale);
		}
		if (this->spell->TargetAuraApply2 != 0) {
			SpellScript::ApplyAura(this->spell->TargetAuraApply2, target, spellScale);
		}
		this->HandleSpellStatValueMod(caster);
	}
	if (this->spell->SpellProjectileData->DestroyOnImpact) {
		worldSpell->Destroy();
	}
}
void GenericSpell::OnPlayerMove(Entity* caster)
{
	SpellScript::DoCastFail((WorldEntity*)(caster), true);
}
void GenericSpell::HandleSpellEffect(WorldEntity* caster, WorldEntity* target, float spellScale)
{
	if (!SpellScript::SpellCostCheckAndRemove(caster)) {
		return;
	}
	if (!this->spell->SpellProjectileData->Enabled) {
		if (this->damage) {
			SpellScript::DealDamage(caster, target, spellScale);
		}
		if (this->spell->SpellHealData->Enabled) {
			SpellScript::Heal(caster, caster, spellScale);
		}
		if (this->spell->CasterAuraApply != 0) {
			SpellScript::ApplyAura(this->spell->CasterAuraApply, caster, spellScale);
		}
		if (this->spell->CasterAuraApply2 != 0) {
			SpellScript::ApplyAura(this->spell->CasterAuraApply2, caster, spellScale);
		}
		if (this->spell->TargetAuraApply != 0) {
			SpellScript::ApplyAura(this->spell->TargetAuraApply, caster, target, spellScale);
		}
		if (this->spell->TargetAuraApply2 != 0) {
			SpellScript::ApplyAura(this->spell->TargetAuraApply2, caster, target, spellScale);
		}
		this->HandleSpellStatValueMod(caster);
	}
	else {
		SpellScript::SpawnProjectile(caster, target, spellScale);
	}
	if (this->spell->HasGlobalCooldown && !this->hasCastTime) {
		SpellScript::TriggerGlobalCooldown(caster);
	}
	SpellScript::SpellResourceGive(caster);
	if (this->hasCooldown) {
		SpellScript::AddCooldown(caster, this->spellId, this->spell->Cooldown);
	}
	SpellScript::SpellCastSuccess(caster);
}
void GenericSpell::HandleSpellStatValueMod(WorldEntity* caster)
{
	if (!this->spell->SpellStatValueModData->Enabled) {
		return;
	}
	Stats* stats = caster->Stats;
	for (int i = 0; i < this->spell->SpellStatValueModData->StatValueMods->Count; i += 1) {
		SpellStatValueModAttributeHelper* spellStatValueModAttributeHelper = this->spell->SpellStatValueModData->StatValueMods->GetData(i);
		ValueStat* valueStat = (ValueStat*)(stats->GetSStatFromId(spellStatValueModAttributeHelper->Stat));
		if (spellStatValueModAttributeHelper->Stat != 0) {
			if (spellStatValueModAttributeHelper->HasValueMod) {
				ValueStat* expr_5B = valueStat;
				expr_5B->Current += spellStatValueModAttributeHelper->GiveValue;
			}
			if (spellStatValueModAttributeHelper->HasPercentMod) {
				ValueStat* expr_79 = valueStat;
				expr_79->Current += valueStat->Max * (spellStatValueModAttributeHelper->GivePercentValue / (float)100);
			}
		}
		else {
			if (spellStatValueModAttributeHelper->HasValueMod) {
				if (spellStatValueModAttributeHelper->GiveValue > (float)0) {
					stats->TakeHeal((int)(spellStatValueModAttributeHelper->GiveValue), false, caster);
				}
				else {
					stats->TakeDamage((int)(spellStatValueModAttributeHelper->GiveValue), false, caster);
				}
			}
			if (spellStatValueModAttributeHelper->HasPercentMod) {
				if (spellStatValueModAttributeHelper->GivePercentValue > (float)0) {
					stats->TakeHeal((int)(valueStat->Max * (spellStatValueModAttributeHelper->GivePercentValue / (float)100)), false, caster);
				}
				else {
					stats->TakeDamage((int)(valueStat->Max * (spellStatValueModAttributeHelper->GivePercentValue / (float)100)), false, caster);
				}
			}
		}
	}
}
void GenericSpell::COnSpellCastSuccess(WorldEntity* player)
{
	if (!this->hasCastTime && this->damage) {
		SpellScript::PlayStandardSpellCastFinish(player);
		return;
	}
	SpellScript::PlayStandardSpellCastFinish();
}
void GenericSpell::COnSpellCastStarted(WorldEntity* player)
{
	if (this->spell->SpellCastEffectData->Enabled) {
		SpellScript::AddSpellCastEffect(player);
	}
}
void GenericSpell::COnSpellCastEnded(WorldEntity* player)
{
	if (this->spell->SpellCastEffectData->Enabled) {
		SpellScript::RemoveSpellCastEffects(player);
	}
}

