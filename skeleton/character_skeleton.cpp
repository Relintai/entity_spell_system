#include "character_skeleton.h"


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
	set_animation_player_path(_animation_player_path);
	set_animation_tree_path(_animation_tree_path);
}

CharacterSkeleton::CharacterSkeleton() {
	_animation_player = NULL;
	_animation_tree = NULL;
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
