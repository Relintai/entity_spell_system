#ifndef STAT_H
#define STAT_H

#include "core/ustring.h"
#include "core/reference.h"
#include "core/vector.h"
#include "scene/resources/curve.h"

#include "stat_modifier.h"

class Stat : public Reference {
	GDCLASS(Stat, Reference);

public:
	static const String STAT_BINDING_STRING;
	static const String MAIN_STAT_BINDING_STRING;
	static const String MODIFIER_APPLY_TYPE_BINDING_STRING;

	enum StatId {
		STAT_ID_HEALTH = 0,
		STAT_ID_SPEED = 1,
		STAT_ID_MANA = 2,
		STAT_ID_GLOBAL_COOLDOWN = 3,
		STAT_ID_HASTE = 4,

		STAT_ID_AGILITY = 5,
		STAT_ID_STRENGTH = 6,
		STAT_ID_STAMINA = 7,
		STAT_ID_INTELLECT = 8,
		STAT_ID_LUCK = 9, //+crit, + loot

		STAT_ID_HASTE_RATING = 10,
		STAT_ID_RESLILIENCE = 11,
		STAT_ID_ARMOR = 12,

		STAT_ID_ATTACK_POWER = 13,
		STAT_ID_SPELL_POWER = 14,

		STAT_ID_MELEE_CRIT = 15,
		STAT_ID_MELEE_CRIT_BONUS = 16,
		STAT_ID_SPELL_CRIT = 17,
		STAT_ID_SPELL_CRIT_BONUS = 18,
		STAT_ID_BLOCK = 19,
		STAT_ID_PARRY = 20,
		STAT_ID_DAMAGE_REDUCTION = 21,
		STAT_ID_MELEE_DAMAGE_REDUCTION = 22,
		STAT_ID_SPELL_DAMAGE_REDUCTION = 23,
		STAT_ID_DAMAGE_TAKEN = 24,
		STAT_ID_HEAL_TAKEN = 25,
		STAT_ID_MELEE_DAMAGE = 26,
		STAT_ID_SPELL_DAMAGE = 27,

		STAT_ID_HOLY_RESIST = 28,
		STAT_ID_SHADOW_RESIST = 29,
		STAT_ID_NATURE_RESIST = 30,
		STAT_ID_FIRE_RESIST = 31,
		STAT_ID_FROST_RESIST = 32,
		STAT_ID_LIGHTNING_RESIST = 33,
		STAT_ID_CHAOS_RESIST = 34,
		STAT_ID_SILENCE_RESIST = 35,
		STAT_ID_FEAR_RESIST = 36,
		STAT_ID_STUN_RESIST = 37,

		STAT_ID_ENERGY = 38,
		STAT_ID_RAGE = 39,

		STAT_ID_XP_RATE = 40,

		STAT_ID_TOTAL_STATS = 41,
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
		MAIN_STAT_LUCK = 4,
	};

	enum MainStatIds {
		MAIN_STAT_ID_AGILITY = STAT_ID_AGILITY,
		MAIN_STAT_ID_STRENGTH = STAT_ID_STRENGTH,
		MAIN_STAT_ID_STAMINA = STAT_ID_STAMINA,
		MAIN_STAT_ID_INTELLECT = STAT_ID_INTELLECT,
		MAIN_STAT_ID_LUCK = STAT_ID_LUCK,

		MAIN_STAT_ID_COUNT = 5,
		MAIN_STAT_ID_MIN = MAIN_STAT_ID_AGILITY,
		MAIN_STAT_ID_MAX = MAIN_STAT_ID_LUCK,
	};

	static String stat_id_name(int stat_id);

public:
	Stat::StatId get_id();
	void set_id(Stat::StatId id);

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
	void remove_modifier(int id);
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
	Stat(Stat::StatId id);
	Stat(Stat::StatId id, StatModifierApplyType modifier_apply_type);
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
};

VARIANT_ENUM_CAST(Stat::StatId);
VARIANT_ENUM_CAST(Stat::MainStatIds);
VARIANT_ENUM_CAST(Stat::StatModifierApplyType);

#endif
