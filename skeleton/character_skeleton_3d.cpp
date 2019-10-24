#include "character_skeleton_3d.h"

#include "../data/item_visual.h"

NodePath CharacterSkeleton3D::get_bone_path(int index) {
    ERR_FAIL_INDEX_V(index, EntityEnums::SKELETON_POINTS_MAX, NodePath());
    
	return _bone_paths[index];
}
void CharacterSkeleton3D::set_bone_path(int index, NodePath path) {
    ERR_FAIL_INDEX(index, EntityEnums::SKELETON_POINTS_MAX);
    
	_bone_paths[index] = path;

	_bone_nodes[index] = get_node_or_null(path);
}

Ref<CharacterSkeletonVisualEntry> CharacterSkeleton3D::get_visual(int index) {
	ERR_FAIL_INDEX_V(index, EntityEnums::SKELETON_POINTS_MAX, Ref<CharacterSkeletonVisualEntry>());

	return _visuals[index];
}
void CharacterSkeleton3D::set_visual(int index, Ref<CharacterSkeletonVisualEntry> entry) {
	ERR_FAIL_INDEX(index, EntityEnums::SKELETON_POINTS_MAX);

	_visuals[index] = entry;
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

CharacterSkeleton3D::CharacterSkeleton3D() {
	for (int i = 0; i < EntityEnums::SKELETON_POINTS_MAX; ++i) {
		_bone_nodes[i] = NULL;
	}

	_animation_player = NULL;
}

void CharacterSkeleton3D::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_ENTER_TREE: {
			update_nodes();
		} break;
		case NOTIFICATION_PROCESS: {
		} break;
		case NOTIFICATION_EXIT_TREE: {

		} break;
	}
}

void CharacterSkeleton3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_bone_path", "index"), &CharacterSkeleton3D::get_bone_path);
	ClassDB::bind_method(D_METHOD("set_bone_path", "index", "path"), &CharacterSkeleton3D::set_bone_path);

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

    ADD_GROUP("Bone Paths", "bone_path_");
	ADD_PROPERTYI(PropertyInfo(Variant::NODE_PATH, "bone_path_root"), "set_bone_path", "get_bone_path", EntityEnums::SKELETON_POINT_ROOT);

	ClassDB::bind_method(D_METHOD("get_bone_node", "bone_idx"), &CharacterSkeleton3D::get_bone_node);

	ClassDB::bind_method(D_METHOD("get_animation_player_path"), &CharacterSkeleton3D::get_animation_player_path);
	ClassDB::bind_method(D_METHOD("set_animation_player_path", "path"), &CharacterSkeleton3D::set_animation_player_path);
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "animation_player_path"), "set_animation_player_path", "get_animation_player_path");

	ClassDB::bind_method(D_METHOD("get_animation_tree_path"), &CharacterSkeleton3D::get_animation_tree_path);
	ClassDB::bind_method(D_METHOD("set_animation_tree_path", "path"), &CharacterSkeleton3D::set_animation_tree_path);
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "animation_tree_path"), "set_animation_tree_path", "get_animation_tree_path");

	ClassDB::bind_method(D_METHOD("get_animation_player"), &CharacterSkeleton3D::get_animation_player);
	ClassDB::bind_method(D_METHOD("get_animation_tree"), &CharacterSkeleton3D::get_animation_tree);

	ClassDB::bind_method(D_METHOD("update_nodes"), &CharacterSkeleton3D::update_nodes);
}
