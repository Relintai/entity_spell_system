#ifndef VENDOR_ITEM_DATA_H
#define VENDOR_ITEM_DATA_H

#include "core/resource.h"

#include "vendor_item_data_entry.h"

class VendorItemData : public Resource {
	GDCLASS(VendorItemData, Resource);

public:
	//Vendor data
	int get_num_vendor_datas();
	void set_num_vendor_datas(int value);

	Ref<VendorItemDataEntry> get_vendor_data(int index);
	void set_vendor_data(int index, Ref<VendorItemDataEntry> data);

	Vector<Variant> get_vendor_datas();
	void set_vendor_datas(const Vector<Variant> &data);

	VendorItemData();
	~VendorItemData();

protected:
	static void _bind_methods();

private:
	Vector<Ref<VendorItemData> > _vendor_datas;
};

#endif
