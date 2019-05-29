#include "stat.h"

const String Stat::STAT_BINDING_STRING = "Health, Speed, Mana, GCD, Haste, Agility, Strength, Stamina, Intellect, Luck, Haste Rating, Resilience, Armor, Attack Power, Spell Power, Melee Crit, Melee Crit bonus, Spell Crit, Spell Crit Bonus, Block, Parry, Damage Reduction, Melee Damage Reduction, Spell Damage Reduction, Damage Taken, Heal Taken, Melee Damage, Spell Damage, Holy Resist, Shadow Resist, Nature Resist, Fire Resist, Frost Resist, Lightning Resist, Chaos Resist, Silence Resist, Fear Resist, None";

const String Stat::MODIFIER_APPLY_TYPE_BINDING_STRING = "Standard, Only min modifier, Only Max modifier";

Stat::Stat() {
	_id = Stat::STAT_ID_NONE;

	_base = (float)(0);
	_bonus = (float)(0);
	_percent = (float)(0);
	_s_max = (float)(0);
	_s_current = (float)(0);
	_c_max = (float)(0);
	_c_current = (float)(0);

	_disabled = false;
	_modifier_apply_type = MODIFIER_APPLY_TYPE_STANDARD;
}

Stat::Stat(Stat::StatId id) {
	_id = id;

	_base = (float)(0);
	_bonus = (float)(0);
	_percent = (float)(0);
	_s_max = (float)(0);
	_s_current = (float)(0);
	_c_max = (float)(0);
	_c_current = (float)(0);

	_disabled = false;
	_modifier_apply_type = MODIFIER_APPLY_TYPE_STANDARD;
}

Stat::Stat(Stat::StatId id, StatModifierApplyType modifier_apply_type) {
	_id = id;

	_base = (float)(0);
	_bonus = (float)(0);
	_percent = (float)(0);
	_s_max = (float)(0);
	_s_current = (float)(0);
	_c_max = (float)(0);
	_c_current = (float)(0);

	_disabled = false;
	_modifier_apply_type = modifier_apply_type;
	_id = id;
}

//Stat
Stat::Stat(Stat::StatId id, StatModifierApplyType modifier_apply_type, float base, float bonus, float percent) {
	_id = id;

	_base = (float)(0);
	_bonus = (float)(0);
	_percent = (float)(0);
	_s_max = (float)(0);
	_s_current = (float)(0);
	_c_max = (float)(0);
	_c_current = (float)(0);
	_disabled = false;
	_modifier_apply_type = modifier_apply_type;

	_id = id;

	_base = base;
	_bonus = bonus;
	_percent = percent;

	_disabled = false;
}

Stat::Stat(Stat::StatId id, StatModifierApplyType modifier_apply_type, float base) {
	_id = id;

	_base = (float)(0);
	_bonus = (float)(0);
	_percent = (float)(0);
	_s_max = (float)(0);
	_s_current = (float)(0);
	_c_max = (float)(0);
	_c_current = (float)(0);

	_disabled = false;
	_modifier_apply_type = modifier_apply_type;
	_id = id;
	_base = base;
	_percent = 100;
	_bonus = 0;

	_disabled = false;
}

Stat::~Stat() {
	_modifiers.clear();
}

_FORCE_INLINE_ Vector<Ref<StatModifier> > *Stat::get_modifiers() {
	return &_modifiers;
}

int Stat::get_modifier_count() {
	return _modifiers.size();
}

Ref<StatModifier> Stat::get_modifier(int index) {
	return _modifiers.get(index);
}

void Stat::set_dependency(Ref<Stat> other, Ref<Curve> curve) {
	_dependency = other;
	_dependency_curve = curve;
}

void Stat::remove_dependencies() {
	_dependency = Ref<Stat>(NULL);
	_dependency_curve = Ref<Curve>(NULL);
}

Stat::StatId Stat::get_id() {
	return _id;
}

void Stat::set_id(Stat::StatId id) {
	_id = id;
}

Stat::StatModifierApplyType Stat::get_stat_modifier_type() {
	return _modifier_apply_type;
}

void Stat::set_stat_modifier_type(Stat::StatModifierApplyType value) {
	_modifier_apply_type = value;
}

bool Stat::get_dirty() {
	return _dirty;
}

void Stat::set_dirty(bool value) {
	_dirty = value;
}

bool Stat::get_disabled() {
	return _disabled;
}

void Stat::set_disabled(bool value) {
	_disabled = value;

	emit_signal("s_changed", this);
}

void Stat::add_modifier(int id, float _max_mod, float percent_mod, bool apply) {
	Ref<StatModifier> statModifier = Ref<StatModifier>(memnew(StatModifier(id, _max_mod, percent_mod)));

	if (apply) {
		apply_modifier(statModifier);
	}

	_modifiers.push_back(statModifier);
}

void Stat::remove_modifier(int id, bool apply) {
	for (int i = 0; i < _modifiers.size(); i += 1) {
		if (_modifiers.get(i)->get_id() == id) {
			Ref<StatModifier> modifier = _modifiers.get(i);
			_modifiers.remove(i);

			if (apply) {
				de_apply_modifier(modifier);
			}

			return;
		}
	}
}

void Stat::apply_modifier(Ref<StatModifier> modifier) {
	if (_modifier_apply_type == MODIFIER_APPLY_TYPE_STANDARD) {
		_bonus += modifier->get_bonus_mod();
		_percent += modifier->get_percent_mod();
	} else {
		if (modifier->get_percent_mod() >= (float)0) {
			_bonus += modifier->get_bonus_mod();
			_percent += modifier->get_percent_mod();
		} else {
			int num = -1;
			if (get_modifiers()->size() > 0) {
				float percent_mod = get_modifiers()->get(0)->get_percent_mod();
				for (int i = 1; i < get_modifiers()->size(); i += 1) {
					if ((_modifiers.get(i)->get_percent_mod() < (float)0) && (_modifiers.get(i)->get_percent_mod() < percent_mod)) {
						num = i;
						percent_mod = _modifiers.get(i)->get_percent_mod();
					}
				}
			}

			if (num != -1) {
				if (modifier->get_percent_mod() < _modifiers.get(num)->get_percent_mod()) {
					_percent -= _modifiers.get(num)->get_percent_mod();
				}

				_percent += modifier->get_percent_mod();
			} else {

				_percent += modifier->get_percent_mod();
			}
		}
	}
	//	emit_signal("s_changed", this);
}

void Stat::de_apply_modifier(Ref<StatModifier> modifier) {
	if (_modifier_apply_type == MODIFIER_APPLY_TYPE_STANDARD) {
		_bonus -= modifier->get_bonus_mod();
		_percent -= modifier->get_percent_mod();
	} else {
		if (modifier->get_percent_mod() >= (float)0) {
			//_bonus -= modifier->get_bonus_mod();
			_percent -= modifier->get_percent_mod();
		} else {
			int num = -1;

			if (get_modifiers()->size() > 0) {
				float percent_mod = get_modifiers()->get(0)->get_percent_mod();

				for (int i = 1; i < get_modifiers()->size(); i += 1) {
					if ((_modifiers.get(i)->get_percent_mod() < (float)0) && (_modifiers.get(i)->get_percent_mod() < percent_mod)) {
						num = i;
						percent_mod = _modifiers.get(i)->get_percent_mod();
					}
				}
			}

			if (num != -1 && _modifiers[num] == modifier) {
				_percent -= modifier->get_percent_mod();
			}
		}
	}

	if (_modifiers.size() == 0) {
		recalculate();
	}

	//	emit_signal("s_changed", this);
}

void Stat::re_apply_modifiers() {
	reset_values();

	if (_modifier_apply_type == MODIFIER_APPLY_TYPE_STANDARD) {
		for (int i = 0; i < _modifiers.size(); i += 1) {
			Ref<StatModifier> mod = _modifiers.get(i);

			_bonus += mod->get_bonus_mod();
			_percent += mod->get_percent_mod();
		}
	} else {
		re_apply_modifier_not_negative_stacking_percents();
	}

	if (_modifiers.size() == 0) {
		recalculate();
	}

	//	emit_signal("s_changed", this);
}

void Stat::re_apply_modifier_not_negative_stacking_percents() {
	reset_values();

	for (int i = 1; i < get_modifiers()->size(); i += 1) {
		if (_modifiers.get(i)->get_percent_mod() > (float)0) {
			Ref<StatModifier> mod = _modifiers.get(i);

			_bonus += mod->get_bonus_mod();
			_percent += mod->get_percent_mod();
		}
	}

	int num = -1;
	if (get_modifiers()->size() > 0) {
		float percent_mod = get_modifiers()->get(0)->get_percent_mod();

		for (int j = 1; j < get_modifiers()->size(); ++j) {

			if ((_modifiers.get(j)->get_percent_mod() < (float)0) && (_modifiers.get(j)->get_percent_mod() < percent_mod)) {
				num = j;
				percent_mod = _modifiers.get(j)->get_percent_mod();
			}
		}
	}

	if (num != -1) {
		Ref<StatModifier> mod = _modifiers.get(num);

		_bonus += mod->get_bonus_mod();
		_percent += mod->get_percent_mod();
	}

	//	emit_signal("s_changed", this);
}

//Stat

float Stat::gets_current() {
	return _s_current;
}

void Stat::sets_current(float value) {
	_s_current = value;

	emit_signal("s_changed", this);
	send();
}

float Stat::gets_max() {
	return _s_max;
}

void Stat::sets_max(float value) {
	_s_max = value;

	emit_signal("s_changed", this);
	send();
}

float Stat::getc_current() {
	return _c_current;
}

void Stat::setc_current(float value) {
	_c_current = value;

	emit_signal("c_changed", this);
}

float Stat::getc_max() {
	return _c_max;
}

void Stat::setc_max(float value) {
	_s_current = value;

	emit_signal("c_changed", this);
}

float Stat::get_base() {
	return _base;
}

void Stat::set_base(float value) {
	_base = value;
	recalculate();

	emit_signal("s_changed", this);
	send();
}

float Stat::get_bonus() {
	return _bonus;
}

void Stat::set_bonus(float value) {
	_bonus = value;
	recalculate();

	emit_signal("s_changed", this);
	send();
}

float Stat::get_percent() {
	return _percent;
}

void Stat::set_percent(float value) {
	_percent = value;
	recalculate();

	emit_signal("s_changed", this);
	send();
}

void Stat::reset_values() {
	if (_disabled) {
		return;
	}

	_percent = 100;
	_bonus = 0;
	_percent = 0;

	_dirty = true;

	emit_signal("s_changed", this);
	send();
}

void Stat::recalculate() {
	if (_disabled) {
		return;
	}

	_s_max = (_percent / (float)100) * (_base + _bonus);

	if (_s_current > _s_max) {
		_s_current = _s_max;
	}

	_dirty = true;
}

void Stat::send() {
	_c_current = _s_current;
	_c_max = _s_max;

	emit_signal("c_changed", this);
}


bool Stat::iss_current_zero() {
	return (fabs(_s_current) < .000001);
}

bool Stat::isc_current_zero() {
	return (fabs(_c_current) < .000001);
}

void Stat::set_to_max() {
	_s_current = _s_max;

	emit_signal("s_changed", this);
	send();
}

void Stat::set_values(float base, float bonus, float percent) {
	_base = base;
	_bonus = bonus;
	_percent = percent;
	_disabled = false;

	recalculate();

	emit_signal("s_changed", this);
	send();
}

void Stat::set_from_stat(Ref<Stat> other) {
	_s_current = other->_s_current;
	_s_max = other->_s_max;
	_c_current = other->_c_current;
	_c_max = other->_c_max;
	_base = other->_base;
	_bonus = other->_bonus;
	_percent = other->_percent;
	set_dirty(true);

	emit_signal("s_changed", this);
	send();
}

void Stat::set(float current, float max, float base, float bonus, float percent) {
	_s_current = current;
	_s_max = max;
	_c_current = current;
	_c_max = max;
	_base = base;
	_bonus = bonus;
	_percent = percent;
	_dirty = true;
	_disabled = false;

	emit_signal("s_changed", this);
	send();
}

void Stat::_bind_methods() {
	ADD_SIGNAL(MethodInfo("s_changed", PropertyInfo(Variant::OBJECT, "stat", PROPERTY_HINT_RESOURCE_TYPE, "Stat")));
	ADD_SIGNAL(MethodInfo("c_changed", PropertyInfo(Variant::OBJECT, "stat", PROPERTY_HINT_RESOURCE_TYPE, "Stat")));

	ClassDB::bind_method(D_METHOD("get_id"), &Stat::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "id"), &Stat::set_id);

	ClassDB::bind_method(D_METHOD("get_stat_modifier_type"), &Stat::get_stat_modifier_type);
	ClassDB::bind_method(D_METHOD("set_stat_modifier_type", "value"), &Stat::set_stat_modifier_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "stat_type", PROPERTY_HINT_ENUM, "Standard, Min Modifier, Max modifier"), "set_stat_modifier_type", "get_stat_modifier_type");

	ClassDB::bind_method(D_METHOD("get_dirty"), &Stat::get_dirty);
	ClassDB::bind_method(D_METHOD("set_dirty", "value"), &Stat::set_dirty);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_dirty"), "set_dirty", "get_dirty");

	ClassDB::bind_method(D_METHOD("get_disabled"), &Stat::get_disabled);
	ClassDB::bind_method(D_METHOD("set_disabled", "value"), &Stat::set_disabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "dirty"), "set_disabled", "get_disabled");

	ClassDB::bind_method(D_METHOD("gets_current"), &Stat::gets_current);
	ClassDB::bind_method(D_METHOD("sets_current", "value"), &Stat::sets_current);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "scurrent"), "sets_current", "gets_current");

	ClassDB::bind_method(D_METHOD("getc_current"), &Stat::getc_current);
	ClassDB::bind_method(D_METHOD("setc_current", "value"), &Stat::setc_current);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "ccurrent"), "setc_current", "getc_current");

	ClassDB::bind_method(D_METHOD("gets_max"), &Stat::gets_max);
	ClassDB::bind_method(D_METHOD("sets_max"), &Stat::sets_max);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "smax"), "sets_max", "gets_max");

	ClassDB::bind_method(D_METHOD("getc_max"), &Stat::getc_max);
	ClassDB::bind_method(D_METHOD("setc_max"), &Stat::setc_max);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "cmax"), "setc_max", "getc_max");

	ClassDB::bind_method(D_METHOD("get_base"), &Stat::get_base);
	ClassDB::bind_method(D_METHOD("set_base", "value"), &Stat::set_base);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "base"), "set_base", "get_base");

	ClassDB::bind_method(D_METHOD("get_bonus"), &Stat::get_bonus);
	ClassDB::bind_method(D_METHOD("set_bonus", "value"), &Stat::set_bonus);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "bonus"), "set_bonus", "get_bonus");

	ClassDB::bind_method(D_METHOD("get_percent"), &Stat::get_percent);
	ClassDB::bind_method(D_METHOD("set_percent", "value"), &Stat::set_percent);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "percent"), "set_percent", "get_percent");

	ClassDB::bind_method(D_METHOD("reset_values"), &Stat::reset_values);
	ClassDB::bind_method(D_METHOD("recalculate"), &Stat::recalculate);
	ClassDB::bind_method(D_METHOD("iss_current_zero"), &Stat::iss_current_zero);
	ClassDB::bind_method(D_METHOD("isc_current_zero"), &Stat::isc_current_zero);

	ClassDB::bind_method(D_METHOD("set_from_stat", "stat"), &Stat::set_from_stat);

	//ClassDB::bind_method(D_METHOD("set", "current", "max", "modCurrent", "modMax", "modPercent", "nomodCurrent", "nomodMax", "nomodPercent"), &Stat::set);
	//ClassDB::bind_method(D_METHOD("set_from_stat", "stat"), &Stat::set_from_stat);
	//ClassDB::bind_method(D_METHOD("copy_values_from", "stat"), &Stat::copy_values_from);
	ClassDB::bind_method(D_METHOD("set_to_max"), &Stat::set_to_max);
	ClassDB::bind_method(D_METHOD("set_values", "current", "base", "percent"), &Stat::set_values);

	//ClassDB::bind_method(D_METHOD("apply_modifier", "modifier"), &Stat::apply_modifier);
	//ClassDB::bind_method(D_METHOD("de_apply_modifier", "modifier"), &Stat::de_apply_modifier);
	ClassDB::bind_method(D_METHOD("re_apply_modifier_not_negative_stacking_percents"), &Stat::re_apply_modifier_not_negative_stacking_percents);


	ClassDB::bind_method(D_METHOD("add_modifier", "id", "maxMod", "percentMod", "apply"), &Stat::add_modifier);
	ClassDB::bind_method(D_METHOD("remove_modifier", "id", "apply"), &Stat::remove_modifier);
	ClassDB::bind_method(D_METHOD("re_apply_modifiers"), &Stat::re_apply_modifiers);

	ClassDB::bind_method(D_METHOD("set_dependency", "stat", "curve"), &Stat::set_dependency);
	ClassDB::bind_method(D_METHOD("remove_dependencies"), &Stat::remove_dependencies);

	BIND_ENUM_CONSTANT(Stat::STAT_ID_HEALTH);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_SPEED);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_MANA);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_GLOBAL_COOLDOWN);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_HASTE);

	BIND_ENUM_CONSTANT(Stat::STAT_ID_AGILITY);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_STRENGTH);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_STAMINA);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_INTELLECT);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_LUCK);

	BIND_ENUM_CONSTANT(Stat::STAT_ID_HASTE_RATING);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_RESLILIENCE);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_ARMOR);

	BIND_ENUM_CONSTANT(Stat::STAT_ID_ATTACK_POWER);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_SPELL_POWER);

	BIND_ENUM_CONSTANT(Stat::STAT_ID_MELEE_CRIT);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_MELEE_CRIT_BONUS);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_SPELL_CRIT);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_SPELL_CRIT_BONUS);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_BLOCK);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_PARRY);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_DAMAGE_REDUCTION);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_MELEE_DAMAGE_REDUCTION);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_SPELL_DAMAGE_REDUCTION);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_DAMAGE_TAKEN);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_MELEE_DAMAGE);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_SPELL_DAMAGE);

	BIND_ENUM_CONSTANT(Stat::STAT_ID_HOLY_RESIST);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_SHADOW_RESIST);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_NATURE_RESIST);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_FIRE_RESIST);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_FROST_RESIST);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_LIGHTNING_RESIST);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_CHAOS_RESIST);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_SILENCE_RESIST);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_FEAR_RESIST);

	BIND_ENUM_CONSTANT(Stat::STAT_ID_TOTAL_STATS);
	BIND_ENUM_CONSTANT(Stat::STAT_ID_NONE);

	BIND_ENUM_CONSTANT(Stat::MODIFIER_APPLY_TYPE_STANDARD);
	BIND_ENUM_CONSTANT(Stat::MODIFIER_APPLY_TYPE_ONLY_MIN_MODIFIER);
	BIND_ENUM_CONSTANT(Stat::MODIFIER_APPLY_TYPE_ONLY_MAX_MODIFIER);
}
