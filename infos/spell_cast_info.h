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

#ifndef SPELL_INFOS_H
#define SPELL_INFOS_H

#include "../entities/entity.h"
#include "core/reference.h"

class Spell;
class Entity;

class SpellCastInfo : public Reference {
	GDCLASS(SpellCastInfo, Reference);

public:
	Entity *get_caster();
	void set_caster(Entity *caster);
	void set_caster_bind(Node *caster);

	Entity *get_target();
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

	void physics_process(float delta);

	void resolve_references(Node *owner);
	Dictionary to_dict();
	void from_dict(const Dictionary &dict);

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

	int _spell_id;
	Ref<Spell> _spell;

	NodePath _target_path;
};

#endif
