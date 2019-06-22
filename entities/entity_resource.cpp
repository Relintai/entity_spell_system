#include "entity_resource.h"

bool EntityResource::get_dirty() {
	return _dirty;
}
void EntityResource::set_dirty(bool value) {
	_dirty = value;
}

bool EntityResource::get_should_process() {
	return _should_process;
}
void EntityResource::set_should_process(bool value) {
	_should_process = value;
}

void EntityResource::process(float delta) {
	ERR_FAIL_COND(!has_method("_process"));

	call("_process");
}

EntityResource::EntityResource() {
	_dirty = false;

	_should_process = has_method("_process");
}

void EntityResource::_bind_methods() {
	ADD_SIGNAL(MethodInfo("starget_changed", PropertyInfo(Variant::OBJECT, "Entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	ADD_SIGNAL(MethodInfo("ctarget_changed", PropertyInfo(Variant::OBJECT, "Entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	BIND_VMETHOD(MethodInfo("_process", PropertyInfo(Variant::REAL, "delta")));

	ClassDB::bind_method(D_METHOD("process", "delta"), &EntityResource::process);

	ClassDB::bind_method(D_METHOD("get_dirty"), &EntityResource::get_dirty);
	ClassDB::bind_method(D_METHOD("set_dirty", "value"), &EntityResource::set_dirty);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "dirty"), "set_dirty", "get_dirty");

	ClassDB::bind_method(D_METHOD("get_should_process"), &EntityResource::get_should_process);
	ClassDB::bind_method(D_METHOD("set_should_process", "value"), &EntityResource::set_should_process);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "should_process"), "set_should_process", "get_should_process");
}
