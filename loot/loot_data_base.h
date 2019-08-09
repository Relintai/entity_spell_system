#ifndef LOOT_DATA_BASE_H
#define LOOT_DATA_BASE_H

#include "core/array.h"

#include "../data/item_template.h"

class LootDataBase : public Resource {
	GDCLASS(LootDataBase, Resource);

public:
	float get_chance() const;
	void set_chance(const float value);

	void get_loot(Array into);

	LootDataBase();

protected:
	static void _bind_methods();

private:
	float _chance;
};

#endif
