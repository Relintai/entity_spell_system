#include "talent.h"

Ref<Talent> Talent::get_required_talent() const {
	return _required_talent;
}
void Talent::set_required_talent(const Ref<Talent> rank) {
	_required_talent = rank;
}

Ref<Spell> Talent::get_required_spell() const {
	return _required_talent;
}
void Talent::set_required_spell(const Ref<Spell> spell) {
	_required_spell = spell;
}

Ref<Spell> Talent::get_teaches_spell() const {
	return _teaches_spell;
}
void Talent::set_teaches_spell(const Ref<Spell> spell) {
	_teaches_spell = spell;
}

Ref<Aura> Talent::get_apply_aura() const {
	return _aura;
}
void Talent::set_apply_aura(Ref<Aura> aura) {
	_aura = Ref<Aura>(aura);
}

Talent::Talent() {
	set_aura_type(SpellEnums::AURA_TYPE_TALENT);
	set_hide(true);
}

Talent::~Talent() {
	_required_talent.unref();
	_required_spell.unref();
	_teaches_spell.unref();
	_aura.unref();
}

void Talent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_required_talent"), &Talent::get_required_talent);
	ClassDB::bind_method(D_METHOD("set_required_talent", "next_rank"), &Talent::set_required_talent);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "required_talent", PROPERTY_HINT_RESOURCE_TYPE, "Talent"), "set_required_talent", "get_required_talent");

	ClassDB::bind_method(D_METHOD("get_required_spell"), &Talent::get_required_spell);
	ClassDB::bind_method(D_METHOD("set_required_spell", "next_rank"), &Talent::set_required_spell);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "required_spell", PROPERTY_HINT_RESOURCE_TYPE, "Spell"), "set_required_spell", "get_required_spell");

	ClassDB::bind_method(D_METHOD("get_teaches_spell"), &Talent::get_teaches_spell);
	ClassDB::bind_method(D_METHOD("set_teaches_spell", "next_rank"), &Talent::set_teaches_spell);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "teaches_spell", PROPERTY_HINT_RESOURCE_TYPE, "Spell"), "set_teaches_spell", "get_teaches_spell");

	ClassDB::bind_method(D_METHOD("get_apply_aura"), &Talent::get_apply_aura);
	ClassDB::bind_method(D_METHOD("set_apply_aura", "value"), &Talent::set_apply_aura);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "apply_aura", PROPERTY_HINT_RESOURCE_TYPE, "Aura"), "set_apply_aura", "get_apply_aura");
}
