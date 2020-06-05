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

#ifndef SPELL_DAMAGE_INFO_H
#define SPELL_DAMAGE_INFO_H

#include "../spell_enums.h"
#include "core/reference.h"
#include "scene/main/node.h"

class Entity;
class Spell;
class Aura;

class SpellDamageInfo : public Reference {
	GDCLASS(SpellDamageInfo, Reference);

public:
	enum DamageSourceType {
		DAMAGE_SOURCE_UNKNOWN,
		DAMAGE_SOURCE_SPELL,
		DAMAGE_SOURCE_AURA,
	};

protected:
	static void _bind_methods();

public:
	bool get_immune();
	void set_immune(bool value);

	int damage_get();
	void damage_set(int value);

	bool crit_get();
	void crit_set(bool value);

	int amount_absorbed_get();
	void amount_absorbed_set(int value);

	SpellEnums::SpellType spell_type_get();
	void spell_type_set(SpellEnums::SpellType value);

	Entity *dealer_get();
	void dealer_set(Entity *value);
	void dealer_set_bind(Node *value);

	Entity *receiver_get();
	void receiver_set(Entity *value);
	void receiver_set_bind(Node *value);

	Ref<Reference> source_get();
	void source_set(Ref<Reference> value);

	Ref<Spell> spell_source_get();
	void spell_source_set(Ref<Spell> value);

	Ref<Aura> aura_source_get();
	void aura_source_set(Ref<Aura> value);

	int source_get_id();
	void source_set_id(int value);

	DamageSourceType source_get_type();
	void source_set_type(DamageSourceType value);

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
	SpellEnums::SpellType _spell_type;

	DamageSourceType _damage_source_type;
	Ref<Reference> _damage_source;
	int _damage_source_id;

	Entity *_dealer;
	Entity *_receiver;

	NodePath _dealer_path;
	NodePath _receiver_path;
};

VARIANT_ENUM_CAST(SpellDamageInfo::DamageSourceType);

#endif
