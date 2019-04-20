#include "SpellMgrComponent.h"
SpellMgrComponent::SpellMgrComponent(WorldEntity* owner){
	this->owner = owner;
}
void SpellMgrComponent::Init()
{
	if (this->init) {
		return;
	}
	this->init = true;
	Character* character = this->owner->PlayerData->Character;
	if (this->owner->PlayerData->Type != 3) {
		this->spellIds = character->Spells;
	}
	this->dataPresent = true;
	this->itemDataLoader = ItemDataLoader::Instance;
}
void SpellMgrComponent::OnLevelLoaded()
{
}
void SpellMgrComponent::CSendCastSpellRequest(int spellId)
{
	if (!this->owner->isLocalPlayer) {
		return;
	}
	if (Spells::Instance->GetData(spellId)->GetComponent<Spell>()->IsLocalSpell) {
		SpellMgr::CastSpell(this->owner, spellId, (float)1);
		return;
	}
	if (this->owner->PlayerData->State != PlayerStates::STATE_NORMAL) {
		return;
	}
	if (this->owner->Stats->CIsDead) {
		return;
	}
	if (!this->dataPresent) {
		this->CSendCastSpell(spellId);
		return;
	}
	if (!this->PlayerKnowsSpell(spellId)) {
		return;
	}
	this->CSendCastSpell(spellId);
}
void SpellMgrComponent::CSendCastItemSpellRequest(ItemData* itemData)
{
	if (!this->owner->isLocalPlayer) {
		return;
	}
	int spellId = itemData->SpellId;
	if (Spells::Instance->GetData(spellId)->GetComponent<Spell>()->IsLocalSpell) {
		SpellMgr::CastSpell(this->owner, spellId, (float)1);
		return;
	}
	if (this->owner->PlayerData->State != PlayerStates::STATE_NORMAL) {
		return;
	}
	if (this->owner->Stats->CIsDead) {
		return;
	}
	if (!this->dataPresent) {
		this->CSendCastItemSpell(itemData->Id);
		return;
	}
	if (!this->owner->Inventory->CHasItem(itemData->Id, 1)) {
		return;
	}
	this->CSendCastItemSpell(itemData->Id);
}
void SpellMgrComponent::CSendCastSpell(int spellId)
{
	if (CxNet::IsClient) {
		SSpellCastRequestMsg sSpellCastRequestMsg = SSpellCastRequestMsg();
		sSpellCastRequestMsg.SpellId = spellId;
		sSpellCastRequestMsg.Serialize(CxNet::NetBuffer);
		CxNet::SendBufferToServer(0);
	}
}
void SpellMgrComponent::CSendCastItemSpell(int itemId)
{
	if (CxNet::IsClient) {
		SItemSpellCastRequestMsg sItemSpellCastRequestMsg = SItemSpellCastRequestMsg();
		sItemSpellCastRequestMsg.ItemId = itemId;
		sItemSpellCastRequestMsg.Serialize(CxNet::NetBuffer);
		CxNet::SendBufferToServer(0);
	}
}
void SpellMgrComponent::SSendSpellCastSuccess(int spellId)
{
	if (CxNet::IsServer) {
		CSpellCastEventSuccessMsg cSpellCastEventSuccessMsg = CSpellCastEventSuccessMsg();
		cSpellCastEventSuccessMsg.Guid = this->owner->PlayerData->GUID;
		cSpellCastEventSuccessMsg.SpellId = spellId;
		cSpellCastEventSuccessMsg.Serialize(CxNet::NetBuffer);
		CxNet::SendBufferToAllClients(0);
	}
}
void SpellMgrComponent::SSendSpellCastFailed(int spellId)
{
	if (CxNet::IsServer) {
		CSpellCastEventFailedMsg cSpellCastEventFailedMsg = CSpellCastEventFailedMsg();
		cSpellCastEventFailedMsg.Guid = this->owner->PlayerData->GUID;
		cSpellCastEventFailedMsg.SpellId = spellId;
		cSpellCastEventFailedMsg.Serialize(CxNet::NetBuffer);
		CxNet::SendBufferToAllClients(0);
	}
}
void SpellMgrComponent::CReceiveSpellCastSuccess(int spellId)
{
	if (!Spells::Instance->SpellsDict->ContainsKey(spellId)) {
		return;
	}
	SpellMgr::COnSpellCastSuccess(this->owner, spellId);
}
void SpellMgrComponent::CReceiveSpellSpellCastFailed(int spellId)
{
	if (!Spells::Instance->SpellsDict->ContainsKey(spellId)) {
		return;
	}
	DELEGATE_INVOKE(SpellMgr::COnCastFailed, this->owner, spellId);
}
void SpellMgrComponent::SReceiveCastSpellRequest(int spellId)
{
	if (this->owner->PlayerData->State != PlayerStates::STATE_NORMAL) {
		return;
	}
	if (!this->owner->isServer || this->owner->Stats->sIsDead) {
		return;
	}
	if (!this->PlayerKnowsSpell(spellId)) {
		return;
	}
	if (this->owner->isLocalPlayer) {
		if (this->lastLevel != this->owner->PlayerData->Level) {
			this->lastLevel = this->owner->PlayerData->Level;
			BrokenSeals::BSDebugSettings->SpellScale = this->owner->PlayerData->Character->Stats->SpellScaling->Evaluate((float)(this->owner->PlayerData->Level));
		}
		SpellMgr::CastSpell(this->owner, spellId, BrokenSeals::BSDebugSettings->SpellScale);
		return;
	}
	SpellMgr::CastSpell(this->owner, spellId, this->owner->PlayerData->Character->Stats->SpellScaling->Evaluate((float)(this->owner->PlayerData->Level)));
}
void SpellMgrComponent::SReceiveCastItemSpellRequest(int itemId)
{
	if (this->owner->PlayerData->State != PlayerStates::STATE_NORMAL) {
		return;
	}
	if (!this->owner->isServer || this->owner->Stats->sIsDead) {
		return;
	}
	if (!this->itemDataLoader->data->ContainsKey(itemId)) {
		return;
	}
	ItemData* component = this->itemDataLoader->data->GetData(itemId)->GetComponent<ItemData>();
	if (component == null) {
		return;
	}
	int spellId = component->SpellId;
	if (spellId == 0) {
		return;
	}
	if (!this->owner->Inventory->SHasItem(itemId, 1)) {
		return;
	}
	if (this->owner->isLocalPlayer) {
		if (this->lastLevel != this->owner->PlayerData->Level) {
			this->lastLevel = this->owner->PlayerData->Level;
			BrokenSeals::BSDebugSettings->SpellScale = this->owner->PlayerData->Character->Stats->SpellScaling->Evaluate((float)(this->owner->PlayerData->Level));
		}
		SpellMgr::CastSpell(this->owner, spellId, BrokenSeals::BSDebugSettings->SpellScale);
		return;
	}
	SpellMgr::CastSpell(this->owner, spellId, this->owner->PlayerData->Character->Stats->SpellScaling->Evaluate((float)(this->owner->PlayerData->Level)));
}
void SpellMgrComponent::SCastSpell(int spellId)
{
	if (this->owner->PlayerData->State != PlayerStates::STATE_NORMAL) {
		return;
	}
	if (!this->owner->isServer || this->owner->Stats->sIsDead) {
		return;
	}
	if (!this->PlayerKnowsSpell(spellId)) {
		return;
	}
	if (this->owner->isLocalPlayer) {
		if (this->lastLevel != this->owner->PlayerData->Level) {
			this->lastLevel = this->owner->PlayerData->Level;
			BrokenSeals::BSDebugSettings->SpellScale = this->owner->PlayerData->Character->Stats->SpellScaling->Evaluate((float)(this->owner->PlayerData->Level));
		}
		SpellMgr::CastSpell(this->owner, spellId, BrokenSeals::BSDebugSettings->SpellScale);
		return;
	}
	SpellMgr::CastSpell(this->owner, spellId, this->owner->PlayerData->Character->Stats->SpellScaling->Evaluate((float)(this->owner->PlayerData->Level)));
}
void SpellMgrComponent::AICastSpell(int spellId)
{
	if (this->owner->PlayerData->State != PlayerStates::STATE_NORMAL) {
		return;
	}
	if (!this->owner->isServer || this->owner->Stats->sIsDead) {
		return;
	}
	SpellMgr::CastSpell(this->owner, spellId, this->owner->PlayerData->Character->Stats->SpellScaling->Evaluate((float)(this->owner->PlayerData->Level)));
}
bool SpellMgrComponent::PlayerKnowsSpell(int spellID)
{
	bool flag = false;
	for (int i = 0; i < this->spellIds->SpellIds->Count; i += 1) {
		if (this->spellIds->SpellIds->GetData(i) == spellID) {
			flag = true;
			break;
		}
	}
	bool flag2 = true;
	if ((flag && (this->owner->PlayerData != null)) && (Spells::Instance->GetData(spellID)->gameObject->GetComponent<Spell>()->Level > this->owner->PlayerData->Level)) {
		flag2 = false;
	}
	return flag & flag2;
}

