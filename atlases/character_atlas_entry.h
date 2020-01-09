#ifndef CHARACTER_ATLAS_ENTRY_H
#define CHARACTER_ATLAS_ENTRY_H

#include "core/resource.h"

class CharacterAtlasEntry : public Resource {
	GDCLASS(CharacterAtlasEntry, Resource);

public:
	CharacterAtlasEntry();

protected:
	static void _bind_methods();

	//private:
};

#endif
