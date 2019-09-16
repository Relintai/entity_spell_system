#ifndef PLAYER_CHARACTER_DATA_H
#define PLAYER_CHARACTER_DATA_H

#include "core/resource.h"
#include "core/ustring.h"

#include "entity_data.h"

//Rename this to EntityData, and rename EntityData to EntityClassData
//inheritance in entiotyData?

class PlayerCharacterData : public Resource {
	GDCLASS(PlayerCharacterData, Resource);

public:

	Ref<EntityData> get_entity_data();
	void set_entity_data(Ref<EntityData> data);

	PlayerCharacterData();
	~PlayerCharacterData();

protected:
	static void _bind_methods();

private:
	Ref<EntityData> _entity_data;
};


#endif
