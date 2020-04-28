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

#ifndef ENTITY_H
#define ENTITY_H

#include "core/io/networked_multiplayer_peer.h"

#include "scene/main/node.h"

#include "../data/entities/xp_data.h"
#include "../data/items/craft_recipe.h"
#include "../data/items/item_instance.h"
#include "../data/spells/spell.h"
#include "./data/entity_data.h"
#include "core/hash_map.h"
#include "core/io/json.h"
#include "core/math/transform.h"
#include "core/math/transform_2d.h"
#include "core/object.h"
#include "core/ustring.h"
#include "core/vector.h"

#include "../data/spells/spell.h"
#include "./resources/entity_resource.h"
#include "stats/stat.h"

#include "../entity_enums.h"
#include "../utility/entity_create_info.h"

#include "../inventory/bag.h"
#include "../utility/category_cooldown.h"
#include "../utility/cooldown.h"
#include "./data/entity_data_container.h"

#include "../profiles/actionbar/action_bar_profile.h"
#include "../profiles/input/input_profile.h"

#include "./ai/entity_ai.h"

#include "../data/auras/aura_group.h"

#include "core/version.h"

class EntityData;
class AuraData;
class Spell;
class SpellDamageInfo;
class SpellHealInfo;
class SpellCastInfo;
class EntityCreateInfo;
class TalentRowData;
class CharacterSpec;
class EntitySkill;
class ClassProfile;
class Spatial;
class Node2D;

enum SpellCastDataSignals {
	CastFailed,
	StartCasting,
	CastFinished,
	SetTarget
};

VARIANT_ENUM_CAST(SpellCastDataSignals);

enum PlayerStates {
	STATE_FREEZE,
	STATE_NORMAL
};

VARIANT_ENUM_CAST(PlayerStates);

enum PlayerSendFlags {
	SEND_FLAG_NONE,
	SEND_FLAG_INVENTORY,
	SEND_FLAG_SPELL_DATA,
	SEND_FLAG_AURAS,
};

#define ISSERVER() (is_inside_tree() && (!get_tree()->has_network_peer() || (get_tree()->has_network_peer() && get_tree()->is_network_server())))
#define ISCLIENT() (is_inside_tree() && get_tree()->has_network_peer() && !get_tree()->is_network_server())

#define SET_RPC_OFF(p_method_name) rpc_config(p_method_name, MultiplayerAPI::RPC_MODE_DISABLED);
#define SET_RPC_REMOTE(p_method_name) rpc_config(p_method_name, MultiplayerAPI::RPC_MODE_REMOTE);
#define SET_RPC_MASTER(p_method_name) rpc_config(p_method_name, MultiplayerAPI::RPC_MODE_MASTER);
#define SET_RPC_PUPPET(p_method_name) rpc_config(p_method_name, MultiplayerAPI::RPC_MODE_PUPPET);
#define SET_RPC_REMOTESYNC(p_method_name) rpc_config(p_method_name, MultiplayerAPI::RPC_MODE_REMOTESYNC);
#define SET_RPC_MASTERSYNC(p_method_name) rpc_config(p_method_name, MultiplayerAPI::RPC_MODE_MASTERSYNC);
#define SET_RPC_PUPPETSYNC(p_method_name) rpc_config(p_method_name, MultiplayerAPI::RPC_MODE_PUPPETSYNC);

// f.e.   RPC(method, arg0, arg1, etc)
#define RPC(func, ...)                                        \
	if (is_inside_tree() && get_tree()->has_network_peer()) { \
		rpc(#func, ##__VA_ARGS__);                            \
	}                                                         \
	func(__VA_ARGS__);

#define VRPC(func, ...)                                       \
	if (is_inside_tree() && get_tree()->has_network_peer()) { \
		vrpc(#func, ##__VA_ARGS__);                           \
	}                                                         \
	func(__VA_ARGS__);

#define ORPC(func, ...)                                                   \
	if (is_inside_tree() && get_tree()->has_network_peer()) {             \
		if (get_tree()->is_network_server() && get_network_master() != 1) \
			rpc_id(get_network_master(), #func, ##__VA_ARGS__);           \
	}                                                                     \
	func(__VA_ARGS__);

#define RPCS(func, ...)                                       \
	if (is_inside_tree() && get_tree()->has_network_peer()) { \
		if (get_tree()->is_network_server()) {                \
			func(__VA_ARGS__);                                \
		} else {                                              \
			rpc_id(1, #func, ##__VA_ARGS__);                  \
		}                                                     \
	} else {                                                  \
		func(__VA_ARGS__);                                    \
	}

//RPC Objects

#define RPCOBJ(rpcfunc, rpc_var, normalfunc, normal_var)      \
	if (is_inside_tree() && get_tree()->has_network_peer()) { \
		rpc(#rpcfunc, rpc_var);                               \
	}                                                         \
	normalfunc(normal_var);

#define VRPCOBJ(rpcfunc, rpc_var, normalfunc, normal_var)     \
	if (is_inside_tree() && get_tree()->has_network_peer()) { \
		vrpc(#rpcfunc, rpc_var);                              \
	}                                                         \
	normalfunc(normal_var);

#define VRPCOBJ12(rpcfunc, rpc_var, normalfunc, normal_var1, normal_var2) \
	if (is_inside_tree() && get_tree()->has_network_peer()) {             \
		vrpc(#rpcfunc, rpc_var);                                          \
	}                                                                     \
	normalfunc(normal_var1, normal_var2);

#define VRPCOBJP(rpcfunc, rpc_var1, rpc_var2, normalfunc, normal_var1, normal_var2) \
	if (is_inside_tree() && get_tree()->has_network_peer()) {                       \
		vrpc(#rpcfunc, rpc_var1, rpc_var2);                                         \
	}                                                                               \
	normalfunc(normal_var1, normal_var2);

#define ORPCOBJ(rpcfunc, rpc_var, normalfunc, normal_var)                 \
	if (is_inside_tree() && get_tree()->has_network_peer()) {             \
		if (get_tree()->is_network_server() && get_network_master() != 1) \
			rpc_id(get_network_master(), #rpcfunc, rpc_var);              \
	}                                                                     \
	normalfunc(normal_var);

#define RPCSOBJ(rpcfunc, rpc_var, normalfunc, normal_var)     \
	if (is_inside_tree() && get_tree()->has_network_peer()) { \
		if (get_tree()->is_network_server()) {                \
			normalfunc(normal_var);                           \
		} else {                                              \
			rpc_id(1, #rpcfunc, rpc_var);                     \
		}                                                     \
	} else {                                                  \
		normalfunc(normal_var);                               \
	}

#define ORPCOBJP(rpcfunc, rpc_var1, rpc_var2, normalfunc, normal_var1, normal_var2) \
	if (is_inside_tree() && get_tree()->has_network_peer()) {                       \
		if (get_tree()->is_network_server() && get_network_master() != 1)           \
			rpc_id(get_network_master(), #rpcfunc, rpc_var1, rpc_var2);             \
	}                                                                               \
	normalfunc(normal_var1, normal_var2);

// f.e. RSET(rset("property", "value"), property, value)
#define RSET(rset_func, variable, value)                      \
	if (is_inside_tree() && get_tree()->has_network_peer()) { \
		rset_func;                                            \
	}                                                         \
	variable = value;

class Entity : public Node {
	GDCLASS(Entity, Node);

public:
	////    Base    ////

	NodePath get_body_path();
	void set_body_path(NodePath value);
	Node *get_body();
	Spatial *get_body_3d();
	Node2D *get_body_2d();
	void set_body(Node *body);

	NodePath get_character_skeleton_path();
	void set_character_skeleton_path(NodePath value);
	Node *get_character_skeleton();
	void set_character_skeleton(Node *skeleton);

	//Transforms
	Transform get_transform_3d(bool only_stored = false) const;
	void set_transform_3d(const Transform &transform, bool only_stored = false);

	Transform2D get_transform_2d(bool only_stored = false) const;
	void set_transform_2d(const Transform2D &transform, bool only_stored = false);

	//GUID
	int gets_guid();
	void sets_guid(int value);

	int getc_guid();
	void setc_guid(int value);

	//EntityPlayerType
	int gets_entity_player_type();
	void sets_entity_player_type(int value);

	int getc_entity_player_type();
	void setc_entity_player_type(int value);

	//EntityType
	EntityEnums::EntityType gets_entity_type();
	void sets_entity_type(EntityEnums::EntityType value);

	EntityEnums::EntityType getc_entity_type();
	void setc_entity_type(EntityEnums::EntityType value);

	//Relations
	EntityEnums::EntityRelationType gets_relation_to_bind(Node *to);
	EntityEnums::EntityRelationType gets_relation_to(Entity *to);

	EntityEnums::EntityRelationType _gets_relation_to(Node *to);

	EntityEnums::EntityRelationType getc_relation_to_bind(Node *to);
	EntityEnums::EntityRelationType getc_relation_to(Entity *to);

	EntityEnums::EntityRelationType _getc_relation_to(Node *to);

	//EntityInteractionType
	EntityEnums::EntityInteractionType gets_entity_interaction_type();
	void sets_entity_interaction_type(EntityEnums::EntityInteractionType value);

	EntityEnums::EntityInteractionType getc_entity_interaction_type();
	void setc_entity_interaction_type(EntityEnums::EntityInteractionType value);

	int gets_immunity_flags();
	void sets_immunity_flags(int value);

	int gets_entity_flags();
	void sets_entity_flags(int value);

	int getc_entity_flags();
	void setc_entity_flags(int value);

	String gets_entity_name();
	void sets_entity_name(String value);

	String getc_entity_name();
	void setc_entity_name(String value);

	EntityEnums::EntityGender gets_gender();
	void sets_gender(EntityEnums::EntityGender value);

	EntityEnums::EntityGender getc_gender();
	void setc_gender(EntityEnums::EntityGender value);

	int gets_class_level();
	void sets_class_level(int value);
	int getc_class_level();
	void setc_class_level(int value);

	int gets_character_level();
	void sets_character_level(int value);
	int getc_character_level();
	void setc_character_level(int value);

	int gets_class_xp();
	void sets_class_xp(int value);
	int getc_class_xp();
	void setc_class_xp(int value);

	int gets_character_xp();
	void sets_character_xp(int value);
	int getc_character_xp();
	void setc_character_xp(int value);

	int gets_money();
	void sets_money(int value);
	int getc_money();
	void setc_money(int value);

	Ref<EntityData> gets_entity_data();
	void sets_entity_data(Ref<EntityData> value);

	Ref<EntityData> getc_entity_data();
	void setc_entity_data(Ref<EntityData> value);

	int gets_entity_data_id();
	void sets_entity_data_id(int value);

	int getc_entity_data_id();
	void setc_entity_data_id(int value);

	StringName gets_entity_data_path();
	void sets_entity_data_path(const StringName &value);

	StringName getc_entity_data_path();
	void setc_entity_data_path(const StringName &value);

	EntityEnums::AIStates gets_ai_state() const;
	void sets_ai_state(EntityEnums::AIStates state);

	EntityEnums::AIStates gets_ai_state_stored() const;
	void sets_ai_state_stored(EntityEnums::AIStates state);

	int gets_seed();
	void sets_seed(int value);

	int getc_seed();
	void setc_seed(int value);

	////     Stats    ////
	Ref<Stat> get_stat(int index);
	void set_stat(int index, Ref<Stat> entry);

	void dies();
	void diec();

	void notification_sstat_changed(Ref<Stat> stat);
	void notification_cstat_changed(Ref<Stat> stat);

	void ssend_stat(int id, int ccurrent, int cmax);
	void creceive_stat(int id, int ccurrent, int cmax);

	////    Equip Slots    ////

	bool equip_should_deny(ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item);

	void equip_son_success(ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);
	void equip_son_fail(ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);

	void equip_con_success(ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);
	void equip_con_fail(ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);

	void equip_crequest(ItemEnums::EquipSlots equip_slot, int bag_slot);
	void equips(ItemEnums::EquipSlots equip_slot, int bag_slot);
	void _equips(ItemEnums::EquipSlots equip_slot, int bag_slot);

	void equip_csuccess(ItemEnums::EquipSlots equip_slot, int bag_slot);
	void equip_cfail(ItemEnums::EquipSlots equip_slot, int bag_slot);

	Ref<ItemInstance> equip_gets_slot(int index);
	void equip_sets_slot(int index, Ref<ItemInstance> item);

	Ref<ItemInstance> equip_getc_slot(int index);
	void equip_setc_slot(int index, Ref<ItemInstance> item);

	bool equip_can_equip_item(ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item);
	bool _equip_can_equip_item(ItemEnums::EquipSlots equip_slot, Ref<ItemInstance> item);

	void equip_applys_item(Ref<ItemInstance> item);
	void equip_deapplys_item(Ref<ItemInstance> item);

	void _equip_applys_item(Ref<ItemInstance> item);
	void _equip_deapplys_item(Ref<ItemInstance> item);

	void equip_applyc_item(Ref<ItemInstance> item);
	void equip_deapplyc_item(Ref<ItemInstance> item);

	void _equip_applyc_item(Ref<ItemInstance> item);
	void _equip_deapplyc_item(Ref<ItemInstance> item);

	////    Resources    ////

	Ref<EntityResource> resource_gets_index(int index);
	Ref<EntityResource> resource_gets_id(int id);
	void resource_adds(Ref<EntityResource> resource);
	int resource_gets_count();
	void resource_removes(int index);
	void resource_clears();

	Ref<EntityResource> resource_getc_index(int index);
	Ref<EntityResource> resource_getc_id(int id);
	void resource_addc(int index, Ref<EntityResource> resource);
	int resource_getc_count();
	void resource_removec(int index);
	void resource_clearc();

	void resource_addc_rpc(int index, String data);

	void resource_sends_current(int index, int current);
	void resource_sends_curr_max(int index, int current, int max);
	void resource_sends_data(int index, String data);

	void resource_creceive_current(int index, int current);
	void resource_creceive_curr_max(int index, int current, int max);
	void resource_creceive_data(int index, String data);

	Ref<EntityResource> gets_health();
	Ref<EntityResource> gets_speed();
	Ref<EntityResource> getc_health();
	Ref<EntityResource> getc_speed();

	////    Global Cooldown    ////

	bool gcd_hasc();
	bool gcd_hass();
	float gcd_getc();
	float gcd_gets();
	void gcd_starts(float value);
	void gcd_startc(float value);

	////    States    ////
	int getc_state();
	void setc_state(int state);

	int gets_state();
	void sets_state(int state);

	void adds_state_ref(int state_index);
	void removes_state_ref(int state_index);

	////    Crafting System    ////

	void craft_crequest(int id);
	void crafts(int id);

	bool craft_hass_recipe(Ref<CraftRecipe> craft_recipe);
	bool craft_hass_recipe_id(int id);
	void craft_adds_recipe(Ref<CraftRecipe> craft_recipe);
	void craft_adds_recipe_id(int id);
	void craft_removes_recipe(Ref<CraftRecipe> craft_recipe);
	void craft_removes_recipe_id(int id);
	Ref<CraftRecipe> craft_gets_recipe(int index);
	Ref<CraftRecipe> craft_gets_recipe_id(int id);
	int craft_gets_recipe_count();

	bool craft_hasc_recipe(Ref<CraftRecipe> craft_recipe);
	bool craft_hasc_recipe_id(int id);
	void craft_addc_recipe(Ref<CraftRecipe> craft_recipe);
	void craft_addc_recipe_id(int id);
	void craft_removec_recipe(Ref<CraftRecipe> craft_recipe);
	void craft_removec_recipe_id(int id);
	Ref<CraftRecipe> craft_getc_recipe(int index);
	int craft_getc_recipe_count();

	////    SpellSystem    ////

	//EventHandlers
	void notification_saura(int what, Ref<AuraData> data);
	void notification_sheal(int what, Ref<SpellHealInfo> info);
	void notification_scast(int what, Ref<SpellCastInfo> info);
	void notification_sdamage(int what, Ref<SpellDamageInfo> info);

	void notification_scooldown_added(Ref<Cooldown> cooldown);
	void notification_scooldown_removed(Ref<Cooldown> cooldown);

	void notification_scategory_cooldown_added(Ref<CategoryCooldown> category_cooldown);
	void notification_scategory_cooldown_removed(Ref<CategoryCooldown> category_cooldown);

	void notification_sentity_resource_added(Ref<EntityResource> resource);
	void notification_sentity_resource_removed(Ref<EntityResource> resource);

	void notification_sxp_gained(int value);
	void notification_sclass_level_up(int value);
	void notification_scharacter_level_up(int value);

	void notification_sdeath();

	void son_physics_process(float delta);

	//Clientside EventHandlers
	void notification_caura(int what, Ref<AuraData> data);
	void notification_cheal(int what, Ref<SpellHealInfo> info);
	void notification_ccast(int what, Ref<SpellCastInfo> info);
	void notification_cdamage(int what, Ref<SpellDamageInfo> info);

	void notification_ccooldown_added(Ref<Cooldown> cooldown);
	void notification_ccooldown_removed(Ref<Cooldown> cooldown);

	void notification_ccategory_cooldown_added(Ref<CategoryCooldown> category_cooldown);
	void notification_ccategory_cooldown_removed(Ref<CategoryCooldown> category_cooldown);

	void notification_centity_resource_added(Ref<EntityResource> resource);
	void notification_centity_resource_removed(Ref<EntityResource> resource);

	void notification_cxp_gained(int value);
	void notification_cclass_level_up(int value);
	void notification_ccharacter_level_up(int value);

	void notification_cdeath();

	//gcd
	void notification_sgcd_started();
	void notification_sgcd_finished();
	void notification_cgcd_started();
	void notification_cgcd_finished();

	//Modifiers/Requesters
	void sapply_passives_damage_receive(Ref<SpellDamageInfo> info);
	void sapply_passives_damage_deal(Ref<SpellDamageInfo> info);

	void sapply_passives_heal_receive(Ref<SpellHealInfo> info);
	void sapply_passives_heal_deal(Ref<SpellHealInfo> info);

	//Spell operations
	void spell_casts(int spell_id);
	void spell_crequest_cast(int spell_id);

	void item_uses(int item_id);
	void item_crequest_use(int item_id);
	void _item_uses(int item_id);

	//Damage Operations
	void stake_damage(Ref<SpellDamageInfo> info);
	void sdeal_damage_to(Ref<SpellDamageInfo> info);

	//Heal Operations
	void stake_heal(Ref<SpellHealInfo> info);
	void sdeal_heal_to(Ref<SpellHealInfo> info);

	//Damage, Heal RPCs
	void cdamage_dealt_rpc(String data);
	void cdealt_damage_rpc(String data);
	void cheal_dealt_rpc(String data);
	void cdealt_heal_rpc(String data);

	//Interactions
	bool cans_interact();
	void sinteract();

	bool canc_interact();
	void crequest_interact();

	void ssend_open_window(int window_id);
	void copen_window(int window_id);

	//XP Operations
	void xp_adds(int value);
	void xp_addc(int value);
	void levelup_sclass(int value);
	void levelup_cclass(int value);
	void levelup_scharacter(int value);
	void levelup_ccharacter(int value);

	//Aura Manipulation
	void aura_adds(Ref<AuraData> aura);
	void aura_removes(Ref<AuraData> aura);
	void aura_removes_exact(Ref<AuraData> aura);
	void aura_removes_expired(Ref<AuraData> aura);
	void aura_removes_dispelled(Ref<AuraData> aura);
	void aura_refresheds(Ref<AuraData> aura);

	void aura_addc_rpc(String data);
	void aura_removec_rpc(String data);
	void aura_removec_exact_rpc(String data);
	void aura_removec_expired_rpc(String data);
	void aura_removec_dispelled_rpc(String data);
	void aura_refreshedc_rpc(String data);

	void aura_addc(Ref<AuraData> aura);
	void aura_removec(Ref<AuraData> aura);
	void aura_removec_exact(Ref<AuraData> aura);
	void aura_removec_expired(Ref<AuraData> aura);
	void aura_removec_dispelled(Ref<AuraData> aura);
	void aura_refreshedc(Ref<AuraData> aura);

	void aura_removess_with_group(Ref<AuraGroup> aura_group);

	//NOTE: No reason for shas_aura_by, just query it, and check for null.
	int aura_gets_count();
	Ref<AuraData> aura_gets(int index);
	Ref<AuraData> aura_gets_by(Entity *caster, int aura_id);
	Ref<AuraData> aura_gets_by_bind(Node *caster, int aura_id);

	Ref<AuraData> aura_gets_with_group_by(Entity *caster, Ref<AuraGroup> aura_group);
	Ref<AuraData> aura_gets_with_group_by_bind(Node *caster, Ref<AuraGroup> aura_group);

	int aura_getc_count();
	Ref<AuraData> aura_getc(int index);

	//Hooks
	void moved();

	void notification_cmouse_enter();
	void notification_cmouse_exit();

	void notification_ctargeted();
	void notification_cuntargeted();

	//Update
	void update_auras(float delta);

	bool gets_is_dead();
	bool getc_is_dead();

	////    Casting System    ////

	bool cast_is_castings();
	bool cast_is_castingc();

	Ref<SpellCastInfo> spell_gets_cast_info();
	void sets_spell_cast_info(Ref<SpellCastInfo> info);

	Ref<SpellCastInfo> spell_getc_cast_info();
	void setc_spell_cast_info(Ref<SpellCastInfo> info);

	void cast_starts(Ref<SpellCastInfo> info);
	void cast_fails();
	void cast_delays();
	void cast_finishs();
	void cast_interrupts();

	void cast_startc_rpc(String data);
	void cast_startc(Ref<SpellCastInfo> info);
	void cast_failc();
	void cast_delayc();
	void cast_finishc();
	void cast_interruptc();

	void cast_spell_successs(Ref<SpellCastInfo> info);

	void cast_spell_successc_rpc(String data);
	void cast_spell_successc(Ref<SpellCastInfo> info);

	////    Cooldowns    ////

	Vector<Ref<Cooldown> > *cooldowns_gets();
	Vector<Ref<Cooldown> > *cooldowns_getc();

	HashMap<int, Ref<Cooldown> > *cooldown_get_maps();
	HashMap<int, Ref<Cooldown> > *cooldown_get_mapc();

	bool cooldown_hass(int spell_id);
	void cooldown_adds(int spell_id, float value);
	void cooldown_removes(int spell_id);
	Ref<Cooldown> cooldown_gets(int spell_id);
	Ref<Cooldown> cooldown_gets_index(int index);
	int cooldown_gets_count();

	bool cooldown_hasc(int spell_id);
	void cooldown_addc(int spell_id, float value);
	void cooldown_removec(int spell_id);
	Ref<Cooldown> cooldown_getc(int spell_id);
	Ref<Cooldown> cooldown_getc_index(int index);
	int cooldown_getc_count();

	//Category Cooldowns

	Vector<Ref<CategoryCooldown> > category_cooldowns_gets();
	Vector<Ref<CategoryCooldown> > category_cooldowns_getc();

	bool category_cooldown_hass(int category_id);
	void category_cooldown_adds(int category_id, float value);
	void category_cooldown_removes(int category_id);
	Ref<CategoryCooldown> category_cooldown_gets(int category_id);
	Ref<CategoryCooldown> category_cooldown_gets_index(int index);
	int category_cooldown_gets_count();

	bool category_cooldown_hasc(int category_id);
	void category_cooldown_addc(int category_id, float value);
	void category_cooldown_removec(int spell_id);
	Ref<CategoryCooldown> category_cooldown_getc(int category_id);
	Ref<CategoryCooldown> category_cooldown_getc_index(int index);
	int category_cooldown_getc_count();

	//Known Spells

	int gets_free_spell_points();
	void sets_free_spell_points(int value);

	int getc_free_spell_points();
	void setc_free_spell_points(int value);

	void spell_learn_requestc(int id);
	void spell_learns(int id);

	bool spell_hass(Ref<Spell> spell);
	bool spell_hass_id(int id);
	void spell_adds(Ref<Spell> spell);
	void spell_adds_id(int id);
	void spell_removes(Ref<Spell> spell);
	Ref<Spell> spell_gets(int index);
	int spell_gets_count();

	bool spell_hasc(Ref<Spell> spell);
	bool spell_hasc_id(int id);
	void spell_addc(Ref<Spell> spell);
	void spell_removec(Ref<Spell> spell);
	Ref<Spell> spell_getc(int index);
	int spell_getc_count();

	void spell_addc_rpc(int id);
	void spell_removec_rpc(int id);

	//Skills

	bool skill_hass_id(int id);
	bool skill_hass(Ref<EntitySkill> skill);
	void skill_adds(Ref<EntitySkill> skill);
	void skill_removes(Ref<EntitySkill> skill);
	Ref<EntitySkill> skill_gets(int skill);
	int skill_gets_count();

	bool skill_hasc_id(int id);
	bool skill_hasc(Ref<EntitySkill> skill);
	void skill_addc(Ref<EntitySkill> skill);
	void skill_removec(Ref<EntitySkill> skill);
	Ref<EntitySkill> skill_getc(int index);
	int skill_getc_count();

	void skill_scurrent_changed(Ref<EntitySkill> skill);
	void skill_smax_changed(Ref<EntitySkill> skill);

	void skill_addc_id(int skill_id, int value, int max_value);
	void skill_removec_id(int skill_id);
	void skill_changec(int skill_id, int value);
	void skill_changec_max(int skill_id, int value);

	////    Target    ////

	void target_crequest_change(NodePath path);
	void target_net_sets(NodePath path);
	void target_net_setc(NodePath path);

	Entity *gets_target();
	void sets_target(Node *p_target);

	Entity *getc_target();
	void setc_target(Node *p_target);

	////    Talents    ////

	int gets_free_talent_points();
	void sets_free_talent_points(int value);

	int getc_free_talent_points();
	void setc_free_talent_points(int value);

	void talent_crequest_learn(int spec_index, int talent_row, int talent_culomn);
	void talent_sreceive_learn_request(int spec_index, int talent_row, int talent_culomn);
	void _talent_sreceive_learn_request(int spec_index, int talent_row, int talent_culomn);

	void talent_crequest_reset();
	void talent_sreceive_reset_request();
	void _talent_sreceive_reset_request();

	void talent_sreset();
	void talent_creset();

	void talent_adds(int talent);
	void talent_removes(int talent);
	bool talent_hass(int talent);
	int talent_gets(int index);
	int talent_gets_count();
	void talents_sclear();

	void talent_addc(int talent);
	void talent_removec(int talent);
	bool talent_hasc(int talent);
	int talent_getc(int index);
	int talent_getc_count();
	void talent_cclear();

	////    Inventory    ////

	Ref<Bag> gets_bag() const;
	void sets_bag(const Ref<Bag> bag);

	Ref<Bag> getc_bag() const;
	void setc_bag(const Ref<Bag> bag);

	Ref<Bag> gets_target_bag() const;
	void sets_target_bag(const Ref<Bag> bag);

	Ref<Bag> getc_target_bag() const;
	void setc_target_bag(const Ref<Bag> bag);

	void setc_bag_rpc(String data);
	void setc_target_bag_rpc(String data);

	void loot_crequest(int index);
	void loots(int index);
	void lootc(int index);

	void item_addc_rpc(int slot_id, String item_data);
	void item_addc(int slot_id, Ref<ItemInstance> item);

	//Bag
	void item_removes(const int slot_id);
	void item_removec(const int slot_id);
	void item_cdeny_remove(const int slot_id);
	void item_crequest_remove(const int slot_id);

	void items_swaps(int slot_id_1, int slot_id_2);
	void items_swapc(int slot_id_1, int slot_id_2);
	void item_cdeny_swap(int slot_id_1, int slot_id_2);
	void item_crequest_swap(int slot_id_1, int slot_id_2);

	void item_cchange_count(int slot_id, int new_count);

	void notification_item_sadded(Ref<Bag> bag, Ref<ItemInstance> item, int slot_id);
	void notification_item_sremoved(Ref<Bag> bag, Ref<ItemInstance> item, int slot_id);
	void notification_items_sswapped(Ref<Bag> bag, int slot_id_1, int slot_id_2);
	void notification_item_sscount_changed(Ref<Bag> bag, Ref<ItemInstance> item, int slot_id);
	void notification_soverburdened(Ref<Bag> bag);
	void notification_soverburden_removed(Ref<Bag> bag);

	//Target Bag

	void target_item_addc_rpc(int slot_id, String item_data);
	void target_item_addc(int slot_id, Ref<ItemInstance> item);

	void target_item_removes(const int slot_id);
	void target_item_removec(const int slot_id);
	void target_item_cdeny_remove(const int slot_id);
	void target_remove_crequest_item(const int slot_id);

	void target_items_sswap(int slot_id_1, int slot_id_2);
	void target_items_cswap(int slot_id_1, int slot_id_2);
	void target_item_cdeny_swap(int slot_id_1, int slot_id_2);
	void target_item_crequest_swap(int slot_id_1, int slot_id_2);

	void target_item_cchange_count(int slot_id, int new_count);

	void notification_target_item_sadded(Ref<Bag> bag, Ref<ItemInstance> item, int slot_id);
	void notification_target_item_sremoved(Ref<Bag> bag, Ref<ItemInstance> item, int slot_id);
	void notification_target_items_sswapped(Ref<Bag> bag, int slot_id_1, int slot_id_2);
	void notification_target_item_sscount_changed(Ref<Bag> bag, Ref<ItemInstance> item, int slot_id);

	////    Data    ////

	void data_adds(Ref<EntityDataContainer> data);
	void data_removes(int index);
	Ref<EntityDataContainer> data_gets(int index);
	int data_gets_count();

	void data_addc(Ref<EntityDataContainer> data);
	void data_removec(int index);
	Ref<EntityDataContainer> data_getc(int index);
	int data_getc_count();

	////    Actionbars    ////

	bool get_actionbar_locked();
	void set_actionbar_locked(bool value);

	Ref<ActionBarProfile> get_action_bar_profile();

	void loaded();

	String random_name();

	void setup(Ref<EntityCreateInfo> info);
	virtual void _setup();
	void setup_actionbars();

	////    AI    ////

	bool gets_is_pet();
	bool getc_is_pet();

	Entity *pet_gets_owner();
	void pet_sets_owner(Entity *entity);
	void pet_sets_owner_bind(Node *entity);

	int pet_gets_formation_index();
	void pet_sets_formation_index(int value);

	EntityEnums::AIStates pet_gets_ai_state();
	void pet_sets_ai_state(EntityEnums::AIStates value);

	EntityEnums::EntityController gets_original_entity_controller();
	void sets_original_entity_controller(EntityEnums::EntityController value);

	EntityEnums::EntityController gets_entity_controller();
	void sets_entity_controller(EntityEnums::EntityController value);

	bool getc_is_controlled();
	void setc_is_controlled(bool value);

	Ref<EntityAI> gets_ai();
	void sets_ai(Ref<EntityAI> value);

	////    Pets    ////

	void pet_adds(Entity *entity);
	void pet_adds_bind(Node *entity);
	Entity *pet_gets(int index);
	void pet_removes_index(int index);
	void pet_removes(Entity *entity);
	void pet_removes_bind(Node *entity);
	int pet_gets_count();

	void pet_addc_path(NodePath path);

	void pet_addc(Entity *entity);
	void pet_addc_bind(Node *entity);
	Entity *pet_getc(int index);
	void pet_removec_index(int index);
	void pet_removec(Entity *entity);
	void pet_removec_bind(Node *entity);
	int pet_getc_count();

	//void pets_attack();
	//void pets_follow();
	//void pets_stop();

	////    Profiles    ////

	Ref<ClassProfile> get_class_profile();

	////    Serialization    ////

	bool is_deserialized();

	Dictionary to_dict();
	void from_dict(const Dictionary &dict);

	virtual Dictionary _to_dict();
	virtual void _from_dict(const Dictionary &dict);

	// Networking
	Entity *sees_gets(int index);
	void sees_removes_index(int index);
	void sees_removes(Entity *entity);
	void sees_removes_bind(Node *entity);
	void sees_adds(Entity *entity);
	void sees_adds_bind(Node *entity);
	int sees_gets_count();

	Entity *seen_by_gets(int index);
	void seen_by_removes_index(int index);
	void seen_by_removes(Entity *entity);
	void seen_by_removes_bind(Node *entity);
	void seen_by_adds(Entity *entity);
	void seen_by_adds_bind(Node *entity);
	int seen_by_gets_count();

	void vrpc(const StringName &p_method, VARIANT_ARG_LIST);
#if VERSION_MAJOR < 4
	Variant _vrpc_bind(const Variant **p_args, int p_argcount, Variant::CallError &r_error);
#else
	Variant _vrpc_bind(const Variant **p_args, int p_argcount, Callable::CallError &r_error);
#endif

	Dictionary data_as_dict(String &data);

	void register_for_physics_process(Ref<SpellCastInfo> info);

	bool get_maunal_process() const;
	void set_maunal_process(bool value);

	void update(float delta);

	Entity();
	~Entity();

protected:
	void _crafts(int id);
	void _notification_sxp_gained(int value);
	void _notification_scharacter_level_up(int level);
	void _notification_sclass_level_up(int level);
	void _moved();
	void _con_target_changed(Node *p_entity, Node *p_old_target);
	void _notification_sdeath();
	void _spell_learns(int id);

	bool _set(const StringName &p_name, const Variant &p_value);
	bool _get(const StringName &p_name, Variant &r_ret) const;
	void _get_property_list(List<PropertyInfo> *p_list) const;
	static void _bind_methods();
	virtual void _notification(int p_what);

private:
	bool _maunal_process;

	const float SAVE_BASE_SECONDS = 10.0;
	bool _deserialized;

	////    Paths    ////

	NodePath _body_path;
	Node *_body;
	Spatial *_body_3d;
	Node2D *_body_2d;

	NodePath _character_skeleton_path;
	Node *_character_skeleton;

	////    Transforms    ////

	Transform _transform;
	Transform2D _transform_2d;

	////    PlayerData    ////

	int _s_guid;
	int _c_guid;

	int _s_class_id;
	int _c_class_id;

	StringName _s_entity_data_path;

	int _s_entity_player_type;
	int _c_entity_player_type;

	int _s_type;
	int _c_type;

	EntityEnums::EntityGender _s_gender;
	EntityEnums::EntityGender _c_gender;

	int _s_class_level;
	int _c_class_level;

	int _s_character_level;
	int _c_character_level;

	int _s_class_xp;
	int _c_class_xp;

	int _s_character_xp;
	int _c_character_xp;

	int _s_money;
	int _c_money;

	Ref<EntityData> _s_entity_data;
	Ref<EntityData> _c_entity_data;

	int _s_send_flag;

	String _s_entity_name;
	String _c_entity_name;

	EntityEnums::EntityInteractionType _s_interaction_type;
	EntityEnums::EntityInteractionType _c_interaction_type;

	int _s_is_dead;
	int _c_is_dead;

	int _s_seed;
	int _c_seed;

	////     Stats    ////

	Vector<Ref<Stat> > _stats;

	////    Equipment    ////

	Ref<ItemInstance> _s_equipment[ItemEnums::EQUIP_SLOT_EQUIP_SLOT_MAX];
	Ref<ItemInstance> _c_equipment[ItemEnums::EQUIP_SLOT_EQUIP_SLOT_MAX];

	////    Resources    ////

	Vector<Ref<EntityResource> > _s_resources;
	Vector<Ref<EntityResource> > _c_resources;

	////    GCD    ////

	float _s_gcd;
	float _c_gcd;

	////    States    ////

	int _s_states[EntityEnums::ENTITY_STATE_TYPE_INDEX_MAX];

	int _s_state;
	int _c_state;

	////    SpellCastData    ////

	Ref<SpellCastInfo> _s_spell_cast_info;
	Ref<SpellCastInfo> _c_spell_cast_info;

	//// AuraComponent    ////

	Vector<Ref<AuraData> > _s_auras;
	Vector<Ref<AuraData> > _c_auras;

	EntityEnums::EntityType _s_entity_type;
	EntityEnums::EntityType _c_entity_type;

	int _s_immunity_flags;

	int _s_entity_flags;
	int _c_entity_flags;

	////    Cooldowns    ////
	Vector<Ref<Cooldown> > _s_cooldowns;
	Vector<Ref<Cooldown> > _c_cooldowns;

	HashMap<int, Ref<Cooldown> > _s_cooldown_map;
	HashMap<int, Ref<Cooldown> > _c_cooldown_map;

	Vector<Ref<CategoryCooldown> > _s_category_cooldowns;
	Vector<Ref<CategoryCooldown> > _c_category_cooldowns;

	int _s_active_category_cooldowns;
	int _c_active_category_cooldowns;

	////    Targeting    ////

	Entity *_s_target;
	Entity *_c_target;

	////    Talents    ////

	int _s_free_talent_points;
	int _c_free_talent_points;

	Vector<int> _s_talents;
	Vector<int> _c_talents;

	////    Data    ////

	Vector<Ref<EntityDataContainer> > _s_data;
	Vector<Ref<EntityDataContainer> > _c_data;

	////    Actionbars    ////

	bool _actionbar_locked;
	Ref<ActionBarProfile> _action_bar_profile;

	////    Crafting System    ////

	Vector<Ref<CraftRecipe> > _s_craft_recipes;
	Vector<Ref<CraftRecipe> > _c_craft_recipes;

	////    Known Spells    ////

	int _s_free_spell_points;
	int _c_free_spell_points;

	Vector<Ref<Spell> > _s_spells;
	Vector<Ref<Spell> > _c_spells;

	////    Skills    ////

	Vector<Ref<EntitySkill> > _s_skills;
	Vector<Ref<EntitySkill> > _c_skills;

	////    Stat Allocations    ////

	//int _unallocated_stats;
	//int _stat_allocations[ESS::get_instance()->stat_get_count()];

	////    Inventory    ////

	Ref<Bag> _s_bag;
	Ref<Bag> _c_bag;

	Ref<Bag> _s_target_bag;
	Ref<Bag> _c_target_bag;

	// AI

	EntityEnums::AIStates _sai_state;
	EntityEnums::AIStates _sai_state_stored;

	EntityEnums::EntityController _s_original_entity_controller;
	EntityEnums::EntityController _s_entity_controller;
	bool _c_is_controlled;
	Ref<EntityAI> _s_ai;

	//Pets

	Entity *_s_pet_owner;
	Entity *_c_pet_owner;

	int _s_pet_formation_index;

	EntityEnums::AIStates _s_pet_ai_state;

	Vector<Entity *> _s_pets;
	Vector<Entity *> _c_pets;

	// Networking

	Vector<Entity *> _s_sees;
	Vector<Entity *> _s_seen_by;

	// Callbacks

	Vector<Ref<SpellCastInfo> > _physics_process_scis;
};

#endif
