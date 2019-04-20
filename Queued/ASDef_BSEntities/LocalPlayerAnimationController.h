#pragma once
#include <System/System.h>
#include "MonoBehaviour.h"
#include "Animator.h"
#include "ValueStat.h"
#include "WorldEntity.h"
#include "PlayerController.h"
#include "SpellCastData.h"
#include "CharacterWeaponDataTypes.h"
#include "Puppet2D_GlobalControl.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Quaternion.h"
#include "Mathf.h"
#include "SoundMgr.h"

using namespace UnityEngine;
using namespace Puppet2D;
using namespace System;
namespace BS {
	namespace Player {
		//Forward Declaration
		class WorldEntity;

		class LocalPlayerAnimationController : public virtual MonoBehaviour, public virtual Object{
			private:
				Array<Animator>* animators;
			private:
				ValueStat* speedStat;
			private:
				WorldEntity* owner;
			private:
				PlayerController* playerController;
			private:
				SpellCastData* spellCastData;
			private:
				CharacterWeaponDataTypes weapon;
			private:
				Puppet2D_GlobalControl* pgd;
			private:
				bool moving;
			private:
				bool casting;
			private:
				bool castingDirty;
			private:
				Vector3* lastpos;
			private:
				Vector2* v2mtmp;
			private:
				Quaternion* movementRotationQuaternion;
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
			public:
				LocalPlayerAnimationController();
		};
	}
}
