#include "WorldSpellHitCallbackBehaviour.h"
namespace BS {
	namespace SpellsNS {
		namespace WorldSpells {
			bool WorldSpellHitCallbackBehaviour::getEnabled(){
				return this->enabled;
			}
			void WorldSpellHitCallbackBehaviour::setEnabled(bool value)
			{
				this->enabled = value;
			}
			WorldSpellHitCallbackBehaviour::WorldSpellHitCallbackBehaviour(WorldSpell* owner)
			{
				this->owner = owner;
				this->t = owner->transform;
			}
			void WorldSpellHitCallbackBehaviour::Init()
			{
				if (this->owner->SpellProjectileAttribute->Collision) {
					this->setEnabled(true);
					return;
				}
				this->setEnabled(false);
			}
			void WorldSpellHitCallbackBehaviour::OnTriggerEnter(Collider* otherCollider)
			{
				if (!this->getEnabled()) {
					return;
				}
				if (otherCollider->transform == null) {
					return;
				}
				if ((otherCollider->transform == this->t) || (otherCollider->transform == this->owner->Caster->transform)) {
					return;
				}
				if (this->didCollide) {
					return;
				}
				this->didCollide = true;
				GameObject* gameObject = otherCollider->gameObject;
				if ((this->owner->Target != null) && (*gameObject != this->owner->Target->gameObject)) {
					this->didCollide = false;
					return;
				}
				(SpellScript*)(this->owner->Spell->SpellScript)->SpellHit(this->owner->Caster, gameObject->GetComponent<WorldEntity>(), this->owner, this->owner->Spell, this->owner->SpellScale);
			}

		}
	}
}
