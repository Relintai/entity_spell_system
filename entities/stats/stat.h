#ifndef STAT_H
#define STAT_H

#include "core/reference.h"
#include "core/ustring.h"
#include "core/vector.h"
#include "scene/resources/curve.h"

#include "stat_modifier.h"

class StatDataEntry;
class Entity;

class Stat : public Reference {
	GDCLASS(Stat, Reference);

public:
	static const String STAT_BINDING_STRING;
	static const String MAIN_STAT_BINDING_STRING;
	static const String MODIFIER_APPLY_TYPE_BINDING_STRING;

	enum StatId {
		STAT_ID_HEALTH = 0,
		STAT_ID_SPEED,
		STAT_ID_MANA,
		STAT_ID_GLOBAL_COOLDOWN,
		STAT_ID_HASTE,

		STAT_ID_AGILITY,
		STAT_ID_STRENGTH,
		STAT_ID_STAMINA,
		STAT_ID_INTELLECT,
		STAT_ID_SPIRIT,

		STAT_ID_HASTE_RATING,
		STAT_ID_RESLILIENCE,
		STAT_ID_ARMOR,

		STAT_ID_ATTACK_POWER,
		STAT_ID_SPELL_POWER,

		STAT_ID_MELEE_CRIT,
		STAT_ID_MELEE_CRIT_BONUS,
		STAT_ID_SPELL_CRIT,
		STAT_ID_SPELL_CRIT_BONUS,
		STAT_ID_BLOCK,
		STAT_ID_PARRY,
		STAT_ID_DAMAGE_REDUCTION,
		STAT_ID_MELEE_DAMAGE_REDUCTION,
		STAT_ID_SPELL_DAMAGE_REDUCTION,
		STAT_ID_DAMAGE_TAKEN,
		STAT_ID_HEAL_TAKEN,
		STAT_ID_MELEE_DAMAGE,
		STAT_ID_SPELL_DAMAGE,

		STAT_ID_HOLY_RESIST,
		STAT_ID_SHADOW_RESIST,
		STAT_ID_NATURE_RESIST,
		STAT_ID_FIRE_RESIST,
		STAT_ID_FROST_RESIST,
		STAT_ID_LIGHTNING_RESIST,
		STAT_ID_CHAOS_RESIST,
		STAT_ID_SILENCE_RESIST,
		STAT_ID_FEAR_RESIST,
		STAT_ID_STUN_RESIST,

		STAT_ID_ENERGY,
		STAT_ID_RAGE,

		STAT_ID_XP_RATE,

		STAT_DISPELL_RESIST,

		STAT_ID_TOTAL_STATS,
		STAT_ID_NONE = STAT_ID_TOTAL_STATS,
	};

	enum StatModifierApplyType {
		MODIFIER_APPLY_TYPE_STANDARD,
		MODIFIER_APPLY_TYPE_ONLY_MIN_MODIFIER,
		MODIFIER_APPLY_TYPE_ONLY_MAX_MODIFIER,
	};

	enum MainStats {
		MAIN_STAT_AGILITY = 0,
		MAIN_STAT_STRENGTH = 1,
		MAIN_STAT_STAMINA = 2,
		MAIN_STAT_INTELLECT = 3,
		MAIN_STAT_SPIRIT = 4,

		MAIN_STAT_ID_START = STAT_ID_AGILITY,
		MAIN_STAT_ID_COUNT = 5,
	};

	static String stat_id_name(int stat_id);

public:
	Stat::StatId get_id();
	void set_id(Stat::StatId id);

	Ref<StatDataEntry> get_stat_data_entry();
	void set_stat_data_entry(Ref<StatDataEntry> entry);

	Entity *get_owner();
	void set_owner(Entity *value);
	void set_owner_bind(Node *value);

	StatModifierApplyType get_stat_modifier_type();
	void set_stat_modifier_type(StatModifierApplyType value);

	bool get_public();
	void set_public(bool value);

	bool get_locked();
	void set_locked(bool value);

	bool get_dirty();
	void set_dirty(bool value);

	bool get_dirty_mods();
	void set_dirty_mods(bool value);

	float get_base();
	float get_bonus();
	float get_percent();

	float gets_current();
	void sets_current(float value);
	float gets_max();
	void sets_max(float value);

	float getc_current();
	void setc_current(float value);
	float getc_max();
	void setc_max(float value);

	void setc_values(int ccurrent, int cmax);

	Vector<Ref<StatModifier> > *get_modifiers();
	Ref<StatModifier> add_modifier(int id, float base_mod, float bonus_mod, float percent_mod);
	Ref<StatModifier> get_or_add_modifier(int id);
	void remove_modifier(int id);
	void remove_modifier_index(int index);
	int get_modifier_count();
	void clear_modifiers();
	Ref<StatModifier> get_modifier(int index);

	void apply_modifiers();

	void reset_values();
	void refresh_currmax();
	bool iss_current_zero();
	bool isc_current_zero();

	void set_to_max();

	void modifier_changed(Ref<StatModifier> modifier);

	Dictionary to_dict();
	void from_dict(const Dictionary &dict);

	Dictionary _to_dict();
	void _from_dict(const Dictionary &dict);

	Stat();
	Stat(Stat::StatId id, Entity* owner);
	Stat(Stat::StatId id, StatModifierApplyType modifier_apply_type, Entity *owner);
	~Stat();

protected:
	static void _bind_methods();

private:
	Stat::StatId _id;

	StatModifierApplyType _modifier_apply_type;

	Vector<Ref<StatModifier> > _modifiers;

	bool _public;
	bool _locked;
	bool _dirty;
	bool _dirty_mods;

	float _base;
	float _bonus;
	float _percent;

	float _s_current;
	float _s_max;

	float _c_current;
	float _c_max;

	Entity *_owner;
	Ref<StatDataEntry> _stat_data_entry;
};

VARIANT_ENUM_CAST(Stat::StatId);
VARIANT_ENUM_CAST(Stat::MainStats);
VARIANT_ENUM_CAST(Stat::StatModifierApplyType);

#endif
