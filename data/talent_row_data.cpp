#include "talent_row_data.h"

Ref<Talent> TalentRowData::get_talent(int index) const {
	ERR_FAIL_INDEX_V(index, MAX_TALENTS_IN_ROW, Ref<Talent>(NULL));

	return _talents[index];
}

void TalentRowData::set_talent(int index, Ref<Talent> talent) {
	ERR_FAIL_INDEX(index, MAX_TALENTS_IN_ROW);

	_talents[index] = Ref<Talent>(talent);
}

TalentRowData::TalentRowData() {
}
TalentRowData::~TalentRowData() {
	for (int i = 0; i < MAX_TALENTS_IN_ROW; ++i) {
		_talents[i].unref();
	}
}

void TalentRowData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_talent", "index"), &TalentRowData::get_talent);
	ClassDB::bind_method(D_METHOD("set_talent", "index", "value"), &TalentRowData::set_talent);

	for (int i = 0; i < MAX_TALENTS_IN_ROW; ++i) {
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "Talent_" + itos(i), PROPERTY_HINT_RESOURCE_TYPE, "Talent", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_talent", "get_talent", i);
	}

	BIND_CONSTANT(MAX_TALENTS_IN_ROW);
}
