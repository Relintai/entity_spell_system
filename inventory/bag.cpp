#include "bag.h"

#include "../data/item_template.h"
#include "../data/item_instance.h"

int Bag::get_allowed_item_types() const {
	return _allowed_item_types;
}

void Bag::set_allowed_item_types(const int value) {
	_allowed_item_types = value;
}

bool Bag::add_item(Ref<ItemInstance> item) {
	ERR_FAIL_COND_V(!item.is_valid(), false);

	if (has_method("_add_item")) {
		return call("_add_item", item);
	}

	int max_stack = item->get_item_template()->get_stack_size();

	if (max_stack > 1) {
		for (int i = 0; i < _items.size(); ++i) {
			Ref<ItemInstance> ii = _items.get(i);

			if (!ii.is_valid())
				continue;

			if (ii->get_stack_size() < max_stack) {
				int fs = max_stack - ii->get_stack_size();

				if (fs > item->get_stack_size()) {
					ii->set_stack_size(ii->get_stack_size() + item->get_stack_size());

					item->set_stack_size(0);

					emit_signal("item_count_changed", Ref<Bag>(this), ii, i);

					return true;
				} else {
					ii->set_stack_size(max_stack);
					item->set_stack_size(item->get_stack_size() - fs);

					emit_signal("item_count_changed", Ref<Bag>(this), ii, i);
				}
			}
		}
	}

	item->set_bag(Ref<Bag>(this));

	for (int i = 0; i < _items.size(); ++i) {
		Ref<ItemInstance> ii = _items.get(i);

		if (!ii.is_valid()) {
			_items.set(i, item);

			emit_signal("item_added", Ref<Bag>(this), item, i);

			if (get_valid_item_count() == _bag_size) {
				emit_signal("overburdened", Ref<Bag>(this));
			}

			return true;
		}
	}

	_items.push_back(item);

	emit_signal("item_added", Ref<Bag>(this), item, _items.size() - 1);

	if (get_valid_item_count() == _bag_size) {
		emit_signal("overburdened", Ref<Bag>(this));
	}

	return true;
}

Ref<ItemInstance> Bag::get_item(const int index) {
	if (has_method("_get_item")) {
		return call("_get_item", index);
	}

	ERR_FAIL_INDEX_V(index, _items.size(), Ref<ItemInstance>());

	return _items.get(index);
}

Ref<ItemInstance> Bag::remove_item(const int index) {
	if (has_method("_remove_item")) {
		return call("_remove_item", index);
	}

	ERR_FAIL_INDEX_V(index, _items.size(), Ref<ItemInstance>());

	Ref<ItemInstance> ii = _items.get(index);

	if (!ii.is_valid())
		return ii;

	ii->set_bag(Ref<Bag>());

	_items.set(index, Ref<ItemInstance>());

	emit_signal("item_removed", Ref<Bag>(this), ii, index);

	if (get_valid_item_count() + 1 == _bag_size) {
		emit_signal("overburden_removed", Ref<Bag>(this));
	}

	return ii;
}

void Bag::swap_items(const int item1_index, const int item2_index) {
	if (has_method("_swap_items")) {
		call("_swap_items", item1_index, item2_index);
		return;
	}

	ERR_FAIL_INDEX(item1_index, _items.size());
	ERR_FAIL_INDEX(item2_index, _items.size());

	Ref<ItemInstance> ii = _items.get(item1_index);

	_items.set(item1_index, _items.get(item2_index));

	_items.set(item2_index, ii);

	emit_signal("item_swapped", Ref<Bag>(this), item1_index, item2_index);
}

bool Bag::can_add_item(const Ref<ItemInstance> item) {
	if (has_method("_can_add_item")) {
		return call("_can_add_item", item);
	}

    return true;
}

int Bag::get_item_count() {
	if (has_method("_get_item_count")) {
		return call("_get_item_count");
	}

	return _items.size();
}

int Bag::get_valid_item_count() {
	if (has_method("_get_valid_item_count")) {
		return call("_get_valid_item_count");
	}

	int ii = 0;

	for (int i = 0; i < _items.size(); ++i) {
		if (_items.get(i).is_valid())
			++ii;
	}

	return ii;
}

int Bag::get_size() {
	if (has_method("_get_size")) {
		return call("_get_size");
	}

	return _bag_size;
}

void Bag::set_size(const int size) {
	if (has_method("_set_size")) {
		call("_set_size", size);
		return;
	}

	int item_count = get_valid_item_count();

	if (_bag_size > size && _bag_size > item_count && size <= item_count) {
		_bag_size = size;

		emit_signal("overburdened", Ref<Bag>(this));

		return;
	}

	_bag_size = size;
}


bool Bag::is_full() {
	if (has_method("_is_full")) {
		return call("_is_full");
	}

	return false;
}

bool Bag::is_overburdened() {
	if (has_method("_is_overburdened")) {
		return call("_is_overburdened");
	}

	return _bag_size < get_valid_item_count();
}

Dictionary Bag::to_dict() {
	return call("_to_dict");
}
void Bag::from_dict(const Dictionary &dict) {
	call("_from_dict", dict);
}

Dictionary Bag::_to_dict() {
	Dictionary dict;

	return dict;
}
void Bag::_from_dict(const Dictionary &dict) {
	_items.clear();
}

Bag::Bag() {
	_allowed_item_types = 0xFFFFFF;
	_bag_size = 0;
}

Bag::~Bag() {
	_items.clear();
}

void Bag::_bind_methods() {
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "could_add"), "_add_item", PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), "_get_item", PropertyInfo(Variant::INT, "index")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), "_remove_item", PropertyInfo(Variant::INT, "index")));
	BIND_VMETHOD(MethodInfo("_swap_items", PropertyInfo(Variant::INT, "item1_index"), PropertyInfo(Variant::INT, "item2_index")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "can"), "_can_add_item", PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::INT, "count"), "_get_item_count"));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::INT, "count"), "_get_valid_item_count"));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::INT, "size"), "_get_size"));
	BIND_VMETHOD(MethodInfo("_set_size", PropertyInfo(Variant::INT, "size")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "full"), "_is_full"));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "overburdened"), "_is_overburdened"));

	ADD_SIGNAL(MethodInfo("item_added", PropertyInfo(Variant::OBJECT, "bag", PROPERTY_HINT_RESOURCE_TYPE, "Bag"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "slot_id")));
	ADD_SIGNAL(MethodInfo("item_removed", PropertyInfo(Variant::OBJECT, "bag", PROPERTY_HINT_RESOURCE_TYPE, "Bag"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "slot_id")));
	ADD_SIGNAL(MethodInfo("item_swapped", PropertyInfo(Variant::OBJECT, "bag", PROPERTY_HINT_RESOURCE_TYPE, "Bag"), PropertyInfo(Variant::INT, "slot_id_1"), PropertyInfo(Variant::INT, "slot_id_2")));
	ADD_SIGNAL(MethodInfo("item_count_changed", PropertyInfo(Variant::OBJECT, "bag", PROPERTY_HINT_RESOURCE_TYPE, "Bag"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "slot_id")));
	ADD_SIGNAL(MethodInfo("overburdened", PropertyInfo(Variant::OBJECT, "bag", PROPERTY_HINT_RESOURCE_TYPE, "Bag")));
	ADD_SIGNAL(MethodInfo("overburden_removed", PropertyInfo(Variant::OBJECT, "bag", PROPERTY_HINT_RESOURCE_TYPE, "Bag")));

	ClassDB::bind_method(D_METHOD("get_allowed_item_types"), &Bag::get_allowed_item_types);
	ClassDB::bind_method(D_METHOD("set_allowed_item_types", "count"), &Bag::set_allowed_item_types);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "allowed_item_types", PROPERTY_HINT_FLAGS, ItemEnums::BINDING_STRING_ITEM_TYPE_FLAGS), "set_allowed_item_types", "get_allowed_item_types");
	

	ClassDB::bind_method(D_METHOD("add_item", "item"), &Bag::add_item);
	ClassDB::bind_method(D_METHOD("get_item", "index"), &Bag::get_item);
	ClassDB::bind_method(D_METHOD("remove_item", "index"), &Bag::remove_item);
    ClassDB::bind_method(D_METHOD("swap_items", "item1_index", "item2_index"), &Bag::swap_items);

    ClassDB::bind_method(D_METHOD("can_add_item", "item"), &Bag::can_add_item);
    
	ClassDB::bind_method(D_METHOD("get_item_count"), &Bag::get_item_count);
	
	ClassDB::bind_method(D_METHOD("get_size"), &Bag::get_size);
	ClassDB::bind_method(D_METHOD("set_size", "size"), &Bag::set_size);
    
    ClassDB::bind_method(D_METHOD("is_full"), &Bag::is_full);
	ClassDB::bind_method(D_METHOD("is_overburdened"), &Bag::is_overburdened);

	//Serialization
	BIND_VMETHOD(MethodInfo("_from_dict", PropertyInfo(Variant::DICTIONARY, "dict")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::DICTIONARY, "dict"), "_to_dict"));

	ClassDB::bind_method(D_METHOD("from_dict", "dict"), &Bag::from_dict);
	ClassDB::bind_method(D_METHOD("to_dict"), &Bag::to_dict);

	ClassDB::bind_method(D_METHOD("_from_dict", "dict"), &Bag::_from_dict);
	ClassDB::bind_method(D_METHOD("_to_dict"), &Bag::_to_dict);
}
