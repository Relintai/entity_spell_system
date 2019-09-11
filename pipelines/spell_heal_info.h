#ifndef SPELL_HEAL_INFO_H
#define SPELL_HEAL_INFO_H

#include "../spell_enums.h"
#include "core/reference.h"
#include "scene/main/node.h"

class Entity;
class Spell;
class Aura;

class SpellHealInfo : public Reference {
	GDCLASS(SpellHealInfo, Reference);

public:
	enum HealSource {
		HEAL_SOURCE_UNKNOWN,
		HEAL_SOURCE_SPELL,
		HEAL_SOURCE_AURA,
	};

protected:
	static void _bind_methods();

public:
    bool get_immune();
	void set_immune(bool value);
    
	int get_heal();
	void set_heal(int value);

	bool get_crit();
	void set_crit(bool value);

	int get_amount_absorbed();
	void set_amount_absorbed(int value);

	SpellEnums::SpellType get_spell_type();
	void set_spell_type(SpellEnums::SpellType value);

	Entity *get_dealer();
	void set_dealer(Node *value);

	Entity *get_receiver();
	void set_receiver(Node *value);

	Ref<Reference> get_heal_source();
	void set_heal_source(Ref<Reference> value);

	Ref<Spell> get_spell_heal_source();
	void set_spell_heal_source(Ref<Spell> value);

	Ref<Aura> get_aura_heal_source();
	void set_aura_heal_source(Ref<Aura> value);

	int get_heal_source_id();
	void set_heal_source_id(int value);

	HealSource get_heal_source_type();
	void set_heal_source_type(HealSource value);

	void reset();

	SpellHealInfo();
	~SpellHealInfo();

private:
	int _heal;
	int _original_heal;
	int _amount_absorbed;
	bool _crit;
	SpellEnums::SpellType _spell_type;
	Entity *_dealer;
	Entity *_receiver;
	HealSource _heal_source_type;
	Ref<Reference> _heal_source;
	int _heal_source_id;
};

VARIANT_ENUM_CAST(SpellHealInfo::HealSource);

#endif
