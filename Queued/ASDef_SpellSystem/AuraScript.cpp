#include "AuraScript.h"
AuraScript::AuraScript(Aura* aura) : BaseAuraScript(aura){
	damagePipelineData = new DamagePipelineData();
	DIMINISHING_RETURN_TIME = (float)15;
	DIMINISHING_RETURN_ROOT_AURA_ID = 1;
}
void AuraScript::Apply(Entity* caster, Entity* target, float spellScale)
{
	this->Apply((WorldEntity*)(caster), (WorldEntity*)(target), spellScale);
}
bool AuraScript::AuraUpdate(Entity* target, AuraData* data)
{
	return this->AuraUpdate((WorldEntity*)(target), data);
}
void AuraScript::DeApply(Entity* target, AuraData* data)
{
	this->DeApply((WorldEntity*)(target), data);
}
void AuraScript::OnDamageReceive(Entity* caster, Entity* target, MonoBehaviour* spell, AuraData* aura, int damage)
{
	this->OnDamageReceive((WorldEntity*)(caster), (WorldEntity*)(target), spell, aura, damage);
}
void AuraScript::OnHit(Entity* caster, Entity* target, MonoBehaviour* spell, AuraData* aura, int damage)
{
	this->OnHit((WorldEntity*)(caster), (WorldEntity*)(target), spell, aura, damage);
}
void AuraScript::OnDispell(Entity* caster)
{
	this->OnDispell((WorldEntity*)(caster));
}
void AuraScript::OnRemove(Entity* caster)
{
	this->OnRemove((WorldEntity*)(caster));
}
void AuraScript::COnAdded(Entity* target, Aura* data, AuraData* aura)
{
	this->COnAdded((WorldEntity*)(target), data, aura);
}
void AuraScript::COnRemoved(Entity* target, Aura* data)
{
	this->COnRemoved((WorldEntity*)(target), data);
}
void AuraScript::COnRefresh(Entity* target, GameObject* data, AuraData* aura)
{
	this->COnRefresh((WorldEntity*)(target), data, aura);
}
void AuraScript::Apply(WorldEntity* caster, WorldEntity* target, float spellScale)
{
}
bool AuraScript::AuraUpdate(WorldEntity* target, AuraData* data)
{
	data->Remaining -= Time::deltaTime;
	if (data->Remaining <= (float)0) {
		data->Remaining = (float)0;
		this->DeApply(target, data);
		return true;
	}
	return false;
}
void AuraScript::DeApply(WorldEntity* target, AuraData* data)
{
}
void AuraScript::OnDamageReceive(WorldEntity* caster, WorldEntity* target, MonoBehaviour* spell, AuraData* aura, int damage)
{
}
void AuraScript::OnHit(WorldEntity* caster, WorldEntity* target, MonoBehaviour* spell, AuraData* aura, int damage)
{
}
void AuraScript::OnDispell(WorldEntity* caster)
{
}
void AuraScript::OnRemove(WorldEntity* caster)
{
	Debug::Log(new String("OnRemove called, Deprecated!"));
	this->DeApply(caster, null);
}
void AuraScript::COnAdded(WorldEntity* target, Aura* data, AuraData* aura)
{
}
void AuraScript::COnRemoved(WorldEntity* target, Aura* data)
{
}
void AuraScript::COnRefresh(WorldEntity* target, GameObject* data, AuraData* aura)
{
}
void AuraScript::RemoveAura(WorldEntity* caster)
{
	AuraComponent* auraComponent = caster->AuraComponent;
	AuraData* data = null;
	for (int i = 0; i < auraComponent->serverAuras->Count; i += 1) {
		if (auraComponent->serverAuras->GetData(i)->AuraId == this->auraId) {
			data = auraComponent->serverAuras->GetData(i);
			break;
		}
	}
	this->DeApply(caster, data);
	auraComponent->JustRemoveAura(this->auraId);
}
bool AuraScript::ShouldApplyModifiers(WorldEntity* target)
{
	AuraComponent* auraComponent = target->AuraComponent;
	for (int i = 0; i < auraComponent->serverAuras->Count; i += 1) {
		if (auraComponent->serverAuras->GetData(i)->AuraId == this->auraId) {
			return false;
		}
	}
	return true;
}
bool AuraScript::BasicAuraUpdate(WorldEntity* target, AuraData* data)
{
	data->Remaining -= Time::deltaTime;
	if (data->Remaining <= (float)0) {
		data->Remaining = (float)0;
		this->DeApply(target, data);
		return true;
	}
	return false;
}
bool AuraScript::ShouldApplyModifiers(WorldEntity* target, float refreshTo)
{
	AuraComponent* auraComponent = target->AuraComponent;
	for (int i = 0; i < auraComponent->serverAuras->Count; i += 1) {
		if (auraComponent->serverAuras->GetData(i)->AuraId == this->auraId) {
			auraComponent->RefreshAura(this->auraId, refreshTo);
			return false;
		}
	}
	return true;
}
bool AuraScript::ShouldApplyModifiers(WorldEntity* target, float refreshTo, WorldEntity* caster, float spellScale)
{
	AuraComponent* auraComponent = target->AuraComponent;
	for (int i = 0; i < auraComponent->serverAuras->Count; i += 1) {
		if (auraComponent->serverAuras->GetData(i)->AuraId == this->auraId) {
			auraComponent->RefreshAura(this->auraId, refreshTo);
			return false;
		}
	}
	this->AddAuraDataToTarget(target, caster, refreshTo, spellScale);
	return true;
}
bool AuraScript::ShouldRemoveModifiers(WorldEntity* target)
{
	AuraComponent* auraComponent = target->AuraComponent;
	int num = 0;
	for (int i = 0; i < auraComponent->serverAuras->Count; i += 1) {
		if (auraComponent->serverAuras->GetData(i)->AuraId == this->auraId) {
			num += 1;
			if (num > 1) {
				return false;
			}
		}
	}
	return true;
}
void AuraScript::RefreshDamageCountAuraDiminished(WorldEntity* target, float refreshTo, WorldEntity* caster, DiminishingReturnAuraData::DiminishingReturnCategory diminsihingType, DamageCountAuraData* aura)
{
	int auraIdForDiminishingReturn = this->GetAuraIdForDiminishingReturn(diminsihingType);
	if (auraIdForDiminishingReturn == -1) {
		Debug::Log(*(new String("AuraScript:RefreshDamageCountAuraDiminished-> Auraid is -1 for a diminishing return aura! DiminishingType: ")) + diminsihingType->ToString());
		return;
	}
	AuraComponent* auraComponent = target->AuraComponent;
	AuraData* auraData = this->getAuraData(target, auraIdForDiminishingReturn);
	DiminishingReturnAuraData* aura2 = null;
	if (auraData != null) {
		if (!is_inst_of<DiminishingReturnAuraData*>(auraData)) {
			Debug::Log(*(new String("AuraScript:RefreshDamageCountAuraDiminished-> Auradata isn't DiminishingReturnAuraData! auraId:")) + BOX<int>(auraIdForDiminishingReturn));
			return;
		}
		auraComponent->RefreshAura(auraData->AuraId, (float)15);
	}
	else {
		this->ApplyAura(auraIdForDiminishingReturn, caster, target, (float)1);
		auraData = this->getAuraData(target, auraIdForDiminishingReturn);
		if (!is_inst_of<DiminishingReturnAuraData*>(auraData)) {
			Debug::Log(*(new String("AuraScript:RefreshDamageCountAuraDiminished-> Auradata isn't DiminishingReturnAuraData! auraId:")) + BOX<int>(auraIdForDiminishingReturn));
			return;
		}
		aura2 = (DiminishingReturnAuraData*)(auraData);
	}
	float diminishedTime = this->GetDiminishedTime(target, aura2, refreshTo);
	auraComponent->RefreshAura(auraData->AuraId, diminishedTime);
}
void AuraScript::AddAuraDataToTarget(WorldEntity* target, AuraData* data)
{
	target->AuraComponent->AddAura(data);
}
void AuraScript::AddAuraDataToTarget(WorldEntity* target, WorldEntity* caster, float duration, float spellScale)
{
	BaseAuraComponent* arg_2D_0 = target->AuraComponent;
	AuraData* data = new AuraData(this->auraId, duration, caster, caster->PlayerData->GUID, this->aura->AuraGroup, spellScale);
	arg_2D_0->AddAura(data);
}
void AuraScript::AddOrRefreshDamageAuraDataToTarget(WorldEntity* target, WorldEntity* caster, float spellScale, float duration, float tick, int damage)
{
	AuraData* auraData = this->TargetHasCastersAura(target, caster);
	if (auraData == null) {
		DamageAuraData* data = new DamageAuraData(this->auraId, duration, caster, caster->PlayerData->GUID, this->aura->AuraGroup, spellScale, tick, damage);
		this->AddAuraDataToTarget(target, data);
		return;
	}
	BaseAuraComponent* arg_5F_0 = target->AuraComponent;
	DamageAuraData* damageAuraData = (DamageAuraData*)(*auraData);
	arg_5F_0->RefreshAura(damageAuraData->AuraId, (Entity*)(damageAuraData->Caster), duration);
	damageAuraData->Damage = damage;
}
void AuraScript::AddOrRefreshHealAuraDataToTarget(WorldEntity* target, WorldEntity* caster, float spellScale, float duration, float tick, int heal)
{
	AuraData* auraData = this->TargetHasCastersAura(target, caster);
	if (auraData == null) {
		HealAuraData* data = new HealAuraData(this->auraId, duration, caster, caster->PlayerData->GUID, this->aura->AuraGroup, spellScale, tick, heal);
		this->AddAuraDataToTarget(target, data);
		return;
	}
	BaseAuraComponent* arg_5F_0 = target->AuraComponent;
	HealAuraData* healAuraData = (HealAuraData*)(*auraData);
	arg_5F_0->RefreshAura(healAuraData->AuraId, (Entity*)(healAuraData->Caster), duration);
	healAuraData->Heal = heal;
}
void AuraScript::AddOrRefreshShieldAuraDataToTarget(WorldEntity* target, WorldEntity* caster, float spellScale, float duration, int absorb)
{
	AuraData* auraData = this->TargetHasAura(target);
	if (auraData == null) {
		ShieldAuraData* data = new ShieldAuraData(this->auraId, duration, caster, caster->PlayerData->GUID, this->aura->AuraGroup, spellScale, absorb);
		this->AddAuraDataToTarget(target, data);
		return;
	}
	BaseAuraComponent* arg_5C_0 = target->AuraComponent;
	ShieldAuraData* shieldAuraData = (ShieldAuraData*)(*auraData);
	arg_5C_0->RefreshAura(shieldAuraData->AuraId, (Entity*)(shieldAuraData->Caster), duration);
	shieldAuraData->RemainingAbsorb = absorb;
}
void AuraScript::AddOrRefreshDiminishingReturnAura(WorldEntity* target, DiminishingReturnAuraData::DiminishingReturnCategory diminishingCategory)
{
	int auraIdForDiminishingReturn = this->GetAuraIdForDiminishingReturn(diminishingCategory);
	if (auraIdForDiminishingReturn == -1) {
		Debug::Log(*(new String("AuraScript:AddOrRefreshDiminishingReturnAura-> Auraid is -1 for a diminishing return aura! DiminishingType: ")) + diminishingCategory->ToString());
		return;
	}
	AuraData* auraData = this->getAuraData(target, auraIdForDiminishingReturn);
	if (auraData == null) {
		this->ApplyAura(auraIdForDiminishingReturn, target, target, (float)1);
		return;
	}
	if (!is_inst_of<DiminishingReturnAuraData*>(auraData)) {
		Debug::Log(*(new String("AuraScript:AddOrRefreshDiminishingReturnAura-> Auradata isn't DiminishingReturnAuraData! auraId:")) + BOX<int>(auraIdForDiminishingReturn));
		return;
	}
	DiminishingReturnAuraData* diminishingReturnAuraData = (DiminishingReturnAuraData*)(*auraData);
	target->AuraComponent->RefreshAura(diminishingReturnAuraData->AuraId, (float)15);
}
void AuraScript::AddStatModifier(WorldEntity* target, int stat, float maxMod, float percentMod)
{
	target->Stats->GetSStatFromId(stat)->Modifiers->Add(this->auraId, maxMod, percentMod, true);
}
void AuraScript::RemoveStatModifier(WorldEntity* target, int stat)
{
	target->Stats->GetSStatFromId(stat)->Modifiers->Remove(this->auraId, true);
}
void AuraScript::AddState(WorldEntity* target, StateData::StateType state)
{
	target->StateComponent->AddState(this->auraId, state);
}
void AuraScript::RemoveState(WorldEntity* target, StateData::StateType state)
{
	target->StateComponent->RemoveStateWithAuraId(this->auraId, state);
}
void AuraScript::RemovethisAura(WorldEntity* target)
{
	BaseAuraComponent* arg_14_0 = target->AuraComponent;
	this->DeApply(target, null);
	arg_14_0->JustRemoveAura(this->auraId);
}
AuraData* AuraScript::TargetHasCastersAura(WorldEntity* target, WorldEntity* caster)
{
	AuraComponent* auraComponent = target->AuraComponent;
	for (int i = 0; i < auraComponent->serverAuras->Count; i += 1) {
		if ((auraComponent->serverAuras->GetData(i)->AuraId == this->auraId) && (auraComponent->serverAuras->GetData(i)->Caster == *caster)) {
			return auraComponent->serverAuras->GetData(i);
		}
	}
	return null;
}
AuraData* AuraScript::TargetHasAura(WorldEntity* target)
{
	AuraComponent* auraComponent = target->AuraComponent;
	for (int i = 0; i < auraComponent->serverAuras->Count; i += 1) {
		if (auraComponent->serverAuras->GetData(i)->AuraId == this->auraId) {
			return auraComponent->serverAuras->GetData(i);
		}
	}
	return null;
}
int AuraScript::CalculateDamage(WorldEntity* caster, WorldEntity* target, float spellScale)
{
	AuraDamageData* auraDamageData = this->aura->AuraDamageData;
	float arg_24_0 = (float)(UnityEngine::Random::Range(auraDamageData->Min, auraDamageData->Max));
	PlayerData* playerData = caster->PlayerData;
	float arg_4D_0 = (float)((int)((arg_24_0 * this->aura->GetDamageScaleForLevel(playerData->Level)) * spellScale));
	Stats* expr_40 = caster->Stats;
	PercentStat* sMeleeDamage = expr_40->SMeleeDamage;
	PercentStat* sDamageTaken = expr_40->SDamageTaken;
	return (int)((arg_4D_0 * (sMeleeDamage->ModPercent / (float)100)) * (sDamageTaken->ModPercent / (float)100));
}
int AuraScript::CalculateHeal(WorldEntity* caster, WorldEntity* target, float spellScale)
{
	AuraHealData* auraHealData = this->aura->AuraHealData;
	float arg_24_0 = (float)(UnityEngine::Random::Range(auraHealData->Min, auraHealData->Max));
	PlayerData* playerData = caster->PlayerData;
	float arg_46_0 = (float)((int)((arg_24_0 * this->aura->GetHealScaleForLevel(playerData->Level)) * spellScale));
	PercentStat* sSpellDamage = caster->Stats->SSpellDamage;
	return (int)(arg_46_0 * (sSpellDamage->ModPercent / (float)100));
}
int AuraScript::CalculateAbsorb(WorldEntity* caster, WorldEntity* target, float spellScale)
{
	AuraAbsorbData* auraAbsorbData = this->aura->AuraAbsorbData;
	float arg_24_0 = (float)(UnityEngine::Random::Range(auraAbsorbData->min, auraAbsorbData->max));
	PlayerData* playerData = caster->PlayerData;
	float arg_46_0 = (float)((int)((arg_24_0 * this->aura->GetAbsorbScaleForLevel(playerData->Level)) * spellScale));
	PercentStat* sSpellDamage = caster->Stats->SSpellDamage;
	return (int)(arg_46_0 * (sSpellDamage->ModPercent / (float)100));
}
void AuraScript::UpdateDamageCountAura(WorldEntity* target, AuraData* aura, int damage, float breakHealthPercent)
{
	DamageCountAuraData* expr_06 = (DamageCountAuraData*)(*aura);
	expr_06->DamageTaken += damage;
	Stats* stats = target->Stats;
	if ((float)(expr_06->DamageTaken) >= (stats->SHealth->Max * (float)0.3)) {
		this->RemovethisAura(target);
	}
}
bool AuraScript::UpdateDamageAura(WorldEntity* target, AuraData* data)
{
	DamageAuraData* damageAuraData = (DamageAuraData*)(*data);
	DamageAuraData* expr_08 = damageAuraData;
	expr_08->TimeSinceLastTick += Time::deltaTime;
	if (damageAuraData->TimeSinceLastTick >= damageAuraData->Tick) {
		DamageAuraData* expr_28 = damageAuraData;
		expr_28->TimeSinceLastTick -= damageAuraData->Tick;
		this->DealDamage(target, damageAuraData);
	}
	return this->BasicAuraUpdate(target, data);
}
bool AuraScript::UpdateDamageAuraTickBool(WorldEntity* target, AuraData* data)
{
	DamageAuraData* damageAuraData = (DamageAuraData*)(*data);
	DamageAuraData* expr_08 = damageAuraData;
	expr_08->TimeSinceLastTick += Time::deltaTime;
	if (damageAuraData->TimeSinceLastTick >= damageAuraData->Tick) {
		DamageAuraData* expr_28 = damageAuraData;
		expr_28->TimeSinceLastTick -= damageAuraData->Tick;
		this->DealDamage(target, damageAuraData);
		return true;
	}
	return false;
}
bool AuraScript::UpdateHealAura(WorldEntity* target, AuraData* data)
{
	HealAuraData* healAuraData = (HealAuraData*)(*data);
	HealAuraData* expr_08 = healAuraData;
	expr_08->TimeSinceLastTick += Time::deltaTime;
	if (healAuraData->TimeSinceLastTick >= healAuraData->Tick) {
		HealAuraData* expr_28 = healAuraData;
		expr_28->TimeSinceLastTick -= healAuraData->Tick;
		this->Heal(target, healAuraData);
	}
	return this->BasicAuraUpdate(target, data);
}
void AuraScript::AbsorbPOnBeforeDamage(DamagePipelineData* data, AuraData* aura)
{
	ShieldAuraData* shieldAuraData = (ShieldAuraData*)(*aura);
	int num = data->Damage;
	if (shieldAuraData->RemainingAbsorb >= num) {
		ShieldAuraData* expr_18 = shieldAuraData;
		expr_18->RemainingAbsorb -= num;
		num = 0;
	}
	else {
		num -= *shieldAuraData->RemainingAbsorb;
		shieldAuraData->RemainingAbsorb = 0;
	}
	data->Damage = num;
	if (shieldAuraData->RemainingAbsorb == 0) {
		BaseAuraComponent* arg_70_0 = (WorldEntity*)(data->Receiver)->AuraComponent;
		this->DeApply((WorldEntity*)(data->Receiver), aura);
		arg_70_0->JustRemoveAura(this->auraId);
	}
}
void AuraScript::DealDamage(WorldEntity* target, DamageAuraData* data)
{
	this->damagePipelineData->Set(data->Damage, false, SpellType::TYPE_MAGIC, data->Caster, target, this->aura->gameObject);
	AuraComponent* auraComponent = target->AuraComponent;
	auraComponent->OnHit((WorldEntity*)(data->Caster), target, this->aura, this->damagePipelineData->Damage);
	auraComponent->POnBeforeDamage(this->damagePipelineData);
	if (this->damagePipelineData->Damage == 0) {
		return;
	}
	target->Stats->TakeDamage(this->damagePipelineData->Damage, false, (WorldEntity*)(data->Caster));
	auraComponent->OnDamageReceive((WorldEntity*)(data->Caster), target, this->aura, this->damagePipelineData->Damage);
}
void AuraScript::DealDamage(WorldEntity* target, DamageAuraData* data, int damage)
{
	this->damagePipelineData->Set(damage, false, SpellType::TYPE_MAGIC, data->Caster, target, this->aura->gameObject);
	AuraComponent* auraComponent = target->AuraComponent;
	auraComponent->OnHit((WorldEntity*)(data->Caster), target, this->aura, this->damagePipelineData->Damage);
	auraComponent->POnBeforeDamage(this->damagePipelineData);
	if (this->damagePipelineData->Damage == 0) {
		return;
	}
	target->Stats->TakeDamage(this->damagePipelineData->Damage, false, (WorldEntity*)(data->Caster));
	auraComponent->OnDamageReceive((WorldEntity*)(data->Caster), target, this->aura, this->damagePipelineData->Damage);
}
void AuraScript::DealDamage(WorldEntity* target, WorldEntity* caster, int damage)
{
	this->damagePipelineData->Set(damage, false, SpellType::TYPE_MAGIC, caster, target, this->aura->gameObject);
	AuraComponent* auraComponent = target->AuraComponent;
	auraComponent->OnHit(caster, target, this->aura, this->damagePipelineData->Damage);
	auraComponent->POnBeforeDamage(this->damagePipelineData);
	if (this->damagePipelineData->Damage == 0) {
		return;
	}
	target->Stats->TakeDamage(this->damagePipelineData->Damage, false, caster);
	auraComponent->OnDamageReceive(caster, target, this->aura, this->damagePipelineData->Damage);
}
void AuraScript::DealDamageWithoutOnHit(WorldEntity* target, WorldEntity* caster, int damage)
{
	this->damagePipelineData->Set(damage, false, SpellType::TYPE_MAGIC, caster, target, this->aura->gameObject);
	AuraComponent* auraComponent = target->AuraComponent;
	auraComponent->POnBeforeDamage(this->damagePipelineData);
	if (this->damagePipelineData->Damage == 0) {
		return;
	}
	target->Stats->TakeDamage(this->damagePipelineData->Damage, false, caster);
	auraComponent->OnDamageReceive(caster, target, this->aura, this->damagePipelineData->Damage);
}
void AuraScript::Heal(WorldEntity* target, HealAuraData* data)
{
	target->Stats->TakeHeal(data->Heal, false, (WorldEntity*)(data->Caster));
}
void AuraScript::Heal(WorldEntity* target, HealAuraData* data, int heal)
{
	target->Stats->TakeHeal(heal, false, (WorldEntity*)(data->Caster));
}
void AuraScript::Heal(WorldEntity* target, AuraData* data, int heal)
{
	target->Stats->TakeHeal(heal, false, (WorldEntity*)(data->Caster));
}
DiminishingReturnAuraData* AuraScript::GetDiminishingReturnAuraDataFor(WorldEntity* target, DiminishingReturnAuraData::DiminishingReturnCategory type)
{
	AuraComponent* auraComponent = target->AuraComponent;
	for (int i = 0; i < auraComponent->serverAuras->Count; i += 1) {
		AuraData* auraData = auraComponent->serverAuras->GetData(i);
		if (is_inst_of<DiminishingReturnAuraData*>(auraData)) {
			DiminishingReturnAuraData* diminishingReturnAuraData = (DiminishingReturnAuraData*)(*auraData);
			if (diminishingReturnAuraData->DiminishingCategory == DiminishingReturnAuraData::DiminishingReturnCategory::TYPE_ROOT) {
				return diminishingReturnAuraData;
			}
		}
	}
	return null;
}
float AuraScript::GetDiminishedTime(WorldEntity* target, DiminishingReturnAuraData::DiminishingReturnCategory diminsihingType, float time)
{
	int auraIdForDiminishingReturn = this->GetAuraIdForDiminishingReturn(diminsihingType);
	if (auraIdForDiminishingReturn == -1) {
		Debug::Log(*(new String("AuraScript:RefreshDamageCountAuraDiminished-> Auraid is -1 for a diminishing return aura! DiminishingType: ")) + diminsihingType->ToString());
		return (float)0;
	}
	AuraData* auraData = this->getAuraData(target, auraIdForDiminishingReturn);
	if (auraData != null) {
		DiminishingReturnAuraData* aura = (DiminishingReturnAuraData*)(*auraData);
		return this->GetDiminishedTime(target, aura, time);
	}
	return time;
}
void AuraScript::AddEffect(WorldEntity* player, EffectPoints bodyPart, Quaternion* rotation)
{
	Transform* effectPoint = player->GetComponent<IEffectPointGetter>()->GetEffectPoint(bodyPart);
	if (effectPoint == null) {
		return;
	}
	GameObject* expr_37 = UnityEngine::Object::Instantiate<GameObject>(this->aura->AuraEffectData->EffectPrefab, Vector3::zero, Quaternion::identity, effectPoint);
	expr_37->AddComponent<EffectAuraIdAttribute>()->AuraId = this->auraId;
	expr_37->transform->localRotation = rotation;
	expr_37->transform->localPosition = Vector3::zero;
}
void AuraScript::AddEffect(WorldEntity* player, GameObject* effectPrefab, EffectPoints bodyPart, Quaternion* rotation)
{
	Transform* effectPoint = player->GetComponent<IEffectPointGetter>()->GetEffectPoint(bodyPart);
	if (effectPoint == null) {
		return;
	}
	GameObject* expr_28 = UnityEngine::Object::Instantiate<GameObject>(effectPrefab, Vector3::zero, Quaternion::identity, effectPoint);
	expr_28->AddComponent<EffectAuraIdAttribute>()->AuraId = this->auraId;
	expr_28->transform->localRotation = rotation;
	expr_28->transform->localPosition = Vector3::zero;
}
void AuraScript::RemoveEffect(WorldEntity* player, EffectPoints bodyPart)
{
	Transform* effectPoint = player->GetComponent<IEffectPointGetter>()->GetEffectPoint(bodyPart);
	if (effectPoint == null) {
		return;
	}
	for (int i = 0; i < effectPoint->childCount; i += 1) {
		Transform* child = effectPoint->GetChild(i);
		EffectAuraIdAttribute* component = child->GetComponent<EffectAuraIdAttribute>();
		if (!component == null && (component->AuraId == this->auraId)) {
			child->SetParent(null);
			UnityEngine::Object::Destroy(child->gameObject);
			return;
		}
	}
}
void AuraScript::RemoveActiveGroupAuras(WorldEntity* target)
{
	if (this->aura->AuraGroup == 0) {
		return;
	}
	target->AuraComponent->RemoveAurasWithGroup(this->aura->AuraGroup);
}
float AuraScript::GetDiminishedTime(WorldEntity* target, DiminishingReturnAuraData* aura, float time)
{
	if (aura != null) {
		if (aura->Count <= 4) {
			time /= (float)(aura->Count);
		}
		else {
			time = (float)0;
		}
	}
	return time;
}
int AuraScript::GetAuraIdForDiminishingReturn(DiminishingReturnAuraData::DiminishingReturnCategory type)
{
	if (type == DiminishingReturnAuraData::DiminishingReturnCategory::TYPE_ROOT) {
		return 1;
	}
	return -1;
}
AuraData* AuraScript::getAuraData(WorldEntity* target, int pAuraId)
{
	AuraComponent* auraComponent = target->AuraComponent;
	for (int i = 0; i < auraComponent->serverAuras->Count; i += 1) {
		if (auraComponent->serverAuras->GetData(i)->AuraId == pAuraId) {
			return auraComponent->serverAuras->GetData(i);
		}
	}
	return null;
}
void AuraScript::ApplyAura(int auraId, WorldEntity* caster, WorldEntity* target, float spellScale)
{
	(AuraScript*)(Auras::Instance->GetData(auraId)->AuraScript)->Apply(caster, target, spellScale);
}
bool AuraScript::IsZero(float x)
{
	return (x < Mathf::Epsilon) && (x > -Mathf::Epsilon);
}
void AuraScript::InitFactory()
{
	BaseAuraScript::CreateAuraScriptFor = new BaseAuraScript::CreateAuraScriptForAction(AuraScript::SSCreateFor);
}
void AuraScript::SSCreateFor(Aura* aura)
{
	int scriptId = aura->ScriptId;
	if (scriptId == 1) {
		new GenericAura(aura);
	}
}

