#ifndef AURA_TRIGGER_DATA_H
#define AURA_TRIGGER_DATA_H

#include "core/reference.h"

#include "../spell_enums.h"
#include "aura.h"
#include "spell.h"

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
