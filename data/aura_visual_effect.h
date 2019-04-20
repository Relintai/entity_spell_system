#ifndef AURA_VISUAL_EFFECT_H
#define AURA_VISUAL_EFFECT_H

#include "core/reference.h"


class AuraVisualEffect : public Reference {
	GDCLASS(AuraVisualEffect, Reference);

public:
	void set_id(){}

protected:
	static void _bind_methods() {
	}

private:
	int id;
};


#endif
