#include "equipment_data.h"

Ref<EquipmentDataEntry> EquipmentDataEntry::get_slot(int index) {
	ERR_FAIL_INDEX_V(index, ItemEnums::EQUIP_SLOT_EQUIP_SLOT_MAX, Ref<EquipmentDataEntry>());

	return _entries[index];
}
void EquipmentDataEntry::set_slot(int index, Ref<EquipmentDataEntry> entry) {
	ERR_FAIL_INDEX(index, ItemEnums::EQUIP_SLOT_EQUIP_SLOT_MAX);

	_entries[index] = entry;
}

EquipmentDataEntry::EquipmentDataEntry() {
}

EquipmentDataEntry::~EquipmentDataEntry() {
	for (int i = 0; i < ItemEnums::EQUIP_SLOT_EQUIP_SLOT_MAX; ++i)
		_entries[i].unref();
}

void EquipmentDataEntry::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_slot", "index"), &EquipmentDataEntry::get_slot);
	ClassDB::bind_method(D_METHOD("set_slot", "index", "entry"), &EquipmentDataEntry::set_slot);

	ADD_GROUP("Slots", "slot");
	for (int i = 0; i < ItemEnums::EQUIP_SLOT_EQUIP_SLOT_MAX; ++i) {
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "slot_" + ItemEnums::get_equip_slot_string(i), PROPERTY_HINT_RESOURCE_TYPE, "EntityData"), "sets_entity_data", "gets_entity_data", i);
	}

	
}
