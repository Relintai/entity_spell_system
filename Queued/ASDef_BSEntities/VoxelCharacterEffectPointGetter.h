#pragma once
#include <System/System.h>
#include "MonoBehaviour.h"
#include "IEffectPointGetter.h"
#include "EffectPoints.h"
#include "Transform.h"
#include <System/Collections/Generic/Dictionary.h>
#include "EffectPointsComparerClass.h"
#include "WorldEntity.h"
#include "PlayerData.h"
#include "ItemData.h"
#include "GameObject.h"
#include <System/Collections/Generic/List.h>
#include "Quaternion.h"
#include "Vector3.h"
#include "ModelMaker.h"
#include "UnityEngine.h"
#include "ItemSubtype.h"
#include "ItemSubSubtype.h"

using namespace UnityEngine;
using namespace System::Collections::Generic;
using namespace BS::Data::Items;
using namespace BS::Player::Models;
using namespace System;
namespace BS {
	namespace Player {
		//Forward Declaration
		class WorldEntity;

		class VoxelCharacterEffectPointGetter : public virtual MonoBehaviour, public virtual IEffectPointGetter, public virtual Object{
			private:
				Dictionary_T<EffectPoints, Transform>* bodyParts;
			private:
				Transform* umat;
			private:
				WorldEntity* we;
			private:
				PlayerData* pd;
			private:
				ItemData* itemData;
			private:
				bool weaponInstantiated;
			private:
				List_T<GameObject>* sces;
			private:
				Quaternion* wepLocalRotation;
			private:
				Vector3* scaleTmp;
			private:
				List_T<GameObject>* hl;
			private:
				void Start();
			public:
				Transform* GetEffectPoint(EffectPoints bodyPartEffectPoint);
			public:
				void AddSpellCastEffect(GameObject* prefab);
			public:
				void RemoveSpellCastEffects();
			public:
				void UmaChanged(GameObject* umaGo);
			private:
				void OnWeaponChanged(ItemData* id);
			private:
				void OnWeaponPrefabLoaded(ItemData* id);
			private:
				EffectPoints GetEffectPointForItemData(ItemData* id);
			public:
				VoxelCharacterEffectPointGetter();
		};
	}
}
