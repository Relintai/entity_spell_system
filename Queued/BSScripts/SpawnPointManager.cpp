#include "SpawnPointManager.h"
bool SpawnPointManager::getAutomaticSpawn(){
	return this->automaticSpawn;
}
List_T<GameObject>* SpawnPointManager::getSpawnPoints()
{
	return this->spawnPoints;
}
List_T<GameObject>* SpawnPointManager::getGraveyardSpawnPoints()
{
	return this->graveyardSpawnPoints;
}
void SpawnPointManager::Start()
{
	this->Refresh();
}
void SpawnPointManager::Refresh()
{
	if (this->spawnPoints == null) {
		return;
	}
	this->spawnPoints->Clear();
	this->graveyardSpawnPoints->Clear();
	FOREACH(_TRANSFORM, MonoBehaviour::transform) {
		Transform deref_transform = *_TRANSFORM;
		Transform* transform = &deref_transform;
		if (!transform->name->StartsWith(new String("GY"))) {
			this->spawnPoints->Add(transform->gameObject);
		}
		else {
			this->graveyardSpawnPoints->Add(transform->gameObject);
		}
	}
}
GameObject* SpawnPointManager::GetSpawnPoint()
{
	if (this->spawnPoints->Count == 0) {
		return null;
	}
	int index = UnityEngine::Random::Range(0, this->spawnPoints->Count);
	return this->spawnPoints->GetData(index);
}
GameObject* SpawnPointManager::GetGraveyardSpawnPoint()
{
	if (this->getGraveyardSpawnPoints()->Count == 0) {
		return this->GetSpawnPoint();
	}
	int index = UnityEngine::Random::Range(0, this->graveyardSpawnPoints->Count);
	return this->graveyardSpawnPoints->GetData(index);
}
SpawnPointManager::SpawnPointManager()
{
	automaticSpawn = true;
	spawnPoints = new List_T<GameObject>();
	graveyardSpawnPoints = new List_T<GameObject>();
}

