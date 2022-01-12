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

#include "species_instance.h"

#include "core/version.h"

#include "../../database/ess_resource_db.h"
#include "../../singletons/ess.h"

#include "entity_species_data.h"

int SpeciesInstance::get_id() const {
	return _id;
}
void SpeciesInstance::set_id(const int value) {
	_id = value;
}

int SpeciesInstance::get_species_id() const {
	return _species_id;
}
void SpeciesInstance::set_species_id(int value) {
	_id = value;

	_species = ESS::get_singleton()->get_resource_db()->get_entity_species_data(_id);
}

StringName SpeciesInstance::get_species_path() const {
	return _path;
}
void SpeciesInstance::set_species_path(const StringName &value) {
	_path = value;

	_species = ESS::get_singleton()->get_resource_db()->get_entity_species_data_path(_path);
}

Ref<EntitySpeciesData> SpeciesInstance::get_species() {
	return _species;
}
void SpeciesInstance::set_species(const Ref<EntitySpeciesData> &value) {
	_species = value;

	if (_species.is_valid()) {
		_path = _species->get_path();
	} else {
		_path = "";
	}
}

int SpeciesInstance::get_skin_color_index() const {
	return _skin_color_index;
}
void SpeciesInstance::set_skin_color_index(const int value) {
	_skin_color_index = value;
}

int SpeciesInstance::get_hair_style_index() const {
	return _hair_style_index;
}
void SpeciesInstance::set_hair_style_index(const int value) {
	_hair_style_index = value;
}

int SpeciesInstance::get_hair_color_index() const {
	return _hair_color_index;
}
void SpeciesInstance::set_hair_color_index(const int value) {
	_hair_color_index = value;
}

int SpeciesInstance::get_head_index() const {
	return _head_index;
}
void SpeciesInstance::set_head_index(const int value) {
	_head_index = value;
}

Dictionary SpeciesInstance::to_dict() {
	return call("_to_dict");
}
void SpeciesInstance::from_dict(const Dictionary &dict) {
	call("_from_dict", dict);
}

Dictionary SpeciesInstance::_to_dict() {
	Dictionary dict;

	dict["id"] = _id;
	dict["species_path"] = _path;
	dict["skin_color_index"] = _skin_color_index;
	dict["hair_style_index"] = _hair_style_index;
	dict["_hair_color_index"] = _hair_color_index;
	dict["head_index"] = _head_index;

	return dict;
}
void SpeciesInstance::_from_dict(const Dictionary &dict) {
#if VERSION_MAJOR > 3
	ERR_FAIL_COND(dict.is_empty());
#else
	ERR_FAIL_COND(dict.empty());
#endif

	_id = dict.get("id", 0);
	set_species_path(dict.get("species_path", ""));
	_skin_color_index = dict.get("skin_color_index", 0);
	_hair_style_index = dict.get("hair_style_index", 0);
	_hair_color_index = dict.get("hair_color_index", 0);
	_head_index = dict.get("head_index", 0);
}

SpeciesInstance::SpeciesInstance() {
	_id = 0;
	_species_id = 0;
	_skin_color_index = 0;
	_hair_style_index = 0;
	_hair_color_index = 0;
	_head_index = 0;
}
SpeciesInstance::~SpeciesInstance() {
	_species.unref();
}

void SpeciesInstance::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_id"), &SpeciesInstance::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &SpeciesInstance::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ClassDB::bind_method(D_METHOD("get_species_id"), &SpeciesInstance::get_species_id);
	ClassDB::bind_method(D_METHOD("set_species_id", "value"), &SpeciesInstance::set_species_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "species_id"), "set_species_id", "get_species_id");

	ClassDB::bind_method(D_METHOD("get_species"), &SpeciesInstance::get_species);
	ClassDB::bind_method(D_METHOD("set_species", "value"), &SpeciesInstance::set_species);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "species", PROPERTY_HINT_RESOURCE_TYPE, "EntitySpeciesData"), "set_species", "get_species");

	ClassDB::bind_method(D_METHOD("get_skin_color_index"), &SpeciesInstance::get_skin_color_index);
	ClassDB::bind_method(D_METHOD("set_skin_color_index", "value"), &SpeciesInstance::set_skin_color_index);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "skin_color_index"), "set_skin_color_index", "get_skin_color_index");

	ClassDB::bind_method(D_METHOD("get_hair_style_index"), &SpeciesInstance::get_hair_style_index);
	ClassDB::bind_method(D_METHOD("set_hair_style_index", "value"), &SpeciesInstance::set_hair_style_index);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "hair_style_index"), "set_hair_style_index", "get_hair_style_index");

	ClassDB::bind_method(D_METHOD("get_hair_color_index"), &SpeciesInstance::get_hair_color_index);
	ClassDB::bind_method(D_METHOD("set_hair_color_index", "value"), &SpeciesInstance::set_hair_color_index);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "hair_color_index"), "set_hair_color_index", "get_hair_color_index");

	ClassDB::bind_method(D_METHOD("get_head_index"), &SpeciesInstance::get_head_index);
	ClassDB::bind_method(D_METHOD("set_head_index", "value"), &SpeciesInstance::set_head_index);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "head_index"), "set_head_index", "get_head_index");

	//Serialization
	BIND_VMETHOD(MethodInfo("_from_dict", PropertyInfo(Variant::DICTIONARY, "dict")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::DICTIONARY, "dict"), "_to_dict"));

	ClassDB::bind_method(D_METHOD("from_dict", "dict"), &SpeciesInstance::from_dict);
	ClassDB::bind_method(D_METHOD("to_dict"), &SpeciesInstance::to_dict);

	ClassDB::bind_method(D_METHOD("_from_dict", "dict"), &SpeciesInstance::_from_dict);
	ClassDB::bind_method(D_METHOD("_to_dict"), &SpeciesInstance::_to_dict);
}
