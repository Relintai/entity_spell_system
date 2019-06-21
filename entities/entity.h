#ifndef ENTITY_H
#define ENTITY_H

#include "core/io/networked_multiplayer_peer.h"

#ifdef ENTITIES_2D
#include "scene/2d/physics_body_2d.h"
#else
#include "scene/3d/physics_body.h"
#endif


#include "../data/character.h"
#include "../data/craft_data_attribute.h"
#include "../data/spell.h"
#include "../data/xp_data.h"
#include "core/hash_map.h"
#include "core/object.h"
#include "core/ustring.h"
#include "core/vector.h"
#include "../inventory/bag_slot.h"
#include "../data/item_instance.h"
#include "player_talent.h"


#include "../data/spell.h"
#include "stats/stat.h"

#include "../data/data_manager.h"

#include "../entity_enums.h"

#include "../spells/spell_cast_info.h"

#include "../skeleton/character_skeleton.h"

#include "../utility/entity_create_info.h"

#include "../utility/cooldown.h"
#include "../utility/category_cooldown.h"

#include "../inventory/bag.h"

class CharacterClass;
class AuraData;
class Spell;
class SpellDamageInfo;
class SpellHealInfo;
class SpellCastInfo;
class EntityCreateInfo;

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
#define SEND_RPC(rpc_func, normal_func) \
    if (is_inside_tree() && get_tree()->has_network_peer() && get_tree()->get_network_peer()->get_connection_status() == NetworkedMultiplayerPeer::CONNECTION_CONNECTED) { \
        rpc_func;\
    }\
	normal_func;

// f.e.   SEND_RPC_TO_SERVER(rpc_id(1, "method", arg), method(arg))
#define SEND_RPC_TO_SERVER(rpc_func, normal_func)                                                                                                                                    \
	if (is_inside_tree() && get_tree()->has_network_peer() && get_tree()->get_network_peer()->get_connection_status() == NetworkedMultiplayerPeer::CONNECTION_CONNECTED) { \
		if (get_tree()->is_network_server())\
			normal_func;\
		else \
			rpc_func;\
	} else {\
		normal_func;\
	}

// f.e. SEND_RSET(rset("property", "value"), property, value)
#define SEND_RSET(rset_func, variable, value) \
    if (is_inside_tree() && get_tree()->has_network_peer() && get_tree()->get_network_peer()->get_connection_status() == NetworkedMultiplayerPeer::CONNECTION_CONNECTED) { \
        rset_func;\
    }\
    variable = value;

    
#ifdef ENTITIES_2D
class Entity : public KinematicBody2D {
	GDCLASS(Entity, KinematicBody2D);

#else

class Entity : public KinematicBody {
	GDCLASS(Entity, KinematicBody);

#endif

public:
    enum InventorySizes {
        BACKPACK_SIZE = 20,
        MAX_BAG_SLOTS = 5,
    };
    
	Entity();
	~Entity();

	void initialize(Ref<EntityCreateInfo> info);

	void Update(); //old, remove

	////    Base    ////

	NodePath get_character_skeleton_path();
	void set_character_skeleton_path(NodePath value);

	CharacterSkeleton *get_character_skeleton();

	int getc_guid();
	void setc_guid(int value);

	int gets_guid();
	void sets_guid(int value);

	int gets_character_class_id();
	void sets_character_class_id(int value);

	int getc_character_class_id();
	void setc_character_class_id(int value);

	EntityEnums::EntityType gets_entity_type();
	void sets_entity_type(EntityEnums::EntityType value);

	EntityEnums::EntityType getc_entity_type();
	void setc_entity_type(EntityEnums::EntityType value);

	String gets_player_name();
	void sets_player_name(String value);

	String getc_player_name();
	void setc_player_name(String value);

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

	Ref<CharacterClass> getc_character_class();
	void setc_character_class(Ref<CharacterClass> value);

	Ref<CharacterClass> gets_character_class();
	void sets_character_class(Ref<CharacterClass> value);

	void sinitialize_stats();

	void reward_xp_for_mob(int level);
	void level_up(int num = 1);
	void set_level_without_modifiers(int newLevel, bool a);
	void apply_level_modifiers();
	void rpc_level_up();
	void registers();

	////    SpellCastData    ////

	bool gets_casting();
	void sets_casting(bool value);

	int gets_spell_id();
	void sets_spell_id(int value);

	float gets_current_cast_time();
	void sets_current_cast_time(float value);

	float gets_cast_time();
	void sets_cast_time(float value);

	float gets_spell_scale();
	void sets_spell_scale(float value);

	bool getc_casting();
	void setc_casting(bool value);

	int getc_spell_id();
	void setc_spell_id(int value);

	float getc_current_cast_time();
	void setc_current_cast_time(float value);

	float getc_cast_time();
	void setc_cast_time(float value);

	String getc_spell_name();
	void setc_spell_name(String value);

	Entity *gets_spell_target();
	void sets_spell_target(Node *p_target);

	int gets_target_guid();
	int gets_spell_cast_game_object_guid();

	////     Stats    ////

	_FORCE_INLINE_ Ref<Stat> get_health() { return _health; }
	_FORCE_INLINE_ Ref<Stat> get_mana() { return _mana; }
	_FORCE_INLINE_ Ref<Stat> get_speed() { return _speed; }
	_FORCE_INLINE_ Ref<Stat> get_gcd() { return _gcd; }
	_FORCE_INLINE_ Ref<Stat> get_melee_crit() { return _melee_crit; }
	_FORCE_INLINE_ Ref<Stat> get_melee_crit_bonus() { return _melee_crit_bonus; }
	_FORCE_INLINE_ Ref<Stat> get_spell_crit() { return _spell_crit; }
	_FORCE_INLINE_ Ref<Stat> get_spell_crit_bonus() { return _spell_crit_bonus; }
	_FORCE_INLINE_ Ref<Stat> get_block() { return _block; }
	_FORCE_INLINE_ Ref<Stat> get_parry() { return _parry; }
	_FORCE_INLINE_ Ref<Stat> get_damage_reduction() { return _damage_reduction; }
	_FORCE_INLINE_ Ref<Stat> get_melee_damage_reduction() { return _melee_damage_reduction; }
	_FORCE_INLINE_ Ref<Stat> get_spell_damage_reduction() { return _spell_damage_reduction; }
	_FORCE_INLINE_ Ref<Stat> get_damage_taken() { return _damage_taken; }
	_FORCE_INLINE_ Ref<Stat> get_heal_taken() { return _heal_taken; }
	_FORCE_INLINE_ Ref<Stat> get_melee_damage() { return _melee_damage; }
	_FORCE_INLINE_ Ref<Stat> get_spell_damage() { return _spell_damage; }

	Ref<Stat> get_stat_int(int index);
	void set_stat_int(int index, Ref<Stat> entry);

	Ref<Stat> get_stat_enum(Stat::StatId stat_id);
	void set_stat_enum(Stat::StatId stat_id, Ref<Stat> entry);

	//GCD
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
	
	void son_hit(Ref<SpellDamageInfo> data);
	void son_before_damage(Ref<SpellDamageInfo> data);
	void son_damage_receive(Ref<SpellDamageInfo> data);
	void son_dealt_damage(Ref<SpellDamageInfo> data);
	void son_damage_dealt(Ref<SpellDamageInfo> data);

	void son_before_heal(Ref<SpellHealInfo> data);
	void son_heal_receive(Ref<SpellHealInfo> data);
	void son_dealt_heal(Ref<SpellHealInfo> data);
	void son_heal_dealt(Ref<SpellHealInfo> data);

	void son_before_cast(Ref<SpellCastInfo> info);
	void son_before_cast_target(Ref<SpellCastInfo> info);
	void son_cast_finished_target(Ref<SpellCastInfo> info);
	void son_cast_finished(Ref<SpellCastInfo> info);
	void son_cast_started(Ref<SpellCastInfo> info);
	void son_cast_failed(Ref<SpellCastInfo> info);

	//Clientside EventHandlers
	void con_cast_failed(Ref<SpellCastInfo> info);
	void con_cast_started(Ref<SpellCastInfo> info);
	void con_cast_state_changed(Ref<SpellCastInfo> info);
	void con_cast_finished(Ref<SpellCastInfo> info);
	void con_spell_cast_success(Ref<SpellCastInfo> info);

	//Modifiers/Requesters
	void sapply_passives_damage_receive(Ref<SpellDamageInfo> data);
	void sapply_passives_damage_deal(Ref<SpellDamageInfo> data);

	void sapply_passives_heal_receive(Ref<SpellHealInfo> data);
	void sapply_passives_heal_deal(Ref<SpellHealInfo> data);

	//Spell operations
	void scast_spell(int spell_id);
	void crequest_spell_cast(int spell_id);

	//Damage Operations
	void stake_damage(Ref<SpellDamageInfo> data);
	void sdeal_damage_to(Ref<SpellDamageInfo> data);

	//Heal Operations
	void stake_heal(Ref<SpellHealInfo> data);
	void sdeal_heal_to(Ref<SpellHealInfo> data);

	//Aura Manipulation
	void sadd_aura(Ref<AuraData> aura);
	void sremove_aura(Ref<AuraData> aura);
	void sremove_aura_expired(Ref<AuraData> aura);
	void sremove_aura_dispelled(Ref<AuraData> aura);

	void cadd_aura(Ref<AuraData> aura);
	void cremove_aura(Ref<AuraData> aura);
	void cremove_aura_expired(Ref<AuraData> aura);
	void cremove_aura_dispelled(Ref<AuraData> aura);

	void sremove_auras_with_group(int aura_group);

	int sget_aura_count();
	Ref<Aura> sget_aura(int index);

	int cget_aura_count();
	Ref<Aura> cget_aura(int index);

	//Hooks
	void moved();
	
	//Update
	void update_auras(float delta);

	//Clientside hooks
	void creceive_damage_taken(Ref<SpellDamageInfo> data);
	void creceiveon_damage_dealt(Ref<SpellDamageInfo> data);
	void creceive_heal_taken(Ref<SpellHealInfo> data);
	void creceiveon_heal_dealt(Ref<SpellHealInfo> data);

	//Old, hook loading update when needed
	void setup_on_player_moves(Entity *bopmccc, Vector<int> *sspells); //load -> remove, just store spellIds

	//Old stuff, remove or update
	void die();
	void resurrect();
	void creceive_resurrect();
	void creceive_died();
	void creceive_mana_changed(int amount);
	bool gets_is_dead();
	bool getc_is_dead();

	void son_death();


	////    Casting System    ////

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
	Vector<Ref<CategoryCooldown> > *gets_category_cooldowns();
	Vector<Ref<CategoryCooldown> > *getc_category_cooldowns();

	HashMap<int, Ref<CategoryCooldown> > * gets_category_cooldown_map();
	HashMap<int, Ref<CategoryCooldown> > * getc_category_cooldown_map();

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

	////    TargetComponent    ////

	void crequest_target_change(NodePath path);
	void net_sets_target(NodePath path);
	void net_setc_target(NodePath path);

	Entity *gets_target();
	void sets_target(Node *p_target);

	Entity *getc_target();
	void setc_target(Node *p_target);

	////    TalentComponent    ////

	void csend_request_rank_increase(int talentID);
	void csend_request_rank_decrease(int talentID);
	void ssend_rank(int talentID, int rank);
	void sreceive_rank_increase(int talentID);
	void sreceive_rank_decrease(int talentID);
	void creceive_rank(int talentID, int rank);
	PlayerTalent *sget_talent(int id, bool create = false);
	PlayerTalent *cget_talent(int id, bool create = false);

	////    Inventory    ////

	Ref<Bag> gets_bag(int index);
	Ref<Bag> getc_bag(int index);
    
	bool stry_to_add_item(int itemId, int count);
	bool stry_to_remove_item(int itemId, int count);
	void ssend_add_item(int slotId, int itemId, int count);
	void ssend_change_item_count(int slotId, int count);
	void ssend_remove_item(int slotId);
	void ssend_move_item(int slot1, int slot2);
	void ssend_sent_items(String items);
	void csend_swap_items(int slot1, int slot2);
	void csend_craft_item_request(int craftId);
	void creceive_add_item(int slotId, int itemId, int count);
	void creceive_change_item_count(int slotId, int count);
	void creceive_remove_item(int slotId);
	void creceive_move_item(int slot1, int slot2);
	void creceive_sent_items(String items);
	void sreceive_swap_items(int slot1, int slot2);
	bool shas_item(int itemId, int count);
	bool chas_item(int itemId, int count);
	int cget_item_count(int itemId);
	int sget_item_count(int itemId);
	bool ccan_craft(CraftDataAttribute *cda);
	bool ctry_to_craft(CraftDataAttribute *cda);
	bool scan_craft(CraftDataAttribute *cda);
	void scraft(CraftDataAttribute *cda);
	void sreceive_craft_item_msg(int craftId);
	void cswap_items_in_slots(int slot1, int slot2);
	void loaded();
	void send_all_items();

	String random_name();

	String request_spell_name(int spellId);
	String request_spell_description(int spellId, int level);

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

	Ref<CharacterClass> _s_character_class;
	Ref<CharacterClass> _c_character_class;

	int _s_send_flag;

	String _s_player_name;
	String _c_player_name;

	////     Stats    ////

	Ref<Stat> _health;
	Ref<Stat> _mana;
	Ref<Stat> _speed;
	Ref<Stat> _gcd;

	Ref<Stat> _melee_crit;
	Ref<Stat> _melee_crit_bonus;
	Ref<Stat> _spell_crit;
	Ref<Stat> _spell_crit_bonus;
	Ref<Stat> _block;
	Ref<Stat> _parry;
	Ref<Stat> _damage_reduction;
	Ref<Stat> _melee_damage_reduction;
	Ref<Stat> _spell_damage_reduction;
	Ref<Stat> _damage_taken;
	Ref<Stat> _heal_taken;
	Ref<Stat> _melee_damage;
	Ref<Stat> _spell_damage;

	Ref<Stat> _stats[Stat::STAT_ID_TOTAL_STATS];

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

	bool _s_casting;
	int _s_spell_id;
	float _s_current_cast_time;
	float _s_cast_time;
	float _s_spell_scale;
	bool _c_casting;
	int _c_spell_id;
	float _c_current_cast_time;
	float _c_cast_time;
	String _c_spell_name;
	Entity *_s_spell_target;
	Entity *_c_spell_target;
	int _s_spell_target_guid;
	int _s_spell_cast_game_object_guid;

	Ref<SpellCastInfo> _s_spell_cast_info;
	Ref<SpellCastInfo> _c_spell_cast_info;

	//// AuraComponent    ////

	Vector<Ref<AuraData> > _s_auras;
	Vector<Ref<AuraData> > _c_auras;

	EntityEnums::EntityType _s_entity_type;
	EntityEnums::EntityType _c_entity_type;

	////    Cooldowns    ////
	Vector<Ref<Cooldown> > _s_cooldowns;
	Vector<Ref<Cooldown> > _c_cooldowns;

	HashMap<int, Ref<Cooldown> > _s_cooldown_map;
	HashMap<int, Ref<Cooldown> > _c_cooldown_map;

	Vector<Ref<CategoryCooldown> > _s_category_cooldowns;
	Vector<Ref<CategoryCooldown> > _c_category_cooldowns;

	HashMap<int, Ref<CategoryCooldown> > _s_category_cooldown_map;
	HashMap<int, Ref<CategoryCooldown> > _c_category_cooldown_map;

	////    targetComponent    ////

	int _s_target_guid;
	Entity *_s_target;
	Entity *_c_target;

	////    TalentComponent    ////

	Vector<Ref<PlayerTalent> > _s_talents;
	Vector<Ref<PlayerTalent> > _c_talents;

	////    Inventory    ////

	Ref<Bag> _s_bags[MAX_BAG_SLOTS];
	Ref<Bag> _c_bags[MAX_BAG_SLOTS];
};

VARIANT_ENUM_CAST(Entity::InventorySizes);

#endif
