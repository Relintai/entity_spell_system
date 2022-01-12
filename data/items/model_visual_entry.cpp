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

#include "model_visual_entry.h"

#include "../../singletons/ess.h"

const String ModelVisualEntry::BINDING_STRING_MODEL_VISUAL_ENTRY_TYPES = "Bone,Attachment";

ModelVisualEntry::ModenVisualEntryType ModelVisualEntry::get_type() const {
	return _type;
}
void ModelVisualEntry::set_type(const ModelVisualEntry::ModenVisualEntryType type) {
	_type = type;
}

int ModelVisualEntry::get_override_layer() const {
	return _override_layer;
}
void ModelVisualEntry::set_override_layer(const int layer) {
	_override_layer = layer;
}

int ModelVisualEntry::get_entity_type() const {
	return _entity_type;
}
void ModelVisualEntry::set_entity_type(const int value) {
	_entity_type = value;
}

int ModelVisualEntry::get_bone() const {
	return _bone;
}
void ModelVisualEntry::set_bone(const int value) {
	_bone = value;
}

int ModelVisualEntry::get_group() const {
	return _group;
}
void ModelVisualEntry::set_group(const int value) {
	_group = value;
}

#ifdef MESH_DATA_RESOURCE_PRESENT
Ref<MeshDataResource> ModelVisualEntry::get_mesh(const int index) {
	ERR_FAIL_INDEX_V(index, _entries.size(), Ref<MeshDataResource>());

	return _entries[index].mesh;
}
void ModelVisualEntry::set_mesh(const int index, const Ref<MeshDataResource> &mesh) {
	ERR_FAIL_INDEX(index, _entries.size());

	_entries.write[index].mesh = mesh;
}
#endif

Ref<Texture> ModelVisualEntry::get_texture(const int index) {
	ERR_FAIL_INDEX_V(index, _entries.size(), Ref<Texture>());

	return _entries[index].texture;
}
void ModelVisualEntry::set_texture(const int index, const Ref<Texture> &texture) {
	ERR_FAIL_INDEX(index, _entries.size());

	_entries.write[index].texture = texture;
}

Color ModelVisualEntry::get_color(const int index) const {
	ERR_FAIL_INDEX_V(index, _entries.size(), Color());

	return _entries[index].color;
}
void ModelVisualEntry::set_color(const int index, const Color &color) {
	ERR_FAIL_INDEX(index, _entries.size());

	_entries.write[index].color = color;
}

Ref<PackedScene> ModelVisualEntry::get_attachment(const int index) {
	ERR_FAIL_INDEX_V(index, _entries.size(), Ref<PackedScene>());

	return _entries[index].attachment;
}
void ModelVisualEntry::set_attachment(const int index, const Ref<PackedScene> &attachment) {
	ERR_FAIL_INDEX(index, _entries.size());
	_entries.write[index].attachment = attachment;
}

Transform ModelVisualEntry::get_transform(const int index) const {
	ERR_FAIL_INDEX_V(index, _entries.size(), Transform());

	return _entries[index].transform;
}
void ModelVisualEntry::set_transform(const int index, const Transform &transform) {
	ERR_FAIL_INDEX(index, _entries.size());

	_entries.write[index].transform = transform;
}

int ModelVisualEntry::get_size() const {
	return _entries.size();
}
void ModelVisualEntry::set_size(const int value) {
	_entries.resize(value);
}

ModelVisualEntry::ModelVisualEntry() {
	_type = MODEL_VISUAL_ENTRY_TYPE_BONE;
	_override_layer = 0;

	_entity_type = 0;
	_bone = 0;
	_group = 0;

	_entries.resize(1);
}

ModelVisualEntry::~ModelVisualEntry() {
	_entries.clear();
}

bool ModelVisualEntry::_set(const StringName &p_name, const Variant &p_value) {
	String name = p_name;

	if (name.begins_with("entry_")) {
		int index = name.get_slicec('_', 1).to_int();

		if (index >= _entries.size()) {
			_entries.resize(index + 1);
		}

		StringName p = name.get_slicec('/', 1);

		if (p == "texture") {
			_entries.write[index].texture = p_value;

			return true;
#ifdef MESH_DATA_RESOURCE_PRESENT
		} else if (p == "mesh") {
			_entries.write[index].mesh = p_value;

			return true;
#endif
		} else if (p == "color") {
			_entries.write[index].color = p_value;

			return true;
		} else if (p == "attachment") {
			_entries.write[index].attachment = p_value;

			return true;
		} else if (p == "transform") {
			_entries.write[index].transform = p_value;

			return true;
		}
	}

	return false;
}
bool ModelVisualEntry::_get(const StringName &p_name, Variant &r_ret) const {
	String name = p_name;

	if (name.begins_with("entry_")) {
		int index = name.get_slicec('_', 1).to_int();

		if (index >= _entries.size()) {
			return false;
		}

		StringName p = name.get_slicec('/', 1);

		if (p == "texture") {
			r_ret = _entries[index].texture;

			return true;
#ifdef MESH_DATA_RESOURCE_PRESENT
		} else if (p == "mesh") {
			r_ret = _entries[index].mesh;

			return true;
#endif
		} else if (p == "color") {
			r_ret = _entries[index].color;

			return true;
		} else if (p == "attachment") {
			r_ret = _entries[index].attachment;

			return true;
		} else if (p == "transform") {
			r_ret = _entries[index].transform;

			return true;
		}
	}

	return false;
}
void ModelVisualEntry::_get_property_list(List<PropertyInfo> *p_list) const {
	for (int i = 0; i < _entries.size(); ++i) {
		if (_type == ModelVisualEntry::MODEL_VISUAL_ENTRY_TYPE_BONE) {
#ifdef MESH_DATA_RESOURCE_PRESENT
			p_list->push_back(PropertyInfo(Variant::OBJECT, "entry_" + itos(i) + "/mesh", PROPERTY_HINT_RESOURCE_TYPE, "MeshDataResource", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL));
#endif
			p_list->push_back(PropertyInfo(Variant::OBJECT, "entry_" + itos(i) + "/texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL));
			p_list->push_back(PropertyInfo(Variant::COLOR, "entry_" + itos(i) + "/color", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL));
		} else {
			p_list->push_back(PropertyInfo(Variant::OBJECT, "entry_" + itos(i) + "/attachment", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL));
		}
		p_list->push_back(PropertyInfo(Variant::TRANSFORM, "entry_" + itos(i) + "/transform", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL));
	}
}

void ModelVisualEntry::_validate_property(PropertyInfo &property) const {
	String name = property.name;

	if (_type == ModelVisualEntry::MODEL_VISUAL_ENTRY_TYPE_BONE) {
		if (name == "entity_type") {
			property.usage = PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED;
			property.hint_string = ESS::get_singleton()->entity_types_get();
		} else if (name == "bone") {
			if (ESS::get_singleton()->skeletons_bones_count() > _entity_type) {
				property.hint_string = ESS::get_singleton()->skeletons_bones_index_get(_entity_type);
			} else {
				property.hint_string = "";
			}
		}
	} else {
		if (name == "entity_type") {
			property.usage = PROPERTY_USAGE_INTERNAL | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED;
		} else if (name == "bone") {
			property.hint_string = EntityEnums::BINDING_STRING_COMMON_CHARCATER_SKELETON_POINTS;
		}
	}

	if (name == "group") {
		property.hint_string = ESS::get_singleton()->model_visual_groups_get();
	} else if (name == "override_layer") {
		property.hint_string = ESS::get_singleton()->texture_layers_get();
	}
}

void ModelVisualEntry::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_type"), &ModelVisualEntry::get_type);
	ClassDB::bind_method(D_METHOD("set_type", "value"), &ModelVisualEntry::set_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, ModelVisualEntry::BINDING_STRING_MODEL_VISUAL_ENTRY_TYPES, PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_type", "get_type");

	ClassDB::bind_method(D_METHOD("get_override_layer"), &ModelVisualEntry::get_override_layer);
	ClassDB::bind_method(D_METHOD("set_override_layer", "value"), &ModelVisualEntry::set_override_layer);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "override_layer", PROPERTY_HINT_ENUM, ""), "set_override_layer", "get_override_layer");

	ClassDB::bind_method(D_METHOD("get_entity_type"), &ModelVisualEntry::get_entity_type);
	ClassDB::bind_method(D_METHOD("set_entity_type", "value"), &ModelVisualEntry::set_entity_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "entity_type", PROPERTY_HINT_ENUM, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_entity_type", "get_entity_type");

	ClassDB::bind_method(D_METHOD("get_bone"), &ModelVisualEntry::get_bone);
	ClassDB::bind_method(D_METHOD("set_bone", "value"), &ModelVisualEntry::set_bone);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "bone", PROPERTY_HINT_ENUM), "set_bone", "get_bone");

	ClassDB::bind_method(D_METHOD("get_group"), &ModelVisualEntry::get_group);
	ClassDB::bind_method(D_METHOD("set_group", "value"), &ModelVisualEntry::set_group);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "group", PROPERTY_HINT_ENUM), "set_group", "get_group");

#ifdef MESH_DATA_RESOURCE_PRESENT
	ClassDB::bind_method(D_METHOD("get_mesh", "index"), &ModelVisualEntry::get_mesh);
	ClassDB::bind_method(D_METHOD("set_mesh", "index", "value"), &ModelVisualEntry::set_mesh);
#endif

	ClassDB::bind_method(D_METHOD("get_texture", "index"), &ModelVisualEntry::get_texture);
	ClassDB::bind_method(D_METHOD("set_texture", "index", "value"), &ModelVisualEntry::set_texture);

	ClassDB::bind_method(D_METHOD("get_color"), &ModelVisualEntry::get_color);
	ClassDB::bind_method(D_METHOD("set_color", "value"), &ModelVisualEntry::set_color);

	ClassDB::bind_method(D_METHOD("get_attachment"), &ModelVisualEntry::get_attachment);
	ClassDB::bind_method(D_METHOD("set_attachment", "value"), &ModelVisualEntry::set_attachment);

	ClassDB::bind_method(D_METHOD("get_transform", "index"), &ModelVisualEntry::get_transform);
	ClassDB::bind_method(D_METHOD("set_transform", "index", "value"), &ModelVisualEntry::set_transform);

	ClassDB::bind_method(D_METHOD("get_size"), &ModelVisualEntry::get_size);
	ClassDB::bind_method(D_METHOD("set_size", "value"), &ModelVisualEntry::set_size);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "size", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_size", "get_size");

	BIND_ENUM_CONSTANT(MODEL_VISUAL_ENTRY_TYPE_BONE);
	BIND_ENUM_CONSTANT(MODEL_VISUAL_ENTRY_TYPE_ATTACHMENT);
}
