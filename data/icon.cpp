#include "icon.h"

int Icon::get_id() {
	return _id;
}

void Icon::set_id(int value) {
	_id = value;
}

String Icon::get_icon_file_name() {
	return _icon_file_name;
}

void Icon::set_icon_file_name(String value) {
	_icon_file_name = value;
}

Vector2i Icon::get_icon_atlas_position() {
	return _icon_atlas_position;
}

void Icon::set_icon_atlas_position(Vector2i value) {
	_icon_atlas_position = value;
}

Ref<Texture> Icon::get_icon() {
	return _icon;
}

void Icon::set_icon(Ref<Texture> value) {
	_icon = value;
}

void Icon::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_id"), &Icon::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &Icon::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ClassDB::bind_method(D_METHOD("get_icon_file_name"), &Icon::get_icon_file_name);
	ClassDB::bind_method(D_METHOD("set_icon_file_name", "value"), &Icon::set_icon_file_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "icon_file_name"), "set_icon_file_name", "get_icon_file_name");

	//ClassDB::bind_method(D_METHOD("get_icon_atlas_position"), &Icon::get_icon_atlas_position);
	//ClassDB::bind_method(D_METHOD("set_icon_atlas_position", "value"), &Icon::set_icon_atlas_position);
	//ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "icon_atlas_position"), "set_icon_atlas_position", "get_icon_atlas_position");

	ClassDB::bind_method(D_METHOD("get_icon"), &Icon::get_icon);
	ClassDB::bind_method(D_METHOD("set_icon", "value"), &Icon::set_icon);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon_atlas_position", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), "set_icon", "get_icon");

	ClassDB::bind_method(D_METHOD("Load_icon"), &Icon::Load_icon);
	ClassDB::bind_method(D_METHOD("is_icon_loaded"), &Icon::is_icon_loaded);
}

Icon::Icon() {
	_id = 0;
	_icon_file_name = "";
}

Icon::Icon(int id, String icon_file_name, Vector2i icon_atlas_position) {
	_id = id;
	_icon_file_name = icon_file_name;
	_icon_atlas_position = icon_atlas_position;
	//_icon ;
}

/*
Rect* Icon::GetIconRect()
{
	return new Rect((float)(iconAtlasPosition->x * 16), (float)(iconAtlasPosition->y * 16), (float)16, (float)16);
}
*/
