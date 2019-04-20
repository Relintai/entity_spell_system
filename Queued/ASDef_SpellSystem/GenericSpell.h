#pragma once
#include <System/System.h>
#include "SpellScript.h"
#include "Spell.h"
#include "Mathf.h"
#include "WorldEntity.h"
#include "WorldSpell.h"
#include "Entity.h"
#include "Stats.h"
#include "SpellStatValueModAttributeHelper.h"
#include "ValueStat.h"

using namespace UnityEngine;
using namespace BS::Player;
using namespace BS::SpellsNS::WorldSpells;
using namespace System;
//Forward Declaration
class SpellScript;

class GenericSpell : public virtual SpellScript, public virtual Object{
	//Attribute: SerializeField*
	private:
		bool hasCastTime;
	//Attribute: SerializeField*
	private:
		bool damage;
	//Attribute: SerializeField*
	private:
		bool hasCooldown;
	public:
		GenericSpell(Spell* spell);
	public:
	virtual void StartCasting(WorldEntity* caster, float spellScale);
	public:
	virtual void CastingFinished(WorldEntity* caster, float spellScale);
	public:
	virtual void SpellHit(WorldEntity* caster, WorldEntity* target, WorldSpell* worldSpell, Spell* spellGO, float spellScale);
	public:
	virtual void OnPlayerMove(Entity* caster);
	private:
		void HandleSpellEffect(WorldEntity* caster, WorldEntity* target, float spellScale);
	private:
		void HandleSpellStatValueMod(WorldEntity* caster);
	public:
	virtual void COnSpellCastSuccess(WorldEntity* player);
	public:
	virtual void COnSpellCastStarted(WorldEntity* player);
	public:
	virtual void COnSpellCastEnded(WorldEntity* player);
};
