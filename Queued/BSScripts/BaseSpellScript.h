#pragma once
#include <System/System.h>
#include "Spell.h"
#include <System/Delegate.h>
#include "Entity.h"
#include "BaseWorldSpell.h"

using namespace BS::Player;
using namespace System;
class BaseSpellScript : public virtual Object
{
	public:
		DELEGATE(void, Spell*) CreateSpellScriptForAction;
	public:
	static BaseSpellScript::CreateSpellScriptForAction* CreateSpellScriptFor;
	public:
		int spellId;
	public:
		Spell* spell;
	public:
		BaseSpellScript(Spell* spell);
	public:
	virtual void StartCasting(Entity* caster, float spellScale);
	public:
	virtual void CastingFinished(Entity* caster, float spellScale);
	public:
	virtual void CastingFailed(Entity* caster);
	public:
	virtual void SpellHit(Entity* caster, Entity* target, BaseWorldSpell* worldSpell, Spell* spell, float spellScale);
	public:
	virtual void OnPlayerMove(Entity* caster);
	public:
	virtual void COnSpellCastStarted(Entity* player);
	public:
	virtual void COnSpellCastSuccess(Entity* player);
	public:
	virtual void COnSpellCastFailed(Entity* player);
	public:
	virtual void COnSpellCastEnded(Entity* player);
	public:
	virtual void OnCastStateChanged(Entity* caster);
};
