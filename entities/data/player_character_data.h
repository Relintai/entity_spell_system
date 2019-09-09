#ifndef PLAYER_CHARACTER_DATA_H
#define PLAYER_CHARACTER_DATA_H

#include "core/resource.h"
#include "core/ustring.h"

#include "entity_data.h"

class PlayerCharacterData : public EntityData {
	GDCLASS(PlayerCharacterData, EntityData);

public:

	PlayerCharacterData();
	~PlayerCharacterData();

protected:
	static void _bind_methods();

private:
};


#endif
