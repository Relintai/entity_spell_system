#include "loot_data_container.h"

Ref<LootDataBase> LootDataContainter::get_entry(int index) const {
	ERR_FAIL_INDEX_V(index, MAX_ENTRIES, Ref<LootDataBase>(NULL));

	return _entries[index];
}
void LootDataContainter::set_entry(const int index, const Ref<LootDataBase> ldb) {
	ERR_FAIL_INDEX(index, MAX_ENTRIES);

	_entries[index] = ldb;
}

void LootDataContainter::_get_loot(Array into) {
	for (int i = 0; i < MAX_ENTRIES; ++i) {
		if (_entries[i].is_valid()) {
			_entries[i]->get_loot(into);
		}
	}
}

LootDataContainter::LootDataContainter() {
}

void LootDataContainter::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_get_loot", "into"), &LootDataContainter::_get_loot);

	ClassDB::bind_method(D_METHOD("get_entry", "index"), &LootDataContainter::get_entry);
	ClassDB::bind_method(D_METHOD("set_entry", "index", "ldb"), &LootDataContainter::set_entry);

	for (int i = 0; i < MAX_ENTRIES; ++i) {
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "entry_" + itos(i), PROPERTY_HINT_RESOURCE_TYPE, "LootDataBase", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_entry", "get_entry", i);
	}

	BIND_CONSTANT(MAX_ENTRIES);
}
