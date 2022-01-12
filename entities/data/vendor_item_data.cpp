/*
Copyright (c) 2019-2022 Péter Magyar

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

#include "vendor_item_data.h"

#include "../../defines.h"

int VendorItemData::get_num_vendor_datas() {
	return _vendor_datas.size();
}

Ref<VendorItemDataEntry> VendorItemData::get_vendor_data(int index) {
	ERR_FAIL_INDEX_V(index, _vendor_datas.size(), Ref<VendorItemDataEntry>());

	return _vendor_datas[index];
}
void VendorItemData::set_vendor_data(int index, Ref<VendorItemDataEntry> vendor_data) {
	ERR_FAIL_INDEX(index, _vendor_datas.size());

	_vendor_datas.set(index, vendor_data);
}

Vector<Variant> VendorItemData::get_vendor_datas() {
	VARIANT_ARRAY_GET(_vendor_datas);
}
void VendorItemData::set_vendor_datas(const Vector<Variant> &vendor_datas) {
	_vendor_datas.clear();
	for (int i = 0; i < vendor_datas.size(); i++) {
		Ref<VendorItemDataEntry> vendor_data = Ref<VendorItemDataEntry>(vendor_datas[i]);

		_vendor_datas.push_back(vendor_data);
	}
}

VendorItemData::VendorItemData() {
}
VendorItemData::~VendorItemData() {
	_vendor_datas.clear();
}

void VendorItemData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_num_vendor_datas"), &VendorItemData::get_num_vendor_datas);
	ClassDB::bind_method(D_METHOD("get_vendor_data", "index"), &VendorItemData::get_vendor_data);
	ClassDB::bind_method(D_METHOD("set_vendor_data", "index", "vendor_data"), &VendorItemData::set_vendor_data);

	ClassDB::bind_method(D_METHOD("get_vendor_datas"), &VendorItemData::get_vendor_datas);
	ClassDB::bind_method(D_METHOD("set_vendor_datas", "vendor_datas"), &VendorItemData::set_vendor_datas);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "vendor_datas", PROPERTY_HINT_NONE, "17/17:VendorItemDataEntry", PROPERTY_USAGE_DEFAULT, "VendorItemDataEntry"), "set_vendor_datas", "get_vendor_datas");
}
