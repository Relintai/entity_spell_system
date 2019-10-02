#include "loot_data_container.h"

int LootDataContainter::get_num_entries() const {
	return _entries.size();
}

Ref<LootDataBase> LootDataContainter::get_entry(int index) const {
	ERR_FAIL_INDEX_V(index, _entries.size(), Ref<LootDataBase>(NULL));

	return _entries.get(index);
}
void LootDataContainter::set_entry(const int index, const Ref<LootDataBase> ldb) {
	ERR_FAIL_INDEX(index, _entries.size());

	_entries.set(index, ldb);
}

void LootDataContainter::_get_loot(Array into) {
	for (int i = 0; i < _entries.size(); ++i) {
		if (_entries[i].is_valid()) {
			_entries.get(i)->get_loot(into);
		}
	}
}

Vector<Variant> LootDataContainter::get_entries() {
	Vector<Variant> r;
	for (int i = 0; i < _entries.size(); i++) {
		r.push_back(_entries[i].get_ref_ptr());
	}
	return r;
}
void LootDataContainter::set_entries(const Vector<Variant> &entries) {
	_entries.clear();
	for (int i = 0; i < entries.size(); i++) {
		Ref<LootDataBase> entry = Ref<LootDataBase>(entries[i]);

		_entries.push_back(entry);
	}
}

LootDataContainter::LootDataContainter() {
}
LootDataContainter::~LootDataContainter() {
	_entries.clear();
}

void LootDataContainter::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_get_loot", "into"), &LootDataContainter::_get_loot);

	ClassDB::bind_method(D_METHOD("get_num_entries"), &LootDataContainter::get_num_entries);

	ClassDB::bind_method(D_METHOD("get_entry", "index"), &LootDataContainter::get_entry);
	ClassDB::bind_method(D_METHOD("set_entry", "index", "ldb"), &LootDataContainter::set_entry);

	ClassDB::bind_method(D_METHOD("get_entries"), &LootDataContainter::get_entries);
	ClassDB::bind_method(D_METHOD("set_entries", "auras"), &LootDataContainter::set_entries);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "entries", PROPERTY_HINT_NONE, "17/17:LootDataBase", PROPERTY_USAGE_DEFAULT, "LootDataBase"), "set_entries", "get_entries");
}
