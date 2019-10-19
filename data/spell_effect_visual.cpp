#include "spell_effect_visual.h"

String SpellEffectVisual::get_text_name() {
	return _text_name;
}
void SpellEffectVisual::set_text_name(String name) {
	_text_name = name;
}

SpellEffectVisual::SpellEffectVisual() {
}

SpellEffectVisual::~SpellEffectVisual() {
}

void SpellEffectVisual::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_text_name"), &SpellEffectVisual::get_text_name);
	ClassDB::bind_method(D_METHOD("set_text_name", "value"), &SpellEffectVisual::set_text_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_name"), "set_text_name", "get_text_name");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "effect_name"), "set_text_name", "get_text_name"); //REMOVE
}
