#include "spell_effect_visual.h"

String SpellEffectVisual::get_effect_name() {
	return _effect_name;
}
void SpellEffectVisual::set_effect_name(String name) {
	_effect_name = name;
}

SpellEffectVisual::SpellEffectVisual() {
}

SpellEffectVisual::~SpellEffectVisual() {
}

void SpellEffectVisual::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_effect_name"), &SpellEffectVisual::get_effect_name);
	ClassDB::bind_method(D_METHOD("set_effect_name", "value"), &SpellEffectVisual::set_effect_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "effect_name"), "set_effect_name", "get_effect_name");
}
