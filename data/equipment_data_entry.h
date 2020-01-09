#ifndef EQUIPMENT_DATA_ENTRY_H
#define EQUIPMENT_DATA_ENTRY_H

#include "core/resource.h"

#include "item_instance.h"

class ItemInstance;

class EquipmentDataEntry : public Resource {
	GDCLASS(EquipmentDataEntry, Resource);

public:
	Ref<ItemInstance> get_item();

	EquipmentDataEntry();
	~EquipmentDataEntry();

protected:
	static void _bind_methods();

	//private:
};

#endif
