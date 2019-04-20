#pragma once
#include <System/System.h>
#include "Vector3.h"
#include "Rigidbody.h"
#include "SpellProjectileData.h"
#include "Transform.h"
#include "WorldSpell.h"
#include "SpellProjectileType.h"
#include "Time.h"

using namespace System;
using namespace UnityEngine;
namespace BS {
	namespace SpellsNS {
		namespace WorldSpells {
			//Forward Declaration
			class WorldSpell;

			//Attribute: Serializable*
			class WorldSpellStraightBehaiour : public virtual Object{
				//Attribute: SerializeField*
				private:
					Vector3* direction;
				//Attribute: SerializeField*
				public:
					Vector3* startPosition;
				//Attribute: SerializeField*
				private:
					Rigidbody* rb;
				//Attribute: SerializeField*
				private:
					SpellProjectileData* sattrib;
				//Attribute: SerializeField*
				private:
					Transform* t;
				//Attribute: SerializeField*
				private:
					bool enabled;
				private:
					WorldSpell* owner;
				public:
					bool getEnabled();
				public:
					void setEnabled(bool value);
				public:
					WorldSpellStraightBehaiour(WorldSpell* owner);
				public:
					void Init();
				public:
					void Update();
			};
		}
	}
}
