#ifndef ITEM_CONTAINER_DATA_H
#define ITEM_CONTAINER_DATA_H

#include "core/resource.h"

#include "item_container_data_entry.h"

class ItemContainerData : public Resource {
	GDCLASS(ItemContainerData, Resource);

public:
	int get_num_container_datas();
	void set_num_container_datas(int value);

	Ref<ItemContainerDataEntry> get_container_data(int index);
	void set_container_data(int index, Ref<ItemContainerDataEntry> aura);

	Vector<Variant> get_container_datas();
	void set_container_datas(const Vector<Variant> &ai_actions);

	ItemContainerData();
	~ItemContainerData();

protected:
	static void _bind_methods();

private:
	Vector<Ref<ItemContainerDataEntry> > _container_datas;
};

#endif
