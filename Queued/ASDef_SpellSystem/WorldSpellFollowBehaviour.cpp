#include "WorldSpellFollowBehaviour.h"
namespace BS {
	namespace SpellsNS {
		namespace WorldSpells {
			bool WorldSpellFollowBehaviour::getEnabled(){
				return this->enabled;
			}
			void WorldSpellFollowBehaviour::setEnabled(bool value)
			{
				this->enabled = value;
			}
			WorldSpellFollowBehaviour::WorldSpellFollowBehaviour(WorldSpell* owner)
			{
				this->owner = owner;
			}
			void WorldSpellFollowBehaviour::Init()
			{
				if (this->owner->SpellProjectileAttribute->Type == SpellProjectileType::Follow) {
					this->sattrib = this->owner->SpellProjectileAttribute;
					if (this->owner->Target != null) {
						this->target = this->owner->Target;
					}
					else {
						WorldEntity* component = this->owner->Caster->GetComponent<WorldEntity>();
						this->target = component->TargetComponent->STarget;
						this->owner->Target = this->target;
					}
					this->ctransform = this->owner->transform;
					this->setEnabled(true);
					return;
				}
				this->setEnabled(false);
			}
			void WorldSpellFollowBehaviour::Update()
			{
				if (!this->getEnabled()) {
					return;
				}
				if ((this->target == null) || (this->target->transform == null)) {
					this->owner->Destroy();
					return;
				}
				Vector3* arg_B8_0 = new Vector3(this->target->transform->position->x, this->target->transform->position->y + (float)1, this->target->transform->position->z);
				Vector3* b = new Vector3(this->ctransform->position->x, this->ctransform->position->y, this->ctransform->position->z);
				Vector3* vector = *arg_B8_0 - *b;
				vector->Normalize();
				Vector3* forward = vector;
				this->ctransform->localRotation = Quaternion::LookRotation(forward);
				vector = (*vector * this->sattrib->Speed) * Time::deltaTime;
				*vector += *b;
				this->ctransform->position = vector;
			}

		}
	}
}
