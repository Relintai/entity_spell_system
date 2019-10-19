#ifndef SPELL_EFFECT_VISUAL_H
#define SPELL_EFFECT_VISUAL_H

#include "core/resource.h"

class SpellEffectVisual : public Resource {
	GDCLASS(SpellEffectVisual, Resource);

public:
	String get_text_name();
	void set_text_name(String name);

	SpellEffectVisual();
	~SpellEffectVisual();

protected:
	static void _bind_methods();

private:
	String _text_name;
};

#endif
