#ifndef SPELL_VISUAL_EFFECT_H
#define SPELL_VISUAL_EFFECT_H

#include "core/reference.h"

class SpellVisualEffect : public Reference {
	GDCLASS(SpellVisualEffect, Reference);

public:
	void set_id() {}

protected:
	static void _bind_methods() {
	}

private:
	int id;
};

#endif
