#pragma once
#include <System/System.h>
#include "FakeNetworkBehaviour.h"
#include "GameObject.h"
#include <System/Collections/Generic/List.h>
#include "ClientScene.h"
#include "Transform.h"
#include "Vector3.h"
#include "UnityEngine.h"
#include "NetworkServer.h"

using namespace UnityEngine;
using namespace System::Collections::Generic;
using namespace UnityEngine::Networking;
using namespace System;
class MobSpawner : public virtual FakeNetworkBehaviour, public virtual Object
{
	//Attribute: SerializeField*
	private:
		List_T<GameObject>* mobPrefabs;
	//Attribute: SerializeField*
	private:
		List_T<int>* howManyToSpawn;
	//Attribute: SerializeField*
	private:
		bool useRegisteredSpawnPositions;
	private:
		List_T<GameObject>* spawnPoints;
	private:
		void Awake();
	public:
	virtual void Start();
	public:
		void AfterLevelGenerated();
	public:
		void RegisterMobSpawnPoint(GameObject* spawnPoint);
};
