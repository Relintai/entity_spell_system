#pragma once
#include <System/System.h>
#include "MonoBehaviour.h"
#include "LootDataAttributeHelper.h"
#include <System/Collections/Generic/List.h>
#include "WorldEntity.h"
#include "PlayerData.h"
#include "Inventory.h"
#include "UnityEngine.h"
#include "LootDataAttribute.h"

using namespace UnityEngine;
using namespace BS::Data::Loot;
using namespace System::Collections::Generic;
using namespace BS::Player;
using namespace System;
namespace BS {
	namespace Loot {
		//Forward Declaration
		class WorldEntity;

		class LootDataLoader : public virtual MonoBehaviour, public virtual Object{
			//Attribute: SerializeField*
			private:
				List_T<LootDataAttributeHelper>* data;
			private:
				List_T<LootDataAttributeHelper>* itemtmp;
			private:
				List_T<int>* itemTmp2;
			public:
			static LootDataLoader* getInstance();
			public:
			static void setInstance(LootDataLoader* value);
			private:
				void Awake();
			public:
				void RandomizeAndAddLoot(WorldEntity* player, WorldEntity* mob, PlayerData* mobPD);
			private:
				void OnDestroy();
			public:
			static LootDataLoader* Instance_var;
			public:
				LootDataLoader();
		};
	}
}
