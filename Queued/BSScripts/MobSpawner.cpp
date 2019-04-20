#include "MobSpawner.h"
void MobSpawner::Awake(){
	this->spawnPoints = new List_T<GameObject>();
}
void MobSpawner::Start()
{
	for (int i = 0; i < this->mobPrefabs->Count; i += 1) {
		ClientScene::RegisterPrefab(this->mobPrefabs->GetData(i));
	}
	if (this->isServer && !this->useRegisteredSpawnPositions) {
		Transform* transform = FakeNetworkBehaviour::transform->Find(new String("MobSpawnPositions"))->gameObject->transform;
		Vector3* position = new Vector3*();
		for (int j = 0; j < transform->childCount; j += 1) {
			Transform* child = transform->GetChild(j);
			int index = UnityEngine::Random::Range(0, this->mobPrefabs->Count);
			int num = this->howManyToSpawn->GetData(index);
			for (int k = 0; k < num; k += 1) {
				position->Set(child->position->x + ((UnityEngine::Random::value * (float)2) - (float)1), child->position->y, child->position->z + ((UnityEngine::Random::value * (float)2) - (float)1));
				NetworkServer::Spawn(UnityEngine::Object::Instantiate<GameObject>(this->mobPrefabs->GetData(index), position, child->rotation));
			}
		}
	}
}
void MobSpawner::AfterLevelGenerated()
{
	if (this->isServer && this->useRegisteredSpawnPositions) {
		Vector3* position = new Vector3*();
		for (int i = 0; i < this->spawnPoints->Count; i += 1) {
			Transform* transform = this->spawnPoints->GetData(i)->transform;
			int index = UnityEngine::Random::Range(0, this->mobPrefabs->Count);
			int num = this->howManyToSpawn->GetData(index);
			for (int j = 0; j < num; j += 1) {
				position->Set(transform->position->x + ((UnityEngine::Random::value * (float)2) - (float)1), transform->position->y, transform->position->z + ((UnityEngine::Random::value * (float)2) - (float)1));
				NetworkServer::Spawn(UnityEngine::Object::Instantiate<GameObject>(this->mobPrefabs->GetData(index), position, transform->rotation));
			}
		}
	}
}
void MobSpawner::RegisterMobSpawnPoint(GameObject* spawnPoint)
{
	this->spawnPoints->Add(spawnPoint);
}

