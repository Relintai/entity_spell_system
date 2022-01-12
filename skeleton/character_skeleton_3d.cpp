/*
Copyright (c) 2019-2022 Péter Magyar

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

#include "character_skeleton_3d.h"

#include "../singletons/ess.h"

#include "../data/items/model_visual.h"

#include "../defines.h"

int CharacterSkeleton3D::get_entity_type() const {
	return _entity_type;
}
void CharacterSkeleton3D::set_entity_type(const int value) {
	_entity_type = value;

	int bones_size = ESS::get_singleton()->skeletons_bones_index_get(_entity_type).get_slice_count(",");
	int attachment_size = ESS::get_singleton()->skeletons_bone_attachment_index_get(_entity_type).get_slice_count(",");

	_attach_point_nodes.resize(attachment_size);
	_entries.resize(bones_size);
}

int CharacterSkeleton3D::get_model_index() {
	return _model_index;
}
void CharacterSkeleton3D::set_model_index(int value) {
	_model_index = value;
}

bool CharacterSkeleton3D::get_model_dirty() const {
	return _model_dirty;
}
void CharacterSkeleton3D::set_model_dirty(bool value) {
	_model_dirty = value;
}

NodePath CharacterSkeleton3D::attach_point_path_get(const int index) const {
	ERR_FAIL_INDEX_V(index, _attach_point_nodes.size(), NodePath());

	return _attach_point_nodes[index].path;
}
void CharacterSkeleton3D::attach_point_path_set(const int index, const NodePath &path) {
	ERR_FAIL_INDEX(index, _attach_point_nodes.size());

	_attach_point_nodes.write[index].path = path;
	_attach_point_nodes.write[index].node = get_node_or_null(path);
}

Node *CharacterSkeleton3D::attach_point_node_get(const int index) {
	ERR_FAIL_INDEX_V(index, _attach_point_nodes.size(), NULL);

	return _attach_point_nodes[index].node;
}

int CharacterSkeleton3D::attach_point_count() const {
	return _attach_point_nodes.size();
}

Node *CharacterSkeleton3D::common_attach_point_node_get(const EntityEnums::CommonCharacterSkeletonPoints index) {
	ERR_FAIL_INDEX_V(common_attach_point_index_get(index), _attach_point_nodes.size(), NULL);

	return _attach_point_nodes[common_attach_point_index_get(index)].node;
}
void CharacterSkeleton3D::common_attach_point_add(const EntityEnums::CommonCharacterSkeletonPoints point, const Ref<PackedScene> &scene) {
	int index = common_attach_point_index_get(point);

	ERR_FAIL_INDEX(index, _attach_point_nodes.size());

	Node *n = _attach_point_nodes[index].node;

	if (INSTANCE_VALIDATE(n) && n->has_method("add")) {
		n->call("add", scene);
	}
}
void CharacterSkeleton3D::common_attach_point_add_timed(const EntityEnums::CommonCharacterSkeletonPoints point, const Ref<PackedScene> &scene, const float time) {
	int index = common_attach_point_index_get(point);

	ERR_FAIL_INDEX(index, _attach_point_nodes.size());

	Node *n = _attach_point_nodes[index].node;

	if (INSTANCE_VALIDATE(n) && n->has_method("add_timed")) {
		n->call("add_timed", scene, time);
	}
}
void CharacterSkeleton3D::common_attach_point_remove(const EntityEnums::CommonCharacterSkeletonPoints point, const Ref<PackedScene> &scene) {
	int index = common_attach_point_index_get(point);

	ERR_FAIL_INDEX(index, _attach_point_nodes.size());

	Node *n = _attach_point_nodes[index].node;

	if (INSTANCE_VALIDATE(n) && n->has_method("remove")) {
		n->call("remove", scene);
	}
}
int CharacterSkeleton3D::common_attach_point_index_get(const EntityEnums::CommonCharacterSkeletonPoints point) {
	return call("_common_attach_point_index_get", point);
}
int CharacterSkeleton3D::_common_attach_point_index_get(const EntityEnums::CommonCharacterSkeletonPoints point) {
	return 0;
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
	for (int i = 0; i < _attach_point_nodes.size(); ++i) {
		_attach_point_nodes.write[i].node = get_node_or_null(_attach_point_nodes[i].path);
	}

	set_animation_player_path(_animation_player_path);
	set_animation_tree_path(_animation_tree_path);
}

int CharacterSkeleton3D::bone_additional_mesh_transform_bone_index_get(const int index) const {
	ERR_FAIL_INDEX_V(index, _bone_model_additional_mesh_transforms.size(), 0);

	return _bone_model_additional_mesh_transforms[index].bone_index;
}
void CharacterSkeleton3D::bone_additional_mesh_transform_bone_index_set(const int index, const int bone_index) {
	ERR_FAIL_INDEX(index, _bone_model_additional_mesh_transforms.size());

	_bone_model_additional_mesh_transforms.write[index].bone_index = bone_index;
}

Transform CharacterSkeleton3D::bone_additional_mesh_transform_transform_get(const int index) const {
	ERR_FAIL_INDEX_V(index, _bone_model_additional_mesh_transforms.size(), Transform());

	return _bone_model_additional_mesh_transforms[index].transform;
}
void CharacterSkeleton3D::bone_additional_mesh_transform_transform_set(const int index, const Transform &transform) {
	ERR_FAIL_INDEX(index, _bone_model_additional_mesh_transforms.size());

	_bone_model_additional_mesh_transforms.write[index].transform = transform;
}

Transform CharacterSkeleton3D::bone_additional_mesh_transform_user_transform_get(const int index) const {
	ERR_FAIL_INDEX_V(index, _bone_model_additional_mesh_transforms.size(), Transform());

	return _bone_model_additional_mesh_transforms[index].user_transform;
}
void CharacterSkeleton3D::bone_additional_mesh_transform_user_transform_set(const int index, const Transform &transform) {
	ERR_FAIL_INDEX(index, _bone_model_additional_mesh_transforms.size());

	_bone_model_additional_mesh_transforms.write[index].user_transform = transform;
}

void CharacterSkeleton3D::bone_additional_mesh_transform_set_count(const int size) {
	_bone_model_additional_mesh_transforms.resize(size);
}
int CharacterSkeleton3D::bone_additional_mesh_transform_get_count() const {
	return _bone_model_additional_mesh_transforms.size();
}

void CharacterSkeleton3D::add_model_visual(Ref<ModelVisual> vis) {
	ERR_FAIL_COND(!vis.is_valid());

	for (int i = 0; i < vis->get_visual_entry_count(); ++i) {
		Ref<ModelVisualEntry> e = vis->get_visual_entry(i);

		if (e.is_valid())
			add_model_visual_entry(vis, e);
	}

	_model_visuals.push_back(vis);

	set_process(true);
	_model_dirty = true;
}
void CharacterSkeleton3D::remove_model_visual(Ref<ModelVisual> vis) {
	ERR_FAIL_COND(!vis.is_valid());

	int index = _model_visuals.find(vis);

	if (index == -1)
		return;

	for (int i = 0; i < vis->get_visual_entry_count(); ++i) {
		Ref<ModelVisualEntry> e = vis->get_visual_entry(i);

		if (e.is_valid())
			remove_model_visual_entry(vis, e);
	}

	_model_visuals.remove(index);

	set_process(true);
	_model_dirty = true;
}
void CharacterSkeleton3D::remove_model_visual_index(int index) {
	ERR_FAIL_INDEX(index, _model_visuals.size());

	set_process(true);
	_model_dirty = true;

	_model_visuals.remove(index);
}
Ref<ModelVisual> CharacterSkeleton3D::get_model_visual(int index) {
	ERR_FAIL_INDEX_V(index, _model_visuals.size(), Ref<ModelVisual>());

	set_process(true);
	_model_dirty = true;

	return _model_visuals.get(index);
}
int CharacterSkeleton3D::get_model_visual_count() {
	return _model_visuals.size();
}
void CharacterSkeleton3D::clear_model_visuals() {
	_model_visuals.clear();

	for (int i = 0; i < _entries.size(); ++i) {
		_entries.write[i].clear();
	}

	_model_dirty = true;
	set_process(true);
}

void CharacterSkeleton3D::add_model_visual_entry(Ref<ModelVisual> vis, Ref<ModelVisualEntry> ive) {
	ERR_FAIL_COND(!vis.is_valid());
	ERR_FAIL_COND(!ive.is_valid());

	if (ive->get_type() == ModelVisualEntry::MODEL_VISUAL_ENTRY_TYPE_ATTACHMENT) {
		EntityEnums::CommonCharacterSkeletonPoints target_bone = static_cast<EntityEnums::CommonCharacterSkeletonPoints>(ive->get_bone());

		for (int i = 0; i < ive->get_size(); ++i) {
			Ref<PackedScene> ps = ive->get_attachment(i);

			if (ps.is_valid()) {
				common_attach_point_add(target_bone, ps);
			}
		}

		return;
	}

	int target_bone_idx = ive->get_bone();

	Vector<Ref<SkeletonModelEntry> > &entries = _entries.write[target_bone_idx];

	for (int i = 0; i < entries.size(); ++i) {
		Ref<SkeletonModelEntry> e = entries.get(i);

		if (e->get_entry() == ive) {
			e->set_count(e->get_count() + 1);
			return;
		}
	}

	Ref<SkeletonModelEntry> e;
	e.instance();

	e->set_priority(vis->get_layer());
	//e->set_color(ive->get_color());
	e->set_entry(ive);

	entries.push_back(e);
	_model_dirty = true;
	set_process(true);
}
void CharacterSkeleton3D::remove_model_visual_entry(Ref<ModelVisual> vis, Ref<ModelVisualEntry> ive) {
	ERR_FAIL_COND(!vis.is_valid());
	ERR_FAIL_COND(!ive.is_valid());

	if (ive->get_type() == ModelVisualEntry::MODEL_VISUAL_ENTRY_TYPE_ATTACHMENT) {
		EntityEnums::CommonCharacterSkeletonPoints target_bone = static_cast<EntityEnums::CommonCharacterSkeletonPoints>(ive->get_bone());

		for (int i = 0; i < ive->get_size(); ++i) {
			Ref<PackedScene> ps = ive->get_attachment(i);

			if (ps.is_valid()) {
				common_attach_point_remove(target_bone, ps);
			}
		}

		return;
	}

	int target_bone_idx = ive->get_bone();

	Vector<Ref<SkeletonModelEntry> > &entries = _entries.write[target_bone_idx];

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
	ERR_FAIL_INDEX_V(bone_index, _entries.size(), Ref<SkeletonModelEntry>());
	ERR_FAIL_INDEX_V(index, _entries[bone_index].size(), Ref<SkeletonModelEntry>());

	return _entries[bone_index].get(index);
}
int CharacterSkeleton3D::get_model_entry_count(const int bone_index) {
	ERR_FAIL_INDEX_V(bone_index, _entries.size(), 0);

	return _entries[bone_index].size();
}

void CharacterSkeleton3D::sort_layers() {
	for (int i = 0; i < _entries.size(); ++i) {
		Vector<Ref<SkeletonModelEntry> > &entries = _entries.write[i];

		entries.sort_custom<_ModelEntryComparator>();
	}
}

void CharacterSkeleton3D::build_model() {
	call("_build_model");
}

void CharacterSkeleton3D::_build_model() {
	set_process(false);
}

Array CharacterSkeleton3D::merge_mesh_array(Array arr) const {
	ERR_FAIL_COND_V(arr.size() != VisualServer::ARRAY_MAX, arr);

	PoolVector3Array verts = arr[VisualServer::ARRAY_VERTEX];
	PoolVector3Array normals = arr[VisualServer::ARRAY_NORMAL];
	PoolVector2Array uvs = arr[VisualServer::ARRAY_TEX_UV];
	PoolColorArray colors = arr[VisualServer::ARRAY_COLOR];
	PoolIntArray indices = arr[VisualServer::ARRAY_INDEX];
	PoolIntArray bones = arr[VisualServer::ARRAY_BONES];
	PoolRealArray weights = arr[VisualServer::ARRAY_WEIGHTS];

	int i = 0;
	while (i < verts.size()) {
		Vector3 v = verts[i];

		Array equals;
		for (int j = i + 1; j < verts.size(); ++j) {
			Vector3 vc = verts[j];

			if (Math::is_equal_approx(v.x, vc.x) && Math::is_equal_approx(v.y, vc.y) && Math::is_equal_approx(v.z, vc.z))
				equals.push_back(j);
		}

		for (int k = 0; k < equals.size(); ++k) {
			int rem = equals[k];
			int remk = rem - k;

			verts.remove(remk);
			normals.remove(remk);
			uvs.remove(remk);
			colors.remove(remk);

			int bindex = remk * 4;
			for (int l = 0; l < 4; ++l) {
				bones.remove(bindex);
				weights.remove(bindex);
			}

			for (int j = 0; j < indices.size(); ++j) {
				int indx = indices[j];

				if (indx == remk)
					indices.set(j, i);
				else if (indx > remk)
					indices.set(j, indx - 1);
			}
		}

		++i;
	}

	arr[VisualServer::ARRAY_VERTEX] = verts;
	arr[VisualServer::ARRAY_NORMAL] = normals;
	arr[VisualServer::ARRAY_TEX_UV] = uvs;
	arr[VisualServer::ARRAY_COLOR] = colors;
	arr[VisualServer::ARRAY_INDEX] = indices;
	arr[VisualServer::ARRAY_BONES] = bones;
	arr[VisualServer::ARRAY_WEIGHTS] = weights;

	return arr;
}
Array CharacterSkeleton3D::bake_mesh_array_uv(Array arr, Ref<Texture> tex, float mul_color) const {
	ERR_FAIL_COND_V(arr.size() != VisualServer::ARRAY_MAX, arr);
	ERR_FAIL_COND_V(!tex.is_valid(), arr);

	Ref<Image> img = tex->get_data();

	ERR_FAIL_COND_V(!img.is_valid(), arr);

	Vector2 imgsize = img->get_size();

	PoolVector2Array uvs = arr[VisualServer::ARRAY_TEX_UV];
	PoolColorArray colors = arr[VisualServer::ARRAY_COLOR];

#if !GODOT4
	img->lock();
#endif

	for (int i = 0; i < uvs.size(); ++i) {
		Vector2 uv = uvs[i];
		uv *= imgsize;

		Color c = img->get_pixelv(uv);

		colors.set(i, colors[i] * c * mul_color);
	}

#if !GODOT4
	img->unlock();
#endif

	arr[VisualServer::ARRAY_COLOR] = colors;

	return arr;
}

CharacterSkeleton3D::CharacterSkeleton3D() {
	_model_dirty = false;
	_model_index = 0;
	_entity_type = 0;

	_animation_player = NULL;
	_animation_tree = NULL;
}

CharacterSkeleton3D::~CharacterSkeleton3D() {
	_attach_point_nodes.clear();

	for (int i = 0; i < _entries.size(); ++i) {
		_entries.write[i].clear();
	}

	_entries.clear();

	_model_visuals.clear();
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

bool CharacterSkeleton3D::_set(const StringName &p_name, const Variant &p_value) {
	String name = p_name;

	if (name.begins_with("attach_point_paths")) {
		int index = name.get_slicec('/', 1).get_slicec('_', 0).to_int();

		if (index >= _attach_point_nodes.size()) {
			_attach_point_nodes.resize(index + 1);
		}

		NodePath np = p_value;

		_attach_point_nodes.write[index].path = np;

		if (is_inside_tree())
			_attach_point_nodes.write[index].node = get_node_or_null(p_value);

		return true;
	} else if (name.begins_with("bone_model_additional_mesh_transforms")) {
		int index = name.get_slicec('/', 1).to_int();

		if (index >= _bone_model_additional_mesh_transforms.size()) {
			_bone_model_additional_mesh_transforms.resize(index + 1);
		}

		String p = name.get_slicec('/', 2);

		if (p == "bone_index") {
			int bi = p_value;

			_bone_model_additional_mesh_transforms.write[index].bone_index = bi;

			return true;
		} else if (p == "transform") {
			Transform tf = p_value;

			_bone_model_additional_mesh_transforms.write[index].transform = tf;

			return true;
		} else if (p == "user_transform") {
			Transform tf = p_value;

			_bone_model_additional_mesh_transforms.write[index].user_transform = tf;

			return true;
		}

		return false;
	}

	return false;
}
bool CharacterSkeleton3D::_get(const StringName &p_name, Variant &r_ret) const {
	String name = p_name;

	if (name.begins_with("attach_point_paths")) {
		int index = name.get_slicec('/', 1).get_slicec('_', 0).to_int();

		if (index >= _attach_point_nodes.size()) {
			return false;
		}

		r_ret = _attach_point_nodes[index].path;

		return true;
	} else if (name.begins_with("bone_model_additional_mesh_transforms")) {
		int index = name.get_slicec('/', 1).to_int();

		if (index >= _bone_model_additional_mesh_transforms.size()) {
			return false;
		}

		String p = name.get_slicec('/', 2);

		if (p == "bone_index") {
			r_ret = _bone_model_additional_mesh_transforms[index].bone_index;

			return true;
		} else if (p == "transform") {
			r_ret = _bone_model_additional_mesh_transforms[index].transform;

			return true;
		} else if (p == "user_transform") {
			r_ret = _bone_model_additional_mesh_transforms[index].user_transform;

			return true;
		}

		return false;
	}

	return false;
}
void CharacterSkeleton3D::_get_property_list(List<PropertyInfo> *p_list) const {
	if (ESS::get_singleton()->skeletons_bone_attachments_count() == 0) {
		return;
	}

	String bones = ESS::get_singleton()->skeletons_bone_attachment_index_get(_entity_type);
	int slicec = bones.get_slice_count(",");

	for (int i = 0; i < slicec; ++i) {
		p_list->push_back(PropertyInfo(Variant::NODE_PATH, "attach_point_paths/" + itos(i) + "_" + bones.get_slicec(',', i)));
	}

	for (int i = 0; i < _bone_model_additional_mesh_transforms.size(); ++i) {
		p_list->push_back(PropertyInfo(Variant::INT, "bone_model_additional_mesh_transforms/" + itos(i) + "/bone_index", PROPERTY_HINT_ENUM, ESS::get_singleton()->skeletons_bones_index_get(_entity_type)));
		p_list->push_back(PropertyInfo(Variant::TRANSFORM, "bone_model_additional_mesh_transforms/" + itos(i) + "/transform"));
		p_list->push_back(PropertyInfo(Variant::TRANSFORM, "bone_model_additional_mesh_transforms/" + itos(i) + "/user_transform"));
	}
}

void CharacterSkeleton3D::_validate_property(PropertyInfo &property) const {
	if (property.name == "entity_type") {
		property.hint_string = ESS::get_singleton()->entity_types_get();
	}
}

void CharacterSkeleton3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_entity_type"), &CharacterSkeleton3D::get_entity_type);
	ClassDB::bind_method(D_METHOD("set_entity_type", "value"), &CharacterSkeleton3D::set_entity_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "entity_type", PROPERTY_HINT_ENUM, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_entity_type", "get_entity_type");

	ClassDB::bind_method(D_METHOD("get_model_index"), &CharacterSkeleton3D::get_model_index);
	ClassDB::bind_method(D_METHOD("set_model_index", "value"), &CharacterSkeleton3D::set_model_index);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "model_index"), "set_model_index", "get_model_index");

	ClassDB::bind_method(D_METHOD("add_model_visual", "vis"), &CharacterSkeleton3D::add_model_visual);
	ClassDB::bind_method(D_METHOD("remove_model_visual", "vis"), &CharacterSkeleton3D::remove_model_visual);
	ClassDB::bind_method(D_METHOD("remove_model_visual_index", "index"), &CharacterSkeleton3D::remove_model_visual_index);
	ClassDB::bind_method(D_METHOD("get_model_visual", "index"), &CharacterSkeleton3D::get_model_visual);
	ClassDB::bind_method(D_METHOD("get_model_visual_count"), &CharacterSkeleton3D::get_model_visual_count);
	ClassDB::bind_method(D_METHOD("clear_model_visuals"), &CharacterSkeleton3D::clear_model_visuals);

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

	ClassDB::bind_method(D_METHOD("bone_additional_mesh_transform_bone_index_get", "index"), &CharacterSkeleton3D::bone_additional_mesh_transform_bone_index_get);
	ClassDB::bind_method(D_METHOD("bone_additional_mesh_transform_bone_index_set", "index", "bone_index"), &CharacterSkeleton3D::bone_additional_mesh_transform_bone_index_set);

	ClassDB::bind_method(D_METHOD("bone_additional_mesh_transform_transform_get", "index"), &CharacterSkeleton3D::bone_additional_mesh_transform_transform_get);
	ClassDB::bind_method(D_METHOD("bone_additional_mesh_transform_transform_set", "index", "transform"), &CharacterSkeleton3D::bone_additional_mesh_transform_transform_set);

	ClassDB::bind_method(D_METHOD("bone_additional_mesh_transform_user_transform_get", "index"), &CharacterSkeleton3D::bone_additional_mesh_transform_user_transform_get);
	ClassDB::bind_method(D_METHOD("bone_additional_mesh_transform_user_transform_set", "index", "transform"), &CharacterSkeleton3D::bone_additional_mesh_transform_user_transform_set);

	ClassDB::bind_method(D_METHOD("bone_additional_mesh_transform_set_count", "size"), &CharacterSkeleton3D::bone_additional_mesh_transform_set_count);
	ClassDB::bind_method(D_METHOD("bone_additional_mesh_transform_get_count"), &CharacterSkeleton3D::bone_additional_mesh_transform_get_count);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "bone_additional_mesh_transform_count", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "bone_additional_mesh_transform_set_count", "bone_additional_mesh_transform_get_count");

	ClassDB::bind_method(D_METHOD("add_model_visual_entry", "vis", "ive"), &CharacterSkeleton3D::add_model_visual_entry);
	ClassDB::bind_method(D_METHOD("remove_model_visual_entry", "vis", "ive"), &CharacterSkeleton3D::remove_model_visual_entry);
	ClassDB::bind_method(D_METHOD("get_model_entry", "bone_index", "index"), &CharacterSkeleton3D::get_model_entry);
	ClassDB::bind_method(D_METHOD("get_model_entry_count", "bone_index"), &CharacterSkeleton3D::get_model_entry_count);

	ClassDB::bind_method(D_METHOD("sort_layers"), &CharacterSkeleton3D::sort_layers);

	ClassDB::bind_method(D_METHOD("build_model"), &CharacterSkeleton3D::build_model);
	ClassDB::bind_method(D_METHOD("_build_model"), &CharacterSkeleton3D::_build_model);

	ClassDB::bind_method(D_METHOD("merge_mesh_array", "arr"), &CharacterSkeleton3D::merge_mesh_array);
	ClassDB::bind_method(D_METHOD("bake_mesh_array_uv", "arr", "tex", "mul_color"), &CharacterSkeleton3D::bake_mesh_array_uv, DEFVAL(0.7));

	//Bone Paths
	ClassDB::bind_method(D_METHOD("attach_point_path_get", "index"), &CharacterSkeleton3D::attach_point_path_get);
	ClassDB::bind_method(D_METHOD("attach_point_path_set", "index", "path"), &CharacterSkeleton3D::attach_point_path_set);

	ClassDB::bind_method(D_METHOD("attach_point_node_get", "index"), &CharacterSkeleton3D::attach_point_node_get);

	ClassDB::bind_method(D_METHOD("attach_point_count"), &CharacterSkeleton3D::attach_point_count);

	BIND_VMETHOD(MethodInfo("_common_attach_point_index_get", PropertyInfo(Variant::INT, "point", PROPERTY_HINT_NONE, EntityEnums::BINDING_STRING_COMMON_CHARCATER_SKELETON_POINTS)));

	ClassDB::bind_method(D_METHOD("common_attach_point_node_get", "point"), &CharacterSkeleton3D::common_attach_point_node_get);
	ClassDB::bind_method(D_METHOD("common_attach_point_add", "point", "scene"), &CharacterSkeleton3D::common_attach_point_add);
	ClassDB::bind_method(D_METHOD("common_attach_point_add_timed", "point", "scene", "time"), &CharacterSkeleton3D::common_attach_point_add_timed);
	ClassDB::bind_method(D_METHOD("common_attach_point_remove", "point", "scene"), &CharacterSkeleton3D::common_attach_point_remove);
	ClassDB::bind_method(D_METHOD("common_attach_point_index_get", "point"), &CharacterSkeleton3D::common_attach_point_index_get);
	ClassDB::bind_method(D_METHOD("_common_attach_point_index_get", "point"), &CharacterSkeleton3D::_common_attach_point_index_get);

	ClassDB::bind_method(D_METHOD("get_animation_player"), &CharacterSkeleton3D::get_animation_player);
	ClassDB::bind_method(D_METHOD("get_animation_tree"), &CharacterSkeleton3D::get_animation_tree);

	ClassDB::bind_method(D_METHOD("update_nodes"), &CharacterSkeleton3D::update_nodes);
}
