#include "MobSpawnPointRegister.h"
void MobSpawnPointRegister::Start(){
	GameObject* gameObject = GameObject::FindGameObjectWithTag(new String("LevelGame"));
	if (gameObject != null){
		MobSpawner* component = gameObject->GetComponent<MobSpawner>();
		if (component != null){
			component->RegisterMobSpawnPoint(MonoBehaviour::gameObject);
		}
	}
}

