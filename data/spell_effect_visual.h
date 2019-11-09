#ifndef SPELL_EFFECT_VISUAL_H
#define SPELL_EFFECT_VISUAL_H

#include "core/resource.h"

class SpellEffectVisual : public Resource {
	GDCLASS(SpellEffectVisual, Resource);

public:
	SpellEffectVisual();
	~SpellEffectVisual();

protected:
	static void _bind_methods();

private:
};

#endif
