#include "LootDataLoader.h"
namespace BS {
	namespace Loot {
		LootDataLoader* LootDataLoader::getInstance(){
			return Instance_var;
		}
		void LootDataLoader::setInstance(LootDataLoader* value)
		{
			Instance_var = value;
		}
		void LootDataLoader::Awake()
		{
			LootDataLoader::setInstance(this);
		}
		void LootDataLoader::RandomizeAndAddLoot(WorldEntity* player, WorldEntity* mob, PlayerData* mobPD)
		{
			Inventory* inventory = player->getInventory();
			inventory->SAddCraftMaterial(1, UnityEngine::Random::Range(10, 24));
			inventory->SAddCraftMaterial(3, UnityEngine::Random::Range(1, 3));
			LootDataAttribute* lootDataAttribute = null;
			if (lootDataAttribute == null) {
				return;
			}
			if (lootDataAttribute->Data->Count == 0) {
				return;
			}
			int num = UnityEngine::Random::Range(lootDataAttribute->MinNum, lootDataAttribute->MaxNum);
			if (num <= 0) {
				return;
			}
			this->itemtmp->Clear();
			this->itemTmp2->Clear();
			int num2 = 0;
			int num3 = 0;
			int num4 = (num * 2) + 1;
			while ((num > num2) && (num3 <= num4)) {
				bool flag = false;
				while (!flag) {
					num3 += 1;
					if (num3 > num4) {
						flag = true;
					}
					int num5 = UnityEngine::Random::Range(0, lootDataAttribute->Data->Count);
					if (!this->itemTmp2->Contains(num5)) {
						LootDataAttributeHelper* lootDataAttributeHelper = lootDataAttribute->Data->GetData(num5);
						if (UnityEngine::Random::Range((float)0, lootDataAttributeHelper->Percent) <= lootDataAttributeHelper->Percent) {
							this->itemTmp2->Add(num5);
							this->itemtmp->Add(lootDataAttributeHelper);
							num2 += 1;
							if (num2 >= num) {
								break;
							}
						}
					}
				}
			}
			if (inventory == null) {
				return;
			}
			for (int i = 0; i < this->itemtmp->Count; i += 1) {
				inventory->SAddCraftMaterial(this->itemtmp->GetData(i)->ItemId, 1);
			}
		}
		void LootDataLoader::OnDestroy()
		{
			LootDataLoader::setInstance(null);
		}
		LootDataLoader* LootDataLoader::Instance_var;
		LootDataLoader::LootDataLoader()
		{
			data = new List_T<LootDataAttributeHelper>();
			itemtmp = new List_T<LootDataAttributeHelper>();
			itemTmp2 = new List_T<int>();
			Instance_var = (LootDataLoader*)(0);
		}

	}
}
