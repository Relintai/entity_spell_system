/*
Copyright (c) 2019-2020 Péter Magyar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "equipment_data.h"

Ref<EquipmentDataEntry> EquipmentData::get_slot(int index) {
	ERR_FAIL_INDEX_V(index, ItemEnums::EQUIP_SLOT_EQUIP_SLOT_MAX, Ref<EquipmentDataEntry>());

	return _entries[index];
}
void EquipmentData::set_slot(int index, Ref<EquipmentDataEntry> entry) {
	ERR_FAIL_INDEX(index, ItemEnums::EQUIP_SLOT_EQUIP_SLOT_MAX);

	_entries[index] = entry;
}

Ref<ItemInstance> EquipmentData::get_item(int index) {
	ERR_FAIL_INDEX_V(index, ItemEnums::EQUIP_SLOT_EQUIP_SLOT_MAX, Ref<ItemInstance>());

	Ref<EquipmentDataEntry> ede = _entries[index];

	if (!ede.is_valid())
		return Ref<ItemInstance>();

	return ede->get_item();
}

EquipmentData::EquipmentData() {
}

EquipmentData::~EquipmentData() {
	for (int i = 0; i < ItemEnums::EQUIP_SLOT_EQUIP_SLOT_MAX; ++i)
		_entries[i].unref();
}

void EquipmentData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_slot", "index"), &EquipmentData::get_slot);
	ClassDB::bind_method(D_METHOD("set_slot", "index", "entry"), &EquipmentData::set_slot);

	ADD_GROUP("Slots", "slot");
	for (int i = 0; i < ItemEnums::EQUIP_SLOT_EQUIP_SLOT_MAX; ++i) {
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "slot_" + ItemEnums::get_equip_slot_string(i), PROPERTY_HINT_RESOURCE_TYPE, "EquipmentDataEntry"), "set_slot", "get_slot", i);
	}
}
