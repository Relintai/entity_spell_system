#include "item_container_data.h"

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
	Vector<Variant> r;
	for (int i = 0; i < _container_datas.size(); i++) {
		r.push_back(_container_datas[i].get_ref_ptr());
	}
	return r;
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
