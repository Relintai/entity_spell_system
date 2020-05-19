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

#include "species_model_data.h"

#include "core/version.h"

int SpeciesModelData::get_id() {
	return _id;
}
void SpeciesModelData::set_id(int value) {
	_id = value;
}

Ref<PackedScene> SpeciesModelData::get_body() {
	return _body;
}
void SpeciesModelData::set_body(Ref<PackedScene> value) {
	_body = value;
}

//Entries

Ref<ModelVisualEntry> SpeciesModelData::get_visual(const int bone_index, const int index) const {
	ERR_FAIL_INDEX_V(bone_index, EntityEnums::SKELETON_POINTS_MAX, Ref<ModelVisualEntry>());
	ERR_FAIL_INDEX_V(index, _visuals[bone_index].size(), Ref<ModelVisualEntry>());

	return _visuals[bone_index].get(index);
}
void SpeciesModelData::set_visual(const int bone_index, const int index, const Ref<ModelVisualEntry> visual) {
	ERR_FAIL_INDEX(bone_index, EntityEnums::SKELETON_POINTS_MAX);
	ERR_FAIL_INDEX(index, _visuals[bone_index].size());

	_visuals[bone_index].set(index, visual);
}
void SpeciesModelData::add_visual(const int bone_index, const Ref<ModelVisualEntry> visual) {
	ERR_FAIL_INDEX(bone_index, EntityEnums::SKELETON_POINTS_MAX);

	_visuals[bone_index].push_back(visual);
}
void SpeciesModelData::remove_visual(const int bone_index, const int index) {
	ERR_FAIL_INDEX(bone_index, EntityEnums::SKELETON_POINTS_MAX);
	ERR_FAIL_INDEX(index, _visuals[bone_index].size());

	_visuals[bone_index].remove(index);
}

int SpeciesModelData::get_visual_count(const int bone_index) const {
	ERR_FAIL_INDEX_V(bone_index, EntityEnums::SKELETON_POINTS_MAX, 0);

	return _visuals[bone_index].size();
}

Vector<Variant> SpeciesModelData::get_visuals(const int bone_index) {
	ERR_FAIL_INDEX_V(bone_index, EntityEnums::SKELETON_POINTS_MAX, Vector<Variant>());

	Vector<Variant> r;
	for (int i = 0; i < _visuals[bone_index].size(); i++) {
#if VERSION_MAJOR < 4
		r.push_back(_visuals[bone_index][i].get_ref_ptr());
#else
		r.push_back(_visuals[bone_index][i]);
#endif
	}
	return r;
}
void SpeciesModelData::set_visuals(const int bone_index, const Vector<Variant> &visuals) {
	ERR_FAIL_INDEX(bone_index, EntityEnums::SKELETON_POINTS_MAX);

	_visuals[bone_index].clear();
	for (int i = 0; i < visuals.size(); i++) {
		Ref<ModelVisualEntry> visual = Ref<ModelVisualEntry>(visuals[i]);

		_visuals[bone_index].push_back(visual);
	}
}

//SkinColors

Color SpeciesModelData::get_skin_color(const int index) const {
	ERR_FAIL_INDEX_V(index, _skin_colors.size(), Color());

	return _skin_colors.get(index);
}
void SpeciesModelData::set_skin_color(const int index, const Color skin_color) {
	ERR_FAIL_INDEX(index, _skin_colors.size());

	_skin_colors.set(index, skin_color);
}
void SpeciesModelData::add_skin_color(const Color skin_color) {
	_skin_colors.push_back(skin_color);
}
void SpeciesModelData::remove_skin_color(const int index) {
	ERR_FAIL_INDEX(index, _skin_colors.size());

	_skin_colors.remove(index);
}

int SpeciesModelData::get_skin_color_count() const {
	return _skin_colors.size();
}

Vector<Variant> SpeciesModelData::get_skin_colors() {
	Vector<Variant> r;
	for (int i = 0; i < _skin_colors.size(); i++) {
		r.push_back(_skin_colors[i]);
	}
	return r;
}
void SpeciesModelData::set_skin_colors(const Vector<Variant> &skin_colors) {
	_skin_colors.clear();
	for (int i = 0; i < skin_colors.size(); i++) {
		Color skin_color = Color(skin_colors[i]);

		_skin_colors.push_back(skin_color);
	}
}

//HairStyles

Ref<ModelVisualEntry> SpeciesModelData::get_hair_style(const int index) const {
	ERR_FAIL_INDEX_V(index, _hair_styles.size(), Ref<ModelVisualEntry>());

	return _hair_styles.get(index);
}
void SpeciesModelData::set_hair_style(const int index, const Ref<ModelVisualEntry> hair_style) {
	ERR_FAIL_INDEX(index, _hair_styles.size());

	_hair_styles.set(index, hair_style);
}
void SpeciesModelData::add_hair_style(const Ref<ModelVisualEntry> hair_style) {
	_hair_styles.push_back(hair_style);
}
void SpeciesModelData::remove_hair_style(const int index) {
	ERR_FAIL_INDEX(index, _hair_styles.size());

	_hair_styles.remove(index);
}

int SpeciesModelData::get_hair_style_count() const {
	return _hair_styles.size();
}

Vector<Variant> SpeciesModelData::get_hair_styles() {
	Vector<Variant> r;
	for (int i = 0; i < _hair_styles.size(); i++) {
#if VERSION_MAJOR < 4
		r.push_back(_hair_styles[i].get_ref_ptr());
#else
		r.push_back(_hair_styles[i]);
#endif
	}
	return r;
}
void SpeciesModelData::set_hair_styles(const Vector<Variant> &hair_styles) {
	_hair_styles.clear();
	for (int i = 0; i < hair_styles.size(); i++) {
		Ref<ModelVisualEntry> hair_style = Ref<ModelVisualEntry>(hair_styles[i]);

		_hair_styles.push_back(hair_style);
	}
}

//HairColors

Color SpeciesModelData::get_hair_color(const int index) const {
	ERR_FAIL_INDEX_V(index, _hair_colors.size(), Color());

	return _hair_colors.get(index);
}
void SpeciesModelData::set_hair_color(const int index, const Color hair_color) {
	ERR_FAIL_INDEX(index, _hair_colors.size());

	_hair_colors.set(index, hair_color);
}
void SpeciesModelData::add_hair_color(const Color hair_color) {
	_hair_colors.push_back(hair_color);
}
void SpeciesModelData::remove_hair_color(const int index) {
	ERR_FAIL_INDEX(index, _hair_colors.size());

	_hair_colors.remove(index);
}

int SpeciesModelData::get_hair_color_count() const {
	return _hair_colors.size();
}

Vector<Variant> SpeciesModelData::get_hair_colors() {
	Vector<Variant> r;
	for (int i = 0; i < _hair_colors.size(); i++) {
		r.push_back(_hair_colors[i]);
	}
	return r;
}
void SpeciesModelData::set_hair_colors(const Vector<Variant> &hair_colors) {
	_hair_colors.clear();
	for (int i = 0; i < hair_colors.size(); i++) {
		Color hair_color = Color(hair_colors[i]);

		_hair_colors.push_back(hair_color);
	}
}

//Heads

Ref<ModelVisualEntry> SpeciesModelData::get_head(const int index) const {
	ERR_FAIL_INDEX_V(index, _heads.size(), Ref<ModelVisualEntry>());

	return _heads.get(index);
}
void SpeciesModelData::set_head(const int index, const Ref<ModelVisualEntry> head) {
	ERR_FAIL_INDEX(index, _heads.size());

	_heads.set(index, head);
}
void SpeciesModelData::add_head(const Ref<ModelVisualEntry> head) {
	_heads.push_back(head);
}
void SpeciesModelData::remove_head(const int index) {
	ERR_FAIL_INDEX(index, _heads.size());

	_heads.remove(index);
}

int SpeciesModelData::get_head_count() const {
	return _heads.size();
}

Vector<Variant> SpeciesModelData::get_heads() {
	Vector<Variant> r;
	for (int i = 0; i < _heads.size(); i++) {
#if VERSION_MAJOR < 4
		r.push_back(_heads[i].get_ref_ptr());
#else
		r.push_back(_heads[i]);
#endif
	}
	return r;
}
void SpeciesModelData::set_heads(const Vector<Variant> &heads) {
	_heads.clear();
	for (int i = 0; i < heads.size(); i++) {
		Ref<ModelVisualEntry> head = Ref<ModelVisualEntry>(heads[i]);

		_heads.push_back(head);
	}
}

SpeciesModelData::SpeciesModelData() {
	_id = 0;
}
SpeciesModelData::~SpeciesModelData() {
	_body.unref();

	for (int i = 0; i < EntityEnums::SKELETON_POINTS_MAX; ++i) {
		_visuals[i].clear();
	}

	_skin_colors.clear();
	_hair_styles.clear();
	_hair_colors.clear();
	_heads.clear();
}

void SpeciesModelData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_id"), &SpeciesModelData::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &SpeciesModelData::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_name"), "set_name", "get_name");

	ClassDB::bind_method(D_METHOD("get_body"), &SpeciesModelData::get_body);
	ClassDB::bind_method(D_METHOD("set_body", "value"), &SpeciesModelData::set_body);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "body", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_body", "get_body");

	//Entries
	ClassDB::bind_method(D_METHOD("get_visual", "bone_index", "index"), &SpeciesModelData::get_visual);
	ClassDB::bind_method(D_METHOD("set_visual", "bone_index", "index", "data"), &SpeciesModelData::set_visual);
	ClassDB::bind_method(D_METHOD("add_visual", "bone_index", "visual"), &SpeciesModelData::add_visual);
	ClassDB::bind_method(D_METHOD("remove_visual", "bone_index", "index"), &SpeciesModelData::remove_visual);

	ClassDB::bind_method(D_METHOD("get_visual_count", "bone_index"), &SpeciesModelData::get_visual_count);

	ClassDB::bind_method(D_METHOD("get_visuals", "bone_index"), &SpeciesModelData::get_visuals);
	ClassDB::bind_method(D_METHOD("set_visuals", "bone_index", "visuals"), &SpeciesModelData::set_visuals);

	ADD_GROUP("Visuals", "visual_");
	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_root", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_ROOT);
	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_pelvis", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_PELVIS);
	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_spine", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_SPINE);
	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_spine_1", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_SPINE_1);
	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_spine_2", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_SPINE_2);
	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_neck", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_NECK);
	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_head", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_HEAD);

	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_left_clavicle", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_LEFT_CLAVICLE);
	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_left_upper_arm", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_LEFT_UPPER_ARM);
	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_left_forearm", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_LEFT_FOREARM);
	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_left_hand", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_LEFT_HAND);
	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_left_thumb_base", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_LEFT_THUMB_BASE);
	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_left_thumb_end", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_LEFT_THUMB_END);
	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_left_fingers_base", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_LEFT_FINGERS_BASE);
	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_left_fingers_end", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_LEFT_FINGERS_END);

	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_right_clavicle", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_RIGHT_CLAVICLE);
	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_right_upper_arm", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_RIGHT_UPPER_ARM);
	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_right_forearm", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_RIGHT_FOREARM);
	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_right_hand", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_RIGHT_HAND);
	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_right_thumb_base", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_RIGHT_THUMB_BASE);
	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_right_thumb_end", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_RIGHT_THUMB_END);
	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_right_fingers_base", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_RIGHT_FINGERS_BASE);
	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_right_fingers_end", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_RIGHT_FINGERS_END);

	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_left_thigh", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_LEFT_THIGH);
	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_left_calf", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_LEFT_CALF);
	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_left_foot", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_LEFT_FOOT);

	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_right_thigh", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_RIGHT_THIGH);
	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_right_calf", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_RIGHT_CALF);
	ADD_PROPERTYI(PropertyInfo(Variant::ARRAY, "visual_right_foot", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_visuals", "get_visuals", EntityEnums::SKELETON_POINT_RIGHT_FOOT);

	//DungeonDatas
	ClassDB::bind_method(D_METHOD("get_skin_color", "index"), &SpeciesModelData::get_skin_color);
	ClassDB::bind_method(D_METHOD("set_skin_color", "index", "data"), &SpeciesModelData::set_skin_color);
	ClassDB::bind_method(D_METHOD("add_skin_color", "skin_color"), &SpeciesModelData::add_skin_color);
	ClassDB::bind_method(D_METHOD("remove_skin_color", "index"), &SpeciesModelData::remove_skin_color);

	ClassDB::bind_method(D_METHOD("get_skin_color_count"), &SpeciesModelData::get_skin_color_count);

	ClassDB::bind_method(D_METHOD("get_skin_colors"), &SpeciesModelData::get_skin_colors);
	ClassDB::bind_method(D_METHOD("set_skin_colors", "skin_colors"), &SpeciesModelData::set_skin_colors);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "skin_colors", PROPERTY_HINT_NONE, "17/17:Color", PROPERTY_USAGE_DEFAULT, "Color"), "set_skin_colors", "get_skin_colors");

	//DungeonDatas
	ClassDB::bind_method(D_METHOD("get_hair_style", "index"), &SpeciesModelData::get_hair_style);
	ClassDB::bind_method(D_METHOD("set_hair_style", "index", "data"), &SpeciesModelData::set_hair_style);
	ClassDB::bind_method(D_METHOD("add_hair_style", "hair_style"), &SpeciesModelData::add_hair_style);
	ClassDB::bind_method(D_METHOD("remove_hair_style", "index"), &SpeciesModelData::remove_hair_style);

	ClassDB::bind_method(D_METHOD("get_hair_style_count"), &SpeciesModelData::get_hair_style_count);

	ClassDB::bind_method(D_METHOD("get_hair_styles"), &SpeciesModelData::get_hair_styles);
	ClassDB::bind_method(D_METHOD("set_hair_styles", "hair_styles"), &SpeciesModelData::set_hair_styles);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "hair_styles", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_hair_styles", "get_hair_styles");

	//DungeonDatas
	ClassDB::bind_method(D_METHOD("get_hair_color", "index"), &SpeciesModelData::get_hair_color);
	ClassDB::bind_method(D_METHOD("set_hair_color", "index", "data"), &SpeciesModelData::set_hair_color);
	ClassDB::bind_method(D_METHOD("add_hair_color", "hair_color"), &SpeciesModelData::add_hair_color);
	ClassDB::bind_method(D_METHOD("remove_hair_color", "index"), &SpeciesModelData::remove_hair_color);

	ClassDB::bind_method(D_METHOD("get_hair_color_count"), &SpeciesModelData::get_hair_color_count);

	ClassDB::bind_method(D_METHOD("get_hair_colors"), &SpeciesModelData::get_hair_colors);
	ClassDB::bind_method(D_METHOD("set_hair_colors", "hair_colors"), &SpeciesModelData::set_hair_colors);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "hair_colors", PROPERTY_HINT_NONE, "17/17:Color", PROPERTY_USAGE_DEFAULT, "Color"), "set_hair_colors", "get_hair_colors");

	//DungeonDatas
	ClassDB::bind_method(D_METHOD("get_head", "index"), &SpeciesModelData::get_head);
	ClassDB::bind_method(D_METHOD("set_head", "index", "data"), &SpeciesModelData::set_head);
	ClassDB::bind_method(D_METHOD("add_head", "head"), &SpeciesModelData::add_head);
	ClassDB::bind_method(D_METHOD("remove_head", "index"), &SpeciesModelData::remove_head);

	ClassDB::bind_method(D_METHOD("get_head_count"), &SpeciesModelData::get_head_count);

	ClassDB::bind_method(D_METHOD("get_heads"), &SpeciesModelData::get_heads);
	ClassDB::bind_method(D_METHOD("set_heads", "heads"), &SpeciesModelData::set_heads);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "heads", PROPERTY_HINT_NONE, "17/17:ModelVisualEntry", PROPERTY_USAGE_DEFAULT, "ModelVisualEntry"), "set_heads", "get_heads");
}
