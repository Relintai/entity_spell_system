#ifndef STAT_H
#define STAT_H

#include "core/ustring.h"
#include "core/reference.h"
#include "core/vector.h"
#include "scene/resources/curve.h"

class StatModifier : public Reference {
	GDCLASS(StatModifier, Reference);

public:
	StatModifier() {
	}

	StatModifier(int i, float maxM, float percentM) {
		_id = i;
		_max_mod = maxM;
		_percent_mod = percentM;
	}

	int get_id() { return _id; }
	void set_id(int value) { _id = value; }
	float get_bonus_mod() { return _max_mod; }
	void set_bonus_mod(float value) { _max_mod = value; }
	float get_percent_mod() { return _percent_mod; }
	void set_percent_mod(float value) { _percent_mod = value; }

protected:
	static void _bind_methods() {
		ClassDB::bind_method(D_METHOD("get_id"), &StatModifier::get_id);
		ClassDB::bind_method(D_METHOD("set_id", "value"), &StatModifier::set_id);
		ADD_PROPERTY(PropertyInfo(Variant::REAL, "id"), "set_id", "get_id");

		ClassDB::bind_method(D_METHOD("get_bonus_mod"), &StatModifier::get_bonus_mod);
		ClassDB::bind_method(D_METHOD("set_bonus_mod", "value"), &StatModifier::set_bonus_mod);
		ADD_PROPERTY(PropertyInfo(Variant::REAL, "bonus_mod"), "set_bonus_mod", "get_bonus_mod");

		ClassDB::bind_method(D_METHOD("get_percent_mod"), &StatModifier::get_percent_mod);
		ClassDB::bind_method(D_METHOD("set_percent_mod", "value"), &StatModifier::set_percent_mod);
		ADD_PROPERTY(PropertyInfo(Variant::REAL, "percent_mod"), "set_percent_mod", "get_percent_mod");
	}

private:
	int _id;
	float _max_mod;
	float _percent_mod;
};

class Stat : public Reference {
	GDCLASS(Stat, Reference);

public:
	static const String STAT_BINDING_STRING;
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

		STAT_ID_TOTAL_STATS = 37,
		STAT_ID_NONE = STAT_ID_TOTAL_STATS,
	};

	enum StatModifierApplyType {
		MODIFIER_APPLY_TYPE_STANDARD,
		MODIFIER_APPLY_TYPE_ONLY_MIN_MODIFIER,
		MODIFIER_APPLY_TYPE_ONLY_MAX_MODIFIER,
	};

public:
	Stat();
	Stat(Stat::StatId id);
	Stat(Stat::StatId id, StatModifierApplyType modifier_apply_type);
	Stat(Stat::StatId id, StatModifierApplyType modifier_apply_type, float base, float bonus, float percent);
	Stat(Stat::StatId id, StatModifierApplyType modifier_apply_type, float base);
	~Stat();

	Stat::StatId get_id();
	void set_id(Stat::StatId id);

	StatModifierApplyType get_stat_modifier_type();
	void set_stat_modifier_type(StatModifierApplyType value);

	bool get_dirty();
	void set_dirty(bool value);
	bool get_disabled();
	void set_disabled(bool value);

	float get_base();
	void set_base(float value);
	float get_bonus();
	void set_bonus(float value);
	float get_percent();
	void set_percent(float value);

	float gets_current();
	void sets_current(float value);
	float gets_max();
	void sets_max(float value);

	float getc_current();
	void setc_current(float value);
	float getc_max();
	void setc_max(float value);

	void reset_values();
	void recalculate();
	bool iss_current_zero();
	bool isc_current_zero();
	void set(float current, float max, float modCurrent, float modMax, float modPercent);
	void set_from_stat(Ref<Stat> other);

	void set_to_max();
	void set_values(float current, float base, float percent);

	void apply_modifier(Ref<StatModifier> modifier);
	void de_apply_modifier(Ref<StatModifier> modifier);
	void re_apply_modifier_not_negative_stacking_percents();

	Vector<Ref<StatModifier> > *get_modifiers();
	void add_modifier(int id, float maxMod, float percentMod, bool apply = true);
	void remove_modifier(int id, bool apply = true);
	void re_apply_modifiers();
	int get_modifier_count();
	Ref<StatModifier> get_modifier(int index);

	void set_dependency(Ref<Stat> other, Ref<Curve> curve);
	void remove_dependencies();

	void send();

protected:
	static void _bind_methods();

private:
	Stat::StatId _id;

	StatModifierApplyType _modifier_apply_type;

	Vector<Ref<StatModifier> > _modifiers;

	bool _dirty;
	bool _disabled;

	float _base;
	float _bonus;
	float _percent;

	float _s_current;
	float _s_max;

	float _c_current;
	float _c_max;

	Ref<Stat> _dependency;
	Ref<Curve> _dependency_curve;
};

VARIANT_ENUM_CAST(Stat::StatId);
VARIANT_ENUM_CAST(Stat::StatModifierApplyType);

#endif
