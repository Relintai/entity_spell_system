#pragma once
#include <System/System.h>
#include "MonoBehaviour.h"
#include "SpriteAnim.h"
#include "PlayerController.h"
#include "SpellCastData.h"
#include "CharacterWeaponDataTypes.h"
#include "Stats.h"
#include "ValueStat.h"
#include "PlayerData.h"
#include "WorldEntity.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "SoundMgr.h"

using namespace UnityEngine;
using namespace System;
namespace BS {
	namespace Player {
		//Forward Declaration
		class PlayerController;

		class SpriteAnimationController : public virtual MonoBehaviour, public virtual Object{
			private:
				SpriteAnim* animator;
			private:
				PlayerController* playerController;
			private:
				SpellCastData* spellCastData;
			private:
				CharacterWeaponDataTypes weapon;
			private:
				Stats* statComponent;
			private:
				ValueStat* speedStat;
			private:
				PlayerData* playerData;
			private:
				WorldEntity* owner;
			private:
				bool moving;
			private:
				bool casting;
			private:
				bool castingDirty;
			private:
				Vector3* lastpos;
			private:
				Quaternion* movementRotationQuaternion;
			private:
				void Awake();
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
				void OnCastFinished(int spellId);
			public:
				void TriggerAttack();
		};
	}
}
