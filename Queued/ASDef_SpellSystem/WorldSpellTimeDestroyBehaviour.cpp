#include "WorldSpellTimeDestroyBehaviour.h"
namespace BS {
	namespace SpellsNS {
		namespace WorldSpells {
			bool WorldSpellTimeDestroyBehaviour::getEnabled(){
				return this->enabled;
			}
			void WorldSpellTimeDestroyBehaviour::setEnabled(bool value)
			{
				this->enabled = value;
			}
			WorldSpellTimeDestroyBehaviour::WorldSpellTimeDestroyBehaviour(WorldSpell* owner)
			{
				this->owner = owner;
				owner->getSpellProjectileAttribute();
			}
			void WorldSpellTimeDestroyBehaviour::Init()
			{
				if (this->owner->SpellProjectileAttribute->Time > (float)0.001) {
					this->setEnabled(true);
					return;
				}
				this->setEnabled(false);
			}
			void WorldSpellTimeDestroyBehaviour::Update()
			{
				if (!this->getEnabled()) {
					return;
				}
				this->elapsedTIme += Time::deltaTime;
				if (this->elapsedTIme > this->sattrib->Time) {
					this->owner->Destroy();
					return;
				}
			}

		}
	}
}
