#include "entity.h"

#include "../data/aura.h"
#include "../data/spell.h"
#include "../entities/auras/aura_data.h"
#include "../pipelines/spell_damage_info.h"
#include "../pipelines/spell_heal_info.h"

NodePath Entity::get_character_skeleton_path() {
	return _character_skeleton_path;
}

void Entity::set_character_skeleton_path(NodePath value) {
	_character_skeleton_path = value;

	Node *node = get_node_or_null(_character_skeleton_path);

	if (node != NULL) {
		_character_skeleton = Object::cast_to<CharacterSkeleton>(node);
	} else {
		_character_skeleton = NULL;
	}
}

CharacterSkeleton *Entity::get_character_skeleton() {
	return _character_skeleton;
}

int Entity::getc_guid() {
	return _c_guid;
}
void Entity::setc_guid(int value) {
	_c_guid = value;
}

int Entity::gets_guid() {
	return _s_guid;
}
void Entity::sets_guid(int value) {
	_s_guid = value;
}

int Entity::gets_class_id() {
	return _s_class_id;
}
void Entity::sets_class_id(int value) {
	_s_class_id = value;
}

int Entity::getc_class_id() {
	return _c_class_id;
}
void Entity::setc_class_id(int value) {
	_c_class_id = value;
}

EntityEnums::EntityType Entity::gets_entity_type() {
	return _s_entity_type;
}
void Entity::sets_entity_type(EntityEnums::EntityType value) {
	_s_entity_type = value;
}

EntityEnums::EntityType Entity::getc_entity_type() {
	return _c_entity_type;
}
void Entity::setc_entity_type(EntityEnums::EntityType value) {
	_c_entity_type = value;
}

String Entity::gets_player_name() {
	return _s_player_name;
}
void Entity::sets_player_name(String value) {
	_s_player_name = value;
}

String Entity::getc_player_name() {
	return _c_player_name;
}
void Entity::setc_player_name(String value) {
	_c_player_name = value;
}

int Entity::gets_gender() {
	return _s_gender;
}
void Entity::sets_gender(int value) {
	_s_gender = value;
}

int Entity::getc_gender() {
	return _c_gender;
}
void Entity::setc_gender(int value) {
	_c_gender = value;
}

int Entity::gets_level() {
	return _s_level;
}
void Entity::sets_level(int value) {
	_s_level = value;
}

int Entity::getc_level() {
	return _c_level;
}
void Entity::setc_level(int value) {
	_c_level = value;
}

int Entity::gets_xp() {
	return _s_xp;
}
void Entity::sets_xp(int value) {
	_s_xp = value;
}

int Entity::getc_xp() {
	return _c_xp;
}
void Entity::setc_xp(int value) {
	_c_xp = value;
}

Ref<CharacterClass> Entity::getc_character_class() {
	return _c_character_class;
}

void Entity::setc_character_class(Ref<CharacterClass> value) {
	_c_character_class = value;

	emit_signal("ccharacter_class_changed", value);
}

Ref<CharacterClass> Entity::gets_character_class() {
	return _s_character_class;
}

void Entity::sets_character_class(Ref<CharacterClass> value) {
	_s_character_class = value;

	if (value.is_valid()) {
		sinitialize_stats();
	}

	if (!Engine::get_singleton()->is_editor_hint())
		set_process(value.is_valid());

	emit_signal("scharacter_class_changed", value);

	setc_character_class(value);
}

Entity *Entity::gets_spell_target() {
	return _s_target;
}

void Entity::sets_spell_target(Node *p_target) {
	if (!p_target) {
		return;
	}

	Entity *e = cast_to<Entity>(p_target);

	if (!e) {
		return;
	}

	_s_target = e;

	emit_signal("starget_changed", _s_target);

	setc_target(p_target);
}

Entity *Entity::getc_spell_target() {
	return _c_target;
}

void Entity::setc_spell_target(Node *p_target) {
	if (!p_target) {
		return;
	}

	Entity *e = cast_to<Entity>(p_target);

	if (!e) {
		return;
	}

	_c_target = e;

	emit_signal("ctarget_changed", _c_target);
}

Entity::Entity() {
	_s_guid = 0;
	_c_guid = 0;

	_s_class_id = 0;
	_c_class_id = 0;

	_s_type = 0;
	_c_type = 0;

	_s_gender = 0;
	_c_gender = 0;

	_s_level = 50;
	_c_level = 50;

	_s_xp = 0;
	_c_xp = 0;

	_s_send_flag = 0;

	_s_player_name = "";
	_c_player_name = "";

	_s_state = PlayerStates::STATE_NORMAL;
	_c_state = PlayerStates::STATE_NORMAL;

	sIsDead = false;
	cIsDead = false;

	_s_gcd = 0;
	_c_gcd = 0;

	for (int i = 0; i < EntityEnums::ENTITY_STATE_TYPE_INDEX_MAX; ++i) {
		_s_states[i] = 0;
	}

	_s_state = 0;
	_c_state = 0;

	sRezTimer = 0;
	cRezTimer = 0;

	_s_casting = false;
	_s_spell_id = 0;
	_s_current_cast_time = 0;
	_s_cast_time = 0;
	_s_spell_scale = 0;
	_c_casting = false;
	_c_spell_id = 0;
	_c_current_cast_time = 0;
	_c_cast_time = 0;
	_c_spell_name = "";
	_s_spell_target = NULL;
	_c_spell_target = NULL;
	_s_spell_target_guid = 0;
	_s_spell_cast_game_object_guid = 0;

	_s_entity_type = EntityEnums::EntityType::ENITIY_TYPE_NONE;
	_c_entity_type = EntityEnums::EntityType::ENITIY_TYPE_NONE;

	_s_target = NULL;
	_c_target = NULL;

	/*
       auras = new Vector<AuraData>();
       serverAuras = new Vector<AuraData>();

       c_spell_name = "";

       cTalents = new Vector<PlayerTalent>();
       sTalents = new Vector<PlayerTalent>();
       owner = owner;*/

	/*
       cCraftMaterialInventory = new Vector<ItemInstance>();
       sCraftMaterialInventory = new Vector<ItemInstance>();
       cInventory = new Vector<ItemInstance>();
       sInventory = new Vector<ItemInstance>();
       owner = owner;
       for (int i = 0; i < 21; i += 1) {
       cInventory->Add(null);
       sInventory->Add(null);
       }*/

	for (int i = 0; i < Stat::STAT_ID_TOTAL_STATS; ++i) {
		_stats[i] = Ref<Stat>(memnew(Stat(static_cast<Stat::StatId>(i))));
	}

	get_stat_enum(Stat::STAT_ID_HEALTH)->set_base(10000);
	get_stat_enum(Stat::STAT_ID_MANA)->set_base(100);
	get_stat_enum(Stat::STAT_ID_SPEED)->set_base(4.2);
	get_stat_enum(Stat::STAT_ID_GLOBAL_COOLDOWN)->set_base(1.5);
	get_stat_enum(Stat::STAT_ID_MELEE_CRIT)->set_base(5);
	get_stat_enum(Stat::STAT_ID_MELEE_CRIT_BONUS)->set_base(50);
	get_stat_enum(Stat::STAT_ID_SPELL_CRIT)->set_base(5);
	get_stat_enum(Stat::STAT_ID_SPELL_CRIT_BONUS)->set_base(50);
	get_stat_enum(Stat::STAT_ID_BLOCK)->set_base(10);
	get_stat_enum(Stat::STAT_ID_PARRY)->set_base(15);
	get_stat_enum(Stat::STAT_ID_MELEE_DAMAGE_REDUCTION)->set_base(15);

	_health = Ref<Stat>(get_stat_enum(Stat::STAT_ID_HEALTH));
	_mana = Ref<Stat>(get_stat_enum(Stat::STAT_ID_MANA));
	_speed = Ref<Stat>(get_stat_enum(Stat::STAT_ID_SPEED));
	_gcd = Ref<Stat>(get_stat_enum(Stat::STAT_ID_GLOBAL_COOLDOWN));

	_melee_crit = Ref<Stat>(get_stat_enum(Stat::STAT_ID_MELEE_CRIT));
	_melee_crit_bonus = Ref<Stat>(get_stat_enum(Stat::STAT_ID_MELEE_CRIT_BONUS));
	_spell_crit = Ref<Stat>(get_stat_enum(Stat::STAT_ID_SPELL_CRIT));
	_spell_crit_bonus = Ref<Stat>(get_stat_enum(Stat::STAT_ID_SPELL_CRIT_BONUS));

	_block = Ref<Stat>(get_stat_enum(Stat::STAT_ID_BLOCK));
	_parry = Ref<Stat>(get_stat_enum(Stat::STAT_ID_PARRY));
	_damage_reduction = Ref<Stat>(get_stat_enum(Stat::STAT_ID_DAMAGE_REDUCTION));
	_melee_damage_reduction = Ref<Stat>(get_stat_enum(Stat::STAT_ID_MELEE_DAMAGE_REDUCTION));
	_spell_damage_reduction = Ref<Stat>(get_stat_enum(Stat::STAT_ID_SPELL_DAMAGE_REDUCTION));
	_damage_taken = Ref<Stat>(get_stat_enum(Stat::STAT_ID_DAMAGE_TAKEN));
	_heal_taken = Ref<Stat>(get_stat_enum(Stat::STAT_ID_HEAL_TAKEN));
	_melee_damage = Ref<Stat>(get_stat_enum(Stat::STAT_ID_MELEE_DAMAGE));
	_spell_damage = Ref<Stat>(get_stat_enum(Stat::STAT_ID_SPELL_DAMAGE));

	_s_auras = memnew(Vector<Ref<AuraData> >());
	_c_auras = memnew(Vector<Ref<AuraData> >());

	_s_cooldowns = memnew(Vector<Ref<Cooldown> >());
	_c_cooldowns = memnew(Vector<Ref<Cooldown> >());

	_s_cooldown_map = memnew(CooldownHashMap());
	_c_cooldown_map = memnew(CooldownHashMap());

	_s_category_cooldowns = memnew(Vector<Ref<CategoryCooldown> >());
	_c_category_cooldowns = memnew(Vector<Ref<CategoryCooldown> >());

	_s_category_cooldown_map = memnew(CategoryCooldownHashMap());
	_c_category_cooldown_map = memnew(CategoryCooldownHashMap());
}

Entity::~Entity() {
	_s_auras->clear();
	_c_auras->clear();
	memdelete(_s_auras);
	memdelete(_c_auras);

	_s_cooldowns->clear();
	_c_cooldowns->clear();
	memdelete(_s_cooldowns);
	memdelete(_c_cooldowns);

	_s_cooldown_map->clear();
	_c_cooldown_map->clear();
	memdelete(_s_cooldown_map);
	memdelete(_c_cooldown_map);

	_s_category_cooldowns->clear();
	_c_category_cooldowns->clear();
	memdelete(_s_category_cooldowns);
	memdelete(_c_category_cooldowns);

	_s_category_cooldown_map->clear();
	_c_category_cooldown_map->clear();
	memdelete(_s_category_cooldown_map);
	memdelete(_c_category_cooldown_map);
}

void Entity::initialize(Ref<EntityCreateInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	_s_player_name = info->get_player_name();
	_c_player_name = info->get_player_name();

	sets_entity_type(info->get_entity_type());
	setc_entity_type(info->get_entity_type());

	sets_level(info->get_level());
	setc_level(info->get_level());

	sets_xp(info->get_xp());
	setc_xp(info->get_xp());

	sets_character_class(info->get_character_class());
	//setc_character_class(info->get_character_class());
	/*
	if (gets_character_class() != NULL) {
		Ref<StatData> sd = gets_character_class()->get_stat_data();

		for (int i = 0; i < Stat::STAT_ID_TOTAL_STATS; ++i) {
			Ref<StatDataEntry> entry = sd->get_stat_data_int(i);
			Ref<Stat> stat = get_stat_int(i);

			entry->get_stats_for_stat(stat);

			if (entry->has_dependency()) {
				Ref<Stat> other = get_stat_enum(entry->get_depends_on());

				stat->set_dependency(other, entry->get_dependdency_curve());
			}
		}
	}*/
}

void Entity::sinitialize_stats() {
	//gets_character_class()->get_stat_data()->get_stats_for_stat(_health);
	//Ref<StatDataEntry> e = gets_character_class()->get_stat_data()->get_stat_data_enum(Stat::STAT_ID_HEALTH);

	gets_character_class()->get_stat_data()->get_stat_for_stat(get_health());
	gets_character_class()->get_stat_data()->get_stat_for_stat(get_mana());
	gets_character_class()->get_stat_data()->get_stat_for_stat(get_speed());
	gets_character_class()->get_stat_data()->get_stat_for_stat(get_gcd());
	gets_character_class()->get_stat_data()->get_stat_for_stat(get_melee_crit());
	gets_character_class()->get_stat_data()->get_stat_for_stat(get_melee_crit_bonus());
	gets_character_class()->get_stat_data()->get_stat_for_stat(get_spell_crit());
	gets_character_class()->get_stat_data()->get_stat_for_stat(get_spell_crit_bonus());
	gets_character_class()->get_stat_data()->get_stat_for_stat(get_block());
	gets_character_class()->get_stat_data()->get_stat_for_stat(get_parry());
	gets_character_class()->get_stat_data()->get_stat_for_stat(get_melee_damage_reduction());
	gets_character_class()->get_stat_data()->get_stat_for_stat(get_spell_damage_reduction());
	gets_character_class()->get_stat_data()->get_stat_for_stat(get_damage_taken());
	gets_character_class()->get_stat_data()->get_stat_for_stat(get_heal_taken());
	gets_character_class()->get_stat_data()->get_stat_for_stat(get_melee_damage());
	gets_character_class()->get_stat_data()->get_stat_for_stat(get_spell_damage());
}

//////     Stat System      //////

bool Entity::gets_is_dead() {
	return sIsDead;
}

bool Entity::getc_is_dead() {
	return sIsDead;
}

bool Entity::getc_has_global_cooldown() {
	return _c_gcd >= 0.000000001;
}

bool Entity::gets_has_global_cooldown() {
	return _s_gcd >= 0.000000001;
}

bool Entity::getc_global_cooldown() {
	return _c_gcd;
}

bool Entity::gets_global_cooldown() {
	return _s_gcd;
}

void Entity::sstart_global_cooldown(float value) {
	_s_gcd = value;

	cstart_global_cooldown(value);
}

void Entity::cstart_global_cooldown(float value) {
	_c_gcd = value;
}

////    States    ////

int Entity::gets_state() {
	return _s_state;
}
void Entity::sets_state(int state) {
	_s_state = state;

	emit_signal("sstate_changed", state);
}

int Entity::getc_state() {
	return _c_state;
}
void Entity::setc_state(int state) {
	_c_state = state;

	emit_signal("cstate_changed", state);
}

void Entity::sadd_state_ref(int state_index) {
	ERR_FAIL_INDEX(state_index, EntityEnums::ENTITY_STATE_TYPE_INDEX_MAX);

	if (_s_states[state_index]++ == 0) {
		sets_state(gets_state() | EntityEnums::get_state_flag_for_index(state_index));
	}
}

void Entity::sremove_state_ref(int state_index) {
	ERR_FAIL_INDEX(state_index, EntityEnums::ENTITY_STATE_TYPE_INDEX_MAX);

	if (--_s_states[state_index] == 0) {
		sets_state(gets_state() ^ EntityEnums::get_state_flag_for_index(state_index));
	}
}

Ref<Stat> Entity::get_stat_int(int index) {
	return _stats[index];
}

void Entity::set_stat_int(int index, Ref<Stat> entry) {
	_stats[index] = Ref<Stat>(entry);
}

Ref<Stat> Entity::get_stat_enum(Stat::StatId stat_id) {
	//ERR_FAIL_COND_V(stat_id == Stat::STAT_ID_NONE);

	if (stat_id == Stat::STAT_ID_NONE) {
		print_error("Add fail cond here, stat has STAT_ID_NONE!");
		return _stats[0];
	}

	return _stats[stat_id];
}

void Entity::set_stat_enum(Stat::StatId stat_id, Ref<Stat> entry) {
	ERR_FAIL_COND(!entry.is_valid());

	//ERR_FAIL_COND(stat_id == Stat::STAT_ID_NONE);

	if (stat_id == Stat::STAT_ID_NONE) {
		print_error("Add fail cond here, stat has STAT_ID_NONE!");
		_stats[0] = Ref<Stat>(entry);
		return;
	}

	_stats[stat_id] = Ref<Stat>(entry);
}

void Entity::stake_damage(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	//serverside

	if (gets_is_dead()) {
		return;
	}

	//send it through the passive damage reductions pipeline
	sapply_passives_damage_receive(data);
	//send it through the onbeforehit handler
	son_before_damage(data);
	//send it throug the onhit pipeliine
	son_hit(data);
	son_damage_receive(data);

	int h = get_health()->gets_current() - data->get_damage();

	if (h < 0) {
		h = 0;
	}

	get_health()->sets_current(h);

	//send an event to client
	creceive_damage_taken(data);

	//signal
	emit_signal("son_damage_received", this, data);

	if (get_health()->gets_current() <= 0) {
		die();
	}
}

void Entity::sdeal_damage_to(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	//serverside

	if (gets_is_dead()) {
		return;
	}

	sapply_passives_damage_deal(data);
	data->get_receiver()->stake_damage(data);
	son_damage_dealt(data);
}

void Entity::stake_heal(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	//serverside

	if (gets_is_dead()) {
		return;
	}

	//send it through the passive damage reductions pipeline
	sapply_passives_heal_receive(data);
	//send it through the onbeforehit handler
	son_before_heal(data);

	son_heal_receive(data);

	int h = get_health()->gets_current() + data->get_heal();

	if (h > get_health()->gets_max()) {
		h = get_health()->gets_max();
	}

	get_health()->sets_current(h);

	//send an event to client
	creceive_heal_taken(data);

	//signal
	emit_signal("son_heal_received", this, data);
}

void Entity::sdeal_heal_to(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	//serverside

	if (gets_is_dead()) {
		return;
	}

	sapply_passives_damage_deal(data);
	data->get_receiver()->stake_damage(data);
	son_damage_dealt(data);
}

void Entity::die() {
	/*
	if (!CxNet::IsServer) {
		return;
	}
	sRezTimer = (float)5;
	sIsDead = true;
	if (SOnDeath != null) {
		DELEGATE_INVOKE(SOnDeath);
	}
	SendDieMessage();*/
}

void Entity::resurrect() {
	/*
	if (!CxNet::IsServer) {
		return;
	}
	sIsDead = false;
	SHealth->SetToMax();
	SHealth->Dirty = false;
	if (SOnResurrect != null) {
		DELEGATE_INVOKE(SOnResurrect);
	}
	GameObject *graveyardSpawnPoint = GameObject::FindGameObjectWithTag(new String("StartPosition"))->GetComponent<SpawnPointManager>()->GetGraveyardSpawnPoint();
	owner->transform->position = graveyardSpawnPoint->transform->position;
	owner->transform->rotation = graveyardSpawnPoint->transform->rotation;
	SendResurrectMessage();*/
}

void Entity::creceive_resurrect() {
	/*
	if (OnResurrect != null) {
		DELEGATE_INVOKE(OnResurrect);
	}
	cIsDead = false;
	CHealth->SetToMax();
	CHealth->Dirty = false;*/
}

void Entity::creceive_damage_taken(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	//the current c health should probably be set here.
	emit_signal("con_damage_received", this, data);
}

void Entity::creceiveon_damage_dealt(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	//the current c health should probably be set here.
	emit_signal("con_damage_dealt", this, data);
}

void Entity::creceive_heal_taken(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	//the current c health should probably be set here.
	emit_signal("con_heal_received", this, data);
}

void Entity::creceiveon_heal_dealt(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	//the current c health should probably be set here.
	emit_signal("con_heal_dealt", this, data);
}

void Entity::creceive_died() {
	/*
	cIsDead = true;
	cRezTimer = (float)5;
	if (OnDeath != null) {
		DELEGATE_INVOKE(OnDeath);
	}
	for (int i = 0; i < eventHandlers->Count; i += 1) {
		eventHandlers->GetData(i)->OnDied(owner->transform->gameObject);
	}*/
}

void Entity::creceive_mana_changed(int amount) {
	/*
	Stat *expr_06 = CMana;
	expr_06->Current -= (float)(amount);
	for (int i = 0; i < eventHandlers->Count; i += 1) {
		eventHandlers->GetData(i)->OnManaUse(owner->transform->gameObject, amount, (int)(CMana->Current));
	}*/
}

void Entity::son_before_aura_applied(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_before_aura_applied(data);
	}
}

void Entity::son_after_aura_applied(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		if (ad == data) {
			continue;
		}

		ad->get_aura()->son_after_aura_applied(data);
	}
}

////    Spell System    ////

void Entity::scast_spell(int spell_id) {
	Ref<CharacterClass> cc = gets_character_class();

	if (cc == NULL)
		return;

	cc->start_casting(spell_id, this, 1);
}

void Entity::crequest_spell_cast(int spell_id) {
	scast_spell(spell_id);
}

void Entity::update_auras(float delta) {
	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->supdate(ad, delta);
	}
}

void Entity::son_before_cast(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_before_cast(info);
	}
}

void Entity::son_before_cast_target(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_before_cast_target(info);
	}
}

void Entity::son_hit(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_hit(data);
	}
}

void Entity::son_before_damage(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_before_damage(data);
	}
}

void Entity::son_damage_receive(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_damage_receive(data);
	}
}

void Entity::son_dealt_damage(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_dealt_damage(data);
	}
}

void Entity::son_damage_dealt(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	//serverside
	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_damage_dealt(data);
	}
}

void Entity::son_before_heal(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_before_heal(data);
	}
}

void Entity::son_heal_receive(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_heal_receive(data);
	}
}

void Entity::son_dealt_heal(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_dealt_heal(data);
	}
}

void Entity::son_heal_dealt(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	//serverside
	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_heal_dealt(data);
	}
}

void Entity::sapply_passives_damage_receive(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->sapply_passives_damage_receive(data);
	}
}

void Entity::sapply_passives_damage_deal(Ref<SpellDamageInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->sapply_passives_damage_deal(data);
	}
}

void Entity::sapply_passives_heal_receive(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->sapply_passives_heal_receive(data);
	}
}

void Entity::sapply_passives_heal_deal(Ref<SpellHealInfo> data) {
	ERR_FAIL_COND(!data.is_valid());

	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->sapply_passives_heal_deal(data);
	}
}

void Entity::son_cast_finished(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_cast_finished(info);
	}
}

void Entity::son_cast_started(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_cast_started(info);
	}
}

void Entity::son_cast_failed(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_cast_failed(info);
	}
}

void Entity::son_cast_finished_target(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_cast_finished_target(info);
	}
}

void Entity::sadd_aura(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	son_before_aura_applied(aura);

	aura->set_owner(this);

	_s_auras->push_back(aura);

	son_after_aura_applied(aura);

	emit_signal("saura_added", aura);

	cadd_aura(aura);
}

void Entity::sremove_aura(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	for (int i = 0; i < _s_auras->size(); i++) {
		Ref<AuraData> ad = _s_auras->get(i);

		if (ad == aura) {
			ad->get_aura()->son_remove(ad);

			_s_auras->remove(i);

			break;
		}
	}

	emit_signal("saura_removed", aura);

	cremove_aura(aura);
}

void Entity::sremove_aura_expired(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	for (int i = 0; i < _s_auras->size(); i++) {
		Ref<AuraData> ad = _s_auras->get(i);

		if (ad == aura) {
			ad->get_aura()->son_remove(ad);

			_s_auras->remove(i);

			break;
		}
	}

	emit_signal("saura_removed_expired", aura);

	cremove_aura(aura);
}

void Entity::sremove_aura_dispelled(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	for (int i = 0; i < _s_auras->size(); i++) {
		Ref<AuraData> ad = _s_auras->get(i);

		if (ad == aura) {
			ad->get_aura()->son_remove(ad);

			_s_auras->remove(i);

			break;
		}
	}

	emit_signal("saura_removed_dispelled", aura);

	cremove_aura(aura);
}

void Entity::cadd_aura(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	_c_auras->push_back(data);
	emit_signal("caura_added", data);
}

void Entity::cremove_aura(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	for (int i = 0; i < _c_auras->size(); i++) {
		if (_c_auras->get(i) == aura) {
			_c_auras->remove(i);
			break;
		}
	}

	emit_signal("caura_removed", aura);
}

void Entity::cremove_aura_dispelled(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	for (int i = 0; i < _c_auras->size(); i++) {
		if (_c_auras->get(i) == aura) {
			_c_auras->remove(i);
			break;
		}
	}

	emit_signal("caura_removed_dispelled", aura);
}

void Entity::cremove_aura_expired(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	for (int i = 0; i < _c_auras->size(); i++) {
		if (_c_auras->get(i) == aura) {
			_c_auras->remove(i);
			break;
		}
	}

	emit_signal("caura_removed_expired", aura);
}

int Entity::sget_aura_count() {
	return _s_auras->size();
}

Ref<Aura> Entity::sget_aura(int index) {
	ERR_FAIL_INDEX_V(index, _s_auras->size(), Ref<Aura>(NULL));

	return Ref<Aura>(_s_auras->get(index));
}

int Entity::cget_aura_count() {
	return _s_auras->size();
}

Ref<Aura> Entity::cget_aura(int index) {
	ERR_FAIL_INDEX_V(index, _c_auras->size(), Ref<Aura>(NULL));

	return Ref<Aura>(_c_auras->get(index));
}

void Entity::moved() {
}

void Entity::con_cast_failed(Ref<SpellCastInfo> info) {
}

void Entity::con_cast_started(Ref<SpellCastInfo> info) {
}

void Entity::con_cast_state_changed(Ref<SpellCastInfo> info) {
}

void Entity::con_cast_finished(Ref<SpellCastInfo> info) {
}

void Entity::con_spell_cast_success(Ref<SpellCastInfo> info) {
}

void Entity::setup_on_player_moves(Entity *bopmccc, Vector<int> *sspells) {
}

////    Casting System    ////

void Entity::sstart_casting(Ref<SpellCastInfo> info) {
	_s_spell_cast_info = Ref<SpellCastInfo>(info);

	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_before_cast(info);
	}

	_s_spell_cast_info->set_is_casting(true);

	emit_signal("scast_started", info);

	cstart_casting(info);
}

void Entity::sfail_cast() {
	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_before_cast(_s_spell_cast_info);
	}

	emit_signal("scast_failed", _s_spell_cast_info);
}

void Entity::sdelay_cast() {
	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_before_cast(_s_spell_cast_info);
	}

	emit_signal("scast_delayed", _s_spell_cast_info);
}

void Entity::sfinish_cast() {

	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_cast_finished(_s_spell_cast_info);
	}

	_s_spell_cast_info->get_spell()->sfinish_cast(_s_spell_cast_info);

	emit_signal("scast_finished", _s_spell_cast_info);

	_s_spell_cast_info = Ref<SpellCastInfo>(NULL);

	cfinish_cast();
}

void Entity::sinterrupt_cast() {
	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_before_cast(_s_spell_cast_info);
	}

	emit_signal("scast_interrupted", _s_spell_cast_info);
}

void Entity::cstart_casting(Ref<SpellCastInfo> info) {
	_c_spell_cast_info = Ref<SpellCastInfo>(info);

	emit_signal("ccast_started", _c_spell_cast_info);
}

void Entity::cfail_cast() {
	emit_signal("ccast_failed", _c_spell_cast_info);

	_c_spell_cast_info = Ref<SpellCastInfo>(NULL);
}

void Entity::cdelay_cast() {

	emit_signal("ccast_delayed", _c_spell_cast_info);
}

void Entity::cfinish_cast() {
	emit_signal("ccast_finished", _c_spell_cast_info);
	_c_spell_cast_info = Ref<SpellCastInfo>(NULL);
}

void Entity::cinterrupt_cast() {
	emit_signal("ccast_interrupted", _c_spell_cast_info);
	_c_spell_cast_info = Ref<SpellCastInfo>(NULL);
}

////    Cooldowns    ////
Vector<Ref<Cooldown> > *Entity::gets_cooldowns() {
	return _s_cooldowns;
}
Vector<Ref<Cooldown> > *Entity::getc_cooldowns() {
	return _c_cooldowns;
}

HashMap<int, Ref<Cooldown> > *Entity::gets_cooldown_map() {
	return _s_cooldown_map;
}
HashMap<int, Ref<Cooldown> > *Entity::getc_cooldown_map() {
	return _c_cooldown_map;
}

bool Entity::hass_cooldown(int spell_id) {
	return _s_cooldown_map->has(spell_id);
}
void Entity::adds_cooldown(int spell_id, float value) {
	if (_s_cooldown_map->has(spell_id)) {
		Ref<Cooldown> cd = _s_cooldown_map->get(spell_id);

		cd->set_remaining(value);

		emit_signal("scooldown_added", cd);
		addc_cooldown(spell_id, value);
		return;
	}

	Ref<Cooldown> cd;
	cd.instance();

	_s_cooldown_map->set(spell_id, cd);
	_s_cooldowns->push_back(cd);

	emit_signal("scooldown_added", cd);
	addc_cooldown(spell_id, value);
}
void Entity::removes_cooldown(int spell_id) {
	if (_s_cooldown_map->has(spell_id)) {
		_s_cooldown_map->erase(spell_id);
	}

	for (int i = 0; i < _s_cooldowns->size(); ++i) {
		if (_s_cooldowns->get(i)->get_spell_id() == spell_id) {
			_s_cooldowns->remove(i);
			return;
		}
	}

	emit_signal("scooldown_removed", spell_id);
}
Ref<Cooldown> Entity::gets_cooldown(int spell_id) {
	if (!_s_cooldown_map->has(spell_id)) {
		return Ref<Cooldown>();
	}

	return _s_cooldown_map->get(spell_id);
}
Ref<Cooldown> Entity::gets_cooldown_index(int index) {
	ERR_FAIL_INDEX_V(index, _s_cooldowns->size(), Ref<Cooldown>());

	return _s_cooldowns->get(index);
}
int Entity::gets_cooldown_count() {
	return _s_cooldowns->size();
}

bool Entity::hasc_cooldown(int spell_id) {
	return _c_cooldown_map->has(spell_id);
}
void Entity::addc_cooldown(int spell_id, float value) {
	if (_c_cooldown_map->has(spell_id)) {
		Ref<Cooldown> cd = _c_cooldown_map->get(spell_id);

		cd->set_remaining(value);

		emit_signal("ccooldown_added", cd);
		return;
	}

	Ref<Cooldown> cd;
	cd.instance();

	_c_cooldown_map->set(spell_id, cd);
	_c_cooldowns->push_back(cd);

	emit_signal("ccooldown_added", cd);
}
void Entity::removec_cooldown(int spell_id) {
	if (_c_cooldown_map->has(spell_id)) {
		_c_cooldown_map->erase(spell_id);
	}

	for (int i = 0; i < _c_cooldowns->size(); ++i) {
		if (_c_cooldowns->get(i)->get_spell_id() == spell_id) {
			_c_cooldowns->remove(i);
			return;
		}
	}

	emit_signal("ccooldown_removed", spell_id);
}
Ref<Cooldown> Entity::getc_cooldown(int spell_id) {
	if (!_c_cooldown_map->has(spell_id)) {
		return Ref<Cooldown>();
	}

	return _c_cooldown_map->get(spell_id);
}
Ref<Cooldown> Entity::getc_cooldown_index(int index) {
	ERR_FAIL_INDEX_V(index, _c_cooldowns->size(), Ref<Cooldown>());

	return _c_cooldowns->get(index);
}
int Entity::getc_cooldown_count() {
	return _c_cooldowns->size();
}

//Category Cooldowns
Vector<Ref<CategoryCooldown> > *Entity::gets_category_cooldowns() {
	return _s_category_cooldowns;
}
Vector<Ref<CategoryCooldown> > *Entity::getc_category_cooldowns() {
	return _c_category_cooldowns;
}

HashMap<int, Ref<CategoryCooldown> > *Entity::gets_category_cooldown_map() {
	return _s_category_cooldown_map;
}
HashMap<int, Ref<CategoryCooldown> > *Entity::getc_category_cooldown_map() {
	return _c_category_cooldown_map;
}

bool Entity::hass_category_cooldown(int spell_id) {
	return _s_category_cooldown_map->has(spell_id);
}
void Entity::adds_category_cooldown(int spell_id, float value) {
	if (_s_category_cooldown_map->has(spell_id)) {
		Ref<CategoryCooldown> cc = _s_category_cooldown_map->get(spell_id);

		cc->set_remaining(value);

		emit_signal("scategory_cooldown_added", cc);
		return;
	}

	Ref<CategoryCooldown> cc;
	cc.instance();

	_s_category_cooldown_map->set(spell_id, cc);
	_s_category_cooldowns->push_back(cc);

	emit_signal("scategory_cooldown_added", cc);
}
void Entity::removes_category_cooldown(int category_id) {
	if (_s_category_cooldown_map->has(category_id)) {
		_s_category_cooldown_map->erase(category_id);
	}

	for (int i = 0; i < _s_category_cooldowns->size(); ++i) {
		if (_s_category_cooldowns->get(i)->get_category_id() == category_id) {
			_s_category_cooldowns->remove(i);
			return;
		}
	}

	emit_signal("scategory_cooldown_removed", category_id);
}
Ref<CategoryCooldown> Entity::gets_category_cooldown(int category_id) {
	if (!_s_category_cooldown_map->has(category_id)) {
		return Ref<CategoryCooldown>();
	}

	return _s_category_cooldown_map->get(category_id);
}
Ref<CategoryCooldown> Entity::gets_category_cooldown_index(int index) {
	ERR_FAIL_INDEX_V(index, _s_category_cooldowns->size(), Ref<Cooldown>());

	return _s_category_cooldowns->get(index);
}
int Entity::gets_category_cooldown_count() {
	return _s_category_cooldowns->size();
}

bool Entity::hasc_category_cooldown(int spell_id) {
	return _c_category_cooldown_map->has(spell_id);
}
void Entity::addc_category_cooldown(int spell_id, float value) {
	if (_c_category_cooldown_map->has(spell_id)) {
		Ref<CategoryCooldown> cc = _c_category_cooldown_map->get(spell_id);

		cc->set_remaining(value);

		emit_signal("ccategory_cooldown_added", cc);
		return;
	}

	Ref<CategoryCooldown> cc;
	cc.instance();

	_c_category_cooldown_map->set(spell_id, cc);
	_c_category_cooldowns->push_back(cc);

	emit_signal("ccategory_cooldown_added", cc);
}
void Entity::removec_category_cooldown(int category_id) {
	if (_c_category_cooldown_map->has(category_id)) {
		_c_category_cooldown_map->erase(category_id);
	}

	for (int i = 0; i < _c_category_cooldowns->size(); ++i) {
		if (_c_category_cooldowns->get(i)->get_category_id() == category_id) {
			_c_category_cooldowns->remove(i);
			return;
		}
	}

	emit_signal("ccategory_cooldown_removed", category_id);
}
Ref<CategoryCooldown> Entity::getc_category_cooldown(int category_id) {
	if (!_c_category_cooldown_map->has(category_id)) {
		return Ref<CategoryCooldown>();
	}

	return _c_category_cooldown_map->get(category_id);
}
Ref<CategoryCooldown> Entity::getc_category_cooldown_index(int index) {
	ERR_FAIL_INDEX_V(index, _c_category_cooldowns->size(), Ref<Cooldown>());

	return _c_category_cooldowns->get(index);
}
int Entity::getc_category_cooldown_count() {
	return _c_category_cooldowns->size();
}


Ref<SpellCastInfo> Entity::gets_spell_cast_info() {
	return Ref<SpellCastInfo>(_s_spell_cast_info);
}

void Entity::sets_spell_cast_info(Ref<SpellCastInfo> info) {
	_s_spell_cast_info = Ref<SpellCastInfo>(info);
}

Ref<SpellCastInfo> Entity::getc_spell_cast_info() {
	return Ref<SpellCastInfo>(_c_spell_cast_info);
}

void Entity::setc_spell_cast_info(Ref<SpellCastInfo> info) {
	_c_spell_cast_info = Ref<SpellCastInfo>(info);
}

void Entity::son_death() {
}

void Entity::sremove_auras_with_group(int aura_group) {
	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		if (ad->get_aura()->get_aura_group() == aura_group) {

			cremove_aura(ad);

			_s_auras->remove(i);

			emit_signal("saura_removed", ad);

			cremove_aura(ad);

			i--;
		}
	}
}

Entity *Entity::gets_target() {
	return _s_target;
}

void Entity::sets_target(Node *p_target) {
	if (p_target == NULL) {
		_s_target = NULL;
		emit_signal("starget_changed", _s_target);
		setc_target(p_target);
		return;
	}

	Entity *e = cast_to<Entity>(p_target);

	if (!e) {
		return;
	}

	_s_target = e;

	emit_signal("starget_changed", _s_target);

	setc_target(p_target);
}

Entity *Entity::getc_target() {
	return _c_target;
}

void Entity::setc_target(Node *p_target) {
	if (p_target == NULL) {
		_c_target = NULL;

		emit_signal("ctarget_changed", _c_target);

		return;
	}

	Entity *e = cast_to<Entity>(p_target);

	if (!e) {
		return;
	}

	_c_target = e;

	emit_signal("ctarget_changed", _c_target);
}

////    TalentCOmponent    ////

void Entity::csend_request_rank_increase(int talentID) {
	/*
       if (CxNet::IsServer) {
       CSendRequestRankIncreaseMsg cSendRequestRankIncreaseMsg = CSendRequestRankIncreaseMsg();
       cSendRequestRankIncreaseMsg.Guid = owner->PlayerData->GUID;
       cSendRequestRankIncreaseMsg.TalentId = talentID;
       cSendRequestRankIncreaseMsg.Serialize(CxNet::NetBuffer);
       CxNet::SendBufferToAllClients(0);
       }*/
}

void Entity::csend_request_rank_decrease(int talentID) {
	/*
       if (CxNet::IsServer) {
       CSendRequestRankDecreaseMsg cSendRequestRankDecreaseMsg = CSendRequestRankDecreaseMsg();
       cSendRequestRankDecreaseMsg.Guid = owner->PlayerData->GUID;
       cSendRequestRankDecreaseMsg.TalentId = talentID;
       cSendRequestRankDecreaseMsg.Serialize(CxNet::NetBuffer);
       CxNet::SendBufferToAllClients(0);
       }*/
}

void Entity::ssend_rank(int talentID, int rank) {
	/*
       if (CxNet::IsServer) {
       SSendRankValueMsg sSendRankValueMsg = SSendRankValueMsg();
       sSendRankValueMsg.Guid = owner->PlayerData->GUID;
       sSendRankValueMsg.TalentId = talentID;
       sSendRankValueMsg.Rank = rank;
       sSendRankValueMsg.Serialize(CxNet::NetBuffer);
       CxNet::SendBufferToAllClients(0);
       }*/
}

void Entity::sreceive_rank_increase(int talentID) {
	/*
       PlayerTalent *playerTalent = SGetTalent(talentID, true);
       if (owner->PlayerData->Character == null) {
       return;
       }
       Talent *talent = Talents::Instance->GetData(talentID);
       if (talent == null) {
       return;
       }
       if (talent->MaxRank >= playerTalent->getRank()) {
       PlayerTalent *expr_47 = playerTalent;
       int rank = expr_47->getRank();
       expr_47->setRank(rank + 1);
       SSendRank(talentID, playerTalent->getRank());
       }*/
}

void Entity::sreceive_rank_decrease(int talentID) {
	/*
       PlayerTalent *playerTalent = SGetTalent(talentID, false);
       if (playerTalent == null) {
       return;
       }
       if (playerTalent->getRank() > 0) {
       PlayerTalent *expr_17 = playerTalent;
       int rank = expr_17->getRank();
       expr_17->setRank(rank - 1);
       SSendRank(talentID, playerTalent->getRank());
       }*/
}

void Entity::creceive_rank(int talentID, int rank) {
	/*
       PlayerTalent *playerTalent = CGetTalent(talentID, true);
       if (owner->PlayerData->Character == null) {
       return;
       }
       Talent *talent = Talents::Instance->GetData(talentID);
       if (talent == null) {
       return;
       }
       if (talent->MaxRank >= playerTalent->getRank()) {
       PlayerTalent *expr_47 = playerTalent;
       int rank2 = expr_47->getRank();
       expr_47->setRank(rank2 + 1);
       if (OnCTalenChangedAction != null) {
       DELEGATE_INVOKE(OnCTalenChangedAction);
       }
       }*/
}

PlayerTalent *Entity::sget_talent(int id, bool create) {
	/*
       for (int i = 0; i < sTalents->Count; i += 1) {
       if (sTalents->GetData(i)->TalentID == id) {
       return sTalents->GetData(i);
       }
       }
       if (create) {
       PlayerTalent *playerTalent = new PlayerTalent(id);
       sTalents->Add(playerTalent);
       return playerTalent;
       }
       return null;*/

	return NULL;
}

PlayerTalent *Entity::cget_talent(int id, bool create) {
	/*
       for (int i = 0; i < cTalents->Count; i += 1) {
       if (cTalents->GetData(i)->TalentID == id) {
       return cTalents->GetData(i);
       }
       }
       if (create) {
       PlayerTalent *playerTalent = new PlayerTalent(id);
       cTalents->Add(playerTalent);
       return playerTalent;
       }
       return null;*/

	return NULL;
}

////    Inventory    ////

Ref<Bag> Entity::gets_bag(int index) {
    ERR_FAIL_INDEX_V(index, MAX_BAG_SLOTS, Ref<Bag>());
    
	return _s_bags[index];
}

Ref<Bag> Entity::getc_bag(int index) {
    ERR_FAIL_INDEX_V(index, MAX_BAG_SLOTS, Ref<Bag>());
     
	return _c_bags[index];
}

void Entity::sadd_craft_material(int itemId, int count) {
	/*
       for (int i = 0; i < sCraftMaterialInventory->Count; i += 1) {
       ItemInstance *itemInstance = sCraftMaterialInventory->GetData(i);
       if (itemInstance->getItemID() == itemId) {
       ItemInstance *expr_1B = itemInstance;
       expr_1B->setCount(count);
       SSendAddCraftMaterial(itemId, count);
       if (SOnCraftMaterialAdded != null) {
       DELEGATE_INVOKE(SOnCraftMaterialAdded, itemInstance);
       }
       return;
       }
       }
       ItemInstance *itemInstance2 = new ItemInstance(itemId, count);
       sCraftMaterialInventory->Add(itemInstance2);
       SSendAddCraftMaterial(itemId, count);
       if (SOnCraftMaterialAdded != null) {
       DELEGATE_INVOKE(SOnCraftMaterialAdded, itemInstance2);
       }*/
}

void Entity::sremove_craft_material(int itemId, int count) {
	/*
       for (int i = 0; i < sCraftMaterialInventory->Count; i += 1) {
       ItemInstance *itemInstance = sCraftMaterialInventory->GetData(i);
       if (itemInstance->getItemID() == itemId) {
       ItemInstance *expr_21 = itemInstance;
       expr_21->setCount(count);
       if (itemInstance->getCount() <= 0) {
       if (itemInstance->getCount() < 0) {
       Array<Object> *expr_46 = new Array<Object>(4);
       expr_46->SetData(0, new String("inventory->SRemoveCraftMaterial: Material count was less than 0. Itemid="));
       expr_46->SetData(1, BOX<int>(itemId));
       expr_46->SetData(2, new String(" player="));
       expr_46->SetData(3, owner->gameObject->name);
       Debug::Log(String::Concat(expr_46));
       }
       sCraftMaterialInventory->RemoveAt(i);
       }
       SSendRemoveCraftMaterial(itemId, count);
       if (SOnCraftMaterialRemoved != null) {
       DELEGATE_INVOKE(SOnCraftMaterialRemoved);
       }
       return;
       }
       }
       Array<Object> *expr_BF = new Array<Object>(4);
       expr_BF->SetData(0, new String("inventory->SRemoveCraftMaterial: Material didn't exist in player's inventory. Itemid="));
       expr_BF->SetData(1, BOX<int>(itemId));
       expr_BF->SetData(2, new String(" player="));
       expr_BF->SetData(3, owner->gameObject->name);
       Debug::Log(String::Concat(expr_BF));*/
}

bool Entity::stry_to_add_item(int itemId, int count) {
	/*
       int num = -1;
       for (int i = 0; i < getSInventory()->Count; i += 1) {
       ItemInstance *itemInstance = getSInventory()->GetData(i);
       if (itemInstance == null) {
       if (num == -1) {
       num = i;
       }
       } else {
       if (itemInstance->getItemID() == itemId) {
       ItemInstance *expr_28 = itemInstance;
       expr_28->setCount(count);
       SSendAddItem(i, itemId, count);
       if (SOnItemAdded != null) {
       DELEGATE_INVOKE(SOnItemAdded, itemInstance);
       }
       return true;
       }
       }
       }
       if (num == -1) {
       return false;
       }
       ItemInstance *itemInstance2 = new ItemInstance(itemId, count);
       getSInventory()->SetData(num, itemInstance2);
       SSendAddItem(num, itemId, count);
       if (SOnItemAdded != null) {
       DELEGATE_INVOKE(SOnItemAdded, itemInstance2);
       }
       return true;*/

	return false;
}

bool Entity::stry_to_remove_item(int itemId, int count) {
	/*
       int i = 0;
       while (i < getSInventory()->Count) {
       ItemInstance *itemInstance = getSInventory()->GetData(i);
       if ((itemInstance != null) && (itemInstance->getItemID() == itemId)) {
       if (itemInstance->getCount() < count) {
       return false;
       }
       if (itemInstance->getCount() == count) {
       getSInventory()->SetData(i, null);
       if (SOnItemRemoved != null) {
       DELEGATE_INVOKE(SOnItemRemoved);
       }
       SSendRemoveItem(i);
       return true;
       }
       ItemInstance *expr_5E = itemInstance;
       expr_5E->setCount(count);
       SSendChangeItemCount(i, itemInstance->getCount());
       if (SOnItemCountChanged != null) {
       DELEGATE_INVOKE(SOnItemCountChanged, itemInstance);
       }
       return true;
       } else {
       i += 1;
       }
       }
       return false;*/

	return false;
}

void Entity::ssend_add_item(int slotId, int itemId, int count) {
	/*
       if (CxNet::IsServer && (owner->Connection != null)) {
       SSendAddItemMsg sSendAddItemMsg = SSendAddItemMsg();
       sSendAddItemMsg.SlotId = slotId;
       sSendAddItemMsg.ItemId = itemId;
       sSendAddItemMsg.Count = count;
       sSendAddItemMsg.Serialize(CxNet::NetBuffer);
       owner->Connection->SendBuffer(0, CxNet::NetBuffer);
       }*/
}

void Entity::ssend_change_item_count(int slotId, int count) {
	/*
       if (CxNet::IsServer && (owner->Connection != null)) {
       SSendChangeItemCountMsg sSendChangeItemCountMsg = SSendChangeItemCountMsg();
       sSendChangeItemCountMsg.SlotId = slotId;
       sSendChangeItemCountMsg.Count = count;
       sSendChangeItemCountMsg.Serialize(CxNet::NetBuffer);
       owner->Connection->SendBuffer(0, CxNet::NetBuffer);
       }*/
}

void Entity::ssend_remove_item(int slotId) {
	/*
       if (CxNet::IsServer && (owner->Connection != null)) {
       SSendRemoveItemMsg sSendRemoveItemMsg = SSendRemoveItemMsg();
       sSendRemoveItemMsg.SlotId = slotId;
       sSendRemoveItemMsg.Serialize(CxNet::NetBuffer);
       owner->Connection->SendBuffer(0, CxNet::NetBuffer);
       }*/
}

void Entity::ssend_move_item(int slot1, int slot2) {
	/*
       if (CxNet::IsServer && (owner->Connection != null)) {
       SSendMoveItemMsg sSendMoveItemMsg = SSendMoveItemMsg();
       sSendMoveItemMsg.Slot1 = slot1;
       sSendMoveItemMsg.Slot2 = slot2;
       sSendMoveItemMsg.Serialize(CxNet::NetBuffer);
       owner->Connection->SendBuffer(0, CxNet::NetBuffer);
       }*/
}

void Entity::ssend_sent_items(String items) {
	/*
       if (CxNet::IsServer && (owner->Connection != null)) {
       SSendSentItemsMsg sSendSentItemsMsg = SSendSentItemsMsg();
       sSendSentItemsMsg.Items = items;
       sSendSentItemsMsg.Serialize(CxNet::NetBuffer);
       owner->Connection->SendBuffer(0, CxNet::NetBuffer);
       }*/
}

void Entity::csend_swap_items(int slot1, int slot2) {
	/*
       if (CxNet::IsServer && (owner->Connection != null)) {
       CSendSwapItemsMsg cSendSwapItemsMsg = CSendSwapItemsMsg();
       cSendSwapItemsMsg.Slot1 = slot1;
       cSendSwapItemsMsg.Slot2 = slot2;
       cSendSwapItemsMsg.Serialize(CxNet::NetBuffer);
       CxNet::SendBufferToServer(0);
       }*/
}

void Entity::csend_craft_item_request(int craftId) {
	/*
       if (CxNet::IsServer && (owner->Connection != null)) {
       CSendCraftItemRequestMsg cSendCraftItemRequestMsg = CSendCraftItemRequestMsg();
       cSendCraftItemRequestMsg.CraftId = craftId;
       cSendCraftItemRequestMsg.Serialize(CxNet::NetBuffer);
       CxNet::SendBufferToServer(0);
       }*/
}

void Entity::ssend_add_craft_material(int itemId, int count) {
	/*
       if (CxNet::IsServer && (owner->Connection != null)) {
       SSendAddCraftMaterialMsg sSendAddCraftMaterialMsg = SSendAddCraftMaterialMsg();
       sSendAddCraftMaterialMsg.ItemId = itemId;
       sSendAddCraftMaterialMsg.Count = count;
       sSendAddCraftMaterialMsg.Serialize(CxNet::NetBuffer);
       owner->Connection->SendBuffer(0, CxNet::NetBuffer);
       }*/
}

void Entity::ssend_remove_craft_material(int itemId, int count) {
	/*
       if (CxNet::IsServer && (owner->Connection != null)) {
       SSendRemoveCraftMaterialMsg sSendRemoveCraftMaterialMsg = SSendRemoveCraftMaterialMsg();
       sSendRemoveCraftMaterialMsg.ItemId = itemId;
       sSendRemoveCraftMaterialMsg.Count = count;
       sSendRemoveCraftMaterialMsg.Serialize(CxNet::NetBuffer);
       owner->Connection->SendBuffer(0, CxNet::NetBuffer);
       }*/
}

void Entity::ssend_sent_craft_materials(String materials) {
	/*
       if (CxNet::IsServer && (owner->Connection != null)) {
       SSendSentCraftMaterialsMsg sSendSentCraftMaterialsMsg = SSendSentCraftMaterialsMsg();
       sSendSentCraftMaterialsMsg.Materials = materials;
       sSendSentCraftMaterialsMsg.Serialize(CxNet::NetBuffer);
       owner->Connection->SendBuffer(0, CxNet::NetBuffer);
       }*/
}

void Entity::creceive_add_item(int slotId, int itemId, int count) {
	/*
       if (getCInventory()->GetData(slotId) == null) {
       getCInventory()->SetData(slotId, new ItemInstance(itemId, count));
       } else {
       if (getCInventory()->GetData(slotId)->ItemID != itemId) {
       Array<Object> *expr_40 = new Array<Object>(6);
       expr_40->SetData(0, new String("Item did not match in slot "));
       expr_40->SetData(1, BOX<int>(slotId));
       expr_40->SetData(2, new String(" "));
       expr_40->SetData(3, BOX<int>(itemId));
       expr_40->SetData(4, new String(" orig id: "));
       expr_40->SetData(5, BOX<int>(getCInventory()->GetData(slotId)->ItemID));
       Debug::Log(String::Concat(expr_40));
       getCInventory()->GetData(slotId)->ItemID = itemId;
       }
       ItemInstance *expr_AB = getCInventory()->GetData(slotId);
       expr_AB->setCount(count);
       }
       if (COnItemAdded != null) {
       DELEGATE_INVOKE(COnItemAdded, getCInventory()->GetData(slotId));
       }*/
}

void Entity::creceive_change_item_count(int slotId, int count) {
	/*
       if (getCInventory()->GetData(slotId) == null) {
       return;
       }
       getCInventory()->GetData(slotId)->ItemID = count;
       if (COnItemCountChanged != null) {
       DELEGATE_INVOKE(COnItemCountChanged, getCInventory()->GetData(slotId));
       }*/
}

void Entity::creceive_remove_item(int slotId) {
	/*
       getCInventory()->SetData(slotId, null);
       if (COnItemRemoved != null) {
       DELEGATE_INVOKE(COnItemRemoved);
       }*/
}

void Entity::creceive_move_item(int slot1, int slot2) {
	/*
       if ((slot1 >= getCInventory()->Count) || (slot2 >= getCInventory()->Count)) {
       return;
       }
       if ((getCInventory()->GetData(slot1) == null) && (getCInventory()->GetData(slot2) == null)) {
       return;
       }
       ItemInstance *value = getCInventory()->GetData(slot1);
       getCInventory()->SetData(slot1, getCInventory()->GetData(slot2));
       getCInventory()->SetData(slot2, value);
       if (COnItemMoved != null) {
       DELEGATE_INVOKE(COnItemMoved);
       }*/
}

void Entity::creceive_add_craft_material(int itemId, int count) {
	/*
       for (int i = 0; i < cCraftMaterialInventory->Count; i += 1) {
       ItemInstance *itemInstance = cCraftMaterialInventory->GetData(i);
       if (itemInstance->getItemID() == itemId) {
       ItemInstance *expr_1B = itemInstance;
       expr_1B->setCount(count);
       if (COnCraftMaterialAdded != null) {
       DELEGATE_INVOKE(COnCraftMaterialAdded, itemInstance);
       }
       return;
       }
       }
       ItemInstance *itemInstance2 = new ItemInstance(itemId, count);
       cCraftMaterialInventory->Add(itemInstance2);
       if (COnCraftMaterialAdded != null) {
       DELEGATE_INVOKE(COnCraftMaterialAdded, itemInstance2);
       }*/
}

void Entity::creceive_remove_craft_material(int itemId, int count) {
	/*
       for (int i = 0; i < getCCraftMaterialInventory()->Count; i += 1) {
       ItemInstance *itemInstance = getCCraftMaterialInventory()->GetData(i);
       if (itemInstance->getItemID() == itemId) {
       ItemInstance *expr_1B = itemInstance;
       expr_1B->setCount(count);
       if (itemInstance->getCount() <= 0) {
       getCCraftMaterialInventory()->RemoveAt(i);
       }
       if (COnCraftMaterialRemoved != null) {
       DELEGATE_INVOKE(COnCraftMaterialRemoved);
       }
       return;
       }
       }*/
}

void Entity::creceive_sent_craft_materials(String materials) {
	/*
       Array<char> *expr_07 = new Array<char>(1);
       expr_07->SetData(0, ';');
       Array<String> *array = materials->Split(expr_07);
       for (int i = 0; i < (array->Length - 1); i += 1) {
       String arg_24_0 = array->GetData(i);
       Array<char> *expr_1F = new Array<char>(1);
       expr_1F->SetData(0, '=');
       Array<String> *array2 = arg_24_0->Split(expr_1F);
       ItemInstance *item = new ItemInstance(BSConvert::ToInt(array2->GetData(0)), BSConvert::ToInt(array2->GetData(1)));
       getCCraftMaterialInventory()->Add(item);
       }
       if (COnCraftMaterialsLoaded != null) {
       DELEGATE_INVOKE(COnCraftMaterialsLoaded);
       }*/
}

void Entity::creceive_sent_items(String items) {
	/*
       Array<char> *expr_07 = new Array<char>(1);
       expr_07->SetData(0, ';');
       Array<String> *array = items->Split(expr_07);
       for (int i = 0; i < (array->Length - 1); i += 1) {
       String arg_24_0 = array->GetData(i);
       Array<char> *expr_1F = new Array<char>(1);
       expr_1F->SetData(0, '=');
       Array<String> *array2 = arg_24_0->Split(expr_1F);
       ItemInstance *value = new ItemInstance(BSConvert::ToInt(array2->GetData(1)), BSConvert::ToInt(array2->GetData(2)));
       getCInventory()->SetData(BSConvert::ToInt(array2->GetData(0)), value);
       }
       if (COnItemsLoaded != null) {
       DELEGATE_INVOKE(COnItemsLoaded);
       }*/
}

void Entity::sreceive_swap_items(int slot1, int slot2) {
	/*
       if ((slot1 >= getSInventory()->Count) || (slot2 >= getSInventory()->Count)) {
       return;
       }
       if ((getSInventory()->GetData(slot1) == null) && (getSInventory()->GetData(slot2) == null)) {
       return;
       }
       ItemInstance *value = getSInventory()->GetData(slot1);
       getSInventory()->SetData(slot1, getSInventory()->GetData(slot2));
       getSInventory()->SetData(slot2, value);
       SSendMoveItem(slot1, slot2);
       if (SOnItemMoved != null) {
       DELEGATE_INVOKE(SOnItemMoved);
       }*/
}

void Entity::send_all_items() {
	/*
       StringBuilder *StringBuilder = new StringBuilder();
       for (int i = 0; i < getSCraftMaterialInventory()->Count; i += 1) {
       StringBuilder->Append(getSCraftMaterialInventory()->GetData(i)->ItemID);
       StringBuilder->Append('=');
       StringBuilder->Append(getSCraftMaterialInventory()->GetData(i)->Count);
       StringBuilder->Append(';');
       if (StringBuilder->Length >= 700) {
       SSendSentCraftMaterials(StringBuilder->ToString());
       StringBuilder->Remove(0, StringBuilder->Length);
       }
       }
       SSendSentCraftMaterials(StringBuilder->ToString());
       if (StringBuilder->Length > 0) {
       StringBuilder->Remove(0, StringBuilder->Length);
       }
       for (int j = 0; j < getSInventory()->Count; j += 1) {
       if (getSInventory()->GetData(j) != null) {
       StringBuilder->Append(j);
       StringBuilder->Append('=');
       StringBuilder->Append(getSInventory()->GetData(j)->ItemID);
       StringBuilder->Append('=');
       StringBuilder->Append(getSInventory()->GetData(j)->Count);
       StringBuilder->Append(';');
       }
       }
       SSendSentItems(StringBuilder->ToString());*/
}

bool Entity::shas_craft_material(int itemId, int count) {
	/*
       for (int i = 0; i < getSCraftMaterialInventory()->Count; i += 1) {
       if ((getSCraftMaterialInventory()->GetData(i)->ItemID == itemId) && (getSCraftMaterialInventory()->GetData(i)->Count >= count)) {
       return true;
       }
       }
       return false;*/

	return false;
}

bool Entity::shas_item(int itemId, int count) {
	/*
       for (int i = 0; i < getSInventory()->Count; i += 1) {
       if (((getSInventory()->GetData(i) != null) && (getSInventory()->GetData(i)->ItemID == itemId)) && (getSInventory()->GetData(i)->Count >= count)) {
       return true;
       }
       }
       return false;*/

	return false;
}

bool Entity::chas_craft_material(int itemId, int count) {
	/*
       for (int i = 0; i < getCCraftMaterialInventory()->Count; i += 1) {
       if ((getCCraftMaterialInventory()->GetData(i)->ItemID == itemId) && (getCCraftMaterialInventory()->GetData(i)->Count >= count)) {
       return true;
       }
       }
       return false;*/

	return false;
}

bool Entity::chas_item(int itemId, int count) {
	/*
       for (int i = 0; i < getCInventory()->Count; i += 1) {
       if (((getCInventory()->GetData(i) != null) && (getCInventory()->GetData(i)->ItemID == itemId)) && (getCInventory()->GetData(i)->Count >= count)) {
       return true;
       }
       }
       return false;*/

	return false;
}

int Entity::cget_item_count(int itemId) {
	/*
       for (int i = 0; i < getCInventory()->Count; i += 1) {
       if ((getCInventory()->GetData(i) != null) && (getCInventory()->GetData(i)->ItemID == itemId)) {
       return getCInventory()->GetData(i)->Count;
       }
       }
       return 0;*/

	return 0;
}

int Entity::sget_item_count(int itemId) {
	/*
       for (int i = 0; i < getSInventory()->Count; i += 1) {
       if ((getSInventory()->GetData(i) != null) && (getSInventory()->GetData(i)->ItemID == itemId)) {
       return getSInventory()->GetData(i)->Count;
       }
       }
       return 0;*/

	return 0;
}

int Entity::cget_craft_material_count(int itemId) {
	/*
       for (int i = 0; i < getCCraftMaterialInventory()->Count; i += 1) {
       if (getCCraftMaterialInventory()->GetData(i)->ItemID == itemId) {
       return getCCraftMaterialInventory()->GetData(i)->Count;
       }
       }
       return 0;*/

	return 0;
}

int Entity::sget_craft_material_count(int itemId) {
	/*
       for (int i = 0; i < getSCraftMaterialInventory()->Count; i += 1) {
       if (getSCraftMaterialInventory()->GetData(i)->ItemID == itemId) {
       return getSCraftMaterialInventory()->GetData(i)->Count;
       }
       }
       return 0;*/

	return 0;
}

bool Entity::ccan_craft(CraftDataAttribute *cda) {
	/*
       for (int i = 0; i < cda->RequiredItems->Count; i += 1) {
       if (!CHasItem(cda->RequiredItems->GetData(i), 1)) {
       return false;
       }
       }
       for (int j = 0; j < cda->RequiredMaterials->Count; j += 1) {
       CraftDataAttributeHelper *craftDataAttributeHelper = cda->RequiredMaterials->GetData(j);
       if (!CHasCraftMaterial(craftDataAttributeHelper->ItemId, craftDataAttributeHelper->Count)) {
       return false;
       }
       }
       return true;*/

	return false;
}

bool Entity::ctry_to_craft(CraftDataAttribute *cda) {
	/*
       if (!CCanCraft(cda)) {
       return false;
       }
       CSendCraftItemRequest(cda->Id);
       return true;*/

	return false;
}

bool Entity::scan_craft(CraftDataAttribute *cda) {
	/*
       for (int i = 0; i < cda->RequiredItems->Count; i += 1) {
       if (!SHasItem(cda->RequiredItems->GetData(i), 1)) {
       return false;
       }
       }
       for (int j = 0; j < cda->RequiredMaterials->Count; j += 1) {
       CraftDataAttributeHelper *craftDataAttributeHelper = cda->RequiredMaterials->GetData(j);
       if (!SHasCraftMaterial(craftDataAttributeHelper->ItemId, craftDataAttributeHelper->Count)) {
       return false;
       }
       }
       return true;*/

	return false;
}

void Entity::scraft(CraftDataAttribute *cda) {
	/*
       if (!STryToAddItem(cda->Item->ItemId, cda->Item->Count)) {
       return;
       }
       for (int i = 0; i < cda->RequiredMaterials->Count; i += 1) {
       CraftDataAttributeHelper *craftDataAttributeHelper = cda->RequiredMaterials->GetData(i);
       SRemoveCraftMaterial(craftDataAttributeHelper->ItemId, craftDataAttributeHelper->Count);
       }*/
}

void Entity::sreceive_craft_item_msg(int craftId) {
	/*
       CraftDataLoader *instance = CraftDataLoader::Instance;
       if (instance == null) {
       return;
       }
       CraftDataAttribute *craftDataWithId = instance->getCraftDataWithId(craftId);
       if (craftDataWithId == null) {
       return;
       }
       if (!SCanCraft(craftDataWithId)) {
       return;
       }
       SCraft(craftDataWithId);*/
}

void Entity::cswap_items_in_slots(int slot1, int slot2) {
	/*
       if ((slot1 >= getCInventory()->Count) || (slot2 >= getCInventory()->Count)) {
       return;
       }
       if ((getCInventory()->GetData(slot1) == null) && (getCInventory()->GetData(slot2) == null)) {
       return;
       }
       CSendSwapItems(slot1, slot2); */
}

void Entity::loaded() {
	//sendstate = true;
}

////    PlayerData    ////

void Entity::reward_xp_for_mob(int level) {
	/*
       int l = level - Level;

       if (Mathf.Abs(l) > 5) {
       if (l < 0) {
       l = -5;
       } else {
       l = 5;
       }
       }

       l += 5;

       Xp += (l * 20);*/
}

void Entity::level_up(int num) {
	/*
       Xp = 0;
       Level += num;

       if (SOnLevelUp != null) {
       SOnLevelUp(owner);
       }

       RpcLevelUp();*/
}

void Entity::set_level_without_modifiers(int newLevel, bool a) {
	/*
       level = newLevel;

       if (SOnLevelChanged != null) {
       SOnLevelChanged(owner, newLevel);
       }*/
}

void Entity::apply_level_modifiers() {
	/*
       owner.Stats.SHealth.Modifiers.Remove(-10);

       owner.Stats.SHealth.Modifiers.Add(-10, 0f, -((1 - character.Stats.HPScaling.Evaluate((float)Level)) * 100f));*/
}

void Entity::rpc_level_up() {
	/*
       if (COnLevelUp != null) {
       COnLevelUp(owner);
       }*/
}

void Entity::registers() {
	/*
       if (aiPlayer) {
       Entity.CRegisterAIPlayer(GUID, owner);

       if (owner.isServer) {
       Entity.SRegisterAIPlayer(GUID, owner);
       }

    //  owner.OnPlayerSpawned(owner, owner.isClient, owner.isServer, owner.isLocalPlayer);

    return;
    }

    if (isLocalPlayer) {
    Entity.RegisterLocalPlayer(GUID, owner);

    //Let's call the playerFactory, so it can modify this instance
    // owner.OnPlayerSpawned(owner, owner.isClient, owner.isServer, owner.isLocalPlayer);

    return;
    }

    if (owner.isClient) {
    Entity.CRegisterNetworkedPlayer(GUID, owner);

    if (owner.isServer) {
    Entity.SRegisterNetworkedPlayer(GUID, owner);
    }

    //Let's call the playerFactory, so it can modify this instance
    //   owner.OnPlayerSpawned(owner, owner.isClient, owner.isServer, owner.isLocalPlayer);
    }
    */

	/*
       pl.CRegisterAIPlayer(transform.gameObject);

       if (isServer)
       {
       pl.SRegisterAIPlayer(transform.gameObject);
       }

    //Let's call the playerFactory, so it can modify this instance
    pf.OnPlayerSpawned(gameObject, isClient, isServer, isLocalPlayer);*/
}

void Entity::update(float delta) {
    for (int i = 0; i < _s_cooldowns->size(); ++i) {
        Ref<Cooldown> cd = _s_cooldowns->get(i);
        
        if (cd->update(delta)) {
            removes_cooldown(cd->get_spell_id());
            --i;
        }
    }
    
    for (int i = 0; i < _s_category_cooldowns->size(); ++i) {
        Ref<CategoryCooldown> cd = _s_category_cooldowns->get(i);
        
        if (cd->update(delta)) {
            removes_category_cooldown(cd->get_category_id());
            --i;
        }
    }
    
	update_auras(delta);

	if (_s_spell_cast_info.is_valid() && _s_spell_cast_info->get_is_casting()) {
		if (_s_spell_cast_info->update_cast_time(delta)) {
			sfinish_cast();
		}
	}
}

void Entity::Update() {
	/*
       getInventory()->Update();
       getPlayerFacingComponent()->Update();
       getStateComponent()->Update();
       getPlayerSpellDataComponent()->Update();
       getOpmcc()->Update();
       getEntity()->Update();
       getFactionComponent()->Update();*/

	/*
       if (owner->isServer && sendstate) {
       sendstate = false;
       SendAllItems();
       } */

	/*
       if (send && owner->isServer) {
       send = false;
       for (int i = 0; i < getSSpellData()->Count; i += 1) {
       PlayerSpellData *playerSpellData = getSSpellData()->GetData(i);
       if (is_inst_of<PlayerSpellCooldownData *>(playerSpellData)) {
       PlayerSpellCooldownData *playerSpellCooldownData = as_cast<PlayerSpellCooldownData *>(playerSpellData);
       SSendAddCPlayerSpellCooldownData(playerSpellCooldownData->SpellId, playerSpellCooldownData->getCooldown(), playerSpellCooldownData->getRemainingCooldown());
       }
       }
       }
       for (int j = 0; j < sSpellData->Count; j += 1) {
       sSpellData->GetData(j)->Update(this);
       }
       for (int k = 0; k < cSpellData->Count; k += 1) {
       cSpellData->GetData(k)->Update(this);
       }*/

	/*
       if (owner->PlayerData->State != PlayerStates::STATE_NORMAL) {
       return;
       }
       if (getSCasting()) {
       setSCurrentCastTime(Time::deltaTime);
       if (getSCurrentCastTime() >= getSCastTime()) {
       SCastFinished();
       }
       }
       if (getCCasting()) {
       setCCurrentCastTime(Time::deltaTime);
       if (getCCurrentCastTime() >= getCCastTime()) {
       CCastFinished();
       }
       }*/
}

String Entity::request_spell_name(int spellId) {
	return "";
}

String Entity::request_spell_description(int spellId, int level) {
	return "";
}

String Entity::random_name() {
	/*/
      String text = new String(l1->GetData(UnityEngine::Random::Range(0, l1->Length)));
      bool flag = true;
      int num = UnityEngine::Random::Range(3, 6);
      for (int i = 0; i < num; i += 1) {
      if (flag) {
     *text += *(new String(l3->GetData(UnityEngine::Random::Range(0, l3->Length))));
     } else {
     *text += *(new String(l2->GetData(UnityEngine::Random::Range(0, l2->Length))));
     }
     }
     return text;*/

	return "";
}

void Entity::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_ENTER_TREE: {
			if (!Engine::get_singleton()->is_editor_hint())
				set_process(true);

			Node *node = get_node_or_null(_character_skeleton_path);

			if (node != NULL) {
				_character_skeleton = Object::cast_to<CharacterSkeleton>(node);
			} else {
				_character_skeleton = NULL;
			}
		} break;
		case NOTIFICATION_PROCESS: {
			update(get_process_delta_time());
		} break;
		case NOTIFICATION_EXIT_TREE: {

		} break;
	}
}

void Entity::_bind_methods() {
	//Signals
	ADD_SIGNAL(MethodInfo("starget_changed", PropertyInfo(Variant::OBJECT, "Entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	ADD_SIGNAL(MethodInfo("ctarget_changed", PropertyInfo(Variant::OBJECT, "Entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	ADD_SIGNAL(MethodInfo("son_damage_received", PropertyInfo(Variant::OBJECT, "Entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "damage_pipeline_data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	ADD_SIGNAL(MethodInfo("con_damage_received", PropertyInfo(Variant::OBJECT, "Entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "damage_pipeline_data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	ADD_SIGNAL(MethodInfo("con_damage_dealt", PropertyInfo(Variant::OBJECT, "Entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "damage_pipeline_data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	ADD_SIGNAL(MethodInfo("son_heal_received", PropertyInfo(Variant::OBJECT, "Entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "damage_pipeline_data", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	ADD_SIGNAL(MethodInfo("con_heal_received", PropertyInfo(Variant::OBJECT, "Entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "damage_pipeline_data", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));

	ADD_SIGNAL(MethodInfo("con_heal_dealt", PropertyInfo(Variant::OBJECT, "Entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "damage_pipeline_data", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));

	ADD_SIGNAL(MethodInfo("scharacter_class_changed", PropertyInfo(Variant::OBJECT, "Entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	ADD_SIGNAL(MethodInfo("ccharacter_class_changed", PropertyInfo(Variant::OBJECT, "Entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	//SpellCastSignals
	ADD_SIGNAL(MethodInfo("scast_started", PropertyInfo(Variant::OBJECT, "spell_cast_info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	ADD_SIGNAL(MethodInfo("scast_failed", PropertyInfo(Variant::OBJECT, "spell_cast_info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	ADD_SIGNAL(MethodInfo("scast_delayed", PropertyInfo(Variant::OBJECT, "spell_cast_info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	ADD_SIGNAL(MethodInfo("scast_finished", PropertyInfo(Variant::OBJECT, "spell_cast_info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	ADD_SIGNAL(MethodInfo("scast_interrupted", PropertyInfo(Variant::OBJECT, "spell_cast_info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));

	ADD_SIGNAL(MethodInfo("ccast_started", PropertyInfo(Variant::OBJECT, "spell_cast_info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	ADD_SIGNAL(MethodInfo("ccast_failed", PropertyInfo(Variant::OBJECT, "spell_cast_info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	ADD_SIGNAL(MethodInfo("ccast_delayed", PropertyInfo(Variant::OBJECT, "spell_cast_info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	ADD_SIGNAL(MethodInfo("ccast_finished", PropertyInfo(Variant::OBJECT, "spell_cast_info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	ADD_SIGNAL(MethodInfo("ccast_interrupted", PropertyInfo(Variant::OBJECT, "spell_cast_info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));

	//Aura signals
	ADD_SIGNAL(MethodInfo("saura_added", PropertyInfo(Variant::OBJECT, "aura_data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	ADD_SIGNAL(MethodInfo("saura_removed", PropertyInfo(Variant::OBJECT, "aura_data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	ADD_SIGNAL(MethodInfo("saura_removed_expired", PropertyInfo(Variant::OBJECT, "aura_data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	ADD_SIGNAL(MethodInfo("saura_removed_dispelled", PropertyInfo(Variant::OBJECT, "aura_data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));

	ADD_SIGNAL(MethodInfo("caura_added", PropertyInfo(Variant::OBJECT, "aura_data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	ADD_SIGNAL(MethodInfo("caura_removed", PropertyInfo(Variant::OBJECT, "aura_data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	ADD_SIGNAL(MethodInfo("caura_removed_dispelled", PropertyInfo(Variant::OBJECT, "aura_data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	ADD_SIGNAL(MethodInfo("caura_removed_expired", PropertyInfo(Variant::OBJECT, "aura_data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));

	//EventHandlers
	ClassDB::bind_method(D_METHOD("son_before_aura_applied", "data"), &Entity::son_before_aura_applied);
	ClassDB::bind_method(D_METHOD("son_after_aura_applied", "data"), &Entity::son_after_aura_applied);

	ClassDB::bind_method(D_METHOD("son_hit", "data"), &Entity::son_hit);
	ClassDB::bind_method(D_METHOD("son_before_damage", "data"), &Entity::son_before_damage);
	ClassDB::bind_method(D_METHOD("son_damage_receive", "data"), &Entity::son_damage_receive);
	ClassDB::bind_method(D_METHOD("son_dealt_damage", "data"), &Entity::son_dealt_damage);
	ClassDB::bind_method(D_METHOD("son_damage_dealt", "data"), &Entity::son_damage_dealt);

	ClassDB::bind_method(D_METHOD("son_before_heal", "data"), &Entity::son_before_damage);
	ClassDB::bind_method(D_METHOD("son_heal_receive", "data"), &Entity::son_damage_receive);
	ClassDB::bind_method(D_METHOD("son_dealt_heal", "data"), &Entity::son_dealt_damage);
	ClassDB::bind_method(D_METHOD("son_heal_dealt", "data"), &Entity::son_damage_dealt);

	ClassDB::bind_method(D_METHOD("son_before_cast", "info"), &Entity::son_before_cast);
	ClassDB::bind_method(D_METHOD("son_before_cast_target", "info"), &Entity::son_before_cast_target);
	ClassDB::bind_method(D_METHOD("son_cast_finished_target", "info"), &Entity::son_cast_finished_target);
	ClassDB::bind_method(D_METHOD("son_cast_finished", "info"), &Entity::son_cast_finished);
	ClassDB::bind_method(D_METHOD("son_cast_started", "info"), &Entity::son_cast_started);
	ClassDB::bind_method(D_METHOD("son_cast_failed", "info"), &Entity::son_cast_failed);

	//Clientside EventHandlers
	ClassDB::bind_method(D_METHOD("con_cast_failed", "info"), &Entity::con_cast_failed);
	ClassDB::bind_method(D_METHOD("con_cast_started", "info"), &Entity::con_cast_started);
	ClassDB::bind_method(D_METHOD("con_cast_state_changed", "info"), &Entity::con_cast_state_changed);
	ClassDB::bind_method(D_METHOD("con_cast_finished", "info"), &Entity::con_cast_finished);
	ClassDB::bind_method(D_METHOD("con_spell_cast_success", "info"), &Entity::con_spell_cast_success);

	//Modifiers/Requesters
	ClassDB::bind_method(D_METHOD("sapply_passives_damage_receive", "data"), &Entity::sapply_passives_damage_receive);
	ClassDB::bind_method(D_METHOD("sapply_passives_damage_deal", "data"), &Entity::sapply_passives_damage_deal);

	//Spell operations
	ClassDB::bind_method(D_METHOD("scast_spell", "spell_id"), &Entity::scast_spell);
	ClassDB::bind_method(D_METHOD("crequest_spell_cast", "spell_id"), &Entity::crequest_spell_cast);

	//Damage Operations
	ClassDB::bind_method(D_METHOD("stake_damage", "data"), &Entity::stake_damage);
	ClassDB::bind_method(D_METHOD("sdeal_damage_to", "data"), &Entity::sdeal_damage_to);

	//Aura Manipulation
	ClassDB::bind_method(D_METHOD("sadd_aura", "aura"), &Entity::sadd_aura);
	ClassDB::bind_method(D_METHOD("sremove_aura", "aura"), &Entity::sremove_aura);
	ClassDB::bind_method(D_METHOD("sremove_aura_expired", "aura"), &Entity::sremove_aura_expired);
	ClassDB::bind_method(D_METHOD("sremove_aura_dispelled", "aura"), &Entity::sremove_aura_dispelled);

	ClassDB::bind_method(D_METHOD("cadd_aura", "aura"), &Entity::cadd_aura);
	ClassDB::bind_method(D_METHOD("cremove_aura", "aura"), &Entity::cremove_aura);
	ClassDB::bind_method(D_METHOD("cremove_aura_expired", "aura"), &Entity::cremove_aura_expired);
	ClassDB::bind_method(D_METHOD("cremove_aura_dispelled", "aura"), &Entity::cremove_aura_dispelled);

	ClassDB::bind_method(D_METHOD("sremove_auras_with_group", "aura_group"), &Entity::sremove_auras_with_group);

	ClassDB::bind_method(D_METHOD("sget_aura_count"), &Entity::sget_aura_count);
	ClassDB::bind_method(D_METHOD("sget_aura", "index"), &Entity::sget_aura);

	ClassDB::bind_method(D_METHOD("cget_aura_count"), &Entity::cget_aura_count);
	ClassDB::bind_method(D_METHOD("cget_aura", "index"), &Entity::cget_aura);

	//Hooks
	ClassDB::bind_method(D_METHOD("moved"), &Entity::moved);

	//Properties
	ClassDB::bind_method(D_METHOD("get_character_skeleton_path"), &Entity::get_character_skeleton_path);
	ClassDB::bind_method(D_METHOD("set_character_skeleton_path", "value"), &Entity::set_character_skeleton_path);
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "character_skeleton_path"), "set_character_skeleton_path", "get_character_skeleton_path");

	ClassDB::bind_method(D_METHOD("gets_entity_type"), &Entity::gets_entity_type);
	ClassDB::bind_method(D_METHOD("sets_entity_type", "value"), &Entity::sets_entity_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "s_entity_type", PROPERTY_HINT_ENUM, "None, Player, AI, Mob"), "sets_entity_type", "gets_entity_type");

	ClassDB::bind_method(D_METHOD("getc_entity_type"), &Entity::getc_entity_type);
	ClassDB::bind_method(D_METHOD("setc_entity_type", "value"), &Entity::sets_entity_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "c_entity_type", PROPERTY_HINT_ENUM, "None, Player, AI, Mob"), "setc_entity_type", "getc_entity_type");

	ClassDB::bind_method(D_METHOD("gets_player_name"), &Entity::gets_player_name);
	ClassDB::bind_method(D_METHOD("sets_player_name", "value"), &Entity::sets_player_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "s_player_name"), "sets_player_name", "gets_player_name");

	ClassDB::bind_method(D_METHOD("getc_player_name"), &Entity::getc_player_name);
	ClassDB::bind_method(D_METHOD("setc_player_name", "value"), &Entity::setc_player_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "c_player_name"), "setc_player_name", "getc_player_name");

	ClassDB::bind_method(D_METHOD("gets_xp"), &Entity::gets_xp);
	ClassDB::bind_method(D_METHOD("sets_xp", "value"), &Entity::sets_xp);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "s_xp"), "sets_xp", "gets_xp");

	ClassDB::bind_method(D_METHOD("getc_xp"), &Entity::getc_xp);
	ClassDB::bind_method(D_METHOD("setc_xp", "value"), &Entity::setc_xp);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "c_xp"), "setc_xp", "getc_xp");

	ClassDB::bind_method(D_METHOD("gets_character_class"), &Entity::gets_character_class);
	ClassDB::bind_method(D_METHOD("sets_character_class", "value"), &Entity::sets_character_class);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "s_character_class", PROPERTY_HINT_RESOURCE_TYPE, "CharacterClass"), "sets_character_class", "gets_character_class");

	ClassDB::bind_method(D_METHOD("getc_character_class"), &Entity::getc_character_class);
	ClassDB::bind_method(D_METHOD("setc_character_class", "value"), &Entity::setc_character_class);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "c_character_class", PROPERTY_HINT_RESOURCE_TYPE, "CharacterClass"), "setc_character_class", "getc_character_class");

	ClassDB::bind_method(D_METHOD("initialize", "entity_create_info"), &Entity::initialize);

	ClassDB::bind_method(D_METHOD("get_health"), &Entity::get_health);
	ClassDB::bind_method(D_METHOD("get_mana"), &Entity::get_mana);
	ClassDB::bind_method(D_METHOD("get_speed"), &Entity::get_speed);
	ClassDB::bind_method(D_METHOD("get_gcd"), &Entity::get_gcd);
	ClassDB::bind_method(D_METHOD("get_melee_crit"), &Entity::get_melee_crit);
	ClassDB::bind_method(D_METHOD("get_melee_crit_bonus"), &Entity::get_melee_crit_bonus);
	ClassDB::bind_method(D_METHOD("get_spell_crit"), &Entity::get_spell_crit);
	ClassDB::bind_method(D_METHOD("get_spell_crit_bonus"), &Entity::get_spell_crit_bonus);
	ClassDB::bind_method(D_METHOD("get_block"), &Entity::get_block);
	ClassDB::bind_method(D_METHOD("get_parry"), &Entity::get_parry);
	ClassDB::bind_method(D_METHOD("get_damage_reduction"), &Entity::get_damage_reduction);
	ClassDB::bind_method(D_METHOD("get_melee_damage_reduction"), &Entity::get_melee_damage_reduction);
	ClassDB::bind_method(D_METHOD("get_spell_damage_reduction"), &Entity::get_spell_damage_reduction);
	ClassDB::bind_method(D_METHOD("get_damage_taken"), &Entity::get_damage_taken);
	ClassDB::bind_method(D_METHOD("get_melee_damage"), &Entity::get_melee_damage);
	ClassDB::bind_method(D_METHOD("get_spell_damage"), &Entity::get_spell_damage);

	ClassDB::bind_method(D_METHOD("get_stat_int", "index"), &Entity::get_stat_int);
	ClassDB::bind_method(D_METHOD("set_stat_int", "index", "entry"), &Entity::set_stat_int);

	ClassDB::bind_method(D_METHOD("get_stat_enum", "index"), &Entity::get_stat_enum);
	ClassDB::bind_method(D_METHOD("set_stat_enum", "stat_id", "entry"), &Entity::set_stat_enum);

	//GCD
	ADD_SIGNAL(MethodInfo("sgcd_started", PropertyInfo(Variant::REAL, "value")));
	ADD_SIGNAL(MethodInfo("cgcd_started", PropertyInfo(Variant::REAL, "value")));

	ClassDB::bind_method(D_METHOD("getc_has_global_cooldown"), &Entity::getc_has_global_cooldown);
	ClassDB::bind_method(D_METHOD("gets_has_global_cooldown"), &Entity::gets_has_global_cooldown);
	ClassDB::bind_method(D_METHOD("getc_global_cooldown"), &Entity::getc_global_cooldown);
	ClassDB::bind_method(D_METHOD("gets_global_cooldown"), &Entity::gets_global_cooldown);
	ClassDB::bind_method(D_METHOD("sstart_global_cooldown", "value"), &Entity::sstart_global_cooldown);
	ClassDB::bind_method(D_METHOD("cstart_global_cooldown", "value"), &Entity::cstart_global_cooldown);

	//States
	ADD_SIGNAL(MethodInfo("sstate_changed", PropertyInfo(Variant::INT, "value")));
	ADD_SIGNAL(MethodInfo("cstate_changed", PropertyInfo(Variant::INT, "value")));

	ClassDB::bind_method(D_METHOD("getc_state"), &Entity::getc_state);
	ClassDB::bind_method(D_METHOD("setc_state", "state"), &Entity::setc_state);
	ClassDB::bind_method(D_METHOD("gets_state"), &Entity::gets_state);
	ClassDB::bind_method(D_METHOD("sets_state", "state"), &Entity::sets_state);
	ClassDB::bind_method(D_METHOD("sadd_state_ref", "state_index"), &Entity::sadd_state_ref);
	ClassDB::bind_method(D_METHOD("sremove_state_ref", "state_index"), &Entity::sremove_state_ref);

	//Cooldowns
	ADD_SIGNAL(MethodInfo("scooldown_added", PropertyInfo(Variant::OBJECT, "cooldown", PROPERTY_HINT_RESOURCE_TYPE, "Cooldown")));
	ADD_SIGNAL(MethodInfo("ccooldown_removed", PropertyInfo(Variant::INT, "spell_id")));

	ClassDB::bind_method(D_METHOD("hass_cooldown", "spell_id"), &Entity::hass_cooldown);
	ClassDB::bind_method(D_METHOD("adds_cooldown", "spell_id", "value"), &Entity::adds_cooldown);
	ClassDB::bind_method(D_METHOD("removes_cooldown", "spell_id"), &Entity::removes_cooldown);
	ClassDB::bind_method(D_METHOD("gets_cooldown", "spell_id"), &Entity::gets_cooldown);
	ClassDB::bind_method(D_METHOD("gets_cooldown_index", "index"), &Entity::gets_cooldown_index);
	ClassDB::bind_method(D_METHOD("gets_cooldown_count"), &Entity::gets_cooldown_count);

	ClassDB::bind_method(D_METHOD("hasc_cooldown", "spell_id"), &Entity::hasc_cooldown);
	ClassDB::bind_method(D_METHOD("addc_cooldown", "spell_id", "value"), &Entity::addc_cooldown);
	ClassDB::bind_method(D_METHOD("removec_cooldown", "spell_id"), &Entity::removec_cooldown);
	ClassDB::bind_method(D_METHOD("getc_cooldown", "spell_id"), &Entity::getc_cooldown);
	ClassDB::bind_method(D_METHOD("getc_cooldown_index", "index"), &Entity::getc_cooldown_index);
	ClassDB::bind_method(D_METHOD("getc_cooldown_count"), &Entity::getc_cooldown_count);

	//Category Cooldowns
	ADD_SIGNAL(MethodInfo("scategory_cooldown_added", PropertyInfo(Variant::OBJECT, "cooldown", PROPERTY_HINT_RESOURCE_TYPE, "CategoryCooldown")));
	ADD_SIGNAL(MethodInfo("ccategory_cooldown_removed", PropertyInfo(Variant::INT, "category_id")));

	ClassDB::bind_method(D_METHOD("hass_category_cooldown", "category_id"), &Entity::hass_category_cooldown);
	ClassDB::bind_method(D_METHOD("adds_category_cooldown", "category_id", "value"), &Entity::adds_category_cooldown);
	ClassDB::bind_method(D_METHOD("removes_category_cooldown", "category_id"), &Entity::removes_category_cooldown);
	ClassDB::bind_method(D_METHOD("gets_category_cooldown", "category_id"), &Entity::gets_category_cooldown);
	ClassDB::bind_method(D_METHOD("gets_category_cooldown_index", "index"), &Entity::gets_category_cooldown_index);
	ClassDB::bind_method(D_METHOD("gets_category_cooldown_count"), &Entity::gets_category_cooldown_count);

	ClassDB::bind_method(D_METHOD("hasc_category_cooldown", "category_id"), &Entity::hasc_category_cooldown);
	ClassDB::bind_method(D_METHOD("addc_category_cooldown", "category_id", "value"), &Entity::addc_category_cooldown);
	ClassDB::bind_method(D_METHOD("removec_category_cooldown", "category_id"), &Entity::removec_category_cooldown);
	ClassDB::bind_method(D_METHOD("getc_category_cooldown", "category_id"), &Entity::getc_category_cooldown);
	ClassDB::bind_method(D_METHOD("getc_category_cooldown_index", "index"), &Entity::getc_category_cooldown_index);
	ClassDB::bind_method(D_METHOD("getc_category_cooldown_count"), &Entity::getc_category_cooldown_count);

	//skeleton
	ClassDB::bind_method(D_METHOD("get_character_skeleton"), &Entity::get_character_skeleton);

	////    Targeting System    ////

	ClassDB::bind_method(D_METHOD("gets_target"), &Entity::gets_target);
	ClassDB::bind_method(D_METHOD("sets_target", "target"), &Entity::sets_target);

	ClassDB::bind_method(D_METHOD("getc_target"), &Entity::getc_target);
	ClassDB::bind_method(D_METHOD("setc_target", "target"), &Entity::setc_target);
    
    ////    Inventory System    ////
    
    ADD_SIGNAL(MethodInfo("sitem_added", PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));
    ADD_SIGNAL(MethodInfo("citem_added", PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));
    
    ClassDB::bind_method(D_METHOD("gets_bag", "index"), &Entity::gets_bag);
    ClassDB::bind_method(D_METHOD("getc_bag", "index"), &Entity::getc_bag);
    
    BIND_ENUM_CONSTANT(BACKPACK_SIZE);
    BIND_ENUM_CONSTANT(MAX_BAG_SLOTS);
}
