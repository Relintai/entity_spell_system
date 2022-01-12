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

#include "item_container_data.h"

#include "../../defines.h"

int ItemContainerData::get_num_container_datas() {
	return _container_datas.size();
}
void ItemContainerData::set_num_container_datas(int value) {
	_container_datas.resize(value);
}

Ref<ItemContainerDataEntry> ItemContainerData::get_container_data(int index) {
	ERR_FAIL_INDEX_V(index, _container_datas.size(), Ref<ItemContainerDataEntry>());

	return _container_datas[index];
}
void ItemContainerData::set_container_data(int index, Ref<ItemContainerDataEntry> container_data) {
	ERR_FAIL_INDEX(index, _container_datas.size());

	_container_datas.set(index, container_data);
}

Vector<Variant> ItemContainerData::get_container_datas() {
	VARIANT_ARRAY_GET(_container_datas);
}
void ItemContainerData::set_container_datas(const Vector<Variant> &container_datas) {
	_container_datas.clear();
	for (int i = 0; i < container_datas.size(); i++) {
		Ref<ItemContainerDataEntry> container_data = Ref<ItemContainerDataEntry>(container_datas[i]);

		_container_datas.push_back(container_data);
	}
}

ItemContainerData::ItemContainerData() {
}

ItemContainerData::~ItemContainerData() {
	_container_datas.clear();
}

void ItemContainerData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_num_container_datas"), &ItemContainerData::get_num_container_datas);
	ClassDB::bind_method(D_METHOD("set_num_container_datas", "value"), &ItemContainerData::set_num_container_datas);

	ClassDB::bind_method(D_METHOD("get_container_data", "index"), &ItemContainerData::get_container_data);
	ClassDB::bind_method(D_METHOD("set_container_data", "index", "container_data"), &ItemContainerData::set_container_data);

	ClassDB::bind_method(D_METHOD("get_container_datas"), &ItemContainerData::get_container_datas);
	ClassDB::bind_method(D_METHOD("set_container_datas", "container_datas"), &ItemContainerData::set_container_datas);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "container_datas", PROPERTY_HINT_NONE, "17/17:ItemContainerDataEntry", PROPERTY_USAGE_DEFAULT, "ItemContainerDataEntry"), "set_container_datas", "get_container_datas");
}
