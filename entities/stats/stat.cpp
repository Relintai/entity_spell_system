#include "stat.h"

#include "../entity.h"
#include "stat_data_entry.h"

const String Stat::STAT_BINDING_STRING = "Health,Speed,Mana,GCD,Haste,Agility,Strength,Stamina,Intellect,Luck,Haste Rating,Resilience,Armor,Attack Power,Spell Power,Melee Crit,Melee Crit bonus,Spell Crit,Spell Crit Bonus,Block,Parry,Damage Reduction,Melee Damage Reduction,Spell Damage Reduction,Damage Taken,Heal Taken,Melee Damage,Spell Damage,Holy Resist,Shadow Resist,Nature Resist,Fire Resist,Frost Resist,Lightning Resist,Chaos Resist,Silence Resist,Fear Resist,Stun Resist,Energy,Rage,XP Rate,None";
const String Stat::MAIN_STAT_BINDING_STRING = "Agility,Strength,Stamina,Intellect,Luck";

const String Stat::MODIFIER_APPLY_TYPE_BINDING_STRING = "Standard,Only min modifier,Only Max modifier";

String Stat::stat_id_name(int stat_id) {
	switch (stat_id) {
		case STAT_ID_HEALTH:
			return "health";
		case STAT_ID_SPEED:
			return "speed";
		case STAT_ID_MANA:
			return "mana";
		case STAT_ID_GLOBAL_COOLDOWN:
			return "gcd";
		case STAT_ID_HASTE:
			return "haste";

		case STAT_ID_AGILITY:
			return "agility";
		case STAT_ID_STRENGTH:
			return "strength";
		case STAT_ID_STAMINA:
			return "stamina";
		case STAT_ID_INTELLECT:
			return "intellect";
		case STAT_ID_LUCK:
			return "luck";

		case STAT_ID_HASTE_RATING:
			return "haste_rating";
		case STAT_ID_RESLILIENCE:
			return "resilience";
		case STAT_ID_ARMOR:
			return "armor";

		case STAT_ID_ATTACK_POWER:
			return "attack_power";
		case STAT_ID_SPELL_POWER:
			return "spell_power";

		case STAT_ID_MELEE_CRIT:
			return "melee_crit";
		case STAT_ID_MELEE_CRIT_BONUS:
			return "melee_crit_bonus";
		case STAT_ID_SPELL_CRIT:
			return "spell_crit";
		case STAT_ID_SPELL_CRIT_BONUS:
			return "spell_crit_bonus";

		case STAT_ID_BLOCK:
			return "block";
		case STAT_ID_PARRY:
			return "parry";
		case STAT_ID_DAMAGE_REDUCTION:
			return "damage_reduction";
		case STAT_ID_MELEE_DAMAGE_REDUCTION:
			return "melee_damage_reduction";
		case STAT_ID_SPELL_DAMAGE_REDUCTION:
			return "spell_damage_reduction";
		case STAT_ID_DAMAGE_TAKEN:
			return "damage_taken";
		case STAT_ID_HEAL_TAKEN:
			return "heal_taken";

		case STAT_ID_MELEE_DAMAGE:
			return "melee_damage";
		case STAT_ID_SPELL_DAMAGE:
			return "spell_damage";

		case STAT_ID_HOLY_RESIST:
			return "holy_resist";
		case STAT_ID_SHADOW_RESIST:
			return "shadow_resist";
		case STAT_ID_NATURE_RESIST:
			return "nature_resist";
		case STAT_ID_FIRE_RESIST:
			return "fire_resist";
		case STAT_ID_FROST_RESIST:
			return "frost_resist";
		case STAT_ID_LIGHTNING_RESIST:
			return "lightning_resist";
		case STAT_ID_CHAOS_RESIST:
			return "chaos_resist";
		case STAT_ID_SILENCE_RESIST:
			return "silence_resist";
		case STAT_ID_FEAR_RESIST:
			return "fear_resist";
		case STAT_ID_STUN_RESIST:
			return "stun_resist";

		case STAT_ID_ENERGY:
			return "energy";
		case STAT_ID_RAGE:
			return "rage";

		case STAT_ID_XP_RATE:
			return "xp_rate";
	}

	return "";
}

Stat::StatId Stat::get_id() {
	return _id;
}
void Stat::set_id(Stat::StatId id) {
	_id = id;
}

Ref<StatDataEntry> Stat::get_stat_data_entry() {
	return _stat_data_entry;
}
void Stat::set_stat_data_entry(Ref<StatDataEntry> entry) {
	_stat_data_entry = entry;
}

Entity *Stat::get_owner() {
	return _owner;
}
void Stat::set_owner(Entity *value) {
	_owner = value;
}
void Stat::set_owner_bind(Node *value) {
	if (!value) {
		return;
	}

	Entity *e = cast_to<Entity>(value);

	if (!e) {
		return;
	}

	_owner = e;
}

Stat::StatModifierApplyType Stat::get_stat_modifier_type() {
	return _modifier_apply_type;
}
void Stat::set_stat_modifier_type(Stat::StatModifierApplyType value) {
	_modifier_apply_type = value;
}

bool Stat::get_public() {
	return _public;
}
void Stat::set_public(bool value) {
	_public = value;
}

bool Stat::get_locked() {
	return _locked;
}
void Stat::set_locked(bool value) {
	_locked = value;
}

bool Stat::get_dirty() {
	return _dirty;
}
void Stat::set_dirty(bool value) {
	_dirty = value;
}

bool Stat::get_dirty_mods() {
	return _dirty_mods;
}
void Stat::set_dirty_mods(bool value) {
	_dirty_mods = value;
}

float Stat::get_base() {
	return _base;
}
float Stat::get_bonus() {
	return _bonus;
}
float Stat::get_percent() {
	return _percent;
}

float Stat::gets_current() {
	return _s_current;
}
void Stat::sets_current(float value) {
	if (_locked) {
		return;
	}

	_s_current = value;

	_dirty = true;
}

float Stat::gets_max() {
	return _s_max;
}
void Stat::sets_max(float value) {
	_s_max = value;

	_dirty = true;
}

float Stat::getc_current() {
	return _c_current;
}
void Stat::setc_current(float value) {
	ERR_FAIL_COND(_owner == NULL);

	_c_current = value;

	_owner->onc_stat_changed(Ref<Stat>(this));

	emit_signal("c_changed", Ref<Stat>(this));
}

float Stat::getc_max() {
	return _c_max;
}
void Stat::setc_max(float value) {
	ERR_FAIL_COND(_owner == NULL);

	_s_current = value;

	_owner->onc_stat_changed(Ref<Stat>(this));

	emit_signal("c_changed", Ref<Stat>(this));
}

void Stat::setc_values(int ccurrent, int cmax) {
	ERR_FAIL_COND(_owner == NULL);

	_c_current = ccurrent;
	_c_max = cmax;

	_owner->onc_stat_changed(Ref<Stat>(this));
	emit_signal("c_changed", Ref<Stat>(this));
}

_FORCE_INLINE_ Vector<Ref<StatModifier> > *Stat::get_modifiers() {
	return &_modifiers;
}

int Stat::get_modifier_count() {
	return _modifiers.size();
}

void Stat::clear_modifiers() {
	_modifiers.clear();

	_dirty = true;
	_dirty_mods = true;
}

Ref<StatModifier> Stat::get_modifier(int index) {
	return _modifiers.get(index);
}

Ref<StatModifier> Stat::add_modifier(int id, float base_mod, float bonus_mod, float percent_mod) {
	Ref<StatModifier> stat_modifier = Ref<StatModifier>(memnew(StatModifier(id, base_mod, bonus_mod, percent_mod, this)));

	_modifiers.push_back(stat_modifier);

	_dirty = true;
	_dirty_mods = true;

	return stat_modifier;
}

Ref<StatModifier> Stat::get_or_add_modifier(int id) {
	for (int i = 0; i < _modifiers.size(); ++i) {
		if (_modifiers.get(i)->get_id() == id) {
			return _modifiers.get(i);
		}
	}

	Ref<StatModifier> stat_modifier = Ref<StatModifier>(memnew(StatModifier(id, 0, 0, 0, this)));

	_modifiers.push_back(stat_modifier);

	return stat_modifier;
}

void Stat::remove_modifier(int id) {
	for (int i = 0; i < _modifiers.size(); ++i) {
		if (_modifiers.get(i)->get_id() == id) {
			Ref<StatModifier> modifier = _modifiers.get(i);
			_modifiers.remove(i);

			_dirty_mods = true;

			return;
		}
	}
}

void Stat::remove_modifier_index(int index) {
	_modifiers.remove(index);
}

void Stat::apply_modifiers() {
	ERR_FAIL_COND(_owner == NULL);
	ERR_FAIL_COND(!_stat_data_entry.is_valid());

	reset_values();

	if (_modifier_apply_type == MODIFIER_APPLY_TYPE_STANDARD) {
		for (int i = 0; i < _modifiers.size(); i += 1) {
			Ref<StatModifier> mod = _modifiers.get(i);
			print_error("apply  " + String::num(mod->get_base_mod()));
			_base += mod->get_base_mod();
			_bonus += mod->get_bonus_mod();
			_percent += mod->get_percent_mod();
		}
	} else {
		for (int i = 0; i < _modifiers.size(); i += 1) {
			Ref<StatModifier> modifier = _modifiers.get(i);

			if (modifier->get_percent_mod() >= (float)0) {
				_base += modifier->get_base_mod();
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
	}

	refresh_currmax();
	_dirty_mods = false;

	for (int i = 0; i < _stat_data_entry->get_mod_stat_count(); ++i) {
		Ref<Stat> stat = _owner->get_stat_enum(_stat_data_entry->get_mod_stat_id(i));
		Ref<Curve> curve = _stat_data_entry->get_mod_stat_curve(i);

		ERR_FAIL_COND(!stat.is_valid());
		ERR_FAIL_COND(!curve.is_valid());

		Ref<StatModifier> sm = stat->get_or_add_modifier(-(static_cast<int>(_id) + 1));

		sm->set_base_mod(_s_current * curve->interpolate(_s_current));
	}

	_owner->ons_stat_changed(Ref<Stat>(this));
	emit_signal("s_changed", Ref<Stat>(this));
}

void Stat::reset_values() {
	_percent = 100;
	_bonus = 0;
	_percent = 0;

	_dirty = true;
	_dirty_mods = true;
}

void Stat::refresh_currmax() {
	float diff = _s_current / _s_max;

	_s_max = (_base + _bonus) * (_percent / 100.0);

	if (_s_current > _s_max) {
		_s_current = _s_max;
	}

	_s_current = _s_max * diff;

	_dirty = true;
}

bool Stat::iss_current_zero() {
	return (fabs(_s_current) < .000001);
}

bool Stat::isc_current_zero() {
	return (fabs(_c_current) < .000001);
}

void Stat::set_to_max() {
	ERR_FAIL_COND(_owner == NULL);

	_s_current = _s_max;

	_dirty = true;

	_owner->ons_stat_changed(Ref<Stat>(this));
	emit_signal("s_changed", Ref<Stat>(this));
}

void Stat::modifier_changed(Ref<StatModifier> modifier) {
	_dirty_mods = true;
}

Dictionary Stat::to_dict() {
	return call("_to_dict");
}
void Stat::from_dict(const Dictionary &dict) {
	call("_from_dict", dict);
}

Dictionary Stat::_to_dict() {
	Dictionary dict;

	dict["id"] = _id;
	dict["modifier_apply_type"] = _modifier_apply_type;

	dict["public"] = _public;
	dict["locked"] = _locked;
	dict["dirty"] = _dirty;
	dict["dirty_mods"] = _dirty_mods;

	dict["base"] = _base;
	dict["bonus"] = _bonus;
	dict["percent"] = _percent;

	dict["current"] = _s_current;
	dict["max"] = _s_max;

	Dictionary modifiers;

	for (int i = 0; _modifiers.size(); ++i) {
		modifiers[i] = _modifiers.get(i)->to_dict();
	}

	dict["modifiers"] = modifiers;

	return dict;
}
void Stat::_from_dict(const Dictionary &dict) {
	ERR_FAIL_COND(dict.empty());

	_id = (Stat::StatId)((int)dict.get("id", 0));
	_modifier_apply_type = (StatModifierApplyType)((int)dict.get("modifier_apply_type", 0));

	_public = dict.get("public", false);
	_locked = dict.get("locked", false);
	_dirty = dict.get("dirty", false);
	_dirty_mods = dict.get("dirty_mods", false);

	_base = dict.get("base", 0);
	_bonus = dict.get("bonus", 0);
	_percent = dict.get("percent", 1);

	_s_current = dict.get("current", 0);
	_s_max = dict.get("max", 0);

	_c_current = _s_current;
	_c_max = _s_max;

	_modifiers.clear();

	Dictionary modifiers = dict.get("modifiers", Dictionary());

	for (int i = 0; i < modifiers.size(); ++i) {
		Ref<StatModifier> sm;
		sm.instance();

		sm->from_dict(modifiers.get(i, Dictionary()));
		sm->set_owner(this);

		_modifiers.push_back(sm);
	}
}

Stat::Stat() {
	_id = Stat::STAT_ID_NONE;
	_owner = NULL;

	_modifier_apply_type = MODIFIER_APPLY_TYPE_STANDARD;

	_public = false;
	_dirty_mods = false;

	_locked = false;
	_dirty = true;

	_base = 0;
	_bonus = 0;
	_percent = 100;

	_s_current = 0;
	_s_max = 0;

	_c_current = 0;
	_c_max = 0;
}

Stat::Stat(Stat::StatId id, Entity *owner) {
	_id = id;
	_owner = owner;

	_modifier_apply_type = MODIFIER_APPLY_TYPE_STANDARD;

	_public = false;
	_dirty_mods = false;

	_locked = false;
	_dirty = true;

	_base = 0;
	_bonus = 0;
	_percent = 100;

	_s_current = 0;
	_s_max = 0;

	_c_current = 0;
	_c_max = 0;
}

Stat::Stat(Stat::StatId id, StatModifierApplyType modifier_apply_type, Entity *owner) {
	_id = id;
	_owner = owner;

	_modifier_apply_type = modifier_apply_type;

	_public = false;
	_dirty_mods = false;

	_locked = false;
	_dirty = true;

	_base = 0;
	_bonus = 0;
	_percent = 100;

	_s_current = 0;
	_s_max = 0;

	_c_current = 0;
	_c_max = 0;
}

Stat::~Stat() {
	_modifiers.clear();
	_owner = NULL;
	_stat_data_entry.unref();
}

void Stat::_bind_methods() {
	ADD_SIGNAL(MethodInfo("s_changed", PropertyInfo(Variant::OBJECT, "stat", PROPERTY_HINT_RESOURCE_TYPE, "Stat")));
	ADD_SIGNAL(MethodInfo("c_changed", PropertyInfo(Variant::OBJECT, "stat", PROPERTY_HINT_RESOURCE_TYPE, "Stat")));

	ClassDB::bind_method(D_METHOD("get_id"), &Stat::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "id"), &Stat::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id", PROPERTY_HINT_ENUM, STAT_BINDING_STRING), "set_id", "get_id");

	ClassDB::bind_method(D_METHOD("get_stat_data_entry"), &Stat::get_stat_data_entry);
	ClassDB::bind_method(D_METHOD("set_stat_data_entry", "value"), &Stat::set_stat_data_entry);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "stat_data_entry", PROPERTY_HINT_RESOURCE_TYPE, "StatDataEntry"), "set_stat_data_entry", "get_stat_data_entry");

	ClassDB::bind_method(D_METHOD("get_owner"), &Stat::get_owner);
	ClassDB::bind_method(D_METHOD("set_owner", "value"), &Stat::set_owner_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "owner", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "set_owner", "get_owner");

	ClassDB::bind_method(D_METHOD("get_stat_modifier_type"), &Stat::get_stat_modifier_type);
	ClassDB::bind_method(D_METHOD("set_stat_modifier_type", "value"), &Stat::set_stat_modifier_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "stat_type", PROPERTY_HINT_ENUM, "Standard, Min Modifier, Max modifier"), "set_stat_modifier_type", "get_stat_modifier_type");

	ClassDB::bind_method(D_METHOD("get_public"), &Stat::get_public);
	ClassDB::bind_method(D_METHOD("set_public", "value"), &Stat::set_public);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "public"), "set_public", "get_public");

	ClassDB::bind_method(D_METHOD("get_locked"), &Stat::get_locked);
	ClassDB::bind_method(D_METHOD("set_locked", "value"), &Stat::set_locked);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "locked"), "set_locked", "get_locked");

	ClassDB::bind_method(D_METHOD("get_dirty"), &Stat::get_dirty);
	ClassDB::bind_method(D_METHOD("set_dirty", "value"), &Stat::set_dirty);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_dirty"), "set_dirty", "get_dirty");

	ClassDB::bind_method(D_METHOD("get_dirty_mods"), &Stat::get_dirty_mods);
	ClassDB::bind_method(D_METHOD("set_dirty_mods", "value"), &Stat::set_dirty_mods);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "dirty_mods"), "set_dirty_mods", "get_dirty_mods");

	ClassDB::bind_method(D_METHOD("get_base"), &Stat::get_base);
	ClassDB::bind_method(D_METHOD("get_bonus"), &Stat::get_bonus);
	ClassDB::bind_method(D_METHOD("get_percent"), &Stat::get_percent);

	ClassDB::bind_method(D_METHOD("gets_current"), &Stat::gets_current);
	ClassDB::bind_method(D_METHOD("sets_current", "value"), &Stat::sets_current);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "scurrent"), "sets_current", "gets_current");

	ClassDB::bind_method(D_METHOD("gets_max"), &Stat::gets_max);
	ClassDB::bind_method(D_METHOD("sets_max"), &Stat::sets_max);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "smax"), "sets_max", "gets_max");

	ClassDB::bind_method(D_METHOD("getc_max"), &Stat::getc_max);
	ClassDB::bind_method(D_METHOD("setc_max"), &Stat::setc_max);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "cmax"), "setc_max", "getc_max");

	ClassDB::bind_method(D_METHOD("getc_current"), &Stat::getc_current);
	ClassDB::bind_method(D_METHOD("setc_current", "value"), &Stat::setc_current);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "ccurrent"), "setc_current", "getc_current");

	ClassDB::bind_method(D_METHOD("setc_values", "ccurrent", "cmax"), &Stat::setc_values);

	ClassDB::bind_method(D_METHOD("add_modifier", "id", "base_mod", "bonus_mod", "percent_mod"), &Stat::add_modifier);
	ClassDB::bind_method(D_METHOD("get_or_add_modifier", "id"), &Stat::get_or_add_modifier);
	ClassDB::bind_method(D_METHOD("remove_modifier", "id"), &Stat::remove_modifier);
	ClassDB::bind_method(D_METHOD("remove_modifier_index", "index"), &Stat::remove_modifier_index);
	ClassDB::bind_method(D_METHOD("get_modifier_count"), &Stat::get_modifier_count);
	ClassDB::bind_method(D_METHOD("clear_modifiers"), &Stat::clear_modifiers);
	ClassDB::bind_method(D_METHOD("get_modifier", "index"), &Stat::get_modifier);

	ClassDB::bind_method(D_METHOD("apply_modifiers"), &Stat::apply_modifiers);

	ClassDB::bind_method(D_METHOD("reset_values"), &Stat::reset_values);
	ClassDB::bind_method(D_METHOD("refresh_currmax"), &Stat::refresh_currmax);
	ClassDB::bind_method(D_METHOD("iss_current_zero"), &Stat::iss_current_zero);
	ClassDB::bind_method(D_METHOD("isc_current_zero"), &Stat::isc_current_zero);

	ClassDB::bind_method(D_METHOD("set_to_max"), &Stat::set_to_max);

	ClassDB::bind_method(D_METHOD("modifier_changed", "modifier"), &Stat::modifier_changed);

	//Serialization
	BIND_VMETHOD(MethodInfo("_from_dict", PropertyInfo(Variant::DICTIONARY, "dict")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::DICTIONARY, "dict"), "_to_dict"));

	ClassDB::bind_method(D_METHOD("from_dict", "dict"), &Stat::from_dict);
	ClassDB::bind_method(D_METHOD("to_dict"), &Stat::to_dict);

	ClassDB::bind_method(D_METHOD("_from_dict", "dict"), &Stat::_from_dict);
	ClassDB::bind_method(D_METHOD("_to_dict"), &Stat::_to_dict);

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

	BIND_ENUM_CONSTANT(Stat::MAIN_STAT_ID_AGILITY);
	BIND_ENUM_CONSTANT(Stat::MAIN_STAT_ID_STRENGTH);
	BIND_ENUM_CONSTANT(Stat::MAIN_STAT_ID_STAMINA);
	BIND_ENUM_CONSTANT(Stat::MAIN_STAT_ID_INTELLECT);
	BIND_ENUM_CONSTANT(Stat::MAIN_STAT_ID_LUCK);
	BIND_ENUM_CONSTANT(Stat::MAIN_STAT_ID_COUNT);
	BIND_ENUM_CONSTANT(Stat::MAIN_STAT_ID_MIN);
	BIND_ENUM_CONSTANT(Stat::MAIN_STAT_ID_MAX);
}
