#include "spell_manager.h"

SpellManager *SpellManager::_instance;

SpellManager *SpellManager::get_instance() {
	return _instance;
}

SpellManager::SpellManager() {
	SpellManager::_instance = this;
}

SpellManager::~SpellManager() {
	SpellManager::_instance = NULL;
}

void SpellManager::CastSpell(Entity *caster, int spellId, float scale) {
}

void SpellManager::CastingFinished(Entity *caster, int spellId, float scale) {
}

void SpellManager::UpdateAuras(Entity *ac) {
}

void SpellManager::OnHit(Entity *ac, Entity *caster, Entity *target, Spell *spell, int damage) {
}

void SpellManager::POnBeforeDamage(Entity *ac, SpellDamageInfo *data) {
}

void SpellManager::OnDamageReceive(Entity *ac, Entity *caster, Entity *target, Spell *spell, int damage) {
}

void SpellManager::RemoveAurasWithGroup(Entity *ac, int auraGroup) {
}

void SpellManager::CRefreshAura(Entity *ac, int auraId, float time) {
}

void SpellManager::CRefreshCasterAura(Entity *ac, int auraId, Entity *caster, float time) {
}

void SpellManager::CAuraAdded(Entity *ac, int id, float remaining, Entity *caster, int casterGUID) {
}

void SpellManager::CAuraRemoved(Entity *ac, int id) {
}

void SpellManager::SetupOnPlayerMoves(Entity *bopmccc, Vector<int> *sspells) {
}

void SpellManager::COnCastFailed(Entity *caster, int spellId) {
}

void SpellManager::COnCastStarted(Entity *caster, int spellId) {
}

void SpellManager::COnCastStateChanged(Entity *caster, int spellId) {
}

void SpellManager::COnCastFinished(Entity *caster, int spellId) {
}

void SpellManager::COnSpellCastSuccess(Entity *caster, int spellId) {
}

String SpellManager::RequestName(int spellId) {
	return "";
}

String SpellManager::RequestDescription(int spellId, int level) {
	return "";
}

/*

void SpellManager::CastSpell(Entity *caster, int spellId, float scale) {
	if (!Spells::Instance->SpellsDict->ContainsKey(spellId)) {
		Debug::Log(*(new String("SpellManager->castSpell: SpellID Doesn't exists! spellId:")) + BOX<int>(spellId));
		return;
	}
	Spell *spell = Spells::Instance->SpellsDict->GetData(spellId);
	if (spell == null) {
		Debug::Log(new String("SpellManager->castSpell: SpellData is null!"));
		return;
	}
	(SpellScript *)(spell->SpellScript)->StartCasting((WorldEntity *)(caster), scale);
}

void SpellManager::CastingFinished(Entity *caster, int spellId, float scale) {
	if (!Spells::Instance->SpellsDict->ContainsKey(spellId)) {
		Debug::Log(new String("SpellManager->CastingFinished: SpellID Doesn't exists!"));
		return;
	}
	Spell *spell = Spells::Instance->SpellsDict->GetData(spellId);
	if (spell == null) {
		Debug::Log(new String("SpellManager->CastingFinished: SpellData is null!"));
		return;
	}
	(SpellScript *)(spell->SpellScript)->CastingFinished((WorldEntity *)(caster), scale);
}

void SpellManager::UpdateAuras(Entity *ac) {
	AuraComponent *auraComponent = as_cast<AuraComponent *>(ac);
	for (int i = 0; i < auraComponent->serverAuras->Count; i += 1) {
		AuraData *auraData = auraComponent->serverAuras->GetData(i);
		AuraScript *auraScript = (AuraScript *)(auraData->Aura->AuraScript);
		if (auraScript == null) {
			Debug::Log(*(new String("AuraComponent->Update(): Aurascript is null! AuraId: ")) + BOX<int>(auraData->AuraId));
		} else {
			if (auraScript->AuraUpdate(auraComponent->Owner, auraData)) {
				auraComponent->serverAuras->RemoveAt(i);
				auraComponent->CReceiveAuraRemoved(auraData->AuraId);
				i -= 1;
			}
		}
	}
}

void SpellManager::OnHit(Entity *ac, Entity *caster, Entity *target, MonoBehaviour *spell, int damage) {
	AuraComponent *auraComponent = as_cast<AuraComponent *>(ac);
	int count = auraComponent->serverAuras->Count;
	for (int i = 0; i < auraComponent->serverAuras->Count; i += 1) {
		(AuraScript *)(auraComponent->serverAuras->GetData(i)->Aura->AuraScript)->OnHit((WorldEntity *)(caster), (WorldEntity *)(target), spell, auraComponent->serverAuras->GetData(i), damage);
		if (count != auraComponent->serverAuras->Count) {
			i -= count - *auraComponent->serverAuras->Count;
			count = auraComponent->serverAuras->Count;
		}
	}
}

void SpellManager::POnBeforeDamage(Entity *ac, SpellDamageInfo *data) {
	AuraComponent *auraComponent = as_cast<AuraComponent *>(ac);
	int count = auraComponent->serverAuras->Count;
	for (int i = 0; i < auraComponent->serverAuras->Count; i += 1) {
		(AuraScript *)(auraComponent->serverAuras->GetData(i)->Aura->AuraScript)->POnBeforeDamage(data, auraComponent->serverAuras->GetData(i));
		if (count != auraComponent->serverAuras->Count) {
			i -= count - *auraComponent->serverAuras->Count;
			count = auraComponent->serverAuras->Count;
		}
	}
}

void SpellManager::OnDamageReceive(Entity *ac, Entity *caster, Entity *target, MonoBehaviour *spell, int damage) {
	AuraComponent *auraComponent = as_cast<AuraComponent *>(ac);
	int count = auraComponent->serverAuras->Count;
	for (int i = 0; i < auraComponent->serverAuras->Count; i += 1) {
		(AuraScript *)(auraComponent->serverAuras->GetData(i)->Aura->AuraScript)->OnDamageReceive((WorldEntity *)(caster), (WorldEntity *)(target), spell, auraComponent->serverAuras->GetData(i), damage);
		if (count != auraComponent->serverAuras->Count) {
			i -= count - *auraComponent->serverAuras->Count;
			count = auraComponent->serverAuras->Count;
		}
	}
}

void SpellManager::RemoveAurasWithGroup(Entity *ac, int auraGroup) {
	AuraComponent *auraComponent = as_cast<AuraComponent *>(ac);
	for (int i = 0; i < auraComponent->serverAuras->Count; i += 1) {
		AuraData *auraData = auraComponent->serverAuras->GetData(i);
		if (auraData->AuraGroup == auraGroup) {
			(AuraScript *)(Auras::Instance->GetData(auraData->AuraId)->AuraScript)->DeApply(auraComponent->Owner, auraData);
			auraComponent->serverAuras->RemoveAt(i);
			i -= 1;
			auraComponent->CReceiveAuraRemoved(auraData->AuraId);
		}
	}
}

void SpellManager::CRefreshAura(Entity *ac, int auraId, float time) {
	AuraComponent *auraComponent = as_cast<AuraComponent *>(ac);
	for (int i = 0; i < auraComponent->auras->Count; i += 1) {
		if (auraComponent->auras->GetData(i)->AuraId == auraId) {
			auraComponent->auras->GetData(i)->Remaining = time;
			Aura *aura = auraComponent->auras->GetData(i)->Aura;
			(AuraScript *)(aura->AuraScript)->COnRefresh((WorldEntity *)(auraComponent->auras->GetData(i)->Caster), aura->gameObject, auraComponent->auras->GetData(i));
			return;
		}
	}
}

void SpellManager::CRefreshCasterAura(Entity *ac, int auraId, Entity *caster, float time) {
	AuraComponent *auraComponent = as_cast<AuraComponent *>(ac);
	for (int i = 0; i < auraComponent->auras->Count; i += 1) {
		if ((auraComponent->auras->GetData(i)->AuraId == auraId) && (auraComponent->auras->GetData(i)->Caster == *caster)) {
			auraComponent->auras->GetData(i)->Remaining = time;
			Aura *aura = auraComponent->auras->GetData(i)->Aura;
			(AuraScript *)(aura->AuraScript)->COnRefresh((WorldEntity *)(caster), aura->gameObject, auraComponent->auras->GetData(i));
			return;
		}
	}
}

void SpellManager::CAuraAdded(Entity *ac, int id, float remaining, Entity *caster, uint casterGUID) {
	AuraComponent *arg_18_0 = as_cast<AuraComponent *>(ac);
	AuraData *auraData = new AuraData(id, remaining, caster, casterGUID, 0, (float)1);
	arg_18_0->auras->Add(auraData);
	Aura *aura = Auras::Instance->GetData(id);
	(AuraScript *)(aura->AuraScript)->COnAdded((WorldEntity *)(caster), aura, auraData);
}

void SpellManager::CAuraRemoved(Entity *ac, int id) {
	AuraComponent *auraComponent = as_cast<AuraComponent *>(ac);
	for (int i = 0; i < auraComponent->auras->Count; i += 1) {
		if (auraComponent->auras->GetData(i)->AuraId == id) {
			auraComponent->auras->RemoveAt(i);
			Aura *aura = Auras::Instance->GetData(id);
			(AuraScript *)(aura->AuraScript)->COnRemoved(auraComponent->Owner, aura);
			return;
		}
	}
}

void SpellManager::SetupOnPlayerMoves(BaseOnPlayerMoveCallbackComponent *bopmccc, List_T<int> *sspells) {
	OnPlayerMoveCallbackComponent *onPlayerMoveCallbackComponent = as_cast<OnPlayerMoveCallbackComponent *>(bopmccc);
	for (int i = 0; i < sspells->Count; i += 1) {
		BaseOnPlayerMoveCallbackComponent *arg_38_0 = onPlayerMoveCallbackComponent;
		SpellScript *expr_2C = (SpellScript *)(Spells::Instance->SpellsDict->GetData(sspells->GetData(i))->SpellScript);
		arg_38_0->SOnPlayerMove += *(new BaseOnPlayerMoveCallbackComponent::OnPlayerMoved(expr_2C->OnPlayerMove));
	}
}

void SpellManager::COnCastFailed(Entity *caster, int spellId) {
	Spell *spell;
	if (!Spells::Instance->SpellsDict->TryGetValue(spellId, spell)) {
		return;
	}
	(SpellScript *)(spell->SpellScript)->COnSpellCastEnded((WorldEntity *)(caster));
}

void SpellManager::COnCastStarted(Entity *caster, int spellId) {
	Spell *spell;
	if (!Spells::Instance->SpellsDict->TryGetValue(spellId, spell)) {
		return;
	}
	(SpellScript *)(spell->SpellScript)->COnSpellCastStarted((WorldEntity *)(caster));
}

void SpellManager::COnCastStateChanged(Entity *caster, int spellId) {
	Spell *spell;
	if (!Spells::Instance->SpellsDict->TryGetValue(spellId, spell)) {
		return;
	}
	(SpellScript *)(spell->SpellScript)->OnCastStateChanged((WorldEntity *)(caster));
}

void SpellManager::COnCastFinished(Entity *caster, int spellId) {
	Spell *spell;
	if (!Spells::Instance->SpellsDict->TryGetValue(spellId, spell)) {
		return;
	}
	(SpellScript *)(spell->SpellScript)->COnSpellCastEnded((WorldEntity *)(caster));
}

void SpellManager::COnSpellCastSuccess(Entity *caster, int spellId) {
	Spell *spell;
	if (!Spells::Instance->SpellsDict->TryGetValue(spellId, spell)) {
		return;
	}
	(SpellScript *)(spell->SpellScript)->COnSpellCastSuccess((WorldEntity *)(caster));
}

String SpellManager::RequestName(int spellId) {
	Spell *spell;
	if (!Spells::Instance->SpellsDict->TryGetValue(spellId, spell)) {
		return new String("");
	}
	return (SpellScript *)(spell->SpellScript)->GetName();
}

String SpellManager::RequestDescription(int spellId, int level) {
	Spell *spell;
	if (!Spells::Instance->SpellsDict->TryGetValue(spellId, spell)) {
		return new String("");
	}
	return (SpellScript *)(spell->SpellScript)->GetDescription(level);
}*/

void SpellManager::_bind_methods() {
}
