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

#include "entity_data_container.h"

#include "core/version.h"

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
#if VERSION_MAJOR > 3
	ERR_FAIL_COND(dict.is_empty());
#else
	ERR_FAIL_COND(dict.empty());
#endif
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
