/*
Copyright (c) 2019-2020 Péter Magyar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
	static const String MAIN_STAT_BINDING_STRING;
	static const String MODIFIER_APPLY_TYPE_BINDING_STRING;

	enum StatModifierApplyType {
		MODIFIER_APPLY_TYPE_STANDARD,
		MODIFIER_APPLY_TYPE_ONLY_MIN_MODIFIER,
		MODIFIER_APPLY_TYPE_ONLY_MAX_MODIFIER,
	};

	static String stat_id_name(int stat_id);

public:
	int get_id();
	void set_id(int id);

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
	Stat(int id, Entity *owner);
	Stat(int id, StatModifierApplyType modifier_apply_type, Entity *owner);
	~Stat();

protected:
	virtual void _validate_property(PropertyInfo &property) const;
	static void _bind_methods();

private:
	int _id;

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

VARIANT_ENUM_CAST(Stat::StatModifierApplyType);

#endif
