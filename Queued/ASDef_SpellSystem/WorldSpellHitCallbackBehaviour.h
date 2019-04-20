#pragma once
#include <System/System.h>
#include "Transform.h"
#include "WorldSpell.h"
#include "Collider.h"
#include "GameObject.h"
#include "SpellScript.h"
#include "WorldEntity.h"

using namespace System;
using namespace UnityEngine;
using namespace BS::Player;
namespace BS {
	namespace SpellsNS {
		namespace WorldSpells {
			//Forward Declaration
			class WorldSpell;

			//Attribute: Serializable*
			class WorldSpellHitCallbackBehaviour : public virtual Object{
				//Attribute: SerializeField*
				private:
					Transform* t;
				//Attribute: SerializeField*
				private:
					bool didCollide;
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
					WorldSpellHitCallbackBehaviour(WorldSpell* owner);
				public:
					void Init();
				public:
					void OnTriggerEnter(Collider* otherCollider);
			};
		}
	}
}
