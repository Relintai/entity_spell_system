#ifndef LOOT_DATA_CONTAINER_H
#define LOOT_DATA_CONTAINER_H

#include "loot_data_base.h"

class LootDataContainter : public LootDataBase {
	GDCLASS(LootDataContainter, LootDataBase);

public:
	Ref<LootDataBase> get_entry(const int index) const;
	void set_entry(const int index, const Ref<LootDataBase> ldb);

	void _get_loot(Array into);

	LootDataContainter();

	enum {
		MAX_ENTRIES = 6,
	};

protected:
	static void _bind_methods();

private:
	Ref<LootDataBase> _entries[MAX_ENTRIES];
};

#endif
