#include "item_visual_entry.h"

int ItemVisualEntry::get_id() {
	return _id;
}
void ItemVisualEntry::set_id(int id) {
	_id = id;
}

EntityEnums::CharacterSkeletonPoints ItemVisualEntry::get_target_bone() {
	return _target_bone;
}
void ItemVisualEntry::set_target_bone(EntityEnums::CharacterSkeletonPoints bone) {
	_target_bone = bone;
}

ItemEnums::EntityTextureLayers ItemVisualEntry::get_layer() {
	return _layer;
}
void ItemVisualEntry::set_layer(ItemEnums::EntityTextureLayers layer) {
	_layer = layer;
}

Ref<MeshDataResource> ItemVisualEntry::get_mesh() {
	return _mesh;
}
void ItemVisualEntry::set_mesh(Ref<MeshDataResource> mesh) {
	_mesh = mesh;
}

Ref<Texture> ItemVisualEntry::get_texture() {
	return _texture;
}
void ItemVisualEntry::set_texture(Ref<Texture> texture) {
	_texture = texture;
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

ItemVisualEntry::ItemVisualEntry() {
	_id = 0;

	_target_bone = EntityEnums::SKELETON_POINT_HEAD;
	_layer = ItemEnums::ENTITY_TEXTURE_LAYER_NONE;

	_color = Color(1, 1, 1, 1);
}

ItemVisualEntry::~ItemVisualEntry() {
	_mesh.unref();
	_texture.unref();
	_effect.unref();
}

void ItemVisualEntry::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_id"), &ItemVisualEntry::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &ItemVisualEntry::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ClassDB::bind_method(D_METHOD("get_target_bone"), &ItemVisualEntry::get_target_bone);
	ClassDB::bind_method(D_METHOD("set_target_bone", "bone"), &ItemVisualEntry::set_target_bone);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "target_bone", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_CHARCATER_SKELETON_POINTS), "set_target_bone", "get_target_bone");

	ClassDB::bind_method(D_METHOD("get_layer"), &ItemVisualEntry::get_layer);
	ClassDB::bind_method(D_METHOD("set_layer", "value"), &ItemVisualEntry::set_layer);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "layer", PROPERTY_HINT_ENUM, ItemEnums::BINDING_STRING_ENTITY_TEXTURE_LAYERS), "set_layer", "get_layer");

	ClassDB::bind_method(D_METHOD("get_mesh"), &ItemVisualEntry::get_mesh);
	ClassDB::bind_method(D_METHOD("set_mesh", "value"), &ItemVisualEntry::set_mesh);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "mesh", PROPERTY_HINT_RESOURCE_TYPE, "MeshDataResource"), "set_mesh", "get_mesh");

	ClassDB::bind_method(D_METHOD("get_texture"), &ItemVisualEntry::get_texture);
	ClassDB::bind_method(D_METHOD("set_texture", "value"), &ItemVisualEntry::set_texture);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), "set_texture", "get_texture");

	ClassDB::bind_method(D_METHOD("get_color"), &ItemVisualEntry::get_color);
	ClassDB::bind_method(D_METHOD("set_color", "value"), &ItemVisualEntry::set_color);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "color"), "set_color", "get_color");

	ClassDB::bind_method(D_METHOD("get_effect"), &ItemVisualEntry::get_effect);
	ClassDB::bind_method(D_METHOD("set_effect", "value"), &ItemVisualEntry::set_effect);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "effect", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_effect", "get_effect");
}
