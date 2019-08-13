#include "talent.h"

Ref<Talent> Talent::get_next_rank() const {
	return _next_rank;
}
void Talent::set_next_rank(const Ref<Talent> rank) {
	_next_rank = rank;
}

Talent::Talent() {
	set_aura_type(SpellEnums::AURA_TYPE_TALENT);
	set_hide(true);
}

Talent::~Talent() {
	_next_rank.unref();
	_aura.unref();
}

void Talent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_next_rank"), &Talent::get_next_rank);
	ClassDB::bind_method(D_METHOD("set_next_rank", "next_rank"), &Talent::set_next_rank);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "next_rank", PROPERTY_HINT_RESOURCE_TYPE, "Talent"), "set_next_rank", "get_next_rank");

	ClassDB::bind_method(D_METHOD("get_apply_aura"), &Talent::get_apply_aura);
	ClassDB::bind_method(D_METHOD("set_apply_aura", "value"), &Talent::set_apply_aura);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "apply_aura", PROPERTY_HINT_RESOURCE_TYPE, "Aura"), "set_apply_aura", "get_apply_aura");
}
