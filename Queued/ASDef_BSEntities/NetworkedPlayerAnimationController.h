#pragma once
#include <System/System.h>
#include "MonoBehaviour.h"
#include "Animator.h"
#include "Transform.h"
#include "SpellCastData.h"
#include "CharacterWeaponDataTypes.h"
#include "Puppet2D_GlobalControl.h"
#include "Entity.h"
#include "GameObject.h"
#include "ValueStat.h"
#include "WorldEntity.h"
#include "Vector2.h"
#include "Time.h"
#include "Mathf.h"
#include "Vector3.h"
#include "SoundMgr.h"

using namespace UnityEngine;
using namespace Puppet2D;
using namespace System;
namespace BS {
	namespace Player {
		//Forward Declaration
		class SpellCastData;

		class NetworkedPlayerAnimationController : public virtual MonoBehaviour, public virtual Object{
			private:
				Array<Animator>* animators;
			private:
				Transform* t;
			private:
				SpellCastData* spellCastData;
			private:
				CharacterWeaponDataTypes weapon;
			private:
				Puppet2D_GlobalControl* pgd;
			private:
				bool moving;
			private:
				bool wasMoving;
			private:
				bool casting;
			private:
				bool movestopQueued;
			private:
				float timeSinceQueue;
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
				ValueStat* speedStat;
			private:
				WorldEntity* we;
			private:
				Vector2* lastpostmp;
			private:
				Vector2* v2mtmp;
			private:
				Vector2* tmp;
			private:
				Vector2* tmp2;
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
			private:
				void LocalPlayerChanged(Entity* lp);
			public:
				void TriggerAttack();
			public:
				NetworkedPlayerAnimationController();
		};
	}
}
