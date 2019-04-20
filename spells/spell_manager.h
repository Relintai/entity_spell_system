#ifndef SPELL_MANAGER_H
#define SPELL_MANAGER_H

#include "scene/main/node.h"
#include "core/ustring.h"
#include "core/vector.h"
#include "../pipelines/spell_damage_info.h"
#include "../entities/entity.h"
#include "../data/spell.h"

//Deprecated, delete later

class SpellManager : public Node {
	GDCLASS(SpellManager, Node);

public:
	static SpellManager *get_instance();

	void CastSpell(Entity *caster, int spellId, float scale);
	void CastingFinished(Entity *caster, int spellId, float scale);
	void UpdateAuras(Entity *auraComponent);
	void OnHit(Entity *auraComponent, Entity *caster, Entity *target, Spell *spell, int damage);
	void POnBeforeDamage(Entity *ac, SpellDamageInfo *data);
	void OnDamageReceive(Entity *ac, Entity *caster, Entity *target, Spell *spell, int damage);
	void RemoveAurasWithGroup(Entity *ac, int auraGroup);
	void CRefreshAura(Entity *ac, int auraId, float time);
	void CRefreshCasterAura(Entity *ac, int auraId, Entity *caster, float time);
	void CAuraAdded(Entity *ac, int id, float remaining, Entity *caster, int casterGUID);
	void CAuraRemoved(Entity *ac, int id);
	void COnCastFailed(Entity *caster, int spellId);
	void SetupOnPlayerMoves(Entity *bopmccc, Vector<int> *sspells);
	void COnCastStarted(Entity *caster, int spellId);
	void COnCastStateChanged(Entity *caster, int spellId);
	void COnCastFinished(Entity *caster, int spellId);
	void COnSpellCastSuccess(Entity *caster, int spellId);

	String RequestName(int spellId);
	String RequestDescription(int spellId, int level);

	SpellManager();
	~SpellManager();

protected:
	static void _bind_methods();

private:
	static SpellManager *_instance;
};

#endif
