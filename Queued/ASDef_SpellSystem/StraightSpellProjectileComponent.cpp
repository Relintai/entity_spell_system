#include "StraightSpellProjectileComponent.h"
void StraightSpellProjectileComponent::Start(){
	if (!this->isServer){
		return;
	}
	this->rb = FakeNetworkBehaviour::GetComponent<Rigidbody>();
}
void StraightSpellProjectileComponent::Update()
{
	if (this->time > (float)0.01) {
		this->elapsedTIme += Time::deltaTime;
		if (this->elapsedTIme > this->time) {
			UnityEngine::Object::Destroy(FakeNetworkBehaviour::transform->gameObject);
			return;
		}
	}
	if (!this->flying) {
		return;
	}
	this->tmp->Set(this->direction->x, this->direction->y, this->direction->z);
	this->tmp *= this->speed * Time::deltaTime;
	this->tmp += FakeNetworkBehaviour::transform->localPosition;
	this->rb->MovePosition(this->tmp);
	this->tmp -= this->startPosition;
	if (this->tmp->magnitude > this->range) {
		UnityEngine::Object::Destroy(FakeNetworkBehaviour::gameObject);
	}
}
void StraightSpellProjectileComponent::OnTriggerEnter(Collider* collision)
{
	if (!this->isServer) {
		return;
	}
	if (collision->transform == null) {
		return;
	}
	if ((collision->transform == FakeNetworkBehaviour::transform) || (collision->transform == this->caster->transform)) {
		return;
	}
	WorldEntity* component = collision->gameObject->GetComponent<WorldEntity>();
	(SpellScript*)(this->spell->SpellScript)->SpellHit(this->caster, component, null, this->spell, this->spellScale);
}
void StraightSpellProjectileComponent::Launch(WorldEntity* caster, Spell* spell, Vector3* dir, float speed, float time, float range, float spellScale)
{
	this->caster = caster;
	this->spell = spell;
	this->startPosition->Set(FakeNetworkBehaviour::transform->localPosition->x, FakeNetworkBehaviour::transform->localPosition->y, FakeNetworkBehaviour::transform->localPosition->z);
	this->direction->Set(dir->x, (float)0, dir->z);
	this->direction->Normalize();
	this->range = range;
	this->speed = speed;
	this->time = time;
	this->flying = true;
	this->spellScale = spellScale;
}

