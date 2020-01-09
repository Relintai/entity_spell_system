#ifndef CHARACTER_ATLAS_H
#define CHARACTER_ATLAS_H

#include "core/resource.h"

class CharacterAtlas : public Resource {
	GDCLASS(CharacterAtlas, Resource);

public:
	CharacterAtlas();

protected:
	static void _bind_methods();

	//private:
};

#endif
