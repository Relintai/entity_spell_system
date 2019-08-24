#ifndef CHARACTER_BONES_H
#define CHARACTER_BONES_H

#include "core/resource.h"

class CharacterBones : public Resource {
	GDCLASS(CharacterBones, Resource);

public:
	CharacterBones();

protected:
	static void _bind_methods();

//private:
};

#endif
