#ifndef SPELL_INFOS_H
#define SPELL_INFOS_H

#include "../entities/entity.h"
#include "core/reference.h"

class Spell;
class Entity;

class SpellCastInfo : public Reference {
	GDCLASS(SpellCastInfo, Reference);

public:
	Entity *get_caster() const;
	void set_caster(Entity *caster);
	void set_caster_bind(Node *caster);

	Entity *get_target() const;
	void set_target(Entity *caster);
	void set_target_bind(Node *caster);

	bool get_has_cast_time() const;
	void set_has_cast_time(bool value);

	float get_cast_time() const;
	void set_cast_time(float value);

	float get_current_cast_time() const;
	void set_current_cast_time(float value);

	bool get_is_casting() const;
	void set_is_casting(bool value);

	int get_num_pushbacks() const;
	void set_num_pushbacks(int value);

	float get_spell_scale() const;
	void set_spell_scale(float value);

	Ref<Spell> get_spell() const;
	void set_spell(Ref<Spell> spell);

	bool update_cast_time(float delta);

	SpellCastInfo();
	~SpellCastInfo();

protected:
	static void _bind_methods();

private:
	Entity *_caster;
	Entity *_target;
	bool _has_cast_time;
	float _cast_time;
	float _spell_scale;

	float _current_cast_time;
	int _num_pushbacks;

	bool _is_casting;

	Ref<Spell> _spell;
};

#endif
