#ifndef DAMAGE_PIPELINE_DATA_H
#define DAMAGE_PIPELINE_DATA_H

#include "../spell_enums.h"
#include "core/reference.h"
#include "scene/main/node.h"

class Entity;
class Spell;
class Aura;

class SpellDamageInfo : public Reference {
	GDCLASS(SpellDamageInfo, Reference);

public:
	enum DamageSource {
		DAMAGE_SOURCE_UNKNOWN,
		DAMAGE_SOURCE_SPELL,
		DAMAGE_SOURCE_AURA,
	};

private:
	int _damage;
	int _original_damage;
	bool _crit;
	SpellEnums::SpellType _spell_type;
	Entity *_dealer;
	Entity *_receiver;
	DamageSource _damage_source_type;
	Ref<Reference> _damage_source;
	int _damage_source_id;

protected:
	static void _bind_methods();

public:
	int get_damage();
	void set_damage(int value);

	bool get_crit();
	void set_crit(bool value);

	SpellEnums::SpellType get_spell_type();
	void set_spell_type(SpellEnums::SpellType value);

	Entity *get_dealer();
	void set_dealer(Node *value);

	Entity *get_receiver();
	void set_receiver(Node *value);

	Ref<Reference> get_damage_source();
	void set_damage_source(Ref<Reference> value);

	Ref<Spell> get_spell_damage_source();
	void set_spell_damage_source(Ref<Spell> value);

	Ref<Aura> get_aura_damage_source();
	void set_aura_damage_source(Ref<Aura> value);

	int get_damage_source_id();
	void set_damage_source_id(int value);

	DamageSource get_damage_source_type();
	void set_damage_source_type(DamageSource value);

	void reset();

	SpellDamageInfo();
	~SpellDamageInfo();
};

VARIANT_ENUM_CAST(SpellDamageInfo::DamageSource);

#endif
