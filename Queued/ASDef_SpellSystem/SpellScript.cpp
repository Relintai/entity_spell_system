#include "spell_script.h"

#include "../entities/entity.h"


void SpellScript::StartCasting(Entity* caster, float spellScale)
{
}

void SpellScript::CastingFinished(Entity* caster, float spellScale)
{
}

void SpellScript::CastingFailed(Entity* caster)
{
}

void SpellScript::SpellHit(Entity* caster, Entity* target, BaseWorldSpell* worldSpell, Spell* spell, float spellScale)
{
}

void SpellScript::OnPlayerMove(Entity* caster)
{
}

void SpellScript::COnSpellCastStarted(Entity* player)
{

}

void SpellScript::COnSpellCastSuccess(Entity* player)
{
}

void SpellScript::COnSpellCastFailed(Entity* player)
{

}

void SpellScript::COnSpellCastEnded(Entity* player)
{

}

void SpellScript::OnCastStateChanged(Entity* caster)
{
	//if (IsStunned(caster)) {
	//	DoCastFail(caster, true);
//	}
}

SpellScript::SpellScript()
{
	//damagePipelineData = new DamagePipelineData();
	PLAYER_HIT_RADIUS = (float)0.5;
}

/*

void SpellScript::InitFactory()
{
	BaseSpellScript::CreateSpellScriptFor = new BaseSpellScript::CreateSpellScriptForAction(SpellScript::SSCreateFor);
}
void SpellScript::SSCreateFor(Spell* spell)
{
	int scriptId = spell->ScriptId;
	if (scriptId == 1) {
		new GenericSpell(spell);
	}
}
SpellScript::SpellScript(Spell* spell) : BaseSpellScript(spell)
{
	damagePipelineData = new DamagePipelineData();
	PLAYER_HIT_RADIUS = (float)0.5;
}
void SpellScript::TriggerGlobalCooldown(WorldEntity* player)
{
	player->Stats->TriggerGlobalCooldown();
}
bool SpellScript::IsCasting(WorldEntity* player)
{
	return player->SpellCastData->SCasting;
}
bool SpellScript::HasClobalCooldown(WorldEntity* player)
{
	return player->Stats->SHasGlobalCooldown;
}
bool SpellScript::IsStunned(WorldEntity* player)
{
	return player->StateComponent->SHasState(StateData::StateType::TYPE_STUN);
}
bool SpellScript::HasState(StateData::StateType state, WorldEntity* player)
{
	return player->StateComponent->SHasState(state);
}
int SpellScript::GetId(WorldEntity* spell)
{
	return spell->GetComponent<Spell>()->SpellID;
}
bool SpellScript::IsSpellOnCooldown(int spellId, WorldEntity* player)
{
	PlayerSpellDataComponent* playerSpellDataComponent = player->PlayerSpellDataComponent;
	for (int i = 0; i < playerSpellDataComponent->SSpellData->Count; i += 1) {
		if (playerSpellDataComponent->SSpellData->GetData(i)->SpellId == spellId) {
			return true;
		}
	}
	return false;
}
void SpellScript::ApplyAura(int auraId, WorldEntity* caster, float spellScale)
{
	(AuraScript*)(Auras::Instance->GetData(auraId)->AuraScript)->Apply(caster, caster, spellScale);
}
void SpellScript::ApplyAura(int auraId, WorldEntity* caster, WorldEntity* target, float spellScale)
{
	(AuraScript*)(Auras::Instance->GetData(auraId)->AuraScript)->Apply(caster, target, spellScale);
}
void SpellScript::RemoveAura(int auraId, WorldEntity* caster)
{
	(AuraScript*)(Auras::Instance->GetData(auraId)->AuraScript)->RemoveAura(caster);
}
void SpellScript::AddCooldown(WorldEntity* player, int spellId, float cooldown)
{
	PlayerSpellDataComponent* arg_10_0 = player->PlayerSpellDataComponent;
	PlayerSpellCooldownData* psd = new PlayerSpellCooldownData(spellId, cooldown, cooldown);
	arg_10_0->AddSSpellData(psd);
}
void SpellScript::DoStartCasting(WorldEntity* player, int spellId, String* spellName, float castTime, bool addMoveHook, float spellScale)
{
	player->SpellCastData->StartCasting(spellId, spellName, castTime, spellScale);
	if (addMoveHook) {
		OnPlayerMoveCallbackComponent* expr_1B = player->Opmcc;
		expr_1B->RegisterSOnPlayerMove(new BaseOnPlayerMoveCallbackComponent::OnPlayerMoved(OnPlayerMove), spellId);
		expr_1B->ServerCallbackAdded();
	}
}
void SpellScript::DoCastFail(WorldEntity* player, bool removeHook)
{
	player->SpellCastData->SCastFailed();
	if (removeHook) {
		player->Opmcc->RemoveSOnPlayerMove(new BaseOnPlayerMoveCallbackComponent::OnPlayerMoved(OnPlayerMove), spellId);
	}
	CastingFailed(player);
}
void SpellScript::AddOnMoveHook(WorldEntity* player)
{
	OnPlayerMoveCallbackComponent* expr_06 = player->Opmcc;
	expr_06->RegisterSOnPlayerMove(new BaseOnPlayerMoveCallbackComponent::OnPlayerMoved(OnPlayerMove), spellId);
	expr_06->ServerCallbackAdded();
}
void SpellScript::RemoveOnMoveHook(WorldEntity* player)
{
	player->Opmcc->RemoveSOnPlayerMove(new BaseOnPlayerMoveCallbackComponent::OnPlayerMoved(OnPlayerMove), spellId);
}
WorldEntity* SpellScript::GetTarget(WorldEntity* player)
{
	return player->TargetComponent->STarget;
}
void SpellScript::DealDamage(WorldEntity* caster, WorldEntity* target, int damage)
{
	if (target != null) {
		damagePipelineData->Set(damage, false, spell->GetSpellType, caster, target, spell->gameObject);
		AuraComponent* auraComponent = target->AuraComponent;
		auraComponent->OnHit(caster, target, spell, damagePipelineData->Damage);
		auraComponent->POnBeforeDamage(damagePipelineData);
		if (damagePipelineData->Damage == 0) {
			return;
		}
		target->Stats->TakeDamage(damagePipelineData->Damage, false, caster);
		auraComponent->OnDamageReceive(caster, target, spell, damagePipelineData->Damage);
	}
}
void SpellScript::DealDamage(WorldEntity* caster, WorldEntity* target, float spellScale)
{
	int num = UnityEngine::Random::Range(spell->DamageMin, spell->DamageMax);
	if (checkParry(caster, target)) {
		return;
	}
	PlayerData* playerData = caster->PlayerData;
	num = (int)(((float)(num) * spell->GetDamageScaleForLevel(playerData->Level)) * spellScale);
	Stats* stats = caster->Stats;
	if (spell->GetSpellType == SpellType::TYPE_MELEE) {
		PercentStat* sMeleeDamage = stats->SMeleeDamage;
		num = (int)((float)(num) * (sMeleeDamage->ModPercent / (float)100));
	}
	else {
		if (spell->GetSpellType == SpellType::TYPE_MAGIC) {
			PercentStat* sSpellDamage = stats->SSpellDamage;
			num = (int)((float)(num) * (sSpellDamage->ModPercent / (float)100));
		}
	}
	float num2 = (float)0;
	float num3 = (float)0;
	bool flag = false;
	if (spell->GetSpellType == SpellType::TYPE_MELEE) {
		num2 = stats->SMeleeCrit->ModPercent;
		num3 = stats->SMeleeCritBonus->ModPercent;
	}
	else {
		if (spell->GetSpellType == SpellType::TYPE_MAGIC) {
			num2 = stats->SSpellCrit->ModPercent;
			num3 = stats->SSpellCritBonus->ModPercent;
		}
	}
	num2 /= (float)100;
	if (UnityEngine::Random::value <= num2) {
		flag = true;
	}
	if (flag) {
		num += (int)((float)(num) * (num3 / (float)100));
	}
	if (target != null) {
		Stats* stats2 = target->Stats;
		num = (int)((float)(num) * (((float)100 - stats2->SDamageReduction->ModPercent) / (float)100));
		if (spell->GetSpellType == SpellType::TYPE_MELEE) {
			num = (int)((float)(num) * (((float)100 - stats2->SMeleeDamageReduction->ModPercent) / (float)100));
		}
		else {
			if (spell->GetSpellType == SpellType::TYPE_MAGIC) {
				num = (int)((float)(num) * (((float)100 - stats2->SSpellDamageReduction->ModPercent) / (float)100));
			}
		}
		num = (int)((float)(num) * (stats2->SDamageTaken->ModPercent / (float)100));
		damagePipelineData->Set(num, flag, spell->GetSpellType, caster, target, spell->gameObject);
		AuraComponent* auraComponent = target->AuraComponent;
		auraComponent->OnHit(caster, target, spell, damagePipelineData->Damage);
		auraComponent->POnBeforeDamage(damagePipelineData);
		if (damagePipelineData->Damage == 0) {
			return;
		}
		stats2->TakeDamage(damagePipelineData->Damage, flag, caster);
		auraComponent->OnDamageReceive(caster, target, spell, damagePipelineData->Damage);
	}
}
void SpellScript::VashDealDamage(WorldEntity* caster, WorldEntity* target, bool increased, float spellScale)
{
	int num = UnityEngine::Random::Range(spell->DamageMin, spell->DamageMax);
	PlayerData* playerData = caster->PlayerData;
	num = (int)(((float)(num) * spell->GetDamageScaleForLevel(playerData->Level)) * spellScale);
	Stats* stats = caster->Stats;
	if (spell->GetSpellType == SpellType::TYPE_MELEE) {
		PercentStat* sMeleeDamage = stats->SMeleeDamage;
		num = (int)((float)(num) * (sMeleeDamage->ModPercent / (float)100));
	}
	else {
		if (spell->GetSpellType == SpellType::TYPE_MAGIC) {
			PercentStat* sSpellDamage = stats->SSpellDamage;
			num = (int)((float)(num) * (sSpellDamage->ModPercent / (float)100));
		}
	}
	float num2 = (float)0;
	float num3 = (float)0;
	bool flag = false;
	if (spell->GetSpellType == SpellType::TYPE_MELEE) {
		num2 = stats->SMeleeCrit->ModPercent;
		num3 = stats->SMeleeCritBonus->ModPercent;
	}
	else {
		if (spell->GetSpellType == SpellType::TYPE_MAGIC) {
			num2 = stats->SSpellCrit->ModPercent;
			num3 = stats->SSpellCritBonus->ModPercent;
		}
	}
	num2 /= (float)100;
	if (UnityEngine::Random::value <= num2) {
		flag = true;
	}
	if (flag) {
		num += (int)((float)(num) * (num3 / (float)100));
	}
	if (increased) {
		num = (int)((float)(num) * (float)1.4);
	}
	if (target != null) {
		Stats* stats2 = target->Stats;
		num = (int)((float)(num) * (((float)100 - stats2->SDamageReduction->ModPercent) / (float)100));
		if (spell->GetSpellType == SpellType::TYPE_MELEE) {
			num = (int)((float)(num) * (((float)100 - stats2->SMeleeDamageReduction->ModPercent) / (float)100));
		}
		else {
			if (spell->GetSpellType == SpellType::TYPE_MAGIC) {
				num = (int)((float)(num) * (((float)100 - stats2->SSpellDamageReduction->ModPercent) / (float)100));
			}
		}
		num = (int)((float)(num) * (stats2->SDamageTaken->ModPercent / (float)100));
		damagePipelineData->Set(num, flag, spell->GetSpellType, caster, target, spell->gameObject);
		AuraComponent* auraComponent = target->AuraComponent;
		auraComponent->OnHit(caster, target, spell, damagePipelineData->Damage);
		auraComponent->POnBeforeDamage(damagePipelineData);
		if (damagePipelineData->Damage == 0) {
			return;
		}
		stats2->TakeDamage(damagePipelineData->Damage, flag, caster);
		auraComponent->OnDamageReceive(caster, target, spell, damagePipelineData->Damage);
	}
}
void SpellScript::Heal(WorldEntity* caster, WorldEntity* target, float spellScale)
{
	int num = UnityEngine::Random::Range(spell->SpellHealData->HealMin, spell->SpellHealData->HealMax);
	PlayerData* playerData = caster->PlayerData;
	num = (int)(((float)(num) * spell->GetHealScaleForLevel(playerData->Level)) * spellScale);
	caster->Stats->TakeHeal(num, false, caster);
}
void SpellScript::Heal(WorldEntity* caster, WorldEntity* target, int heal)
{
	caster->Stats->TakeHeal(heal, false, caster);
}
bool SpellScript::checkParry(WorldEntity* caster, WorldEntity* target)
{
	if (spell->GetSpellType != SpellType::TYPE_MELEE) {
		return false;
	}
	Stat* sParry = target->Stats->SParry;
	return (!sParry->Disabled && ((UnityEngine::Random::value * (float)100) <= sParry->ModPercent)) && (Vector3::Angle(caster->transform->forward, target->transform->forward) > (float)90);
}
//Attribute: Obsolete*
GameObject* SpellScript::OldLaunchFollowProjectile(GameObject* effect, WorldEntity* caster, WorldEntity* target, float speed, float spellScale, float time){
	GameObject* arg_8F_0 = UnityEngine::Object::Instantiate<GameObject>(effect);
	PlayerFacingComponent* playerFacingComponent = caster->PlayerFacingComponent;
	tmp2->Set(caster->transform->position->x + playerFacingComponent->SFacing->x, caster->transform->position->y + playerFacingComponent->SFacing->y, caster->transform->position->z + playerFacingComponent->SFacing->z);
	Vector3* forward = *(target->transform->position) - *(caster->transform->position);
	forward->Normalize();
	arg_8F_0->transform->position = tmp2;
	arg_8F_0->transform->rotation = Quaternion::identity;
	arg_8F_0->transform->localRotation = Quaternion::LookRotation(forward);
	arg_8F_0->GetComponent<SpellProjectileComponent>()->SetFollow(caster, spell, target, speed, spellScale, time);
	NetworkServer::Spawn(arg_8F_0);
	return arg_8F_0;
}
//Attribute: Obsolete*
GameObject* SpellScript::OldLaunchStraightProjectile(GameObject* effect, WorldEntity* caster, float speed, float time, float range, float spellScale){
	GameObject* arg_A0_0 = UnityEngine::Object::Instantiate<GameObject>(effect);
	PlayerFacingComponent* playerFacingComponent = caster->PlayerFacingComponent;
	tmp3->Set(playerFacingComponent->SFacing->x, (float)0, playerFacingComponent->SFacing->z);
	tmp3->Normalize();
	tmp2->Set(caster->transform->position->x, caster->transform->position->y + (float)1.2, caster->transform->position->z);
	tmp2 += tmp3 * (float)1.5;
	arg_A0_0->transform->position = tmp2;
	arg_A0_0->transform->rotation = caster->transform->rotation;
	arg_A0_0->GetComponent<StraightSpellProjectileComponent>()->Launch(caster, spell, tmp3, speed, time, range, spellScale);
	NetworkServer::Spawn(arg_A0_0);
	return arg_A0_0;
}
//Attribute: Obsolete*
GameObject* SpellScript::OldLaunchProjectile(WorldEntity* caster, WorldEntity* target, float spellScale){
	SpellProjectileData* spellProjectileData = spell->SpellProjectileData;
	if (spellProjectileData->Type == SpellProjectileType::Follow){
		OldLaunchFollowProjectile(spellProjectileData->Projectile, caster, target, spellProjectileData->Speed, spellScale, (float)0);
	}
	else {
		if (spellProjectileData->Type == SpellProjectileType::Straight) {
			OldLaunchStraightProjectile(spellProjectileData->Projectile, caster, spellProjectileData->Speed, spellProjectileData->Time, spellProjectileData->Range, spellScale);
		}
	}
	return null;
}
WorldSpell* SpellScript::SpawnProjectile(WorldEntity* caster, WorldEntity* target, float spellScale)
{
	SpellProjectileData* spellProjectileData = spell->SpellProjectileData;
	GameObject* arg_B7_0 = UnityEngine::Object::Instantiate<GameObject>(spellProjectileData->Projectile);
	PlayerFacingComponent* playerFacingComponent = caster->PlayerFacingComponent;
	tmp3->Set(playerFacingComponent->SFacing->x, playerFacingComponent->SFacing->y, playerFacingComponent->SFacing->z);
	tmp3->Normalize();
	tmp2->Set(caster->transform->position->x, caster->transform->position->y + (float)1.2, caster->transform->position->z);
	tmp2 += tmp3 * (float)0.4;
	arg_B7_0->transform->position = tmp2;
	arg_B7_0->transform->rotation = caster->transform->rotation;
	WorldSpell* expr_E3 = arg_B7_0->GetComponent<WorldSpell>();
	expr_E3->SetData(spellProjectileData, caster, spell, spellScale, tmp3, null);
	return expr_E3;
}
bool SpellScript::isInRange(WorldEntity* target, WorldEntity* player)
{
	SpellRangeData* spellRangeData = spell->SpellRangeData;
	tmp2->Set(target->transform->position->x, target->transform->position->y, target->transform->position->z);
	tmp2 -= player->transform->position;
	return tmp2->magnitude < (spellRangeData->Range + ((float)2 * PLAYER_HIT_RADIUS));
}
bool SpellScript::CanCast(WorldEntity* caster, int skipCheck)
{
	return ((((!IsCasting(caster) && (!spell->HasGlobalCooldown || !HasClobalCooldown(caster))) && !IsSpellOnCooldown(spellId, caster)) && (((skipCheck & 1) == 1) || !IsStunned(caster))) && (((skipCheck & 2) == 2) || !HasState(StateData::StateType::TYPE_ROOT, caster))) && (((skipCheck & 4) == 4) || !HasState(StateData::StateType::TYPE_FROZEN, caster));
}
bool SpellScript::CanCastTarget(WorldEntity* caster, int skipCheck)
{
	return (((!IsCasting(caster) && (!spell->HasGlobalCooldown || !HasClobalCooldown(caster))) && !IsSpellOnCooldown(spellId, caster)) && (((skipCheck & 1) == 1) || !IsStunned(caster))) && !GetTarget(caster) == null;
}
bool SpellScript::CanCastTargetRange(WorldEntity* caster, int skipCheck)
{
	if (IsCasting(caster)) {
		return false;
	}
	if (spell->HasGlobalCooldown && HasClobalCooldown(caster)) {
		return false;
	}
	if (IsSpellOnCooldown(spellId, caster)) {
		return false;
	}
	if (((skipCheck & 1) != 1) && IsStunned(caster)) {
		return false;
	}
	WorldEntity* target = GetTarget(caster);
	return !target == null && isInRange(target, caster);
}
bool SpellScript::SpellCostCheckAndRemove(WorldEntity* caster)
{
	if ((spell->CostType == PlayerResourceTypes::None) && (spell->ItemCost == 0)) {
		return true;
	}
	Inventory* inventory = null;
	if (spell->ItemCost != 0) {
		inventory = caster->Inventory;
		if (!inventory->SHasItem(spell->ItemCost, 1)) {
			return false;
		}
	}
	if (spell->CostType != PlayerResourceTypes::None) {
		PlayerResource* playerResource = caster->PlayerResourceComponent->SGetPlayerResource(spell->CostType);
		if (playerResource == null) {
			return false;
		}
		if (playerResource->Current < spell->CostResource) {
			return false;
		}
		PlayerResource* expr_87 = playerResource;
		expr_87->Current -= spell->CostResource;
	}
	if (spell->ItemCost != 0) {
		inventory->STryToRemoveItem(spell->ItemCost, 1);
	}
	return true;
}
bool SpellScript::SpellCostCheck(WorldEntity* caster)
{
	if ((spell->CostType == PlayerResourceTypes::None) && (spell->ItemCost == 0)) {
		return true;
	}
	if ((spell->ItemCost != 0) && !caster->Inventory->SHasItem(spell->ItemCost, 1)) {
		return false;
	}
	if (spell->CostType != PlayerResourceTypes::None) {
		PlayerResource* playerResource = caster->PlayerResourceComponent->SGetPlayerResource(spell->CostType);
		if (playerResource == null) {
			return false;
		}
		if (playerResource->Current < spell->CostResource) {
			return false;
		}
	}
	return true;
}
void SpellScript::SpellResourceGive(WorldEntity* caster)
{
	if (spell->GiveResourceType == PlayerResourceTypes::None) {
		return;
	}
	PlayerResource* playerResource = caster->PlayerResourceComponent->SGetPlayerResource(spell->GiveResourceType);
	if (playerResource == null) {
		return;
	}
	if (playerResource->Current == playerResource->Max) {
		return;
	}
	PlayerResource* expr_39 = playerResource;
	expr_39->Current += spell->GiveResource;
}
void SpellScript::AddSpellCastEffect(WorldEntity* caster)
{
	SpellCastEffectData* spellCastEffectData = spell->SpellCastEffectData;
	if (spellCastEffectData->Effect == null) {
		return;
	}
	CharacterEffectPointGetter* component = caster->GetComponent<CharacterEffectPointGetter>();
	if (component != null) {
		component->AddSpellCastEffect(spellCastEffectData->Effect);
	}
}
void SpellScript::RemoveSpellCastEffects(WorldEntity* caster)
{
	CharacterEffectPointGetter* component = caster->GetComponent<CharacterEffectPointGetter>();
	if (component != null) {
		component->RemoveSpellCastEffects();
	}
}
void SpellScript::AddEffect(WorldEntity* player, GameObject* effectPrefab, EffectPoints bodyPart, Quaternion* rotation)
{
	Transform* effectPoint = player->GetComponent<IEffectPointGetter>()->GetEffectPoint(bodyPart);
	if (effectPoint == null) {
		return;
	}
	GameObject* expr_28 = UnityEngine::Object::Instantiate<GameObject>(effectPrefab, Vector3::zero, Quaternion::identity, effectPoint);
	expr_28->AddComponent<EffectIdAttribute>()->Id = spellId;
	expr_28->transform->localRotation = rotation;
	expr_28->transform->localPosition = Vector3::zero;
}
void SpellScript::AddWorldEffect(WorldEntity* location, GameObject* effectPrefab, Vector3* offset, Quaternion* rotation)
{
	UnityEngine::Object::Instantiate<GameObject>(effectPrefab, *(location->transform->position) + *offset, location->transform->rotation)->AddComponent<EffectIdAttribute>()->Id = spellId;
}
void SpellScript::RemoveEffect(WorldEntity* player, EffectPoints bodyPart)
{
	Transform* effectPoint = player->GetComponent<IEffectPointGetter>()->GetEffectPoint(bodyPart);
	if (effectPoint == null) {
		return;
	}
	for (int i = 0; i < effectPoint->childCount; i += 1) {
		Transform* child = effectPoint->GetChild(i);
		EffectIdAttribute* component = child->GetComponent<EffectIdAttribute>();
		if (!component == null && (component->Id == spellId)) {
			child->SetParent(null);
			UnityEngine::Object::Destroy(child->gameObject);
			return;
		}
	}
}
String* SpellScript::StringifyCooldown(float cooldown)
{
	if (cooldown < (float)60) {
		return BOX<int>((int)(cooldown)) + *(new String(" sec"));
	}
	cooldown /= (float)60;
	int num = (int)(cooldown);
	float num2 = (float)(num);
	if (((double)(cooldown) > ((double)(num2) - 0.05)) && ((double)(cooldown) < ((double)(num2) + 0.05))) {
		return BOX<int>(num) + *(new String(" min"));
	}
	return String::Format(new String("{0:0.0} min"), BOX<float>(cooldown));
}
String* SpellScript::GetName()
{
	return spell->SpellName;
}
String* SpellScript::GetDescription(int level)
{
	if (spell->SpellDescription == *(new String(""))) {
		return new String("");
	}
	String* arg_A6_0 = spell->SpellDescription;
	Array<Object>* expr_2E = new Array<Object>(4);
	expr_2E->SetData(0, BOX<int>((int)((float)(spell->DamageMin) * spell->GetDamageScaleForLevel(level))));
	expr_2E->SetData(1, BOX<int>((int)((float)(spell->DamageMax) * spell->GetDamageScaleForLevel(level))));
	expr_2E->SetData(2, StringifyCooldown(spell->Cooldown));
	expr_2E->SetData(3, new String(spell->CastTime) + *(new String(" sec")));
	return String::Format(arg_A6_0, expr_2E);
}
void SpellScript::SpellCastSuccess(WorldEntity* caster)
{
	caster->SpellMgrComponent->SSendSpellCastSuccess(spellId);
}
void SpellScript::PlaySound(String* sound)
{
	SoundMgr::PlaySoundAndForget(sound);
}
void SpellScript::PlayStandardSpellCastFinish()
{
	PlaySound(new String("SpellEnd"));
}
void SpellScript::PlayStandardSpellCastFinish(WorldEntity* caster)
{
	LocalPlayerAnimationController* component = caster->GetComponent<LocalPlayerAnimationController>();
	if (component != null) {
		component->TriggerAttack();
		AnimStop(caster);
	}
	else {
		NetworkedPlayerAnimationController* component2 = caster->GetComponent<NetworkedPlayerAnimationController>();
		if (component2 != null) {
			component2->TriggerAttack();
			AnimStop(caster);
		}
	}
	PlaySound(new String("SpellEnd"));
}
void SpellScript::PlayStandardIceArcherAttackSpellCastFinish(WorldEntity* caster)
{
	LocalPlayerAnimationController* component = caster->GetComponent<LocalPlayerAnimationController>();
	if (component != null) {
		component->TriggerAttack();
		AnimStop(caster);
	}
	else {
		NetworkedPlayerAnimationController* component2 = caster->GetComponent<NetworkedPlayerAnimationController>();
		if (component2 != null) {
			component2->TriggerAttack();
			AnimStop(caster);
		}
	}
	PlaySound(new String("SpellEnd"));
}
void SpellScript::PlayStandardBerserkerAttackSpellCastFinish(WorldEntity* caster)
{
	LocalPlayerAnimationController* component = caster->GetComponent<LocalPlayerAnimationController>();
	if (component != null) {
		component->TriggerAttack();
		AnimStop(caster);
	}
	else {
		NetworkedPlayerAnimationController* component2 = caster->GetComponent<NetworkedPlayerAnimationController>();
		if (component2 != null) {
			component2->TriggerAttack();
			AnimStop(caster);
		}
	}
	PlaySound(new String("MHit"));
}
void SpellScript::AnimStop(WorldEntity* player)
{
	bool arg_0A_0 = BSSettings::Getinstance()->AnimStopEnabled;
}
*/
