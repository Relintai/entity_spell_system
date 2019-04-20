#pragma once
#include <System/System.h>
#include "BaseWorldSpell.h"
#include "WorldSpellTimeDestroyBehaviour.h"
#include "WorldSpellStraightBehaiour.h"
#include "WorldSpellHitCallbackBehaviour.h"
#include "WorldSpellFollowBehaviour.h"
#include "SpellProjectileData.h"
#include "WorldEntity.h"
#include "Spell.h"
#include "Vector3.h"
#include "BSState.h"
#include "Collider.h"
#include "UnityEngine.h"

using namespace UnityEngine;
using namespace BS::Player;
using namespace System;
namespace BS {
	namespace SpellsNS {
		namespace WorldSpells {
			//Forward Declaration
			class WorldSpellTimeDestroyBehaviour;

			class WorldSpell : public virtual BaseWorldSpell, public virtual Object{
				//Attribute: SerializeField*
				private:
					WorldSpellTimeDestroyBehaviour* WorldSpellTimeDestroyBehaviour;
				//Attribute: SerializeField*
				private:
					WorldSpellStraightBehaiour* WorldSpellStraightBehaiour;
				//Attribute: SerializeField*
				private:
					WorldSpellHitCallbackBehaviour* WorldSpellHitCallbackBehaviour;
				//Attribute: SerializeField*
				private:
					WorldSpellFollowBehaviour* WorldSpellFollowBehaviour;
				//Attribute: SerializeField*
				private:
					SpellProjectileData* spellProjectileAttribute;
				//Attribute: SerializeField*
				private:
					WorldEntity* caster;
				//Attribute: SerializeField*
				private:
					WorldEntity* target;
				//Attribute: SerializeField*
				private:
					Spell* spell;
				//Attribute: SerializeField*
				private:
					float spellScale;
				//Attribute: SerializeField*
				private:
					Vector3* dir;
				public:
					SpellProjectileData* getSpellProjectileAttribute();
				public:
					void setSpellProjectileAttribute(SpellProjectileData* value);
				public:
					WorldEntity* getCaster();
					//Ignored empty method declaration
				public:
					WorldEntity* getTarget();
				public:
					void setTarget(WorldEntity* value);
				public:
					Spell* getSpell();
					//Ignored empty method declaration
				public:
					float getSpellScale();
					//Ignored empty method declaration
				public:
					Vector3* getDir();
					//Ignored empty method declaration
				public:
					Object* getData();
				public:
					void setData(Object* value);
				private:
					void Awake();
				public:
					void Init();
				private:
					void Update();
				public:
					void OnTriggerEnter(Collider* otherCollider);
				public:
					void Destroy();
				public:
					void SetData(SpellProjectileData* spellProjectileAttribute, WorldEntity* caster, Spell* spell, float spellScale, Vector3* dir = , WorldEntity* target = null);
				public:
					void SetData(WorldSpell* other);
				public:
					Object* Data_var;
				public:
					WorldSpell();
			};
		}
	}
}
