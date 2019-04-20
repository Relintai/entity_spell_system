#include "WorldSpellStraightBehaiour.h"
namespace BS {
	namespace SpellsNS {
		namespace WorldSpells {
			bool WorldSpellStraightBehaiour::getEnabled(){
				return this->enabled;
			}
			void WorldSpellStraightBehaiour::setEnabled(bool value)
			{
				this->enabled = value;
			}
			WorldSpellStraightBehaiour::WorldSpellStraightBehaiour(WorldSpell* owner)
			{
				this->owner = owner;
				this->rb = owner->GetComponent<Rigidbody>();
			}
			void WorldSpellStraightBehaiour::Init()
			{
				if (this->owner->SpellProjectileAttribute->Type != SpellProjectileType::Straight) {
					this->setEnabled(false);
					return;
				}
				this->sattrib = this->owner->SpellProjectileAttribute;
				if (((this->owner == null) || (this->owner->Caster == null)) || (this->owner->Caster->transform == null)) {
					return;
				}
				this->startPosition->Set(this->owner->Caster->transform->localPosition->x, this->owner->Caster->transform->localPosition->y, this->owner->Caster->transform->localPosition->z);
				this->direction->Set(this->owner->Dir->x, this->owner->Dir->y, this->owner->Dir->z);
				this->direction->Normalize();
				this->t = this->owner->transform;
				this->setEnabled(true);
			}
			void WorldSpellStraightBehaiour::Update()
			{
				if (!this->getEnabled()) {
					return;
				}
				Vector3* a = this->direction;
				*a *= this->sattrib->Speed * Time::deltaTime;
				this->rb->MovePosition(*a + *(this->t->position));
				*a += this->owner->transform->localPosition;
				if (*a - *(this->startPosition)->magnitude > this->sattrib->Range) {
					this->owner->Destroy();
				}
			}

		}
	}
}
