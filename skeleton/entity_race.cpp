#include "entity_race.h"


void EntityRace::_bind_methods() {
	BIND_VMETHOD(MethodInfo(Variant::STRING, "_generate_name", PropertyInfo(Variant::INT, "seed")));

	BIND_CONSTANT(MAX_SKIN_COLORS);
 }
