/*
Copyright (c) 2019-2020 Péter Magyar

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

ItemEnums::EntityTextureLayers ModelVisualEntry::get_override_layer() {
	return _override_layer;
}
void ModelVisualEntry::set_override_layer(ItemEnums::EntityTextureLayers layer) {
	_override_layer = layer;
}

#ifdef MESH_DATA_RESOURCE_PRESENT
Ref<MeshDataResource> ModelVisualEntry::get_mesh(int index) {
	return _mesh[index];
}
void ModelVisualEntry::set_mesh(int index, Ref<MeshDataResource> mesh) {
	_mesh[index] = mesh;
}
#endif

Ref<Texture> ModelVisualEntry::get_texture(int index) {
	return _texture[index];
}
void ModelVisualEntry::set_texture(int index, Ref<Texture> texture) {
	_texture[index] = texture;
}

Color ModelVisualEntry::get_color() {
	return _color;
}
void ModelVisualEntry::set_color(Color color) {
	_color = color;
}

Ref<PackedScene> ModelVisualEntry::get_effect() {
	return _effect;
}
void ModelVisualEntry::set_effect(Ref<PackedScene> effect) {
	_effect = effect;
}

Vector3 ModelVisualEntry::get_effect_offset(int index) {
	return _effect_offset[index];
}
void ModelVisualEntry::set_effect_offset(int index, Vector3 offset) {
	_effect_offset[index] = offset;
}

ModelVisualEntry::ModelVisualEntry() {
	_override_layer = ItemEnums::ENTITY_TEXTURE_LAYER_NONE;

	_color = Color(1, 1, 1, 1);
}

ModelVisualEntry::~ModelVisualEntry() {
	for (int i = 0; i < 1; ++i) {
#ifdef MESH_DATA_RESOURCE_PRESENT
		_mesh[i].unref();
#endif

		_texture[i].unref();
	}

	_effect.unref();
}

void ModelVisualEntry::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_override_layer"), &ModelVisualEntry::get_override_layer);
	ClassDB::bind_method(D_METHOD("set_override_layer", "value"), &ModelVisualEntry::set_override_layer);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "override_layer", PROPERTY_HINT_ENUM, ItemEnums::BINDING_STRING_ENTITY_TEXTURE_LAYERS), "set_override_layer", "get_override_layer");

#ifdef MESH_DATA_RESOURCE_PRESENT
	ClassDB::bind_method(D_METHOD("get_mesh", "index"), &ModelVisualEntry::get_mesh);
	ClassDB::bind_method(D_METHOD("set_mesh", "index", "value"), &ModelVisualEntry::set_mesh);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "mesh", PROPERTY_HINT_RESOURCE_TYPE, "MeshDataResource"), "set_mesh", "get_mesh", 0);
#endif

	ClassDB::bind_method(D_METHOD("get_texture", "index"), &ModelVisualEntry::get_texture);
	ClassDB::bind_method(D_METHOD("set_texture", "index", "value"), &ModelVisualEntry::set_texture);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), "set_texture", "get_texture", 0);

	ClassDB::bind_method(D_METHOD("get_color"), &ModelVisualEntry::get_color);
	ClassDB::bind_method(D_METHOD("set_color", "value"), &ModelVisualEntry::set_color);
	ADD_PROPERTY(PropertyInfo(Variant::COLOR, "color"), "set_color", "get_color");

	ClassDB::bind_method(D_METHOD("get_effect"), &ModelVisualEntry::get_effect);
	ClassDB::bind_method(D_METHOD("set_effect", "value"), &ModelVisualEntry::set_effect);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "effect", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_effect", "get_effect");

	ClassDB::bind_method(D_METHOD("get_effect_offset", "index"), &ModelVisualEntry::get_effect_offset);
	ClassDB::bind_method(D_METHOD("set_effect_offset", "index", "value"), &ModelVisualEntry::set_effect_offset);
	ADD_PROPERTYI(PropertyInfo(Variant::VECTOR3, "effect_offset"), "set_effect_offset", "get_effect_offset", 0);
}
