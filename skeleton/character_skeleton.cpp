#include "character_skeleton.h"


NodePath CharacterSkeleton::get_bone_path(int index) {
    ERR_FAIL_INDEX_V(index, EntityEnums::MAX_BONE_ID, NodePath());
    
	return _bone_paths[index];
}

void CharacterSkeleton::set_bone_path(int index, NodePath path) {
    ERR_FAIL_INDEX(index, EntityEnums::MAX_BONE_ID);
    
	_bone_paths[index] = path;

	_bone_nodes[index] = get_node_or_null(path);
}

Node *CharacterSkeleton::get_bone_node(EntityEnums::CharacterSkeletonBoneId node_id) {
	return _bone_nodes[node_id];
}

NodePath CharacterSkeleton::get_animation_player_path() {
	return _animation_player_path;
}

void CharacterSkeleton::set_animation_player_path(NodePath path) {
	_animation_player_path = path;

	Node *node = get_node_or_null(_animation_player_path);

	if (node != NULL) {
		_animation_player = Object::cast_to<AnimationPlayer>(node);
	} else {
		_animation_player = NULL;
	}
}

AnimationPlayer *CharacterSkeleton::get_animation_player() {
	return _animation_player;
}

NodePath CharacterSkeleton::get_animation_tree_path() {
	return _animation_tree_path;
}

void CharacterSkeleton::set_animation_tree_path(NodePath path) {
	_animation_tree_path = path;

	Node *node = get_node_or_null(_animation_tree_path);

	if (node != NULL) {
		_animation_tree = Object::cast_to<AnimationTree>(node);
	} else {
		_animation_tree = NULL;
	}
}

AnimationTree *CharacterSkeleton::get_animation_tree() {
	return _animation_tree;
}

void CharacterSkeleton::update_nodes() {
    for (int i = 0; i < EntityEnums::MAX_BONE_ID; ++i) {
        _bone_nodes[i] = get_node_or_null(_bone_paths[i]);
    }

	set_animation_player_path(_animation_player_path);
	set_animation_tree_path(_animation_tree_path);
}

CharacterSkeleton::CharacterSkeleton() {
	for (int i = 0; i < EntityEnums::MAX_BONE_ID; ++i) {
		_bone_nodes[i] = NULL;
	}

	_animation_player = NULL;
}

void CharacterSkeleton::_notification(int p_what) {
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

void CharacterSkeleton::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_bone_path", "index"), &CharacterSkeleton::get_bone_path);
	ClassDB::bind_method(D_METHOD("set_bone_path", "index", "path"), &CharacterSkeleton::set_bone_path);

    ADD_GROUP("Bone Paths", "bone_path_");
    ADD_PROPERTYI(PropertyInfo(Variant::NODE_PATH, "bone_path_hip"), "set_bone_path", "get_bone_path", EntityEnums::BONE_ID_HIP);
    ADD_PROPERTYI(PropertyInfo(Variant::NODE_PATH, "bone_path_left_hand"), "set_bone_path", "get_bone_path", EntityEnums::BONE_ID_LEFT_HAND);
    ADD_PROPERTYI(PropertyInfo(Variant::NODE_PATH, "bone_path_right_hand"), "set_bone_path", "get_bone_path", EntityEnums::BONE_ID_RIGHT_HAND);

	ClassDB::bind_method(D_METHOD("get_bone_node", "bone_idx"), &CharacterSkeleton::get_bone_node);

	ClassDB::bind_method(D_METHOD("get_animation_player_path"), &CharacterSkeleton::get_animation_player_path);
	ClassDB::bind_method(D_METHOD("set_animation_player_path", "path"), &CharacterSkeleton::set_animation_player_path);
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "animation_player_path"), "set_animation_player_path", "get_animation_player_path");

	ClassDB::bind_method(D_METHOD("get_animation_tree_path"), &CharacterSkeleton::get_animation_tree_path);
	ClassDB::bind_method(D_METHOD("set_animation_tree_path", "path"), &CharacterSkeleton::set_animation_tree_path);
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "animation_tree_path"), "set_animation_tree_path", "get_animation_tree_path");

	ClassDB::bind_method(D_METHOD("get_animation_player"), &CharacterSkeleton::get_animation_player);
	ClassDB::bind_method(D_METHOD("get_animation_tree"), &CharacterSkeleton::get_animation_tree);

	ClassDB::bind_method(D_METHOD("update_nodes"), &CharacterSkeleton::update_nodes);
}
