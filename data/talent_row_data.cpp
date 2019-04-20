#include "talent_row_data.h"

Ref<Talent> TalentRowData::get_talent(int index) const {
	return _talents[index];
}

void TalentRowData::set_talent(int index, Ref<Talent> talent) {
	_talents[index] = Ref<Talent>(talent);
}

Ref<Talent> TalentRowData::get_talent0() const {
	return _talents[0];
}

void TalentRowData::set_talent0(Ref<Talent> talent) {
	_talents[0] = Ref<Talent>(talent);
}

Ref<Talent> TalentRowData::get_talent1() const {
	return _talents[1];
}

void TalentRowData::set_talent1(Ref<Talent> talent) {
	_talents[1] = Ref<Talent>(talent);
}

Ref<Talent> TalentRowData::get_talent2() const {
	return _talents[2];
}

void TalentRowData::set_talent2(Ref<Talent> talent) {
	_talents[2] = Ref<Talent>(talent);
}

Ref<Talent> TalentRowData::get_talent3() const {
	return _talents[3];
}

void TalentRowData::set_talent3(Ref<Talent> talent) {
	_talents[3] = Ref<Talent>(talent);
}

Ref<Talent> TalentRowData::get_talent4() const {
	return _talents[4];
}

void TalentRowData::set_talent4(Ref<Talent> talent) {
	_talents[4] = Ref<Talent>(talent);
}

void TalentRowData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_talent", "index"), &TalentRowData::get_talent);
	ClassDB::bind_method(D_METHOD("set_talent", "index", "value"), &TalentRowData::set_talent);

	ClassDB::bind_method(D_METHOD("get_talent0"), &TalentRowData::get_talent0);
	ClassDB::bind_method(D_METHOD("set_talent0", "value"), &TalentRowData::set_talent0);

	ClassDB::bind_method(D_METHOD("get_talent1"), &TalentRowData::get_talent1);
	ClassDB::bind_method(D_METHOD("set_talent1", "value"), &TalentRowData::set_talent1);

	ClassDB::bind_method(D_METHOD("get_talent2"), &TalentRowData::get_talent2);
	ClassDB::bind_method(D_METHOD("set_talent2", "value"), &TalentRowData::set_talent2);

	ClassDB::bind_method(D_METHOD("get_talent3"), &TalentRowData::get_talent3);
	ClassDB::bind_method(D_METHOD("set_talent3", "value"), &TalentRowData::set_talent3);

	ClassDB::bind_method(D_METHOD("get_talent4"), &TalentRowData::get_talent4);
	ClassDB::bind_method(D_METHOD("set_talent4", "value"), &TalentRowData::set_talent4);


	//for (int i = 0; i < MAX_TALENTS_IN_ROW; i++) {
	//	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "Row_" + itos(i) + "/talent" + itos(i), PROPERTY_HINT_RESOURCE_TYPE, "Talent", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_talent", "get_talent", i);
	//}
}
