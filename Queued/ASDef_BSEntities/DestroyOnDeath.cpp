#include "DestroyOnDeath.h"
void DestroyOnDeath::Start(){
	FakeNetworkBehaviour::Start();
	this->lp = FakeNetworkBehaviour::GetComponent<WorldEntity>();
	if (this->isServer){
		Stats* expr_25 = this->lp->Stats;
		expr_25->addSOnDeath(new Stats::SOnDeathAction(DELEGATE_FUNC(DestroyOnDeath::SOnDeath)));
		expr_25->addSOnDamageTaken(new Stats::OnDamageTakenAction(DELEGATE_FUNC(DestroyOnDeath::SOnDamageTaken, _1, _2, _3, _4)));
		this->pd = this->lp->PlayerData;
		this->level = this->pd->Level;
	}
}
void DestroyOnDeath::SOnDeath()
{
	this->destroy = true;
}
void DestroyOnDeath::SOnDamageTaken(int damage, bool crit, WorldEntity* receiver, WorldEntity* dealer)
{
	if (dealer == null) {
		return;
	}
	if (dealer->getFactionComponent()->SIsEnemy(this->lp)) {
		this->lastPlayerDamaged = dealer;
	}
}
void DestroyOnDeath::LateUpdate()
{
	if (this->destroy) {
		if (this->count > 5) {
			if (this->isServer) {
				this->AddXPAndLoot();
			}
			Entity::CUnregisterAIPlayer(this->pd->GUID, this->lp);
			if (this->isServer) {
				Entity::SUnregisterAIPlayer(this->pd->GUID, this->lp);
			}
			UnityEngine::Object::Destroy(FakeNetworkBehaviour::gameObject);
			return;
		}
		this->count += 1;
	}
}
void DestroyOnDeath::AddXPAndLoot()
{
	if (this->lastPlayerDamaged != null) {
		PlayerData* playerData = this->lastPlayerDamaged->PlayerData;
		playerData->RewardXPForMob(this->level);
		LootDataLoader::getInstance()->RandomizeAndAddLoot(this->lastPlayerDamaged, this->lp, playerData);
	}
}

