#include "character_skeleton_3d.h"

#include "../data/item_visual.h"

EntityEnums::EntityGender CharacterSkeleton3D::get_gender() {
	return _gender;
}
void CharacterSkeleton3D::set_gender(EntityEnums::EntityGender value) {
	_gender = value;
}

bool CharacterSkeleton3D::get_model_dirty() const {
	return _model_dirty;
}
void CharacterSkeleton3D::set_model_dirty(bool value) {
	_model_dirty = value;
}

NodePath CharacterSkeleton3D::get_bone_path(int index) {
	ERR_FAIL_INDEX_V(index, EntityEnums::SKELETON_POINTS_MAX, NodePath());

	return _bone_paths[index];
}
void CharacterSkeleton3D::set_bone_path(int index, NodePath path) {
	ERR_FAIL_INDEX(index, EntityEnums::SKELETON_POINTS_MAX);

	_bone_paths[index] = path;

	_bone_nodes[index] = get_node_or_null(path);
}

Node *CharacterSkeleton3D::get_bone_node(EntityEnums::CharacterSkeletonPoints node_id) {
	return _bone_nodes[node_id];
}

NodePath CharacterSkeleton3D::get_animation_player_path() {
	return _animation_player_path;
}

void CharacterSkeleton3D::set_animation_player_path(NodePath path) {
	_animation_player_path = path;

	Node *node = get_node_or_null(_animation_player_path);

	if (node != NULL) {
		_animation_player = Object::cast_to<AnimationPlayer>(node);
	} else {
		_animation_player = NULL;
	}
}

AnimationPlayer *CharacterSkeleton3D::get_animation_player() {
	return _animation_player;
}

NodePath CharacterSkeleton3D::get_animation_tree_path() {
	return _animation_tree_path;
}

void CharacterSkeleton3D::set_animation_tree_path(NodePath path) {
	_animation_tree_path = path;

	Node *node = get_node_or_null(_animation_tree_path);

	if (node != NULL) {
		_animation_tree = Object::cast_to<AnimationTree>(node);
	} else {
		_animation_tree = NULL;
	}
}

AnimationTree *CharacterSkeleton3D::get_animation_tree() {
	return _animation_tree;
}

void CharacterSkeleton3D::update_nodes() {
	for (int i = 0; i < EntityEnums::SKELETON_POINTS_MAX; ++i) {
		_bone_nodes[i] = get_node_or_null(_bone_paths[i]);
	}

	set_animation_player_path(_animation_player_path);
	set_animation_tree_path(_animation_tree_path);
}

void CharacterSkeleton3D::add_item_visual(Ref<ItemVisual> vis) {
	ERR_FAIL_COND(!vis.is_valid());

	for (int i = 0; i < EntityEnums::SKELETON_POINTS_MAX; ++i) {
		Ref<ItemVisualEntry> e = vis->get_visual(i);

		if (e.is_valid())
			add_item_visual_entry(vis, e, i);
	}

	_item_visuals.push_back(vis);

	set_process(true);
	_model_dirty = true;
}
void CharacterSkeleton3D::remove_item_visual(Ref<ItemVisual> vis) {
	ERR_FAIL_COND(!vis.is_valid());

	int index = _item_visuals.find(vis);

	if (index == -1)
		return;

	for (int i = 0; i < EntityEnums::SKELETON_POINTS_MAX; ++i) {
		Ref<ItemVisualEntry> e = vis->get_visual(i);

		if (e.is_valid())
			remove_item_visual_entry(vis, e, i);
	}

	_item_visuals.remove(index);

	set_process(true);
	_model_dirty = true;
}
void CharacterSkeleton3D::remove_item_visual_index(int index) {
	ERR_FAIL_INDEX(index, _item_visuals.size());

	set_process(true);
	_model_dirty = true;

	_item_visuals.remove(index);
}
Ref<ItemVisual> CharacterSkeleton3D::get_item_visual(int index) {
	ERR_FAIL_INDEX_V(index, _item_visuals.size(), Ref<ItemVisual>());

	set_process(true);
	_model_dirty = true;

	return _item_visuals.get(index);
}
int CharacterSkeleton3D::get_item_visual_count() {
	return _item_visuals.size();
}
void CharacterSkeleton3D::clear_item_visuals() {
	_item_visuals.clear();

	for (int i = 0; i < EntityEnums::SKELETON_POINTS_MAX; ++i) {
		_entries[i].clear();
	}

	_model_dirty = true;
	set_process(true);
}

void CharacterSkeleton3D::add_item_visual_entry(Ref<ItemVisual> vis, Ref<ItemVisualEntry> ive, int target_bone) {
	ERR_FAIL_COND(!vis.is_valid());
	ERR_FAIL_COND(!ive.is_valid());

	int target_bone_idx = target_bone;

	Vector<Ref<SkeletonModelEntry> > &entries = _entries[target_bone_idx];

	for (int i = 0; i < entries.size(); ++i) {
		Ref<SkeletonModelEntry> e = entries.get(i);

		if (e->get_entry() == ive) {
			e->set_count(e->get_count() + 1);
			return;
		}
	}

	Ref<SkeletonModelEntry> e;
	e.instance();

	e->set_priority(static_cast<int>(vis->get_layer()));
	e->set_color(ive->get_color());
	e->set_entry(ive);

	entries.push_back(e);
	_model_dirty = true;
	set_process(true);
}
void CharacterSkeleton3D::remove_item_visual_entry(Ref<ItemVisual> vis, Ref<ItemVisualEntry> ive, int target_bone) {
	ERR_FAIL_COND(!vis.is_valid());
	ERR_FAIL_COND(!ive.is_valid());

	int target_bone_idx = target_bone;

	Vector<Ref<SkeletonModelEntry> > &entries = _entries[target_bone_idx];

	for (int i = 0; i < entries.size(); ++i) {
		Ref<SkeletonModelEntry> e = entries.get(i);

		if (e->get_entry() == ive) {
			e->set_count(e->get_count() - 1);

			if (e->get_count() <= 0) {
				entries.remove(i);

				_model_dirty = true;
				set_process(true);
			}

			return;
		}
	}
}

Ref<SkeletonModelEntry> CharacterSkeleton3D::get_model_entry(const int bone_index, const int index) {
	ERR_FAIL_INDEX_V(bone_index, EntityEnums::SKELETON_POINTS_MAX, Ref<SkeletonModelEntry>());
	ERR_FAIL_INDEX_V(index, _entries[bone_index].size(), Ref<SkeletonModelEntry>());

	return _entries[bone_index].get(index);
}
int CharacterSkeleton3D::get_model_entry_count(const int bone_index) {
	ERR_FAIL_INDEX_V(bone_index, EntityEnums::SKELETON_POINTS_MAX, 0);

	return _entries[bone_index].size();
}

void CharacterSkeleton3D::sort_layers() {
	for (int i = 0; i < EntityEnums::SKELETON_POINTS_MAX; ++i) {
		Vector<Ref<SkeletonModelEntry> > &entries = _entries[i];

		entries.sort_custom<_ModelEntryComparator>();
	}
}

void CharacterSkeleton3D::build_model() {
	call("_build_model");
}

void CharacterSkeleton3D::_build_model() {
	set_process(false);
}

CharacterSkeleton3D::CharacterSkeleton3D() {
	_model_dirty = false;
	_gender = EntityEnums::GENDER_MALE;

	for (int i = 0; i < EntityEnums::SKELETON_POINTS_MAX; ++i) {
		_bone_nodes[i] = NULL;
	}

	_animation_player = NULL;
}

CharacterSkeleton3D::~CharacterSkeleton3D() {
	for (int i = 0; i < EntityEnums::SKELETON_POINTS_MAX; ++i) {
		_entries[i].clear();
	}

	_item_visuals.clear();
}

void CharacterSkeleton3D::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_ENTER_TREE: {
			update_nodes();
		} break;
		case NOTIFICATION_PROCESS: {
			if (_model_dirty)
				build_model();
		} break;
		case NOTIFICATION_EXIT_TREE: {

		} break;
	}
}

void CharacterSkeleton3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_gender"), &CharacterSkeleton3D::get_gender);
	ClassDB::bind_method(D_METHOD("set_gender", "value"), &CharacterSkeleton3D::set_gender);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "gender", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_ENTITY_GENDER), "set_gender", "get_gender");

	ClassDB::bind_method(D_METHOD("add_item_visual", "vis"), &CharacterSkeleton3D::add_item_visual);
	ClassDB::bind_method(D_METHOD("remove_item_visual", "vis"), &CharacterSkeleton3D::remove_item_visual);
	ClassDB::bind_method(D_METHOD("remove_item_visual_index", "index"), &CharacterSkeleton3D::remove_item_visual_index);
	ClassDB::bind_method(D_METHOD("get_item_visual", "index"), &CharacterSkeleton3D::get_item_visual);
	ClassDB::bind_method(D_METHOD("get_item_visual_count"), &CharacterSkeleton3D::get_item_visual_count);
	ClassDB::bind_method(D_METHOD("clear_item_visuals"), &CharacterSkeleton3D::clear_item_visuals);

	BIND_VMETHOD(MethodInfo("_build_model"));

	ClassDB::bind_method(D_METHOD("get_model_dirty"), &CharacterSkeleton3D::get_model_dirty);
	ClassDB::bind_method(D_METHOD("set_model_dirty", "value"), &CharacterSkeleton3D::set_model_dirty);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "model_dirty"), "set_model_dirty", "get_model_dirty");

	ClassDB::bind_method(D_METHOD("get_animation_player_path"), &CharacterSkeleton3D::get_animation_player_path);
	ClassDB::bind_method(D_METHOD("set_animation_player_path", "path"), &CharacterSkeleton3D::set_animation_player_path);
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "animation_player_path"), "set_animation_player_path", "get_animation_player_path");

	ClassDB::bind_method(D_METHOD("get_animation_tree_path"), &CharacterSkeleton3D::get_animation_tree_path);
	ClassDB::bind_method(D_METHOD("set_animation_tree_path", "path"), &CharacterSkeleton3D::set_animation_tree_path);
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "animation_tree_path"), "set_animation_tree_path", "get_animation_tree_path");

	ClassDB::bind_method(D_METHOD("add_item_visual_entry", "vis", "ive"), &CharacterSkeleton3D::add_item_visual_entry);
	ClassDB::bind_method(D_METHOD("remove_item_visual_entry", "vis", "ive"), &CharacterSkeleton3D::remove_item_visual_entry);
	ClassDB::bind_method(D_METHOD("get_model_entry", "bone_index", "index"), &CharacterSkeleton3D::get_model_entry);
	ClassDB::bind_method(D_METHOD("get_model_entry_count", "bone_index"), &CharacterSkeleton3D::get_model_entry_count);

	ClassDB::bind_method(D_METHOD("sort_layers"), &CharacterSkeleton3D::sort_layers);

	ClassDB::bind_method(D_METHOD("build_model"), &CharacterSkeleton3D::build_model);
	ClassDB::bind_method(D_METHOD("_build_model"), &CharacterSkeleton3D::_build_model);

	//Bone Paths
	ClassDB::bind_method(D_METHOD("get_bone_path", "index"), &CharacterSkeleton3D::get_bone_path);
	ClassDB::bind_method(D_METHOD("set_bone_path", "index", "path"), &CharacterSkeleton3D::set_bone_path);

	ADD_GROUP("Bone Paths", "bone_path_");
	ADD_PROPERTYI(PropertyInfo(Variant::NODE_PATH, "bone_path_root"), "set_bone_path", "get_bone_path", EntityEnums::SKELETON_POINT_ROOT);

	ClassDB::bind_method(D_METHOD("get_bone_node", "bone_idx"), &CharacterSkeleton3D::get_bone_node);

	ClassDB::bind_method(D_METHOD("get_animation_player"), &CharacterSkeleton3D::get_animation_player);
	ClassDB::bind_method(D_METHOD("get_animation_tree"), &CharacterSkeleton3D::get_animation_tree);

	ClassDB::bind_method(D_METHOD("update_nodes"), &CharacterSkeleton3D::update_nodes);

	/*
	//Attack Points?
	ClassDB::bind_method(D_METHOD("get_visual", "index"), &CharacterSkeleton3D::get_visual);
	ClassDB::bind_method(D_METHOD("set_visual", "index", "entry"), &CharacterSkeleton3D::set_visual);

	ADD_GROUP("Visuals", "visual_");
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_root", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_ROOT);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_pelvis", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_PELVIS);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_spine", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_SPINE);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_spine_1", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_SPINE_1);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_spine_2", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_SPINE_2);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_neck", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_NECK);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_head", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_HEAD);

	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_clavicle", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_CLAVICLE);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_upper_arm", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_UPPER_ARM);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_forearm", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_FOREARM);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_hand", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_HAND);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_thumb_base", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_THUMB_BASE);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_thumb_end", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_THUMB_END);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_fingers_base", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_FINGERS_BASE);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_fingers_end", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_FINGERS_END);

	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_clavicle", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_CLAVICLE);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_upper_arm", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_UPPER_ARM);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_forearm", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_FOREARM);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_hand", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_HAND);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_thumb_base", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_THUMB_BASE);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_thumb_end", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_THUMB_END);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_fingers_base", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_FINGERS_BASE);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_fingers_end", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_FINGERS_END);

	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_thigh", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_THIGH);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_calf", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_CALF);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_left_foot", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_LEFT_FOOT);

	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_thigh", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_THIGH);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_calf", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_CALF);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "visual_right_foot", PROPERTY_HINT_RESOURCE_TYPE, "CharacterSkeletonVisualEntry"), "set_visual", "get_visual", EntityEnums::SKELETON_POINT_RIGHT_FOOT);
	*/
}
