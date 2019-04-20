#include "WorldSpell.h"
namespace BS {
	namespace SpellsNS {
		namespace WorldSpells {
			SpellProjectileData* WorldSpell::getSpellProjectileAttribute(){
				return this->spellProjectileAttribute;
			}
			void WorldSpell::setSpellProjectileAttribute(SpellProjectileData* value)
			{
				this->spellProjectileAttribute = value;
			}
			WorldEntity* WorldSpell::getCaster()
			{
				return this->caster;
			}
			WorldEntity* WorldSpell::getTarget()
			{
				return this->target;
			}
			void WorldSpell::setTarget(WorldEntity* value)
			{
				this->target = value;
			}
			Spell* WorldSpell::getSpell()
			{
				return this->spell;
			}
			float WorldSpell::getSpellScale()
			{
				return this->spellScale;
			}
			Vector3* WorldSpell::getDir()
			{
				return this->dir;
			}
			Object* WorldSpell::getData()
			{
				return Data_var;
			}
			void WorldSpell::setData(Object* value)
			{
				Data_var = value;
			}
			void WorldSpell::Awake()
			{
				this->WorldSpellTimeDestroyBehaviour = new WorldSpellTimeDestroyBehaviour(this);
				this->WorldSpellStraightBehaiour = new WorldSpellStraightBehaiour(this);
				this->WorldSpellHitCallbackBehaviour = new WorldSpellHitCallbackBehaviour(this);
				this->WorldSpellFollowBehaviour = new WorldSpellFollowBehaviour(this);
			}
			void WorldSpell::Init()
			{
				this->WorldSpellTimeDestroyBehaviour->Init();
				this->WorldSpellFollowBehaviour->Init();
				this->WorldSpellStraightBehaiour->Init();
				this->WorldSpellHitCallbackBehaviour->Init();
			}
			void WorldSpell::Update()
			{
				if (BSState::Instance->IsServer) {
					this->WorldSpellTimeDestroyBehaviour->Update();
					this->WorldSpellFollowBehaviour->Update();
					this->WorldSpellStraightBehaiour->Update();
				}
			}
			void WorldSpell::OnTriggerEnter(Collider* otherCollider)
			{
				this->WorldSpellHitCallbackBehaviour->OnTriggerEnter(otherCollider);
			}
			void WorldSpell::Destroy()
			{
				UnityEngine::Object::Destroy(BaseWorldSpell::gameObject);
			}
			void WorldSpell::SetData(SpellProjectileData* spellProjectileAttribute, WorldEntity* caster, Spell* spell, float spellScale, Vector3* dir, WorldEntity* target)
			{
				this->spellProjectileAttribute = spellProjectileAttribute;
				this->caster = caster;
				this->target = target;
				this->spell = spell;
				this->spellScale = spellScale;
				this->dir = dir;
				this->Init();
			}
			void WorldSpell::SetData(WorldSpell* other)
			{
				this->spellProjectileAttribute = other->spellProjectileAttribute;
				this->caster = other->caster;
				this->target = other->target;
				this->spell = other->spell;
				this->spellScale = other->spellScale;
				this->dir = other->dir;
				this->Init();
			}
			WorldSpell::WorldSpell()
			{
				Data_var = (Object*)(0);
			}

		}
	}
}
