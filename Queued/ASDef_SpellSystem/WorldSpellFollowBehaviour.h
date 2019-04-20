#pragma once
#include <System/System.h>
#include "Transform.h"
#include "WorldEntity.h"
#include "SpellProjectileData.h"
#include "WorldSpell.h"
#include "SpellProjectileType.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Time.h"

using namespace System;
using namespace UnityEngine;
using namespace BS::Player;
namespace BS {
	namespace SpellsNS {
		namespace WorldSpells {
			//Forward Declaration
			class WorldSpell;

			//Attribute: Serializable*
			class WorldSpellFollowBehaviour : public virtual Object{
				//Attribute: SerializeField*
				private:
					Transform* ctransform;
				//Attribute: SerializeField*
				private:
					WorldEntity* target;
				//Attribute: SerializeField*
				private:
					SpellProjectileData* sattrib;
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
					WorldSpellFollowBehaviour(WorldSpell* owner);
				public:
					void Init();
				public:
					void Update();
			};
		}
	}
}
