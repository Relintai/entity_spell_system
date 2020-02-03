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

#ifndef AURA_TRIGGER_DATA_H
#define AURA_TRIGGER_DATA_H

#include "core/reference.h"

#include "../../spell_enums.h"
#include "../spells/spell.h"
#include "aura.h"

class Spell;

class AuraTriggerData : public Reference {
	GDCLASS(AuraTriggerData, Reference);

public:
	SpellEnums::TriggerEvents get_trigger_event() const { return _trigger_event; }
	void set_trigger_event(const SpellEnums::TriggerEvents trigger_event) { _trigger_event = trigger_event; }

	Ref<Aura> get_aura() const { return _aura; }
	void set_aura(const Ref<Aura> aura) { _aura = aura; }

	Ref<Spell> get_spell() const { return _spell; }
	void set_spell(const Ref<Spell> spell) { _spell = spell; }

protected:
	static void _bind_methods() {
		ClassDB::bind_method(D_METHOD("get_trigger_event"), &AuraTriggerData::get_trigger_event);
		ClassDB::bind_method(D_METHOD("set_trigger_event", "value"), &AuraTriggerData::set_trigger_event);
		ADD_PROPERTY(PropertyInfo(Variant::INT, "trigger_event", PROPERTY_HINT_ENUM, SpellEnums::BINDING_STRING_TRIGGER_EVENTS), "set_trigger_event", "get_trigger_event");

		ClassDB::bind_method(D_METHOD("get_aura"), &AuraTriggerData::get_aura);
		ClassDB::bind_method(D_METHOD("set_aura", "value"), &AuraTriggerData::set_aura);
		ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura", PROPERTY_HINT_RESOURCE_TYPE, "Aura"), "set_aura", "get_aura");

		ClassDB::bind_method(D_METHOD("get_spell"), &AuraTriggerData::get_spell);
		ClassDB::bind_method(D_METHOD("set_spell", "value"), &AuraTriggerData::set_aura);
		ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "spell", PROPERTY_HINT_RESOURCE_TYPE, "Spell"), "set_spell", "get_spell");
	}

private:
	SpellEnums::TriggerEvents _trigger_event;
	Ref<Aura> _aura;
	Ref<Spell> _spell;
};

#endif
