#pragma once
#include <System/System.h>
#include "MonoBehaviour.h"
#include "Animator.h"
#include "Transform.h"
#include "SpellCastData.h"
#include "CharacterWeaponDataTypes.h"
#include "GameObject.h"
#include "Vector2.h"
#include "BrokenSeals.h"
#include "Rigidbody2D.h"
#include "RigidbodyConstraints2D.h"
#include "Time.h"
#include "SoundMgr.h"

using namespace UnityEngine;
using namespace System;
namespace BS {
	namespace Player {
		class OldNetworkedPlayerAnimationController : public virtual MonoBehaviour, public virtual Object
		{
			private:
				Array<Animator>* animators;
			private:
				Transform* t;
			private:
				SpellCastData* spellCastData;
			private:
				CharacterWeaponDataTypes weapon;
			private:
				int weaponTypeAsInt;
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
				Transform* cam;
			private:
				bool animatorGameObjectFound;
			private:
				GameObject* animatorgameObject;
			private:
				int framesSinceLastCheck;
			private:
				bool animatorsEnabled;
			private:
				Vector2* lastpostmp;
			private:
				Vector2* v2mtmp;
			private:
				Vector2* tmp;
			private:
				Vector2* tmp2;
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
			public:
				OldNetworkedPlayerAnimationController();
		};
	}
}
