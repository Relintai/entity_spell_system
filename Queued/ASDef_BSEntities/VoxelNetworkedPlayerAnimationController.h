#pragma once
#include <System/System.h>
#include "MonoBehaviour.h"
#include "Vector3.h"
#include "Animator.h"
#include "WorldEntity.h"
#include "Transform.h"
#include "SpellCastData.h"
#include "Stats.h"
#include "StateComponent.h"
#include "PlayerData.h"
#include "ValueStat.h"
#include "ItemData.h"
#include "Entity.h"
#include "GameObject.h"
#include "Vector2.h"
#include "Quaternion.h"
#include "RaycastHit.h"
#include "ModelMaker.h"
#include "Time.h"
#include "SoundMgr.h"
#include "StateData.h"
#include "Physics.h"

using namespace UnityEngine;
using namespace BS::Data::Items;
using namespace BS::Player::Models;
using namespace System;
namespace BS {
	namespace Player {
		//Forward Declaration
		class WorldEntity;

		class VoxelNetworkedPlayerAnimationController : public virtual MonoBehaviour, public virtual Object{
			private:
				float maxAnimationSpeed;
			private:
				float runSpeedMultiplier;
			private:
				float switchDistance;
			private:
				float umaGenerateDistance;
			private:
				Vector3* localPosition;
			private:
				Animator* animator;
			private:
				WorldEntity* we;
			private:
				Transform* t;
			private:
				SpellCastData* spellCastData;
			private:
				Stats* statComponent;
			private:
				StateComponent* stateComponent;
			private:
				PlayerData* pd;
			private:
				ValueStat* speed;
			private:
				ItemData* itemData;
			private:
				bool stun;
			private:
				bool moving;
			private:
				bool movingchanged;
			private:
				bool casting;
			private:
				bool castingDirty;
			private:
				Transform* lptr;
			private:
				Entity* localPlayer;
			private:
				bool animatorGameObjectFound;
			private:
				GameObject* animatorgameObject;
			private:
				int framesSinceLastCheck;
			private:
				bool animatorsEnabled;
			private:
				bool movestopQueued;
			private:
				float timeSinceQueue;
			private:
				Vector3* lastpostmp;
			private:
				Vector2* v2mtmp;
			private:
				Vector2* tmp;
			private:
				Vector3* v3tmp2;
			private:
				Vector3* v3tmp;
			private:
				bool umaGenerated;
			private:
				Quaternion* fq;
			private:
				Vector3* rchtmp;
			public:
				RaycastHit* rcht;
			private:
				int LAYER;
			public:
				float getMaxAnimationSpeed();
			public:
				void setMaxAnimationSpeed(float value);
			public:
				float getRunSpeedMultiplier();
			public:
				void setRunSpeedMultiplier(float value);
			private:
				void Start();
			private:
				void Update();
			private:
				void OnCastStarted(int spellId);
			private:
				void OnCastEnded(int spellId);
			private:
				void OnCastFailed(int spellId);
			private:
				void OnDied();
			private:
				void OnCastFinished(int spellId);
			private:
				void OnUMAChanged(GameObject* umaGO);
			private:
				void OnWeaponChanged(ItemData* id);
			public:
				void TriggerAttack();
			private:
				void COnStateChanged();
			private:
				void LocalPlayerChanged(Entity* lp);
			private:
				bool IsInLOS(Transform* p1, Transform* p2);
			public:
				VoxelNetworkedPlayerAnimationController();
		};
	}
}
