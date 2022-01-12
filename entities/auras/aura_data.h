/*
Copyright (c) 2019-2022 Péter Magyar

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

#ifndef AURA_DATA_H
#define AURA_DATA_H

#include "core/version.h"

#if VERSION_MAJOR > 3
#include "core/io/resource.h"
#include "core/variant/array.h"
#include "core/variant/dictionary.h"
#else
#include "core/resource.h"
#include "core/array.h"
#include "core/dictionary.h"
#endif

#include "../../spell_enums.h"

class Spell;
class Entity;

class AuraData : public Resource {
	GDCLASS(AuraData, Resource);

public:
	int get_aura_id();
	void set_aura_id(int value);

	bool get_is_timed();
	void set_is_timed(bool value);

	float get_remaining_time();
	void set_remaining_time(float value);
	bool update(float delta);

	Entity *get_owner();
	void set_owner(Entity *value);
	void set_owner_bind(Node *value);

	Entity *caster_get();
	void caster_set(Entity *value);
	void caster_set_bind(Node *value);

	NodePath caster_get_path();
	void caster_set_path(NodePath value);

	float spell_scale_get();
	void spell_scale_set(float value);

	Ref<Spell> get_aura();
	void set_aura(Ref<Spell> aura);

	void refresh(float remaining);

	int damage_get();
	void damage_set(int value);

	float damage_get_count();
	void damage_set_count(int damageTaken);

	float get_tick();
	void set_tick(float value);

	float get_time_since_last_tick();
	void set_time_since_last_tick(float value);

	int get_unhandled_ticks();
	void set_unhandled_ticks(int value);

	int damage_get_taken();
	void damage_set_taken(int value);

	int heal_get();
	void heal_set(int value);

	int get_remaining_absorb();
	void set_remaining_absorb(int remaining_timeAbsorb);

	float get_slow();
	void set_slow(float value);

	void resolve_references(Node *owner);
	Dictionary to_dict();
	void from_dict(const Dictionary &dict);
	Dictionary _to_dict();
	void _from_dict(const Dictionary &dict);

	Array to_send_array();
	void from_send_array(const Array &arr);
	Array _to_send_array();
	void _from_send_array(const Array &arr);

	AuraData();

protected:
	static void _bind_methods();

private:
	Entity *_owner;
	int _aura_id;
	StringName _aura_path;
	float _remaining_time;
	Entity *_caster;
	NodePath _caster_path;
	float _spell_scale;
	int _aura_group;
	Ref<Spell> _aura;

	bool _is_timed;
	int _damage;
	int _heal;
	float _slow;
	int _remaining_absorb;
	float _tick;
	float _time_since_last_tick;
	int _damage_already_taken;
	int _unhandled_ticks;
};

#endif
