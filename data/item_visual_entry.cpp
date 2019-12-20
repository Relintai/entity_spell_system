#include "item_visual_entry.h"

ItemEnums::EntityTextureLayers ItemVisualEntry::get_override_layer() {
	return _override_layer;
}
void ItemVisualEntry::set_override_layer(ItemEnums::EntityTextureLayers layer) {
	_override_layer = layer;
}

#ifdef MESH_DATA_RESOURCE_PRESENT
Ref<MeshDataResource> ItemVisualEntry::get_mesh(int index) {
	return _mesh[index];
}
void ItemVisualEntry::set_mesh(int index, Ref<MeshDataResource> mesh) {
	_mesh[index] = mesh;
}
#endif

Ref<Texture> ItemVisualEntry::get_texture(int index) {
	return _texture[index];
}
void ItemVisualEntry::set_texture(int index, Ref<Texture> texture) {
	_texture[index] = texture;
}

Color ItemVisualEntry::get_color() {
	return _color;
}
void ItemVisualEntry::set_color(Color color) {
	_color = color;
}

Ref<PackedScene> ItemVisualEntry::get_effect() {
	return _effect;
}
void ItemVisualEntry::set_effect(Ref<PackedScene> effect) {
	_effect = effect;
}

Vector3 ItemVisualEntry::get_effect_offset(int index) {
	return _effect_offset[index];
}
void ItemVisualEntry::set_effect_offset(int index, Vector3 offset) {
	_effect_offset[index] = offset;
}

ItemVisualEntry::ItemVisualEntry() {
	_override_layer = ItemEnums::ENTITY_TEXTURE_LAYER_NONE;

	_color = Color(1, 1, 1, 1);
}

ItemVisualEntry::~ItemVisualEntry() {
	for (int i = 0; i < EntityEnums::GENDER_COUNT; ++i) {
		#ifdef MESH_DATA_RESOURCE_PRESENT
		_mesh[i].unref();
		#endif
		
		_texture[i].unref();
	}

	_effect.unref();
}

void ItemVisualEntry::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_override_layer"), &ItemVisualEntry::get_override_layer);
	ClassDB::bind_method(D_METHOD("set_override_layer", "value"), &ItemVisualEntry::set_override_layer);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "override_layer", PROPERTY_HINT_ENUM, ItemEnums::BINDING_STRING_ENTITY_TEXTURE_LAYERS), "set_override_layer", "get_override_layer");

	#ifdef MESH_DATA_RESOURCE_PRESENT
	ClassDB::bind_method(D_METHOD("get_mesh", "index"), &ItemVisualEntry::get_mesh);
	ClassDB::bind_method(D_METHOD("set_mesh", "index", "value"), &ItemVisualEntry::set_mesh);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "mesh_male", PROPERTY_HINT_RESOURCE_TYPE, "MeshDataResource"), "set_mesh", "get_mesh", EntityEnums::GENDER_MALE);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "mesh_female", PROPERTY_HINT_RESOURCE_TYPE, "MeshDataResource"), "set_mesh", "get_mesh", EntityEnums::GENDER_FEMALE);
	#endif

	ClassDB::bind_method(D_METHOD("get_texture", "index"), &ItemVisualEntry::get_texture);
	ClassDB::bind_method(D_METHOD("set_texture", "index", "value"), &ItemVisualEntry::set_texture);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "texture_male", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), "set_texture", "get_texture", EntityEnums::GENDER_MALE);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "texture_female", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), "set_texture", "get_texture", EntityEnums::GENDER_FEMALE);

	ClassDB::bind_method(D_METHOD("get_color"), &ItemVisualEntry::get_color);
	ClassDB::bind_method(D_METHOD("set_color", "value"), &ItemVisualEntry::set_color);
	ADD_PROPERTY(PropertyInfo(Variant::COLOR, "color"), "set_color", "get_color");

	ClassDB::bind_method(D_METHOD("get_effect"), &ItemVisualEntry::get_effect);
	ClassDB::bind_method(D_METHOD("set_effect", "value"), &ItemVisualEntry::set_effect);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "effect_male", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_effect", "get_effect");

	ClassDB::bind_method(D_METHOD("get_effect_offset", "index"), &ItemVisualEntry::get_effect_offset);
	ClassDB::bind_method(D_METHOD("set_effect_offset", "index", "value"), &ItemVisualEntry::set_effect_offset);
	ADD_PROPERTYI(PropertyInfo(Variant::VECTOR3, "effect_offset_male"), "set_effect_offset", "get_effect_offset", EntityEnums::GENDER_MALE);
	ADD_PROPERTYI(PropertyInfo(Variant::VECTOR3, "effect_offset_female"), "set_effect_offset", "get_effect_offset", EntityEnums::GENDER_FEMALE);
}

