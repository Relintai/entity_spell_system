#pragma once
#include <System/System.h>
#include "MonoBehaviour.h"
#include "Animator.h"
#include "Player.h"
#include "WorldEntity.h"
#include "SpellCastData.h"
#include "CharacterWeaponDataTypes.h"
#include "Vector2.h"
#include "ReInput.h"
#include "SoundMgr.h"

using namespace UnityEngine;
using namespace Rewired;
using namespace System;
namespace BS {
	namespace Player {
		class OldLocalPlayerAnimationController : public virtual MonoBehaviour, public virtual Object
		{
			private:
				Array<Animator>* animators;
			private:
				Player* rPlayer;
			private:
				WorldEntity* owner;
			private:
				SpellCastData* spellCastData;
			private:
				CharacterWeaponDataTypes weapon;
			private:
				int weaponTypeAsInt;
			private:
				bool moving;
			private:
				bool casting;
			private:
				bool castingDirty;
			private:
				Vector2* v2mtmp;
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
