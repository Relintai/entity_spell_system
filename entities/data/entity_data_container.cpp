#include "entity_data_container.h"

Dictionary EntityDataContainer::to_dict() {
	return call("_to_dict");
}
void EntityDataContainer::from_dict(const Dictionary &dict) {
	call("_from_dict", dict);
}

Dictionary EntityDataContainer::_to_dict() {
	Dictionary dict;

	dict["class_name"] = get_class_static();

	return dict;
}
void EntityDataContainer::_from_dict(const Dictionary &dict) {
	ERR_FAIL_COND(dict.empty());

}

EntityDataContainer::EntityDataContainer() {
}
EntityDataContainer::~EntityDataContainer() {
}

void EntityDataContainer::_bind_methods() {
	//Serialization
	BIND_VMETHOD(MethodInfo("_from_dict", PropertyInfo(Variant::DICTIONARY, "dict")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::DICTIONARY, "dict"), "_to_dict"));

	ClassDB::bind_method(D_METHOD("from_dict", "dict"), &EntityDataContainer::from_dict);
	ClassDB::bind_method(D_METHOD("to_dict"), &EntityDataContainer::to_dict);

	ClassDB::bind_method(D_METHOD("_from_dict", "dict"), &EntityDataContainer::_from_dict);
	ClassDB::bind_method(D_METHOD("_to_dict"), &EntityDataContainer::_to_dict);
}
