#ifndef ENTITY_RACE_H
#define ENTITY_RACE_H

#include "core/resource.h"
#include "core/ustring.h"

class Spell;
class Aura;

class EntityRace : public Resource {
	GDCLASS(EntityRace, Resource);

public:
	enum {
		MAX_SKIN_COLORS = 10,
		MAX_SPELLS = 10,
		MAX_AURAS = 10
	};

	enum EntityRaceType {
		ENTITY_RACE_TYPE_NONE,
		ENTITY_RACE_TYPE_HUMANOID,
		ENTITY_RACE_TYPE_BEAST
	};

	String generate_name(int seed);

protected:
	static void _bind_methods();

private:

	String _name;
	String _description;
	//Ref<SkeletonData> _skeleton_data;
	Color _preset_skin_colors[MAX_SKIN_COLORS];
	Ref<Spell> _spells[MAX_SPELLS];
	Ref<Aura> _auras[MAX_AURAS];
	EntityRaceType _type;
};

#endif
