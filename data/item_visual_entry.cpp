#include "item_visual_entry.h"

ItemEnums::EntityTextureLayers ItemVisualEntry::get_override_layer() {
	return _override_layer;
}
void ItemVisualEntry::set_override_layer(ItemEnums::EntityTextureLayers layer) {
	_override_layer = layer;
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

	_override_layer = ItemEnums::ENTITY_TEXTURE_LAYER_NONE;

	_color = Color(1, 1, 1, 1);
}

ItemVisualEntry::~ItemVisualEntry() {
	_mesh.unref();
	_texture.unref();
	_effect.unref();
}

void ItemVisualEntry::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_override_layer"), &ItemVisualEntry::get_override_layer);
	ClassDB::bind_method(D_METHOD("set_override_layer", "value"), &ItemVisualEntry::set_override_layer);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "override_layer", PROPERTY_HINT_ENUM, ItemEnums::BINDING_STRING_ENTITY_TEXTURE_LAYERS), "set_override_layer", "get_override_layer");

	ClassDB::bind_method(D_METHOD("get_mesh"), &ItemVisualEntry::get_mesh);
	ClassDB::bind_method(D_METHOD("set_mesh", "value"), &ItemVisualEntry::set_mesh);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "mesh", PROPERTY_HINT_RESOURCE_TYPE, "MeshDataResource"), "set_mesh", "get_mesh");

	ClassDB::bind_method(D_METHOD("get_texture"), &ItemVisualEntry::get_texture);
	ClassDB::bind_method(D_METHOD("set_texture", "value"), &ItemVisualEntry::set_texture);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), "set_texture", "get_texture");

	ClassDB::bind_method(D_METHOD("get_color"), &ItemVisualEntry::get_color);
	ClassDB::bind_method(D_METHOD("set_color", "value"), &ItemVisualEntry::set_color);
	ADD_PROPERTY(PropertyInfo(Variant::COLOR, "color"), "set_color", "get_color");

	ClassDB::bind_method(D_METHOD("get_effect"), &ItemVisualEntry::get_effect);
	ClassDB::bind_method(D_METHOD("set_effect", "value"), &ItemVisualEntry::set_effect);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "effect", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_effect", "get_effect");
}
