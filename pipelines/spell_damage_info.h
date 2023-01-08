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

#ifndef SPELL_DAMAGE_INFO_H
#define SPELL_DAMAGE_INFO_H

#include "core/version.h"

#include "core/object/ref_counted.h"


#include "../spell_enums.h"
#include "scene/main/node.h"

class Entity;
class Spell;

class SpellDamageInfo : public RefCounted {
	GDCLASS(SpellDamageInfo, RefCounted);

public:
	enum DamageSourceType {
		DAMAGE_SOURCE_UNKNOWN = 0,
		DAMAGE_SOURCE_SPELL,
		DAMAGE_SOURCE_AURA,
	};

protected:
	static void _bind_methods();

public:
	bool get_immune() const;
	void set_immune(const bool value);

	int damage_get() const;
	void damage_set(const int value);

	bool crit_get() const;
	void crit_set(const bool value);

	int amount_absorbed_get() const;
	void amount_absorbed_set(const int value);

	int damage_type_get() const;
	void damage_type_set(const int value);

	Entity *dealer_get();
	void dealer_set(Entity *value);
	void dealer_set_bind(Node *value);

	Entity *receiver_get();
	void receiver_set(Entity *value);
	void receiver_set_bind(Node *value);

	Ref<RefCounted> source_get();
	void source_set(Ref<RefCounted> value);

	Ref<Spell> spell_source_get();
	void spell_source_set(const Ref<Spell> &value);

	Ref<Spell> aura_source_get();
	void aura_source_set(const Ref<Spell> &value);

	int source_get_id() const;
	void source_set_id(const int value);

	int source_get_type() const;
	void source_set_type(const int value);

	void reset();

	void resolve_references(Node *owner);
	Dictionary to_dict();
	void from_dict(const Dictionary &dict);

	SpellDamageInfo();
	~SpellDamageInfo();

private:
	bool _immune;
	int _damage;
	int _original_damage;
	int _amount_absorbed;
	bool _crit;
	int _damage_type;

	int _damage_source_type;
	Ref<RefCounted> _damage_source;
	int _damage_source_id;

	Entity *_dealer;
	Entity *_receiver;

	NodePath _dealer_path;
	NodePath _receiver_path;
};

#endif
