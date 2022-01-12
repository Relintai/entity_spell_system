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

#include "species_model_data.h"

#include "core/version.h"

#include "../../defines.h"
#include "../../singletons/ess.h"

#if VERSION_MAJOR > 3
#include "core/string/ustring.h"
#else
#include "core/ustring.h"
#endif


int SpeciesModelData::get_id() {
	return _id;
}
void SpeciesModelData::set_id(int value) {
	_id = value;
}

int SpeciesModelData::get_bone_structure() const {
	return _bone_structure;
}
void SpeciesModelData::set_bone_structure(const int value) {
	_bone_structure = value;
}

Ref<PackedScene> SpeciesModelData::get_body() {
	return _body;
}
void SpeciesModelData::set_body(Ref<PackedScene> value) {
	_body = value;
}

//Entries

Ref<ModelVisualEntry> SpeciesModelData::get_visual(const int index) const {
	ERR_FAIL_INDEX_V(index, _visuals.size(), Ref<ModelVisualEntry>());

	return _visuals.get(index);
}
void SpeciesModelData::set_visual(const int index, const Ref<ModelVisualEntry> visual) {
	ERR_FAIL_INDEX(index, _visuals.size());

	_visuals.set(index, visual);
}
void SpeciesModelData::add_visual(const Ref<ModelVisualEntry> &visual) {
	_visuals.push_back(visual);
}
void SpeciesModelData::remove_visual(const int index) {
	ERR_FAIL_INDEX(index, _visuals.size());

	_visuals.remove(index);
}

int SpeciesModelData::get_visual_count() const {
	return _visuals.size();
}

Vector<Variant> SpeciesModelData::get_visuals() {
	VARIANT_ARRAY_GET(_visuals);
}
void SpeciesModelData::set_visuals(const Vector<Variant> &visuals) {
	VARIANT_ARRAY_SET(visuals, _visuals, ModelVisualEntry);
}

//Customizable Slots
String SpeciesModelData::get_customizable_slots_string() const {
	return _customizable_slots_string;
}
void SpeciesModelData::set_customizable_slots_string(const String &value) {
	_customizable_slots_string = value;

	if (value == "") {
		_customizable_slots.resize(0);
		return;
	}

	_customizable_slots.resize(_customizable_slots_string.get_slice_count(","));
}

Ref<ModelVisualEntry> SpeciesModelData::get_customizable_slot_entry(const int slot_index, const int index) const {
	ERR_FAIL_INDEX_V(slot_index, _customizable_slots.size(), Ref<ModelVisualEntry>());
	ERR_FAIL_INDEX_V(index, _customizable_slots[slot_index].size(), Ref<ModelVisualEntry>());

	return _customizable_slots[slot_index].get(index);
}
void SpeciesModelData::set_customizable_slot_entry(const int slot_index, const int index, const Ref<ModelVisualEntry> customizable_slot) {
	ERR_FAIL_INDEX(slot_index, _customizable_slots.size());
	ERR_FAIL_INDEX(index, _customizable_slots[slot_index].size());

	_customizable_slots.write[slot_index].set(index, customizable_slot);
}
void SpeciesModelData::add_customizable_slot_entry(const int slot_index, const Ref<ModelVisualEntry> customizable_slot) {
	ERR_FAIL_INDEX(slot_index, _customizable_slots.size());

	_customizable_slots.write[slot_index].push_back(customizable_slot);
}
void SpeciesModelData::remove_customizable_slot_entry(const int slot_index, const int index) {
	ERR_FAIL_INDEX(slot_index, _customizable_slots.size());
	ERR_FAIL_INDEX(index, _customizable_slots.size());

	_customizable_slots.write[slot_index].remove(index);
}

int SpeciesModelData::get_customizable_slot_count() const {
	return _customizable_slots.size();
}

int SpeciesModelData::get_customizable_slot_entry_count(const int slot_index) const {
	ERR_FAIL_INDEX_V(slot_index, _customizable_slots.size(), 0);

	return _customizable_slots[slot_index].size();
}

Vector<Variant> SpeciesModelData::get_customizable_slot_entries(const int slot_index) const {
	Vector<Variant> r;

	ERR_FAIL_INDEX_V(slot_index, _customizable_slots.size(), r);

	for (int i = 0; i < _customizable_slots[slot_index].size(); i++) {
#if GODOT4
		r.push_back(_customizable_slots[slot_index][i]);
#else
		r.push_back(_customizable_slots[slot_index][i].get_ref_ptr());
#endif
	}
	return r;
}
void SpeciesModelData::set_customizable_slot_entries(const int slot_index, const Vector<Variant> &customizable_slots) {
	ERR_FAIL_INDEX(slot_index, _customizable_slots.size());

	_customizable_slots.write[slot_index].clear();
	for (int i = 0; i < customizable_slots.size(); i++) {
		Ref<ModelVisualEntry> e = Ref<ModelVisualEntry>(customizable_slots[i]);
		_customizable_slots.write[slot_index].push_back(e);
	}
}

//Color Customizable Slots
String SpeciesModelData::get_customizable_color_slots_string() const {
	return _customizable_color_slots_string;
}
void SpeciesModelData::set_customizable_color_slots_string(const String &value) {
	_customizable_color_slots_string = value;

	if (value == "") {
		_visuals.resize(0);
		return;
	}

	_customizable_color_slots.resize(_customizable_color_slots_string.get_slice_count(","));
}

Color SpeciesModelData::get_color_customizable_slot_color(const int slot_index, const int index) const {
	ERR_FAIL_INDEX_V(slot_index, _customizable_color_slots.size(), Color());
	ERR_FAIL_INDEX_V(index, _customizable_color_slots.size(), Color());

	return _customizable_color_slots[slot_index].colors.get(index);
}
void SpeciesModelData::set_color_customizable_slot_color(const int slot_index, const int index, const Color color_customizable_slot) {
	ERR_FAIL_INDEX(slot_index, _customizable_color_slots.size());
	ERR_FAIL_INDEX(index, _customizable_color_slots[slot_index].colors.size());

	_customizable_color_slots.write[slot_index].colors.set(index, color_customizable_slot);
}
void SpeciesModelData::add_color_customizable_slot_color(const int slot_index, const Color color_customizable_slot) {
	ERR_FAIL_INDEX(slot_index, _customizable_color_slots.size());

	_customizable_color_slots.write[slot_index].colors.push_back(color_customizable_slot);
}
void SpeciesModelData::remove_color_customizable_slot_color(const int slot_index, const int index) {
	ERR_FAIL_INDEX(slot_index, _customizable_color_slots.size());
	ERR_FAIL_INDEX(index, _customizable_color_slots.size());

	_customizable_color_slots.write[slot_index].colors.remove(index);
}

Vector<Color> SpeciesModelData::get_color_customizable_slot_colors(const int slot_index) const {
	ERR_FAIL_INDEX_V(slot_index, _customizable_color_slots.size(), Vector<Color>());

	return _customizable_color_slots[slot_index].colors;
}
void SpeciesModelData::set_color_customizable_slot_colors(const int slot_index, const Vector<Color> &colors) {
	ERR_FAIL_INDEX(slot_index, _customizable_color_slots.size());

	_customizable_color_slots.write[slot_index].colors = colors;
}

uint64_t SpeciesModelData::get_color_customizable_slot_bone_slot_mask(const int slot_index) const {
	ERR_FAIL_INDEX_V(slot_index, _customizable_color_slots.size(), 0);

	return _customizable_color_slots[slot_index].bone_slot_mask;
}
void SpeciesModelData::set_color_customizable_slot_bone_slot_mask(const int slot_index, const uint64_t value) {
	ERR_FAIL_INDEX(slot_index, _customizable_color_slots.size());

	_customizable_color_slots.write[slot_index].bone_slot_mask = value;
}

int SpeciesModelData::get_color_customizable_slot_texture_layer(const int slot_index) const {
	ERR_FAIL_INDEX_V(slot_index, _customizable_color_slots.size(), 0);

	return _customizable_color_slots[slot_index].texture_layer;
}
void SpeciesModelData::set_color_customizable_slot_texture_layer(const int slot_index, const int value) {
	ERR_FAIL_INDEX(slot_index, _customizable_color_slots.size());

	_customizable_color_slots.write[slot_index].texture_layer = value;
}

int SpeciesModelData::get_color_customizable_count() const {
	return _customizable_color_slots.size();
}

int SpeciesModelData::get_color_customizable_slot_count(const int slot_index) const {
	ERR_FAIL_INDEX_V(slot_index, _customizable_color_slots.size(), 0);

	return _customizable_color_slots[slot_index].colors.size();
}

SpeciesModelData::SpeciesModelData() {
	_id = 0;
	_bone_structure = 0;
}
SpeciesModelData::~SpeciesModelData() {
	_body.unref();

	_visuals.clear();

	for (int i = 0; i < _customizable_slots.size(); ++i) {
		_customizable_slots.write[i].clear();
	}

	for (int i = 0; i < _customizable_color_slots.size(); ++i) {
		_customizable_color_slots.write[i].colors.clear();
	}

	_customizable_slots.clear();
	_customizable_color_slots.clear();
}

bool SpeciesModelData::_set(const StringName &p_name, const Variant &p_value) {
	String name = p_name;

	if (name.begins_with("customizable_slots")) {
		int index = name.get_slicec('/', 1).get_slicec('_', 0).to_int();

		if (_customizable_slots.size() <= index) {
			_customizable_slots.resize(index + 1);
		}

		set_customizable_slot_entries(index, p_value);

		return true;
	} else if (name.begins_with("customizable_color_slots")) {
		int index = name.get_slicec('/', 1).get_slicec('_', 0).to_int();

		if (_customizable_color_slots.size() <= index) {
			_customizable_color_slots.resize(index + 1);
		}

		String prop = name.get_slicec('/', 2);

		if (prop == "texture_layer") {
			_customizable_color_slots.write[index].texture_layer = p_value;
			return true;
		} else if (prop == "bone_slot_mask") {
			_customizable_color_slots.write[index].bone_slot_mask = p_value;
			return true;
		} else if (prop == "colors") {
			_customizable_color_slots.write[index].colors = p_value;
			return true;
		}

		return false;
	}

	return false;
}
bool SpeciesModelData::_get(const StringName &p_name, Variant &r_ret) const {
	String name = p_name;

	if (name.begins_with("customizable_slots")) {
		int index = name.get_slicec('/', 1).get_slicec('_', 0).to_int();

		if (_customizable_slots.size() <= index) {
			return false;
		}

		r_ret = get_customizable_slot_entries(index);
		return true;
	} else if (name.begins_with("customizable_color_slots")) {
		int index = name.get_slicec('/', 1).get_slicec('_', 0).to_int();

		if (_customizable_color_slots.size() <= index) {
			return false;
		}

		String prop = name.get_slicec('/', 2);

		if (prop == "texture_layer") {
			r_ret = _customizable_color_slots[index].texture_layer;
			return true;
		} else if (prop == "bone_slot_mask") {
			r_ret = _customizable_color_slots[index].bone_slot_mask;
			return true;
		} else if (prop == "colors") {
			r_ret = _customizable_color_slots[index].colors;
			return true;
		}

		return false;
	}

	return false;
}
void SpeciesModelData::_get_property_list(List<PropertyInfo> *p_list) const {
	int count = _customizable_slots_string.get_slice_count(",");

	for (int i = 0; i < count; ++i) {
		p_list->push_back(PropertyInfo(Variant::ARRAY, "customizable_slots/" + itos(i) + "_" + _customizable_slots_string.get_slicec(',', i), PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL, "ModelVisualEntry"));
	}

	count = _customizable_color_slots_string.get_slice_count(",");

	for (int i = 0; i < count; ++i) {
		p_list->push_back(PropertyInfo(Variant::INT, "customizable_color_slots/" + itos(i) + "_" + _customizable_color_slots_string.get_slicec(',', i) + "/texture_layer", PROPERTY_HINT_ENUM, ESS::get_singleton()->texture_layers_get(), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED));
		p_list->push_back(PropertyInfo(Variant::INT, "customizable_color_slots/" + itos(i) + "_" + _customizable_color_slots_string.get_slicec(',', i) + "/bone_slot_mask", PROPERTY_HINT_FLAGS, ESS::get_singleton()->skeletons_bones_index_get(_bone_structure), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL));
		p_list->push_back(PropertyInfo(Variant::ARRAY, "customizable_color_slots/" + itos(i) + "_" + _customizable_color_slots_string.get_slicec(',', i) + "/colors", PROPERTY_HINT_NONE, "17/17:Color", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL, "Color"));
	}
}
void SpeciesModelData::_validate_property(PropertyInfo &property) const {
	String prop = property.name;

	if (prop == "bone_structure") {
		property.hint_string = ESS::get_singleton()->entity_types_get();
	}
}

void SpeciesModelData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_id"), &SpeciesModelData::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &SpeciesModelData::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ClassDB::bind_method(D_METHOD("get_bone_structure"), &SpeciesModelData::get_bone_structure);
	ClassDB::bind_method(D_METHOD("set_bone_structure", "value"), &SpeciesModelData::set_bone_structure);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "bone_structure", PROPERTY_HINT_ENUM, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_bone_structure", "get_bone_structure");

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_name"), "set_name", "get_name");

	ClassDB::bind_method(D_METHOD("get_body"), &SpeciesModelData::get_body);
	ClassDB::bind_method(D_METHOD("set_body", "value"), &SpeciesModelData::set_body);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "body", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_body", "get_body");

	//Entries
	ClassDB::bind_method(D_METHOD("get_visual", "index"), &SpeciesModelData::get_visual);
	ClassDB::bind_method(D_METHOD("set_visual", "index", "data"), &SpeciesModelData::set_visual);
	ClassDB::bind_method(D_METHOD("add_visual", "visual"), &SpeciesModelData::add_visual);
	ClassDB::bind_method(D_METHOD("remove_visual", "index"), &SpeciesModelData::remove_visual);

	ClassDB::bind_method(D_METHOD("get_visual_count"), &SpeciesModelData::get_visual_count);

	ClassDB::bind_method(D_METHOD("get_visuals"), &SpeciesModelData::get_visuals);
	ClassDB::bind_method(D_METHOD("set_visuals", "visuals"), &SpeciesModelData::set_visuals);

	//Customizable Slots
	ClassDB::bind_method(D_METHOD("get_customizable_slots_string"), &SpeciesModelData::get_customizable_slots_string);
	ClassDB::bind_method(D_METHOD("set_customizable_slots_string", "value"), &SpeciesModelData::set_customizable_slots_string);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "customizable_slots_string"), "set_customizable_slots_string", "get_customizable_slots_string");

	ClassDB::bind_method(D_METHOD("get_customizable_slot_entry", "slot_index", "index"), &SpeciesModelData::get_customizable_slot_entry);
	ClassDB::bind_method(D_METHOD("set_customizable_slot_entry", "slot_index", "index", "data"), &SpeciesModelData::set_customizable_slot_entry);
	ClassDB::bind_method(D_METHOD("add_customizable_slot_entry", "slot_index", "customizable_slot"), &SpeciesModelData::add_customizable_slot_entry);
	ClassDB::bind_method(D_METHOD("remove_customizable_slot_entry", "slot_index", "index"), &SpeciesModelData::remove_customizable_slot_entry);

	ClassDB::bind_method(D_METHOD("get_customizable_slot_count"), &SpeciesModelData::get_customizable_slot_count);
	ClassDB::bind_method(D_METHOD("get_customizable_slot_entry_count", "slot_index"), &SpeciesModelData::get_customizable_slot_entry_count);

	ClassDB::bind_method(D_METHOD("get_customizable_slot_entries", "slot_index"), &SpeciesModelData::get_customizable_slot_entries);
	ClassDB::bind_method(D_METHOD("set_customizable_slot_entries", "slot_index", "customizable_slots"), &SpeciesModelData::set_customizable_slot_entries);

	//Color Slots
	ClassDB::bind_method(D_METHOD("get_customizable_color_slots_string"), &SpeciesModelData::get_customizable_color_slots_string);
	ClassDB::bind_method(D_METHOD("set_customizable_color_slots_string", "value"), &SpeciesModelData::set_customizable_color_slots_string);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "customizable_color_slots_string"), "set_customizable_color_slots_string", "get_customizable_color_slots_string");

	ClassDB::bind_method(D_METHOD("get_color_customizable_slot_color", "slot_index", "index"), &SpeciesModelData::get_color_customizable_slot_color);
	ClassDB::bind_method(D_METHOD("set_color_customizable_slot_color", "slot_index", "index", "data"), &SpeciesModelData::set_color_customizable_slot_color);
	ClassDB::bind_method(D_METHOD("add_color_customizable_slot_color", "slot_index", "color_customizable_slot"), &SpeciesModelData::add_color_customizable_slot_color);
	ClassDB::bind_method(D_METHOD("remove_color_customizable_slot_color", "slot_index", "index"), &SpeciesModelData::remove_color_customizable_slot_color);

	ClassDB::bind_method(D_METHOD("get_color_customizable_slot_colors", "slot_index"), &SpeciesModelData::get_color_customizable_slot_colors);
	ClassDB::bind_method(D_METHOD("set_color_customizable_slot_colors", "slot_index", "colors"), &SpeciesModelData::set_color_customizable_slot_colors);

	ClassDB::bind_method(D_METHOD("get_color_customizable_slot_bone_slot_mask", "slot_index"), &SpeciesModelData::get_color_customizable_slot_bone_slot_mask);
	ClassDB::bind_method(D_METHOD("set_color_customizable_slot_bone_slot_mask", "slot_index", "value"), &SpeciesModelData::set_color_customizable_slot_bone_slot_mask);

	ClassDB::bind_method(D_METHOD("get_color_customizable_slot_texture_layer", "slot_index"), &SpeciesModelData::get_color_customizable_slot_texture_layer);
	ClassDB::bind_method(D_METHOD("set_color_customizable_slot_texture_layer", "slot_index", "value"), &SpeciesModelData::set_color_customizable_slot_texture_layer);

	ClassDB::bind_method(D_METHOD("get_color_customizable_count"), &SpeciesModelData::get_color_customizable_count);
	ClassDB::bind_method(D_METHOD("get_color_customizable_slot_count", "slot_index"), &SpeciesModelData::get_color_customizable_slot_count);
}
