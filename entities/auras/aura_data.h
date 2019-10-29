#ifndef AURA_DATA_H
#define AURA_DATA_H

#include "core/reference.h"
#include "core/array.h"
#include "core/dictionary.h"

#include "../../spell_enums.h"

class Aura;
class Entity;

class AuraData : public Reference {
	GDCLASS(AuraData, Reference);

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

	Entity *get_caster();
	void set_caster(Entity *value);
	void set_caster_bind(Node *value);

	NodePath get_caster_path();
	void set_caster_path(NodePath value);

	float get_spell_scale();
	void set_spell_scale(float value);

	Ref<Aura> get_aura();
	void set_aura(Ref<Aura> aura);

	void refresh(float remaining);

	int get_damage();
	void set_damage(int value);

	float get_damage_count();
	void set_damage_count(int damageTaken);

	float get_tick();
	void set_tick(float value);

	float get_time_since_last_tick();
	void set_time_since_last_tick(float value);

	int get_unhandled_ticks();
	void set_unhandled_ticks(int value);

	int get_damage_taken();
	void set_damage_taken(int value);

	int get_heal();
	void set_heal(int value);

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
	float _remaining_time;
	Entity *_caster;
	NodePath _caster_path;
	float _spell_scale;
	int _aura_group;
	Ref<Aura> _aura;

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
