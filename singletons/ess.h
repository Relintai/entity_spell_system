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

#ifndef ESS_H
#define ESS_H

#include "core/version.h"

#if VERSION_MAJOR > 3
#include "core/config/engine.h"
#include "core/core_bind.h"
#include "core/io/resource.h"
#include "core/object/object.h"
#include "core/string/ustring.h"
#else
#include "core/bind/core_bind.h"
#include "core/engine.h"
#include "core/object.h"
#include "core/resource.h"
#include "core/ustring.h"
#endif

#include "scene/main/node.h"

#include "../defines.h"

class ESSResourceDB;
class ESSEntitySpawner;
class EntityCreateInfo;
class ESSMaterialCache;

class ESS : public Object {
	GDCLASS(ESS, Object);

public:
	static ESS *get_singleton();

	bool get_use_spell_points() const;
	void set_use_spell_points(const bool value);

	bool get_scale_spells_by_default() const;
	void set_scale_spells_by_default(const bool value);

	bool get_automatic_load() const;
	void set_automatic_load(const bool load);

	bool get_load_folders() const;
	void set_load_folders(const bool load);

	bool get_use_class_xp() const;
	void set_use_class_xp(const bool value);

	bool get_allow_class_spell_learning() const;
	void set_allow_class_spell_learning(const bool value);

	bool get_allow_class_recipe_learning() const;
	void set_allow_class_recipe_learning(const bool value);

	int get_auto_learn_spells() const;
	void set_auto_learn_spells(const int value);

	Ref<ESSResourceDB> get_resource_db();
	void set_resource_db(const Ref<ESSResourceDB> &resource_db);

	ESSEntitySpawner *get_entity_spawner();
	void set_entity_spawner(ESSEntitySpawner *spawner);
	void set_entity_spawner_bind(Node *spawner);

	String get_resource_db_path();
	void set_resource_db_path(const String &path);

	void request_entity_spawn(Ref<EntityCreateInfo> info);
	void request_entity_spawn_deferred(Ref<EntityCreateInfo> info);

	void load_resource_db();
	Ref<Resource> load_resource(const String &path, const String &type_hint = "");

	void load_all();

	//Stats
	String stat_get_string() const;
	void stat_set_string(const String &stat_enum_string);

	int stat_get_id(const StringName &name) const;
	StringName stat_get_name(const int id) const;

	int stat_get_property_id(const StringName &name) const;
	StringName stat_get_property_name(const int id) const;
	bool stat_is_property(const StringName &name) const;

	int stat_get_count() const;

	PoolStringArray stats_get() const;
	void stats_set(const PoolStringArray &array);

	int stat_get_main_stat_count() const;
	void stat_set_main_stat_count(const int index);

	//Equipslots
	String equip_slot_get_string() const;
	void equip_slot_set_string(const String &equip_slot_enum_string);

	int equip_slot_get_id(const StringName &name) const;
	StringName equip_slot_get_name(const int id) const;

	int equip_slot_get_property_id(const StringName &name) const;
	StringName equip_slot_get_property_name(const int id) const;
	bool equip_slot_is_property(const StringName &name) const;

	int equip_slot_get_count() const;

	PoolStringArray equip_slots_get() const;
	void equip_slots_set(const PoolStringArray &array);

	//Skeletons
	String entity_types_get() const;
	void entity_types_set(const String &value);

	String skeletons_bones_index_get(const int index) const;
	int skeletons_bones_count();

	PoolStringArray skeletons_bones_get() const;
	void skeletons_bones_set(const PoolStringArray &value);

	String skeletons_bone_attachment_index_get(const int index) const;
	int skeletons_bone_attachments_count();

	PoolStringArray skeletons_bone_attachment_points_get() const;
	void skeletons_bone_attachment_points_set(const PoolStringArray &value);

	//Other
	String model_visual_groups_get() const;
	void model_visual_groups_set(const String &value);

	String texture_layers_get() const;
	void texture_layers_set(const String &value);

	//Diminishing Returns
	String dminishing_return_categories_get() const;
	void dminishing_return_categories_set(const String &value);

	float dminishing_return_length_get() const;
	void dminishing_return_length_set(const float value);

	int dminishing_return_steps_get() const;
	void dminishing_return_steps_set(const int value);

	//Levels/XP
	int get_max_character_level() const;
	int get_max_class_level() const;

	int get_character_xp(int current_level);
	void set_character_xp(int current_level, int value);
	bool can_character_level_up(int current_level);

	PoolIntArray get_character_xp_data();
	void set_character_xp_data(const PoolIntArray &data);

	int get_class_xp(int current_level);
	void set_class_xp(int current_level, int value);
	bool can_class_level_up(int current_level);

	PoolIntArray get_class_xp_data();
	void set_class_xp_data(const PoolIntArray &data);

#ifdef TEXTURE_PACKER_PRESENT
	int get_texture_flags() const;
	void set_texture_flags(const int flags);

	int get_max_atlas_size() const;
	void set_max_atlas_size(const int size);

	bool get_keep_original_atlases() const;
	void set_keep_original_atlases(const bool value);

	Color get_background_color() const;
	void set_background_color(const Color &color);

	int get_margin() const;
	void set_margin(const int margin);
#endif

	StringName get_default_ess_material_cache_class();
	void set_default_ess_material_cache_class(const StringName &cls_name);

	PoolStringArray material_paths_get() const;
	void material_paths_set(const PoolStringArray &array);

	void material_add(const Ref<Material> &value);
	Ref<Material> material_get(const int index);
	void material_set(const int index, const Ref<Material> &value);
	void material_remove(const int index);
	int material_get_num() const;
	void materials_clear();
	void materials_load();
	void ensure_materials_loaded();

	Vector<Variant> materials_get();
	void materials_set(const Vector<Variant> &materials);

	Ref<ESSMaterialCache> material_cache_get(const uint64_t key);
	void material_cache_unref(const uint64_t key);

	ESS();
	~ESS();

protected:
	static void _bind_methods();

private:
	bool _automatic_load;

	Ref<ESSResourceDB> _ess_resource_db;
	ESSEntitySpawner *_ess_entity_spawner;

	String _ess_resource_db_path;

	static ESS *instance;

	bool _use_spell_points;
	bool _scale_spells_by_default;
	bool _automatic_class_levelups;
	bool _use_global_class_level;
	bool _use_class_xp;
	bool _allow_class_spell_learning;
	bool _allow_class_recipe_learning;
	bool _auto_learn_spells;

	//Stats
	Vector<StringName> _stat_id_to_name;
	HashMap<StringName, int> _stat_name_to_id;

	Vector<StringName> _stat_id_to_property;
	HashMap<StringName, int> _stat_property_to_id;

	String _stat_enum_string;
	int _stat_main_stat_count;

	//Equipslots
	Vector<StringName> _equip_slot_id_to_name;
	HashMap<StringName, int> _equip_slot_name_to_id;

	Vector<StringName> _equip_slot_id_to_property;
	HashMap<StringName, int> _equip_slot_property_to_id;

	String _equip_slot_enum_string;

	//Entity Types
	String _entity_types;
	PoolStringArray _skeletons_bones;
	PoolStringArray _skeletons_bone_attachment_points;

	//Other
	String _model_visual_groups;
	String _texture_layers;

	//Diminishing Returns
	String _dminishing_return_categories;
	float _dminishing_return_length;
	int _dminishing_return_steps;

	//Levels/XP
	PoolIntArray _class_xps;
	PoolIntArray _character_xps;

	StringName _default_ess_material_cache_class;

	Mutex _material_cache_mutex;

	Map<uint64_t, Ref<ESSMaterialCache>> _material_cache;

#ifdef TEXTURE_PACKER_PRESENT
	int _texture_flags;
	int _max_atlas_size;
	bool _keep_original_atlases;
	Color _background_color;
	int _margin;
#endif

	PoolStringArray _material_paths;
	Vector<Ref<Material>> _materials;
};

#endif
