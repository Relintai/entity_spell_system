#ifndef LOOT_DATA_CONTAINER_H
#define LOOT_DATA_CONTAINER_H

#include "core/vector.h"
#include "loot_data_base.h"

class LootDataContainter : public LootDataBase {
	GDCLASS(LootDataContainter, LootDataBase);

public:
	int get_num_entries() const;

	Ref<LootDataBase> get_entry(const int index) const;
	void set_entry(const int index, const Ref<LootDataBase> ldb);

	void _get_loot(Array into);

	Vector<Variant> get_entries();
	void set_entries(const Vector<Variant> &auras);

	LootDataContainter();
	~LootDataContainter();

protected:
	static void _bind_methods();

private:
	Vector<Ref<LootDataBase> > _entries;
};

#endif
