#ifndef SPELL_EFFECT_VISUAL_H
#define SPELL_EFFECT_VISUAL_H

#include "core/resource.h"

class SpellEffectVisual : public Resource {
	GDCLASS(SpellEffectVisual, Resource);

public:
	String get_effect_name();
	void set_effect_name(String name);

	SpellEffectVisual();
	~SpellEffectVisual();

protected:
	static void _bind_methods();

private:
	String _effect_name;
};

#endif
