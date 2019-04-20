#pragma once
#include <System/System.h>
#include "MonoBehaviour.h"
#include "GameObject.h"
#include <System/Collections/Generic/List.h>
#include "Transform.h"
#include "UnityEngine.h"

using namespace UnityEngine;
using namespace System::Collections::Generic;
using namespace System;
class SpawnPointManager : public virtual MonoBehaviour, public virtual Object
{
	//Attribute: SerializeField*
	private:
		bool automaticSpawn;
	private:
		List_T<GameObject>* spawnPoints;
	private:
		List_T<GameObject>* graveyardSpawnPoints;
	public:
		bool getAutomaticSpawn();
		//Ignored empty method declaration
	public:
		List_T<GameObject>* getSpawnPoints();
		//Ignored empty method declaration
	public:
		List_T<GameObject>* getGraveyardSpawnPoints();
		//Ignored empty method declaration
	private:
		void Start();
	public:
		void Refresh();
	public:
		GameObject* GetSpawnPoint();
	public:
		GameObject* GetGraveyardSpawnPoint();
	public:
		SpawnPointManager();
};
