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

	int get_damage();
	void set_damage(int value);

	bool get_crit();
	void set_crit(bool value);

	int get_amount_absorbed();
	void set_amount_absorbed(int value);

	SpellEnums::SpellType get_spell_type();
	void set_spell_type(SpellEnums::SpellType value);

	Entity *get_dealer();
	void set_dealer(Entity *value);
	void set_dealer_bind(Node *value);

	Entity *get_receiver();
	void set_receiver(Entity *value);
	void set_receiver_bind(Node *value);

	Ref<Reference> get_damage_source();
	void set_damage_source(Ref<Reference> value);

	Ref<Spell> get_spell_damage_source();
	void set_spell_damage_source(Ref<Spell> value);

	Ref<Aura> get_aura_damage_source();
	void set_aura_damage_source(Ref<Aura> value);

	int get_damage_source_id();
	void set_damage_source_id(int value);

	DamageSourceType get_damage_source_type();
	void set_damage_source_type(DamageSourceType value);

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
