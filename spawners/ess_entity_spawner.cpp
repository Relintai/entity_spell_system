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

#include "ess_entity_spawner.h"

#include "../singletons/ess.h"

#include "../utility/entity_create_info.h"

_FORCE_INLINE_ void ESSEntitySpawner::request_entity_spawn(Ref<EntityCreateInfo> info) {
	if (has_method("_request_entity_spawn"))
		call("_request_entity_spawn", info);

	emit_signal("on_entity_spawn", info);
}
_FORCE_INLINE_ void ESSEntitySpawner::request_entity_spawn_deferred(Ref<EntityCreateInfo> info) {
	call_deferred("request_entity_spawn", info);
}

ESSEntitySpawner::ESSEntitySpawner() {
	if (ESS::get_singleton()) {
		ESS::get_singleton()->set_entity_spawner(this);
	}
}

ESSEntitySpawner::~ESSEntitySpawner() {
	if (ESS::get_singleton() && ESS::get_singleton()->get_entity_spawner() == this) {
		ESS::get_singleton()->set_entity_spawner(NULL);
	}
}

void ESSEntitySpawner::_bind_methods() {
	BIND_VMETHOD(MethodInfo("_request_entity_spawn", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "EntityCreateInfo")));
	ADD_SIGNAL(MethodInfo("on_entity_spawn", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "EntityCreateInfo")));

	ClassDB::bind_method(D_METHOD("request_entity_spawn", "info"), &ESSEntitySpawner::request_entity_spawn);
	ClassDB::bind_method(D_METHOD("request_entity_spawn_deferred", "info"), &ESSEntitySpawner::request_entity_spawn_deferred);
}
