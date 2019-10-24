#include "item_visual.h"

ItemEnums::EntityTextureLayers ItemVisual::get_layer() {
	return _layer;
}
void ItemVisual::set_layer(ItemEnums::EntityTextureLayers layer) {
	_layer = layer;
}

Ref<ItemVisualEntry> ItemVisual::get_visual(int index) {
	ERR_FAIL_INDEX_V(index, EntityEnums::SKELETON_POINTS_MAX, Ref<ItemVisualEntry>());

	return _entries[index];
}
void ItemVisual::set_visual(int index, Ref<ItemVisualEntry> entry) {
	ERR_FAIL_INDEX(index, EntityEnums::SKELETON_POINTS_MAX);

	_entries[index] = entry;
}

ItemVisual::ItemVisual() {
	_layer = ItemEnums::ENTITY_TEXTURE_LAYER_NONE;
}

ItemVisual::~ItemVisual() {
	for (int i = 0; i < EntityEnums::SKELETON_POINTS_MAX; ++i) {
		_entries[i].unref();
	}
}

void ItemVisual::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_layer"), &ItemVisual::get_layer);
	ClassDB::bind_method(D_METHOD("set_layer", "layer"), &ItemVisual::set_layer);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "layer", PROPERTY_HINT_ENUM, ItemEnums::BINDING_STRING_ENTITY_TEXTURE_LAYERS), "set_layer", "get_layer");

	ClassDB::bind_method(D_METHOD("get_visual", "index"), &ItemVisual::get_visual);
	ClassDB::bind_method(D_METHOD("set_visual", "index", "entry"), &ItemVisual::set_visual);

	ADD_GROUP("Visuals", "visual_");
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_root", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_ROOT);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_pelvis", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_PELVIS);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_spine", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_SPINE);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_spine_1", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_SPINE_1);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_spine_2", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_SPINE_2);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_neck", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_NECK);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_head", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_HEAD);

	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_clavicle", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_CLAVICLE);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_upper_arm", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_UPPER_ARM);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_forearm", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_FOREARM);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_hand", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_HAND);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_thumb_base", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_THUMB_BASE);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_thumb_end", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_THUMB_END);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_fingers_base", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_FINGERS_BASE);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_fingers_end", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_FINGERS_END);

	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_clavicle", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_CLAVICLE);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_upper_arm", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_UPPER_ARM);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_forearm", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_FOREARM);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_hand", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_HAND);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_thumb_base", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_THUMB_BASE);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_thumb_end", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_THUMB_END);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_fingers_base", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_FINGERS_BASE);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_fingers_end", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_FINGERS_END);

	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_thigh", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_THIGH);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_calf", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_CALF);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_foot", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_FOOT);

	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_thigh", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_THIGH);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_calf", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_CALF);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_foot", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_FOOT);

}
