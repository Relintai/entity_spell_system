#include "skill.h"

Skill::Skill() {
	set_aura_type(SpellEnums::AURA_TYPE_SKILL);
	set_hide(true);
}

Skill::~Skill() {
}

void Skill::_bind_methods() {
}
