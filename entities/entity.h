#ifndef ENTITY_H
#define ENTITY_H

#include "../data/character.h"
#include "../data/craft_data_attribute.h"
#include "../data/spell.h"
#include "../data/xp_data.h"
#include "core/hash_map.h"
#include "core/object.h"
#include "core/ustring.h"
#include "core/vector.h"
#include "item_instance.h"
#include "player_talent.h"
#include "scene/3d/physics_body.h"

#include "../data/spell.h"
#include "stats/stat.h"

#include "../data/data_manager.h"

#include "../entity_enums.h"

#include "../spells/spell_cast_info.h"

class CharacterClass;
class AuraData;
class Spell;
class SpellDamageInfo;
class SpellCastInfo;

class EntityCreateInfo : public Object {
public:
	int get_guid() { return _guid; }
	void set_guid(int value) { _guid = value; }

	EntityEnums::EntityType get_entity_type() { return _entity_type; }
	void set_entity_type(EntityEnums::EntityType value) { _entity_type = value; }

	String get_player_name() { return _player_name; }
	void set_player_name(String value) { _player_name = value; }

	int get_level() { return _level; }
	void set_level(int value) { _level = value; }

	int get_xp() { return _xp; }
	void set_xp(int value) { _xp = value; }

	Ref<CharacterClass> get_character_class() { return _character_class; }
	void set_character_class(Ref<CharacterClass> value) { _character_class = value; }

protected:
	static void _bind_methods() {
		ClassDB::bind_method(D_METHOD("get_entity_type"), &EntityCreateInfo::get_entity_type);
		ClassDB::bind_method(D_METHOD("set_entity_type", "value"), &EntityCreateInfo::set_entity_type);
		ADD_PROPERTY(PropertyInfo(Variant::INT, "entity_type", PROPERTY_HINT_ENUM, "None, Player, AI, Mob"), "set_entity_type", "get_entity_type");

		ClassDB::bind_method(D_METHOD("get_player_name"), &EntityCreateInfo::get_player_name);
		ClassDB::bind_method(D_METHOD("set_player_name", "value"), &EntityCreateInfo::set_player_name);
		ADD_PROPERTY(PropertyInfo(Variant::STRING, "player_name"), "set_player_name", "get_player_name");

		ClassDB::bind_method(D_METHOD("get_level"), &EntityCreateInfo::get_level);
		ClassDB::bind_method(D_METHOD("set_level", "value"), &EntityCreateInfo::set_level);
		ADD_PROPERTY(PropertyInfo(Variant::STRING, "level"), "set_level", "get_level");

		ClassDB::bind_method(D_METHOD("get_xp"), &EntityCreateInfo::get_xp);
		ClassDB::bind_method(D_METHOD("set_xp", "value"), &EntityCreateInfo::set_xp);
		ADD_PROPERTY(PropertyInfo(Variant::STRING, "xp"), "set_xp", "get_xp");

		ClassDB::bind_method(D_METHOD("get_character_class"), &EntityCreateInfo::get_character_class);
		ClassDB::bind_method(D_METHOD("set_character_class", "value"), &EntityCreateInfo::set_character_class);
		ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "character_class", PROPERTY_HINT_RESOURCE_TYPE, "CharacterClass"), "set_character_class", "get_character_class");
	}

private:
	int _guid;
	EntityEnums::EntityType _entity_type;
	String _player_name;
	int _level;
	int _xp;

	Ref<CharacterClass> _character_class;
};

struct EntitySpellCastInfo {
	bool s_casting;
	int s_spellId;
	int s_spell_cast_game_object_guid;
	float s_current_cast_time;
	float s_cast_time;
	float s_spell_scale;
	bool c_casting;
	int c_spell_id;
	float c_current_cast_time;
	float c_cast_time;
	String c_spell_name;
	float anim_reduction;
	//Entity *s_target;
	//Entity *c_target;
	int s_target_guid;
	//Entity *owner;
};

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

class Entity : public KinematicBody {
	GDCLASS(Entity, KinematicBody)

public:
	Entity();
	~Entity();

	void initialize(EntityCreateInfo *info);

	//EntityType getType();

	void AfterLoadFinished();
	void Update();
	void Awake();
	void Start();
	void LateUpdate();
	void init();
	void update();
	void Init();
	void InitVariables();

	////    Base    ////

	int getc_guid();
	void setc_guid(int value);

	int gets_guid();
	void sets_guid(int value);

	PlayerStates getc_state();
	void setc_state(PlayerStates state);

	PlayerStates gets_state();
	void sets_state(PlayerStates state);

	int gets_class_id();
	void sets_class_id(int value);

	int getc_class_id();
	void setc_class_id(int value);

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

	bool gets_casting() { return _s_casting; }
	void sets_casting(bool value) { _s_casting = value; }

	int gets_spell_id() { return _s_spell_id; }
	void sets_spell_id(int value) { _s_spell_id = value; }

	float gets_current_cast_time() { return _s_current_cast_time; }
	void sets_current_cast_time(float value) { _s_current_cast_time = value; }

	float gets_cast_time() { return _s_cast_time; }
	void sets_cast_time(float value) { _s_cast_time = value; }

	float gets_spell_scale() { return _s_spell_scale; }
	void sets_spell_scale(float value) { _s_spell_scale = value; }

	bool getc_casting() { return _c_casting; }
	void setc_casting(bool value) { _c_casting = value; }

	int getc_spell_id() { return _c_spell_id; }
	void setc_spell_id(int value) { _c_spell_id = value; }

	float getc_current_cast_time() { return _c_current_cast_time; }
	void setc_current_cast_time(float value) { _c_current_cast_time = value; }

	float getc_cast_time() { return _c_cast_time; }
	void setc_cast_time(float value) { _c_cast_time = value; }

	String getc_spell_name() { return _c_spell_name; }
	void setc_spell_name(String value) { _c_spell_name = value; }

	Entity *gets_spell_target();
	void sets_spell_target(Node *p_target);

	Entity *getc_spell_target();
	void setc_spell_target(Node *p_target);

	//Game_object *gets_spell_cast_game_object() { return _s_spell_cast_game_object; }
	//void sets_spell_cast_game_object(Game_object *value) { _s_spell_cast_game_object = value; }

	int gets_target_guid() { return _s_target_guid; }
	int gets_spell_cast_game_object_guid() { return _s_spell_cast_game_object_guid; }

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
	_FORCE_INLINE_ Ref<Stat> get_melee_damage() { return _melee_damage; }
	_FORCE_INLINE_ Ref<Stat> get_spell_damage() { return _spell_damage; }

	Ref<Stat> get_stat_int(int index);
	void set_stat_int(int index, Ref<Stat> entry);

	Ref<Stat> get_stat_enum(Stat::StatId stat_id);
	void set_stat_enum(Stat::StatId stat_id, Ref<Stat> entry);

	////    SpellSystem    ////

	void scast_spell(int spell_id);
	void crequest_spell_cast(int spell_id);
	void casting_finished(Entity *caster, int spellId, float scale);
	void update_auras(float delta);
	void son_before_cast(Ref<SpellCastInfo> info);
	void son_before_cast_target(Ref<SpellCastInfo> info);
	void son_hit(Ref<SpellDamageInfo> data);
	void son_before_damage(Ref<SpellDamageInfo> data);
	void son_damage_receive(Ref<SpellDamageInfo> data);
	void son_dealt_damage(Ref<SpellDamageInfo> data);
	void sapply_passives_damage_receive(Ref<SpellDamageInfo> data);
	void sapply_passives_damage_deal(Ref<SpellDamageInfo> data);
	void remove_auras_with_group(Entity *ac, int auraGroup);

	void sremove_aura_expired(Ref<AuraData> aura);
	void cremove_aura_expired(Ref<AuraData> aura);

	void sremove_aura(Ref<AuraData> aura);
	void cremove_aura(Ref<AuraData> aura);

	void crefresh_aura(Entity *ac, int auraId, float time);
	void crefresh_caster_aura(Entity *ac, int auraId, Entity *caster, float time);
	void caura_added(Entity *ac, int id, float remaining, Entity *caster, int casterGUID);
	void caura_removed(Entity *ac, int id);
	void con_cast_failed(Entity *caster, int spellId);
	void setup_on_player_moves(Entity *bopmccc, Vector<int> *sspells);
	void con_cast_started(Entity *caster, int spellId);
	void con_cast_state_changed(Entity *caster, int spellId);
	void con_cast_finished(Entity *caster, int spellId);
	void con_spell_cast_success(Entity *caster, int spellId);

	void son_before_aura_applied(Ref<AuraData> data);
	void son_after_aura_applied(Ref<AuraData> data);

	//rename to remove_aura()
	virtual void just_remove_aura(int auraId);
	virtual void add_aura(Ref<AuraData> data);
	virtual void remove_auras_with_group(int auraGroup);
	virtual void refresh_aura(int auraId, float time);
	virtual void refresh_aura(int auraId, Entity *caster, float time);
	virtual void ssend_refresh_aura(int auraId, float time);
	virtual void ssend_refresh_caster_aura(int auraId, Entity *caster, float time);
	virtual void ssend_aura_added(int auraId, float time, Entity *caster);
	virtual void ssend_aura_removed(int auraId);
	virtual void creceive_refresh_aura(int auraId, float time);
	virtual void creceive_refresh_caster_aura(int auraId, Entity *caster, float time);
	virtual void creceive_aura_added(int id, float remaining, Entity *caster);
	virtual void creceive_aura_removed(int id);

	void stake_damage(Ref<SpellDamageInfo> data);
	void son_damage_dealt(Ref<SpellDamageInfo> data);
	void sdeal_damage_to(Ref<SpellDamageInfo> data);
	void take_heal(int heal, bool crit, Entity *dealer);
	void die();
	void resurrect();
	void creceive_resurrect();
	void creceive_damage_taken(Ref<SpellDamageInfo> data);
	void creceiveon_damage_dealt(Ref<SpellDamageInfo> data);
	void creceive_heal_taken(int heal, bool crit, Entity *dealer);
	void creceive_died();
	void creceive_mana_changed(int amount);
	void trigger_global_cooldown();
	void creceive_trigger_global_cooldown();
	//void Set(bool SIsDead, float SRezTimer, bool SHasGlobalCooldown);

	bool gets_is_dead();
	bool getc_is_dead();
	bool getc_has_global_cooldown();
	bool gets_has_global_cooldown();

	/*
	void SendDamageTakenMessage(int damage, bool crit, Entity *dealer);
	void SendHealTakenMessage(int heal, bool crit, Entity *dealer);
	void SendResurrectMessage();
	void SendDieMessage();
	void SendTriggerGCDMessage();
	Ref<Stat> GetSStatFromId(int id);
	Ref<Stat> GetCStatFromId(int id);

	static int GetStatIdFromString(String *name);*/

	/*
	void AddStat(CStatUpdateMsg &msg, Ref<Stat> stat);
	void AddStat(CStatUpdateMsg &msg, Ref<Stat> stat);
	void AddStat(CStatUpdateMsg &msg, Ref<Stat> stat);
	void AddStat(CStatUpdateMsg &msg, Stat *stat);
	void CHandleStatUpdateMsg(CStatUpdateMsg &msg);
	void CReadStat(CStatUpdateMsg &msg);
	void ReadStat(CStatUpdateMsg &msg, Stat *stat);
	void ReadStat(CStatUpdateMsg &msg, Stat *stat);
	void ReadStat(CStatUpdateMsg &msg, Stat *stat);
*/
	//void OnStateChanged(PlayerStates newState);
	void son_death();

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

	void scast_finished();
	void ccast_finished();

	void on_cast_state_change();

	void scast_started(Ref<SpellCastInfo> info);


	Ref<SpellCastInfo> gets_spell_cast_info();
	void sets_spell_cast_info(Ref<SpellCastInfo> info);

	Ref<SpellCastInfo> getc_spell_cast_info();
	void setc_spell_cast_info(Ref<SpellCastInfo> info);

	//networking
	//void ssend_start_casting(int spellId, float castTime);
	//void ssend_cast_failed();
	//void ssend_cast_finished(int spellId);

	//void creceive_start_casting(int spellId, float castTime);
	//void creceive_cast_finished();
	//void creceive_cast_failed();


	void start_animation_time(float time);

	////    TargetComponent    ////

	Entity *gets_target();
	void sets_target(Node *p_target);

	Entity *getc_target();
	void setc_target(Node *p_target);

	int get_starget_guid();
	void set_starget_guid(int value);
	void set_target(Entity *t);
	void sreceive_ctarget_change(Entity *t);
	void ai_set_target(Entity *t);
	void csend_target();
	void sbroadcast_target_change();
	void on_state_changed(PlayerStates newState);

	////    TalentComponent    ////

	void csend_request_rank_increase(int talentID);
	void csend_request_rank_decrease(int talentID);
	void ssend_rank(int talentID, int rank);
	void sreceive_rank_increase(int talentID);
	void sreceive_rank_decrease(int talentID);
	void creceive_rank(int talentID, int rank);
	PlayerTalent *sget_talent(int id, bool create = false);
	PlayerTalent *cget_talent(int id, bool create = false);

	////    PlayerSpellDataComponent    ////

	Vector<int> *gets_spell_data();
	Vector<int> *getc_spell_data();
	//HashMap<int, PlayerLocalSpellData> *getLocalSpellData(); //this should be the same object

	bool get_send();
	void set_send(bool value);
	//void AddSSpellData(PlayerSpellData *psd);
	//void AddCSpellData(PlayerSpellData *psd);
	//void RemoveSSpellData(PlayerSpellData *psd);
	void ssend_add_cplayer_spell_cooldown_data(int spellId, float cooldown, float remainingCooldown);
	void ssend_remove_cplayer_spell_cooldown_data(int spellId);
	void creceive_add_cplayer_spell_cooldown_data(int spellId, float cooldown, float remainingCooldown);
	void creceive_remove_cplayer_spell_cooldown_data(int spellId);
	//void RemoveCSpellData(int spellId, Type *type);

	////    Inventory    ////

	int INVENTORY_DEFAULT_SIZE;

	Vector<ItemInstance *> *get_sinventory();
	Vector<ItemInstance *> *get_cinventory();
	//Vector<ItemInstance *> *getSCraftMaterialInventory();
	//Vector<ItemInstance *> *getCCraftMaterialInventory();

	//void Update();
	void sadd_craft_material(int itemId, int count);
	void sremove_craft_material(int itemId, int count);
	bool stry_to_add_item(int itemId, int count);
	bool stry_to_remove_item(int itemId, int count);
	void ssend_add_item(int slotId, int itemId, int count);
	void ssend_change_item_count(int slotId, int count);
	void ssend_remove_item(int slotId);
	void ssend_move_item(int slot1, int slot2);
	void ssend_sent_items(String items);
	void csend_swap_items(int slot1, int slot2);
	void csend_craft_item_request(int craftId);
	void ssend_add_craft_material(int itemId, int count);
	void ssend_remove_craft_material(int itemId, int count);
	void ssend_sent_craft_materials(String materials);
	void creceive_add_item(int slotId, int itemId, int count);
	void creceive_change_item_count(int slotId, int count);
	void creceive_remove_item(int slotId);
	void creceive_move_item(int slot1, int slot2);
	void creceive_add_craft_material(int itemId, int count);
	void creceive_remove_craft_material(int itemId, int count);
	void creceive_sent_craft_materials(String materials);
	void creceive_sent_items(String items);
	void sreceive_swap_items(int slot1, int slot2);
	bool shas_craft_material(int itemId, int count);
	bool shas_item(int itemId, int count);
	bool chas_craft_material(int itemId, int count);
	bool chas_item(int itemId, int count);
	int cget_item_count(int itemId);
	int sget_item_count(int itemId);
	int cget_craft_material_count(int itemId);
	int sget_craft_material_count(int itemId);
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

	/*
	void AddGraphicScripts();
	static Entity *SEntitySpawn(EntityType type, int classId, int level, String name, int Guid = 0u, CxConnection *connection = null, bool owner = false, Vector3 *position =, Quaternion *rotation =);
	static Entity *NetworkSpawnCharacter(int Guid, EntityType type, int classId, int level, String name, CxConnection *connection = null, bool owner = false, Vector3 *position =, Quaternion *rotation =);
	static Entity *CEntitySpawn(int Guid, EntityType type, int classId, int level, String name, CxConnection *connection = null, bool owner = false, Vector3 *position =, Quaternion *rotation =);
	void OnPlayerSpawneds(Entity *player, bool isClientPlayer, bool is_serverPlayer, bool isLocalPlayerPlayer);
	*/

protected:
	static void _bind_methods();
	virtual void _notification(int p_notification);
	virtual void update(float delta);

private:
	const float SAVE_BASE_SECONDS = 10.0;

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

	PlayerStates _s_state = PlayerStates::STATE_NORMAL;
	PlayerStates _c_state = PlayerStates::STATE_NORMAL;

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
	Ref<Stat> _melee_damage;
	Ref<Stat> _spell_damage;


	Ref<Stat> _stats[Stat::STAT_ID_TOTAL_STATS];



	bool sIsDead;
	bool cIsDead;
	bool localClient;

	bool s;
	bool c;
	bool cHasGlobalCooldown;
	bool sHasGlobalCooldown;
	float sRezTimer;
	float cRezTimer;
	//bool init;

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

	Vector<Ref<AuraData> > *_s_auras;
	Vector<Ref<AuraData> > *_c_auras;

	EntityEnums::EntityType _s_entity_type;
	EntityEnums::EntityType _c_entity_type;

	////    targetComponent    ////

	int _s_target_guid;
	Entity *_s_target;
	Entity *_c_target;

	////    TalentComponent    ////

	Vector<PlayerTalent *> *_s_talents;
	Vector<PlayerTalent *> *_c_talents;

	////    PlayerSpellDataComponent    ////

	Vector<int> *_s_spell_data;
	Vector<int> *_c_spell_data;
	HashMap<int, int> *_local_spell_data;

	////    Inventory    ////

	Vector<ItemInstance *> *_s_inventory;
	Vector<ItemInstance *> *_c_inventory;
};

#endif
