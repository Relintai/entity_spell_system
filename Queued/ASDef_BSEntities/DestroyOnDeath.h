#pragma once
#include <System/System.h>
#include "FakeNetworkBehaviour.h"
#include "WorldEntity.h"
#include "PlayerData.h"
#include "Stats.h"
#include "Entity.h"
#include "UnityEngine.h"
#include "LootDataLoader.h"

using namespace BS::Player;
using namespace BS::Loot;
using namespace System;
//Forward Declaration
class WorldEntity;

class DestroyOnDeath : public virtual FakeNetworkBehaviour, public virtual Object{
	private:
		bool destroy;
	private:
		int count;
	private:
		WorldEntity* lp;
	private:
		WorldEntity* lastPlayerDamaged;
	private:
		PlayerData* pd;
	private:
		int level;
	public:
	virtual void Start();
	public:
		void SOnDeath();
	public:
		void SOnDamageTaken(int damage, bool crit, WorldEntity* receiver, WorldEntity* dealer);
	private:
		void LateUpdate();
	private:
		void AddXPAndLoot();
};
