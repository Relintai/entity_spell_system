#include "talent_row_data.h"

Ref<Talent> TalentRowData::get_talent_index(int index) const {
	ERR_FAIL_INDEX_V(index, TOTAL_ENTRIES, Ref<Talent>());

	return _talents[index];
}

void TalentRowData::set_talent_index(int index, Ref<Talent> talent) {
	ERR_FAIL_INDEX(index, TOTAL_ENTRIES);

	_talents[index] = Ref<Talent>(talent);
}

Ref<Talent> TalentRowData::get_talent(int culomn, int rank) const {
	ERR_FAIL_INDEX_V(culomn, MAX_TALENTS_IN_ROW, Ref<Talent>());
	ERR_FAIL_INDEX_V(rank, MAX_TALENTS_PER_ENTRY, Ref<Talent>());

	return _talents[culomn * MAX_TALENTS_IN_ROW + rank];
}
void TalentRowData::set_talent(int culomn, int rank, Ref<Talent> talent) {
	ERR_FAIL_INDEX(culomn, MAX_TALENTS_IN_ROW);
	ERR_FAIL_INDEX(rank, MAX_TALENTS_PER_ENTRY);

	_talents[culomn * MAX_TALENTS_IN_ROW + rank] = talent;
}

bool TalentRowData::has_talent_with_id(int id) {
	for (int i = 0; i < TOTAL_ENTRIES; ++i) {
		if (_talents[i].is_valid() && _talents[i]->get_id() == id)
			return true;
	}

	return false;
}

Ref<Talent> TalentRowData::get_talent_with_id(int id) {
	for (int i = 0; i < TOTAL_ENTRIES; ++i) {
		if (_talents[i].is_valid() && _talents[i]->get_id() == id)
			return _talents[i];
	}

	return Ref<Talent>();
}

TalentRowData::TalentRowData() {
}
TalentRowData::~TalentRowData() {
	for (int i = 0; i < TOTAL_ENTRIES; ++i) {
		_talents[i].unref();
	}
}

void TalentRowData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_talent_index", "index"), &TalentRowData::get_talent_index);
	ClassDB::bind_method(D_METHOD("set_talent_index", "index", "value"), &TalentRowData::set_talent_index);

	ClassDB::bind_method(D_METHOD("get_talent", "culomn", "rank"), &TalentRowData::get_talent);
	ClassDB::bind_method(D_METHOD("set_talent", "culomn", "rank", "talent"), &TalentRowData::set_talent);

	ClassDB::bind_method(D_METHOD("has_talent_with_id", "id"), &TalentRowData::has_talent_with_id);
	ClassDB::bind_method(D_METHOD("get_talent_with_id", "id"), &TalentRowData::get_talent_with_id);

	for (int i = 0; i < MAX_TALENTS_IN_ROW; ++i) {
		for (int j = 0; j < MAX_TALENTS_PER_ENTRY; ++j) {
			ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "Talent_" + itos(i) + "_" + itos(j), PROPERTY_HINT_RESOURCE_TYPE, "Talent", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_talent_index", "get_talent_index", i * MAX_TALENTS_IN_ROW + j);
		}
	}

	BIND_CONSTANT(MAX_TALENTS_IN_ROW);
	BIND_CONSTANT(MAX_TALENTS_PER_ENTRY);
	BIND_CONSTANT(TOTAL_ENTRIES);
}
