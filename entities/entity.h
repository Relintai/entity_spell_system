#ifndef ENTITY_H
#define ENTITY_H

#include "core/io/networked_multiplayer_peer.h"

#ifdef ENTITIES_2D
#include "scene/2d/physics_body_2d.h"
#else
#include "scene/3d/physics_body.h"
#endif

#include "../data/craft_recipe.h"
#include "../data/item_instance.h"
#include "../data/spell.h"
#include "../data/xp_data.h"
#include "./data/entity_data.h"
#include "core/hash_map.h"
#include "core/object.h"
#include "core/ustring.h"
#include "core/vector.h"

#include "entity_resource.h"
#include "../data/spell.h"
#include "stats/stat.h"

#include "../data/data_manager.h"
#include "../entity_enums.h"
#include "../skeleton/character_skeleton.h"
#include "../utility/entity_create_info.h"

#include "../utility/category_cooldown.h"
#include "../utility/cooldown.h"
#include "../inventory/bag.h"
#include "./data/entity_data_container.h"
#include "./skills/entity_skill.h"

class EntityData;
class AuraData;
class Spell;
class SpellDamageInfo;
class SpellHealInfo;
class SpellCastInfo;
class EntityCreateInfo;
class TalentRowData;
class CharacterSpec;

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

#define SET_RPC_OFF(p_method_name) rpc_config(p_method_name, MultiplayerAPI::RPC_MODE_DISABLED);
#define SET_RPC_REMOTE(p_method_name) rpc_config(p_method_name, MultiplayerAPI::RPC_MODE_REMOTE);
#define SET_RPC_MASTER(p_method_name) rpc_config(p_method_name, MultiplayerAPI::RPC_MODE_MASTER);
#define SET_RPC_PUPPET(p_method_name) rpc_config(p_method_name, MultiplayerAPI::RPC_MODE_PUPPET);
#define SET_RPC_REMOTESYNC(p_method_name) rpc_config(p_method_name, MultiplayerAPI::RPC_MODE_REMOTESYNC);
#define SET_RPC_MASTERSYNC(p_method_name) rpc_config(p_method_name, MultiplayerAPI::RPC_MODE_MASTERSYNC);
#define SET_RPC_PUPPETSYNC(p_method_name) rpc_config(p_method_name, MultiplayerAPI::RPC_MODE_PUPPETSYNC);

// f.e.   SEND_RPC(rpc("method", arg), method(arg))
#define SEND_RPC(rpc_func, normal_func)                                                                                                                                    \
	if (is_inside_tree() && get_tree()->has_network_peer() && get_tree()->get_network_peer()->get_connection_status() == NetworkedMultiplayerPeer::CONNECTION_CONNECTED) { \
		rpc_func;                                                                                                                                                          \
	}                                                                                                                                                                      \
	normal_func;

// f.e.   SEND_RPC_TO_SERVER(rpc_id(1, "method", arg), method(arg))
#define SEND_RPC_TO_SERVER(rpc_func, normal_func)                                                                                                                          \
	if (is_inside_tree() && get_tree()->has_network_peer() && get_tree()->get_network_peer()->get_connection_status() == NetworkedMultiplayerPeer::CONNECTION_CONNECTED) { \
		if (get_tree()->is_network_server())                                                                                                                               \
			normal_func;                                                                                                                                                   \
		else                                                                                                                                                               \
			rpc_func;                                                                                                                                                      \
	} else {                                                                                                                                                               \
		normal_func;                                                                                                                                                       \
	}

// f.e. SEND_RSET(rset("property", "value"), property, value)
#define SEND_RSET(rset_func, variable, value)                                                                                                                              \
	if (is_inside_tree() && get_tree()->has_network_peer() && get_tree()->get_network_peer()->get_connection_status() == NetworkedMultiplayerPeer::CONNECTION_CONNECTED) { \
		rset_func;                                                                                                                                                         \
	}                                                                                                                                                                      \
	variable = value;

#ifdef ENTITIES_2D
class Entity : public KinematicBody2D {
	GDCLASS(Entity, KinematicBody2D);

#else

class Entity : public KinematicBody {
	GDCLASS(Entity, KinematicBody);

#endif

public:
	void initialize(Ref<EntityCreateInfo> info);

	////    Base    ////

	NodePath get_character_skeleton_path();
	void set_character_skeleton_path(NodePath value);

	CharacterSkeleton *get_character_skeleton();

	int getc_guid();
	void setc_guid(int value);

	int gets_guid();
	void sets_guid(int value);

	int gets_entity_data_id();
	void sets_entity_data_id(int value);

	int getc_entity_data_id();
	void setc_entity_data_id(int value);

	//EntityType
	EntityEnums::EntityType gets_entity_type();
	void sets_entity_type(EntityEnums::EntityType value);

	EntityEnums::EntityType getc_entity_type();
	void setc_entity_type(EntityEnums::EntityType value);

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

	EntityEnums::EntityController gets_entity_controller();
	void sets_entity_controller(EntityEnums::EntityController value);

	String gets_entity_name();
	void sets_entity_name(String value);

	String getc_entity_name();
	void setc_entity_name(String value);

	int gets_gender();
	void sets_gender(int value);

	int getc_gender();
	void setc_gender(int value);

	int gets_level();
	void sets_level(int value);

	int getc_level();
	void setc_level(int value);

	int gets_xp();
	void sets_xp(int value);

	int getc_xp();
	void setc_xp(int value);

	int gets_money();
	void sets_money(int value);

	int getc_money();
	void setc_money(int value);

	Ref<EntityData> getc_entity_data();
	void setc_entity_data(Ref<EntityData> value);

	Ref<EntityData> gets_entity_data();
	void sets_entity_data(Ref<EntityData> value);

	void sinitialize_stats();

	void reward_xp_for_mob(int level);
	void level_up(int num = 1);
	void set_level_without_modifiers(int newLevel, bool a);
	void apply_level_modifiers();
	void rpc_level_up();
	void registers();

	////     Stats    ////

	_FORCE_INLINE_ Ref<Stat> get_health() { return _stats[Stat::STAT_ID_HEALTH]; }
	_FORCE_INLINE_ Ref<Stat> get_mana() { return _stats[Stat::STAT_ID_MANA]; }
	_FORCE_INLINE_ Ref<Stat> get_energy() { return _stats[Stat::STAT_ID_RAGE]; }
	_FORCE_INLINE_ Ref<Stat> get_rage() { return _stats[Stat::STAT_ID_ENERGY]; }
	_FORCE_INLINE_ Ref<Stat> get_speed() { return _stats[Stat::STAT_ID_SPEED]; }
	_FORCE_INLINE_ Ref<Stat> get_gcd() { return _stats[Stat::STAT_ID_GLOBAL_COOLDOWN]; }

	_FORCE_INLINE_ Ref<Stat> get_melee_crit() { return _stats[Stat::STAT_ID_MELEE_CRIT]; }
	_FORCE_INLINE_ Ref<Stat> get_melee_crit_bonus() { return _stats[Stat::STAT_ID_MELEE_CRIT_BONUS]; }
	_FORCE_INLINE_ Ref<Stat> get_spell_crit() { return _stats[Stat::STAT_ID_SPELL_CRIT]; }
	_FORCE_INLINE_ Ref<Stat> get_spell_crit_bonus() { return _stats[Stat::STAT_ID_SPELL_CRIT_BONUS]; }

	_FORCE_INLINE_ Ref<Stat> get_block() { return _stats[Stat::STAT_ID_BLOCK]; }
	_FORCE_INLINE_ Ref<Stat> get_parry() { return _stats[Stat::STAT_ID_PARRY]; }
	_FORCE_INLINE_ Ref<Stat> get_damage_reduction() { return _stats[Stat::STAT_ID_DAMAGE_REDUCTION]; }
	_FORCE_INLINE_ Ref<Stat> get_melee_damage_reduction() { return _stats[Stat::STAT_ID_MELEE_DAMAGE_REDUCTION]; }
	_FORCE_INLINE_ Ref<Stat> get_spell_damage_reduction() { return _stats[Stat::STAT_ID_SPELL_DAMAGE_REDUCTION]; }
	_FORCE_INLINE_ Ref<Stat> get_damage_taken() { return _stats[Stat::STAT_ID_DAMAGE_TAKEN]; }
	_FORCE_INLINE_ Ref<Stat> get_heal_taken() { return _stats[Stat::STAT_ID_HEAL_TAKEN]; }
	_FORCE_INLINE_ Ref<Stat> get_melee_damage() { return _stats[Stat::STAT_ID_MELEE_DAMAGE]; }
	_FORCE_INLINE_ Ref<Stat> get_spell_damage() { return _stats[Stat::STAT_ID_SPELL_DAMAGE]; }

	Ref<Stat> get_stat_int(int index);
	void set_stat_int(int index, Ref<Stat> entry);

	Ref<Stat> get_stat_enum(Stat::StatId stat_id);
	void set_stat_enum(Stat::StatId stat_id, Ref<Stat> entry);

	void sdie();
	void cdie();

	void ons_stat_changed(Ref<Stat> stat);
	void onc_stat_changed(Ref<Stat> stat);

	////    Equip Slots    ////

	Ref<ItemInstance> equip(Ref<ItemInstance> item);
	Ref<ItemInstance> get_equip_slot(int index);

	////    Resources    ////

	Ref<EntityResource> gets_resource(int index);
	Ref<EntityResource> gets_resource_type(int type);
	void adds_resource(Ref<EntityResource> resource);
	int gets_resource_count();
	void removes_resource(int index);
	void clears_resource();

	Ref<EntityResource> getc_resource(int index);
	Ref<EntityResource> getc_resource_type(int type);
	void addc_resource(Ref<EntityResource> resource);
	int getc_resource_count();
	void removec_resource(int index);
	void clearc_resource();

	////    Global Cooldown    ////

	bool getc_has_global_cooldown();
	bool gets_has_global_cooldown();
	bool getc_global_cooldown();
	bool gets_global_cooldown();
	void sstart_global_cooldown(float value);
	void cstart_global_cooldown(float value);

	////    States    ////
	int getc_state();
	void setc_state(int state);

	int gets_state();
	void sets_state(int state);

	void sadd_state_ref(int state_index);
	void sremove_state_ref(int state_index);

	////    SpellSystem    ////

	//EventHandlers
	void son_before_aura_applied(Ref<AuraData> data);
	void son_after_aura_applied(Ref<AuraData> data);

	void son_before_damage_hit(Ref<SpellDamageInfo> info);
	void son_hit(Ref<SpellDamageInfo> info);
	void son_before_damage(Ref<SpellDamageInfo> info);
	void son_damage_receive(Ref<SpellDamageInfo> info);
	void son_dealt_damage(Ref<SpellDamageInfo> info);
	void son_damage_dealt(Ref<SpellDamageInfo> info);

	void son_before_heal_hit(Ref<SpellHealInfo> info);
	void son_before_heal(Ref<SpellHealInfo> info);
	void son_heal_receive(Ref<SpellHealInfo> info);
	void son_dealt_heal(Ref<SpellHealInfo> info);
	void son_heal_dealt(Ref<SpellHealInfo> info);

	void son_before_cast(Ref<SpellCastInfo> info);
	void son_before_cast_target(Ref<SpellCastInfo> info);
	void son_cast_finished_target(Ref<SpellCastInfo> info);
	void son_cast_finished(Ref<SpellCastInfo> info);
	void son_cast_started(Ref<SpellCastInfo> info);
	void son_cast_failed(Ref<SpellCastInfo> info);
	void son_spell_cast_success(Ref<SpellCastInfo> info);

	void son_death();

	void son_cooldown_added(Ref<Cooldown> cooldown);
	void son_cooldown_removed(Ref<Cooldown> cooldown);

	void son_category_cooldown_added(Ref<CategoryCooldown> category_cooldown);
	void son_category_cooldown_removed(Ref<CategoryCooldown> category_cooldown);

	void son_gcd_started();
	void son_gcd_finished();
	void con_gcd_started();
	void con_gcd_finished();

	void son_physics_process();

	void son_xp_gained(int value);
	void son_level_up(int value);

	//Clientside EventHandlers
	void con_cast_failed(Ref<SpellCastInfo> info);
	void con_cast_started(Ref<SpellCastInfo> info);
	void con_cast_state_changed(Ref<SpellCastInfo> info);
	void con_cast_finished(Ref<SpellCastInfo> info);
	void con_spell_cast_success(Ref<SpellCastInfo> info);

	void con_death();

	void con_cooldown_added(Ref<Cooldown> cooldown);
	void con_cooldown_removed(Ref<Cooldown> cooldown);
	void con_category_cooldown_added(Ref<CategoryCooldown> category_cooldown);
	void con_category_cooldown_removed(Ref<CategoryCooldown> category_cooldown);

	void con_aura_added(Ref<AuraData> data);
	void con_aura_removed(Ref<AuraData> data);
	void con_aura_refresh(Ref<AuraData> data);

	void con_damage_dealt(Ref<SpellDamageInfo> info);
	void con_dealt_damage(Ref<SpellDamageInfo> info);
	void con_heal_dealt(Ref<SpellHealInfo> info);
	void con_dealt_heal(Ref<SpellHealInfo> info);

	void con_xp_gained(int value);
	void con_level_up(int value);

	//Modifiers/Requesters
	void sapply_passives_damage_receive(Ref<SpellDamageInfo> info);
	void sapply_passives_damage_deal(Ref<SpellDamageInfo> info);

	void sapply_passives_heal_receive(Ref<SpellHealInfo> info);
	void sapply_passives_heal_deal(Ref<SpellHealInfo> info);

	//Spell operations
	void scast_spell(int spell_id);
	void crequest_spell_cast(int spell_id);

	//Damage Operations
	void stake_damage(Ref<SpellDamageInfo> info);
	void sdeal_damage_to(Ref<SpellDamageInfo> info);

	//Heal Operations
	void stake_heal(Ref<SpellHealInfo> info);
	void sdeal_heal_to(Ref<SpellHealInfo> info);

	//Interactions
	bool cans_interact();
	void sinteract();

	bool canc_interact();
	void crequest_interact();

	void ssend_open_loot_window();
	void ssend_open_container_window();
	void ssend_open_vendor_window();

	void copen_loot_window();
	void copen_container_window();
	void copen_vendor_window();

	//XP Operations
	void adds_xp(int value);
	void addc_xp(int value);
	void s_levelup(int value);
	void c_levelup(int value);

	//Aura Manipulation
	void sadd_aura(Ref<AuraData> aura);
	void sremove_aura(Ref<AuraData> aura);
	void sremove_aura_exact(Ref<AuraData> aura);
	void sremove_aura_expired(Ref<AuraData> aura);
	void sremove_aura_dispelled(Ref<AuraData> aura);
	void saura_refreshed(Ref<AuraData> aura);

	void cadd_aura(Ref<AuraData> aura);
	void cremove_aura(Ref<AuraData> aura);
	void cremove_aura_exact(Ref<AuraData> aura);
	void cremove_aura_expired(Ref<AuraData> aura);
	void cremove_aura_dispelled(Ref<AuraData> aura);
	void caura_refreshed(Ref<AuraData> aura);

	void sremove_auras_with_group(int aura_group);

	//NOTE: No reason for shas_aura_by, just query it, and check for null.
	int sget_aura_count();
	Ref<AuraData> sget_aura(int index);
	Ref<AuraData> sget_aura_by(Entity *caster, int aura_id);
	Ref<AuraData> sget_aura_by_bind(Node *caster, int aura_id);

	int cget_aura_count();
	Ref<AuraData> cget_aura(int index);

	//Hooks
	void moved();

	void onc_mouse_enter();
	void onc_mouse_exit();

	void onc_targeted();
	void onc_untargeted();

	//Update
	void update_auras(float delta);

	//Old stuff, remove or update
	void resurrect();
	void creceive_resurrect();
	void creceive_mana_changed(int amount);
	bool gets_is_dead();
	bool getc_is_dead();

	////    Casting System    ////

	bool sis_casting();
	bool cis_casting();

	Ref<SpellCastInfo> gets_spell_cast_info();
	void sets_spell_cast_info(Ref<SpellCastInfo> info);

	Ref<SpellCastInfo> getc_spell_cast_info();
	void setc_spell_cast_info(Ref<SpellCastInfo> info);

	void sstart_casting(Ref<SpellCastInfo> info);
	void sfail_cast();
	void sdelay_cast();
	void sfinish_cast();
	void sinterrupt_cast();

	void cstart_casting(Ref<SpellCastInfo> info);
	void cfail_cast();
	void cdelay_cast();
	void cfinish_cast();
	void cinterrupt_cast();

	void sspell_cast_success(Ref<SpellCastInfo> info);
	void cspell_cast_success(Ref<SpellCastInfo> info);

	////    Cooldowns    ////

	Vector<Ref<Cooldown> > *gets_cooldowns();
	Vector<Ref<Cooldown> > *getc_cooldowns();

	HashMap<int, Ref<Cooldown> > *gets_cooldown_map();
	HashMap<int, Ref<Cooldown> > *getc_cooldown_map();

	bool hass_cooldown(int spell_id);
	void adds_cooldown(int spell_id, float value);
	void removes_cooldown(int spell_id);
	Ref<Cooldown> gets_cooldown(int spell_id);
	Ref<Cooldown> gets_cooldown_index(int index);
	int gets_cooldown_count();

	bool hasc_cooldown(int spell_id);
	void addc_cooldown(int spell_id, float value);
	void removec_cooldown(int spell_id);
	Ref<Cooldown> getc_cooldown(int spell_id);
	Ref<Cooldown> getc_cooldown_index(int index);
	int getc_cooldown_count();

	//Category Cooldowns

	Vector<Ref<CategoryCooldown> > gets_category_cooldowns();
	Vector<Ref<CategoryCooldown> > getc_category_cooldowns();

	bool hass_category_cooldown(int category_id);
	void adds_category_cooldown(int category_id, float value);
	void removes_category_cooldown(int category_id);
	Ref<CategoryCooldown> gets_category_cooldown(int category_id);
	Ref<CategoryCooldown> gets_category_cooldown_index(int index);
	int gets_category_cooldown_count();

	bool hasc_category_cooldown(int category_id);
	void addc_category_cooldown(int category_id, float value);
	void removec_category_cooldown(int spell_id);
	Ref<CategoryCooldown> getc_category_cooldown(int category_id);
	Ref<CategoryCooldown> getc_category_cooldown_index(int index);
	int getc_category_cooldown_count();

	//Known Spells

	int gets_free_spell_points();
	void sets_free_spell_points(int value);

	int getc_free_spell_points();
	void setc_free_spell_points(int value);

	bool hass_spell(Ref<Spell> spell);
	void adds_spell(Ref<Spell> spell);
	void removes_spell(Ref<Spell> spell);
	Ref<Spell> gets_spell(int index);
	int gets_spell_count();

	bool hasc_spell(Ref<Spell> spell);
	void addc_spell(Ref<Spell> spell);
	void removec_spell(Ref<Spell> spell);
	Ref<Spell> getc_spell(int index);
	int getc_spell_count();

	//Skills

	bool hass_skill(Ref<EntitySkill> skill);
	void adds_skill(Ref<EntitySkill> skill);
	void removes_skill(Ref<EntitySkill> skill);
	Ref<EntitySkill> gets_skill(int skill);
	int gets_skill_count();

	bool hasc_skill(Ref<EntitySkill> skill);
	void addc_skill(Ref<EntitySkill> skill);
	void removec_skill(Ref<EntitySkill> skill);
	Ref<EntitySkill> getc_skill(int index);
	int getc_skill_count();

	////    Target    ////

	void crequest_target_change(NodePath path);
	void net_sets_target(NodePath path);
	void net_setc_target(NodePath path);

	Entity *gets_target();
	void sets_target(Node *p_target);

	Entity *getc_target();
	void setc_target(Node *p_target);

	////    Talents    ////

	int gets_free_talent_points();
	void sets_free_talent_points(int value);

	int getc_free_talent_points();
	void setc_free_talent_points(int value);

	void crequest_talent_learn(int spec_index, int talent_row, int talent_culomn);
	void sreceive_talent_learn_request(int spec_index, int talent_row, int talent_culomn);
	void _sreceive_talent_learn_request(int spec_index, int talent_row, int talent_culomn);

	void crequest_talent_reset();
	void sreceive_reset_talent_request();
	void _sreceive_reset_talent_request();

	void sreset_talents();
	void creset_talents();

	void adds_talent(int talent);
	void removes_talent(int talent);
	bool hass_talent(int talent);
	int gets_talent(int index);
	int gets_talent_count();
	void sclear_talents();

	void addc_talent(int talent);
	void removec_talent(int talent);
	bool hasc_talent(int talent);
	int getc_talent(int index);
	int getc_talent_count();
	void cclear_talents();

	////    Inventory    ////

	Ref<Bag> gets_bag() const;
	Ref<Bag> getc_bag() const;

	void sets_bag(const Ref<Bag> bag);
	void setc_bag(const Ref<Bag> bag);

	Ref<Bag> gets_target_bag() const;
	void sets_target_bag(const Ref<Bag> bag);

	Ref<Bag> getc_target_bag() const;
	void setc_target_bag(const Ref<Bag> bag);

	void crequest_loot(int index);
	void sloot(int index);

	////    Data    ////

	void adds_data(Ref<EntityDataContainer> data);
	void removes_data(int index);
	Ref<EntityDataContainer> gets_data(int index);
	int gets_data_count();

	void addc_data(Ref<EntityDataContainer> data);
	void removec_data(int index);
	Ref<EntityDataContainer> getc_data(int index);
	int getc_data_count();

	void loaded();

	String random_name();

	void setup();
	virtual void _setup();

	Dictionary to_dict();
	void from_dict(const Dictionary &dict);

	virtual Dictionary _to_dict();
	virtual void _from_dict(const Dictionary &dict);

	Entity();
	~Entity();

protected:
	static void _bind_methods();
	virtual void _notification(int p_what);
	virtual void update(float delta);

private:
	const float SAVE_BASE_SECONDS = 10.0;

	////    Paths    ////

	NodePath _character_skeleton_path;
	CharacterSkeleton *_character_skeleton;

	////    PlayerData    ////

	int _s_guid;
	int _c_guid;

	int _s_class_id;
	int _c_class_id;

	int _s_type;
	int _c_type;

	int _s_gender;
	int _c_gender;

	int _s_level;
	int _c_level;

	int _s_xp;
	int _c_xp;

	int _s_money;
	int _c_money;

	Ref<EntityData> _s_entity_data;
	Ref<EntityData> _c_entity_data;

	int _s_send_flag;

	String _s_entity_name;
	String _c_entity_name;

	EntityEnums::EntityInteractionType _s_interaction_type;
	EntityEnums::EntityInteractionType _c_interaction_type;

	////     Stats    ////

	Ref<Stat> _stats[Stat::STAT_ID_TOTAL_STATS];

	////    Equipment    ////

	Ref<ItemInstance> _equipment[ItemEnums::EQUIP_SLOT_EQUIP_SLOT_MAX];

	////    Resources    ////

	Vector<Ref<EntityResource> > _s_resources;
	Vector<Ref<EntityResource> > _c_resources;

	//old
	bool sIsDead;
	bool cIsDead;
	bool localClient;

	bool s;
	bool c;
	float sRezTimer;
	float cRezTimer;

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

	EntityEnums::EntityController _s_entity_controller;

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

	int _s_target_guid;
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
	//int _stat_allocations[Stat::STAT_ID_TOTAL_STATS];

	////    Inventory    ////

	Ref<Bag> _s_bag;
	Ref<Bag> _c_bag;

	Ref<Bag> _s_target_bag;
	Ref<Bag> _c_target_bag;
};

#endif
