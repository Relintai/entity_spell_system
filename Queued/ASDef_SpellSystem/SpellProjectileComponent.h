#pragma once
#include <System/System.h>
#include "FakeNetworkBehaviour.h"
#include "WorldEntity.h"
#include "Spell.h"
#include "Vector3.h"
#include "Rigidbody2D.h"
#include "UnityEngine.h"
#include "Time.h"
#include "Quaternion.h"
#include "Collider2D.h"
#include "SpellScript.h"

using namespace BS::Player;
using namespace UnityEngine;
using namespace System;
//Forward Declaration
class SpellScript;

class SpellProjectileComponent : public virtual FakeNetworkBehaviour, public virtual Object{
	private:
		WorldEntity* caster;
	private:
		Spell* spell;
	private:
		WorldEntity* target;
	private:
		float speed;
	private:
		float time;
	private:
		bool didCollide;
	public:
		Vector3* startPosition;
	private:
		float spellScale;
	private:
		Rigidbody2D* rb;
	private:
		float elapsedTIme;
	public:
		Vector3* tmp;
	public:
		Vector3* tmp2;
	public:
	virtual void Start();
	private:
		void Update();
	private:
		void OnTriggerEnter2D(Collider2D* collision);
	public:
		void SetFollow(WorldEntity* caster, Spell* spell, WorldEntity* target, float speed, float spellScale, float time);
};
