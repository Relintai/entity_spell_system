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

#ifndef SPELL_INFOS_H
#define SPELL_INFOS_H

#include "core/version.h"

#if VERSION_MAJOR > 3
#include "core/io/resource.h"
#else
#include "core/resource.h"
#endif

class Spell;
class Entity;
class ItemInstance;
class ItemTemplate;

class SpellCastInfo : public Resource {
	GDCLASS(SpellCastInfo, Resource);

public:
	Entity *caster_get();
	void caster_set(Entity *caster);
	void caster_set_bind(Node *caster);

	Entity *target_get();
	void target_set(Entity *caster);
	void target_set_bind(Node *caster);

	bool has_cast_time_get() const;
	void has_cast_time_set(bool value);

	float cast_time_get() const;
	void cast_time_set(float value);

	float current_cast_time_get() const;
	void current_cast_time_set(float value);

	bool is_casting_get() const;
	void is_casting_set(bool value);

	int num_pushbacks_get() const;
	void num_pushbacks_set(int value);

	float spell_scale_get() const;
	void spell_scale_set(float value);

	Ref<Spell> get_spell() const;
	void set_spell(const Ref<Spell> &spell);

	Ref<ItemInstance> get_source_item() const;
	void set_source_item(const Ref<ItemInstance> &item);

	Ref<ItemTemplate> get_source_template() const;
	void set_source_template(const Ref<ItemTemplate> &source_template);

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
	Ref<ItemInstance> _source_item;
	Ref<ItemTemplate> _source_template;

	NodePath _target_path;
};

#endif
