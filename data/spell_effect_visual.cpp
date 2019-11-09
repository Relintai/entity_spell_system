#include "spell_effect_visual.h"

SpellEffectVisual::SpellEffectVisual() {
}

SpellEffectVisual::~SpellEffectVisual() {
}

void SpellEffectVisual::_bind_methods() {
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_name"), "set_name", "get_name");
}
