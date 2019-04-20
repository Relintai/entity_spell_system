#ifndef AURA_DATA_H
#define AURA_DATA_H

#include "../../spell_enums.h"
#include "core/reference.h"

class Aura;
class Entity;

class AuraData : public Reference {
	GDCLASS(AuraData, Reference);

public:
	int get_aura_id();
	void set_aura_id(int value);

	float get_remaining_time();
	void set_remaining_time(float value);
	bool update_remaining_time(float delta);

	Entity *get_owner();
	void set_owner(Node *value);

	Entity *get_caster();
	void set_caster(Node *value);

	int get_caster_guid();
	void set_caster_guid(int value);

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

	AuraData();

protected:
	static void _bind_methods();

private:
	Entity *_owner;
	int _aura_id;
	float _remaining_time;
	Entity *_caster;
	int _caster_guid;
	float _spell_scale;
	int _aura_group;
	Ref<Aura> _aura;

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
