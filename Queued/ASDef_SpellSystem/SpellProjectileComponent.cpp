#include "SpellProjectileComponent.h"
void SpellProjectileComponent::Start(){
	if (!this->isServer){
		return;
	}
	this->startPosition = FakeNetworkBehaviour::transform->position;
	this->rb = FakeNetworkBehaviour::GetComponent<Rigidbody2D>();
}
void SpellProjectileComponent::Update()
{
	if ((this->target == null) || (this->target->transform == null)) {
		if (this->isServer) {
			UnityEngine::Object::Destroy(FakeNetworkBehaviour::transform->gameObject);
		}
		return;
	}
	if (this->isServer && (this->time > (float)0.01)) {
		this->elapsedTIme += Time::deltaTime;
		if (this->elapsedTIme > this->time) {
			UnityEngine::Object::Destroy(FakeNetworkBehaviour::transform->gameObject);
			return;
		}
	}
	this->tmp->Set(this->target->transform->position->x, this->target->transform->position->y + (float)1, this->target->transform->position->z - (float)0.1);
	this->tmp2->Set(FakeNetworkBehaviour::transform->position->x, FakeNetworkBehaviour::transform->position->y, FakeNetworkBehaviour::transform->position->z);
	this->tmp -= this->tmp2;
	this->tmp->Normalize();
	this->tmp->x = this->tmp->x * (this->speed * Time::deltaTime);
	this->tmp->y = this->tmp->y * (this->speed * Time::deltaTime);
	this->tmp->z = this->tmp->z * (this->speed * Time::deltaTime);
	this->tmp->x = this->tmp->x + FakeNetworkBehaviour::transform->position->x;
	this->tmp->y = this->tmp->y + FakeNetworkBehaviour::transform->position->y;
	this->tmp->z = this->tmp->z + FakeNetworkBehaviour::transform->position->z;
	Vector3* forward = *(this->target->transform->position) - *(FakeNetworkBehaviour::transform->position);
	forward->Normalize();
	FakeNetworkBehaviour::transform->localRotation = Quaternion::LookRotation(forward);
	this->rb->MovePosition(this->tmp);
}
void SpellProjectileComponent::OnTriggerEnter2D(Collider2D* collision)
{
	if (!this->isServer) {
		return;
	}
	if ((collision == null) || (collision->gameObject == null)) {
		UnityEngine::Object::Destroy(FakeNetworkBehaviour::transform->gameObject);
		return;
	}
	if (collision->transform == FakeNetworkBehaviour::transform) {
		return;
	}
	if (this->didCollide) {
		return;
	}
	this->didCollide = true;
	WorldEntity* component = collision->gameObject->GetComponent<WorldEntity>();
	if (*component != this->target) {
		this->didCollide = false;
		return;
	}
	(SpellScript*)(this->spell->SpellScript)->SpellHit(this->caster, component, null, this->spell, this->spellScale);
}
void SpellProjectileComponent::SetFollow(WorldEntity* caster, Spell* spell, WorldEntity* target, float speed, float spellScale, float time)
{
	this->caster = caster;
	this->spell = spell;
	this->startPosition->Set(FakeNetworkBehaviour::transform->position->x, FakeNetworkBehaviour::transform->position->y, FakeNetworkBehaviour::transform->position->z);
	this->target = target;
	this->speed = speed;
	this->time = time;
	this->spellScale = spellScale;
}

