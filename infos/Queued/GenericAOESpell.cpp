#include "GenericAOESpell.h"
namespace BS {
namespace SpellsNS {
namespace generic {
GenericAOESpell::GenericAOESpell(Spell *spell) :
		SpellScript(spell) {
	if (!Mathf::Approximately(spell->CastTime, (float)0)) {
		this->hasCastTime = true;
	}
	if (!Mathf::Approximately(spell->Cooldown, (float)0)) {
		this->hasCooldown = true;
	}
	this->genericSpellAttribute = spell->GenericSpellData;
	this->spellHealAttribute = spell->SpellHealData;
	if (this->spellHealAttribute != null) {
		this->heal = true;
	}
	if ((spell->DamageMin > 0) && (spell->DamageMax > 0)) {
		this->damage = true;
	}
	this->aoeAttrib = spell->SpellAOEData;
	if (this->aoeAttrib == null) {
		Debug::LogError((*(new String("Spell ")) + *(spell->name)) + *(new String(" doesn't have an AOEAttribute attached!")));
	}
	this->rangeAttrib = spell->SpellRangeData;
	if (this->rangeAttrib != null) {
		this->range = true;
	}
	this->spellCastEffectAttribute = spell->SpellCastEffectData;
	if (this->spellCastEffectAttribute != null) {
		this->hasSpellCastEffect = true;
	}
}
void GenericAOESpell::StartCasting(WorldEntity *caster, float spellScale) {
	if ((this->genericSpellAttribute->NeedsTarget || this->damage) && !this->hasCastTime) {
		if (!SpellScript::CanCastTarget(caster, 0)) {
			return;
		}
	} else {
		if (!SpellScript::CanCast(caster, 0)) {
			return;
		}
	}
	WorldEntity *worldEntity = null;
	if (this->genericSpellAttribute->NeedsTarget || this->damage) {
		worldEntity = SpellScript::GetTarget(caster);
	}
	if (!this->hasCastTime) {
		if (this->range && !SpellScript::isInRange(caster, worldEntity)) {
			return;
		}
		this->HandleSpellEffect(caster, worldEntity, spellScale);
		return;
	} else {
		if (!SpellScript::SpellCostCheck(caster)) {
			return;
		}
		SpellScript::DoStartCasting(caster, this->spellId, this->spell->NameKey, this->spell->CastTime, !this->genericSpellAttribute->CanMoveWhileCasting, spellScale);
		return;
	}
}
void GenericAOESpell::CastingFinished(WorldEntity *caster, float spellScale) {
	WorldEntity *worldEntity = null;
	if (this->genericSpellAttribute->NeedsTarget || this->damage) {
		worldEntity = SpellScript::GetTarget(caster);
	}
	if (this->genericSpellAttribute->NeedsTarget && (worldEntity == null)) {
		return;
	}
	if (this->range && !SpellScript::isInRange(caster, worldEntity)) {
		return;
	}
	this->HandleSpellEffect(caster, worldEntity, spellScale);
	if (this->hasCastTime && !this->genericSpellAttribute->CanMoveWhileCasting) {
		SpellScript::RemoveOnMoveHook(caster);
	}
}
void GenericAOESpell::SpellHit(WorldEntity *caster, WorldEntity *target, WorldSpell *worldSpell, Spell *spellGo, float spellScale) {
	if (target->CompareTag(new String("Player"))) {
		if (this->damage) {
			SpellScript::DealDamage(caster, target, spellScale);
		}
		if (this->heal) {
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
	}
	worldSpell->Destroy();
}
void GenericAOESpell::OnPlayerMove(Entity *caster) {
	SpellScript::DoCastFail((WorldEntity *)(caster), true);
}
void GenericAOESpell::HandleSpellEffect(WorldEntity *caster, WorldEntity *target, float spellScale) {
	if (!SpellScript::SpellCostCheckAndRemove(caster)) {
		return;
	}
	if (this->damage) {
		SpellScript::DealDamage(caster, target, spellScale);
	}
	if (this->heal) {
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
	if (this->spell->HasGlobalCooldown) {
		SpellScript::TriggerGlobalCooldown(caster);
	}
	SpellScript::SpellResourceGive(caster);
	if (this->hasCooldown) {
		SpellScript::AddCooldown(caster, this->spellId, this->spell->Cooldown);
	}
	SpellScript::SpellCastSuccess(caster);
}
void GenericAOESpell::COnSpellCastSuccess(WorldEntity *player) {
	if (!this->hasCastTime) {
		SpellScript::PlayStandardSpellCastFinish(player);
		return;
	}
	SpellScript::PlayStandardSpellCastFinish();
}
void GenericAOESpell::COnSpellCastStarted(WorldEntity *player) {
	if (this->hasSpellCastEffect) {
		SpellScript::AddSpellCastEffect(player);
	}
}
void GenericAOESpell::COnSpellCastEnded(WorldEntity *player) {
	if (this->hasSpellCastEffect) {
		SpellScript::RemoveSpellCastEffects(player);
	}
}

} // namespace generic
} // namespace SpellsNS
} // namespace BS
