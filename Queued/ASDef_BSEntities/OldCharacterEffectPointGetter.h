#pragma once
#include <System/System.h>
#include "MonoBehaviour.h"
#include "IEffectPointGetter.h"
#include "EffectPoints.h"
#include "Transform.h"
#include <System/Collections/Generic/Dictionary.h>
#include "EffectPointsComparerClass.h"
#include "PlayerData.h"
#include "ItemData.h"
#include "GameObject.h"
#include <System/Collections/Generic/List.h>
#include "Quaternion.h"
#include "Vector3.h"
#include "<PrivateImplementationDetails>.h"
#include "UnityEngine.h"
#include "ItemSubtype.h"
#include "ItemSubSubtype.h"

using namespace UnityEngine;
using namespace System::Collections::Generic;
using namespace BS::Data::Items;
using namespace System;
namespace BS {
	namespace Player {
		class OldCharacterEffectPointGetter : public virtual MonoBehaviour, public virtual IEffectPointGetter, public virtual Object
		{
			private:
				Dictionary_T<EffectPoints, Transform>* bodyParts;
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
			private:
				void OnWeaponChanged(ItemData* id);
			private:
				void OnWeaponPrefabLoaded(ItemData* id);
			private:
				EffectPoints GetEffectPointForItemData(ItemData* id);
			public:
				OldCharacterEffectPointGetter();
		};
	}
}
