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

#include "model_visual.h"

ItemEnums::EntityTextureLayers ModelVisual::get_layer() {
	return _layer;
}
void ModelVisual::set_layer(ItemEnums::EntityTextureLayers layer) {
	_layer = layer;
}

Ref<ModelVisualEntry> ModelVisual::get_visual(int index) {
	ERR_FAIL_INDEX_V(index, EntityEnums::SKELETON_POINTS_MAX, Ref<ModelVisualEntry>());

	return _entries[index];
}
void ModelVisual::set_visual(int index, Ref<ModelVisualEntry> entry) {
	ERR_FAIL_INDEX(index, EntityEnums::SKELETON_POINTS_MAX);

	_entries[index] = entry;
}

ModelVisual::ModelVisual() {
	_layer = ItemEnums::ENTITY_TEXTURE_LAYER_NONE;
}

ModelVisual::~ModelVisual() {
	for (int i = 0; i < EntityEnums::SKELETON_POINTS_MAX; ++i) {
		_entries[i].unref();
	}
}

void ModelVisual::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_layer"), &ModelVisual::get_layer);
	ClassDB::bind_method(D_METHOD("set_layer", "layer"), &ModelVisual::set_layer);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "layer", PROPERTY_HINT_ENUM, ItemEnums::BINDING_STRING_ENTITY_TEXTURE_LAYERS), "set_layer", "get_layer");

	ClassDB::bind_method(D_METHOD("get_visual", "index"), &ModelVisual::get_visual);
	ClassDB::bind_method(D_METHOD("set_visual", "index", "entry"), &ModelVisual::set_visual);

	ADD_GROUP("Visuals", "visual_");
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_root", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_ROOT);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_pelvis", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_PELVIS);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_spine", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_SPINE);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_spine_1", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_SPINE_1);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_spine_2", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_SPINE_2);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_neck", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_NECK);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_head", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_HEAD);

	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_clavicle", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_CLAVICLE);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_upper_arm", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_UPPER_ARM);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_forearm", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_FOREARM);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_hand", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_HAND);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_thumb_base", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_THUMB_BASE);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_thumb_end", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_THUMB_END);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_fingers_base", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_FINGERS_BASE);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_fingers_end", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_FINGERS_END);

	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_clavicle", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_CLAVICLE);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_upper_arm", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_UPPER_ARM);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_forearm", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_FOREARM);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_hand", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_HAND);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_thumb_base", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_THUMB_BASE);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_thumb_end", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_THUMB_END);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_fingers_base", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_FINGERS_BASE);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_fingers_end", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_FINGERS_END);

	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_thigh", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_THIGH);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_calf", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_CALF);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_foot", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_FOOT);

	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_thigh", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_THIGH);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_calf", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_CALF);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_foot", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_FOOT);
}
