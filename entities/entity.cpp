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

#include "entity.h"

#include "../database/ess_resource_db.h"
#include "../singletons/ess.h"
#include "../singletons/profile_manager.h"

#include "../data/species/entity_species_data.h"
#include "../data/spells/spell.h"
#include "../entities/auras/aura_data.h"
#include "../infos/spell_cast_info.h"
#include "../inventory/bag.h"
#include "../pipelines/spell_damage_info.h"
#include "../pipelines/spell_heal_info.h"
#include "../profiles/class_profile.h"
#include "./data/character_spec.h"
#include "./data/entity_data.h"
#include "./data/vendor_item_data.h"
#include "./data/vendor_item_data_entry.h"
#include "./resources/entity_resource_health.h"
#include "./resources/entity_resource_speed.h"
#include "./skills/entity_skill.h"
#include "scene/2d/node_2d.h"

#if VERSION_MAJOR > 3
#include "core/object/script_language.h"
#else
#include "core/script_language.h"
#endif

#include "core/version.h"

#include "../defines.h"

#define PROPERTY_DEBUG false

#if PROPERTY_DEBUG
#define PROPERTY_USAGE_ENTITY_HIDDEN PROPERTY_USAGE_DEFAULT
#else
#define PROPERTY_USAGE_ENTITY_HIDDEN PROPERTY_USAGE_STORAGE
#endif

#define NOTIFICATION_IMPLS(func, signal, ...)                                          \
	if (_s_entity_controller == EntityEnums::ENITIY_CONTROLLER_AI && _s_ai.is_valid()) \
		_s_ai->func(this, __VA_ARGS__);                                                \
                                                                                       \
	if (has_method("_" #func))                                                         \
		call("_" #func, __VA_ARGS__);                                                  \
                                                                                       \
	for (int i = 0; i < _s_auras.size(); ++i) {                                        \
		Ref<AuraData> ad = _s_auras.get(i);                                            \
		ad->get_aura()->func(ad, __VA_ARGS__);                                         \
	}                                                                                  \
                                                                                       \
	emit_signal(signal, this, __VA_ARGS__);

#define NOTIFICATION_IMPLSS(func, signal)                                              \
	if (_s_entity_controller == EntityEnums::ENITIY_CONTROLLER_AI && _s_ai.is_valid()) \
		_s_ai->func(this);                                                             \
                                                                                       \
	if (has_method("_" #func))                                                         \
		call("_" #func);                                                               \
                                                                                       \
	for (int i = 0; i < _s_auras.size(); ++i) {                                        \
		Ref<AuraData> ad = _s_auras.get(i);                                            \
		ad->get_aura()->func(ad);                                                      \
	}                                                                                  \
                                                                                       \
	emit_signal(signal, this);

#define NOTIFICATION_IMPLC(func, signal, ...)   \
	if (has_method("_" #func))                  \
		call("_" #func, __VA_ARGS__);           \
                                                \
	for (int i = 0; i < _c_auras.size(); ++i) { \
		Ref<AuraData> ad = _c_auras.get(i);     \
		ad->get_aura()->func(ad, __VA_ARGS__);  \
	}                                           \
                                                \
	emit_signal(signal, this, __VA_ARGS__);

#define NOTIFICATION_IMPLCS(func, signal)       \
	if (has_method("_" #func))                  \
		call("_" #func);                        \
                                                \
	for (int i = 0; i < _c_auras.size(); ++i) { \
		Ref<AuraData> ad = _c_auras.get(i);     \
		ad->get_aura()->func(ad);               \
	}                                           \
                                                \
	emit_signal(signal, this);

#define NOTIFICATION_RES_IMPLS(func, signal, ...)                                      \
	if (_s_entity_controller == EntityEnums::ENITIY_CONTROLLER_AI && _s_ai.is_valid()) \
		_s_ai->func(__VA_ARGS__);                                                      \
                                                                                       \
	if (has_method("_" #func))                                                         \
		call("_" #func, __VA_ARGS__);                                                  \
                                                                                       \
	for (int i = 0; i < _s_auras.size(); ++i) {                                        \
		Ref<AuraData> ad = _s_auras.get(i);                                            \
		ad->get_aura()->func(ad, __VA_ARGS__);                                         \
	}                                                                                  \
                                                                                       \
	emit_signal(signal, __VA_ARGS__);

#define NOTIFICATION_RES_IMPLC(func, signal, ...) \
	if (has_method("_" #func))                    \
		call("_" #func, __VA_ARGS__);             \
                                                  \
	for (int i = 0; i < _c_auras.size(); ++i) {   \
		Ref<AuraData> ad = _c_auras.get(i);       \
		ad->get_aura()->func(ad, __VA_ARGS__);    \
	}                                             \
                                                  \
	emit_signal(signal, __VA_ARGS__);

#define NOTIFICATION_AURA_IMPLS(func, signal, what, ...)                               \
	if (_s_entity_controller == EntityEnums::ENITIY_CONTROLLER_AI && _s_ai.is_valid()) \
		_s_ai->func(what, __VA_ARGS__);                                                \
                                                                                       \
	if (has_method("_" #func))                                                         \
		call("_" #func, what, __VA_ARGS__);                                            \
                                                                                       \
	for (int i = 0; i < _s_auras.size(); ++i) {                                        \
		Ref<AuraData> ad = _s_auras.get(i);                                            \
		ad->get_aura()->func(what, ad, __VA_ARGS__);                                   \
	}                                                                                  \
                                                                                       \
	emit_signal(signal, what, __VA_ARGS__);

#define NOTIFICATION_AURA_DIFF_IMPLS(func, aura_func, signal, what, ...)                               \
	if (_s_entity_controller == EntityEnums::ENITIY_CONTROLLER_AI && _s_ai.is_valid()) \
		_s_ai->func(what, __VA_ARGS__);                                                \
                                                                                       \
	if (has_method("_" #func))                                                         \
		call("_" #func, what, __VA_ARGS__);                                            \
                                                                                       \
	for (int i = 0; i < _s_auras.size(); ++i) {                                        \
		Ref<AuraData> ad = _s_auras.get(i);                                            \
		ad->get_aura()->aura_func(what, ad, __VA_ARGS__);                                   \
	}                                                                                  \
                                                                                       \
	emit_signal(signal, what, __VA_ARGS__);

#define NOTIFICATION_AURA_IMPLC(func, signal, what, ...) \
	if (has_method("_" #func))                           \
		call("_" #func, what, __VA_ARGS__);              \
                                                         \
	for (int i = 0; i < _c_auras.size(); ++i) {          \
		Ref<AuraData> ad = _c_auras.get(i);              \
		ad->get_aura()->func(what, ad, __VA_ARGS__);     \
	}                                                    \
                                                         \
	emit_signal(signal, what, __VA_ARGS__);

NodePath Entity::get_body_path() {
	return _body_path;
}
void Entity::set_body_path(NodePath value) {
	_body_path = value;

	set_body(get_node_or_null(_body_path));

	if (INSTANCE_VALIDATE(_body))
		_body->set_owner(this);
}
Node *Entity::get_body() {
	return _body;
}
Spatial *Entity::get_body_3d() {
	return _body_3d;
}
Node2D *Entity::get_body_2d() {
	return _body_2d;
}
void Entity::set_body(Node *body) {
	_body = body;
	_body_2d = Object::cast_to<Node2D>(body);
	_body_3d = Object::cast_to<Spatial>(body);
}

void Entity::instance_body(const Ref<EntityData> &data, const int model_index) {
	if (is_queued_for_deletion())
		return;

	if (get_body() == NULL && data.is_valid() && data->get_entity_species_data().is_valid() &&
			data->get_entity_species_data()->get_model_data_count() > model_index &&
			data->get_entity_species_data()->get_model_data(model_index).is_valid() &&
			data->get_entity_species_data()->get_model_data(model_index)->get_body().is_valid()) {
		Node *node = data->get_entity_species_data()->get_model_data(model_index)->get_body()->instance();

		add_child(node);
		set_body(node);

		on_body_changed();
	}
}

void Entity::on_body_changed() {
	if (has_method("_body_changed"))
		call("_body_changed");

	emit_signal("body_changed", this);
}

NodePath Entity::get_character_skeleton_path() {
	return _character_skeleton_path;
}
void Entity::set_character_skeleton_path(NodePath value) {
	_character_skeleton_path = value;

	set_character_skeleton(get_node_or_null(_character_skeleton_path));
}
Node *Entity::get_character_skeleton() {
	return _character_skeleton;
}
void Entity::set_character_skeleton(Node *skeleton) {
	_character_skeleton = skeleton;

	if (INSTANCE_VALIDATE(_character_skeleton) && _character_skeleton->has_method("add_model_visual")) {
		for (int i = 0; i < _c_equipment.size(); ++i) {
			Ref<ItemInstance> ii = _c_equipment[i];

			if (ii.is_valid())
				_character_skeleton->call("add_model_visual", ii->get_item_template()->get_model_visual());
		}
	}
}

//GUID
int Entity::gets_guid() {
	return _s_guid;
}
void Entity::sets_guid(int value) {
	_s_guid = value;

	VRPC(setc_guid, value);
}

int Entity::getc_guid() {
	return _c_guid;
}
void Entity::setc_guid(int value) {
	_c_guid = value;

	//set_name(String::num(_c_guid));
}

//Transforms
Transform Entity::get_transform_3d(bool only_stored) const {
	if (!only_stored && _body_3d) {
		ERR_FAIL_COND_V(!INSTANCE_VALIDATE(_body_3d), _transform);

		return _body_3d->get_transform();
	}

	return _transform;
}
void Entity::set_transform_3d(const Transform &transform, bool only_stored) {
	if (!only_stored && _body_3d) {
		ERR_FAIL_COND(!INSTANCE_VALIDATE(_body_3d));

		return _body_3d->set_transform(transform);
	}

	_transform = transform;
}

Transform2D Entity::get_transform_2d(bool only_stored) const {
	if (!only_stored && _body_2d) {
		ERR_FAIL_COND_V(!INSTANCE_VALIDATE(_body_2d), _transform_2d);

		return _body_2d->get_transform();
	}

	return _transform_2d;
}
void Entity::set_transform_2d(const Transform2D &transform, bool only_stored) {
	if (!only_stored && _body_2d) {
		ERR_FAIL_COND(!INSTANCE_VALIDATE(_body_2d));

		return _body_2d->set_transform(_transform_2d);
	}

	_transform_2d = transform;
}

//EntityPlayerType
int Entity::gets_entity_player_type() {
	return _s_entity_player_type;
}
void Entity::sets_entity_player_type(int value) {
	_s_entity_player_type = value;

	VRPC(setc_entity_player_type, value);
}

int Entity::getc_entity_player_type() {
	return _c_entity_player_type;
}
void Entity::setc_entity_player_type(int value) {
	_c_entity_player_type = value;
}

//EntityType
int Entity::gets_entity_type() {
	return _s_entity_type;
}
void Entity::sets_entity_type(int value) {
	_s_entity_type = value;

	VRPC(setc_entity_type, value);
}

int Entity::getc_entity_type() {
	return _c_entity_type;
}
void Entity::setc_entity_type(int value) {
	_c_entity_type = value;
}

//Relations
EntityEnums::EntityRelationType Entity::gets_relation_to_bind(Node *to) {
	Entity *e = Object::cast_to<Entity>(to);

	ERR_FAIL_COND_V(!INSTANCE_VALIDATE(e), EntityEnums::ENTITY_RELATION_TYPE_NEUTRAL);

	return gets_relation_to(e);
}
EntityEnums::EntityRelationType Entity::gets_relation_to(Entity *to) {
	ERR_FAIL_COND_V(!INSTANCE_VALIDATE(to), EntityEnums::ENTITY_RELATION_TYPE_NEUTRAL);

	return static_cast<EntityEnums::EntityRelationType>(static_cast<int>(call("_gets_relation_to", to)));
}

EntityEnums::EntityRelationType Entity::_gets_relation_to(Node *to) {
	if (to == this)
		return EntityEnums::ENTITY_RELATION_TYPE_FRIENDLY;

	return EntityEnums::ENTITY_RELATION_TYPE_HOSTILE;
}

EntityEnums::EntityRelationType Entity::getc_relation_to_bind(Node *to) {
	Entity *e = Object::cast_to<Entity>(to);

	ERR_FAIL_COND_V(!INSTANCE_VALIDATE(e), EntityEnums::ENTITY_RELATION_TYPE_NEUTRAL);

	return getc_relation_to(e);
}
EntityEnums::EntityRelationType Entity::getc_relation_to(Entity *to) {
	ERR_FAIL_COND_V(!INSTANCE_VALIDATE(to), EntityEnums::ENTITY_RELATION_TYPE_NEUTRAL);

	return static_cast<EntityEnums::EntityRelationType>(static_cast<int>(call("_getc_relation_to", to)));
}

EntityEnums::EntityRelationType Entity::_getc_relation_to(Node *to) {
	if (to == this)
		return EntityEnums::ENTITY_RELATION_TYPE_FRIENDLY;

	return EntityEnums::ENTITY_RELATION_TYPE_HOSTILE;
}

//EntityInteractionType
EntityEnums::EntityInteractionType Entity::gets_entity_interaction_type() {
	return _s_interaction_type;
}
void Entity::sets_entity_interaction_type(EntityEnums::EntityInteractionType value) {
	_s_interaction_type = value;

	VRPC(setc_entity_interaction_type, value);
}

EntityEnums::EntityInteractionType Entity::getc_entity_interaction_type() {
	return _c_interaction_type;
}
void Entity::setc_entity_interaction_type(EntityEnums::EntityInteractionType value) {
	_c_interaction_type = value;
}

int Entity::gets_immunity_flags() {
	return _s_immunity_flags;
}
void Entity::sets_immunity_flags(int value) {
	_s_immunity_flags = value;
}

int Entity::gets_entity_flags() {
	return _s_entity_flags;
}
void Entity::sets_entity_flags(int value) {
	_s_entity_flags = value;

	VRPC(setc_entity_flags, value);
}

int Entity::getc_entity_flags() {
	return _c_entity_flags;
}
void Entity::setc_entity_flags(int value) {
	_c_entity_flags = value;
}

String Entity::gets_entity_name() {
	return _s_entity_name;
}
void Entity::sets_entity_name(String value) {
	_s_entity_name = value;

	emit_signal("sname_changed", this);

	VRPC(setc_entity_name, value);
}

String Entity::getc_entity_name() {
	return _c_entity_name;
}
void Entity::setc_entity_name(String value) {
	_c_entity_name = value;

	emit_signal("cname_changed", this);
}

int Entity::gets_model_index() {
	return _s_model_index;
}
void Entity::sets_model_index(int value) {
	_s_model_index = value;

	VRPC(setc_model_index, value);
}

int Entity::getc_model_index() {
	return _c_model_index;
}
void Entity::setc_model_index(int value) {
	_c_model_index = value;

	if (INSTANCE_VALIDATE(_character_skeleton)) {
		if (_character_skeleton->has_method("set_model_index"))
			_character_skeleton->call("set_model_index", _c_model_index);
	}
}

int Entity::gets_level() {
	return _s_level;
}
void Entity::sets_level(int value) {
	_s_level = value;

	emit_signal("son_level_changed", this, value);

	VRPC(setc_level, value);
}
int Entity::getc_level() {
	return _c_level;
}
void Entity::setc_level(int value) {
	_c_level = value;

	emit_signal("con_level_changed", this, value);
}

int Entity::gets_xp() {
	return _s_xp;
}
void Entity::sets_xp(int value) {
	_s_xp = value;

	ORPC(setc_xp, value);
}
int Entity::getc_xp() {
	return _c_xp;
}
void Entity::setc_xp(int value) {
	_c_xp = value;
}

int Entity::gets_money() {
	return _s_money;
}
void Entity::sets_money(int value) {
	_s_money = value;

	ORPC(setc_money, value);
}

int Entity::getc_money() {
	return _c_money;
}
void Entity::setc_money(int value) {
	_c_money = value;
}

int Entity::gets_entity_data_id() {
	return _s_class_id;
}

void Entity::sets_entity_data_id(int value) {
	_s_class_id = value;
}

int Entity::getc_entity_data_id() {
	return _c_class_id;
}

void Entity::setc_entity_data_id(int value) {
	_c_class_id = value;

	if (_c_class_id == 0) {
		setc_entity_data(Ref<EntityData>());
		return;
	}

	if (ESS::get_singleton() != NULL) {
		setc_entity_data(ESS::get_singleton()->get_resource_db()->get_entity_data(_c_class_id));
	}
}

StringName Entity::gets_entity_data_path() {
	return _s_entity_data_path;
}
void Entity::sets_entity_data_path(const StringName &value) {
	_s_entity_data_path = value;
}

Ref<EntityData> Entity::gets_entity_data() {
	return _s_entity_data;
}

void Entity::sets_entity_data(Ref<EntityData> value) {
	if (is_queued_for_deletion()) {
		return;
	}

	_s_class_id = 0;

	if (value.is_valid()) {
		_s_class_id = value->get_id();
	}

	_s_entity_data = value;

	//setup();

	instance_body(value, _s_model_index);

	emit_signal("sentity_data_changed", value);

	VRPC(setc_entity_data_id, _s_class_id);
}

Ref<EntityData> Entity::getc_entity_data() {
	return _c_entity_data;
}

void Entity::setc_entity_data(Ref<EntityData> value) {
	_c_entity_data = value;

	instance_body(value, _c_model_index);

	emit_signal("centity_data_changed", value);
}

EntityEnums::AIStates Entity::gets_ai_state() const {
	return _sai_state;
}
void Entity::sets_ai_state(EntityEnums::AIStates state) {
	_sai_state = state;
}

EntityEnums::AIStates Entity::gets_ai_state_stored() const {
	return _sai_state_stored;
}
void Entity::sets_ai_state_stored(EntityEnums::AIStates state) {
	_sai_state_stored = state;
}

int Entity::gets_seed() {
	return _s_seed;
}
void Entity::sets_seed(int value) {
	_s_seed = value;

	ORPC(setc_seed, value);
}

int Entity::getc_seed() {
	return _c_seed;
}
void Entity::setc_seed(int value) {
	_c_seed = value;
}

void Entity::_initialize() {
	_s_resources.resize(EntityEnums::ENTITY_RESOURCE_INDEX_RESOURCES_BEGIN);
	_c_resources.resize(EntityEnums::ENTITY_RESOURCE_INDEX_RESOURCES_BEGIN);

	_s_resources.set(EntityEnums::ENTITY_RESOURCE_INDEX_HEALTH, Ref<EntityResourceHealth>(memnew(EntityResourceHealth)));
	_s_resources.set(EntityEnums::ENTITY_RESOURCE_INDEX_SPEED, Ref<EntityResourceSpeed>(memnew(EntityResourceSpeed)));

	_c_resources.set(EntityEnums::ENTITY_RESOURCE_INDEX_HEALTH, Ref<EntityResourceHealth>(memnew(EntityResourceHealth)));
	_c_resources.set(EntityEnums::ENTITY_RESOURCE_INDEX_SPEED, Ref<EntityResourceSpeed>(memnew(EntityResourceSpeed)));

	for (int i = 0; i < EntityEnums::ENTITY_RESOURCE_INDEX_RESOURCES_BEGIN; ++i) {
		_s_resources.get(i)->set_owner(this);
		_c_resources.get(i)->set_owner(this);
	}
}

void Entity::setup(Ref<EntityCreateInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	sets_guid(info->get_guid());

	sets_entity_player_type(info->get_entity_player_type());

	if (info->get_network_owner() != 0)
		set_network_master(info->get_network_owner());

	sets_original_entity_controller(info->get_entity_controller());
	sets_entity_controller(info->get_entity_controller());

	_s_level = info->get_level();

	_s_xp = info->get_xp();

	if (info->get_entity_name() != "") {
		sets_entity_name(info->get_entity_name());
	}

#if VERSION_MAJOR > 3
	if (!info->get_serialized_data().is_empty()) {
#else
	if (!info->get_serialized_data().empty()) {
#endif
		from_dict(info->get_serialized_data());
	} else {
		sets_entity_data(info->get_entity_data());
	}

	if (has_method("_setup")) {
#if GODOT4
		call("_setup");
#else
		call_multilevel("_setup");
#endif
	}
}

void Entity::_setup() {
	if (!_s_entity_data.is_valid())
		return;

	if (_deserialized) {
		Ref<EntityClassData> cc = gets_entity_data()->get_entity_class_data();
		ERR_FAIL_COND(!cc.is_valid());

		//Ref<StatData> stat_data = _s_entity_data->get_stat_data();

		sets_ai(_s_entity_data->get_ai_instance());

		for (int i = 0; i < _s_auras.size(); ++i) {
			Ref<AuraData> ad = _s_auras.get(i);

			if (!ad->get_aura()->aura_get_hide())
				VRPCOBJ(aura_addc_rpc, JSON::print(ad->to_dict()), aura_addc, ad);
		}

		if (gets_entity_player_type() == EntityEnums::ENTITY_PLAYER_TYPE_PLAYER || gets_entity_player_type() == EntityEnums::ENTITY_PLAYER_TYPE_DISPLAY) {
			/*
			if (ESS::get_singleton()->get_use_global_class_level()) {
				Ref<ClassProfile> cp = ProfileManager::get_singleton()->getc_player_profile()->get_class_profile(gets_entity_data()->get_path());

				if (cp.is_valid()) {
					int leveldiff = cp->get_level() - _s_level;

					sets_class_level(cp->get_level());

					if (leveldiff > 0) {
						levelup_sclass(leveldiff);
					}

					sets_class_xp(cp->get_xp());
				}
			}
*/
			setup_actionbars();
		}

		if (gets_entity_player_type() == EntityEnums::ENTITY_PLAYER_TYPE_AI) {
			sets_entity_name(_s_entity_data->get_name());
		}

		return;
	}

	ERR_FAIL_COND(!gets_entity_data().is_valid());

	Ref<EntityClassData> cc = gets_entity_data()->get_entity_class_data();

	ERR_FAIL_COND(!cc.is_valid());

	Ref<StatData> stat_data = cc->get_stat_data();

	ERR_FAIL_COND(!stat_data.is_valid());

	for (int i = 0; i < ESS::get_singleton()->stat_get_count(); ++i) {
		stat_set_base(i, stat_data->get_base(i));
	}

	for (int i = 0; i < ESS::get_singleton()->stat_get_count(); ++i) {
		stat_setc_current(i, stat_gets_current(i));
		stat_set_dirty(i, false);
	}

	for (int i = 0; i < cc->get_num_auras(); ++i) {
		Ref<Spell> a = cc->get_aura(i);

		if (a.is_valid()) {
			a->aura_sapply_simple(this, this, 1.0);
		}
	}

	_s_entity_data->setup_resources(this);

	sets_entity_data_id(_s_entity_data->get_id());

	Ref<EntitySpeciesData> spd = _s_entity_data->get_entity_species_data();

	if (spd.is_valid()) {
		sets_entity_type(spd->get_type());
	} else {
		sets_entity_type(0);
	}

	sets_entity_interaction_type(_s_entity_data->get_entity_interaction_type());
	sets_immunity_flags(_s_entity_data->get_immunity_flags());
	sets_entity_flags(_s_entity_data->get_entity_flags());

	//if (_s_entity_controller == EntityEnums::ENITIY_CONTROLLER_NONE) {
	//	sets_original_entity_controller(_s_entity_data->get_entity_controller());
	//	sets_entity_controller(_s_entity_data->get_entity_controller());
	//}

	//sets_entity_name(_s_entity_data->get_entity_name());
	sets_money(_s_entity_data->get_money());

	Ref<EntityClassData> cd = _s_entity_data->get_entity_class_data();

	if (cd.is_valid()) {
		for (int i = 0; i < cd->get_num_start_spells(); ++i) {
			spell_adds(cd->get_start_spell(i));
		}
	}

	for (int i = 0; i < cc->get_num_craft_recipes(); ++i) {
		craft_adds_recipe(cc->get_craft_recipe(i));
	}

	if (_s_entity_data->get_equipment_data().is_valid()) {
		Ref<EquipmentData> eqd = _s_entity_data->get_equipment_data();

		for (int i = 0; i < ESS::get_singleton()->equip_slot_get_count(); ++i) {
			Ref<ItemInstance> ii = eqd->get_item(i);

			if (ii.is_valid())
				_s_equipment.write[i] = ii;
		}
	}

	sets_ai(_s_entity_data->get_ai_instance());

	if (!Engine::get_singleton()->is_editor_hint())
		set_process(_s_entity_data.is_valid());

	if (gets_entity_player_type() == EntityEnums::ENTITY_PLAYER_TYPE_PLAYER || gets_entity_player_type() == EntityEnums::ENTITY_PLAYER_TYPE_DISPLAY) {
		setup_actionbars();
	}

	if (gets_entity_player_type() == EntityEnums::ENTITY_PLAYER_TYPE_AI) {
		sets_entity_name(_s_entity_data->get_name());
	}

	int chl = _s_level;
	int chxp = _s_xp;

	_s_level = 1;

	levelups(chl - 1);
	sets_xp(chxp);

	if (ESS::get_singleton()->get_allow_class_spell_learning()) {
		Ref<ClassProfile> class_profile = ProfileManager::get_singleton()->getc_player_profile()->get_class_profile(_s_entity_data->get_path());

		if (class_profile.is_valid() && class_profile->has_custom_data("spells")) {
			Vector<String> spells = class_profile->get_custom_data("spells");

			for (int i = 0; i < spells.size(); ++i) {
				spell_adds_id(ESS::get_singleton()->get_resource_db()->spell_path_to_id(spells.get(i)));
			}
		}
	}

	if (ESS::get_singleton()->get_allow_class_recipe_learning()) {
		Ref<ClassProfile> class_profile = ProfileManager::get_singleton()->getc_player_profile()->get_class_profile(_s_entity_data->get_path());

		if (class_profile.is_valid() && class_profile->has_custom_data("recipes")) {
			Vector<String> recipes = class_profile->get_custom_data("recipes");

			for (int i = 0; i < recipes.size(); ++i) {
				craft_adds_recipe_id(ESS::get_singleton()->get_resource_db()->craft_recipe_path_to_id(recipes.get(i)));
			}
		}
	}
}

void Entity::setup_actionbars() {
	if (!gets_entity_data().is_valid())
		return;

	if (is_deserialized()) {
		return;
	}

	get_action_bar_profile();
	/*
	ProfileManager *pm = ProfileManager::get_singleton();

	if (pm != NULL) {
		Ref<ClassProfile> cp = get_class_profile();

		if (cp.is_valid()) {
			set_actionbar_locked(cp->get_actionbar_locked());
			_action_bar_profile = cp->get_default_action_bar_profile();

			get_action_bar_profile()->clear_action_bars();

			Ref<ActionBarProfile> abp = cp->get_action_bar_profile();

			get_action_bar_profile()->from_actionbar_profile(abp);
		}
	}*/

	if (!gets_bag().is_valid()) {
		Ref<Bag> bag;
		bag.instance();

		bag->set_size(gets_entity_data()->get_bag_size());

		sets_bag(bag);
	}
}

// AI

bool Entity::gets_is_pet() {
	return _s_pet_owner;
}

bool Entity::getc_is_pet() {
	return _c_pet_owner;
}

Entity *Entity::pet_gets_owner() {
	return _s_pet_owner;
}
void Entity::pet_sets_owner(Entity *entity) {
	_s_pet_owner = entity;
}
void Entity::pet_sets_owner_bind(Node *entity) {
	if (!entity) {
		return;
	}

	Entity *e = cast_to<Entity>(entity);

	if (!e) {
		return;
	}

	return pet_sets_owner(e);
}

int Entity::pet_gets_formation_index() {
	return _s_pet_formation_index;
}
void Entity::pet_sets_formation_index(int value) {
	_s_pet_formation_index = value;
}

EntityEnums::AIStates Entity::pet_gets_ai_state() {
	return _s_pet_ai_state;
}
void Entity::pet_sets_ai_state(EntityEnums::AIStates value) {
	_s_pet_ai_state = value;
}

EntityEnums::EntityController Entity::gets_original_entity_controller() {
	return _s_entity_controller;
}
void Entity::sets_original_entity_controller(EntityEnums::EntityController value) {
	_s_entity_controller = value;
}

EntityEnums::EntityController Entity::gets_entity_controller() {
	return _s_entity_controller;
}
void Entity::sets_entity_controller(EntityEnums::EntityController value) {
	_s_entity_controller = value;

	ORPC(setc_entity_controller, value);
}

EntityEnums::EntityController Entity::getc_entity_controller() {
	return _s_entity_controller;
}
void Entity::setc_entity_controller(EntityEnums::EntityController value) {
	if (_c_entity_controller == value) {
		return;
	}

	_c_entity_controller = value;

	emit_signal("onc_entity_controller_changed");
}

bool Entity::getc_is_controlled() {
	if (is_inside_tree() && get_tree()->has_network_peer()) {
		return (_c_entity_controller == EntityEnums::ENITIY_CONTROLLER_PLAYER) && (get_network_master() == get_tree()->get_network_unique_id());
	} else {
		return _c_entity_controller == EntityEnums::ENITIY_CONTROLLER_PLAYER;
	}
}

Ref<EntityAI> Entity::gets_ai() {
	return _s_ai;
}
void Entity::sets_ai(Ref<EntityAI> value) {
	if (_s_ai.is_valid()) {
		_s_ai->set_owner(NULL);
		_s_ai.unref();
	}

	_s_ai = value;
	_s_ai->set_owner(this);
}

////    Pets    ////

void Entity::pet_adds(Entity *entity) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(entity));

	//the owner always want to see his pet, and you pet will always want to see the owner
	sees_adds(entity);
	entity->sees_adds(this);

	entity->pet_sets_owner(this);

	_s_pets.push_back(entity);

	entity->sets_ai_state_stored(entity->gets_ai_state());
	entity->sets_ai_state(_s_pet_ai_state);
	entity->sets_entity_controller(EntityEnums::ENITIY_CONTROLLER_AI);

	entity->pet_sets_formation_index(_s_pets.size());

	//full callback stack spet_added
}
void Entity::pet_adds_bind(Node *entity) {
	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(!e);

	pet_adds(e);
}
Entity *Entity::pet_gets(int index) {
	ERR_FAIL_INDEX_V(index, _s_pets.size(), NULL);

	return _s_pets.get(index);
}
void Entity::pet_removes_index(int index) {
	ERR_FAIL_INDEX(index, _s_pets.size());

	Entity *entity = _s_pets.get(index);

	_s_pets.remove(index);

	sees_removes(entity);

	for (int i = 0; i < _s_pets.size(); ++i) {
		Entity *pet = _s_pets.get(index);

		ERR_CONTINUE(!INSTANCE_VALIDATE(pet));

		_s_pets.get(i)->pet_sets_formation_index(i);
	}

	ERR_FAIL_COND(!INSTANCE_VALIDATE(entity));

	entity->pet_sets_owner(NULL);

	entity->sets_ai_state(entity->gets_ai_state_stored());
	entity->sets_entity_controller(entity->gets_original_entity_controller());

	//full callback stack spet_added
}
void Entity::pet_removes(Entity *entity) {
	for (int i = 0; i < _s_pets.size(); ++i) {
		if (_s_pets.get(i) == entity) {
			pet_removes_index(i);
			return;
		}
	}
}
void Entity::pet_removes_bind(Node *entity) {
	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(!e);

	pet_removes(e);
}
int Entity::pet_gets_count() {
	return _s_pets.size();
}

void Entity::pet_addc_path(NodePath path) {
	Node *n = get_node_or_null(path);

	Entity *entity = Object::cast_to<Entity>(n);

	ERR_FAIL_COND(!INSTANCE_VALIDATE(entity));

	pet_addc(entity);
}

void Entity::pet_addc(Entity *entity) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(entity));

	_c_pets.push_back(entity);

	//full callback stack spet_added
}
void Entity::pet_addc_bind(Node *entity) {
	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(!e);

	pet_addc(e);
}
Entity *Entity::pet_getc(int index) {
	ERR_FAIL_INDEX_V(index, _c_pets.size(), NULL);

	return _c_pets.get(index);
}
void Entity::pet_removec_index(int index) {
	ERR_FAIL_INDEX(index, _c_pets.size());

	//Entity *entity = _c_pets.get(index);

	_c_pets.remove(index);

	//#if VERSION_MAJOR < 4
	//ERR_FAIL_COND(!ObjectDB::instance_validate(entity));
	//#else
	//ERR_FAIL_COND(entity == NULL);
	//#endif

	//full callback stack spet_added
}
void Entity::pet_removec(Entity *entity) {
	for (int i = 0; i < _c_pets.size(); ++i) {
		if (_c_pets.get(i) == entity) {
			pet_removec_index(i);
			return;
		}
	}
}
void Entity::pet_removec_bind(Node *entity) {
	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(!e);

	pet_removec(e);
}
int Entity::pet_getc_count() {
	return _s_pets.size();
}

////    Profiles    ////

Ref<ClassProfile> Entity::get_class_profile() {
	return ProfileManager::get_singleton()->getc_player_profile()->get_class_profile(_s_entity_data->get_path());
}

////    Serialization    ////

bool Entity::is_deserialized() {
	return _deserialized;
}

Dictionary Entity::to_dict() {
	return call("_to_dict");
}
void Entity::from_dict(const Dictionary &dict) {
	_deserialized = true;

	call("_from_dict", dict);

	emit_signal("deserialized", this);
}

Dictionary Entity::_to_dict() {
	Dictionary dict;

	////    Transforms    ////

	//Not needed (at least atm)

	////    PlayerData    ////

	dict["guid"] = _s_guid;
	//dict["entity_data_id"] = _s_class_id;

	if (_s_entity_data.is_valid())
		dict["entity_data_path"] = _s_entity_data->get_path();
	else
		dict["entity_data_path"] = _s_entity_data_path;

	//int _s_entity_player_type;

	dict["type"] = _s_type;
	dict["model_index"] = _s_model_index;
	dict["level"] = _s_level;

	dict["xp"] = gets_xp();

	dict["money"] = _s_money;

	//dict["send_flag"] = _s_send_flag;
	dict["entity_name"] = _s_entity_name;

	dict["interaction_type"] = static_cast<int>(_s_interaction_type);

	//int _s_is_dead;

	dict["seed"] = _s_seed;

	dict["entity_type"] = _s_entity_type;
	dict["immunity_flags"] = _s_immunity_flags;
	dict["entity_flags"] = _s_entity_flags;
	//dict["entity_controller"] = _s_entity_controller;
	//dict["entity_controller"] = _s_original_entity_controller;

	////     Stats    ////

	Dictionary sd;

	for (int i = 0; i < ESS::get_singleton()->stat_get_count(); ++i) {
		Dictionary sdict;

		sdict["base"] = stat_get_base(i);
		sdict["base_calculated"] = stat_get_base_calculated(i);
		sdict["bonus"] = stat_get_bonus(i);
		sdict["percent"] = stat_get_percent(i);
		sdict["current"] = stat_gets_current(i);

		sd[i] = sdict;
	}

	dict["stats"] = sd;

	////    Equipment    ////

	Dictionary equipment;

	for (int i = 0; i < ESS::get_singleton()->equip_slot_get_count(); ++i) {
		Ref<ItemInstance> ii = _s_equipment[i];

		if (ii.is_valid())
			equipment[i] = ii->to_dict();
	}

	dict["equipment"] = equipment;

	////    Resources    ////

	Dictionary rd;

	for (int i = 0; i < _s_resources.size(); ++i) {
		Ref<EntityResource> r = _s_resources.get(i);

		ERR_CONTINUE(!r.is_valid());

		rd[String::num(i)] = r->to_dict();
	}

	dict["resources"] = rd;

	////    GCD    ////

	dict["gcd"] = _s_gcd;

	////    States    ////

	Dictionary stated;

	for (int i = 0; i < EntityEnums::ENTITY_STATE_TYPE_INDEX_MAX; ++i) {
		stated[i] = _s_states[i];
	}

	dict["states"] = stated;

	dict["state"] = _s_state;

	////    SpellCastData    ////

	//Not needed
	//Ref<SpellCastInfo> _s_spell_cast_info;
	//Ref<SpellCastInfo> _c_spell_cast_info;

	//// AuraComponent    ////

	Dictionary auras;

	for (int i = 0; i < _s_auras.size(); ++i) {
		auras[i] = _s_auras.get(i)->to_dict();
	}

	dict["auras"] = auras;

	////    Cooldowns    ////

	Dictionary cds;

	for (int i = 0; i < _s_cooldowns.size(); ++i) {
		Dictionary cdict;

		cdict["path"] = ESS::get_singleton()->get_resource_db()->spell_id_to_path(_s_cooldowns[i].id);
		cdict["remaining"] = _s_cooldowns[i].cooldown;

		cds[i] = cdict;
	}

	dict["cooldowns"] = cds;

	Dictionary ccds;

	for (int i = 0; i < _s_category_cooldowns.size(); ++i) {
		Dictionary ccdict;

		ccdict["path"] = ESS::get_singleton()->get_resource_db()->spell_id_to_path(_s_category_cooldowns[i].id);
		ccdict["remaining"] = _s_category_cooldowns[i].cooldown;

		ccds[i] = ccdict;
	}

	dict["category_cooldowns"] = ccds;

	dict["active_category_cooldowns"] = _s_active_category_cooldowns;

	////    Talents    ////

	dict["free_class_talent_points"] = _s_free_class_talent_points;
	dict["class_talents"] = _s_class_talents;

	dict["free_character_talent_points"] = _s_free_character_talent_points;
	dict["character_talents"] = _s_character_talents;

	////    Data    ////

	Array entity_datas;

	for (int i = 0; i < _s_data.size(); ++i) {
		entity_datas.append(_s_data.get(i)->to_dict());
	}

	dict["entity_datas"] = entity_datas;

	////    Crafting    ////

	Dictionary known_recipes;

	for (int i = 0; i < _s_craft_recipes.size(); ++i) {
		known_recipes[i] = _s_craft_recipes.get(i)->get_path();
	}

	dict["known_recipes"] = known_recipes;

	////    Known Spells    ////

	if (ESS::get_singleton()->get_use_spell_points())
		dict["free_spell_points"] = _s_free_spell_points;

	Dictionary known_spells;

	for (int i = 0; i < _s_spells.size(); ++i) {
		known_spells[i] = _s_spells.get(i)->get_path();
	}

	dict["known_spells"] = known_spells;

	////    Skills    ////

	Dictionary skills;

	for (int i = 0; i < _s_skills.size(); ++i) {
		skills[i] = _s_skills.get(i)->to_dict();
	}

	dict["skills"] = skills;

	////    Bags    ////

	if (_s_bag.is_valid())
		dict["bag"] = _s_bag->to_dict();

	////     Actionbars    ////

	dict["actionbar_locked"] = _actionbar_locked;

	if (_action_bar_profile.is_valid())
		dict["actionbar_profile"] = _action_bar_profile->to_dict();

	// AI

	//not needed

	//Pets

	//Not yet properly implemented

	// Callbacks

	//Probably not needed
	//Vector<Ref<SpellCastInfo> > _physics_process_scis;

	return dict;
}
void Entity::_from_dict(const Dictionary &dict) {
#if VERSION_MAJOR > 3
	ERR_FAIL_COND(dict.is_empty());
#else
	ERR_FAIL_COND(dict.empty());
#endif

	////    Transforms    ////

	//Not needed for now

	////    PlayerData    ////

	sets_guid(dict.get("guid", 0));
	sets_entity_type(dict.get("type", 0));

	//entity_data_path at end

	sets_model_index(static_cast<int>(static_cast<int>(dict.get("model_index", 0))));

	/*
	if (ESS::get_singleton()->get_use_global_class_level()) {
		_s_level = (dict.get("class_level", 0));
		_s_xp = (dict.get("class_xp", 0));
	} else {
		sets_class_level(dict.get("class_level", 0));
		sets_xp(dict.get("xp", 0));
	}
*/

	sets_level(dict.get("level", 0));
	sets_xp(dict.get("xp", 0));

	sets_money(dict.get("money", 0));

	sets_entity_name(dict.get("entity_name", ""));

	sets_entity_interaction_type(static_cast<EntityEnums::EntityInteractionType>(static_cast<int>(dict.get("interaction_type", 0))));

	//int _s_is_dead;

	sets_seed(dict.get("seed", _s_seed));

	//EntityPlayerType not needed
	sets_immunity_flags(dict.get("immunity_flags", 0));
	sets_entity_flags(dict.get("entity_flags", 0));
	
	//EntityEnums::EntityController contr = static_cast<EntityEnums::EntityController>(static_cast<int>(dict.get("entity_controller", 0)));

	//sets_original_entity_controller(contr);
	//sets_entity_controller(contr);

	////     Stats    ////

	Dictionary stats = dict.get("stats", Dictionary());

	for (int i = 0; i < ESS::get_singleton()->stat_get_count(); ++i) {
		Dictionary sd = stats.get(String::num(i), Dictionary());

		stat_set_base(i, sd.get("base", 0));
		stat_set_base_calculated(i, sd.get("base_calculated", 0));
		stat_set_bonus(i, sd.get("bonus", 0));
		stat_set_percent(i, sd.get("percent", 1));

		float curr = sd.get("current", 0);
		stat_sets_current(i, curr);
		stat_setc_current(i, curr);

		stat_set_dirty(i, true);
	}

	////    Equipment    ////

	Dictionary equipment = dict.get("equipment", Dictionary());

	for (int i = 0; i < ESS::get_singleton()->equip_slot_get_count(); ++i) {
		if (equipment.has(String::num(i))) {
			Ref<ItemInstance> ii = _s_equipment[i];

			if (!ii.is_valid()) {
				ii.instance();
			}

			ii->from_dict(equipment[String::num(i)]);

			_s_equipment.write[i] = ii;
			_c_equipment.write[i] = ii;
		}
	}

	////    Resources    ////

	_s_resources.resize(EntityEnums::ENTITY_RESOURCE_INDEX_RESOURCES_BEGIN);
	_c_resources.resize(EntityEnums::ENTITY_RESOURCE_INDEX_RESOURCES_BEGIN);

	Dictionary rd = dict.get("resources", Dictionary());

	Dictionary hpdict = rd.get(String::num(EntityEnums::ENTITY_RESOURCE_INDEX_HEALTH), Dictionary());
	_s_resources.get(EntityEnums::ENTITY_RESOURCE_INDEX_HEALTH)->from_dict(hpdict);
	_c_resources.get(EntityEnums::ENTITY_RESOURCE_INDEX_HEALTH)->from_dict(hpdict);

	Dictionary speeddict = rd.get(String::num(EntityEnums::ENTITY_RESOURCE_INDEX_SPEED), Dictionary());
	_s_resources.get(EntityEnums::ENTITY_RESOURCE_INDEX_SPEED)->from_dict(speeddict);
	_c_resources.get(EntityEnums::ENTITY_RESOURCE_INDEX_SPEED)->from_dict(speeddict);

	for (int i = EntityEnums::ENTITY_RESOURCE_INDEX_RESOURCES_BEGIN; i < rd.size(); ++i) {
		Dictionary ird = rd.get(String::num(i), Dictionary());

		StringName data_path = ird.get("data_path", "");

		Ref<EntityResource> resd = ESS::get_singleton()->get_resource_db()->get_entity_resource_path(data_path);

		ERR_CONTINUE(!resd.is_valid());

		Ref<EntityResource> res = resd->duplicate();

		ERR_CONTINUE(!res.is_valid());

		res->from_dict(ird);

		resource_adds(res);
	}

	////    GCD    ////

	_s_gcd = dict.get("gcd", 0);
	_c_gcd = _s_gcd;

	////    States    ////

	Dictionary statesd = dict.get("states", Dictionary());

	for (int i = 0; i < EntityEnums::ENTITY_STATE_TYPE_INDEX_MAX; ++i) {
		_s_states[i] = statesd.get(String::num(i), 0);
	}

	_s_state = dict.get("state", Dictionary());
	_c_state = _s_state;

	////    SpellCastData    ////

	//Not needed

	////    Auras    ////

	_s_auras.clear();
	_c_auras.clear();

	Dictionary auras = dict.get("auras", Dictionary());

	for (int i = 0; i < auras.size(); ++i) {
		Ref<AuraData> r;
		r.instance();

		r->from_dict(auras.get(String::num(i), Dictionary()));
		r->set_owner(this);
		r->resolve_references(this);

		_s_auras.push_back(r);
		//_c_auras.push_back(r);
	}

	////    Cooldowns    ////

	_s_cooldowns.clear();
	_c_cooldowns.clear();

	Dictionary cds = dict.get("cooldowns", Dictionary());

	for (int i = 0; i < cds.size(); ++i) {
		Dictionary cddict = cds.get(String::num(i), Dictionary());

		Cooldown cd;

		cd.path = dict.get("path", "");
		cd.id = ESS::get_singleton()->get_resource_db()->spell_path_to_id(cd.path);
		cd.cooldown = dict.get("remaining", 0);

		_s_cooldowns.push_back(cd);
		_c_cooldowns.push_back(cd);
	}

	Dictionary ccds = dict.get("category_cooldowns", Dictionary());

	for (int i = 0; i < ccds.size(); ++i) {
		Dictionary ccdict = ccds.get(String::num(i), Dictionary());

		Cooldown ccd;

		ccd.path = dict.get("path", "");
		ccd.id = ESS::get_singleton()->get_resource_db()->spell_path_to_id(ccd.path);
		ccd.cooldown = dict.get("remaining", 0);

		_s_category_cooldowns.push_back(ccd);
		_c_category_cooldowns.push_back(ccd);
	}

	_s_active_category_cooldowns = dict.get("active_category_cooldowns", 0);
	_c_active_category_cooldowns = _s_active_category_cooldowns;

	////    Class Talents    ////

	_s_free_class_talent_points = dict.get("free_class_talent_points", 0);
	_c_free_class_talent_points = _s_free_class_talent_points;

	Vector<int> class_talents = dict.get("class_talents", Vector<int>());

	for (int i = 0; i < class_talents.size(); ++i) {
		class_talent_adds(class_talents[i]);
	}

	////    Character Talents    ////

	_s_free_character_talent_points = dict.get("free_character_talent_points", 0);
	_c_free_character_talent_points = _s_free_character_talent_points;

	Vector<int> character_talents = dict.get("character_talents", Vector<int>());

	for (int i = 0; i < character_talents.size(); ++i) {
		character_talent_adds(character_talents[i]);
	}

	////    Data    ////

	Array entity_datas = dict.get("entity_datas", Array());

	for (int i = 0; i < entity_datas.size(); ++i) {
		Dictionary entry = entity_datas.get(i);

		String class_name = dict.get("class_name", EntityDataContainer::get_class_static());

		if (ClassDB::can_instance(class_name) && ClassDB::is_parent_class(class_name, EntityDataContainer::get_class_static())) {
			Ref<EntityDataContainer> data = Ref<EntityDataContainer>(ClassDB::instance(class_name));

			if (data.is_valid()) {
				data->from_dict(entry);

				_s_data.push_back(data);
				_c_data.push_back(data);
			}
		}
	}

	////    Crafting    ////

	_s_craft_recipes.clear();
	_c_craft_recipes.clear();

	Dictionary known_recipes = dict.get("known_recipes", Dictionary());

	for (int i = 0; i < known_recipes.size(); ++i) {
		StringName crn = known_recipes.get(String::num(i), "");

		if (ESS::get_singleton() != NULL) {
			Ref<CraftRecipe> cr = ESS::get_singleton()->get_resource_db()->get_craft_recipe_path(crn);

			if (cr.is_valid()) {
				craft_adds_recipe(cr);
			}
		}
	}

	////    Known Spells    ////

	if (ESS::get_singleton()->get_use_spell_points())
		sets_free_spell_points(dict.get("free_spell_points", 0));

	Dictionary known_spells = dict.get("known_spells", Dictionary());

	for (int i = 0; i < known_spells.size(); ++i) {
		StringName spell_path = known_spells.get(String::num(i), "");

		if (ESS::get_singleton() != NULL) {
			Ref<Spell> sp = ESS::get_singleton()->get_resource_db()->get_spell_path(spell_path);

			if (sp.is_valid()) {
				_s_spells.push_back(sp);
				_c_spells.push_back(sp);
			}
		}
	}

	////    Skills    ////

	Dictionary skills = dict.get("skills", Dictionary());

	for (int i = 0; i < skills.size(); ++i) {
		Ref<EntitySkill> r;
		r.instance();

		r->from_dict(skills.get(String::num(i), Dictionary()));

		_s_skills.push_back(r);
		_c_skills.push_back(r);
	}

	////    Bags    ////

	Dictionary bagd = dict.get("bag", Dictionary());

#if VERSION_MAJOR > 3
	if (!bagd.is_empty()) {
#else
	if (!bagd.empty()) {
#endif
		if (!_s_bag.is_valid()) {
			Ref<Bag> bag;
			bag.instance();

			bag->from_dict(bagd);

			sets_bag(bag);
		} else {
			_s_bag->from_dict(bagd);
		}
	}

	////     Actionbars    ////

	_actionbar_locked = dict.get("actionbar_locked", false);

	if (dict.has("actionbar_profile")) {
		if (!_action_bar_profile.is_valid())
			_action_bar_profile.instance();

		_action_bar_profile->from_dict(dict.get("actionbar_profile", Dictionary()));
	}

	StringName edp = dict.get("entity_data_path", "");

	if (ESS::get_singleton() != NULL) {
		sets_entity_data(ESS::get_singleton()->get_resource_db()->get_entity_data_path(edp));
	}

	sets_entity_data_path(edp);

	// AI

	//Not needed right now

	//Pets

	//NYI

	// Networking

	//Not Needed

	// Callbacks

	//Not Needed
}

//////     Stat System      //////

bool Entity::gets_is_dead() {
	return _s_is_dead;
}

bool Entity::getc_is_dead() {
	return _c_is_dead;
}

bool Entity::gcd_hasc() const {
	return _c_gcd >= 0.000000001;
}

bool Entity::gcd_hass() const {
	return _s_gcd >= 0.000000001;
}

float Entity::gcd_getc() const {
	return _c_gcd;
}

void Entity::gcd_setc(const float value) {
	_c_gcd = value;
}

float Entity::gcd_gets() const {
	return _s_gcd;
}

void Entity::gcd_sets(const float value) {
	_s_gcd = value;
}

void Entity::gcd_starts(float value) {
	_s_gcd = value;

	notification_sgcd_started();

	ORPC(gcd_startc, value);
}

void Entity::gcd_startc(float value) {
	_c_gcd = value;

	notification_cgcd_started();
}

////    States    ////

int Entity::gets_state() {
	return _s_state;
}
void Entity::sets_state(int state) {
	_s_state = state;

	emit_signal("sstate_changed", state);

	VRPC(setc_state, state);
}

int Entity::getc_state() {
	return _c_state;
}
void Entity::setc_state(int state) {
	_c_state = state;

	emit_signal("cstate_changed", state);
}

void Entity::adds_state_ref(int state_index) {
	ERR_FAIL_INDEX(state_index, EntityEnums::ENTITY_STATE_TYPE_INDEX_MAX);

	if (_s_states[state_index]++ == 0) {
		sets_state(gets_state() | EntityEnums::get_state_flag_for_index(state_index));
	}
}

void Entity::removes_state_ref(int state_index) {
	ERR_FAIL_INDEX(state_index, EntityEnums::ENTITY_STATE_TYPE_INDEX_MAX);

	if (--_s_states[state_index] == 0) {
		sets_state(gets_state() ^ EntityEnums::get_state_flag_for_index(state_index));
	}
}

PoolIntArray Entity::states_gets() const {
	PoolIntArray arr;
	arr.resize(EntityEnums::ENTITY_STATE_TYPE_INDEX_MAX);

#if !GODOT4
	PoolIntArray::Write w = arr.write();
#endif

	for (int i = 0; i < EntityEnums::ENTITY_STATE_TYPE_INDEX_MAX; ++i) {
#if !GODOT4
		w[i] = _s_states[i];
#else
		arr.write[i] = _s_states[i];
#endif
	}

	return arr;
}
void Entity::states_sets(const PoolIntArray &data) {
	ERR_FAIL_COND(data.size() <= EntityEnums::ENTITY_STATE_TYPE_INDEX_MAX);

	for (int i = 0; i < EntityEnums::ENTITY_STATE_TYPE_INDEX_MAX; ++i) {
		_s_states[i] = data[i];
	}
}

////    Crafting System    ////

void Entity::craft_crequest(int id) {
	crafts(id);
}
void Entity::crafts(int id) {
	if (has_method("_crafts")) {
		call("_crafts", id);
	}
}

bool Entity::craft_hass_recipe(Ref<CraftRecipe> craft_recipe) {
	for (int i = 0; i < _s_craft_recipes.size(); ++i) {
		if (_s_craft_recipes.get(i) == craft_recipe) {
			return true;
		}
	}

	return false;
}
bool Entity::craft_hass_recipe_id(int id) {
	for (int i = 0; i < _s_craft_recipes.size(); ++i) {
		Ref<CraftRecipe> cr = _s_craft_recipes.get(i);

		ERR_CONTINUE(!cr.is_valid());

		if (cr->get_id() == id) {
			return true;
		}
	}

	return false;
}
void Entity::craft_adds_recipe(Ref<CraftRecipe> craft_recipe) {
	ERR_FAIL_COND(!craft_recipe.is_valid());

	if (craft_hass_recipe(craft_recipe))
		return;

	_s_craft_recipes.push_back(craft_recipe);

	emit_signal("crafts_recipe_added", this, craft_recipe);

	ORPC(craft_addc_recipe_id, craft_recipe->get_id());
}
void Entity::craft_adds_recipe_id(int id) {
	ERR_FAIL_COND(!ESS::get_singleton());

	if (craft_hass_recipe_id(id))
		return;

	Ref<CraftRecipe> craft_recipe = ESS::get_singleton()->get_resource_db()->get_craft_recipe(id);

	ERR_FAIL_COND(!craft_recipe.is_valid());

	_s_craft_recipes.push_back(craft_recipe);

	if (ESS::get_singleton()->get_allow_class_recipe_learning() && (_s_entity_player_type == EntityEnums::ENTITY_PLAYER_TYPE_PLAYER || gets_entity_player_type() == EntityEnums::ENTITY_PLAYER_TYPE_DISPLAY)) {
		Ref<ClassProfile> class_profile = ProfileManager::get_singleton()->getc_player_profile()->get_class_profile(_s_entity_data->get_path());

		if (class_profile->has_custom_data("recipes")) {
			Vector<String> recipes = class_profile->get_custom_data("recipes");

			bool found = false;

			for (int i = 0; i < recipes.size(); ++i) {
				if (recipes[i] == craft_recipe->get_path()) {
					found = true;
					break;
				}
			}

			if (!found) {
				recipes.push_back(craft_recipe->get_path());
				class_profile->set_custom_data("recipes", recipes);
			}
		} else {
			Vector<String> recipes;
			recipes.push_back(craft_recipe->get_path());
			class_profile->set_custom_data("recipes", recipes);
		}
	}

	emit_signal("crafts_recipe_added", this, craft_recipe);

	ORPC(craft_addc_recipe_id, id);
}
void Entity::craft_removes_recipe(Ref<CraftRecipe> craft_recipe) {
	for (int i = 0; i < _s_craft_recipes.size(); ++i) {
		if (_s_craft_recipes.get(i) == craft_recipe) {
			_s_craft_recipes.remove(i);
			break;
		}
	}

	emit_signal("crafts_recipe_removed", this, craft_recipe);

	ORPC(craft_removec_recipe, craft_recipe);
}
void Entity::craft_removes_recipe_id(int id) {
	Ref<CraftRecipe> craft_recipe;

	for (int i = 0; i < _s_craft_recipes.size(); ++i) {
		craft_recipe = _s_craft_recipes.get(i);

		if (craft_recipe->get_id() == id) {
			_s_craft_recipes.remove(i);
			break;
		}
	}

	emit_signal("crafts_recipe_removed", this, craft_recipe);

	ORPC(craft_removec_recipe_id, id);
}
Ref<CraftRecipe> Entity::craft_gets_recipe(int index) {
	ERR_FAIL_INDEX_V(index, _s_craft_recipes.size(), Ref<CraftRecipe>());

	return _s_craft_recipes.get(index);
}
Ref<CraftRecipe> Entity::craft_gets_recipe_id(int id) {
	for (int i = 0; i < _s_craft_recipes.size(); ++i) {
		Ref<CraftRecipe> craft_recipe = _s_craft_recipes.get(i);

		if (craft_recipe->get_id() == id) {
			return craft_recipe;
		}
	}

	return Ref<CraftRecipe>();
}
int Entity::craft_gets_recipe_count() {
	return _s_craft_recipes.size();
}

bool Entity::craft_hasc_recipe(Ref<CraftRecipe> craft_recipe) {
	for (int i = 0; i < _c_craft_recipes.size(); ++i) {
		if (_c_craft_recipes.get(i) == craft_recipe) {
			return true;
		}
	}

	return false;
}
bool Entity::craft_hasc_recipe_id(int id) {
	for (int i = 0; i < _c_craft_recipes.size(); ++i) {
		Ref<CraftRecipe> cr = _c_craft_recipes.get(i);

		ERR_CONTINUE(!cr.is_valid());

		if (cr->get_id() == id) {
			return true;
		}
	}

	return false;
}
void Entity::craft_addc_recipe(Ref<CraftRecipe> craft_recipe) {
	if (craft_hasc_recipe(craft_recipe))
		return;

	_c_craft_recipes.push_back(craft_recipe);

	emit_signal("ccraft_recipe_added", this, craft_recipe);
}
void Entity::craft_addc_recipe_id(int id) {
	ERR_FAIL_COND(!ESS::get_singleton());

	if (craft_hasc_recipe_id(id))
		return;

	Ref<CraftRecipe> craft_recipe = ESS::get_singleton()->get_resource_db()->get_craft_recipe(id);

	ERR_FAIL_COND(!craft_recipe.is_valid());

	_c_craft_recipes.push_back(craft_recipe);

	emit_signal("ccraft_recipe_added", this, craft_recipe);
}
void Entity::craft_removec_recipe(Ref<CraftRecipe> craft_recipe) {
	for (int i = 0; i < _c_craft_recipes.size(); ++i) {
		if (_c_craft_recipes.get(i) == craft_recipe) {
			_c_craft_recipes.remove(i);
			break;
		}
	}

	emit_signal("ccraft_recipe_removed", this, craft_recipe);
}
void Entity::craft_removec_recipe_id(int id) {
	Ref<CraftRecipe> craft_recipe;

	for (int i = 0; i < _c_craft_recipes.size(); ++i) {
		craft_recipe = _c_craft_recipes.get(i);

		if (craft_recipe->get_id() == id) {
			_c_craft_recipes.remove(i);
			break;
		}
	}

	emit_signal("ccraft_recipe_removed", this, craft_recipe);
}
Ref<CraftRecipe> Entity::craft_getc_recipe(int index) {
	ERR_FAIL_INDEX_V(index, _c_craft_recipes.size(), Ref<CraftRecipe>());

	return _c_craft_recipes.get(index);
}
int Entity::craft_getc_recipe_count() {
	return _c_craft_recipes.size();
}

Vector<Variant> Entity::scraft_recipes_get() {
	VARIANT_ARRAY_GET(_s_craft_recipes);
}
void Entity::scraft_recipes_set(const Vector<Variant> &resources) {
	VARIANT_ARRAY_SET(resources, _s_craft_recipes, CraftRecipe);
}

////    Stat System    ////

EntityStat Entity::get_stat(const int stat_id) const {
	ERR_FAIL_INDEX_V(stat_id, ESS::get_singleton()->stat_get_count(), EntityStat());

	return _stats[stat_id];
}

void Entity::set_stat(const int stat_id, const EntityStat &entry) {
	ERR_FAIL_INDEX(stat_id, ESS::get_singleton()->stat_get_count());

	_stats.set(stat_id, entry);
}

bool Entity::stat_get_dirty(const int stat_id) const {
	ERR_FAIL_INDEX_V(stat_id, ESS::get_singleton()->stat_get_count(), false);

	return _stats[stat_id].dirty;
}
void Entity::stat_set_dirty(const int stat_id, const bool value) {
	ERR_FAIL_INDEX(stat_id, ESS::get_singleton()->stat_get_count());

	_stats.write[stat_id].dirty = value;
}

float Entity::stat_get_base(const int stat_id) const {
	ERR_FAIL_INDEX_V(stat_id, ESS::get_singleton()->stat_get_count(), 0);

	return _stats[stat_id].base;
}
void Entity::stat_set_base(const int stat_id, const float value) {
	ERR_FAIL_INDEX(stat_id, ESS::get_singleton()->stat_get_count());

	_stats.write[stat_id].base = value;

	stat_recalculate(stat_id);
}
void Entity::stat_mod_base(const int stat_id, const float value) {
	ERR_FAIL_INDEX(stat_id, ESS::get_singleton()->stat_get_count());

	_stats.write[stat_id].base += value;

	stat_recalculate(stat_id);
}

float Entity::stat_get_base_calculated(const int stat_id) const {
	ERR_FAIL_INDEX_V(stat_id, ESS::get_singleton()->stat_get_count(), 0);

	return _stats[stat_id].base_calculated;
}
void Entity::stat_set_base_calculated(const int stat_id, const float value) {
	ERR_FAIL_INDEX(stat_id, ESS::get_singleton()->stat_get_count());

	_stats.write[stat_id].base_calculated = value;

	stat_recalculate(stat_id);
}

float Entity::stat_get_bonus(const int stat_id) const {
	ERR_FAIL_INDEX_V(stat_id, ESS::get_singleton()->stat_get_count(), 0);

	return _stats[stat_id].bonus;
}
void Entity::stat_set_bonus(const int stat_id, const float value) {
	ERR_FAIL_INDEX(stat_id, ESS::get_singleton()->stat_get_count());

	_stats.write[stat_id].bonus = value;

	stat_recalculate(stat_id);
}
void Entity::stat_mod_bonus(const int stat_id, const float value) {
	ERR_FAIL_INDEX(stat_id, ESS::get_singleton()->stat_get_count());

	_stats.write[stat_id].bonus += value;

	stat_recalculate(stat_id);
}

float Entity::stat_get_percent(const int stat_id) const {
	ERR_FAIL_INDEX_V(stat_id, ESS::get_singleton()->stat_get_count(), 0);

	return _stats[stat_id].percent;
}
void Entity::stat_set_percent(const int stat_id, const float value) {
	ERR_FAIL_INDEX(stat_id, ESS::get_singleton()->stat_get_count());

	_stats.write[stat_id].percent = value;

	stat_recalculate(stat_id);
}
void Entity::stat_mod_percent(const int stat_id, const float value) {
	ERR_FAIL_INDEX(stat_id, ESS::get_singleton()->stat_get_count());

	_stats.write[stat_id].percent += value;

	stat_recalculate(stat_id);
}

void Entity::stat_mod(const int stat_id, const float base, const float bonus, const float percent) {
	ERR_FAIL_INDEX(stat_id, ESS::get_singleton()->stat_get_count());

	_stats.write[stat_id].base += base;
	_stats.write[stat_id].bonus += bonus;
	_stats.write[stat_id].percent += percent;

	stat_recalculate(stat_id);
}

float Entity::stat_gets_current(const int stat_id) const {
	ERR_FAIL_INDEX_V(stat_id, ESS::get_singleton()->stat_get_count(), 0);

	return _stats[stat_id].scurrent;
}
void Entity::stat_sets_current(const int stat_id, const float value) {
	ERR_FAIL_INDEX(stat_id, ESS::get_singleton()->stat_get_count());

	_stats.write[stat_id].scurrent = value;
}

float Entity::stat_getc_current(const int stat_id) const {
	ERR_FAIL_INDEX_V(stat_id, ESS::get_singleton()->stat_get_count(), 0);

	return _stats[stat_id].ccurrent;
}
void Entity::stat_setc_current(const int stat_id, const float value) {
	ERR_FAIL_INDEX(stat_id, ESS::get_singleton()->stat_get_count());

	_stats.write[stat_id].ccurrent = value;

	notification_cstat_changed(stat_id, value);
}

void Entity::stat_recalculate(const int stat_id) {
	ERR_FAIL_INDEX(stat_id, ESS::get_singleton()->stat_get_count());

	stat_sets_current(stat_id, (stat_get_base(stat_id) + stat_get_base_calculated(stat_id) + stat_get_bonus(stat_id)) * (stat_get_percent(stat_id) / 100.0));

	stat_set_dirty(stat_id, true);

	notification_sstat_changed(stat_id, stat_gets_current(stat_id));
}

void Entity::dies() {
	//serverside

	notification_sdeath();

	//send an event to client
	VRPC(diec);

	//signal
	emit_signal("diesd", this);
}

void Entity::diec() {
	notification_cdeath();
}

void Entity::notification_sstat_changed(const int statid, const float current) {
	for (int i = 0; i < _s_resources.size(); ++i) {
		_s_resources.get(i)->notification_sstat_changed(statid, current);
	}
}
void Entity::notification_cstat_changed(const int statid, const float current) {
	for (int i = 0; i < _c_resources.size(); ++i) {
		_c_resources.get(i)->notification_cstat_changed(statid, current);
	}
}

void Entity::ssend_stat(int id, int ccurrent) {
	ERR_FAIL_INDEX(id, ESS::get_singleton()->stat_get_count());

	//Only the owner needs access to stats
	ORPC(creceive_stat, id, ccurrent);
}

void Entity::creceive_stat(int id, int ccurrent) {
	ERR_FAIL_INDEX(id, ESS::get_singleton()->stat_get_count());

	stat_setc_current(id, ccurrent);
}

////    Equip Slots    ////

bool Entity::equip_should_deny(int equip_slot, Ref<ItemInstance> item) {
	if (_s_entity_controller == EntityEnums::ENITIY_CONTROLLER_AI && _s_ai.is_valid()) {
		if (_s_ai->equip_should_deny(this, equip_slot, item))
			return true;
	}

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		if (ad->get_aura()->equip_should_deny(ad, equip_slot, item))
			return true;
	}

	if (has_method("_equip_should_deny"))
		if (call("_equip_should_deny", equip_slot, item))
			return true;

	return false;
}

void Entity::equip_son_success(int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	if (_s_entity_controller == EntityEnums::ENITIY_CONTROLLER_AI && _s_ai.is_valid()) {
		_s_ai->equip_son_success(this, equip_slot, item, old_item, bag_slot);
	}

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->equip_son_success(ad, equip_slot, item, old_item, bag_slot);
	}

	if (has_method("_equip_son_success"))
		call("_equip_son_success", equip_slot, item, old_item, bag_slot);

	emit_signal("equip_son_success", this, equip_slot, item, old_item, bag_slot);
}

void Entity::equip_son_fail(int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	if (_s_entity_controller == EntityEnums::ENITIY_CONTROLLER_AI && _s_ai.is_valid()) {
		_s_ai->equip_son_fail(this, equip_slot, item, old_item, bag_slot);
	}

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->equip_son_fail(ad, equip_slot, item, old_item, bag_slot);
	}

	if (has_method("_equip_son_fail"))
		call("_equip_son_fail", equip_slot, item, old_item, bag_slot);

	emit_signal("equip_son_fail", this, equip_slot, item, old_item, bag_slot);
}

void Entity::equip_con_success(int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	if (_s_entity_controller == EntityEnums::ENITIY_CONTROLLER_AI && _s_ai.is_valid()) {
		_s_ai->equip_con_success(this, equip_slot, item, old_item, bag_slot);
	}

	for (int i = 0; i < _c_auras.size(); ++i) {
		Ref<AuraData> ad = _c_auras.get(i);

		ad->get_aura()->equip_con_success(ad, equip_slot, item, old_item, bag_slot);
	}

	if (has_method("_equip_con_success"))
		call("_equip_con_success", equip_slot, item, old_item, bag_slot);

	emit_signal("equip_con_success", this, equip_slot, item, old_item, bag_slot);
}

void Entity::equip_con_fail(int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot) {
	if (_s_entity_controller == EntityEnums::ENITIY_CONTROLLER_AI && _s_ai.is_valid()) {
		_s_ai->equip_con_fail(this, equip_slot, item, old_item, bag_slot);
	}

	for (int i = 0; i < _c_auras.size(); ++i) {
		Ref<AuraData> ad = _c_auras.get(i);

		ad->get_aura()->equip_con_fail(ad, equip_slot, item, old_item, bag_slot);
	}

	if (has_method("_equip_con_fail"))
		call("_equip_con_fail", equip_slot, item, old_item, bag_slot);

	emit_signal("equip_con_fail", this, equip_slot, item, old_item, bag_slot);
}

void Entity::equip_crequest(int equip_slot, int bag_slot) {
	RPCS(equips, equip_slot, bag_slot)
}
void Entity::equips(int equip_slot, int bag_slot) {
	call("_equips", equip_slot, bag_slot);
}
void Entity::_equips(int equip_slot, int bag_slot) {
	ERR_FAIL_INDEX(equip_slot, ESS::get_singleton()->equip_slot_get_count());
	ERR_FAIL_COND(!_s_bag.is_valid());

	Ref<ItemInstance> bag_item = _s_bag->get_item(bag_slot);
	Ref<ItemInstance> equipped_item = equip_gets_slot(equip_slot);

	if (!equip_can_equip_item(equip_slot, bag_item)) {
		ORPC(equip_cfail, equip_slot, bag_slot);
		return;
	}

	if (equip_should_deny(equip_slot, bag_item)) {
		ORPC(equip_cfail, equip_slot, bag_slot);
		return;
	}

	//check armor type
	//check required skills

	if (equipped_item.is_valid())
		equip_deapplys_item(equipped_item);

	if (bag_item.is_valid())
		equip_applys_item(bag_item);

	equip_sets_slot(equip_slot, bag_item);
	_s_bag->add_item_at(bag_slot, equipped_item, false);

	ORPC(equip_csuccess, equip_slot, bag_slot);
}
void Entity::equip_csuccess(int equip_slot, int bag_slot) {
	ERR_FAIL_INDEX(equip_slot, ESS::get_singleton()->equip_slot_get_count());
	ERR_FAIL_COND(!_c_bag.is_valid());

	Ref<ItemInstance> old_bag_item = _c_bag->get_item(bag_slot);
	Ref<ItemInstance> old_equipped_item = equip_getc_slot(equip_slot);

	_c_bag->add_item_at(bag_slot, old_equipped_item);
	equip_setc_slot(equip_slot, old_bag_item);

	if (old_equipped_item.is_valid())
		equip_deapplyc_item(old_equipped_item);

	if (old_bag_item.is_valid())
		equip_applyc_item(old_bag_item);

	equip_con_success(equip_slot, old_bag_item, old_equipped_item, bag_slot);
}
void Entity::equip_cfail(int equip_slot, int bag_slot) {
	ERR_FAIL_INDEX(equip_slot, ESS::get_singleton()->equip_slot_get_count());
	ERR_FAIL_COND(!_c_bag.is_valid());

	Ref<ItemInstance> bag_item = _c_bag->get_item(bag_slot);
	Ref<ItemInstance> equipped_item = equip_getc_slot(equip_slot);

	equip_con_fail(equip_slot, equipped_item, bag_item, bag_slot);
}

Ref<ItemInstance> Entity::equip_gets_slot(int index) {
	ERR_FAIL_INDEX_V(index, ESS::get_singleton()->equip_slot_get_count(), Ref<ItemInstance>());

	return _s_equipment[index];
}
void Entity::equip_sets_slot(int index, Ref<ItemInstance> item) {
	ERR_FAIL_INDEX(index, ESS::get_singleton()->equip_slot_get_count());

	_s_equipment.write[index] = item;
}

Ref<ItemInstance> Entity::equip_getc_slot(int index) {
	ERR_FAIL_INDEX_V(index, ESS::get_singleton()->equip_slot_get_count(), Ref<ItemInstance>());

	return _c_equipment[index];
}
void Entity::equip_setc_slot(int index, Ref<ItemInstance> item) {
	ERR_FAIL_INDEX(index, ESS::get_singleton()->equip_slot_get_count());

	_c_equipment.write[index] = item;
}

bool Entity::equip_can_equip_item(int equip_slot, Ref<ItemInstance> item) {
	return call("_equip_can_equip_item", equip_slot, item);
}
bool Entity::_equip_can_equip_item(int equip_slot, Ref<ItemInstance> item) {
	//deequip
	if (!item.is_valid())
		return true;

	Ref<ItemTemplate> it = item->get_item_template();

	ERR_FAIL_COND_V(!it.is_valid(), false);

	return it->get_equip_slot() == equip_slot;
}

void Entity::equip_applys_item(Ref<ItemInstance> item) {
	call("_equip_applys_item", item);
}
void Entity::equip_deapplys_item(Ref<ItemInstance> item) {
	call("_equip_deapplys_item", item);
}

void Entity::_equip_applys_item(Ref<ItemInstance> item) {
	ERR_FAIL_COND(!item.is_valid());

	Ref<ItemTemplate> it = item->get_item_template();

	ERR_FAIL_COND(!it.is_valid());

	for (int i = 0; i < item->stat_modifier_get_count(); ++i) {
		int sid = item->stat_modifier_get_stat_id(i);

		stat_mod_base(sid, item->stat_modifier_get_base_mod(i));
		stat_mod_bonus(sid, item->stat_modifier_get_bonus_mod(i));
		stat_mod_percent(sid, item->stat_modifier_get_percent_mod(i));
	}
}
void Entity::_equip_deapplys_item(Ref<ItemInstance> item) {
	ERR_FAIL_COND(!item.is_valid());

	Ref<ItemTemplate> it = item->get_item_template();

	ERR_FAIL_COND(!it.is_valid());

	for (int i = 0; i < item->stat_modifier_get_count(); ++i) {
		int sid = item->stat_modifier_get_stat_id(i);

		stat_mod_base(sid, -item->stat_modifier_get_base_mod(i));
		stat_mod_bonus(sid, -item->stat_modifier_get_bonus_mod(i));
		stat_mod_percent(sid, -item->stat_modifier_get_percent_mod(i));
	}
}

void Entity::equip_applyc_item(Ref<ItemInstance> item) {
	call("_equip_applyc_item", item);
}
void Entity::equip_deapplyc_item(Ref<ItemInstance> item) {
	call("_equip_deapplyc_item", item);
}

void Entity::_equip_applyc_item(Ref<ItemInstance> item) {
	ERR_FAIL_COND(!item.is_valid());

	Ref<ItemTemplate> it = item->get_item_template();

	ERR_FAIL_COND(!it.is_valid());

	if (it->get_model_visual().is_valid() && INSTANCE_VALIDATE(_character_skeleton)) {
		if (_character_skeleton->has_method("add_model_visual"))
			_character_skeleton->call("add_model_visual", it->get_model_visual());
	}
}
void Entity::_equip_deapplyc_item(Ref<ItemInstance> item) {
	ERR_FAIL_COND(!item.is_valid());

	Ref<ItemTemplate> it = item->get_item_template();

	ERR_FAIL_COND(!it.is_valid());

	if (it->get_model_visual().is_valid() && INSTANCE_VALIDATE(_character_skeleton)) {
		if (_character_skeleton->has_method("remove_model_visual"))
			_character_skeleton->call("remove_model_visual", it->get_model_visual());
	}
}

////    Resources    ////

Ref<EntityResource> Entity::resource_gets_index(int index) {
	ERR_FAIL_INDEX_V(index, _s_resources.size(), Ref<EntityResource>());

	return _s_resources.get(index);
}
Ref<EntityResource> Entity::resource_gets_id(int id) {
	for (int i = EntityEnums::ENTITY_RESOURCE_INDEX_RESOURCES_BEGIN; i < _s_resources.size(); ++i) {
		Ref<EntityResource> r = _s_resources.get(i);

		if (r->get_id() == id) {
			return r;
		}
	}

	return Ref<EntityResource>();
}
void Entity::resource_adds(Ref<EntityResource> resource) {
	ERR_FAIL_COND(!resource.is_valid());

	_s_resources.push_back(resource);

	resource->ons_added(this);

	notification_sentity_resource_added(resource);

	VRPCOBJP(resource_addc_rpc, _s_resources.size() - 1, JSON::print(resource->to_dict()), resource_addc, _s_resources.size() - 1, resource);
}
int Entity::resource_gets_count() {
	return _s_resources.size();
}
void Entity::resource_removes(int index) {
	ERR_FAIL_INDEX(index, _s_resources.size());

	Ref<EntityResource> res = _s_resources.get(index);
	_s_resources.remove(index);

	notification_sentity_resource_removed(res);

	VRPC(resource_removec, index);
}
void Entity::resource_clears() {
	_s_resources.resize(EntityEnums::ENTITY_RESOURCE_INDEX_RESOURCES_BEGIN);

	VRPC(resource_clearc);
}

void Entity::resource_addc_rpc(int index, String data) {
	//Ref<EntityResource> res;

	Dictionary dict = data_as_dict(data);
	/*
	String clsname = dict.get("id", "EntityResource");

	res = Ref<EntityResource>(Object::cast_to<EntityResource>(ClassDB::instance(clsname)));

	ERR_FAIL_COND(!res.is_valid());
	//res.instance();

	String script_path = dict.get("script", "");

	Ref<Script> s;
	if (script_path != "") {
		if (ResourceLoader::exists(script_path)) {
			s = ResourceLoader::load(script_path);

			if (s.is_valid()) {
				res->set_script(s.get_ref_ptr());
			} else {
				ERR_PRINT("Error, script is not valid! " + script_path);
			}
		}
	}

	Dictionary d = dict.get("data", Dictionary());
	res->from_dict(d);
	res->resolve_references();
*/

	int data_id = dict.get("data_id", 0);

	Ref<EntityResource> resd = ESS::get_singleton()->get_resource_db()->get_entity_resource(data_id);

	ERR_FAIL_COND(!resd.is_valid());

	Ref<EntityResource> res = resd->duplicate();

	ERR_FAIL_COND(!res.is_valid());

	res->from_dict(dict);

	resource_addc(index, res);
}

Ref<EntityResource> Entity::resource_getc_index(int index) {
	ERR_FAIL_INDEX_V(index, _c_resources.size(), Ref<EntityResource>());

	return _c_resources.get(index);
}
Ref<EntityResource> Entity::resource_getc_id(int id) {
	for (int i = EntityEnums::ENTITY_RESOURCE_INDEX_RESOURCES_BEGIN; i < _c_resources.size(); ++i) {
		Ref<EntityResource> r = _c_resources.get(i);

		if (r->get_id() == id) {
			return r;
		}
	}

	return Ref<EntityResource>(NULL);
}
void Entity::resource_addc(int index, Ref<EntityResource> resource) {
	ERR_FAIL_COND(!resource.is_valid());

	if (_c_resources.size() <= index) {
		_c_resources.resize(index + 1);
	}

	_c_resources.set(index, resource);

	resource->onc_added(this);

	notification_centity_resource_added(resource);
}
int Entity::resource_getc_count() {
	return _c_resources.size();
}
void Entity::resource_removec(int index) {
	ERR_FAIL_INDEX(index, _c_resources.size());

	Ref<EntityResource> res = _c_resources.get(index);
	_c_resources.remove(index);

	notification_centity_resource_removed(res);
}
void Entity::resource_clearc() {
	_c_resources.resize(EntityEnums::ENTITY_RESOURCE_INDEX_RESOURCES_BEGIN);
}

void Entity::resource_sends_current(int index, int current) {
	VRPC(resource_creceive_current, index, current);
}
void Entity::resource_sends_curr_max(int index, int current, int max) {
	VRPC(resource_creceive_curr_max, index, current, max);
}
void Entity::resource_sends_data(int index, String data) {
	VRPC(resource_creceive_data, index, data);
}

void Entity::resource_creceive_current(int index, int current) {
	ERR_FAIL_INDEX(index, _c_resources.size());

	Ref<EntityResource> res = _c_resources.get(index);

	ERR_FAIL_COND(!res.is_valid());

	res->receivec_update(current);
}
void Entity::resource_creceive_curr_max(int index, int current, int max) {
	ERR_FAIL_INDEX(index, _c_resources.size());

	Ref<EntityResource> res = _c_resources.get(index);

	ERR_FAIL_COND(!res.is_valid());

	res->receivec_update_full(current, max);
}
void Entity::resource_creceive_data(int index, String data) {
	ERR_FAIL_INDEX(index, _c_resources.size());

	Ref<EntityResource> res = _c_resources.get(index);

	ERR_FAIL_COND(!res.is_valid());

	res->receivec_update_string(data);
}

Ref<EntityResource> Entity::gets_health() {
	return _s_resources.get(EntityEnums::ENTITY_RESOURCE_INDEX_HEALTH);
}
Ref<EntityResource> Entity::gets_speed() {
	return _s_resources.get(EntityEnums::ENTITY_RESOURCE_INDEX_SPEED);
}
Ref<EntityResource> Entity::getc_health() {
	return _c_resources.get(EntityEnums::ENTITY_RESOURCE_INDEX_HEALTH);
}
Ref<EntityResource> Entity::getc_speed() {
	return _c_resources.get(EntityEnums::ENTITY_RESOURCE_INDEX_SPEED);
}

Vector<Variant> Entity::sresources_get() {
	VARIANT_ARRAY_GET(_s_resources);
}
void Entity::sresources_set(const Vector<Variant> &resources) {
	VARIANT_ARRAY_SET(resources, _s_resources, EntityResource);

	for (int i = 0; i < _s_resources.size(); ++i) {
		Ref<EntityResource> res = _s_resources[i];

		ERR_CONTINUE(!res.is_valid());

		res->set_owner(this);
	}
}

void Entity::stake_damage(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	//serverside

	if (gets_is_dead()) {
		return;
	}

	notification_sdamage(SpellEnums::NOTIFICATION_DAMAGE_BEFORE_HIT, info);

	if (info->get_immune()) {
		VRPCOBJ12(cdamage_dealt_rpc, JSON::print(info->to_dict()), notification_cdamage, SpellEnums::NOTIFICATION_DAMAGE_DAMAGE_DEALT, info);

		return;
	}

	//send it through the passive damage reductions pipeline
	sapply_passives_damage_receive(info);

	//send it through the onbeforehit handler
	notification_sdamage(SpellEnums::NOTIFICATION_DAMAGE_BEFORE_DAMAGE, info);

	//send it throug the onhit pipeliine
	notification_sdamage(SpellEnums::NOTIFICATION_DAMAGE_HIT, info);

	notification_sdamage(SpellEnums::NOTIFICATION_DAMAGE_RECEIVE, info);

	Ref<EntityResource> hp = resource_gets_index(EntityEnums::ENTITY_RESOURCE_INDEX_HEALTH);
	ERR_FAIL_COND(!hp.is_valid());

	int h = hp->get_current_value() - info->damage_get();

	if (h < 0) {
		h = 0;
	}

	hp->set_current_value(h);

	notification_sdamage(SpellEnums::NOTIFICATION_DAMAGE_DAMAGE_DEALT, info);

	//signal
	emit_signal("son_damage_received", this, info);

	//send an event to client
	VRPCOBJ12(cdamage_dealt_rpc, JSON::print(info->to_dict()), notification_cdamage, SpellEnums::NOTIFICATION_DAMAGE_DAMAGE_DEALT, info);

	if (hp->get_current_value() <= 0) {
		dies();
	}
}

void Entity::sdeal_damage_to(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	//serverside

	if (gets_is_dead()) {
		return;
	}

	sapply_passives_damage_deal(info);
	info->receiver_get()->stake_damage(info);
	notification_sdamage(SpellEnums::NOTIFICATION_DAMAGE_DEALT_DAMAGE, info);

	//send an event to client
	VRPCOBJ12(cdealt_damage_rpc, JSON::print(info->to_dict()), notification_cdamage, SpellEnums::NOTIFICATION_DAMAGE_DEALT_DAMAGE, info);

	//signal
	emit_signal("son_dealt_damage", this, info);
}

void Entity::stake_heal(Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	//serverside

	if (gets_is_dead()) {
		return;
	}

	notification_sheal(SpellEnums::NOTIFICATION_HEAL_BEFORE_HIT, info);

	if (info->get_immune()) {
		VRPCOBJ12(cheal_dealt_rpc, JSON::print(info->to_dict()), notification_cheal, SpellEnums::NOTIFICATION_HEAL_HEAL_DEALT, info);
		return;
	}

	//send it through the passive damage reductions pipeline
	sapply_passives_heal_receive(info);

	//send it through the onbeforehit handler
	notification_sheal(SpellEnums::NOTIFICATION_HEAL_BEFORE_HEAL, info);

	notification_sheal(SpellEnums::NOTIFICATION_HEAL_RECEIVE, info);

	Ref<EntityResource> hp = resource_gets_index(EntityEnums::ENTITY_RESOURCE_INDEX_HEALTH);
	ERR_FAIL_COND(!hp.is_valid());

	int h = hp->get_current_value() + info->heal_get();

	if (h > hp->get_max_value()) {
		h = hp->get_max_value();
	}
	hp->set_current_value(h);

	//send an event to client
	VRPCOBJ12(cheal_dealt_rpc, JSON::print(info->to_dict()), notification_cheal, SpellEnums::NOTIFICATION_HEAL_HEAL_DEALT, info);

	//signal
	emit_signal("son_heal_received", this, info);
}

void Entity::sdeal_heal_to(Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());
	ERR_FAIL_COND(info->receiver_get() == NULL);

	//serverside

	if (gets_is_dead()) {
		return;
	}

	sapply_passives_heal_deal(info);
	info->receiver_get()->stake_heal(info);
	notification_sheal(SpellEnums::NOTIFICATION_HEAL_HEAL_DEALT, info);

	VRPCOBJ12(cdealt_heal_rpc, JSON::print(info->to_dict()), notification_cheal, SpellEnums::NOTIFICATION_HEAL_DEALT_HEAL, info);

	emit_signal("son_heal_dealt", this, info);
}

//Damage, Heal RPCs
void Entity::cdamage_dealt_rpc(String data) {
	Ref<SpellDamageInfo> info;
	info.instance();
	info->from_dict(data_as_dict(data));
	info->resolve_references(this);

	notification_cdamage(SpellEnums::NOTIFICATION_DAMAGE_DAMAGE_DEALT, info);
}
void Entity::cdealt_damage_rpc(String data) {
	Ref<SpellDamageInfo> info;
	info.instance();
	info->from_dict(data_as_dict(data));
	info->resolve_references(this);

	notification_cdamage(SpellEnums::NOTIFICATION_DAMAGE_DEALT_DAMAGE, info);
}
void Entity::cheal_dealt_rpc(String data) {
	Ref<SpellHealInfo> info;
	info.instance();
	info->from_dict(data_as_dict(data));
	info->resolve_references(this);

	notification_cheal(SpellEnums::NOTIFICATION_HEAL_HEAL_DEALT, info);
}
void Entity::cdealt_heal_rpc(String data) {
	Ref<SpellHealInfo> info;
	info.instance();
	info->from_dict(data_as_dict(data));
	info->resolve_references(this);

	notification_cheal(SpellEnums::NOTIFICATION_HEAL_DEALT_HEAL, info);
}

//Interactions
bool Entity::cans_interact() {
	if (!_s_entity_data.is_valid()) {
		if (has_method("_cans_interact")) {
			return call("_cans_interact");
		}

		return false;
	}

	return _s_entity_data->cans_interact(this);
}

void Entity::sinteract() {
	if (!cans_interact()) {
		return;
	}

	if (!_s_entity_data.is_valid()) {
		if (has_method("_sinteract")) {
			call("_sinteract");
		}
	}

	_s_entity_data->sinteract(this);
}

bool Entity::canc_interact() {
	if (has_method("_canc_interact")) {
		return call("_canc_interact");
	}

	if (!INSTANCE_VALIDATE(_c_target)) {
		return false;
	}

	EntityEnums::EntityInteractionType it = _c_target->getc_entity_interaction_type();

	if (it == EntityEnums::ENITIY_INTERACTION_TYPE_NONE || it == EntityEnums::ENITIY_INTERACTION_TYPE_NORMAL) {
		return false;
	}

	return true;
}

void Entity::crequest_interact() {
	sinteract();
}

void Entity::ssend_open_window(int window_id) {
	ORPC(copen_window, window_id);
}
void Entity::copen_window(int window_id) {
	emit_signal("onc_open_winow_request", window_id);
}

bool Entity::iss_target_in_interact_range() {
	return call("_iss_target_in_interact_range");
}
bool Entity::isc_target_in_interact_range() {
	return call("_isc_target_in_interact_range");
}
bool Entity::_iss_target_in_interact_range() {
	Entity *t = gets_target();

	if (!ObjectDB::instance_validate(t)) {
		return false;
	}

	Node2D *b2d = get_body_2d();

	if (b2d) {
		Node2D *tb = t->get_body_2d();

		if (!tb) {
			return false;
		}

		return (b2d->get_transform().get_origin() - tb->get_transform().get_origin()).length_squared() <= EntityEnums::ENTITY_INTERACT_RANGE_SQUARED;
	}

	Spatial *b3d = get_body_3d();

	if (b3d) {
		Spatial *tb = t->get_body_3d();

		if (!tb) {
			return false;
		}

		return (b3d->get_transform().get_origin() - tb->get_transform().get_origin()).length_squared() <= EntityEnums::ENTITY_INTERACT_RANGE_SQUARED;
	}

	return false;
}
bool Entity::_isc_target_in_interact_range() {
	Entity *t = getc_target();

	if (!ObjectDB::instance_validate(t)) {
		return false;
	}

	Node2D *b2d = get_body_2d();

	if (b2d) {
		Node2D *tb = t->get_body_2d();

		if (!tb) {
			return false;
		}

		return (b2d->get_transform().get_origin() - tb->get_transform().get_origin()).length_squared() <= EntityEnums::ENTITY_INTERACT_RANGE_SQUARED;
	}

	Spatial *b3d = get_body_3d();

	if (b3d) {
		Spatial *tb = t->get_body_3d();

		if (!tb) {
			return false;
		}

		return (b3d->get_transform().get_origin() - tb->get_transform().get_origin()).length_squared() <= EntityEnums::ENTITY_INTERACT_RANGE_SQUARED;
	}

	return false;
}

//XP Operations
void Entity::xp_adds(int value) {
	_s_xp += value;

	notification_sxp_gained(value);

	ORPC(xp_addc, value);
}
void Entity::xp_addc(int value) {
	_c_xp += value;

	notification_cxp_gained(value);
}

void Entity::levelups(int value) {
	if (value <= 0)
		return;

	if (_s_level == ESS::get_singleton()->get_max_character_level())
		return;

	_s_level += value;

	notification_slevel_up(value);

	VRPC(levelupc, value);
}
void Entity::levelupc(int value) {
	_c_level += value;

	notification_clevel_up(value);
}

////    Spell System    ////

void Entity::spell_casts(int spell_id) {
	if (_s_spells.size() == 0) {
		return;
	}

	for (int i = 0; i < _s_spells.size(); i++) {
		Ref<Spell> s = _s_spells[i];

		ERR_CONTINUE(!s.is_valid());

		if (s->get_id() == spell_id) {
			s->cast_starts_simple(this, 1);
			return;
		}
	}
}

void Entity::spell_crequest_cast(int spell_id) {
	RPCS(spell_casts, spell_id);
}

void Entity::item_uses(int item_id) {
	call("_item_uses", item_id);
}
void Entity::item_crequest_use(int item_id) {
	RPCS(item_uses, item_id);
}
void Entity::_item_uses(int item_id) {
	Ref<ItemTemplate> it = ESS::get_singleton()->get_resource_db()->get_item_template(item_id);

	ERR_FAIL_COND(!it.is_valid());

	Ref<Spell> sp = it->get_use_spell();

	ERR_FAIL_COND(!sp.is_valid());

	ItemEnums::ItemType type = it->get_item_type();

	if (type == ItemEnums::ITEM_TYPE_EQUIPMENT) {
		Ref<ItemInstance> ii = equip_gets_slot(it->get_equip_slot());

		if (!ii.is_valid())
			return;

		if (ii->get_item_template() != it)
			return;

		Ref<SpellCastInfo> info;
		info.instance();

		info->caster_set(this);
		info->target_set(gets_target());
		info->has_cast_time_set(sp->cast_time_get_enabled());
		info->cast_time_set(sp->cast_time_get());
		info->spell_scale_set(1);
		info->set_spell(sp);
		info->set_source_item(ii);
		info->set_source_template(it);

		cast_starts(info);

		sp->cast_starts(info);
	} else {
		if (!gets_bag()->has_item(it, 1))
			return;

		Ref<SpellCastInfo> info;
		info.instance();

		info->caster_set(this);
		info->target_set(gets_target());
		info->has_cast_time_set(sp->cast_time_get_enabled());
		info->cast_time_set(sp->cast_time_get());
		info->spell_scale_set(1);
		info->set_spell(sp);
		info->set_source_template(it);

		cast_starts(info);

		sp->cast_starts(info);
	}
}

void Entity::update_auras(float delta) {
	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->aura_supdate(ad, delta);
	}
}

void Entity::sapply_passives_damage_receive(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->aura_sapply_passives_damage_receive(info);
	}
}

void Entity::sapply_passives_damage_deal(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->aura_sapply_passives_damage_deal(info);
	}
}

void Entity::sapply_passives_heal_receive(Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->aura_sapply_passives_heal_receive(info);
	}
}

void Entity::sapply_passives_heal_deal(Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->aura_sapply_passives_heal_deal(info);
	}
}

void Entity::notification_saura(int what, Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (_s_entity_controller == EntityEnums::ENITIY_CONTROLLER_AI && _s_ai.is_valid()) {
		_s_ai->notification_saura(what, data);
	}

	if (has_method("_notification_saura"))
		call("_notification_saura", what, data);

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->notification_saura(what, data);
	}

	emit_signal("notification_saura", what, data);
}
void Entity::notification_sheal(int what, Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_s_entity_controller == EntityEnums::ENITIY_CONTROLLER_AI && _s_ai.is_valid()) {
		_s_ai->notification_sheal(what, info);
	}

	if (has_method("_notification_sheal"))
		call("_notification_sheal", what, info);

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->notification_sheal(what, ad, info);
	}
}
void Entity::notification_scast(int what, Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	NOTIFICATION_AURA_DIFF_IMPLS(notification_scast, notification_aura_scast, "notification_scast", what, info);
}
void Entity::notification_sdamage(int what, Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_s_entity_controller == EntityEnums::ENITIY_CONTROLLER_AI && _s_ai.is_valid()) {
		_s_ai->notification_sdamage(what, info);
	}

	if (has_method("_notification_sdamage"))
		call("_notification_sdamage", what, info);

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->notification_sdamage(what, ad, info);
	}
}

void Entity::notification_sdeath() {
	if (_s_entity_controller == EntityEnums::ENITIY_CONTROLLER_AI && _s_ai.is_valid()) {
		_s_ai->notification_sdeath(this);
	}

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->notification_sdeath(ad);
	}

	if (has_method("_notification_sdeath"))
		call("_notification_sdeath");
}

void Entity::notification_scooldown_added(int id, float value) {
	NOTIFICATION_RES_IMPLS(notification_scooldown_added, "scooldown_added", id, value);
}
void Entity::notification_scooldown_removed(int id, float value) {
	NOTIFICATION_RES_IMPLS(notification_scooldown_removed, "scooldown_removed", id, value);
}

void Entity::notification_scategory_cooldown_added(int id, float value) {
	NOTIFICATION_RES_IMPLS(notification_scategory_cooldown_added, "scategory_cooldown_added", id, value);
}
void Entity::notification_scategory_cooldown_removed(int id, float value) {
	NOTIFICATION_RES_IMPLS(notification_scategory_cooldown_removed, "scategory_cooldown_removed", id, value);
}

void Entity::notification_sgcd_started() {
	NOTIFICATION_IMPLS(notification_sgcd_started, "sgcd_started", _s_gcd);
}
void Entity::notification_sgcd_finished() {
	NOTIFICATION_IMPLSS(notification_sgcd_finished, "sgcd_finished");
}
void Entity::notification_cgcd_started() {
	NOTIFICATION_IMPLC(notification_cgcd_started, "cgcd_started", _c_gcd);
}
void Entity::notification_cgcd_finished() {
	NOTIFICATION_IMPLCS(notification_cgcd_finished, "cgcd_finished");
}

void Entity::son_physics_process(float delta) {
	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_physics_process_aura(ad);
	}

	if (_physics_process_scis.size() > 0) {
		for (int i = 0; i < _physics_process_scis.size(); ++i) {
			Ref<SpellCastInfo> sci = _physics_process_scis.get(i);

			ERR_CONTINUE(!sci.is_valid());

			sci->physics_process(delta);
		}

		_physics_process_scis.clear();
	}
}

void Entity::notification_sxp_gained(int value) {
	NOTIFICATION_IMPLS(notification_sxp_gained, "notification_sxp_gained", value);
}

void Entity::notification_slevel_up(int value) {
	NOTIFICATION_IMPLS(notification_slevel_up, "notification_slevel_up", value);
}

void Entity::notification_sentity_resource_added(Ref<EntityResource> resource) {
	NOTIFICATION_RES_IMPLS(notification_sentity_resource_added, "sentity_resource_added", resource);
}

void Entity::notification_sentity_resource_removed(Ref<EntityResource> resource) {
	NOTIFICATION_RES_IMPLS(notification_sentity_resource_removed, "sentity_resource_removed", resource);
}

void Entity::aura_adds(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	notification_saura(SpellEnums::NOTIFICATION_AURA_BEFORE_APPLIED, aura);

	aura->set_owner(this);

	_s_auras.push_back(aura);

	notification_saura(SpellEnums::NOTIFICATION_AURA_AFTER_APPLIED, aura);

	notification_saura(SpellEnums::NOTIFICATION_AURA_ADDED, aura);

	if (!aura->get_aura()->aura_get_hide())
		VRPCOBJ(aura_addc_rpc, JSON::print(aura->to_dict()), aura_addc, aura);
}

void Entity::aura_removes(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	int aid = aura->get_aura_id();
	Entity *caster = aura->caster_get();

	Ref<AuraData> a;
	bool removed = false;
	for (int i = 0; i < _s_auras.size(); i++) {
		a = _s_auras.get(i);

		if (a->get_aura_id() == aid && a->caster_get() == caster) {
			_s_auras.remove(i);
			removed = true;
			break;
		}
	}

	if (removed) {
		notification_saura(SpellEnums::NOTIFICATION_AURA_REMOVED, a);

		if (!aura->get_aura()->aura_get_hide())
			VRPCOBJ(aura_removec_rpc, JSON::print(aura->to_dict()), aura_removec, aura);
	}
}

void Entity::aura_removes_exact(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	for (int i = 0; i < _s_auras.size(); i++) {
		Ref<AuraData> ad = _s_auras.get(i);

		if (ad == aura) {
			ad->get_aura()->son_remove(ad);

			_s_auras.remove(i);

			break;
		}
	}

	notification_saura(SpellEnums::NOTIFICATION_AURA_REMOVED, aura);

	if (!aura->get_aura()->aura_get_hide())
		VRPCOBJ(aura_removec_rpc, JSON::print(aura->to_dict()), aura_removec, aura);
}

void Entity::aura_removes_expired(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	for (int i = 0; i < _s_auras.size(); i++) {
		Ref<AuraData> ad = _s_auras.get(i);

		if (ad == aura) {
			ad->get_aura()->son_remove(ad);

			_s_auras.remove(i);

			break;
		}
	}

	notification_saura(SpellEnums::NOTIFICATION_AURA_REMOVED, aura);

	if (!aura->get_aura()->aura_get_hide())
		VRPCOBJ(aura_removec_rpc, JSON::print(aura->to_dict()), aura_removec, aura);
}

void Entity::aura_removes_dispelled(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	for (int i = 0; i < _s_auras.size(); i++) {
		Ref<AuraData> ad = _s_auras.get(i);

		if (ad == aura) {
			ad->get_aura()->son_remove(ad);

			_s_auras.remove(i);

			break;
		}
	}

	notification_saura(SpellEnums::NOTIFICATION_AURA_REMOVED, aura);

	if (!aura->get_aura()->aura_get_hide())
		VRPCOBJ(aura_removec_rpc, JSON::print(aura->to_dict()), aura_removec, aura);
}

void Entity::aura_refresheds(Ref<AuraData> aura) {
	//ERR_EXPLAIN("NYI");
	ERR_FAIL();

	ERR_FAIL_COND(!aura.is_valid());

	notification_saura(SpellEnums::NOTIFICATION_AURA_REFRESHED, aura);

	if (!aura->get_aura()->aura_get_hide())
		VRPCOBJ(aura_refreshedc_rpc, JSON::print(aura->to_dict()), aura_refreshedc, aura);
}

void Entity::aura_addc_rpc(String data) {
	Ref<AuraData> aura;
	aura.instance();
	aura->from_dict(data_as_dict(data));
	aura->set_owner(this);
	aura->resolve_references(this);

	aura_addc(aura);
}

void Entity::aura_removec_rpc(String data) {
	Ref<AuraData> aura;
	aura.instance();
	aura->from_dict(data_as_dict(data));
	aura->set_owner(this);
	aura->resolve_references(this);

	aura_removec(aura);
}

void Entity::aura_removec_exact_rpc(String data) {
	Ref<AuraData> aura;
	aura.instance();
	aura->from_dict(data_as_dict(data));
	aura->set_owner(this);
	aura->resolve_references(this);

	aura_removec_exact(aura);
}

void Entity::aura_removec_expired_rpc(String data) {
	Ref<AuraData> aura;
	aura.instance();
	aura->from_dict(data_as_dict(data));
	aura->set_owner(this);
	aura->resolve_references(this);

	aura_removec_expired(aura);
}

void Entity::aura_removec_dispelled_rpc(String data) {
	Ref<AuraData> aura;
	aura.instance();
	aura->from_dict(data_as_dict(data));
	aura->set_owner(this);
	aura->resolve_references(this);

	aura_removec_dispelled(aura);
}

void Entity::aura_refreshedc_rpc(String data) {
	Ref<AuraData> aura;
	aura.instance();
	aura->from_dict(data_as_dict(data));
	aura->set_owner(this);
	aura->resolve_references(this);

	aura_refreshedc(aura);
}

void Entity::aura_addc(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	_c_auras.push_back(aura);

	notification_caura(SpellEnums::NOTIFICATION_AURA_ADDED, aura);
}

void Entity::aura_removec(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	int aid = aura->get_aura_id();
	Entity *caster = aura->caster_get();

	Ref<AuraData> a;
	bool removed = false;
	for (int i = 0; i < _c_auras.size(); i++) {
		a = _c_auras.get(i);

		if (a->get_aura_id() == aid && a->caster_get() == caster) {
			_c_auras.remove(i);
			removed = true;
			break;
		}
	}

	if (removed) {
		notification_caura(SpellEnums::NOTIFICATION_AURA_REMOVED, aura);
	}
}

void Entity::aura_removec_exact(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	for (int i = 0; i < _c_auras.size(); i++) {
		if (_c_auras.get(i) == aura) {
			_c_auras.remove(i);
			break;
		}
	}

	notification_caura(SpellEnums::NOTIFICATION_AURA_REMOVED, aura);
}

void Entity::aura_removec_dispelled(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	for (int i = 0; i < _c_auras.size(); i++) {
		if (_c_auras.get(i) == aura) {
			_c_auras.remove(i);
			break;
		}
	}

	notification_caura(SpellEnums::NOTIFICATION_AURA_REMOVED, aura);
}

void Entity::aura_refreshedc(Ref<AuraData> aura) {
	//ERR_EXPLAIN("NYI");
	ERR_FAIL();

	ERR_FAIL_COND(!aura.is_valid());

	notification_caura(SpellEnums::NOTIFICATION_AURA_REFRESHED, aura);
}

void Entity::aura_removec_expired(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	for (int i = 0; i < _c_auras.size(); i++) {
		if (_c_auras.get(i) == aura) {
			_c_auras.remove(i);
			break;
		}
	}

	notification_caura(SpellEnums::NOTIFICATION_AURA_REMOVED, aura);
}

int Entity::aura_gets_count() {
	return _s_auras.size();
}

Ref<AuraData> Entity::aura_gets(int index) {
	ERR_FAIL_INDEX_V(index, _s_auras.size(), Ref<AuraData>(NULL));

	return Ref<AuraData>(_s_auras.get(index));
}

Ref<AuraData> Entity::aura_gets_by(Entity *caster, int aura_id) {
	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		if (ad->get_aura_id() == aura_id && ad->caster_get() == caster) {
			return ad;
		}
	}

	return Ref<AuraData>(NULL);
}
Ref<AuraData> Entity::aura_gets_by_bind(Node *caster, int aura_id) {
	if (!caster) {
		return Ref<AuraData>();
	}

	Entity *e = cast_to<Entity>(caster);

	if (!e) {
		return Ref<AuraData>();
	}

	return aura_gets_by(e, aura_id);
}

Ref<AuraData> Entity::aura_gets_with_group_by(Entity *caster, Ref<AuraGroup> aura_group) {
	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		if (ad->get_aura()->aura_get_aura_group() == aura_group && ad->caster_get() == caster) {
			return ad;
		}
	}

	return Ref<AuraData>();
}
Ref<AuraData> Entity::aura_gets_with_group_by_bind(Node *caster, Ref<AuraGroup> aura_group) {
	if (!INSTANCE_VALIDATE(caster)) {
		return Ref<AuraData>();
	}

	Entity *e = cast_to<Entity>(caster);

	if (!e) {
		return Ref<AuraData>();
	}

	return aura_gets_with_group_by(e, aura_group);
}

int Entity::aura_getc_count() {
	return _s_auras.size();
}

Ref<AuraData> Entity::aura_getc(int index) {
	ERR_FAIL_INDEX_V(index, _c_auras.size(), Ref<AuraData>(NULL));

	return Ref<AuraData>(_c_auras.get(index));
}

Vector<Variant> Entity::sauras_get() {
	VARIANT_ARRAY_GET(_s_auras);
}
void Entity::sauras_set(const Vector<Variant> &data) {
	VARIANT_ARRAY_SET(data, _s_auras, AuraData);
}

void Entity::moved() {
	if (has_method("_moved"))
		call("_moved");
}

void Entity::notification_cmouse_enter() {
	if (has_method("_notification_cmouse_enter"))
		call("_notification_cmouse_enter");

	emit_signal("notification_cmouse_entered");
}
void Entity::notification_cmouse_exit() {
	if (has_method("_notification_cmouse_exit"))
		call("_notification_cmouse_exit");

	emit_signal("notification_cmouse_exited");
}

void Entity::notification_ctargeted() {
	if (has_method("_notification_ctargeted"))
		call("_notification_ctargeted");

	emit_signal("notification_ctargeted");
}
void Entity::notification_cuntargeted() {
	if (has_method("_notification_cuntargeted"))
		call("_notification_cuntargeted");

	emit_signal("notification_cuntargeted");
}

void Entity::notification_caura(int what, Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	//NOTIFICATION_RES_IMPLC(notification_caura, "notification_caura", what, data);

	for (int i = 0; i < _c_auras.size(); ++i) {
		Ref<AuraData> ad = _c_auras.get(i);

		ad->get_aura()->notification_caura(what, data);
	}

	if (has_method("_notification_caura"))
		call("_notification_caura", what, data);

	emit_signal("notification_caura", what, data);
}
void Entity::notification_cheal(int what, Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	for (int i = 0; i < _c_auras.size(); ++i) {
		Ref<AuraData> ad = _c_auras.get(i);

		ad->get_aura()->notification_cheal(what, ad, info);
	}

	if (has_method("_notification_cheal"))
		call("_notification_cheal", info);

	//the current c health should probably be set here.
	emit_signal("notification_cheal", this, what, info);
}
void Entity::notification_ccast(int what, Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	info->get_spell()->notification_ccast(what, info);

	for (int i = 0; i < _c_auras.size(); ++i) {
		Ref<AuraData> ad = _c_auras.get(i);

		ad->get_aura()->notification_aura_ccast(what, ad, info);
	}

	if (has_method("_notification_ccast"))
		call("_notification_ccast", what, info);

	emit_signal("notification_ccast", what, info);
}
void Entity::notification_cdamage(int what, Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	for (int i = 0; i < _c_auras.size(); ++i) {
		Ref<AuraData> ad = _c_auras.get(i);

		ad->get_aura()->notification_cdamage(what, ad, info);
	}

	if (has_method("_notification_cdamage"))
		call("_notification_cdamage", what, info);

	//the current c health should probably be set here.
	emit_signal("notification_cdamage", this, what, info);
}

void Entity::notification_cdeath() {
	NOTIFICATION_IMPLCS(notification_cdeath, "diecd")
}

void Entity::notification_ccooldown_added(int id, float value) {
	NOTIFICATION_RES_IMPLC(notification_ccooldown_added, "ccooldown_added", id, value)
}
void Entity::notification_ccooldown_removed(int id, float value) {
	NOTIFICATION_RES_IMPLC(notification_ccooldown_removed, "ccooldown_removed", id, value)
}
void Entity::notification_ccategory_cooldown_added(int id, float value) {
	NOTIFICATION_RES_IMPLC(notification_ccategory_cooldown_added, "ccategory_cooldown_added", id, value)
}
void Entity::notification_ccategory_cooldown_removed(int id, float value) {
	NOTIFICATION_RES_IMPLC(notification_ccategory_cooldown_removed, "ccategory_cooldown_removed", id, value)
}

void Entity::notification_cxp_gained(int value) {
	NOTIFICATION_IMPLC(notification_cxp_gained, "notification_cxp_gained", value)
}

void Entity::notification_clevel_up(int value) {
	NOTIFICATION_IMPLC(notification_clevel_up, "notification_clevel_up", value)
}

void Entity::notification_centity_resource_added(Ref<EntityResource> resource) {
	NOTIFICATION_RES_IMPLC(notification_centity_resource_added, "centity_resource_added", resource)
}

void Entity::notification_centity_resource_removed(Ref<EntityResource> resource) {
	NOTIFICATION_RES_IMPLC(notification_centity_resource_removed, "centity_resource_removed", resource)
}

////    Casting System    ////

void Entity::cast_starts(Ref<SpellCastInfo> info) {
	_s_spell_cast_info = Ref<SpellCastInfo>(info);

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->notification_aura_scast(SpellEnums::NOTIFICATION_CAST_STARTED, ad, info);
	}

	_s_spell_cast_info->is_casting_set(true);

	notification_scast(SpellEnums::NOTIFICATION_CAST_STARTED, info);

	VRPCOBJ(cast_startc_rpc, JSON::print(info->to_dict()), cast_startc, info);
}

void Entity::cast_fails() {
	notification_scast(SpellEnums::NOTIFICATION_CAST_FAILED, _s_spell_cast_info);

	_s_spell_cast_info.unref();

	VRPC(cast_failc);
}

void Entity::cast_delays() {
	emit_signal("notification_scast", SpellEnums::NOTIFICATION_CAST_DELAYED, _s_spell_cast_info);

	VRPC(cast_delayc);
}

void Entity::cast_finishs() {
	_s_spell_cast_info->get_spell()->cast_finishs(_s_spell_cast_info);

	notification_scast(SpellEnums::NOTIFICATION_CAST_FINISHED, _s_spell_cast_info);

	_s_spell_cast_info.unref();

	VRPC(cast_finishc);
}

void Entity::cast_interrupts() {
	notification_scast(SpellEnums::NOTIFICATION_CAST_INTERRUPTED, _s_spell_cast_info);

	_s_spell_cast_info.unref();

	VRPC(cast_interruptc);
}

void Entity::cast_startc_rpc(String data) {
	Ref<SpellCastInfo> info;
	info.instance();
	info->from_dict(data_as_dict(data));
	info->resolve_references(this);

	cast_startc(info);
}

void Entity::cast_startc(Ref<SpellCastInfo> info) {
	_c_spell_cast_info = Ref<SpellCastInfo>(info);

	notification_ccast(SpellEnums::NOTIFICATION_CAST_STARTED, _c_spell_cast_info);
}

void Entity::cast_failc() {
	notification_ccast(SpellEnums::NOTIFICATION_CAST_FAILED, _c_spell_cast_info);

	_c_spell_cast_info.unref();
}

void Entity::cast_delayc() {
	//c_on_cast_

	notification_scast(SpellEnums::NOTIFICATION_CAST_DELAYED, _c_spell_cast_info);
}

void Entity::cast_finishc() {
	notification_ccast(SpellEnums::NOTIFICATION_CAST_FINISHED, _c_spell_cast_info);

	_c_spell_cast_info.unref();
}

void Entity::cast_interruptc() {
	notification_ccast(SpellEnums::NOTIFICATION_CAST_INTERRUPTED, _c_spell_cast_info);

	_c_spell_cast_info.unref();
}

void Entity::cast_spell_successs(Ref<SpellCastInfo> info) {
	notification_scast(SpellEnums::NOTIFICATION_CAST_SUCCESS, info);

	VRPCOBJ(cast_spell_successc_rpc, JSON::print(info->to_dict()), cast_spell_successc, info);
}

void Entity::cast_spell_successc_rpc(String data) {
	Ref<SpellCastInfo> info;
	info.instance();
	info->from_dict(data_as_dict(data));
	info->resolve_references(this);

	cast_spell_successc(info);
}

void Entity::cast_spell_successc(Ref<SpellCastInfo> info) {
	notification_ccast(SpellEnums::NOTIFICATION_CAST_SUCCESS, info);
}

////    Cooldowns    ////

bool Entity::cooldown_hass(int spell_id) {
	for (int i = 0; i < _s_cooldowns.size(); ++i) {
		if (_s_cooldowns[i].id == spell_id) {
			return true;
		}
	}

	return false;
}
void Entity::cooldown_adds(int spell_id, float value) {
	for (int i = 0; i < _s_cooldowns.size(); ++i) {
		if (_s_cooldowns[i].id == spell_id) {
			_s_cooldowns.write[i].cooldown = value;

			notification_scooldown_added(spell_id, value);

			ORPC(cooldown_addc, spell_id, value);

			return;
		}
	}

	Cooldown cd;
	cd.id = spell_id;
	cd.cooldown = value;

	_s_cooldowns.push_back(cd);

	notification_scooldown_added(spell_id, value);

	ORPC(cooldown_addc, spell_id, value);
}
void Entity::cooldown_removes(int spell_id) {
	for (int i = 0; i < _s_cooldowns.size(); ++i) {
		if (_s_cooldowns[i].id == spell_id) {
			float cd = _s_cooldowns[i].cooldown;

			_s_cooldowns.remove(i);

			notification_scooldown_removed(spell_id, cd);

			ORPC(cooldown_removec, spell_id);

			return;
		}
	}
}

float Entity::cooldown_gets(int spell_id) {
	for (int i = 0; i < _s_cooldowns.size(); ++i) {
		if (_s_cooldowns[i].id == spell_id) {
			return _s_cooldowns[i].cooldown;
		}
	}

	return 0;
}
float Entity::cooldown_gets_index(int index) {
	ERR_FAIL_INDEX_V(index, _s_cooldowns.size(), 0);

	return _s_cooldowns[index].cooldown;
}
int Entity::cooldown_gets_count() {
	return _s_cooldowns.size();
}

bool Entity::cooldown_hasc(int spell_id) {
	for (int i = 0; i < _c_cooldowns.size(); ++i) {
		if (_c_cooldowns[i].id == spell_id) {
			return true;
		}
	}

	return false;
}
void Entity::cooldown_addc(int spell_id, float value) {
	for (int i = 0; i < _c_cooldowns.size(); ++i) {
		if (_c_cooldowns[i].id == spell_id) {
			_c_cooldowns.write[i].cooldown = value;

			notification_ccooldown_added(spell_id, value);

			return;
		}
	}

	Cooldown cd;
	cd.id = spell_id;
	cd.cooldown = value;

	_c_cooldowns.push_back(cd);

	notification_ccooldown_added(spell_id, value);
}
void Entity::cooldown_removec(int spell_id) {
	for (int i = 0; i < _c_cooldowns.size(); ++i) {
		if (_c_cooldowns[i].id == spell_id) {
			float cd = _c_cooldowns[i].cooldown;

			_c_cooldowns.remove(i);

			notification_ccooldown_removed(spell_id, cd);

			return;
		}
	}
}
float Entity::cooldown_getc(int spell_id) {
	for (int i = 0; i < _c_cooldowns.size(); ++i) {
		if (_c_cooldowns[i].id == spell_id) {
			return _c_cooldowns[i].cooldown;
		}
	}

	return 0;
}
float Entity::cooldown_getc_index(int index) {
	ERR_FAIL_INDEX_V(index, _c_cooldowns.size(), 0);

	return _c_cooldowns[index].cooldown;
}
int Entity::cooldown_getc_count() {
	return _c_cooldowns.size();
}

Vector<Variant> Entity::scooldowns_get() {
	Vector<Variant> arr;
	arr.resize(_s_cooldowns.size() * 3);

	for (int i = 0; i < _s_cooldowns.size(); ++i) {
		int indx = i * 3;

		arr.write[indx] = _s_cooldowns[i].id;
		arr.write[indx + 1] = _s_cooldowns[i].cooldown;
		arr.write[indx + 2] = _s_cooldowns[i].path;
	}

	return arr;
}
void Entity::scooldowns_set(const Vector<Variant> &data) {
	ERR_FAIL_COND(data.size() % 3 != 0);

	_s_cooldowns.resize(data.size() / 3);

	for (int i = 0; i < _s_cooldowns.size(); ++i) {
		int indx = i * 3;

		_s_cooldowns.write[i].id = data[indx];
		_s_cooldowns.write[i].cooldown = data[indx + 1];
		_s_cooldowns.write[i].path = data[indx + 2];
	}
}

//Category Cooldowns

bool Entity::category_cooldown_hass(int category_id) {
	return (category_id & _s_active_category_cooldowns) > 0;
}
void Entity::category_cooldown_adds(int category_id, float value) {
	if ((category_id & _s_active_category_cooldowns)) {
		for (int i = 0; i < _s_category_cooldowns.size(); ++i) {
			if (_s_category_cooldowns[i].id == category_id) {
				_s_category_cooldowns.write[i].cooldown = value;

				notification_scategory_cooldown_added(category_id, value);

				ORPC(category_cooldown_addc, category_id, value);

				return;
			}
		}
	}

	Cooldown cd;
	cd.id = category_id;
	cd.cooldown = value;

	_s_active_category_cooldowns |= category_id;
	_s_category_cooldowns.push_back(cd);

	notification_scategory_cooldown_added(category_id, value);

	ORPC(category_cooldown_addc, category_id, value);
}
void Entity::category_cooldown_removes(int category_id) {
	Cooldown cc;
	bool found = false;

	for (int i = 0; i < _s_category_cooldowns.size(); ++i) {
		if (_s_category_cooldowns[i].id == category_id) {
			cc = _s_category_cooldowns.get(i);
			_s_category_cooldowns.remove(i);
			found = true;

			break;
		}
	}

	if (!found)
		return;

	_s_active_category_cooldowns ^= category_id;

	notification_scategory_cooldown_removed(cc.id, cc.cooldown);

	ORPC(category_cooldown_removec, category_id);
}
float Entity::category_cooldown_gets(int category_id) {
	ERR_FAIL_COND_V(!(category_id & _s_active_category_cooldowns), 0);

	for (int i = 0; i < _s_category_cooldowns.size(); ++i) {
		if (_s_category_cooldowns[i].id == category_id) {
			return _s_category_cooldowns[i].cooldown;
		}
	}

	return 0;
}
float Entity::category_cooldown_gets_index(int index) {
	ERR_FAIL_INDEX_V(index, _s_category_cooldowns.size(), 0);

	return _s_category_cooldowns.get(index).cooldown;
}
int Entity::category_cooldown_gets_count() {
	return _s_category_cooldowns.size();
}

bool Entity::category_cooldown_hasc(int category_id) {
	return (category_id & _c_active_category_cooldowns) > 0;
}
void Entity::category_cooldown_addc(int category_id, float value) {
	if ((category_id & _c_active_category_cooldowns)) {
		for (int i = 0; i < _c_category_cooldowns.size(); ++i) {
			if (_c_category_cooldowns[i].id == category_id) {
				_c_category_cooldowns.write[i].cooldown = value;

				notification_ccategory_cooldown_added(category_id, value);

				return;
			}
		}
	}

	Cooldown cd;
	cd.id = category_id;
	cd.cooldown = value;

	_c_category_cooldowns.push_back(cd);
	_c_active_category_cooldowns |= category_id;

	notification_ccategory_cooldown_added(category_id, value);
}
void Entity::category_cooldown_removec(int category_id) {
	Cooldown cc;
	bool found = false;

	for (int i = 0; i < _c_category_cooldowns.size(); ++i) {
		if (_c_category_cooldowns[i].id == category_id) {
			cc = _c_category_cooldowns.get(i);
			_c_category_cooldowns.remove(i);
			found = true;

			break;
		}
	}

	if (!found)
		return;

	_c_active_category_cooldowns ^= category_id;

	notification_ccategory_cooldown_removed(cc.id, cc.cooldown);
}
float Entity::category_cooldown_getc(int category_id) {
	ERR_FAIL_COND_V(!(category_id & _c_active_category_cooldowns), 0);

	for (int i = 0; i < _c_category_cooldowns.size(); ++i) {
		if (_c_category_cooldowns[i].id == category_id) {
			return _c_category_cooldowns[i].cooldown;
		}
	}

	return 0;
}
float Entity::category_cooldown_getc_index(int index) {
	ERR_FAIL_INDEX_V(index, _c_category_cooldowns.size(), 0);

	return _c_category_cooldowns[index].cooldown;
}
int Entity::category_cooldown_getc_count() {
	return _c_category_cooldowns.size();
}

Vector<Variant> Entity::scategory_cooldowns_get() {
	Vector<Variant> arr;
	arr.resize(_s_category_cooldowns.size() * 3);

	for (int i = 0; i < _s_category_cooldowns.size(); ++i) {
		int indx = i * 3;

		arr.write[indx] = _s_category_cooldowns[i].id;
		arr.write[indx + 1] = _s_category_cooldowns[i].cooldown;
		arr.write[indx + 2] = _s_category_cooldowns[i].path;
	}

	return arr;
}
void Entity::scategory_cooldowns_set(const Vector<Variant> &data) {
	ERR_FAIL_COND(data.size() % 3 != 0);

	_s_category_cooldowns.resize(data.size() / 3);

	for (int i = 0; i < _s_category_cooldowns.size(); ++i) {
		int indx = i * 3;

		_s_category_cooldowns.write[i].id = data[indx];
		_s_category_cooldowns.write[i].cooldown = data[indx + 1];
		_s_category_cooldowns.write[i].path = data[indx + 2];
	}
}

//Known Spells

int Entity::gets_free_spell_points() {
	return _s_free_spell_points;
}
void Entity::sets_free_spell_points(int value) {
	_s_free_spell_points = value;

	emit_signal("sfree_spell_points_changed", this, value);

	ORPC(setc_free_spell_points, value);
}

int Entity::getc_free_spell_points() {
	return _c_free_spell_points;
}
void Entity::setc_free_spell_points(int value) {
	_c_free_spell_points = value;

	emit_signal("cfree_spell_points_changed", this, value);
}

void Entity::spell_learn_requestc(int id) {
	spell_learns(id);
}
void Entity::spell_learns(int id) {
	//if (has_method("_spell_learns")) {
	call("_spell_learns", id);
	//	return;
	//	}
}

bool Entity::spell_hass(Ref<Spell> spell) {
	for (int i = 0; i < _s_spells.size(); ++i) {
		if (_s_spells.get(i) == spell) {
			return true;
		}
	}

	return false;
}
bool Entity::spell_hass_id(int id) {
	for (int i = 0; i < _s_spells.size(); ++i) {
		Ref<Spell> spell = _s_spells.get(i);

		if (!spell.is_valid())
			continue;

		if (spell->get_id() == id) {
			return true;
		}
	}

	return false;
}
void Entity::spell_adds(Ref<Spell> spell) {
	if (spell_hass(spell))
		return;

	//int id = spell->get_id();

	_s_spells.push_back(spell);

	if (ESS::get_singleton()->get_allow_class_spell_learning() && (_s_entity_player_type == EntityEnums::ENTITY_PLAYER_TYPE_PLAYER || gets_entity_player_type() == EntityEnums::ENTITY_PLAYER_TYPE_DISPLAY)) {
		Ref<ClassProfile> class_profile = ProfileManager::get_singleton()->getc_player_profile()->get_class_profile(_s_entity_data->get_path());

		if (class_profile->has_custom_data("spells")) {
			Vector<String> spells = class_profile->get_custom_data("spells");

			bool found = false;

			for (int i = 0; i < spells.size(); ++i) {
				if (spells[i] == spell->get_path()) {
					found = true;
					break;
				}
			}

			if (!found) {
				spells.push_back(spell->get_path());
				class_profile->set_custom_data("spells", spells);
			}

		} else {
			Vector<String> spells;
			spells.push_back(spell->get_path());
			class_profile->set_custom_data("spells", spells);
		}
	}

	emit_signal("sspell_added", this, spell);

	ORPCOBJ(spell_addc_rpc, spell->get_id(), spell_addc, spell);
}
void Entity::spell_adds_id(int id) {
	Ref<Spell> spell = ESS::get_singleton()->get_resource_db()->get_spell(id);

	ERR_FAIL_COND(!spell.is_valid());

	spell_adds(spell);
}
void Entity::spell_removes(Ref<Spell> spell) {
	for (int i = 0; i < _s_spells.size(); ++i) {
		if (_s_spells.get(i) == spell) {
			_s_spells.remove(i);
			break;
		}
	}

	emit_signal("sspell_removed", this, spell);

	ORPCOBJ(spell_removec_rpc, spell->get_id(), spell_removec, spell);
}
Ref<Spell> Entity::spell_gets(int index) {
	ERR_FAIL_INDEX_V(index, _s_spells.size(), Ref<Spell>());

	return _s_spells.get(index);
}
int Entity::spell_gets_count() {
	return _s_spells.size();
}

bool Entity::spell_hasc(Ref<Spell> spell) {
	for (int i = 0; i < _c_spells.size(); ++i) {
		if (_c_spells.get(i) == spell) {
			return true;
		}
	}

	return false;
}
bool Entity::spell_hasc_id(int id) {
	for (int i = 0; i < _c_spells.size(); ++i) {
		Ref<Spell> spell = _c_spells.get(i);

		if (!spell.is_valid())
			continue;

		if (spell->get_id() == id) {
			return true;
		}
	}

	return false;
}
void Entity::spell_addc(Ref<Spell> spell) {
	if (spell_hasc(spell))
		return;

	_c_spells.push_back(spell);

	emit_signal("cspell_added", this, spell);
}
void Entity::spell_removec(Ref<Spell> spell) {
	for (int i = 0; i < _c_spells.size(); ++i) {
		if (_c_spells.get(i) == spell) {
			_c_spells.remove(i);
			break;
		}
	}

	emit_signal("cspell_removed", this, spell);
}
Ref<Spell> Entity::spell_getc(int index) {
	ERR_FAIL_INDEX_V(index, _c_spells.size(), Ref<Spell>());

	return _c_spells.get(index);
}
int Entity::spell_getc_count() {
	return _c_spells.size();
}

void Entity::spell_addc_rpc(int id) {
	ERR_FAIL_COND(ESS::get_singleton() == NULL);

	spell_addc(ESS::get_singleton()->get_resource_db()->get_spell(id));
}
void Entity::spell_removec_rpc(int id) {
	ERR_FAIL_COND(ESS::get_singleton() == NULL);

	spell_removec(ESS::get_singleton()->get_resource_db()->get_spell(id));
}

Vector<Variant> Entity::sspells_get() {
	VARIANT_ARRAY_GET(_s_spells);
}
void Entity::sspells_set(const Vector<Variant> &data) {
	VARIANT_ARRAY_SET(data, _s_spells, Spell);
}

//Skills
bool Entity::skill_hass_id(int id) {
	for (int i = 0; i < _s_skills.size(); ++i) {
		Ref<EntitySkill> skill = _s_skills.get(i);

		ERR_CONTINUE(!skill.is_valid());

		if (skill->get_skill_id() == id) {
			return true;
		}
	}

	return false;
}
bool Entity::skill_hass(Ref<EntitySkill> skill) {
	for (int i = 0; i < _s_skills.size(); ++i) {
		if (_s_skills.get(i) == skill) {
			return true;
		}
	}

	return false;
}
void Entity::skill_adds(Ref<EntitySkill> skill) {
	if (skill_hass(skill))
		return;

	skill->CONNECT("current_changed", this, Entity, skill_scurrent_changed);
	skill->CONNECT("max_changed", this, Entity, skill_smax_changed);

	_s_skills.push_back(skill);

	emit_signal("sskill_added", this, skill);

	ORPC(skill_addc_id, skill->get_skill_id(), skill->get_current(), skill->get_max());
}
void Entity::skill_removes(Ref<EntitySkill> skill) {
	for (int i = 0; i < _s_skills.size(); ++i) {
		if (_s_skills.get(i) == skill) {
			_s_skills.remove(i);
			break;
		}
	}

	emit_signal("sskill_removed", this, skill);

	ORPC(skill_removec_id, skill->get_skill_id());
}
Ref<EntitySkill> Entity::skill_gets(int index) {
	ERR_FAIL_INDEX_V(index, _s_skills.size(), Ref<EntitySkill>());

	return _s_skills.get(index);
}
int Entity::skill_gets_count() {
	return _s_skills.size();
}

bool Entity::skill_hasc_id(int id) {
	for (int i = 0; i < _c_skills.size(); ++i) {
		Ref<EntitySkill> skill = _c_skills.get(i);

		ERR_CONTINUE(!skill.is_valid());

		if (skill->get_skill_id() == id) {
			return true;
		}
	}

	return false;
}
bool Entity::skill_hasc(Ref<EntitySkill> skill) {
	for (int i = 0; i < _c_skills.size(); ++i) {
		if (_c_skills.get(i) == skill) {
			return true;
		}
	}

	return false;
}
void Entity::skill_addc(Ref<EntitySkill> skill) {
	if (skill_hasc(skill))
		return;

	_c_skills.push_back(skill);

	emit_signal("cskill_added", this, skill);
}
void Entity::skill_removec(Ref<EntitySkill> skill) {
	for (int i = 0; i < _c_skills.size(); ++i) {
		if (_c_skills.get(i) == skill) {
			_c_skills.remove(i);
			break;
		}
	}

	emit_signal("cskill_removed", this, skill);
}
Ref<EntitySkill> Entity::skill_getc(int index) {
	ERR_FAIL_INDEX_V(index, _c_skills.size(), Ref<EntitySkill>());

	return _c_skills.get(index);
}
int Entity::skill_getc_count() {
	return _c_skills.size();
}

void Entity::skill_scurrent_changed(Ref<EntitySkill> skill) {
	//todo events

	ORPC(skill_changec, skill->get_skill_id(), skill->get_current());
}
void Entity::skill_smax_changed(Ref<EntitySkill> skill) {
	//todo events

	ORPC(skill_changec_max, skill->get_skill_id(), skill->get_max());
}

void Entity::skill_addc_id(int skill_id, int value, int max_value) {
	ERR_FAIL_COND(skill_hasc_id(skill_id));

	Ref<EntitySkill> skill;
	skill.instance();

	skill->set_skill_id(skill_id);
	skill->set_current(value);
	skill->set_max(max_value);

	skill_addc(skill);
}
void Entity::skill_removec_id(int skill_id) {
	for (int i = 0; i < _c_skills.size(); ++i) {
		Ref<EntitySkill> skill = _c_skills.get(i);

		ERR_CONTINUE(!skill.is_valid());

		if (skill->get_skill_id() == skill_id) {
			_c_skills.remove(i);

			emit_signal("cskill_removed", this, skill);

			return;
		}
	}
}
void Entity::skill_changec(int skill_id, int value) {
	for (int i = 0; i < _c_skills.size(); ++i) {
		Ref<EntitySkill> skill = _c_skills.get(i);

		ERR_CONTINUE(!skill.is_valid());

		if (skill->get_skill_id() == skill_id) {
			skill->set_current(value);

			emit_signal("cskill_changed", this, skill);

			return;
		}
	}
}
void Entity::skill_changec_max(int skill_id, int value) {
	for (int i = 0; i < _c_skills.size(); ++i) {
		Ref<EntitySkill> skill = _c_skills.get(i);

		ERR_CONTINUE(!skill.is_valid());

		if (skill->get_skill_id() == skill_id) {
			skill->set_max(value);

			emit_signal("cskill_changed", this, skill);

			return;
		}
	}
}

Vector<Variant> Entity::sskills_get() {
	VARIANT_ARRAY_GET(_s_skills);
}
void Entity::sskills_set(const Vector<Variant> &data) {
	VARIANT_ARRAY_SET(data, _s_skills, EntitySkill);
}

////    Casting System    ////

bool Entity::cast_is_castings() {
	return _s_spell_cast_info.is_valid();
}
bool Entity::cast_is_castingc() {
	return _c_spell_cast_info.is_valid();
}

Ref<SpellCastInfo> Entity::spell_gets_cast_info() {
	return Ref<SpellCastInfo>(_s_spell_cast_info);
}

void Entity::sets_spell_cast_info(Ref<SpellCastInfo> info) {
	_s_spell_cast_info = Ref<SpellCastInfo>(info);
}

Ref<SpellCastInfo> Entity::spell_getc_cast_info() {
	return Ref<SpellCastInfo>(_c_spell_cast_info);
}

void Entity::setc_spell_cast_info(Ref<SpellCastInfo> info) {
	_c_spell_cast_info = Ref<SpellCastInfo>(info);
}

void Entity::aura_removess_with_group(Ref<AuraGroup> aura_group) {
	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		if (ad->get_aura()->aura_get_aura_group() == aura_group) {
			aura_removec(ad);

			_s_auras.remove(i);

			emit_signal("saura_removed", ad);

			aura_removec(ad);

			i--;
		}
	}
}

void Entity::target_crequest_change(NodePath path) {
	RPCS(target_net_sets, path);
}

void Entity::target_net_sets(NodePath path) {
	if (!ISSERVER())
		return;

	Node *p_target = get_node_or_null(path);

	sets_target(p_target);

	if (p_target == NULL) {
		VRPC(target_net_setc, NodePath());
	} else {
		if (gets_target() == NULL) {
			VRPC(target_net_setc, NodePath());
		} else {
			VRPC(target_net_setc, gets_target()->get_path());
		}
	}
}
void Entity::target_net_setc(NodePath path) {
	Node *p_target = get_node_or_null(path);

	setc_target(p_target);
}

Entity *Entity::gets_target() {
	return _s_target;
}

void Entity::sets_target(Node *p_target) {
	Entity *original_target = _s_target;

	if (!INSTANCE_VALIDATE(original_target)) {
		original_target = NULL;
		_s_target = NULL;
	}

	if (p_target == NULL) {
		_s_target = NULL;

		if (has_method("_son_target_changed")) {
			call("_son_target_changed", this, original_target);
		}

		for (int i = 0; i < _s_resources.size(); ++i) {
			_s_resources.get(i)->ons_target_changed(this, original_target);
		}

		emit_signal("starget_changed", this, original_target);
		setc_target(p_target);
		return;
	}

	Entity *e = cast_to<Entity>(p_target);

	if (!e) {
		return;
	}

	_s_target = e;

	if (has_method("_son_target_changed")) {
		call("_son_target_changed", this, original_target);
	}

	for (int i = 0; i < _s_resources.size(); ++i) {
		_s_resources.get(i)->ons_target_changed(this, original_target);
	}

	emit_signal("starget_changed", this, original_target);

	if (is_inside_tree() && !get_tree()->has_network_peer()) {
		setc_target(p_target);
	}
}

Entity *Entity::getc_target() {
	return _c_target;
}
void Entity::setc_target(Node *p_target) {
	Entity *original_target = _c_target;

	if (!INSTANCE_VALIDATE(original_target)) {
		original_target = NULL;
		_c_target = NULL;
	}

	if (p_target == NULL) {
		_c_target = NULL;

		if (has_method("_con_target_changed")) {
			call("_con_target_changed", this, original_target);
		}

		for (int i = 0; i < _c_resources.size(); ++i) {
			_c_resources.get(i)->onc_target_changed(this, original_target);
		}

		emit_signal("ctarget_changed", this, original_target);

		return;
	}

	Entity *e = cast_to<Entity>(p_target);

	if (!e) {
		return;
	}

	_c_target = e;

	if (has_method("_con_target_changed")) {
		call("_con_target_changed", this, original_target);
	}

	for (int i = 0; i < _c_resources.size(); ++i) {
		_c_resources.get(i)->onc_target_changed(this, original_target);
	}

	emit_signal("ctarget_changed", this, original_target);
}

////    Class Talents    ////

int Entity::gets_free_class_talent_points() {
	return _s_free_class_talent_points;
}
void Entity::sets_free_class_talent_points(int value) {
	_s_free_class_talent_points = value;

	ORPC(setc_free_class_talent_points, value);
}

int Entity::getc_free_class_talent_points() {
	return _c_free_class_talent_points;
}
void Entity::setc_free_class_talent_points(int value) {
	_c_free_class_talent_points = value;
}

void Entity::class_talent_crequest_learn(int spec_index, int class_talent_row, int class_talent_culomn) {
	class_talent_sreceive_learn_request(spec_index, class_talent_row, class_talent_culomn);
}

void Entity::class_talent_sreceive_learn_request(int spec_index, int class_talent_row, int class_talent_culomn) {
	call("_class_talent_sreceive_learn_request", spec_index, class_talent_row, class_talent_culomn);
}

void Entity::_class_talent_sreceive_learn_request(int spec_index, int class_talent_row, int class_talent_culomn) {
	if (gets_free_class_talent_points() <= 0)
		return;

	ERR_FAIL_COND(!_s_entity_data.is_valid());

	Ref<EntityClassData> class_data = _s_entity_data->get_entity_class_data();

	ERR_FAIL_COND(!class_data.is_valid());

	Ref<CharacterSpec> spec = class_data->get_spec(spec_index);

	ERR_FAIL_COND(!spec.is_valid());

	for (int i = 0; i < spec->get_num_ranks(class_talent_row, class_talent_culomn); ++i) {
		Ref<Spell> class_talent = spec->get_talent(class_talent_row, class_talent_culomn, i);

		if (!class_talent.is_valid())
			return;

		int class_talent_id = class_talent->get_id();

		if (class_talent_hass(class_talent_id))
			continue;

		if (class_talent->aura_get_talent_required_talent().is_valid()) {
			if (!class_talent_hass(class_talent->aura_get_talent_required_talent()->get_id())) {
				return;
			}
		}

		if (class_talent->aura_get_talent_required_spell().is_valid()) {
			if (!spell_hass(class_talent->aura_get_talent_required_spell())) {
				return;
			}
		}

		if (i > 0) {
			Ref<Spell> pt = spec->get_talent(class_talent_row, class_talent_culomn, i - 1);

			for (int j = 0; j < aura_gets_count(); ++j) {
				Ref<AuraData> ad = aura_gets(j);

				if (ad->get_aura_id() == pt->get_id()) {
					aura_removes(ad);

					break;
				}
			}
		}

		Ref<AuraApplyInfo> info;
		info.instance();

		info->caster_set(this);
		info->target_set(this);
		info->spell_scale_set(1);
		info->set_aura(class_talent);

		class_talent->aura_sapply(info);

		class_talent_adds(class_talent_id);

		sets_free_class_talent_points(gets_free_class_talent_points() - 1);

		return;
	}
}

void Entity::class_talent_crequest_reset() {
	class_talent_sreceive_reset_request();
}
void Entity::class_talent_sreceive_reset_request() {
	call("_class_talent_sreceive_reset_request");
}
void Entity::_class_talent_sreceive_reset_request() {
	class_talent_sreset();
}

void Entity::class_talent_sreset() {
	_s_class_talents.clear();

	if (has_method("_son_class_talent_reset"))
		call("_son_class_talent_reset", this);

	emit_signal("sclass_talent_reset", this);

	ORPC(class_talent_creset);
}
void Entity::class_talent_creset() {
	_c_class_talents.clear();

	if (has_method("_con_class_talent_reset"))
		call("_con_class_talent_reset", this);

	emit_signal("cclass_talent_reset", this);
}

void Entity::class_talent_adds(int class_talent) {
	if (class_talent_hass(class_talent))
		return;

	_s_class_talents.push_back(class_talent);

	if (has_method("_son_class_talent_learned"))
		call("_son_class_talent_learned", class_talent);

	emit_signal("sclass_talent_learned", this, class_talent);

	ORPC(class_talent_addc, class_talent);
}
void Entity::class_talent_removes(int class_talent) {
	for (int i = 0; i < _s_class_talents.size(); ++i) {
		if (_s_class_talents[i] == class_talent) {
			_s_class_talents.remove(i);

			for (int j = 0; j < aura_gets_count(); ++j) {
				Ref<AuraData> ad = aura_gets(j);

				if (ad->get_aura_id() == class_talent) {
					aura_removes(ad);

					break;
				}
			}

			break;
		}
	}

	ORPC(class_talent_removec, class_talent);
}
bool Entity::class_talent_hass(int class_talent) {
	for (int i = 0; i < _s_class_talents.size(); ++i) {
		if (_s_class_talents[i] == class_talent) {
			return true;
		}
	}

	return false;
}
int Entity::class_talent_gets(int index) {
	ERR_FAIL_INDEX_V(index, _s_class_talents.size(), 0);

	return _s_class_talents.get(index);
}
int Entity::class_talent_gets_count() {
	return _s_class_talents.size();
}
void Entity::class_talents_sclear() {
	_s_class_talents.clear();

	ORPC(class_talent_cclear);
}

void Entity::class_talent_addc(int class_talent) {
	if (class_talent_hasc(class_talent))
		return;

	_c_class_talents.push_back(class_talent);

	if (has_method("_con_class_talent_learned"))
		call("_con_class_talent_learned", class_talent);

	emit_signal("cclass_talent_learned", this, class_talent);
}
void Entity::class_talent_removec(int class_talent) {
	for (int i = 0; i < _c_class_talents.size(); ++i) {
		if (_c_class_talents[i] == class_talent) {
			_c_class_talents.remove(i);
			return;
		}
	}
}
bool Entity::class_talent_hasc(int class_talent) {
	for (int i = 0; i < _c_class_talents.size(); ++i) {
		if (_c_class_talents[i] == class_talent) {
			return true;
		}
	}

	return false;
}
int Entity::class_talent_getc(int index) {
	ERR_FAIL_INDEX_V(index, _c_class_talents.size(), 0);

	return _c_class_talents.get(index);
}
int Entity::class_talent_getc_count() {
	return _c_class_talents.size();
}
void Entity::class_talent_cclear() {
	_c_class_talents.clear();
}

PoolIntArray Entity::sclass_talents_get() {
	PoolIntArray arr;
	arr.resize(_s_class_talents.size());

#if !GODOT4
	PoolIntArray::Write w = arr.write();
#endif

	for (int i = 0; i < _s_class_talents.size(); ++i) {
#if !GODOT4
		w[i] = _s_class_talents[i];
#else
		arr.write[i] = _s_class_talents[i];
#endif
	}

	return arr;
}
void Entity::sclass_talents_set(const PoolIntArray &data) {
	_s_class_talents.resize(data.size());

	for (int i = 0; i < _s_class_talents.size(); ++i) {
		_s_class_talents.write[i] = data[i];
	}
}

////    Character Talents    ////

int Entity::gets_free_character_talent_points() {
	return _s_free_character_talent_points;
}
void Entity::sets_free_character_talent_points(int value) {
	_s_free_character_talent_points = value;

	ORPC(setc_free_character_talent_points, value);
}

int Entity::getc_free_character_talent_points() {
	return _c_free_character_talent_points;
}
void Entity::setc_free_character_talent_points(int value) {
	_c_free_character_talent_points = value;
}

void Entity::character_talent_crequest_learn(int spec_index, int character_talent_row, int character_talent_culomn) {
	character_talent_sreceive_learn_request(spec_index, character_talent_row, character_talent_culomn);
}

void Entity::character_talent_sreceive_learn_request(int spec_index, int character_talent_row, int character_talent_culomn) {
	call("_character_talent_sreceive_learn_request", spec_index, character_talent_row, character_talent_culomn);
}

void Entity::_character_talent_sreceive_learn_request(int spec_index, int character_talent_row, int character_talent_culomn) {
	if (gets_free_character_talent_points() <= 0)
		return;

	ERR_FAIL_COND(!_s_entity_data.is_valid());

	Ref<EntityClassData> class_data = _s_entity_data->get_entity_class_data();

	ERR_FAIL_COND(!class_data.is_valid());

	Ref<CharacterSpec> spec = class_data->get_spec(spec_index);

	ERR_FAIL_COND(!spec.is_valid());

	for (int i = 0; i < spec->get_num_ranks(character_talent_row, character_talent_culomn); ++i) {
		Ref<Spell> character_talent = spec->get_talent(character_talent_row, character_talent_culomn, i);

		if (!character_talent.is_valid())
			return;

		int character_talent_id = character_talent->get_id();

		if (character_talent_hass(character_talent_id))
			continue;

		if (character_talent->aura_get_talent_required_talent().is_valid()) {
			if (!character_talent_hass(character_talent->aura_get_talent_required_talent()->get_id())) {
				return;
			}
		}

		if (character_talent->aura_get_talent_required_spell().is_valid()) {
			if (!spell_hass(character_talent->aura_get_talent_required_spell())) {
				return;
			}
		}

		if (i > 0) {
			Ref<Spell> pt = spec->get_talent(character_talent_row, character_talent_culomn, i - 1);

			for (int j = 0; j < aura_gets_count(); ++j) {
				Ref<AuraData> ad = aura_gets(j);

				if (ad->get_aura_id() == pt->get_id()) {
					aura_removes(ad);

					break;
				}
			}
		}

		Ref<AuraApplyInfo> info;
		info.instance();

		info->caster_set(this);
		info->target_set(this);
		info->spell_scale_set(1);
		info->set_aura(character_talent);

		character_talent->aura_sapply(info);

		character_talent_adds(character_talent_id);

		sets_free_character_talent_points(gets_free_character_talent_points() - 1);

		return;
	}
}

void Entity::character_talent_crequest_reset() {
	character_talent_sreceive_reset_request();
}
void Entity::character_talent_sreceive_reset_request() {
	call("_character_talent_sreceive_reset_request");
}
void Entity::_character_talent_sreceive_reset_request() {
	character_talent_sreset();
}

void Entity::character_talent_sreset() {
	_s_character_talents.clear();

	if (has_method("_son_character_talent_reset"))
		call("_son_character_talent_reset", this);

	emit_signal("scharacter_talent_reset", this);

	ORPC(character_talent_creset);
}
void Entity::character_talent_creset() {
	_c_character_talents.clear();

	if (has_method("_con_character_talent_reset"))
		call("_con_character_talent_reset", this);

	emit_signal("ccharacter_talent_reset", this);
}

void Entity::character_talent_adds(int character_talent) {
	if (character_talent_hass(character_talent))
		return;

	_s_character_talents.push_back(character_talent);

	if (has_method("_son_character_talent_learned"))
		call("_son_character_talent_learned", character_talent);

	emit_signal("scharacter_talent_learned", this, character_talent);

	ORPC(character_talent_addc, character_talent);
}
void Entity::character_talent_removes(int character_talent) {
	for (int i = 0; i < _s_character_talents.size(); ++i) {
		if (_s_character_talents[i] == character_talent) {
			_s_character_talents.remove(i);

			for (int j = 0; j < aura_gets_count(); ++j) {
				Ref<AuraData> ad = aura_gets(j);

				if (ad->get_aura_id() == character_talent) {
					aura_removes(ad);

					break;
				}
			}

			break;
		}
	}

	ORPC(character_talent_removec, character_talent);
}
bool Entity::character_talent_hass(int character_talent) {
	for (int i = 0; i < _s_character_talents.size(); ++i) {
		if (_s_character_talents[i] == character_talent) {
			return true;
		}
	}

	return false;
}
int Entity::character_talent_gets(int index) {
	ERR_FAIL_INDEX_V(index, _s_character_talents.size(), 0);

	return _s_character_talents.get(index);
}
int Entity::character_talent_gets_count() {
	return _s_character_talents.size();
}
void Entity::character_talents_sclear() {
	_s_character_talents.clear();

	ORPC(character_talent_cclear);
}

void Entity::character_talent_addc(int character_talent) {
	if (character_talent_hasc(character_talent))
		return;

	_c_character_talents.push_back(character_talent);

	if (has_method("_con_character_talent_learned"))
		call("_con_character_talent_learned", character_talent);

	emit_signal("ccharacter_talent_learned", this, character_talent);
}
void Entity::character_talent_removec(int character_talent) {
	for (int i = 0; i < _c_character_talents.size(); ++i) {
		if (_c_character_talents[i] == character_talent) {
			_c_character_talents.remove(i);
			return;
		}
	}
}
bool Entity::character_talent_hasc(int character_talent) {
	for (int i = 0; i < _c_character_talents.size(); ++i) {
		if (_c_character_talents[i] == character_talent) {
			return true;
		}
	}

	return false;
}
int Entity::character_talent_getc(int index) {
	ERR_FAIL_INDEX_V(index, _c_character_talents.size(), 0);

	return _c_character_talents.get(index);
}
int Entity::character_talent_getc_count() {
	return _c_character_talents.size();
}
void Entity::character_talent_cclear() {
	_c_character_talents.clear();
}

PoolIntArray Entity::scharacter_talents_get() {
	PoolIntArray arr;
	arr.resize(_s_character_talents.size());

#if !GODOT4
	PoolIntArray::Write w = arr.write();
#endif

	for (int i = 0; i < _s_character_talents.size(); ++i) {
#if !GODOT4
		w[i] = _s_character_talents[i];
#else
		arr.write[i] = _s_character_talents[i];
#endif
	}

	return arr;
}
void Entity::scharacter_talents_set(const PoolIntArray &data) {
	_s_character_talents.resize(data.size());

	for (int i = 0; i < _s_character_talents.size(); ++i) {
		_s_character_talents.write[i] = data[i];
	}
}

////    Bag    ////

Ref<Bag> Entity::gets_bag() const {
	return _s_bag;
}
void Entity::sets_bag(const Ref<Bag> bag) {
	if (_s_bag.is_valid()) {
		_s_bag->DISCONNECT("item_added", this, Entity, notification_item_sadded);
		_s_bag->DISCONNECT("item_removed", this, Entity, notification_item_sremoved);
		_s_bag->DISCONNECT("item_swapped", this, Entity, notification_items_sswapped);
		_s_bag->DISCONNECT("item_count_changed", this, Entity, notification_item_sscount_changed);
		_s_bag->DISCONNECT("overburdened", this, Entity, notification_soverburdened);
		_s_bag->DISCONNECT("overburden_removed", this, Entity, notification_soverburden_removed);
	}

	_s_bag = bag;

	if (_s_bag.is_valid()) {
		_s_bag->CONNECT("item_added", this, Entity, notification_item_sadded);
		_s_bag->CONNECT("item_removed", this, Entity, notification_item_sremoved);
		_s_bag->CONNECT("item_swapped", this, Entity, notification_items_sswapped);
		_s_bag->CONNECT("item_count_changed", this, Entity, notification_item_sscount_changed);
		_s_bag->CONNECT("overburdened", this, Entity, notification_soverburdened);
		_s_bag->CONNECT("overburden_removed", this, Entity, notification_soverburden_removed);
	}

	emit_signal("sbag_changed", this, _s_bag);

	if (_s_bag.is_valid()) {
		ORPC(setc_bag_rpc, JSON::print(_s_bag->to_dict()));
	} else {
		ORPC(setc_bag_rpc, "");
	}
}

Ref<Bag> Entity::getc_bag() const {
	return _c_bag;
}
void Entity::setc_bag(const Ref<Bag> bag) {
	_c_bag = bag;

	emit_signal("cbag_changed", this, _c_bag);
}

Ref<Bag> Entity::gets_target_bag() const {
	return _s_target_bag;
}
void Entity::sets_target_bag(const Ref<Bag> bag) {
	if (_s_target_bag.is_valid()) {
		_s_target_bag->DISCONNECT("item_added", this, Entity, notification_target_item_sadded);
		_s_target_bag->DISCONNECT("item_removed", this, Entity, notification_target_item_sremoved);
		_s_target_bag->DISCONNECT("item_swapped", this, Entity, notification_target_items_sswapped);
		_s_target_bag->DISCONNECT("item_count_changed", this, Entity, notification_target_item_sscount_changed);
	}

	_s_target_bag = bag;

	if (_s_target_bag.is_valid()) {
		_s_target_bag->CONNECT("item_added", this, Entity, notification_target_item_sadded);
		_s_target_bag->CONNECT("item_removed", this, Entity, notification_target_item_sremoved);
		_s_target_bag->CONNECT("item_swapped", this, Entity, notification_target_items_sswapped);
		_s_target_bag->CONNECT("item_count_changed", this, Entity, notification_target_item_sscount_changed);
	}

	emit_signal("starget_bag_changed", this, _s_target_bag);

	if (_s_target_bag.is_valid()) {
		ORPC(setc_target_bag_rpc, JSON::print(_s_target_bag->to_dict()));
	} else {
		ORPC(setc_target_bag_rpc, "");
	}
}

Ref<Bag> Entity::getc_target_bag() const {
	return _c_target_bag;
}
void Entity::setc_target_bag(const Ref<Bag> bag) {
	_c_target_bag = bag;

	emit_signal("ctarget_bag_changed", this, _s_target_bag);
}

void Entity::setc_bag_rpc(String data) {
	Ref<Bag> bag;
	bag.instance();
	bag->from_dict(data_as_dict(data));

	setc_bag(bag);
}
void Entity::setc_target_bag_rpc(String data) {
	Ref<Bag> bag;
	bag.instance();
	bag->from_dict(data_as_dict(data));

	setc_target_bag(bag);
}

void Entity::loot_crequest(int index) {
	RPCS(loots, index);
}
void Entity::loots(int index) {
	ERR_FAIL_COND(!_s_bag.is_valid());
	ERR_FAIL_COND(!_s_target_bag.is_valid());

	Ref<ItemInstance> ii = _s_target_bag->get_item(index);

	if (_s_bag->can_add_item(ii)) {
		_s_target_bag->remove_item(index);
		_s_bag->add_item(ii);
	}
}
void Entity::lootc(int index) {
	ERR_FAIL_COND(!_c_target_bag.is_valid());

	_c_target_bag->remove_item(index);
}

void Entity::notification_item_sadded(Ref<Bag> bag, Ref<ItemInstance> item, int slot_id) {
	ORPCOBJP(item_addc_rpc, slot_id, JSON::print(item->to_dict()), item_addc, slot_id, item);
}
void Entity::item_addc_rpc(int slot_id, String item_data) {
	Ref<ItemInstance> ii;
	ii.instance();
	ii->from_dict(data_as_dict(item_data));

	item_addc(slot_id, ii);
}
void Entity::item_addc(int slot_id, Ref<ItemInstance> item) {
	ERR_FAIL_COND(!_c_bag.is_valid());

	_c_bag->add_item_at(slot_id, item);
}
void Entity::notification_item_sremoved(Ref<Bag> bag, Ref<ItemInstance> item, int slot_id) {
	ORPC(item_removec, slot_id);
}
void Entity::item_removes(const int slot_id) {
	ERR_FAIL_COND(!_s_bag.is_valid());

	_s_bag->remove_item(slot_id);
}
void Entity::item_removec(const int slot_id) {
	ERR_FAIL_COND(!_c_bag.is_valid());

	_c_bag->remove_item(slot_id);
}
void Entity::item_cdeny_remove(const int slot_id) {
}
void Entity::item_crequest_remove(const int slot_id) {
	RPCS(item_removes, slot_id);
}

void Entity::notification_items_sswapped(Ref<Bag> bag, int slot_id_1, int slot_id_2) {
	ORPC(items_swapc, slot_id_1, slot_id_2);
}
void Entity::items_swaps(int slot_id_1, int slot_id_2) {
	ERR_FAIL_COND(!_s_bag.is_valid());

	_s_bag->swap_items(slot_id_1, slot_id_2);
}
void Entity::items_swapc(int slot_id_1, int slot_id_2) {
	ERR_FAIL_COND(!_c_bag.is_valid());

	_c_bag->swap_items(slot_id_1, slot_id_2);
}
void Entity::item_cdeny_swap(int slot_id_1, int slot_id_2) {
}
void Entity::item_crequest_swap(int slot_id_1, int slot_id_2) {
	RPCS(items_swaps, slot_id_1, slot_id_2);
}

void Entity::notification_item_sscount_changed(Ref<Bag> bag, Ref<ItemInstance> item, int slot_id) {
	ERR_FAIL_COND(!item.is_valid());

	ORPC(item_cchange_count, slot_id, item->get_stack_size());
}
void Entity::item_cchange_count(int slot_id, int new_count) {
	ERR_FAIL_COND(!_c_bag.is_valid());

	_c_bag->set_item_count(slot_id, new_count);
}

void Entity::notification_soverburdened(Ref<Bag> bag) {
}
void Entity::notification_soverburden_removed(Ref<Bag> bag) {
}

//Target Bag

void Entity::notification_target_item_sadded(Ref<Bag> bag, Ref<ItemInstance> item, int slot_id) {
	ORPCOBJP(target_item_addc_rpc, slot_id, JSON::print(item->to_dict()), target_item_addc, slot_id, item);
}
void Entity::target_item_addc_rpc(int slot_id, String item_data) {
	Ref<ItemInstance> ii;
	ii.instance();
	ii->from_dict(data_as_dict(item_data));

	target_item_addc(slot_id, ii);
}
void Entity::target_item_addc(int slot_id, Ref<ItemInstance> item) {
	ERR_FAIL_COND(!_c_target_bag.is_valid());

	_c_target_bag->add_item_at(slot_id, item);
}

void Entity::notification_target_item_sremoved(Ref<Bag> bag, Ref<ItemInstance> item, int slot_id) {
	ORPC(target_item_removec, slot_id);
}
void Entity::target_item_removes(const int slot_id) {
	ERR_FAIL_COND(!_s_target_bag.is_valid());

	_s_target_bag->remove_item(slot_id);
}
void Entity::target_item_removec(const int slot_id) {
	ERR_FAIL_COND(!_c_target_bag.is_valid());

	_c_target_bag->remove_item(slot_id);
}
void Entity::target_item_cdeny_remove(const int slot_id) {
}
void Entity::target_remove_crequest_item(const int slot_id) {
	RPCS(target_item_removes, slot_id);
}

void Entity::notification_target_items_sswapped(Ref<Bag> bag, int slot_id_1, int slot_id_2) {
	ORPC(target_items_cswap, slot_id_1, slot_id_2);
}
void Entity::target_items_sswap(int slot_id_1, int slot_id_2) {
	ERR_FAIL_COND(!_s_target_bag.is_valid());

	_s_target_bag->swap_items(slot_id_1, slot_id_2);
}
void Entity::target_items_cswap(int slot_id_1, int slot_id_2) {
	ERR_FAIL_COND(!_c_target_bag.is_valid());

	_c_target_bag->swap_items(slot_id_1, slot_id_2);
}
void Entity::target_item_cdeny_swap(int slot_id_1, int slot_id_2) {
}
void Entity::target_item_crequest_swap(int slot_id_1, int slot_id_2) {
	RPCS(target_items_sswap, slot_id_1, slot_id_2);
}

void Entity::notification_target_item_sscount_changed(Ref<Bag> bag, Ref<ItemInstance> item, int slot_id) {
	ERR_FAIL_COND(!item.is_valid());

	ORPC(target_item_cchange_count, slot_id, item->get_stack_size());
}
void Entity::target_item_cchange_count(int slot_id, int new_count) {
	ERR_FAIL_COND(!_c_target_bag.is_valid());

	Ref<ItemInstance> ii = _c_target_bag->get_item(slot_id);

	ERR_FAIL_COND(!ii.is_valid());

	ii->set_stack_size(new_count);
}

//Vendors
void Entity::vendor_item_buy_crequest(const int index, const int count) {
	RPCS(vendor_item_sbuy, index, count);
}
void Entity::vendor_item_sbuy(const int index, const int count) {
	call("_vendor_item_sbuy", index, count);
}
void Entity::vendor_item_sell_crequest(const int slot_id) {
	RPCS(vendor_item_ssell, slot_id);
}
void Entity::vendor_item_ssell(const int slot_id) {
	call("_vendor_item_ssell", slot_id);
}

////    DATA    ////
void Entity::data_adds(Ref<EntityDataContainer> data) {
	_s_data.push_back(data);
}
void Entity::data_removes(int index) {
	ERR_FAIL_INDEX(index, _s_data.size());

	_s_data.remove(index);
}
Ref<EntityDataContainer> Entity::data_gets(int index) {
	ERR_FAIL_INDEX_V(index, _s_data.size(), Ref<EntityDataContainer>());

	return _s_data.get(index);
}
int Entity::data_gets_count() {
	return _s_data.size();
}

void Entity::data_addc(Ref<EntityDataContainer> data) {
	_c_data.push_back(data);
}
void Entity::data_removec(int index) {
	ERR_FAIL_INDEX(index, _c_data.size());

	_c_data.remove(index);
}
Ref<EntityDataContainer> Entity::data_getc(int index) {
	ERR_FAIL_INDEX_V(index, _c_data.size(), Ref<EntityDataContainer>());

	return _c_data.get(index);
}
int Entity::data_getc_count() {
	return _c_data.size();
}

Vector<Variant> Entity::sdatas_get() {
	VARIANT_ARRAY_GET(_s_data);
}
void Entity::sdatas_set(const Vector<Variant> &data) {
	VARIANT_ARRAY_SET(data, _s_data, EntityDataContainer);
}

////    Actionbars    ////

bool Entity::get_actionbar_locked() {
	return _actionbar_locked;
}
void Entity::set_actionbar_locked(bool value) {
	_actionbar_locked = value;
}

Ref<ActionBarProfile> Entity::get_action_bar_profile() {
	if (_action_bar_profile.is_valid())
		return _action_bar_profile;

	_action_bar_profile.instance();

	Ref<ClassProfile> cp = ProfileManager::get_singleton()->getc_player_profile()->get_class_profile(gets_entity_data()->get_path());

	if (cp.is_valid()) {
		set_actionbar_locked(cp->get_actionbar_locked());
		Ref<ActionBarProfile> p = cp->get_default_action_bar_profile();

		if (p.is_valid())
			_action_bar_profile->from_actionbar_profile(p);
	}

	return _action_bar_profile;
}

void Entity::loaded() {
	//sendstate = true;
}

////    PlayerData    ////

bool Entity::get_maunal_process() const {
	return _maunal_process;
}
void Entity::set_maunal_process(const bool value) {
	_maunal_process = value;
}

void Entity::update(float delta) {
	if (_s_gcd > 0.0000001) {
		_s_gcd -= delta;

		if (_s_gcd <= 0) {
			_s_gcd = 0;

			notification_sgcd_finished();
		}
	}

	if (_c_gcd > 0.0000001) {
		_c_gcd -= delta;

		if (_c_gcd <= 0) {
			_c_gcd = 0;

			notification_cgcd_finished();
		}
	}

	for (int i = 0; i < _c_cooldowns.size(); ++i) {
		_c_cooldowns.write[i].cooldown -= delta;
	}

	for (int i = 0; i < _c_category_cooldowns.size(); ++i) {
		_c_category_cooldowns.write[i].cooldown -= delta;
	}

	for (int i = 0; i < _s_cooldowns.size(); ++i) {
		float cd = _s_cooldowns[i].cooldown;

		cd -= delta;

		_s_cooldowns.write[i].cooldown = cd;

		if (cd <= 0) {
			cooldown_removes(_s_cooldowns[i].id);
			--i;
		}
	}

	for (int i = 0; i < _s_category_cooldowns.size(); ++i) {
		float cd = _s_category_cooldowns[i].cooldown;

		cd -= delta;

		_s_category_cooldowns.write[i].cooldown = cd;

		if (cd <= 0) {
			category_cooldown_removes(_s_category_cooldowns[i].id);
			--i;
		}
	}

	update_auras(delta);

	if (ISSERVER()) {
		if (_s_spell_cast_info.is_valid() && _s_spell_cast_info->is_casting_get()) {
			if (_s_spell_cast_info->update_cast_time(delta)) {
				cast_finishs();
			}
		}

		for (int i = 0; i < ESS::get_singleton()->stat_get_count(); ++i) {
			if (stat_get_dirty(i)) {
				ssend_stat(i, stat_gets_current(i));

				stat_set_dirty(i, false);
			}
		}

		if (_s_entity_controller == EntityEnums::ENITIY_CONTROLLER_AI && _s_ai.is_valid() && _s_ai->get_enabled()) {
			if (_s_pet_owner)
				_s_ai->pet_update(delta);
			else
				_s_ai->update(delta);
		}

		for (int i = 0; i < _s_resources.size(); ++i) {
			Ref<EntityResource> res = _s_resources.get(i);

			ERR_CONTINUE(!res.is_valid());

			if (res->get_should_process())
				res->process_server(delta);

			if (res->get_dirty()) {
				resource_sends_curr_max(i, res->get_current_value(), res->get_max_value());
				res->set_dirty(false);
			}
		}
	}

	if (ISCLIENT()) {
		if (_c_spell_cast_info.is_valid() && _c_spell_cast_info->is_casting_get()) {
			_c_spell_cast_info->update_cast_time(delta);
		}

		for (int i = 0; i < _c_resources.size(); ++i) {
			Ref<EntityResource> res = _c_resources.get(i);

			ERR_CONTINUE(!res.is_valid());

			if (res->get_should_process())
				res->process_client(delta);
		}
	}
}

String Entity::random_name() {
	return "";
}

//Networking

Entity *Entity::sees_gets(int index) {
	ERR_FAIL_INDEX_V(index, _s_sees.size(), NULL);

	return _s_sees.get(index);
}
void Entity::sees_removes_index(int index) {
	Entity *e = _s_sees.get(index);

	if (unlikely(!INSTANCE_VALIDATE(e))) {
		_s_sees.remove(index);
		return;
	}

	e->seen_by_removes(this);

	_s_sees.remove(index);
}
void Entity::sees_removes(Entity *entity) {
	if (unlikely(!INSTANCE_VALIDATE(entity))) {
		_s_sees.erase(entity);
		return;
	}

	entity->seen_by_removes(this);

	_s_sees.erase(entity);
}
void Entity::sees_removes_bind(Node *entity) {
	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(!e);

	sees_removes(e);
}
void Entity::sees_adds(Entity *entity) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(entity));

	entity->seen_by_adds(this);

	for (int i = 0; i < _s_sees.size(); ++i) {
		if (_s_sees.get(i) == entity)
			return;
	}

	_s_sees.push_back(entity);
}
void Entity::sees_adds_bind(Node *entity) {
	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(!e);

	sees_adds(e);
}
int Entity::sees_gets_count() {
	return _s_sees.size();
}

Entity *Entity::seen_by_gets(int index) {
	ERR_FAIL_INDEX_V(index, _s_seen_by.size(), NULL);

	return _s_seen_by.get(index);
}
void Entity::seen_by_removes_index(int index) {
	_s_seen_by.remove(index);
}
void Entity::seen_by_removes(Entity *entity) {
	_s_seen_by.erase(entity);
}
void Entity::seen_by_removes_bind(Node *entity) {
	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(!e);

	seen_by_removes(e);
}
void Entity::seen_by_adds(Entity *entity) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(entity));

	for (int i = 0; i < _s_seen_by.size(); ++i) {
		if (_s_seen_by.get(i) == entity)
			return;
	}

	_s_seen_by.push_back(entity);
}
void Entity::seen_by_adds_bind(Node *entity) {
	Entity *e = Object::cast_to<Entity>(entity);

	ERR_FAIL_COND(!e);

	seen_by_adds(e);
}

int Entity::seen_by_gets_count() {
	return _s_seen_by.size();
}

void Entity::vrpc(const StringName &p_method, VARIANT_ARG_DECLARE) {
	VARIANT_ARGPTRS;

	int argc = 0;
	for (int i = 0; i < VARIANT_ARG_MAX; i++) {
		if (argptr[i]->get_type() == Variant::NIL)
			break;
		argc++;
	}

	for (int i = 0; i < _s_seen_by.size(); ++i) {
		Entity *e = _s_seen_by.get(i);

		if (unlikely(!INSTANCE_VALIDATE(e))) {
			_s_seen_by.remove(i);
			--i;
			continue;
		}

		int netm = e->get_network_master();

		if (netm != 1)
			rpcp(netm, false, p_method, argptr, argc);
	}

	if (get_network_master() != 1)
		rpcp(get_network_master(), false, p_method, argptr, argc);
}

#if VERSION_MAJOR < 4
Variant Entity::_vrpc_bind(const Variant **p_args, int p_argcount, Variant::CallError &r_error) {
#else
Variant Entity::_vrpc_bind(const Variant **p_args, int p_argcount, Callable::CallError &r_error) {
#endif
	if (p_argcount < 1) {
#if VERSION_MAJOR < 4
		r_error.error = Variant::CallError::CALL_ERROR_TOO_FEW_ARGUMENTS;
#else
		r_error.error = Callable::CallError::CALL_ERROR_TOO_FEW_ARGUMENTS;
#endif

		r_error.argument = 1;
		return Variant();
	}

	if (p_args[0]->get_type() != Variant::STRING) {
#if VERSION_MAJOR < 4
		r_error.error = Variant::CallError::CALL_ERROR_INVALID_ARGUMENT;
#else
		r_error.error = Callable::CallError::CALL_ERROR_INVALID_ARGUMENT;
#endif

		r_error.argument = 0;
		r_error.expected = Variant::STRING;
		return Variant();
	}

	StringName method = *p_args[0];

	for (int i = 0; i < _s_seen_by.size(); ++i) {
		Entity *e = _s_seen_by.get(i);

#if VERSION_MAJOR < 4
		if (unlikely(!ObjectDB::instance_validate(e))) {
#else
		if (unlikely(e == NULL)) {
#endif

			_s_seen_by.remove(i);
			--i;
			continue;
		}

		int netm = e->get_network_master();

		if (netm != 1)
			rpcp(netm, false, method, &p_args[1], p_argcount - 1);
	}

	//call(method, &p_args[1], p_argcount - 1);

#if VERSION_MAJOR < 4
	r_error.error = Variant::CallError::CALL_OK;
#else
	r_error.error = Callable::CallError::CALL_OK;
#endif

	return Variant();
}

Dictionary Entity::data_as_dict(String &data) {
	Error err;
	String err_txt;
	int err_line;
	Variant v;
	err = JSON::parse(data, v, err_txt, err_line);

	ERR_FAIL_COND_V(err != OK, v);

	Dictionary d = v;

	return d;
}

void Entity::register_for_physics_process(Ref<SpellCastInfo> info) {
	_physics_process_scis.push_back(info);
}

Entity::Entity() {
	_maunal_process = false;
	_deserialized = false;

	_body = NULL;
	_body_3d = NULL;
	_body_2d = NULL;

	_s_guid = 0;
	_c_guid = 0;

	_s_class_id = 0;
	_c_class_id = 0;

	_s_type = 0;
	_c_type = 0;

	_s_entity_player_type = 0;
	_c_entity_player_type = 0;

	_s_model_index = 0;
	_c_model_index = 0;

	_s_level = 1;
	_c_level = 1;

	_s_level = 1;
	_c_level = 1;

	_s_xp = 0;

	_s_send_flag = 0;

	_c_money = 0;
	_s_money = 0;

	_s_entity_name = "";
	_c_entity_name = "";

	_s_state = PlayerStates::STATE_NORMAL;
	_c_state = PlayerStates::STATE_NORMAL;

	_s_gcd = 0;
	_c_gcd = 0;

	_s_is_dead = 0;
	_c_is_dead = 0;

	_s_interaction_type = EntityEnums::ENITIY_INTERACTION_TYPE_NORMAL;
	_c_interaction_type = EntityEnums::ENITIY_INTERACTION_TYPE_NORMAL;

	_s_seed = 0;
	_c_seed = _s_seed;

	for (int i = 0; i < EntityEnums::ENTITY_STATE_TYPE_INDEX_MAX; ++i) {
		_s_states[i] = 0;
	}

	_s_state = 0;
	_c_state = 0;

	_s_active_category_cooldowns = 0;
	_c_active_category_cooldowns = 0;

	_s_entity_type = 0;
	_c_entity_type = 0;

	_s_immunity_flags = 0;

	_s_entity_flags = 0;
	_c_entity_flags = 0;

	_s_target = NULL;
	_c_target = NULL;

	_s_free_character_talent_points = 0;
	_c_free_character_talent_points = 0;

	_s_free_class_talent_points = 0;
	_c_free_class_talent_points = 0;

	_s_free_spell_points = 0;
	_c_free_spell_points = 0;

	//_action_bar_profile.instance();
	_actionbar_locked = false;

	_stats.resize(ESS::get_singleton()->stat_get_count());

	_sai_state = EntityEnums::AI_STATE_OFF;
	_sai_state_stored = EntityEnums::AI_STATE_OFF;

	_s_original_entity_controller = EntityEnums::ENITIY_CONTROLLER_NONE;
	_s_entity_controller = EntityEnums::ENITIY_CONTROLLER_NONE;
	_c_entity_controller = EntityEnums::ENITIY_CONTROLLER_NONE;

	_s_pet_owner = NULL;
	_c_pet_owner = NULL;
	_s_pet_formation_index = 0;
	_s_pet_ai_state = EntityEnums::AI_STATE_OFF;

	_s_equipment.resize(ESS::get_singleton()->equip_slot_get_count());
	_c_equipment.resize(ESS::get_singleton()->equip_slot_get_count());

	SET_RPC_REMOTE("csend_request_rank_increase");
	SET_RPC_REMOTE("csend_request_rank_decrease");

	SET_RPC_REMOTE("setc_guid");
	SET_RPC_REMOTE("setc_entity_data_id");
	SET_RPC_REMOTE("setc_entity_type");
	SET_RPC_REMOTE("setc_entity_name");
	SET_RPC_REMOTE("setc_model_index");
	SET_RPC_REMOTE("setc_level");
	SET_RPC_REMOTE("setc_xp");
	SET_RPC_REMOTE("setc_seed");
	SET_RPC_REMOTE("setc_entity_controller");

	//EntityType

	//EntityInteractionType

	SET_RPC_REMOTE("setc_entity_interaction_type");
	SET_RPC_REMOTE("setc_entity_flags");
	SET_RPC_REMOTE("setc_money");

	////     Stats    ////

	SET_RPC_REMOTE("creceive_stat");

	SET_RPC_REMOTE("diec");

	//send_stat

	////    Equip Slots    ////

	SET_RPC_REMOTE("equips");
	SET_RPC_REMOTE("equip_csuccess");
	SET_RPC_REMOTE("equip_cfail");

	////    Resources    ////

	SET_RPC_REMOTE("resource_addc_rpc");
	SET_RPC_REMOTE("resource_removec");
	SET_RPC_REMOTE("resource_clearc");

	SET_RPC_REMOTE("resource_creceive_current");
	SET_RPC_REMOTE("resource_creceive_curr_max");
	SET_RPC_REMOTE("resource_creceive_data");

	////    Global Cooldown    ////

	SET_RPC_REMOTE("gcd_startc");

	////    States    ////

	SET_RPC_REMOTE("setc_state");

	////    Crafting System    ////

	SET_RPC_REMOTE("crafts");

	SET_RPC_REMOTE("craft_addc_recipe_id");
	SET_RPC_REMOTE("craft_removec_recipe_id");

	////    SpellSystem    ////

	SET_RPC_REMOTE("spell_casts");
	SET_RPC_REMOTE("item_uses");

	//Damage Operations

	SET_RPC_REMOTE("stake_damage");
	SET_RPC_REMOTE("stake_damage");

	//Heal Operations

	SET_RPC_REMOTE("stake_heal");
	SET_RPC_REMOTE("sdeal_heal_to");

	//Damage, Heal RPCs

	SET_RPC_REMOTE("cdamage_dealt_rpc");
	SET_RPC_REMOTE("cdealt_damage_rpc");
	SET_RPC_REMOTE("cheal_dealt_rpc");
	SET_RPC_REMOTE("cdealt_heal_rpc");

	//Interactions

	SET_RPC_REMOTE("sinteract");

	SET_RPC_REMOTE("copen_window");

	//XP Operations

	SET_RPC_REMOTE("xp_addc");
	SET_RPC_REMOTE("levelup_cclass");
	SET_RPC_REMOTE("levelup_ccharacter");

	//Aura Manipulation

	SET_RPC_REMOTE("aura_addc_rpc");
	SET_RPC_REMOTE("aura_removec_rpc");
	SET_RPC_REMOTE("aura_removec_exact_rpc");
	SET_RPC_REMOTE("aura_removec_expired_rpc");
	SET_RPC_REMOTE("aura_removec_dispelled_rpc");
	SET_RPC_REMOTE("aura_refreshedc_rpc");

	////    Casting System    ////

	SET_RPC_REMOTE("setc_spell_cast_info");

	SET_RPC_REMOTE("cast_startc_rpc");
	SET_RPC_REMOTE("cast_failc");
	SET_RPC_REMOTE("cast_delayc");
	SET_RPC_REMOTE("cast_finishc");
	SET_RPC_REMOTE("cast_interruptc");

	SET_RPC_REMOTE("cast_spell_successc_rpc");

	////    Cooldowns    ////

	SET_RPC_REMOTE("cooldown_addc");
	SET_RPC_REMOTE("cooldown_removec");

	//Category Cooldowns

	SET_RPC_REMOTE("category_cooldown_addc");
	SET_RPC_REMOTE("category_cooldown_removec");

	//Known Spells

	SET_RPC_REMOTE("setc_free_spell_points");
	SET_RPC_REMOTE("spell_learns");

	SET_RPC_REMOTE("spell_addc_rpc");
	SET_RPC_REMOTE("spell_removec_rpc");

	//Skills

	SET_RPC_REMOTE("skill_addc_id");
	SET_RPC_REMOTE("skill_removec_id");
	SET_RPC_REMOTE("skill_changec");
	SET_RPC_REMOTE("skill_changec_max");

	////    Target    ////

	SET_RPC_REMOTE("target_net_sets");
	SET_RPC_REMOTE("target_net_setc");

	////    Talents    ////

	SET_RPC_REMOTE("setc_free_talent_points");
	SET_RPC_REMOTE("talent_sreceive_learn_request");
	SET_RPC_REMOTE("talent_sreceive_reset_request");

	SET_RPC_REMOTE("talent_sreset");

	SET_RPC_REMOTE("talent_addc");
	SET_RPC_REMOTE("talent_removec");

	////    Inventory    ////

	SET_RPC_REMOTE("setc_bag_rpc");
	SET_RPC_REMOTE("setc_target_bag_rpc");

	SET_RPC_REMOTE("loots");
	SET_RPC_REMOTE("lootc");

	SET_RPC_REMOTE("item_addc_rpc");
	SET_RPC_REMOTE("item_removes");
	SET_RPC_REMOTE("item_removec");
	SET_RPC_REMOTE("item_cdeny_remove");
	SET_RPC_REMOTE("items_swaps");
	SET_RPC_REMOTE("items_swapc");
	SET_RPC_REMOTE("item_cdeny_swap");
	SET_RPC_REMOTE("item_cchange_count");

	SET_RPC_REMOTE("target_item_addc_rpc");
	SET_RPC_REMOTE("target_item_removes");
	SET_RPC_REMOTE("target_item_removec");
	SET_RPC_REMOTE("target_item_cdeny_remove");
	SET_RPC_REMOTE("target_items_sswap");
	SET_RPC_REMOTE("target_items_cswap");
	SET_RPC_REMOTE("target_item_cdeny_swap");
	SET_RPC_REMOTE("target_item_cchange_count");

	////    Data    ////

	SET_RPC_REMOTE("data_addc");
	SET_RPC_REMOTE("data_removec");
}

Entity::~Entity() {
	//Ref<EntityData> _s_entity_data;
	//Ref<EntityData> _c_entity_data;

	_s_resources.clear();
	_c_resources.clear();

	//Ref<SpellCastInfo> _s_spell_cast_info;
	//Ref<SpellCastInfo> _c_spell_cast_info;

	_s_auras.clear();
	_c_auras.clear();

	_s_cooldowns.clear();
	_c_cooldowns.clear();

	_s_category_cooldowns.clear();
	_c_category_cooldowns.clear();

	_s_data.clear();
	_c_data.clear();

	_s_craft_recipes.clear();
	_c_craft_recipes.clear();

	_s_spells.clear();
	_c_spells.clear();

	_s_free_class_talent_points = 0;
	_c_free_character_talent_points = 0;

	_s_class_talents.clear();
	_c_character_talents.clear();

	_stats.clear();

	_s_equipment.clear();
	_c_equipment.clear();

	_action_bar_profile.unref();

	_s_sees.clear();
	_s_seen_by.clear();

	_s_ai.unref();

	_s_pets.clear();

	_physics_process_scis.clear();
}

void Entity::_crafts(int id) {
	if (!craft_hass_recipe_id(id))
		return;

	Ref<CraftRecipe> recipe = craft_gets_recipe_id(id);

	if (!recipe.is_valid())
		return;

	for (int i = 0; i < recipe->get_required_tools_count(); ++i) {
		Ref<CraftRecipeHelper> mat = recipe->get_required_tool(i);

		if (!mat.is_valid())
			continue;

		if (!gets_bag()->has_item(mat->get_item(), mat->get_count()))
			return;
	}

	for (int i = 0; i < recipe->get_required_materials_count(); ++i) {
		Ref<CraftRecipeHelper> mat = recipe->get_required_material(i);

		if (!mat.is_valid())
			continue;

		if (!gets_bag()->has_item(mat->get_item(), mat->get_count()))
			return;
	}

	//ok, player has everything

	for (int i = 0; i < recipe->get_required_materials_count(); ++i) {
		Ref<CraftRecipeHelper> mat = recipe->get_required_material(i);

		if (!mat.is_valid())
			continue;

		gets_bag()->remove_items(mat->get_item(), mat->get_count());
	}

	Ref<ItemInstance> item = recipe->get_item()->get_item()->create_item_instance();

	gets_bag()->add_item(item);
}

void Entity::_notification_sxp_gained(int value) {
	/*
	if (ESS::get_singleton()->get_use_class_xp() && ESS::get_singleton()->get_automatic_class_levelups()) {
		if (ESS::get_singleton()->get_resource_db()->get_xp_data()->can_class_level_up(gets_class_level())) {

			int xpr = ESS::get_singleton()->get_resource_db()->get_xp_data()->get_class_xp(gets_class_level());

			if (xpr <= gets_class_xp()) {
				levelup_sclass(1);
				sets_class_xp(0);
			}
		}
	}*/

	if (ESS::get_singleton()->can_character_level_up(gets_level())) {
		int xpr = ESS::get_singleton()->get_character_xp(gets_level());

		if (xpr <= gets_xp()) {
			levelups(1);
			sets_xp(0);
		}
	}
}

void Entity::_notification_slevel_up(int level) {
	if (!gets_entity_data().is_valid())
		return;

	Ref<EntityClassData> ecd = gets_entity_data()->get_entity_class_data();

	if (!ecd.is_valid())
		return;

	for (int i = 0; i < ESS::get_singleton()->stat_get_main_stat_count(); ++i) {
		int st = ecd->get_stat_data()->get_level_stat_data()->get_stat_diff(i, gets_level() - level, gets_level());

		stat_mod_base(i, st);
	}

	if (!ESS::get_singleton()->get_use_class_xp()) {
		if (ESS::get_singleton()->get_use_spell_points())
			sets_free_spell_points(gets_free_spell_points() + ecd->get_spell_points_per_level() * level);

		sets_free_character_talent_points(gets_free_character_talent_points() + level);
	}

	if (ESS::get_singleton()->get_use_spell_points())
		sets_free_spell_points(gets_free_spell_points() + ecd->get_spell_points_per_level() * level);

	sets_free_class_talent_points(gets_free_class_talent_points() + level);

	if (ESS::get_singleton()->get_auto_learn_spells()) {
		for (int i = 0; i < ecd->get_num_spells(); ++i) {
			Ref<Spell> sp = ecd->get_spell(i);

			if (!sp.is_valid())
				continue;

			if (sp->get_level() <= gets_level() && !spell_hass(sp)) {
				Ref<Spell> rs = sp->get_training_required_spell();

				if (rs.is_valid() && !spell_hass(rs)) {
					continue;
				}

				spell_learns(sp->get_id());
			}
		}
	}
}

void Entity::_moved() {
	if (cast_is_castings())
		cast_fails();
}

void Entity::_con_target_changed(Node *p_entity, Node *p_old_target) {
	//Entity *entity = Object::cast_to<Entity>(p_entity);
	Entity *old_target = Object::cast_to<Entity>(p_old_target);

	if (INSTANCE_VALIDATE(old_target))
		old_target->notification_cuntargeted();

	if (INSTANCE_VALIDATE(getc_target())) {
		getc_target()->notification_ctargeted();

		if (canc_interact())
			crequest_interact();
	}
}

void Entity::_notification_sdeath() {
	//only if mob
	/*
	if dead:
		return
	
	if starget == null:
		queue_free()
		return
		
	#warning-ignore:unused_variable
	for i in range(aura_gets_count()):
		aura_removes(aura_gets(0))
	
	dead = true
	
	var ldiff : float = slevel - starget.slevel + 10.0
	
	if ldiff < 0:
		ldiff = 0
		
	if ldiff > 15:
		ldiff = 15
		
	ldiff /= 10.0
	
	starget.xp_adds(int(5.0 * slevel * ldiff))
		
	starget = null
	
	sentity_interaction_type = EntityEnums.ENITIY_INTERACTION_TYPE_LOOT
	ai_state = EntityEnums.AI_STATE_OFF
	
	anim_node_state_machine.travel("dead")
	
#	set_process(false)
	set_physics_process(false)
	*/
}

void Entity::_spell_learns(int id) {
	if (ESS::get_singleton()->get_use_spell_points()) {
		ERR_FAIL_COND(gets_free_spell_points() <= 0);
	}

	ERR_FAIL_COND(!_s_entity_data.is_valid());

	Ref<EntityClassData> cd = _s_entity_data->get_entity_class_data();

	ERR_FAIL_COND(!cd.is_valid());

	for (int i = 0; i < cd->get_num_spells(); ++i) {
		Ref<Spell> sp = cd->get_spell(i);

		if (!sp.is_valid())
			continue;

		if (sp->get_id() == id) {
			int req_level = sp->get_level();

			if (req_level > gets_level()) {
				return;
			}

			int cost = sp->get_training_cost();

			if (gets_money() < cost) {
				return;
			}

			sets_money(gets_money() - cost);

			Ref<Spell> req_spell = sp->get_training_required_spell();

			if (req_spell.is_valid() && !spell_hass(req_spell)) {
				return;
			}

			spell_adds(sp);

			if (ESS::get_singleton()->get_use_spell_points())
				sets_free_spell_points(_s_free_spell_points - 1);

			return;
		}
	}
}

void Entity::_vendor_item_sbuy(const int index, const int count) {
	if (count <= 0)
		return;

	Entity *e = gets_target();

	if (!e)
		return;

	if (!iss_target_in_interact_range()) {
		return;
	}

	Ref<EntityData> ed = e->gets_entity_data();

	if (!ed.is_valid())
		return;

	Ref<EntityClassData> ecd = ed->get_entity_class_data();

	if (!ecd.is_valid())
		return;

	Ref<VendorItemData> vid = ecd->get_vendor_item_data();

	if (!vid.is_valid())
		return;

	if (vid->get_num_vendor_datas() <= index) {
		return;
	}

	Ref<VendorItemDataEntry> vide = vid->get_vendor_data(index);

	if (!vide.is_valid())
		return;

	Ref<ItemTemplate> t = vide->get_item();

	if (!t.is_valid())
		return;

	int price = vide->get_price();

	if (gets_money() < price)
		return;

	Ref<Bag> sbag = gets_bag();

	int s = count;
	if (t->get_stack_size() < s)
		s = t->get_stack_size();

	Ref<ItemInstance> ii = t->create_item_instance();
	ii->set_stack_size(s);

	//todo make this work with item templates
	if (!sbag->can_add_item(ii)) {
		return;
	}

	sets_money(gets_money() - price);
	sbag->add_item(ii);
}
void Entity::_vendor_item_ssell(const int slot_id) {
	Entity *e = gets_target();

	if (!e)
		return;

	if (!iss_target_in_interact_range()) {
		return;
	}

	Ref<EntityData> ed = e->gets_entity_data();

	if (!ed.is_valid())
		return;

	Ref<EntityClassData> ecd = ed->get_entity_class_data();

	if (!ecd.is_valid())
		return;

	Ref<VendorItemData> vid = ecd->get_vendor_item_data();

	if (!vid.is_valid())
		return;

	Ref<Bag> bag = gets_bag();

	Ref<ItemInstance> ii = bag->get_item(slot_id);

	if (!ii.is_valid())
		return;

	Ref<ItemTemplate> it = ii->get_item_template();

	int price = it->get_price();

	if (price == 0)
		return;

	sets_money(gets_money() + price);

	bag->remove_item(slot_id);
}

void Entity::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_POSTINITIALIZE: {
			call("_initialize");
		} break;
		case NOTIFICATION_INSTANCED: {
			set_body(get_node_or_null(_body_path));

			if (INSTANCE_VALIDATE(_body))
				_body->set_owner(this);

			_character_skeleton = get_node_or_null(_character_skeleton_path);

			if (_character_skeleton != NULL) {
				if (_character_skeleton->has_method("set_model_index"))
					_character_skeleton->call("set_model_index", _c_model_index);
			}
		} break;
		case NOTIFICATION_ENTER_TREE: {
			if (!Engine::get_singleton()->is_editor_hint())
				set_process(true);

			if (!_body) {
				set_body(get_node_or_null(_body_path));

				if (INSTANCE_VALIDATE(_body))
					_body->set_owner(this);
			}

			if (!_character_skeleton) {
				_character_skeleton = get_node_or_null(_character_skeleton_path);

				if (_character_skeleton != NULL) {
					if (_character_skeleton->has_method("set_model_index"))
						_character_skeleton->call("set_model_index", _c_model_index);
				}
			}
		} break;
		case NOTIFICATION_PROCESS: {
			if (!_maunal_process)
				update(get_process_delta_time());
		} break;
		case NOTIFICATION_PHYSICS_PROCESS: {
			son_physics_process(get_physics_process_delta_time());
		} break;
		case NOTIFICATION_EXIT_TREE: {
			for (int i = 0; i < _s_seen_by.size(); ++i) {
				Entity *e = _s_seen_by.get(i);

				if (INSTANCE_VALIDATE(e))
					e->sees_removes(this);
			}
		} break;
	}
}

bool Entity::_set(const StringName &p_name, const Variant &p_value) {
	String name = p_name;

	String main_prop = name.get_slicec('/', 0);

	if (main_prop == "stat") {
		int stat_id = name.get_slicec('/', 1).to_int();
		String stat_prop_name = name.get_slicec('/', 2);

		if (stat_prop_name == "base") {
			stat_set_base(stat_id, p_value);

			return true;
		} else if (stat_prop_name == "bonus") {
			stat_set_bonus(stat_id, p_value);

			return true;
		} else if (stat_prop_name == "percent") {
			stat_set_percent(stat_id, p_value);

			return true;
		} else if (stat_prop_name == "scurrent") {
			stat_sets_current(stat_id, p_value);

			return true;
		} else {
			return false;
		}
	} else if (main_prop == "sequipment") {
		int slot_id = name.get_slicec('/', 1).to_int();

		if (_s_equipment.size() <= slot_id) {
			return false;
		}

		_s_equipment.write[slot_id] = p_value;

		return true;
	}

	return false;
}

bool Entity::_get(const StringName &p_name, Variant &r_ret) const {
	String name = p_name;

	String main_prop = name.get_slicec('/', 0);

	if (main_prop == "stat") {
		int stat_id = name.get_slicec('/', 1).to_int();
		String stat_prop_name = name.get_slicec('/', 2);

		if (stat_prop_name == "base") {
			r_ret = stat_get_base(stat_id);

			return true;
		} else if (stat_prop_name == "bonus") {
			r_ret = stat_get_bonus(stat_id);

			return true;
		} else if (stat_prop_name == "percent") {
			r_ret = stat_get_percent(stat_id);

			return true;
		} else if (stat_prop_name == "scurrent") {
			r_ret = stat_gets_current(stat_id);

			return true;
		} else {
			return false;
		}
	} else if (main_prop == "sequipment") {
		int slot_id = name.get_slicec('/', 1).to_int();

		if (_s_equipment.size() <= slot_id) {
			return false;
		}

		r_ret = _s_equipment[slot_id];

		return true;
	}

	return false;
}

void Entity::_get_property_list(List<PropertyInfo> *p_list) const {
#if PROPERTY_DEBUG
	int property_usange = PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL;
#else
	int property_usange = PROPERTY_USAGE_STORAGE | PROPERTY_USAGE_INTERNAL;
#endif

	for (int i = 0; i < ESS::get_singleton()->stat_get_count(); ++i) {
		p_list->push_back(PropertyInfo(Variant::REAL, "stat/" + itos(i) + "/base", PROPERTY_HINT_NONE, "", property_usange));
		p_list->push_back(PropertyInfo(Variant::REAL, "stat/" + itos(i) + "/percent", PROPERTY_HINT_NONE, "", property_usange));
		p_list->push_back(PropertyInfo(Variant::REAL, "stat/" + itos(i) + "/scurrent", PROPERTY_HINT_NONE, "", property_usange));
	}

	for (int i = 0; i < ESS::get_singleton()->equip_slot_get_count(); ++i) {
		p_list->push_back(PropertyInfo(Variant::OBJECT, "sequipment/" + itos(i), PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance", property_usange));
	}
}

void Entity::_validate_property(PropertyInfo &property) const {
	String name = property.name;

	if (name == "sentity_player_type" || name == "centity_player_type") {
		property.hint_string = ESS::get_singleton()->entity_types_get();
	}
}

void Entity::_bind_methods() {
	//Signals
	ADD_SIGNAL(MethodInfo("deserialized", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	ADD_SIGNAL(MethodInfo("sname_changed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	ADD_SIGNAL(MethodInfo("cname_changed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	ADD_SIGNAL(MethodInfo("starget_changed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "old_target", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	ADD_SIGNAL(MethodInfo("ctarget_changed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "old_target", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	ADD_SIGNAL(MethodInfo("son_damage_received", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	ADD_SIGNAL(MethodInfo("con_damage_received", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	ADD_SIGNAL(MethodInfo("son_damage_dealt", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	ADD_SIGNAL(MethodInfo("con_damage_dealt", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	ADD_SIGNAL(MethodInfo("son_dealt_damage", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	ADD_SIGNAL(MethodInfo("con_dealt_damage", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	ADD_SIGNAL(MethodInfo("son_heal_received", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	ADD_SIGNAL(MethodInfo("con_heal_received", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));

	ADD_SIGNAL(MethodInfo("son_dealt_heal", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	ADD_SIGNAL(MethodInfo("con_dealt_heal", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));

	ADD_SIGNAL(MethodInfo("son_heal_dealt", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	ADD_SIGNAL(MethodInfo("con_heal_dealt", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));

	ADD_SIGNAL(MethodInfo("sentity_data_changed", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "EntityData")));
	ADD_SIGNAL(MethodInfo("centity_data_changed", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "EntityData")));

	ADD_SIGNAL(MethodInfo("diesd", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	ADD_SIGNAL(MethodInfo("diecd", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	ADD_SIGNAL(MethodInfo("sentity_resource_added", PropertyInfo(Variant::OBJECT, "resource", PROPERTY_HINT_RESOURCE_TYPE, "EntityResource")));
	ADD_SIGNAL(MethodInfo("sentity_resource_removed", PropertyInfo(Variant::OBJECT, "resource", PROPERTY_HINT_RESOURCE_TYPE, "EntityResource")));
	ADD_SIGNAL(MethodInfo("centity_resource_added", PropertyInfo(Variant::OBJECT, "resource", PROPERTY_HINT_RESOURCE_TYPE, "EntityResource")));
	ADD_SIGNAL(MethodInfo("centity_resource_removed", PropertyInfo(Variant::OBJECT, "resource", PROPERTY_HINT_RESOURCE_TYPE, "EntityResource")));

	//Skills
	ADD_SIGNAL(MethodInfo("sskill_added", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "skill", PROPERTY_HINT_RESOURCE_TYPE, "EntitySkill")));
	ADD_SIGNAL(MethodInfo("sskill_removed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "skill", PROPERTY_HINT_RESOURCE_TYPE, "EntitySkill")));

	ADD_SIGNAL(MethodInfo("cskill_added", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "skill", PROPERTY_HINT_RESOURCE_TYPE, "EntitySkill")));
	ADD_SIGNAL(MethodInfo("cskill_removed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "skill", PROPERTY_HINT_RESOURCE_TYPE, "EntitySkill")));
	ADD_SIGNAL(MethodInfo("cskill_changed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "skill", PROPERTY_HINT_RESOURCE_TYPE, "EntitySkill")));

	//Windows
	ADD_SIGNAL(MethodInfo("onc_open_winow_request", PropertyInfo(Variant::INT, "window_id")));

	//setup
	BIND_VMETHOD(MethodInfo("_setup"));
	BIND_VMETHOD(MethodInfo("_initialize"));

	ClassDB::bind_method(D_METHOD("_initialize"), &Entity::_initialize);
	ClassDB::bind_method(D_METHOD("setup", "info"), &Entity::setup);
	ClassDB::bind_method(D_METHOD("_setup"), &Entity::_setup);
	ClassDB::bind_method(D_METHOD("setup_actionbars"), &Entity::setup_actionbars);

	//binds

	ClassDB::bind_method(D_METHOD("stat_get_dirty", "stat_id"), &Entity::stat_get_dirty);
	ClassDB::bind_method(D_METHOD("stat_set_dirty", "stat_id", "value"), &Entity::stat_set_dirty);

	ClassDB::bind_method(D_METHOD("stat_get_base", "stat_id"), &Entity::stat_get_base);
	ClassDB::bind_method(D_METHOD("stat_set_base", "stat_id", "value"), &Entity::stat_set_base);
	ClassDB::bind_method(D_METHOD("stat_mod_base", "stat_id", "value"), &Entity::stat_mod_base);

	ClassDB::bind_method(D_METHOD("stat_get_base_calculated", "stat_id"), &Entity::stat_get_base_calculated);
	ClassDB::bind_method(D_METHOD("stat_set_base_calculated", "stat_id", "value"), &Entity::stat_set_base_calculated);

	ClassDB::bind_method(D_METHOD("stat_get_bonus", "stat_id"), &Entity::stat_get_bonus);
	ClassDB::bind_method(D_METHOD("stat_set_bonus", "stat_id", "value"), &Entity::stat_set_bonus);
	ClassDB::bind_method(D_METHOD("stat_mod_bonus", "stat_id", "value"), &Entity::stat_mod_bonus);

	ClassDB::bind_method(D_METHOD("stat_get_percent", "stat_id"), &Entity::stat_get_percent);
	ClassDB::bind_method(D_METHOD("stat_set_percent", "stat_id", "value"), &Entity::stat_set_percent);
	ClassDB::bind_method(D_METHOD("stat_mod_percent", "stat_id", "value"), &Entity::stat_mod_percent);

	ClassDB::bind_method(D_METHOD("stat_mod", "stat_id", "base", "bonus", "percent"), &Entity::stat_mod);

	ClassDB::bind_method(D_METHOD("stat_gets_current", "stat_id"), &Entity::stat_gets_current);
	ClassDB::bind_method(D_METHOD("stat_sets_current", "stat_id", "value"), &Entity::stat_sets_current);

	ClassDB::bind_method(D_METHOD("stat_getc_current", "stat_id"), &Entity::stat_getc_current);
	ClassDB::bind_method(D_METHOD("stat_setc_current", "stat_id", "value"), &Entity::stat_setc_current);

	ClassDB::bind_method(D_METHOD("stat_recalculate", "stat_id"), &Entity::stat_recalculate);

	ClassDB::bind_method(D_METHOD("ssend_stat", "id", "ccurrent"), &Entity::ssend_stat);
	ClassDB::bind_method(D_METHOD("creceive_stat", "id", "ccurrent"), &Entity::creceive_stat);

	ClassDB::bind_method(D_METHOD("dies"), &Entity::dies);
	ClassDB::bind_method(D_METHOD("diec"), &Entity::diec);

	ClassDB::bind_method(D_METHOD("notification_sstat_changed", "stat"), &Entity::notification_sstat_changed);
	ClassDB::bind_method(D_METHOD("notification_cstat_changed", "stat"), &Entity::notification_cstat_changed);

	//EventHandlers
	BIND_VMETHOD(MethodInfo("_notification_sdeath"));

	BIND_VMETHOD(MethodInfo("_notification_sgcd_started", PropertyInfo(Variant::REAL, "gcd")));
	BIND_VMETHOD(MethodInfo("_notification_sgcd_finished"));

	BIND_VMETHOD(MethodInfo("_notification_sxp_gained", PropertyInfo(Variant::INT, "value")));
	BIND_VMETHOD(MethodInfo("_notification_slevel_up", PropertyInfo(Variant::INT, "value")));

	BIND_VMETHOD(MethodInfo("_notification_sentity_resource_added", PropertyInfo(Variant::OBJECT, "resource", PROPERTY_HINT_RESOURCE_TYPE, "EntityResource")));
	BIND_VMETHOD(MethodInfo("_notification_sentity_resource_removed", PropertyInfo(Variant::OBJECT, "resource", PROPERTY_HINT_RESOURCE_TYPE, "EntityResource")));

	BIND_VMETHOD(MethodInfo("_son_target_changed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "old_target", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	BIND_VMETHOD(MethodInfo("_con_target_changed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "old_target", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	//Serverside
	ADD_SIGNAL(MethodInfo("notification_sdamage", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	ADD_SIGNAL(MethodInfo("notification_sheal", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	ADD_SIGNAL(MethodInfo("notification_scast", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "spell_cast_info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	ADD_SIGNAL(MethodInfo("notification_saura", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "aura_data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));

	BIND_VMETHOD(MethodInfo("_notification_saura", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_notification_sheal", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	BIND_VMETHOD(MethodInfo("_notification_scast", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_notification_sdamage", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	ClassDB::bind_method(D_METHOD("notification_saura", "what", "data"), &Entity::notification_saura);
	ClassDB::bind_method(D_METHOD("notification_sheal", "what", "info"), &Entity::notification_sheal);
	ClassDB::bind_method(D_METHOD("notification_scast", "what", "info"), &Entity::notification_scast);
	ClassDB::bind_method(D_METHOD("notification_sdamage", "what", "info"), &Entity::notification_sdamage);

	//Clientside
	ADD_SIGNAL(MethodInfo("notification_cdamage", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	ADD_SIGNAL(MethodInfo("notification_cheal", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	ADD_SIGNAL(MethodInfo("notification_ccast", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "spell_cast_info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	ADD_SIGNAL(MethodInfo("notification_caura", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "aura_data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));

	BIND_VMETHOD(MethodInfo("_notification_caura", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_notification_cheal", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	BIND_VMETHOD(MethodInfo("_notification_ccast", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_notification_cdamage", PropertyInfo(Variant::INT, "what"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	ClassDB::bind_method(D_METHOD("notification_caura", "what", "data"), &Entity::notification_caura);
	ClassDB::bind_method(D_METHOD("notification_cheal", "what", "info"), &Entity::notification_cheal);
	ClassDB::bind_method(D_METHOD("notification_ccast", "what", "info"), &Entity::notification_ccast);
	ClassDB::bind_method(D_METHOD("notification_cdamage", "what", "info"), &Entity::notification_cdamage);

	ClassDB::bind_method(D_METHOD("notification_sdeath"), &Entity::notification_sdeath);

	ClassDB::bind_method(D_METHOD("notification_sgcd_started"), &Entity::notification_sgcd_started);
	ClassDB::bind_method(D_METHOD("notification_sgcd_finished"), &Entity::notification_sgcd_finished);

	ClassDB::bind_method(D_METHOD("notification_sentity_resource_added", "resource"), &Entity::notification_sentity_resource_added);
	ClassDB::bind_method(D_METHOD("notification_sentity_resource_removed", "resource"), &Entity::notification_sentity_resource_removed);

	//Class Talents

	ClassDB::bind_method(D_METHOD("gets_free_class_talent_points"), &Entity::gets_free_class_talent_points);
	ClassDB::bind_method(D_METHOD("sets_free_class_talent_points", "value"), &Entity::sets_free_class_talent_points);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "sfree_class_talent_points", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_ENTITY_HIDDEN), "sets_free_class_talent_points", "gets_free_class_talent_points");

	ClassDB::bind_method(D_METHOD("getc_free_class_talent_points"), &Entity::getc_free_class_talent_points);
	ClassDB::bind_method(D_METHOD("setc_free_class_talent_points", "value"), &Entity::setc_free_class_talent_points);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "cfree_class_talent_points", PROPERTY_HINT_NONE, "", 0), "setc_free_class_talent_points", "getc_free_class_talent_points");

	BIND_VMETHOD(MethodInfo("_class_talent_sreceive_learn_request", PropertyInfo(Variant::INT, "spec_index"), PropertyInfo(Variant::INT, "class_talent_row"), PropertyInfo(Variant::INT, "class_talent_culomn")));
	BIND_VMETHOD(MethodInfo("_class_talent_sreceive_reset_request"));

	ADD_SIGNAL(MethodInfo("sclass_talent_learned", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "class_talent_id")));
	ADD_SIGNAL(MethodInfo("cclass_talent_learned", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "class_talent_id")));

	ADD_SIGNAL(MethodInfo("sclass_talent_reset", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	ADD_SIGNAL(MethodInfo("cclass_talent_reset", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	BIND_VMETHOD(MethodInfo("_son_class_talent_learned", PropertyInfo(Variant::INT, "class_talent_id")));
	BIND_VMETHOD(MethodInfo("_con_class_talent_learned", PropertyInfo(Variant::INT, "class_talent_id")));

	BIND_VMETHOD(MethodInfo("_son_class_talent_reset"));
	BIND_VMETHOD(MethodInfo("_con_class_talent_reset"));

	ClassDB::bind_method(D_METHOD("class_talent_crequest_learn", "spec_index", "class_talent_row", "class_talent_culomn"), &Entity::class_talent_crequest_learn);
	ClassDB::bind_method(D_METHOD("class_talent_sreceive_learn_request", "spec_index", "class_talent_row", "class_talent_culomn"), &Entity::class_talent_sreceive_learn_request);
	ClassDB::bind_method(D_METHOD("_class_talent_sreceive_learn_request", "spec_index", "class_talent_row", "class_talent_culomn"), &Entity::_class_talent_sreceive_learn_request);

	ClassDB::bind_method(D_METHOD("class_talent_crequest_reset"), &Entity::class_talent_crequest_reset);
	ClassDB::bind_method(D_METHOD("class_talent_sreceive_reset_request"), &Entity::class_talent_sreceive_reset_request);
	ClassDB::bind_method(D_METHOD("_class_talent_sreceive_reset_request"), &Entity::_class_talent_sreceive_reset_request);

	ClassDB::bind_method(D_METHOD("class_talent_sreset"), &Entity::class_talent_sreset);
	ClassDB::bind_method(D_METHOD("class_talent_creset"), &Entity::class_talent_creset);

	ClassDB::bind_method(D_METHOD("class_talent_adds", "class_talent"), &Entity::class_talent_adds);
	ClassDB::bind_method(D_METHOD("class_talent_removes", "class_talent"), &Entity::class_talent_removes);
	ClassDB::bind_method(D_METHOD("class_talent_hass", "class_talent"), &Entity::class_talent_hass);
	ClassDB::bind_method(D_METHOD("class_talent_gets", "index"), &Entity::class_talent_gets);
	ClassDB::bind_method(D_METHOD("class_talent_gets_count"), &Entity::class_talent_gets_count);
	ClassDB::bind_method(D_METHOD("class_talents_sclear"), &Entity::class_talents_sclear);

	ClassDB::bind_method(D_METHOD("class_talent_addc", "class_talent"), &Entity::class_talent_addc);
	ClassDB::bind_method(D_METHOD("class_talent_removec", "class_talent"), &Entity::class_talent_removec);
	ClassDB::bind_method(D_METHOD("class_talent_hasc", "class_talent"), &Entity::class_talent_hasc);
	ClassDB::bind_method(D_METHOD("class_talent_getc", "index"), &Entity::class_talent_getc);
	ClassDB::bind_method(D_METHOD("class_talent_getc_count"), &Entity::class_talent_getc_count);
	ClassDB::bind_method(D_METHOD("class_talent_cclear"), &Entity::class_talent_cclear);

	ClassDB::bind_method(D_METHOD("sclass_talents_get"), &Entity::sclass_talents_get);
	ClassDB::bind_method(D_METHOD("sclass_talents_set", "data"), &Entity::sclass_talents_set);
	ADD_PROPERTY(PropertyInfo(Variant::POOL_INT_ARRAY, "sclass_talents", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_ENTITY_HIDDEN), "sclass_talents_set", "sclass_talents_get");

	//Character Talents

	ClassDB::bind_method(D_METHOD("gets_free_character_talent_points"), &Entity::gets_free_character_talent_points);
	ClassDB::bind_method(D_METHOD("sets_free_character_talent_points", "value"), &Entity::sets_free_character_talent_points);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "sfree_character_talent_points", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_ENTITY_HIDDEN), "sets_free_character_talent_points", "gets_free_character_talent_points");

	ClassDB::bind_method(D_METHOD("getc_free_character_talent_points"), &Entity::getc_free_character_talent_points);
	ClassDB::bind_method(D_METHOD("setc_free_character_talent_points", "value"), &Entity::setc_free_character_talent_points);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "cfree_character_talent_points", PROPERTY_HINT_NONE, "", 0), "setc_free_character_talent_points", "getc_free_character_talent_points");

	BIND_VMETHOD(MethodInfo("_character_talent_sreceive_learn_request", PropertyInfo(Variant::INT, "spec_index"), PropertyInfo(Variant::INT, "character_talent_row"), PropertyInfo(Variant::INT, "character_talent_culomn")));
	BIND_VMETHOD(MethodInfo("_character_talent_sreceive_reset_request"));

	ADD_SIGNAL(MethodInfo("scharacter_talent_learned", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "character_talent_id")));
	ADD_SIGNAL(MethodInfo("ccharacter_talent_learned", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "character_talent_id")));

	ADD_SIGNAL(MethodInfo("scharacter_talent_reset", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	ADD_SIGNAL(MethodInfo("ccharacter_talent_reset", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	BIND_VMETHOD(MethodInfo("_son_character_talent_learned", PropertyInfo(Variant::INT, "character_talent_id")));
	BIND_VMETHOD(MethodInfo("_con_character_talent_learned", PropertyInfo(Variant::INT, "character_talent_id")));

	BIND_VMETHOD(MethodInfo("_son_character_talent_reset"));
	BIND_VMETHOD(MethodInfo("_con_character_talent_reset"));

	ClassDB::bind_method(D_METHOD("character_talent_crequest_learn", "spec_index", "character_talent_row", "character_talent_culomn"), &Entity::character_talent_crequest_learn);
	ClassDB::bind_method(D_METHOD("character_talent_sreceive_learn_request", "spec_index", "character_talent_row", "character_talent_culomn"), &Entity::character_talent_sreceive_learn_request);
	ClassDB::bind_method(D_METHOD("_character_talent_sreceive_learn_request", "spec_index", "character_talent_row", "character_talent_culomn"), &Entity::_character_talent_sreceive_learn_request);

	ClassDB::bind_method(D_METHOD("character_talent_crequest_reset"), &Entity::character_talent_crequest_reset);
	ClassDB::bind_method(D_METHOD("character_talent_sreceive_reset_request"), &Entity::character_talent_sreceive_reset_request);
	ClassDB::bind_method(D_METHOD("_character_talent_sreceive_reset_request"), &Entity::_character_talent_sreceive_reset_request);

	ClassDB::bind_method(D_METHOD("character_talent_sreset"), &Entity::character_talent_sreset);
	ClassDB::bind_method(D_METHOD("character_talent_creset"), &Entity::character_talent_creset);

	ClassDB::bind_method(D_METHOD("character_talent_adds", "character_talent"), &Entity::character_talent_adds);
	ClassDB::bind_method(D_METHOD("character_talent_removes", "character_talent"), &Entity::character_talent_removes);
	ClassDB::bind_method(D_METHOD("character_talent_hass", "character_talent"), &Entity::character_talent_hass);
	ClassDB::bind_method(D_METHOD("character_talent_gets", "index"), &Entity::character_talent_gets);
	ClassDB::bind_method(D_METHOD("character_talent_gets_count"), &Entity::character_talent_gets_count);
	ClassDB::bind_method(D_METHOD("character_talents_sclear"), &Entity::character_talents_sclear);

	ClassDB::bind_method(D_METHOD("character_talent_addc", "character_talent"), &Entity::character_talent_addc);
	ClassDB::bind_method(D_METHOD("character_talent_removec", "character_talent"), &Entity::character_talent_removec);
	ClassDB::bind_method(D_METHOD("character_talent_hasc", "character_talent"), &Entity::character_talent_hasc);
	ClassDB::bind_method(D_METHOD("character_talent_getc", "index"), &Entity::character_talent_getc);
	ClassDB::bind_method(D_METHOD("character_talent_getc_count"), &Entity::character_talent_getc_count);
	ClassDB::bind_method(D_METHOD("character_talent_cclear"), &Entity::character_talent_cclear);

	ClassDB::bind_method(D_METHOD("scharacter_talents_get"), &Entity::scharacter_talents_get);
	ClassDB::bind_method(D_METHOD("scharacter_talents_set", "data"), &Entity::scharacter_talents_set);
	ADD_PROPERTY(PropertyInfo(Variant::POOL_INT_ARRAY, "scharacter_talents", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_ENTITY_HIDDEN), "scharacter_talents_set", "scharacter_talents_get");

	//Cooldowns
	BIND_VMETHOD(MethodInfo("notification_scooldown_added", PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));
	BIND_VMETHOD(MethodInfo("notification_scooldown_removed", PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));
	BIND_VMETHOD(MethodInfo("notification_scategory_cooldown_added", PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));
	BIND_VMETHOD(MethodInfo("notification_scategory_cooldown_removed", PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));

	ClassDB::bind_method(D_METHOD("notification_scooldown_added", "cooldown"), &Entity::notification_scooldown_added);
	ClassDB::bind_method(D_METHOD("notification_scooldown_removed", "cooldown"), &Entity::notification_scooldown_removed);
	ClassDB::bind_method(D_METHOD("notification_scategory_cooldown_added", "category_cooldown"), &Entity::notification_scategory_cooldown_added);
	ClassDB::bind_method(D_METHOD("notification_scategory_cooldown_removed", "category_cooldown"), &Entity::notification_scategory_cooldown_removed);

	//Clientside EventHandlers
	BIND_VMETHOD(MethodInfo("_notification_cdeath"));

	BIND_VMETHOD(MethodInfo("notification_ccooldown_added", PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));
	BIND_VMETHOD(MethodInfo("notification_ccooldown_removed", PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));
	BIND_VMETHOD(MethodInfo("notification_ccategory_cooldown_added", PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));
	BIND_VMETHOD(MethodInfo("notification_ccategory_cooldown_removed", PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));

	ClassDB::bind_method(D_METHOD("notification_ccooldown_added", "cooldown"), &Entity::notification_ccooldown_added);
	ClassDB::bind_method(D_METHOD("notification_ccooldown_removed", "cooldown"), &Entity::notification_ccooldown_removed);
	ClassDB::bind_method(D_METHOD("notification_ccategory_cooldown_added", "category_cooldown"), &Entity::notification_ccategory_cooldown_added);
	ClassDB::bind_method(D_METHOD("notification_ccategory_cooldown_removed", "category_cooldown"), &Entity::notification_ccategory_cooldown_removed);

	BIND_VMETHOD(MethodInfo("_notification_cgcd_started", PropertyInfo(Variant::REAL, "gcd")));
	BIND_VMETHOD(MethodInfo("_notification_cgcd_finished"));

	BIND_VMETHOD(MethodInfo("_notification_cxp_gained", PropertyInfo(Variant::INT, "value")));
	BIND_VMETHOD(MethodInfo("_notification_clevel_up", PropertyInfo(Variant::INT, "value")));

	BIND_VMETHOD(MethodInfo("_notification_centity_resource_added", PropertyInfo(Variant::OBJECT, "resource", PROPERTY_HINT_RESOURCE_TYPE, "EntityResource")));
	BIND_VMETHOD(MethodInfo("_notification_centity_resource_removed", PropertyInfo(Variant::OBJECT, "resource", PROPERTY_HINT_RESOURCE_TYPE, "EntityResource")));

	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "value"), "_canc_interact"));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "value"), "_cans_interact"));
	BIND_VMETHOD(MethodInfo("_sinteract"));

	ClassDB::bind_method(D_METHOD("cast_spell_successc", "info"), &Entity::cast_spell_successc);
	ClassDB::bind_method(D_METHOD("cast_spell_successc_rpc", "data"), &Entity::cast_spell_successc_rpc);

	ClassDB::bind_method(D_METHOD("notification_cdeath"), &Entity::notification_cdeath);

	ClassDB::bind_method(D_METHOD("notification_cgcd_started"), &Entity::notification_cgcd_started);
	ClassDB::bind_method(D_METHOD("notification_cgcd_finished"), &Entity::notification_cgcd_finished);

	ClassDB::bind_method(D_METHOD("notification_cxp_gained", "value"), &Entity::notification_cxp_gained);
	ClassDB::bind_method(D_METHOD("notification_clevel_up", "value"), &Entity::notification_clevel_up);

	ClassDB::bind_method(D_METHOD("notification_centity_resource_added", "resource"), &Entity::notification_centity_resource_added);
	ClassDB::bind_method(D_METHOD("notification_centity_resource_removed", "resource"), &Entity::notification_centity_resource_removed);

	//Modifiers/Requesters
	ClassDB::bind_method(D_METHOD("sapply_passives_damage_receive", "data"), &Entity::sapply_passives_damage_receive);
	ClassDB::bind_method(D_METHOD("sapply_passives_damage_deal", "data"), &Entity::sapply_passives_damage_deal);

	//Spell operations
	ClassDB::bind_method(D_METHOD("spell_casts", "spell_id"), &Entity::spell_casts);
	ClassDB::bind_method(D_METHOD("spell_crequest_cast", "spell_id"), &Entity::spell_crequest_cast);

	BIND_VMETHOD(MethodInfo("_item_uses", PropertyInfo(Variant::INT, "item_id")));

	ClassDB::bind_method(D_METHOD("item_uses", "item_id"), &Entity::item_uses);
	ClassDB::bind_method(D_METHOD("item_crequest_use", "item_id"), &Entity::item_crequest_use);
	ClassDB::bind_method(D_METHOD("_item_uses", "item_id"), &Entity::_item_uses);

	//Damage Operations
	ClassDB::bind_method(D_METHOD("stake_damage", "data"), &Entity::stake_damage);
	ClassDB::bind_method(D_METHOD("sdeal_damage_to", "data"), &Entity::sdeal_damage_to);

	//Heal Operations
	ClassDB::bind_method(D_METHOD("stake_heal", "data"), &Entity::stake_heal);
	ClassDB::bind_method(D_METHOD("sdeal_heal_to", "data"), &Entity::sdeal_heal_to);

	//Damage, Heal RPCs
	ClassDB::bind_method(D_METHOD("cdamage_dealt_rpc", "data"), &Entity::cdamage_dealt_rpc);
	ClassDB::bind_method(D_METHOD("cdealt_damage_rpc", "data"), &Entity::cdealt_damage_rpc);
	ClassDB::bind_method(D_METHOD("cheal_dealt_rpc", "data"), &Entity::cheal_dealt_rpc);
	ClassDB::bind_method(D_METHOD("cdealt_heal_rpc", "data"), &Entity::cdealt_heal_rpc);

	//Interactions
	ClassDB::bind_method(D_METHOD("cans_interact"), &Entity::cans_interact);
	ClassDB::bind_method(D_METHOD("sinteract"), &Entity::sinteract);

	ClassDB::bind_method(D_METHOD("canc_interact"), &Entity::canc_interact);
	ClassDB::bind_method(D_METHOD("crequest_interact"), &Entity::crequest_interact);

	ClassDB::bind_method(D_METHOD("ssend_open_window", "window_id"), &Entity::ssend_open_window);
	ClassDB::bind_method(D_METHOD("copen_window", "window_id"), &Entity::copen_window);

	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "ret"), "_iss_target_in_interact_range"));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "ret"), "_isc_target_in_interact_range"));

	ClassDB::bind_method(D_METHOD("iss_target_in_interact_range"), &Entity::iss_target_in_interact_range);
	ClassDB::bind_method(D_METHOD("isc_target_in_interact_range"), &Entity::isc_target_in_interact_range);
	ClassDB::bind_method(D_METHOD("_iss_target_in_interact_range"), &Entity::_iss_target_in_interact_range);
	ClassDB::bind_method(D_METHOD("_isc_target_in_interact_range"), &Entity::_isc_target_in_interact_range);

	//XP Operations
	ADD_SIGNAL(MethodInfo("notification_sxp_gained", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "value")));
	ADD_SIGNAL(MethodInfo("notification_cxp_gained", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "value")));

	ADD_SIGNAL(MethodInfo("notification_clevel_up", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "value")));
	ADD_SIGNAL(MethodInfo("notification_slevel_up", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "value")));

	ADD_SIGNAL(MethodInfo("son_level_changed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "level")));
	ADD_SIGNAL(MethodInfo("con_level_changed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "level")));

	ClassDB::bind_method(D_METHOD("xp_adds", "value"), &Entity::xp_adds);
	ClassDB::bind_method(D_METHOD("xp_addc", "value"), &Entity::xp_addc);

	ClassDB::bind_method(D_METHOD("levelups", "value"), &Entity::levelups);
	ClassDB::bind_method(D_METHOD("levelupc", "value"), &Entity::levelupc);

	ClassDB::bind_method(D_METHOD("notification_sxp_gained", "value"), &Entity::notification_sxp_gained);
	ClassDB::bind_method(D_METHOD("notification_slevel_up", "value"), &Entity::notification_slevel_up);

	//Aura Manipulation
	ClassDB::bind_method(D_METHOD("aura_adds", "aura"), &Entity::aura_adds);
	ClassDB::bind_method(D_METHOD("aura_removes", "aura"), &Entity::aura_removes);
	ClassDB::bind_method(D_METHOD("aura_removes_exact", "aura"), &Entity::aura_removes_exact);
	ClassDB::bind_method(D_METHOD("aura_removes_expired", "aura"), &Entity::aura_removes_expired);
	ClassDB::bind_method(D_METHOD("aura_removes_dispelled", "aura"), &Entity::aura_removes_dispelled);
	//ClassDB::bind_method(D_METHOD("aura_refresheds", "aura"), &Entity::aura_refresheds);

	ClassDB::bind_method(D_METHOD("aura_addc_rpc", "data"), &Entity::aura_addc_rpc);
	ClassDB::bind_method(D_METHOD("aura_removec_rpc", "data"), &Entity::aura_removec_rpc);
	ClassDB::bind_method(D_METHOD("aura_removec_exact_rpc", "data"), &Entity::aura_removec_exact_rpc);
	ClassDB::bind_method(D_METHOD("aura_removec_expired_rpc", "data"), &Entity::aura_removec_expired_rpc);
	ClassDB::bind_method(D_METHOD("aura_removec_dispelled_rpc", "data"), &Entity::aura_removec_dispelled_rpc);

	ClassDB::bind_method(D_METHOD("aura_addc", "aura"), &Entity::aura_addc);
	ClassDB::bind_method(D_METHOD("aura_removec", "aura"), &Entity::aura_removec);
	ClassDB::bind_method(D_METHOD("aura_removec_exact", "aura"), &Entity::aura_removec_exact);
	ClassDB::bind_method(D_METHOD("aura_removec_expired", "aura"), &Entity::aura_removec_expired);
	ClassDB::bind_method(D_METHOD("aura_removec_dispelled", "aura"), &Entity::aura_removec_dispelled);
	//ClassDB::bind_method(D_METHOD("aura_refreshedc", "aura"), &Entity::aura_refreshedc);

	ClassDB::bind_method(D_METHOD("aura_removess_with_group", "aura_group"), &Entity::aura_removess_with_group);

	ClassDB::bind_method(D_METHOD("aura_gets_count"), &Entity::aura_gets_count);
	ClassDB::bind_method(D_METHOD("aura_gets", "index"), &Entity::aura_gets);
	ClassDB::bind_method(D_METHOD("aura_gets_by", "caster", "aura_id"), &Entity::aura_gets_by_bind);
	ClassDB::bind_method(D_METHOD("aura_gets_with_group_by", "caster", "aura_group"), &Entity::aura_gets_with_group_by_bind);

	ClassDB::bind_method(D_METHOD("aura_getc_count"), &Entity::aura_getc_count);
	ClassDB::bind_method(D_METHOD("aura_getc", "index"), &Entity::aura_getc);

	ClassDB::bind_method(D_METHOD("sauras_get"), &Entity::sauras_get);
	ClassDB::bind_method(D_METHOD("sauras_set", "data"), &Entity::sauras_set);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "sauras", PROPERTY_HINT_NONE, "17/17:AuraData", PROPERTY_USAGE_ENTITY_HIDDEN, "AuraData"), "sauras_set", "sauras_get");

	//Hooks
	BIND_VMETHOD(MethodInfo("_moved"));
	ClassDB::bind_method(D_METHOD("moved"), &Entity::moved);

	ADD_SIGNAL(MethodInfo("notification_cmouse_entered"));
	ADD_SIGNAL(MethodInfo("notification_cmouse_exited"));

	BIND_VMETHOD(MethodInfo("_notification_cmouse_enter"));
	BIND_VMETHOD(MethodInfo("_notification_cmouse_exit"));

	ClassDB::bind_method(D_METHOD("notification_cmouse_enter"), &Entity::notification_cmouse_enter);
	ClassDB::bind_method(D_METHOD("notification_cmouse_exit"), &Entity::notification_cmouse_exit);

	ADD_SIGNAL(MethodInfo("notification_ctargeted"));
	ADD_SIGNAL(MethodInfo("notification_cuntargeted"));

	BIND_VMETHOD(MethodInfo("_notification_ctargeted"));
	BIND_VMETHOD(MethodInfo("_notification_cuntargeted"));

	ClassDB::bind_method(D_METHOD("notification_ctargeted"), &Entity::notification_ctargeted);
	ClassDB::bind_method(D_METHOD("notification_cuntargeted"), &Entity::notification_cuntargeted);

	//Properties
	ClassDB::bind_method(D_METHOD("get_body_path"), &Entity::get_body_path);
	ClassDB::bind_method(D_METHOD("set_body_path", "value"), &Entity::set_body_path);
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "body_path"), "set_body_path", "get_body_path");

	ClassDB::bind_method(D_METHOD("get_character_skeleton_path"), &Entity::get_character_skeleton_path);
	ClassDB::bind_method(D_METHOD("set_character_skeleton_path", "value"), &Entity::set_character_skeleton_path);
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "character_skeleton_path"), "set_character_skeleton_path", "get_character_skeleton_path");

	ClassDB::bind_method(D_METHOD("gets_entity_data_id"), &Entity::gets_entity_data_id);
	ClassDB::bind_method(D_METHOD("sets_entity_data_id", "value"), &Entity::sets_entity_data_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "characterclass_id", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_ENTITY_HIDDEN), "sets_entity_data_id", "gets_entity_data_id");

	ClassDB::bind_method(D_METHOD("getc_entity_data_id"), &Entity::getc_entity_data_id);
	ClassDB::bind_method(D_METHOD("setc_entity_data_id", "value"), &Entity::setc_entity_data_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "entity_data_id", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_ENTITY_HIDDEN), "setc_entity_data_id", "getc_entity_data_id");

	ClassDB::bind_method(D_METHOD("gets_entity_player_type"), &Entity::gets_entity_player_type);
	ClassDB::bind_method(D_METHOD("sets_entity_player_type", "value"), &Entity::sets_entity_player_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "sentity_player_type", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_ENTITY_HIDDEN), "sets_entity_player_type", "gets_entity_player_type");

	ClassDB::bind_method(D_METHOD("getc_entity_player_type"), &Entity::getc_entity_player_type);
	ClassDB::bind_method(D_METHOD("setc_entity_player_type", "value"), &Entity::setc_entity_player_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "centity_player_type", PROPERTY_HINT_NONE, "", 0), "setc_entity_player_type", "getc_entity_player_type");

	ClassDB::bind_method(D_METHOD("gets_guid"), &Entity::gets_guid);
	ClassDB::bind_method(D_METHOD("sets_guid", "value"), &Entity::sets_guid);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "sguid", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_ENTITY_HIDDEN), "sets_guid", "gets_guid");

	ClassDB::bind_method(D_METHOD("getc_guid"), &Entity::getc_guid);
	ClassDB::bind_method(D_METHOD("setc_guid", "value"), &Entity::setc_guid);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "cguid", PROPERTY_HINT_NONE, "", 0), "setc_guid", "getc_guid");

	ClassDB::bind_method(D_METHOD("gets_entity_type"), &Entity::gets_entity_type);
	ClassDB::bind_method(D_METHOD("sets_entity_type", "value"), &Entity::sets_entity_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "sentity_type", PROPERTY_HINT_ENUM, "", PROPERTY_USAGE_ENTITY_HIDDEN), "sets_entity_type", "gets_entity_type");

	ClassDB::bind_method(D_METHOD("getc_entity_type"), &Entity::getc_entity_type);
	ClassDB::bind_method(D_METHOD("setc_entity_type", "value"), &Entity::sets_entity_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "centity_type", PROPERTY_HINT_ENUM, "", 0), "setc_entity_type", "getc_entity_type");

	ClassDB::bind_method(D_METHOD("gets_ai_state"), &Entity::gets_ai_state);
	ClassDB::bind_method(D_METHOD("sets_ai_state", "value"), &Entity::sets_ai_state);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "ai_state", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_AI_STATES, PROPERTY_USAGE_ENTITY_HIDDEN), "sets_ai_state", "gets_ai_state");

	ClassDB::bind_method(D_METHOD("gets_seed"), &Entity::gets_seed);
	ClassDB::bind_method(D_METHOD("sets_seed", "value"), &Entity::sets_seed);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "sseed", PROPERTY_HINT_ENUM, "", PROPERTY_USAGE_ENTITY_HIDDEN), "sets_seed", "gets_seed");

	ClassDB::bind_method(D_METHOD("getc_seed"), &Entity::getc_seed);
	ClassDB::bind_method(D_METHOD("setc_seed", "value"), &Entity::setc_seed);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "cseed", PROPERTY_HINT_NONE, "", 0), "setc_seed", "getc_seed");

	//Interaction type
	BIND_VMETHOD(MethodInfo("_gets_relation_to", PropertyInfo(Variant::OBJECT, "to", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	BIND_VMETHOD(MethodInfo("_getc_relation_to", PropertyInfo(Variant::OBJECT, "to", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	ClassDB::bind_method(D_METHOD("gets_relation_to", "to"), &Entity::gets_relation_to_bind);
	ClassDB::bind_method(D_METHOD("_gets_relation_to", "to"), &Entity::_gets_relation_to);

	ClassDB::bind_method(D_METHOD("getc_relation_to", "to"), &Entity::getc_relation_to_bind);
	ClassDB::bind_method(D_METHOD("_getc_relation_to", "to"), &Entity::_getc_relation_to);

	ClassDB::bind_method(D_METHOD("gets_entity_interaction_type"), &Entity::gets_entity_interaction_type);
	ClassDB::bind_method(D_METHOD("sets_entity_interaction_type", "value"), &Entity::sets_entity_interaction_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "sentity_interaction_type", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_ENTITY_INTERACTION_TYPE, PROPERTY_USAGE_ENTITY_HIDDEN), "sets_entity_interaction_type", "gets_entity_interaction_type");

	ClassDB::bind_method(D_METHOD("getc_entity_interaction_type"), &Entity::getc_entity_interaction_type);
	ClassDB::bind_method(D_METHOD("setc_entity_interaction_type", "value"), &Entity::setc_entity_interaction_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "centity_interaction_type", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_ENTITY_INTERACTION_TYPE, 0), "setc_entity_interaction_type", "getc_entity_interaction_type");

	ClassDB::bind_method(D_METHOD("gets_immunity_flags"), &Entity::gets_immunity_flags);
	ClassDB::bind_method(D_METHOD("sets_immunity_flags", "value"), &Entity::sets_immunity_flags);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "simmunity_flags", PROPERTY_HINT_FLAGS, EntityEnums::BINDING_STRING_ENTITY_IMMUNITY_FLAGS, PROPERTY_USAGE_ENTITY_HIDDEN), "sets_immunity_flags", "gets_immunity_flags");

	ClassDB::bind_method(D_METHOD("gets_entity_flags"), &Entity::gets_entity_flags);
	ClassDB::bind_method(D_METHOD("sets_entity_flags", "value"), &Entity::sets_entity_flags);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "sentity_flags", PROPERTY_HINT_FLAGS, EntityEnums::BINDING_STRING_ENTITY_FLAGS, PROPERTY_USAGE_ENTITY_HIDDEN), "sets_entity_flags", "gets_entity_flags");

	ClassDB::bind_method(D_METHOD("getc_entity_flags"), &Entity::getc_entity_flags);
	ClassDB::bind_method(D_METHOD("setc_entity_flags", "value"), &Entity::setc_entity_flags);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "centity_flags", PROPERTY_HINT_FLAGS, EntityEnums::BINDING_STRING_ENTITY_FLAGS, 0), "setc_entity_flags", "getc_entity_flags");

	ClassDB::bind_method(D_METHOD("gets_entity_name"), &Entity::gets_entity_name);
	ClassDB::bind_method(D_METHOD("sets_entity_name", "value"), &Entity::sets_entity_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "sentity_name"), "sets_entity_name", "gets_entity_name");

	ClassDB::bind_method(D_METHOD("getc_entity_name"), &Entity::getc_entity_name);
	ClassDB::bind_method(D_METHOD("setc_entity_name", "value"), &Entity::setc_entity_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "centity_name", PROPERTY_HINT_NONE, "", 0), "setc_entity_name", "getc_entity_name");

	ClassDB::bind_method(D_METHOD("gets_model_index"), &Entity::gets_model_index);
	ClassDB::bind_method(D_METHOD("sets_model_index", "value"), &Entity::sets_model_index);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "smodel_index", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_ENTITY_HIDDEN), "sets_model_index", "gets_model_index");

	ClassDB::bind_method(D_METHOD("getc_model_index"), &Entity::getc_model_index);
	ClassDB::bind_method(D_METHOD("setc_model_index", "value"), &Entity::setc_model_index);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "cmodel_index", PROPERTY_HINT_NONE, "", 0), "setc_model_index", "getc_model_index");

	ClassDB::bind_method(D_METHOD("gets_level"), &Entity::gets_level);
	ClassDB::bind_method(D_METHOD("sets_level", "value"), &Entity::sets_level);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "slevel"), "sets_level", "gets_level");

	ClassDB::bind_method(D_METHOD("getc_level"), &Entity::getc_level);
	ClassDB::bind_method(D_METHOD("setc_level", "value"), &Entity::setc_level);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "clevel", PROPERTY_HINT_NONE, "", 0), "setc_level", "getc_level");

	ClassDB::bind_method(D_METHOD("gets_xp"), &Entity::gets_xp);
	ClassDB::bind_method(D_METHOD("sets_xp", "value"), &Entity::sets_xp);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "sxp", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_ENTITY_HIDDEN), "sets_xp", "gets_xp");

	ClassDB::bind_method(D_METHOD("getc_xp"), &Entity::getc_xp);
	ClassDB::bind_method(D_METHOD("setc_xp", "value"), &Entity::setc_xp);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "cxp", PROPERTY_HINT_NONE, "", 0), "setc_xp", "getc_xp");

	ClassDB::bind_method(D_METHOD("gets_money"), &Entity::gets_money);
	ClassDB::bind_method(D_METHOD("sets_money", "value"), &Entity::sets_money);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "smoney"), "sets_money", "gets_money");

	ClassDB::bind_method(D_METHOD("getc_money"), &Entity::getc_money);
	ClassDB::bind_method(D_METHOD("setc_money", "value"), &Entity::setc_money);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "cmoney", PROPERTY_HINT_NONE, "", 0), "setc_money", "getc_money");

	ClassDB::bind_method(D_METHOD("gets_entity_data"), &Entity::gets_entity_data);
	ClassDB::bind_method(D_METHOD("sets_entity_data", "value"), &Entity::sets_entity_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "sentity_data", PROPERTY_HINT_RESOURCE_TYPE, "EntityData"), "sets_entity_data", "gets_entity_data");

	ClassDB::bind_method(D_METHOD("getc_entity_data"), &Entity::getc_entity_data);
	ClassDB::bind_method(D_METHOD("setc_entity_data", "value"), &Entity::setc_entity_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "centity_data", PROPERTY_HINT_RESOURCE_TYPE, "EntityData", 0), "setc_entity_data", "getc_entity_data");

	//todo
	//for (int i = 0; i < ESS::get_singleton()->stat_get_count(); ++i) {
	//	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "stats/" + itos(i), PROPERTY_HINT_RESOURCE_TYPE, "Stat"), "set_stat_int", "get_stat_int", i);
	//}

	//Equipment System

	ADD_SIGNAL(MethodInfo("equip_son_success", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));
	ADD_SIGNAL(MethodInfo("equip_son_fail", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));
	ADD_SIGNAL(MethodInfo("equip_con_success", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));
	ADD_SIGNAL(MethodInfo("equip_con_fail", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));

	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "ret"), "_equip_should_deny", PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));

	BIND_VMETHOD(MethodInfo("_equip_son_success", PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));
	BIND_VMETHOD(MethodInfo("_equip_son_fail", PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));
	BIND_VMETHOD(MethodInfo("_equip_con_success", PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));
	BIND_VMETHOD(MethodInfo("_equip_con_fail", PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::OBJECT, "old_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "bag_slot")));

	ADD_SIGNAL(MethodInfo("equipment_changed", PropertyInfo(Variant::INT, "slot")));

	ClassDB::bind_method(D_METHOD("equip_should_deny", "equip_slot", "item"), &Entity::equip_should_deny);

	ClassDB::bind_method(D_METHOD("equip_son_success", "equip_slot", "item", "old_item", "bag_slot"), &Entity::equip_son_success);
	ClassDB::bind_method(D_METHOD("equip_son_fail", "equip_slot", "item", "old_item", "bag_slot"), &Entity::equip_son_fail);
	ClassDB::bind_method(D_METHOD("equip_con_success", "equip_slot", "item", "old_item", "bag_slot"), &Entity::equip_con_success);
	ClassDB::bind_method(D_METHOD("equip_con_fail", "equip_slot", "item", "old_item", "bag_slot"), &Entity::equip_con_fail);

	BIND_VMETHOD(MethodInfo("_equips", PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::INT, "bag_slot")));

	ClassDB::bind_method(D_METHOD("equip_crequest", "equip_slot", "bag_slot"), &Entity::equip_crequest);
	ClassDB::bind_method(D_METHOD("equips", "equip_slot", "bag_slot"), &Entity::equips);
	ClassDB::bind_method(D_METHOD("_equips", "equip_slot", "bag_slot"), &Entity::_equips);

	ClassDB::bind_method(D_METHOD("equip_csuccess", "equip_slot", "bag_slot"), &Entity::equip_csuccess);
	ClassDB::bind_method(D_METHOD("equip_cfail", "equip_slot", "bag_slot"), &Entity::equip_cfail);

	ClassDB::bind_method(D_METHOD("equip_gets_slot", "index"), &Entity::equip_gets_slot);
	ClassDB::bind_method(D_METHOD("equip_getc_slot", "index"), &Entity::equip_getc_slot);

	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "can"), "_equip_can_equip_item", PropertyInfo(Variant::INT, "equip_slot"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));

	ClassDB::bind_method(D_METHOD("equip_can_equip_item", "equip_slot", "item"), &Entity::equip_can_equip_item);
	ClassDB::bind_method(D_METHOD("_equip_can_equip_item", "equip_slot", "item"), &Entity::_equip_can_equip_item);

	BIND_VMETHOD(MethodInfo("_equip_applys_item", PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));
	BIND_VMETHOD(MethodInfo("_equip_deapplys_item", PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));

	ClassDB::bind_method(D_METHOD("equip_applys_item", "item"), &Entity::equip_applys_item);
	ClassDB::bind_method(D_METHOD("equip_deapplys_item", "item"), &Entity::equip_deapplys_item);

	ClassDB::bind_method(D_METHOD("_equip_applys_item", "item"), &Entity::_equip_applys_item);
	ClassDB::bind_method(D_METHOD("_equip_deapplys_item", "item"), &Entity::_equip_deapplys_item);

	BIND_VMETHOD(MethodInfo("_equip_applyc_item", PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));
	BIND_VMETHOD(MethodInfo("_equip_deapplyc_item", PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));

	ClassDB::bind_method(D_METHOD("cequip_applys_item", "item"), &Entity::equip_applyc_item);
	ClassDB::bind_method(D_METHOD("equip_deapplyc_item", "item"), &Entity::equip_deapplyc_item);

	ClassDB::bind_method(D_METHOD("_equip_applyc_item", "item"), &Entity::_equip_applyc_item);
	ClassDB::bind_method(D_METHOD("_equip_deapplyc_item", "item"), &Entity::_equip_deapplyc_item);

	//Resources
	ClassDB::bind_method(D_METHOD("resource_gets_index", "index"), &Entity::resource_gets_index);
	ClassDB::bind_method(D_METHOD("resource_gets_id", "type"), &Entity::resource_gets_id);
	ClassDB::bind_method(D_METHOD("resource_adds", "palyer_resource"), &Entity::resource_adds);
	ClassDB::bind_method(D_METHOD("resource_gets_count"), &Entity::resource_gets_count);
	ClassDB::bind_method(D_METHOD("resource_removes", "index"), &Entity::resource_removes);
	ClassDB::bind_method(D_METHOD("resource_clears"), &Entity::resource_clears);

	ClassDB::bind_method(D_METHOD("resource_addc_rpc", "index", "data"), &Entity::resource_addc_rpc);

	ClassDB::bind_method(D_METHOD("resource_getc_index", "index"), &Entity::resource_getc_index);
	ClassDB::bind_method(D_METHOD("resource_getc_id", "type"), &Entity::resource_getc_id);
	ClassDB::bind_method(D_METHOD("resource_addc", "palyer_resource"), &Entity::resource_addc);
	ClassDB::bind_method(D_METHOD("resource_getc_count"), &Entity::resource_getc_count);
	ClassDB::bind_method(D_METHOD("resource_removec", "index"), &Entity::resource_removec);
	ClassDB::bind_method(D_METHOD("resource_clearc"), &Entity::resource_clearc);

	ClassDB::bind_method(D_METHOD("resource_sends_current", "index", "current"), &Entity::resource_sends_current);
	ClassDB::bind_method(D_METHOD("resource_sends_curr_max", "index", "current", "max"), &Entity::resource_sends_curr_max);
	ClassDB::bind_method(D_METHOD("resource_sends_data", "index", "data"), &Entity::resource_sends_data);

	ClassDB::bind_method(D_METHOD("resource_creceive_current", "index", "current"), &Entity::resource_creceive_current);
	ClassDB::bind_method(D_METHOD("resource_creceive_curr_max", "index", "current", "max"), &Entity::resource_creceive_curr_max);
	ClassDB::bind_method(D_METHOD("resource_creceive_data", "index", "data"), &Entity::resource_creceive_data);

	ClassDB::bind_method(D_METHOD("gets_health"), &Entity::gets_health);
	ClassDB::bind_method(D_METHOD("gets_speed"), &Entity::gets_speed);
	ClassDB::bind_method(D_METHOD("getc_health"), &Entity::getc_health);
	ClassDB::bind_method(D_METHOD("getc_speed"), &Entity::getc_speed);

	ClassDB::bind_method(D_METHOD("sresources_get"), &Entity::sresources_get);
	ClassDB::bind_method(D_METHOD("sresources_set", "caster_aura_applys"), &Entity::sresources_set);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "sresources", PROPERTY_HINT_NONE, "17/17:EntityResource", PROPERTY_USAGE_ENTITY_HIDDEN, "EntityResource"), "sresources_set", "sresources_get");

	//GCD
	ADD_SIGNAL(MethodInfo("sgcd_started", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::REAL, "value")));
	ADD_SIGNAL(MethodInfo("sgcd_finished", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	ADD_SIGNAL(MethodInfo("cgcd_started", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::REAL, "value")));
	ADD_SIGNAL(MethodInfo("cgcd_finished", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	ClassDB::bind_method(D_METHOD("gcd_hasc"), &Entity::gcd_hasc);
	ClassDB::bind_method(D_METHOD("gcd_hass"), &Entity::gcd_hass);

	ClassDB::bind_method(D_METHOD("gcd_getc"), &Entity::gcd_getc);
	ClassDB::bind_method(D_METHOD("gcd_setc", "value"), &Entity::gcd_setc);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "cgcd", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_ENTITY_HIDDEN), "gcd_setc", "gcd_getc");

	ClassDB::bind_method(D_METHOD("gcd_gets"), &Entity::gcd_gets);
	ClassDB::bind_method(D_METHOD("gcd_sets", "value"), &Entity::gcd_sets);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "sgcd", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_ENTITY_HIDDEN), "gcd_sets", "gcd_gets");

	ClassDB::bind_method(D_METHOD("gcd_starts", "value"), &Entity::gcd_starts);
	ClassDB::bind_method(D_METHOD("gcd_startc", "value"), &Entity::gcd_startc);

	//Data
	ClassDB::bind_method(D_METHOD("data_adds", "data"), &Entity::data_adds);
	ClassDB::bind_method(D_METHOD("data_removes", "index"), &Entity::data_removes);
	ClassDB::bind_method(D_METHOD("data_gets", "index"), &Entity::data_gets);
	ClassDB::bind_method(D_METHOD("data_gets_count"), &Entity::data_gets_count);

	ClassDB::bind_method(D_METHOD("data_addc", "data"), &Entity::data_addc);
	ClassDB::bind_method(D_METHOD("data_removec", "index"), &Entity::data_removec);
	ClassDB::bind_method(D_METHOD("data_getc", "index"), &Entity::data_getc);
	ClassDB::bind_method(D_METHOD("data_getc_count"), &Entity::data_getc_count);

	ClassDB::bind_method(D_METHOD("sdatas_get"), &Entity::sdatas_get);
	ClassDB::bind_method(D_METHOD("sdatas_set", "data"), &Entity::sdatas_set);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "sdatas", PROPERTY_HINT_NONE, "17/17:EntityDataContainer", PROPERTY_USAGE_ENTITY_HIDDEN, "EntityDataContainer"), "sdatas_set", "sdatas_get");

	//States
	ADD_SIGNAL(MethodInfo("sstate_changed", PropertyInfo(Variant::INT, "value")));
	ADD_SIGNAL(MethodInfo("cstate_changed", PropertyInfo(Variant::INT, "value")));

	ClassDB::bind_method(D_METHOD("getc_state"), &Entity::getc_state);
	ClassDB::bind_method(D_METHOD("setc_state", "state"), &Entity::setc_state);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "cstate", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_ENTITY_HIDDEN), "setc_state", "getc_state");

	ClassDB::bind_method(D_METHOD("gets_state"), &Entity::gets_state);
	ClassDB::bind_method(D_METHOD("sets_state", "state"), &Entity::sets_state);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "sstate", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_ENTITY_HIDDEN), "sets_state", "gets_state");

	ClassDB::bind_method(D_METHOD("adds_state_ref", "state_index"), &Entity::adds_state_ref);
	ClassDB::bind_method(D_METHOD("removes_state_ref", "state_index"), &Entity::removes_state_ref);

	ClassDB::bind_method(D_METHOD("states_gets"), &Entity::states_gets);
	ClassDB::bind_method(D_METHOD("states_sets", "state"), &Entity::states_sets);
	ADD_PROPERTY(PropertyInfo(Variant::POOL_INT_ARRAY, "sstates", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_ENTITY_HIDDEN), "states_sets", "states_gets");

	//Casting System

	ClassDB::bind_method(D_METHOD("cast_is_castings"), &Entity::cast_is_castings);
	ClassDB::bind_method(D_METHOD("cast_is_castingc"), &Entity::cast_is_castingc);

	ClassDB::bind_method(D_METHOD("spell_gets_cast_info"), &Entity::spell_gets_cast_info);
	ClassDB::bind_method(D_METHOD("sets_spell_cast_info", "value"), &Entity::sets_spell_cast_info);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "sspell_cast_info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo", PROPERTY_USAGE_ENTITY_HIDDEN), "sets_spell_cast_info", "spell_gets_cast_info");

	ClassDB::bind_method(D_METHOD("spell_getc_cast_info"), &Entity::spell_getc_cast_info);
	ClassDB::bind_method(D_METHOD("setc_spell_cast_info", "value"), &Entity::setc_spell_cast_info);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "cspell_cast_info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo", 0), "setc_spell_cast_info", "spell_getc_cast_info");

	ClassDB::bind_method(D_METHOD("cast_starts", "info"), &Entity::cast_starts);
	ClassDB::bind_method(D_METHOD("cast_fails"), &Entity::cast_fails);
	ClassDB::bind_method(D_METHOD("cast_delays"), &Entity::cast_delays);
	ClassDB::bind_method(D_METHOD("cast_finishs"), &Entity::cast_finishs);
	ClassDB::bind_method(D_METHOD("cast_interrupts"), &Entity::cast_interrupts);

	ClassDB::bind_method(D_METHOD("cast_startc_rpc", "data"), &Entity::cast_startc_rpc);
	ClassDB::bind_method(D_METHOD("cast_startc", "info"), &Entity::cast_startc);
	ClassDB::bind_method(D_METHOD("cast_failc"), &Entity::cast_failc);
	ClassDB::bind_method(D_METHOD("cast_delayc"), &Entity::cast_delayc);
	ClassDB::bind_method(D_METHOD("cast_finishc"), &Entity::cast_finishc);
	ClassDB::bind_method(D_METHOD("cast_interruptc"), &Entity::cast_interruptc);
	ClassDB::bind_method(D_METHOD("cast_spell_successs", "info"), &Entity::cast_spell_successs);

	//Cooldowns
	ADD_SIGNAL(MethodInfo("scooldown_added", PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));
	ADD_SIGNAL(MethodInfo("scooldown_removed", PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));
	ADD_SIGNAL(MethodInfo("ccooldown_added", PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));
	ADD_SIGNAL(MethodInfo("ccooldown_removed", PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));

	ClassDB::bind_method(D_METHOD("cooldown_hass", "spell_id"), &Entity::cooldown_hass);
	ClassDB::bind_method(D_METHOD("cooldown_adds", "spell_id", "value"), &Entity::cooldown_adds);
	ClassDB::bind_method(D_METHOD("cooldown_removes", "spell_id"), &Entity::cooldown_removes);
	ClassDB::bind_method(D_METHOD("cooldown_gets", "spell_id"), &Entity::cooldown_gets);
	ClassDB::bind_method(D_METHOD("cooldown_gets_index", "index"), &Entity::cooldown_gets_index);
	ClassDB::bind_method(D_METHOD("cooldown_gets_count"), &Entity::cooldown_gets_count);

	ClassDB::bind_method(D_METHOD("cooldown_hasc", "spell_id"), &Entity::cooldown_hasc);
	ClassDB::bind_method(D_METHOD("cooldown_addc", "spell_id", "value"), &Entity::cooldown_addc);
	ClassDB::bind_method(D_METHOD("cooldown_removec", "spell_id"), &Entity::cooldown_removec);
	ClassDB::bind_method(D_METHOD("cooldown_getc", "spell_id"), &Entity::cooldown_getc);
	ClassDB::bind_method(D_METHOD("cooldown_getc_index", "index"), &Entity::cooldown_getc_index);
	ClassDB::bind_method(D_METHOD("cooldown_getc_count"), &Entity::cooldown_getc_count);

	ClassDB::bind_method(D_METHOD("scooldowns_get"), &Entity::scooldowns_get);
	ClassDB::bind_method(D_METHOD("scooldowns_set", "data"), &Entity::scooldowns_set);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "scooldowns", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_ENTITY_HIDDEN), "scooldowns_set", "scooldowns_get");

	//Category Cooldowns
	ADD_SIGNAL(MethodInfo("scategory_cooldown_added", PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));
	ADD_SIGNAL(MethodInfo("scategory_cooldown_removed", PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));
	ADD_SIGNAL(MethodInfo("ccategory_cooldown_added", PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));
	ADD_SIGNAL(MethodInfo("ccategory_cooldown_removed", PropertyInfo(Variant::INT, "id"), PropertyInfo(Variant::REAL, "value")));

	ClassDB::bind_method(D_METHOD("category_cooldown_hass", "category_id"), &Entity::category_cooldown_hass);
	ClassDB::bind_method(D_METHOD("category_cooldown_adds", "category_id", "value"), &Entity::category_cooldown_adds);
	ClassDB::bind_method(D_METHOD("category_cooldown_removes", "category_id"), &Entity::category_cooldown_removes);
	ClassDB::bind_method(D_METHOD("category_cooldown_gets", "category_id"), &Entity::category_cooldown_gets);
	ClassDB::bind_method(D_METHOD("category_cooldown_gets_index", "index"), &Entity::category_cooldown_gets_index);
	ClassDB::bind_method(D_METHOD("category_cooldown_gets_count"), &Entity::category_cooldown_gets_count);

	ClassDB::bind_method(D_METHOD("category_cooldown_hasc", "category_id"), &Entity::category_cooldown_hasc);
	ClassDB::bind_method(D_METHOD("category_cooldown_addc", "category_id", "value"), &Entity::category_cooldown_addc);
	ClassDB::bind_method(D_METHOD("category_cooldown_removec", "category_id"), &Entity::category_cooldown_removec);
	ClassDB::bind_method(D_METHOD("category_cooldown_getc", "category_id"), &Entity::category_cooldown_getc);
	ClassDB::bind_method(D_METHOD("category_cooldown_getc_index", "index"), &Entity::category_cooldown_getc_index);
	ClassDB::bind_method(D_METHOD("category_cooldown_getc_count"), &Entity::category_cooldown_getc_count);

	ClassDB::bind_method(D_METHOD("scategory_cooldowns_get"), &Entity::scategory_cooldowns_get);
	ClassDB::bind_method(D_METHOD("scategory_cooldowns_set", "data"), &Entity::scategory_cooldowns_set);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "scategory_cooldowns", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_ENTITY_HIDDEN), "scategory_cooldowns_set", "scategory_cooldowns_get");

	//Known Spells
	ADD_SIGNAL(MethodInfo("sspell_added", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "spell", PROPERTY_HINT_RESOURCE_TYPE, "Spell")));
	ADD_SIGNAL(MethodInfo("sspell_removed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "spell", PROPERTY_HINT_RESOURCE_TYPE, "Spell")));
	ADD_SIGNAL(MethodInfo("cspell_added", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "spell", PROPERTY_HINT_RESOURCE_TYPE, "Spell")));
	ADD_SIGNAL(MethodInfo("cspell_removed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "spell", PROPERTY_HINT_RESOURCE_TYPE, "Spell")));

	ADD_SIGNAL(MethodInfo("sfree_spell_points_changed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "new_value")));
	ADD_SIGNAL(MethodInfo("cfree_spell_points_changed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::INT, "new_value")));

	ClassDB::bind_method(D_METHOD("gets_free_spell_points"), &Entity::gets_free_spell_points);
	ClassDB::bind_method(D_METHOD("sets_free_spell_points", "value"), &Entity::sets_free_spell_points);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "sfree_spell_points", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_ENTITY_HIDDEN), "sets_free_spell_points", "gets_free_spell_points");

	ClassDB::bind_method(D_METHOD("getc_free_spell_points"), &Entity::getc_free_spell_points);
	ClassDB::bind_method(D_METHOD("setc_free_spell_points", "value"), &Entity::setc_free_spell_points);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "cfree_spell_points", PROPERTY_HINT_NONE, "", 0), "setc_free_spell_points", "getc_free_spell_points");

	ClassDB::bind_method(D_METHOD("spell_learn_requestc", "id"), &Entity::spell_learn_requestc);
	ClassDB::bind_method(D_METHOD("spell_learns", "id"), &Entity::spell_learns);

	ClassDB::bind_method(D_METHOD("spell_hass", "spell"), &Entity::spell_hass);
	ClassDB::bind_method(D_METHOD("spell_hass_id", "id"), &Entity::spell_hass_id);
	ClassDB::bind_method(D_METHOD("spell_adds", "spell"), &Entity::spell_adds);
	ClassDB::bind_method(D_METHOD("spell_adds_id", "id"), &Entity::spell_adds_id);
	ClassDB::bind_method(D_METHOD("spell_removes", "spell"), &Entity::spell_removes);
	ClassDB::bind_method(D_METHOD("spell_gets", "spell"), &Entity::spell_gets);
	ClassDB::bind_method(D_METHOD("spell_gets_count"), &Entity::spell_gets_count);

	ClassDB::bind_method(D_METHOD("spell_hasc", "spell"), &Entity::spell_hasc);
	ClassDB::bind_method(D_METHOD("spell_hasc_id", "id"), &Entity::spell_hasc_id);
	ClassDB::bind_method(D_METHOD("spell_addc", "spell"), &Entity::spell_addc);
	ClassDB::bind_method(D_METHOD("spell_removec", "spell"), &Entity::spell_removec);
	ClassDB::bind_method(D_METHOD("spell_getc", "spell"), &Entity::spell_getc);
	ClassDB::bind_method(D_METHOD("spell_getc_count"), &Entity::spell_getc_count);

	ClassDB::bind_method(D_METHOD("spell_addc_rpc", "id"), &Entity::spell_addc_rpc);
	ClassDB::bind_method(D_METHOD("spell_removec_rpc", "id"), &Entity::spell_removec_rpc);

	ClassDB::bind_method(D_METHOD("sspells_get"), &Entity::sspells_get);
	ClassDB::bind_method(D_METHOD("sspells_set", "data"), &Entity::sspells_set);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "sspells", PROPERTY_HINT_NONE, "17/17:Spell", PROPERTY_USAGE_ENTITY_HIDDEN, "Spell"), "sspells_set", "sspells_get");

	//Crafting
	BIND_VMETHOD(MethodInfo("_crafts", PropertyInfo(Variant::INT, "id")));

	ADD_SIGNAL(MethodInfo("crafts_success", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));
	ADD_SIGNAL(MethodInfo("ccraft_success", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));

	ADD_SIGNAL(MethodInfo("crafts_recipe_added", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "craft_recipe", PROPERTY_HINT_RESOURCE_TYPE, "CraftRecipe")));
	ADD_SIGNAL(MethodInfo("ccraft_recipe_added", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "craft_recipe", PROPERTY_HINT_RESOURCE_TYPE, "CraftRecipe")));

	ClassDB::bind_method(D_METHOD("craft_crequest", "id"), &Entity::craft_crequest);
	ClassDB::bind_method(D_METHOD("crafts", "id"), &Entity::crafts);

	ClassDB::bind_method(D_METHOD("craft_hass_recipe", "craft_recipe"), &Entity::craft_hass_recipe);
	ClassDB::bind_method(D_METHOD("craft_hass_recipe_id", "id"), &Entity::craft_hass_recipe_id);
	ClassDB::bind_method(D_METHOD("craft_adds_recipe", "craft_recipe"), &Entity::craft_adds_recipe);
	ClassDB::bind_method(D_METHOD("craft_adds_recipe_id", "id"), &Entity::craft_adds_recipe_id);
	ClassDB::bind_method(D_METHOD("craft_removes_recipe", "craft_recipe"), &Entity::craft_removes_recipe);
	ClassDB::bind_method(D_METHOD("craft_removes_recipe_id", "id"), &Entity::craft_removes_recipe_id);
	ClassDB::bind_method(D_METHOD("craft_gets_recipe", "index"), &Entity::craft_gets_recipe);
	ClassDB::bind_method(D_METHOD("craft_gets_recipe_id", "id"), &Entity::craft_gets_recipe_id);
	ClassDB::bind_method(D_METHOD("craft_gets_recipe_count"), &Entity::craft_gets_recipe_count);

	ClassDB::bind_method(D_METHOD("craft_hasc_recipe", "craft_recipe"), &Entity::craft_hasc_recipe);
	ClassDB::bind_method(D_METHOD("craft_hasc_recipe_id", "id"), &Entity::craft_hasc_recipe_id);
	ClassDB::bind_method(D_METHOD("craft_addc_recipe", "craft_recipe"), &Entity::craft_addc_recipe);
	ClassDB::bind_method(D_METHOD("craft_addc_recipe_id", "id"), &Entity::craft_addc_recipe_id);
	ClassDB::bind_method(D_METHOD("craft_removec_recipe", "craft_recipe"), &Entity::craft_removec_recipe);
	ClassDB::bind_method(D_METHOD("craft_removec_recipe_id", "id"), &Entity::craft_removec_recipe_id);
	ClassDB::bind_method(D_METHOD("craft_getc_recipe", "craft_recipe"), &Entity::craft_getc_recipe);
	ClassDB::bind_method(D_METHOD("craft_getc_recipe_count"), &Entity::craft_getc_recipe_count);

	ClassDB::bind_method(D_METHOD("scraft_recipes_get"), &Entity::scraft_recipes_get);
	ClassDB::bind_method(D_METHOD("scraft_recipes_set", "caster_aura_applys"), &Entity::scraft_recipes_set);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "scraft_recipes", PROPERTY_HINT_NONE, "17/17:CraftRecipe", PROPERTY_USAGE_ENTITY_HIDDEN, "CraftRecipe"), "scraft_recipes_set", "scraft_recipes_get");

	//Skills
	ClassDB::bind_method(D_METHOD("skill_hass_id", "id"), &Entity::skill_hass_id);
	ClassDB::bind_method(D_METHOD("skill_hass", "skill"), &Entity::skill_hass);
	ClassDB::bind_method(D_METHOD("skill_adds", "skill"), &Entity::skill_adds);
	ClassDB::bind_method(D_METHOD("skill_removes", "skill"), &Entity::skill_removes);
	ClassDB::bind_method(D_METHOD("skill_gets", "skill"), &Entity::skill_gets);
	ClassDB::bind_method(D_METHOD("skill_gets_count"), &Entity::skill_gets_count);

	ClassDB::bind_method(D_METHOD("skill_hasc_id", "id"), &Entity::skill_hasc_id);
	ClassDB::bind_method(D_METHOD("skill_hasc", "skill"), &Entity::skill_hasc);
	ClassDB::bind_method(D_METHOD("skill_addc", "skill"), &Entity::skill_addc);
	ClassDB::bind_method(D_METHOD("skill_removec", "skill"), &Entity::skill_removec);
	ClassDB::bind_method(D_METHOD("skill_getc", "skill"), &Entity::skill_getc);
	ClassDB::bind_method(D_METHOD("skill_getc_count"), &Entity::skill_getc_count);

	ClassDB::bind_method(D_METHOD("skill_addc_id", "skill_id", "value", "max_value"), &Entity::skill_addc_id);
	ClassDB::bind_method(D_METHOD("skill_removec_id", "skill_id"), &Entity::skill_removec_id);
	ClassDB::bind_method(D_METHOD("skill_changec", "skill_id", "value"), &Entity::skill_changec);
	ClassDB::bind_method(D_METHOD("skill_changec_max", "skill_id", "value"), &Entity::skill_changec_max);

	ClassDB::bind_method(D_METHOD("sskills_get"), &Entity::sskills_get);
	ClassDB::bind_method(D_METHOD("sskills_set", "data"), &Entity::sskills_set);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "sskills", PROPERTY_HINT_NONE, "17/17:EntitySkill", PROPERTY_USAGE_ENTITY_HIDDEN, "EntitySkill"), "sskills_set", "sskills_get");

	//skeleton
	ClassDB::bind_method(D_METHOD("get_body"), &Entity::get_body);
	ClassDB::bind_method(D_METHOD("get_body_3d"), &Entity::get_body_3d);
	ClassDB::bind_method(D_METHOD("get_body_2d"), &Entity::get_body_2d);
	ClassDB::bind_method(D_METHOD("set_body", "body"), &Entity::set_body);
	ClassDB::bind_method(D_METHOD("get_character_skeleton"), &Entity::get_character_skeleton);
	ClassDB::bind_method(D_METHOD("set_character_skeleton", "skeleton"), &Entity::set_character_skeleton);

	ClassDB::bind_method(D_METHOD("instance_body"), &Entity::instance_body);
	ClassDB::bind_method(D_METHOD("on_body_changed"), &Entity::on_body_changed);

	BIND_VMETHOD(MethodInfo("_body_changed"));
	ADD_SIGNAL(MethodInfo("body_changed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	//Transforms
	ClassDB::bind_method(D_METHOD("get_transform_3d", "only_stored"), &Entity::get_transform_3d, DEFVAL(false));
	ClassDB::bind_method(D_METHOD("set_transform_3d", "transform", "only_stored"), &Entity::set_transform_3d, DEFVAL(false));

	ClassDB::bind_method(D_METHOD("get_transform_2d", "only_stored"), &Entity::get_transform_2d, DEFVAL(false));
	ClassDB::bind_method(D_METHOD("set_transform_2d", "transform", "only_stored"), &Entity::set_transform_2d, DEFVAL(false));

	////    Targeting System    ////

	ClassDB::bind_method(D_METHOD("target_crequest_change", "path"), &Entity::target_crequest_change);
	ClassDB::bind_method(D_METHOD("target_net_sets", "path"), &Entity::target_net_sets);
	ClassDB::bind_method(D_METHOD("target_net_setc", "path"), &Entity::target_net_setc);

	ClassDB::bind_method(D_METHOD("gets_target"), &Entity::gets_target);
	ClassDB::bind_method(D_METHOD("sets_target", "target"), &Entity::sets_target);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "starget", PROPERTY_HINT_RESOURCE_TYPE, "Entity", 0), "sets_target", "gets_target");

	ClassDB::bind_method(D_METHOD("getc_target"), &Entity::getc_target);
	ClassDB::bind_method(D_METHOD("setc_target", "target"), &Entity::setc_target);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ctarget", PROPERTY_HINT_RESOURCE_TYPE, "Entity", 0), "setc_target", "getc_target");

	////    Inventory System    ////

	ADD_SIGNAL(MethodInfo("sbag_changed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "bag", PROPERTY_HINT_RESOURCE_TYPE, "Bag")));
	ADD_SIGNAL(MethodInfo("cbag_changed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "bag", PROPERTY_HINT_RESOURCE_TYPE, "Bag")));

	ClassDB::bind_method(D_METHOD("gets_bag"), &Entity::gets_bag);
	ClassDB::bind_method(D_METHOD("sets_bag", "bag"), &Entity::sets_bag);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "sbag", PROPERTY_HINT_RESOURCE_TYPE, "Bag"), "sets_bag", "gets_bag");

	ClassDB::bind_method(D_METHOD("getc_bag"), &Entity::getc_bag);
	ClassDB::bind_method(D_METHOD("setc_bag", "bag"), &Entity::setc_bag);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "cbag", PROPERTY_HINT_RESOURCE_TYPE, "Bag", 0), "setc_bag", "getc_bag");

	ADD_SIGNAL(MethodInfo("starget_bag_changed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "bag", PROPERTY_HINT_RESOURCE_TYPE, "Bag")));
	ADD_SIGNAL(MethodInfo("ctarget_bag_changed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "bag", PROPERTY_HINT_RESOURCE_TYPE, "Bag")));

	ClassDB::bind_method(D_METHOD("gets_target_bag"), &Entity::gets_target_bag);
	ClassDB::bind_method(D_METHOD("sets_target_bag", "bag"), &Entity::sets_target_bag);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "starget_bag", PROPERTY_HINT_RESOURCE_TYPE, "Bag", PROPERTY_USAGE_ENTITY_HIDDEN), "sets_target_bag", "gets_target_bag");

	ClassDB::bind_method(D_METHOD("getc_target_bag"), &Entity::getc_target_bag);
	ClassDB::bind_method(D_METHOD("setc_target_bag", "bag"), &Entity::setc_target_bag);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ctarget_bag", PROPERTY_HINT_RESOURCE_TYPE, "Bag", 0), "setc_target_bag", "getc_target_bag");

	ClassDB::bind_method(D_METHOD("setc_bag_rpc", "data"), &Entity::setc_bag_rpc);
	ClassDB::bind_method(D_METHOD("setc_target_bag_rpc", "data"), &Entity::setc_target_bag_rpc);

	ClassDB::bind_method(D_METHOD("loot_crequest"), &Entity::loot_crequest);
	ClassDB::bind_method(D_METHOD("loots"), &Entity::loots);
	ClassDB::bind_method(D_METHOD("lootc"), &Entity::lootc);

	//Bag
	ClassDB::bind_method(D_METHOD("notification_item_sadded", "bag", "item", "slot_id"), &Entity::notification_item_sadded);
	ClassDB::bind_method(D_METHOD("item_addc_rpc", "slot_id", "item_data"), &Entity::item_addc_rpc);
	ClassDB::bind_method(D_METHOD("item_addc", "slot_id", "item"), &Entity::item_addc);

	ClassDB::bind_method(D_METHOD("notification_item_sremoved", "bag", "item", "slot_id"), &Entity::notification_item_sremoved);
	ClassDB::bind_method(D_METHOD("item_removes", "slot_id"), &Entity::item_removes);
	ClassDB::bind_method(D_METHOD("item_removec", "slot_id"), &Entity::item_removec);
	ClassDB::bind_method(D_METHOD("item_cdeny_remove", "slot_id"), &Entity::item_cdeny_remove);
	ClassDB::bind_method(D_METHOD("item_crequest_remove", "slot_id"), &Entity::item_crequest_remove);

	ClassDB::bind_method(D_METHOD("notification_items_sswapped", "bag", "slot_id_1", "slot_id_2"), &Entity::notification_items_sswapped);
	ClassDB::bind_method(D_METHOD("items_swaps", "slot_id_1", "slot_id_2"), &Entity::items_swaps);
	ClassDB::bind_method(D_METHOD("items_swapc", "slot_id_1", "slot_id_2"), &Entity::items_swapc);
	ClassDB::bind_method(D_METHOD("item_cdeny_swap", "slot_id_1", "slot_id_2"), &Entity::item_cdeny_swap);
	ClassDB::bind_method(D_METHOD("item_crequest_swap", "slot_id_1", "slot_id_2"), &Entity::item_crequest_swap);

	ClassDB::bind_method(D_METHOD("notification_item_sscount_changed", "bag", "item", "slot_id"), &Entity::notification_item_sscount_changed);
	ClassDB::bind_method(D_METHOD("item_cchange_count", "slot_id", "new_count"), &Entity::item_cchange_count);

	ClassDB::bind_method(D_METHOD("notification_soverburdened", "bag"), &Entity::notification_soverburdened);
	ClassDB::bind_method(D_METHOD("notification_soverburden_removed", "bag"), &Entity::notification_soverburden_removed);

	//target Bag
	ClassDB::bind_method(D_METHOD("notification_target_item_sadded", "bag", "item", "slot_id"), &Entity::notification_target_item_sadded);
	ClassDB::bind_method(D_METHOD("target_item_addc_rpc", "slot_id", "item_data"), &Entity::target_item_addc_rpc);
	ClassDB::bind_method(D_METHOD("target_item_addc", "slot_id", "item"), &Entity::target_item_addc);

	ClassDB::bind_method(D_METHOD("notification_target_item_sremoved", "bag", "item", "slot_id"), &Entity::notification_target_item_sremoved);
	ClassDB::bind_method(D_METHOD("target_item_removes", "slot_id"), &Entity::target_item_removes);
	ClassDB::bind_method(D_METHOD("target_item_removec", "slot_id"), &Entity::target_item_removec);
	ClassDB::bind_method(D_METHOD("target_item_cdeny_remove", "slot_id"), &Entity::target_item_cdeny_remove);
	ClassDB::bind_method(D_METHOD("target_remove_crequest_item", "slot_id"), &Entity::target_remove_crequest_item);

	ClassDB::bind_method(D_METHOD("notification_target_items_sswapped", "bag", "slot_id_1", "slot_id_2"), &Entity::notification_target_items_sswapped);
	ClassDB::bind_method(D_METHOD("target_items_sswap", "slot_id_1", "slot_id_2"), &Entity::target_items_sswap);
	ClassDB::bind_method(D_METHOD("target_items_cswap", "slot_id_1", "slot_id_2"), &Entity::target_items_cswap);
	ClassDB::bind_method(D_METHOD("target_item_cdeny_swap", "slot_id_1", "slot_id_2"), &Entity::target_item_cdeny_swap);
	ClassDB::bind_method(D_METHOD("target_item_crequest_swap", "slot_id_1", "slot_id_2"), &Entity::target_item_crequest_swap);

	ClassDB::bind_method(D_METHOD("notification_target_item_sscount_changed", "bag", "item", "slot_id"), &Entity::notification_target_item_sscount_changed);
	ClassDB::bind_method(D_METHOD("target_item_cchange_count", "slot_id", "new_count"), &Entity::target_item_cchange_count);

	//Vendors
	ClassDB::bind_method(D_METHOD("vendor_item_buy_crequest", "index", "count"), &Entity::vendor_item_buy_crequest);
	ClassDB::bind_method(D_METHOD("vendor_item_sbuy", "index", "count"), &Entity::vendor_item_sbuy);
	ClassDB::bind_method(D_METHOD("vendor_item_sell_crequest", "slot_id"), &Entity::vendor_item_sell_crequest);
	ClassDB::bind_method(D_METHOD("vendor_item_ssell", "slot_id"), &Entity::vendor_item_ssell);

	BIND_VMETHOD(MethodInfo("_vendor_item_sbuy", PropertyInfo(Variant::INT, "index"), PropertyInfo(Variant::INT, "count")));
	BIND_VMETHOD(MethodInfo("_vendor_item_ssell", PropertyInfo(Variant::INT, "slot_id")));

	ClassDB::bind_method(D_METHOD("_vendor_item_sbuy", "index", "count"), &Entity::_vendor_item_sbuy);
	ClassDB::bind_method(D_METHOD("_vendor_item_ssell", "slot_id"), &Entity::_vendor_item_ssell);

	//Actionbars

	ClassDB::bind_method(D_METHOD("get_actionbar_locked"), &Entity::get_actionbar_locked);
	ClassDB::bind_method(D_METHOD("set_actionbar_locked", "value"), &Entity::set_actionbar_locked);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "actionbar_locked", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_ENTITY_HIDDEN), "set_actionbar_locked", "get_actionbar_locked");

	ClassDB::bind_method(D_METHOD("get_action_bar_profile"), &Entity::get_action_bar_profile);

	//Pets

	ClassDB::bind_method(D_METHOD("pet_adds", "entity"), &Entity::pet_adds_bind);
	ClassDB::bind_method(D_METHOD("pet_gets", "index"), &Entity::pet_gets);
	ClassDB::bind_method(D_METHOD("pet_removes_index", "index"), &Entity::pet_removes_index);
	ClassDB::bind_method(D_METHOD("pet_removes", "entity"), &Entity::pet_removes_bind);
	ClassDB::bind_method(D_METHOD("pet_gets_count"), &Entity::pet_gets_count);

	ClassDB::bind_method(D_METHOD("pet_addc_path"), &Entity::pet_addc_path);

	ClassDB::bind_method(D_METHOD("pet_addc", "entity"), &Entity::pet_addc_bind);
	ClassDB::bind_method(D_METHOD("pet_getc", "index"), &Entity::pet_getc);
	ClassDB::bind_method(D_METHOD("pet_removec_index", "index"), &Entity::pet_removec_index);
	ClassDB::bind_method(D_METHOD("pet_removec", "entity"), &Entity::pet_removec_bind);
	ClassDB::bind_method(D_METHOD("pet_getc_count"), &Entity::pet_getc_count);

	//ClassDB::bind_method(D_METHOD("pets_attack"), &Entity::pets_attack);
	//ClassDB::bind_method(D_METHOD("pets_follow"), &Entity::pets_follow);
	//ClassDB::bind_method(D_METHOD("pets_stop"), &Entity::pets_stop);

	// AI

	ClassDB::bind_method(D_METHOD("gets_is_pet"), &Entity::gets_is_pet);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "sis_pet", PROPERTY_HINT_NONE, "", 0), "", "gets_is_pet");

	ClassDB::bind_method(D_METHOD("getc_is_pet"), &Entity::getc_is_pet);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "cis_pet", PROPERTY_HINT_NONE, "", 0), "", "getc_is_pet");

	ClassDB::bind_method(D_METHOD("pet_gets_owner"), &Entity::pet_gets_owner);
	ClassDB::bind_method(D_METHOD("pet_sets_owner", "entity"), &Entity::pet_sets_owner_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "spet_owner", PROPERTY_HINT_RESOURCE_TYPE, "Entity", 0), "pet_sets_owner", "pet_gets_owner");

	ClassDB::bind_method(D_METHOD("pet_gets_formation_index"), &Entity::pet_gets_formation_index);
	ClassDB::bind_method(D_METHOD("pet_sets_formation_index", "value"), &Entity::pet_sets_formation_index);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "spet_formation_index", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_ENTITY_HIDDEN), "pet_sets_formation_index", "pet_gets_formation_index");

	ClassDB::bind_method(D_METHOD("pet_gets_ai_state"), &Entity::pet_gets_ai_state);
	ClassDB::bind_method(D_METHOD("pet_sets_ai_state", "value"), &Entity::pet_sets_ai_state);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "pet_gets_ai_state", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_AI_STATES, PROPERTY_USAGE_ENTITY_HIDDEN), "pet_sets_ai_state", "pet_gets_ai_state");

	ClassDB::bind_method(D_METHOD("gets_original_entity_controller"), &Entity::gets_original_entity_controller);
	ClassDB::bind_method(D_METHOD("sets_original_entity_controller", "value"), &Entity::sets_original_entity_controller);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "soriginal_entity_controller", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_ENTITY_CONTOLLER, PROPERTY_USAGE_ENTITY_HIDDEN), "sets_original_entity_controller", "gets_original_entity_controller");

	ClassDB::bind_method(D_METHOD("gets_entity_controller"), &Entity::gets_entity_controller);
	ClassDB::bind_method(D_METHOD("sets_entity_controller", "value"), &Entity::sets_entity_controller);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "sentity_controller", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_ENTITY_CONTOLLER), "sets_entity_controller", "gets_entity_controller");

	ClassDB::bind_method(D_METHOD("getc_entity_controller"), &Entity::getc_entity_controller);
	ClassDB::bind_method(D_METHOD("setc_entity_controller", "value"), &Entity::setc_entity_controller);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "centity_controller", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_ENTITY_CONTOLLER), "setc_entity_controller", "getc_entity_controller");

	ADD_SIGNAL(MethodInfo("onc_entity_controller_changed"));

	ClassDB::bind_method(D_METHOD("getc_is_controlled"), &Entity::getc_is_controlled);

	ClassDB::bind_method(D_METHOD("gets_ai"), &Entity::gets_ai);
	ClassDB::bind_method(D_METHOD("sets_ai", "value"), &Entity::sets_ai);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "sai", PROPERTY_HINT_RESOURCE_TYPE, "EntityAI", PROPERTY_USAGE_ENTITY_HIDDEN), "sets_ai", "gets_ai");

	//Serialization
	BIND_VMETHOD(MethodInfo("_from_dict", PropertyInfo(Variant::DICTIONARY, "dict")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::DICTIONARY, "dict"), "_to_dict"));

	ClassDB::bind_method(D_METHOD("is_deserialized"), &Entity::is_deserialized);

	ClassDB::bind_method(D_METHOD("from_dict", "dict"), &Entity::from_dict);
	ClassDB::bind_method(D_METHOD("to_dict"), &Entity::to_dict);

	ClassDB::bind_method(D_METHOD("_from_dict", "dict"), &Entity::_from_dict);
	ClassDB::bind_method(D_METHOD("_to_dict"), &Entity::_to_dict);

	//Networking
	ClassDB::bind_method(D_METHOD("sees_gets", "index"), &Entity::sees_gets);
	ClassDB::bind_method(D_METHOD("sees_removes_index", "index"), &Entity::sees_removes_index);
	ClassDB::bind_method(D_METHOD("sees_removes", "entity"), &Entity::sees_removes_bind);
	ClassDB::bind_method(D_METHOD("sees_adds", "entity"), &Entity::sees_adds_bind);
	ClassDB::bind_method(D_METHOD("sees_gets_count"), &Entity::sees_gets_count);

	ClassDB::bind_method(D_METHOD("seen_by_gets", "index"), &Entity::seen_by_gets);
	ClassDB::bind_method(D_METHOD("seen_by_removes_index", "index"), &Entity::seen_by_removes_index);
	ClassDB::bind_method(D_METHOD("seen_by_removes", "entity"), &Entity::seen_by_removes_bind);
	ClassDB::bind_method(D_METHOD("seen_by_adds", "entity"), &Entity::seen_by_adds_bind);
	ClassDB::bind_method(D_METHOD("seen_by_gets_count"), &Entity::seen_by_gets_count);

	MethodInfo mi;

	mi.arguments.push_back(PropertyInfo(Variant::STRING, "method"));

	mi.name = "vrpc";
	ClassDB::bind_vararg_method(METHOD_FLAGS_DEFAULT, "vrpc", &Entity::_vrpc_bind, mi);

	ClassDB::bind_method(D_METHOD("register_for_physics_process", "info"), &Entity::register_for_physics_process);

	ClassDB::bind_method(D_METHOD("get_maunal_process"), &Entity::get_maunal_process);
	ClassDB::bind_method(D_METHOD("set_maunal_process", "value"), &Entity::set_maunal_process);

	ClassDB::bind_method(D_METHOD("update", "delta"), &Entity::update);

	ClassDB::bind_method(D_METHOD("_crafts", "id"), &Entity::_crafts);
	ClassDB::bind_method(D_METHOD("_notification_sxp_gained", "value"), &Entity::_notification_sxp_gained);
	ClassDB::bind_method(D_METHOD("_notification_slevel_up", "level"), &Entity::_notification_slevel_up);
	ClassDB::bind_method(D_METHOD("_moved"), &Entity::_moved);
	ClassDB::bind_method(D_METHOD("_con_target_changed", "entity", "old_target"), &Entity::_con_target_changed);
	ClassDB::bind_method(D_METHOD("_notification_sdeath"), &Entity::_notification_sdeath);
	ClassDB::bind_method(D_METHOD("_spell_learns", "id"), &Entity::_spell_learns);
}
