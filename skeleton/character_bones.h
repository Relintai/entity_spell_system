#ifndef CHARACTER_BONES_H
#define CHARACTER_BONES_H

#include "scene/2d/node_2d.h"

class CharacterBones : public Node2D {
	GDCLASS(CharacterBones, Node2D);

public:
	CharacterBones();

protected:
	static void _bind_methods();

//private:
};

#endif
