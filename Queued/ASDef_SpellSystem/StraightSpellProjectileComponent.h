#pragma once
#include <System/System.h>
#include "FakeNetworkBehaviour.h"
#include "WorldEntity.h"
#include "Spell.h"
#include "Vector3.h"
#include "Rigidbody.h"
#include "Time.h"
#include "UnityEngine.h"
#include "Collider.h"
#include "SpellScript.h"

using namespace BS::Player;
using namespace UnityEngine;
using namespace System;
//Forward Declaration
class SpellScript;

class StraightSpellProjectileComponent : public virtual FakeNetworkBehaviour, public virtual Object{
	private:
		WorldEntity* caster;
	private:
		Spell* spell;
	private:
		Vector3* direction;
	private:
		float range;
	private:
		float speed;
	//Attribute: SerializeField*
	private:
		float time;
	public:
		Vector3* startPosition;
	private:
		float spellScale;
	private:
		bool flying;
	private:
		Rigidbody* rb;
	private:
		float elapsedTIme;
	public:
		Vector3* tmp;
	public:
	virtual void Start();
	private:
		void Update();
	private:
		void OnTriggerEnter(Collider* collision);
	public:
		void Launch(WorldEntity* caster, Spell* spell, Vector3* dir, float speed, float time, float range, float spellScale);
};
