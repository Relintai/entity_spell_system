#include "equipment_data_entry.h"

Ref<ItemInstance> EquipmentDataEntry::get_item() {
	if (has_method("_get_item")) {
		return call("_get_item");
	}

	return Ref<ItemInstance>();
}

EquipmentDataEntry::EquipmentDataEntry() {
}

EquipmentDataEntry::~EquipmentDataEntry() {
}

void EquipmentDataEntry::_bind_methods() {
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), "_get_item"));

	ClassDB::bind_method(D_METHOD("get_item"), &EquipmentDataEntry::get_item);
}
