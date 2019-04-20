#pragma once
#include <System/System.h>
#include "SpellProjectileData.h"
#include "WorldSpell.h"
#include "Time.h"

using namespace System;
using namespace UnityEngine;
namespace BS {
	namespace SpellsNS {
		namespace WorldSpells {
			//Forward Declaration
			class WorldSpell;

			//Attribute: Serializable*
			class WorldSpellTimeDestroyBehaviour : public virtual Object{
				//Attribute: SerializeField*
				private:
					SpellProjectileData* sattrib;
				//Attribute: SerializeField*
				private:
					float elapsedTIme;
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
					WorldSpellTimeDestroyBehaviour(WorldSpell* owner);
				public:
					void Init();
				public:
					void Update();
			};
		}
	}
}
