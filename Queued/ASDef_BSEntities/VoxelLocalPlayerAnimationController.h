#pragma once
#include <System/System.h>
#include "MonoBehaviour.h"
#include "Animator.h"
#include "WorldEntity.h"
#include "SpellCastData.h"
#include "PlayerData.h"
#include "TargetComponent.h"
#include "StateComponent.h"
#include "Stats.h"
#include "ValueStat.h"
#include "PlayerController.h"
#include "ItemData.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Transform.h"
#include "Quaternion.h"
#include "BSState.h"
#include "BrokenSeals.h"
#include "ModelMaker.h"
#include "Time.h"
#include "SoundMgr.h"
#include "GameObject.h"
#include "StateData.h"

using namespace UnityEngine;
using namespace BS::Data::Items;
using namespace BS::Player::Models;
using namespace System;
namespace BS {
	namespace Player {
		//Forward Declaration
		class WorldEntity;

		class VoxelLocalPlayerAnimationController : public virtual MonoBehaviour, public virtual Object{
			//Attribute: SerializeField*
			private:
				float maxAnimationSpeed;
			//Attribute: SerializeField*
			private:
				float runSpeedMultiplier;
			private:
				Animator* animator;
			private:
				WorldEntity* we;
			private:
				SpellCastData* spellCastData;
			private:
				PlayerData* pd;
			private:
				TargetComponent* targetComp;
			private:
				StateComponent* stateComponent;
			private:
				Stats* statComponent;
			private:
				ValueStat* speed;
			private:
				PlayerController* playerController;
			private:
				ItemData* itemData;
			private:
				bool casting;
			private:
				bool castingDirty;
			private:
				Vector3* lastpostmp;
			private:
				Vector2* v2mtmp;
			private:
				Vector3* localPosition;
			private:
				bool overridefacing;
			private:
				float overrideRemainingTime;
			//Attribute: SerializeField*
			private:
				float overridefor;
			private:
				bool moving;
			private:
				bool turning;
			private:
				bool stun;
			private:
				float turnOffTimer;
			private:
				bool hasTurnOffTimer;
			private:
				Transform* t;
			private:
				Vector3* ftv3;
			private:
				Quaternion* fq;
			private:
				Vector3* up;
			private:
				Vector3* overrideTmp;
			private:
				bool menuOpen;
			private:
				Vector3* lastpos;
			public:
				float getMaxAnimationSpeed();
			public:
				void setMaxAnimationSpeed(float value);
			public:
				float getRunSpeedMultiplier();
			public:
				void setRunSpeedMultiplier(float value);
			private:
				void Awake();
			private:
				void Start();
			private:
				void Update();
			public:
				void Turned(bool turned, float direction);
			private:
				void OnCastStarted(int spellId);
			private:
				void OnCastEnded(int spellId);
			private:
				void OnCastFailed(int spellId);
			private:
				void OnCastFinished(int spellId);
			private:
				void OnDied();
			private:
				void OnIngameMenuChanged(bool open);
			public:
				void TriggerAttack();
			private:
				void OnUMAChanged(GameObject* umaGO);
			private:
				void OnWeaponChanged(ItemData* id);
			private:
				void COnStateChanged();
			private:
				void StartFacingOverride();
			private:
				void OnAnimStopped();
			private:
				void OnAnimStopFinished();
			public:
				VoxelLocalPlayerAnimationController();
		};
	}
}
