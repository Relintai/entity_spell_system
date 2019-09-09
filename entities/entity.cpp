#include "entity.h"

#include "../data/aura.h"
#include "../data/spell.h"
#include "../entities/auras/aura_data.h"
#include "../infos/spell_cast_info.h"
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

	SEND_RPC(rpc("setc_guid", value), setc_guid(value));
}

int Entity::gets_entity_data_id() {
	return _s_class_id;
}
void Entity::sets_entity_data_id(int value) {
	_s_class_id = value;

	SEND_RPC(rpc("setc_entity_data_id", value), setc_entity_data_id(value));
}

int Entity::getc_entity_data_id() {
	return _c_class_id;
}
void Entity::setc_entity_data_id(int value) {
	_c_class_id = value;

	if (DataManager::get_instance() != NULL) {
		setc_entity_data(DataManager::get_instance()->get_entity_data(value));
	}
}

EntityEnums::EntityType Entity::gets_entity_type() {
	return _s_entity_type;
}
void Entity::sets_entity_type(EntityEnums::EntityType value) {
	_s_entity_type = value;

	SEND_RPC(rpc("setc_entity_type", value), setc_entity_type(value));
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

	SEND_RPC(rpc("setc_player_name", value), setc_player_name(value));
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

	SEND_RPC(rpc("setc_gender", value), setc_gender(value));
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

	SEND_RPC(rpc("setc_level", value), setc_level(value));
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

	SEND_RPC(rpc("setc_xp", value), setc_xp(value));
}

int Entity::getc_xp() {
	return _c_xp;
}
void Entity::setc_xp(int value) {
	_c_xp = value;
}

Ref<EntityData> Entity::getc_entity_data() {
	return _c_entity_data;
}

void Entity::setc_entity_data(Ref<EntityData> value) {
	_c_entity_data = value;

	emit_signal("centity_data_changed", value);
}

Ref<EntityData> Entity::gets_entity_data() {
	return _s_entity_data;
}

void Entity::sets_entity_data(Ref<EntityData> value) {
	_s_entity_data = value;

	if (value.is_valid()) {
		value->setup_resources(this);
		sinitialize_stats();
		sets_entity_data_id(value->get_id());
	}

	if (!Engine::get_singleton()->is_editor_hint())
		set_process(value.is_valid());

	emit_signal("sentity_data_changed", value);

	//SEND_RPC(rpc("setc_entity_data", value), setc_entity_data(value));
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

	_s_active_category_cooldowns = 0;
	_c_active_category_cooldowns = 0;

	_s_entity_type = EntityEnums::EntityType::ENITIY_TYPE_NONE;
	_c_entity_type = EntityEnums::EntityType::ENITIY_TYPE_NONE;

	_s_target = NULL;
	_c_target = NULL;

	for (int i = 0; i < Stat::STAT_ID_TOTAL_STATS; ++i) {
		Ref<Stat> s = Ref<Stat>(memnew(Stat(static_cast<Stat::StatId>(i))));

		s->connect("s_changed", this, "ons_stat_changed");
		s->connect("c_changed", this, "onc_stat_changed");

		_stats[i] = s;
	}

	get_stat_enum(Stat::STAT_ID_HEALTH)->set_base(10000);
	get_stat_enum(Stat::STAT_ID_MANA)->set_base(100);
	get_stat_enum(Stat::STAT_ID_RAGE)->set_base(100);
	get_stat_enum(Stat::STAT_ID_ENERGY)->set_base(100);
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
	_rage = Ref<Stat>(get_stat_enum(Stat::STAT_ID_RAGE));
	_energy = Ref<Stat>(get_stat_enum(Stat::STAT_ID_ENERGY));
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

	SET_RPC_REMOTE("crequest_spell_cast");
	SET_RPC_REMOTE("csend_request_rank_increase");
	SET_RPC_REMOTE("csend_request_rank_decrease");

	SET_RPC_REMOTE("setc_guid");
	SET_RPC_REMOTE("setc_entity_data_id");
	SET_RPC_REMOTE("setc_entity_type");
	SET_RPC_REMOTE("setc_player_name");
	SET_RPC_REMOTE("setc_gender");
	SET_RPC_REMOTE("setc_level");
	SET_RPC_REMOTE("setc_xp");

	////     Stats    ////

	//send stats

	//GCD

	SET_RPC_REMOTE("cstart_global_cooldown");

	////    States    ////

	SET_RPC_REMOTE("setc_state");

	////    SpellSystem    ////

	//Clientside EventHandlers

	SET_RPC_REMOTE("con_cast_failed");
	SET_RPC_REMOTE("con_cast_started");
	SET_RPC_REMOTE("con_cast_state_changed");
	SET_RPC_REMOTE("con_cast_finished");
	SET_RPC_REMOTE("con_spell_cast_success");

	//Spell operations

	SET_RPC_REMOTE("crequest_spell_cast");

	//Aura Manipulation

	SET_RPC_REMOTE("cadd_aura");
	SET_RPC_REMOTE("cremove_aura");
	SET_RPC_REMOTE("cremove_aura_expired");
	SET_RPC_REMOTE("cremove_aura_dispelled");

	//Clientside hooks

	SET_RPC_REMOTE("con_damage_dealt");
	SET_RPC_REMOTE("con_dealt_damage");
	SET_RPC_REMOTE("con_heal_dealt");
	SET_RPC_REMOTE("con_dealt_heal");

	////    Casting System    ////

	SET_RPC_REMOTE("cstart_casting");
	SET_RPC_REMOTE("cfail_cast");
	SET_RPC_REMOTE("cdelay_cast");
	SET_RPC_REMOTE("cfinish_cast");
	SET_RPC_REMOTE("cinterrupt_cast");

	////    Cooldowns    ////

	SET_RPC_REMOTE("addc_cooldown");
	SET_RPC_REMOTE("removec_cooldown");

	//Category Cooldowns

	SET_RPC_REMOTE("addc_category_cooldown");
	SET_RPC_REMOTE("removec_category_cooldown");

	////    TargetComponent    ////

	SET_RPC_REMOTE("crequest_tagret_change");
	SET_RPC_REMOTE("net_sets_target");
	SET_RPC_REMOTE("net_setc_target");
}

Entity::~Entity() {
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

	sets_entity_data(info->get_entity_data());
	//setc_entity_data(info->get_entity_data());
	/*
	if (gets_entity_data() != NULL) {
		Ref<StatData> sd = gets_entity_data()->get_stat_data();

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
	//gets_entity_data()->get_stat_data()->get_stats_for_stat(_health);
	//Ref<StatDataEntry> e = gets_entity_data()->get_stat_data()->get_stat_data_enum(Stat::STAT_ID_HEALTH);

	Ref<EntityData> cc = gets_entity_data();

	ERR_FAIL_COND(!cc.is_valid());

	cc->get_stat_data()->get_stat_for_stat(get_health());
	cc->get_stat_data()->get_stat_for_stat(get_mana());
	cc->get_stat_data()->get_stat_for_stat(get_rage());
	cc->get_stat_data()->get_stat_for_stat(get_energy());
	cc->get_stat_data()->get_stat_for_stat(get_speed());
	cc->get_stat_data()->get_stat_for_stat(get_gcd());
	cc->get_stat_data()->get_stat_for_stat(get_melee_crit());
	cc->get_stat_data()->get_stat_for_stat(get_melee_crit_bonus());
	cc->get_stat_data()->get_stat_for_stat(get_spell_crit());
	cc->get_stat_data()->get_stat_for_stat(get_spell_crit_bonus());
	cc->get_stat_data()->get_stat_for_stat(get_block());
	cc->get_stat_data()->get_stat_for_stat(get_parry());
	cc->get_stat_data()->get_stat_for_stat(get_melee_damage_reduction());
	cc->get_stat_data()->get_stat_for_stat(get_spell_damage_reduction());
	cc->get_stat_data()->get_stat_for_stat(get_damage_taken());
	cc->get_stat_data()->get_stat_for_stat(get_heal_taken());
	cc->get_stat_data()->get_stat_for_stat(get_melee_damage());
	cc->get_stat_data()->get_stat_for_stat(get_spell_damage());

	for (int i = 0; i < cc->get_num_auras(); ++i) {
		Ref<Aura> a = cc->get_aura(i);

		if (a.is_valid()) {
			a->sapply_simple(this, this, 1.0);
		}
	}
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

	void son_gcd_started();

	emit_signal("sgcd_started", _s_gcd);

	SEND_RPC(rpc("cstart_global_cooldown", value), cstart_global_cooldown(value));
}

void Entity::cstart_global_cooldown(float value) {
	_c_gcd = value;

	void con_gcd_started();

	emit_signal("cgcd_started", _c_gcd);
}

////    States    ////

int Entity::gets_state() {
	return _s_state;
}
void Entity::sets_state(int state) {
	_s_state = state;

	emit_signal("sstate_changed", state);

	SEND_RPC(rpc("setc_state", state), setc_state(state));
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

void Entity::sdie() {
	//serverside

	son_death();

	//send an event to client
	SEND_RPC(rpc("cdie"), cdie());

	//signal
	emit_signal("sdied", this);
}

void Entity::cdie() {
	con_death();

	emit_signal("cdied", this);
}

void Entity::ons_stat_changed(Ref<Stat> stat) {
	for (int i = 0; i < _s_resources.size(); ++i) {
		_s_resources.get(i)->ons_stat_changed(stat);
	}
}
void Entity::onc_stat_changed(Ref<Stat> stat) {
	for (int i = 0; i < _c_resources.size(); ++i) {
		_c_resources.get(i)->onc_stat_changed(stat);
	}
}

////    Resources    ////

Ref<EntityResource> Entity::gets_resource(int index) {
	ERR_FAIL_INDEX_V(index, _s_resources.size(), Ref<EntityResource>());

	return _s_resources.get(index);
}
Ref<EntityResource> Entity::gets_resource_type(int type) {
	for (int i = 0; i < _s_resources.size(); ++i) {
		Ref<EntityResource> r = _s_resources.get(i);

		if (r->get_resource_type() == type) {
			return r;
		}
	}

	return Ref<EntityResource>(NULL);
}
void Entity::adds_resource(Ref<EntityResource> resource) {
	ERR_FAIL_COND(!resource.is_valid());

	resource->ons_added(this);
	_s_resources.push_back(resource);

	//temporary
	addc_resource(resource);
}
int Entity::gets_resource_count() {
	return _s_resources.size();
}
void Entity::removes_resource(int index) {
	ERR_FAIL_INDEX(index, _s_resources.size());

	_s_resources.remove(index);
}

void Entity::clears_resource() {
	_s_resources.clear();
}

Ref<EntityResource> Entity::getc_resource(int index) {
	ERR_FAIL_INDEX_V(index, _c_resources.size(), Ref<EntityResource>());

	return _c_resources.get(index);
}
Ref<EntityResource> Entity::getc_resource_type(int type) {
	for (int i = 0; i < _c_resources.size(); ++i) {
		Ref<EntityResource> r = _c_resources.get(i);

		if (r->get_resource_type() == type) {
			return r;
		}
	}

	return Ref<EntityResource>(NULL);
}
void Entity::addc_resource(Ref<EntityResource> resource) {
	ERR_FAIL_COND(!resource.is_valid());

	resource->onc_added(this);

	_c_resources.push_back(resource);
}
int Entity::getc_resource_count() {
	return _c_resources.size();
}
void Entity::removec_resource(int index) {
	ERR_FAIL_INDEX(index, _c_resources.size());

	_c_resources.remove(index);
}
void Entity::clearc_resource() {
	_s_resources.clear();
}

void Entity::stake_damage(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	//serverside

	if (gets_is_dead()) {
		return;
	}

	//send it through the passive damage reductions pipeline
	sapply_passives_damage_receive(info);
	//send it through the onbeforehit handler
	son_before_damage(info);
	//send it throug the onhit pipeliine
	son_hit(info);
	son_damage_receive(info);

	int h = get_health()->gets_current() - info->get_damage();

	if (h < 0) {
		h = 0;
	}

	get_health()->sets_current(h);

	son_damage_dealt(info);

	//signal
	emit_signal("son_damage_received", this, info);

	//send an event to client
	SEND_RPC(rpc("con_damage_dealt", info), con_damage_dealt(info));

	if (get_health()->gets_current() <= 0) {
		sdie();
	}
}

void Entity::sdeal_damage_to(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	//serverside

	if (gets_is_dead()) {
		return;
	}

	sapply_passives_damage_deal(info);
	info->get_receiver()->stake_damage(info);
	son_dealt_damage(info);

	//send an event to client
	SEND_RPC(rpc("con_dealt_damage", info), con_dealt_damage(info));

	//signal
	emit_signal("son_damage_received", this, info);

	if (get_health()->gets_current() <= 0) {
		sdie();
	}
}

void Entity::stake_heal(Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	//serverside

	if (gets_is_dead()) {
		return;
	}

	//send it through the passive damage reductions pipeline
	sapply_passives_heal_receive(info);
	//send it through the onbeforehit handler
	son_before_heal(info);

	son_heal_receive(info);

	int h = get_health()->gets_current() + info->get_heal();

	if (h > get_health()->gets_max()) {
		h = get_health()->gets_max();
	}
	get_health()->sets_current(h);

	//send an event to client
	SEND_RPC(rpc("con_heal_dealt", info), con_heal_dealt(info));

	//signal
	emit_signal("son_heal_received", this, info);
}

void Entity::sdeal_heal_to(Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());
	ERR_FAIL_COND(info->get_receiver() == NULL);

	//serverside

	if (gets_is_dead()) {
		return;
	}

	sapply_passives_heal_deal(info);
	info->get_receiver()->stake_heal(info);
	son_heal_dealt(info);
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

	if (_s_entity_data.is_valid()) {
		_s_entity_data->son_after_aura_applied(data);
	}

	if (has_method("_son_before_aura_applied"))
		call("_son_before_aura_applied", data);

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_before_aura_applied(data);
	}
}

void Entity::son_after_aura_applied(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (_s_entity_data.is_valid()) {
		_s_entity_data->son_after_aura_applied(data);
	}

	if (has_method("_son_after_aura_applied"))
		call("_son_after_aura_applied", data);

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		if (ad == data) {
			continue;
		}

		ad->get_aura()->son_after_aura_applied(data);
	}
}

////    Spell System    ////

void Entity::scast_spell(int spell_id) {
	Ref<EntityData> cc = gets_entity_data();

	if (cc == NULL)
		return;

	cc->start_casting(spell_id, this, 1);
}

void Entity::crequest_spell_cast(int spell_id) {
	SEND_RPC_TO_SERVER(rpc_id(1, "scast_spell", spell_id), scast_spell(spell_id));
}

void Entity::update_auras(float delta) {
	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->supdate(ad, delta);
	}
}

void Entity::son_before_cast(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_s_entity_data.is_valid()) {
		_s_entity_data->son_before_cast(info);
	}

	if (has_method("_son_before_cast"))
		call("_son_before_cast", info);

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_before_cast(ad, info);
	}
}

void Entity::son_before_cast_target(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_s_entity_data.is_valid()) {
		_s_entity_data->son_after_aura_applied(info);
	}

	if (has_method("_son_before_cast_target"))
		call("_son_before_cast_target", info);

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_before_cast_target(ad, info);
	}
}

void Entity::son_hit(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_s_entity_data.is_valid()) {
		_s_entity_data->son_hit(info);
	}

	if (has_method("_son_hit"))
		call("_son_hit", info);

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_hit(ad, info);
	}
}

void Entity::son_before_damage(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_s_entity_data.is_valid()) {
		_s_entity_data->son_before_damage(info);
	}

	if (has_method("_son_before_damage"))
		call("_son_before_damage", info);

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_before_damage(ad, info);
	}
}

void Entity::son_damage_receive(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_s_entity_data.is_valid()) {
		_s_entity_data->son_damage_receive(info);
	}

	if (has_method("_son_damage_receive"))
		call("_son_damage_receive", info);

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_damage_receive(ad, info);
	}
}

void Entity::son_dealt_damage(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_s_entity_data.is_valid()) {
		_s_entity_data->son_dealt_damage(info);
	}

	if (has_method("_son_dealt_damage"))
		call("_son_dealt_damage", info);

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_dealt_damage(ad, info);
	}
}

void Entity::son_damage_dealt(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_s_entity_data.is_valid()) {
		_s_entity_data->son_damage_dealt(info);
	}

	if (has_method("_son_damage_dealt"))
		call("_son_damage_dealt", info);

	//serverside
	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_damage_dealt(ad, info);
	}
}

void Entity::son_before_heal(Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_s_entity_data.is_valid()) {
		_s_entity_data->son_before_heal(info);
	}

	if (has_method("_son_before_heal"))
		call("_son_before_heal", info);

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_before_heal(ad, info);
	}
}

void Entity::son_heal_receive(Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_s_entity_data.is_valid()) {
		_s_entity_data->son_heal_receive(info);
	}

	if (has_method("_son_heal_receive"))
		call("_son_heal_receive", info);

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_heal_receive(ad, info);
	}
}

void Entity::son_dealt_heal(Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_s_entity_data.is_valid()) {
		_s_entity_data->son_dealt_heal(info);
	}

	if (has_method("_son_dealt_heal"))
		call("_son_dealt_heal", info);

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_dealt_heal(ad, info);
	}
}

void Entity::son_heal_dealt(Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_s_entity_data.is_valid()) {
		_s_entity_data->son_heal_dealt(info);
	}

	if (has_method("_son_heal_dealt"))
		call("_son_heal_dealt", info);

	//serverside
	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_heal_dealt(ad, info);
	}
}

void Entity::sapply_passives_damage_receive(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->sapply_passives_damage_receive(info);
	}
}

void Entity::sapply_passives_damage_deal(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->sapply_passives_damage_deal(info);
	}
}

void Entity::sapply_passives_heal_receive(Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->sapply_passives_heal_receive(info);
	}
}

void Entity::sapply_passives_heal_deal(Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->sapply_passives_heal_deal(info);
	}
}

void Entity::son_cast_finished(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_s_entity_data.is_valid()) {
		_s_entity_data->son_cast_finished(info);
	}

	if (has_method("_son_cast_finished"))
		call("_son_cast_finished", info);

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_cast_finished(ad, info);
	}
}

void Entity::son_cast_started(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_s_entity_data.is_valid()) {
		_s_entity_data->son_cast_started(info);
	}

	if (has_method("_son_cast_started"))
		call("_son_cast_started", info);

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_cast_started(ad, info);
	}
}

void Entity::son_cast_failed(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_s_entity_data.is_valid()) {
		_s_entity_data->son_cast_failed(info);
	}

	if (has_method("_son_cast_failed"))
		call("_son_cast_failed", info);

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_cast_failed(ad, info);
	}
}

void Entity::son_cast_finished_target(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_s_entity_data.is_valid()) {
		_s_entity_data->son_cast_finished_target(info);
	}

	if (has_method("_son_cast_finished_target"))
		call("_son_cast_finished_target", info);

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_cast_finished_target(ad, info);
	}
}

void Entity::son_death() {
	if (_s_entity_data.is_valid()) {
		_s_entity_data->son_death(this);
	}

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_death(ad);
	}

	if (has_method("_son_death"))
		call("_son_death");
}

void Entity::son_cooldown_added(Ref<Cooldown> cooldown) {
	ERR_FAIL_COND(!cooldown.is_valid());

	if (_s_entity_data.is_valid()) {
		_s_entity_data->son_cooldown_added(cooldown);
	}

	if (has_method("_son_cooldown_added"))
		call("_son_cooldown_added", cooldown);

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_cooldown_added(ad, cooldown);
	}
}
void Entity::son_cooldown_removed(Ref<Cooldown> cooldown) {
	ERR_FAIL_COND(!cooldown.is_valid());

	if (_s_entity_data.is_valid()) {
		_s_entity_data->son_cooldown_removed(cooldown);
	}

	if (has_method("_son_cooldown_removed"))
		call("_son_cooldown_removed", cooldown);

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_cooldown_removed(ad, cooldown);
	}
}

void Entity::son_category_cooldown_added(Ref<CategoryCooldown> category_cooldown) {
	ERR_FAIL_COND(!category_cooldown.is_valid());

	if (_s_entity_data.is_valid()) {
		_s_entity_data->son_category_cooldown_added(category_cooldown);
	}

	if (has_method("_son_category_cooldown_added"))
		call("_son_category_cooldown_added", category_cooldown);

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_category_cooldown_added(ad, category_cooldown);
	}
}
void Entity::son_category_cooldown_removed(Ref<CategoryCooldown> category_cooldown) {
	ERR_FAIL_COND(!category_cooldown.is_valid());

	if (_s_entity_data.is_valid()) {
		_s_entity_data->son_category_cooldown_removed(category_cooldown);
	}

	if (has_method("_son_category_cooldown_removed"))
		call("_son_category_cooldown_removed", category_cooldown);

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_category_cooldown_removed(ad, category_cooldown);
	}
}

void Entity::son_gcd_started() {
	if (_s_entity_data.is_valid()) {
		_s_entity_data->son_gcd_started(this, _s_gcd);
	}

	if (has_method("_son_gcd_started"))
		call("_son_gcd_started", _s_gcd);

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_gcd_started(ad, _s_gcd);
	}
}
void Entity::son_gcd_finished() {
	if (_s_entity_data.is_valid()) {
		_s_entity_data->son_gcd_finished(this);
	}

	if (has_method("_son_gcd_finished"))
		call("_son_gcd_finished");

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_gcd_finished(ad);
	}
}
void Entity::con_gcd_started() {
	if (_s_entity_data.is_valid()) {
		_s_entity_data->con_gcd_started(this, _c_gcd);
	}

	if (has_method("_con_gcd_started"))
		call("_con_gcd_started", _c_gcd);

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->con_gcd_started(ad, _c_gcd);
	}
}
void Entity::con_gcd_finished() {
	if (_s_entity_data.is_valid()) {
		_s_entity_data->con_gcd_finished(this);
	}

	if (has_method("_con_gcd_finished"))
		call("_con_gcd_finished");

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->con_gcd_finished(ad);
	}
}

void Entity::sadd_aura(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	son_before_aura_applied(aura);

	aura->set_owner(this);

	_s_auras.push_back(aura);

	son_after_aura_applied(aura);

	emit_signal("saura_added", aura);

	if (!aura->get_aura()->get_hide())
		SEND_RPC(rpc("cadd_aura", aura), cadd_aura(aura));
}

void Entity::sremove_aura(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	int aid = aura->get_aura_id();
	Entity *caster = aura->get_caster();

	Ref<AuraData> a;
	bool removed = false;
	for (int i = 0; i < _s_auras.size(); i++) {
		a = _s_auras.get(i);

		if (a->get_aura_id() == aid && a->get_caster() == caster) {
			_s_auras.remove(i);
			removed = true;
			break;
		}
	}

	if (removed) {
		emit_signal("saura_removed", a);

		if (!aura->get_aura()->get_hide())
			SEND_RPC(rpc("cremove_aura", a), cremove_aura(a));
	}
}

void Entity::sremove_aura_exact(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	for (int i = 0; i < _s_auras.size(); i++) {
		Ref<AuraData> ad = _s_auras.get(i);

		if (ad == aura) {
			ad->get_aura()->son_remove(ad);

			_s_auras.remove(i);

			break;
		}
	}

	emit_signal("saura_removed", aura);

	if (!aura->get_aura()->get_hide())
		SEND_RPC(rpc("cremove_aura", aura), cremove_aura(aura));
}

void Entity::sremove_aura_expired(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	for (int i = 0; i < _s_auras.size(); i++) {
		Ref<AuraData> ad = _s_auras.get(i);

		if (ad == aura) {
			ad->get_aura()->son_remove(ad);

			_s_auras.remove(i);

			break;
		}
	}

	emit_signal("saura_removed_expired", aura);

	if (!aura->get_aura()->get_hide())
		SEND_RPC(rpc("cremove_aura", aura), cremove_aura(aura));
}

void Entity::sremove_aura_dispelled(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	for (int i = 0; i < _s_auras.size(); i++) {
		Ref<AuraData> ad = _s_auras.get(i);

		if (ad == aura) {
			ad->get_aura()->son_remove(ad);

			_s_auras.remove(i);

			break;
		}
	}

	emit_signal("saura_removed_dispelled", aura);

	if (!aura->get_aura()->get_hide())
		SEND_RPC(rpc("cremove_aura", aura), cremove_aura(aura));
}

void Entity::saura_refreshed(Ref<AuraData> aura) {
	ERR_EXPLAIN("NYI");
	ERR_FAIL();

	ERR_FAIL_COND(!aura.is_valid());

	emit_signal("caura_refreshed", aura);

	if (!aura->get_aura()->get_hide())
		SEND_RPC(rpc("caura_refreshed", aura), caura_refreshed(aura));
}

void Entity::cadd_aura(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	_c_auras.push_back(aura);

	aura->get_aura()->con_aura_added(aura);

	emit_signal("caura_added", aura);
}

void Entity::cremove_aura(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	int aid = aura->get_aura_id();
	Entity *caster = aura->get_caster();

	Ref<AuraData> a;
	bool removed = false;
	for (int i = 0; i < _c_auras.size(); i++) {
		a = _c_auras.get(i);

		if (a->get_aura_id() == aid && a->get_caster() == caster) {
			_c_auras.remove(i);
			removed = true;
			break;
		}
	}

	if (removed) {
		aura->get_aura()->con_aura_removed(aura);

		if (_s_entity_data.is_valid()) {
			_s_entity_data->con_aura_removed(aura);
		}

		if (has_method("_con_aura_removed"))
			call("_con_aura_removed", aura);

		emit_signal("caura_removed", a);
	}
}

void Entity::cremove_aura_exact(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	aura->get_aura()->con_aura_removed(aura);

	for (int i = 0; i < _c_auras.size(); i++) {
		if (_c_auras.get(i) == aura) {
			_c_auras.remove(i);
			break;
		}
	}

	if (_s_entity_data.is_valid()) {
		_s_entity_data->con_aura_removed(aura);
	}

	if (has_method("_con_aura_removed"))
		call("_con_aura_removed", aura);

	emit_signal("caura_removed", aura);
}

void Entity::cremove_aura_dispelled(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	aura->get_aura()->con_aura_removed(aura);

	for (int i = 0; i < _c_auras.size(); i++) {
		if (_c_auras.get(i) == aura) {
			_c_auras.remove(i);
			break;
		}
	}

	if (_s_entity_data.is_valid()) {
		_s_entity_data->con_aura_removed(aura);
	}

	if (has_method("_con_aura_removed"))
		call("_con_aura_removed", aura);

	emit_signal("caura_removed_dispelled", aura);
}

void Entity::caura_refreshed(Ref<AuraData> aura) {
	ERR_EXPLAIN("NYI");
	ERR_FAIL();

	ERR_FAIL_COND(!aura.is_valid());

	emit_signal("caura_refreshed", aura);
}

void Entity::cremove_aura_expired(Ref<AuraData> aura) {
	ERR_FAIL_COND(!aura.is_valid());

	aura->get_aura()->con_aura_removed(aura);

	for (int i = 0; i < _c_auras.size(); i++) {
		if (_c_auras.get(i) == aura) {
			_c_auras.remove(i);
			break;
		}
	}

	if (_s_entity_data.is_valid()) {
		_s_entity_data->con_aura_removed(aura);
	}

	if (has_method("_con_aura_removed"))
		call("_con_aura_removed", aura);

	emit_signal("caura_removed_expired", aura);
}

int Entity::sget_aura_count() {
	return _s_auras.size();
}

Ref<AuraData> Entity::sget_aura(int index) {
	ERR_FAIL_INDEX_V(index, _s_auras.size(), Ref<AuraData>(NULL));

	return Ref<AuraData>(_s_auras.get(index));
}

Ref<AuraData> Entity::sget_aura_by(Entity *caster, int aura_id) {
	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		if (ad->get_aura_id() == aura_id && ad->get_caster() == caster) {
			return ad;
		}
	}

	return Ref<AuraData>(NULL);
}
Ref<AuraData> Entity::sget_aura_by_bind(Node *caster, int aura_id) {
	if (!caster) {
		return Ref<AuraData>(NULL);
	}

	Entity *e = cast_to<Entity>(caster);

	if (!e) {
		return Ref<AuraData>(NULL);
	}

	return sget_aura_by(e, aura_id);
}

int Entity::cget_aura_count() {
	return _s_auras.size();
}

Ref<AuraData> Entity::cget_aura(int index) {
	ERR_FAIL_INDEX_V(index, _c_auras.size(), Ref<AuraData>(NULL));

	return Ref<AuraData>(_c_auras.get(index));
}

void Entity::moved() {
	if (has_method("_moved"))
		call("_moved");
}

void Entity::con_cast_failed(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	info->get_spell()->con_spell_cast_failed(info);

	if (_c_entity_data.is_valid()) {
		_c_entity_data->con_cast_failed(info);
	}

	for (int i = 0; i < _c_auras.size(); ++i) {
		Ref<AuraData> ad = _c_auras.get(i);

		ad->get_aura()->con_cast_failed(ad, info);
	}

	if (has_method("_con_cast_failed"))
		call("_con_cast_failed");
}

void Entity::con_cast_started(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	info->get_spell()->con_spell_cast_started(info);

	if (_c_entity_data.is_valid()) {
		_c_entity_data->con_cast_started(info);
	}

	for (int i = 0; i < _c_auras.size(); ++i) {
		Ref<AuraData> ad = _c_auras.get(i);

		ad->get_aura()->con_cast_started(ad, info);
	}

	if (has_method("_con_cast_started"))
		call("_con_cast_started");
}

void Entity::con_cast_state_changed(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	//info->get_spell()->con_spell_cast_(info);

	if (_c_entity_data.is_valid()) {
		_c_entity_data->con_cast_state_changed(info);
	}

	for (int i = 0; i < _c_auras.size(); ++i) {
		Ref<AuraData> ad = _c_auras.get(i);

		ad->get_aura()->con_cast_state_changed(ad, info);
	}

	if (has_method("_con_cast_state_changed"))
		call("_con_cast_state_changed");
}

void Entity::con_cast_finished(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	info->get_spell()->con_spell_cast_success(info);

	if (_c_entity_data.is_valid()) {
		_c_entity_data->con_cast_finished(info);
	}

	for (int i = 0; i < _c_auras.size(); ++i) {
		Ref<AuraData> ad = _c_auras.get(i);

		ad->get_aura()->con_cast_finished(ad, info);
	}

	if (has_method("_con_cast_finished"))
		call("_con_cast_finished");
}

void Entity::con_spell_cast_success(Ref<SpellCastInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	info->get_spell()->con_spell_cast_success(info);

	if (_c_entity_data.is_valid()) {
		_c_entity_data->con_spell_cast_success(info);
	}

	for (int i = 0; i < _c_auras.size(); ++i) {
		Ref<AuraData> ad = _c_auras.get(i);

		ad->get_aura()->con_spell_cast_success(ad, info);
	}

	if (has_method("_con_spell_cast_success"))
		call("_con_spell_cast_success");
}

void Entity::con_death() {
	if (_c_entity_data.is_valid()) {
		_c_entity_data->con_death(this);
	}

	for (int i = 0; i < _c_auras.size(); ++i) {
		Ref<AuraData> ad = _c_auras.get(i);

		ad->get_aura()->con_death(ad);
	}

	if (has_method("_con_death"))
		call("_con_death");
}

void Entity::con_cooldown_added(Ref<Cooldown> cooldown) {
	ERR_FAIL_COND(!cooldown.is_valid());

	if (_c_entity_data.is_valid()) {
		_c_entity_data->con_cooldown_added(cooldown);
	}

	for (int i = 0; i < _c_auras.size(); ++i) {
		Ref<AuraData> ad = _c_auras.get(i);

		ad->get_aura()->con_cooldown_added(ad, cooldown);
	}

	if (has_method("_con_cooldown_added"))
		call("_con_cooldown_added");
}
void Entity::con_cooldown_removed(Ref<Cooldown> cooldown) {
	ERR_FAIL_COND(!cooldown.is_valid());

	if (_c_entity_data.is_valid()) {
		_c_entity_data->con_cooldown_removed(cooldown);
	}

	for (int i = 0; i < _c_auras.size(); ++i) {
		Ref<AuraData> ad = _c_auras.get(i);

		ad->get_aura()->con_cooldown_removed(ad, cooldown);
	}

	if (has_method("_con_cooldown_removed"))
		call("_con_cooldown_removed");
}
void Entity::con_category_cooldown_added(Ref<CategoryCooldown> category_cooldown) {
	ERR_FAIL_COND(!category_cooldown.is_valid());

	if (_c_entity_data.is_valid()) {
		_c_entity_data->con_category_cooldown_added(category_cooldown);
	}

	for (int i = 0; i < _c_auras.size(); ++i) {
		Ref<AuraData> ad = _c_auras.get(i);

		ad->get_aura()->con_category_cooldown_added(ad, category_cooldown);
	}

	if (has_method("_con_category_cooldown_added"))
		call("_con_category_cooldown_added");
}
void Entity::con_category_cooldown_removed(Ref<CategoryCooldown> category_cooldown) {
	ERR_FAIL_COND(!category_cooldown.is_valid());

	if (_c_entity_data.is_valid()) {
		_c_entity_data->con_category_cooldown_removed(category_cooldown);
	}

	for (int i = 0; i < _c_auras.size(); ++i) {
		Ref<AuraData> ad = _c_auras.get(i);

		ad->get_aura()->con_category_cooldown_removed(ad, category_cooldown);
	}

	if (has_method("_con_category_cooldown_removed"))
		call("_con_category_cooldown_removed");
}

void Entity::con_aura_added(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (_c_entity_data.is_valid()) {
		_c_entity_data->con_aura_added(data);
	}

	for (int i = 0; i < _c_auras.size(); ++i) {
		Ref<AuraData> ad = _c_auras.get(i);

		ad->get_aura()->con_aura_added(data);
	}

	if (has_method("_con_aura_added"))
		call("_con_aura_added");
}

void Entity::con_aura_removed(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (_c_entity_data.is_valid()) {
		_c_entity_data->con_aura_removed(data);
	}

	for (int i = 0; i < _c_auras.size(); ++i) {
		Ref<AuraData> ad = _c_auras.get(i);

		ad->get_aura()->con_aura_removed(data);
	}

	if (has_method("_con_aura_removed"))
		call("_con_aura_removed");
}

void Entity::con_aura_refresh(Ref<AuraData> data) {
	ERR_FAIL_COND(!data.is_valid());

	if (_c_entity_data.is_valid()) {
		_c_entity_data->con_aura_refresh(data);
	}

	for (int i = 0; i < _c_auras.size(); ++i) {
		Ref<AuraData> ad = _c_auras.get(i);

		ad->get_aura()->con_aura_refresh(data);
	}

	if (has_method("_con_aura_refresh"))
		call("_con_aura_refresh");
}

void Entity::con_damage_dealt(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_c_entity_data.is_valid()) {
		_c_entity_data->con_damage_dealt(info);
	}

	for (int i = 0; i < _c_auras.size(); ++i) {
		Ref<AuraData> ad = _c_auras.get(i);

		ad->get_aura()->con_damage_dealt(ad, info);
	}

	if (has_method("_con_damage_dealt"))
		call("_con_damage_dealt", info);

	//the current c health should probably be set here.
	emit_signal("con_damage_dealt", this, info);
}

void Entity::con_dealt_damage(Ref<SpellDamageInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_c_entity_data.is_valid()) {
		_c_entity_data->con_dealt_damage(info);
	}

	for (int i = 0; i < _c_auras.size(); ++i) {
		Ref<AuraData> ad = _c_auras.get(i);

		ad->get_aura()->con_dealt_damage(ad, info);
	}

	if (has_method("_con_dealt_damage"))
		call("_con_dealt_damage", info);

	//the current c health should probably be set here.
	emit_signal("con_dealt_damage", this, info);
}

void Entity::con_heal_dealt(Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_c_entity_data.is_valid()) {
		_c_entity_data->con_heal_dealt(info);
	}

	for (int i = 0; i < _c_auras.size(); ++i) {
		Ref<AuraData> ad = _c_auras.get(i);

		ad->get_aura()->con_heal_dealt(ad, info);
	}

	if (has_method("_con_heal_dealt"))
		call("_con_heal_dealt", info);

	//the current c health should probably be set here.
	emit_signal("con_heal_dealt", this, info);
}

void Entity::con_dealt_heal(Ref<SpellHealInfo> info) {
	ERR_FAIL_COND(!info.is_valid());

	if (_c_entity_data.is_valid()) {
		_c_entity_data->con_dealt_heal(info);
	}

	for (int i = 0; i < _c_auras.size(); ++i) {
		Ref<AuraData> ad = _c_auras.get(i);

		ad->get_aura()->con_dealt_heal(ad, info);
	}

	if (has_method("_con_dealt_heal"))
		call("_con_dealt_heal", info);

	//the current c health should probably be set here.
	emit_signal("con_dealt_heal", this, info);
}

////    Casting System    ////

void Entity::sstart_casting(Ref<SpellCastInfo> info) {
	_s_spell_cast_info = Ref<SpellCastInfo>(info);

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_before_cast(ad, info);
	}

	_s_spell_cast_info->set_is_casting(true);

	emit_signal("scast_started", info);

	SEND_RPC(rpc("cstart_casting", info), cstart_casting(info));
}

void Entity::sfail_cast() {
	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_before_cast(ad, _s_spell_cast_info);
	}

	emit_signal("scast_failed", _s_spell_cast_info);

	SEND_RPC(rpc("cfail_cast"), cfail_cast());
}

void Entity::sdelay_cast() {
	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_before_cast(ad, _s_spell_cast_info);
	}

	emit_signal("scast_delayed", _s_spell_cast_info);

	SEND_RPC(rpc("cdelay_cast"), cdelay_cast());
}

void Entity::sfinish_cast() {

	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_cast_finished(ad, _s_spell_cast_info);
	}

	_s_spell_cast_info->get_spell()->sfinish_cast(_s_spell_cast_info);

	emit_signal("scast_finished", _s_spell_cast_info);

	_s_spell_cast_info = Ref<SpellCastInfo>(NULL);

	SEND_RPC(rpc("cfinish_cast"), cfinish_cast());
}

void Entity::sinterrupt_cast() {
	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		ad->get_aura()->son_before_cast(ad, _s_spell_cast_info);
	}

	emit_signal("scast_interrupted", _s_spell_cast_info);

	SEND_RPC(rpc("cinterrupt_cast"), cinterrupt_cast());
}

void Entity::cstart_casting(Ref<SpellCastInfo> info) {
	_c_spell_cast_info = Ref<SpellCastInfo>(info);

	con_cast_started(_c_spell_cast_info);

	emit_signal("ccast_started", _c_spell_cast_info);
}

void Entity::cfail_cast() {
	con_cast_failed(_c_spell_cast_info);

	emit_signal("ccast_failed", _c_spell_cast_info);

	_c_spell_cast_info = Ref<SpellCastInfo>(NULL);
}

void Entity::cdelay_cast() {

	//c_on_cast_

	emit_signal("ccast_delayed", _c_spell_cast_info);
}

void Entity::cfinish_cast() {
	con_cast_finished(_c_spell_cast_info);
	emit_signal("ccast_finished", _c_spell_cast_info);
	_c_spell_cast_info = Ref<SpellCastInfo>(NULL);
}

void Entity::cinterrupt_cast() {
	con_cast_failed(_c_spell_cast_info);
	emit_signal("ccast_interrupted", _c_spell_cast_info);
	_c_spell_cast_info = Ref<SpellCastInfo>(NULL);
}

////    Cooldowns    ////
Vector<Ref<Cooldown> > *Entity::gets_cooldowns() {
	return &_s_cooldowns;
}
Vector<Ref<Cooldown> > *Entity::getc_cooldowns() {
	return &_c_cooldowns;
}

HashMap<int, Ref<Cooldown> > *Entity::gets_cooldown_map() {
	return &_s_cooldown_map;
}
HashMap<int, Ref<Cooldown> > *Entity::getc_cooldown_map() {
	return &_c_cooldown_map;
}

bool Entity::hass_cooldown(int spell_id) {
	return _s_cooldown_map.has(spell_id);
}
void Entity::adds_cooldown(int spell_id, float value) {
	if (_s_cooldown_map.has(spell_id)) {
		Ref<Cooldown> cd = _s_cooldown_map.get(spell_id);

		cd->set_remaining(value);

		son_cooldown_added(cd);

		emit_signal("scooldown_added", cd);

		SEND_RPC(rpc("addc_cooldown", spell_id, value), addc_cooldown(spell_id, value));

		return;
	}

	Ref<Cooldown> cd;
	cd.instance();

	cd->set_spell_id(spell_id);
	cd->set_remaining(value);

	_s_cooldown_map.set(spell_id, cd);
	_s_cooldowns.push_back(cd);

	son_cooldown_added(cd);

	emit_signal("scooldown_added", cd);

	SEND_RPC(rpc("addc_cooldown", spell_id, value), addc_cooldown(spell_id, value));
}
void Entity::removes_cooldown(int spell_id) {
	Ref<Cooldown> cd;

	if (_s_cooldown_map.has(spell_id)) {
		_s_cooldown_map.erase(spell_id);
	}

	for (int i = 0; i < _s_cooldowns.size(); ++i) {
		if (_s_cooldowns.get(i)->get_spell_id() == spell_id) {
			cd = _s_cooldowns.get(i);

			_s_cooldowns.remove(i);

			break;
		}
	}

	son_cooldown_removed(cd);

	emit_signal("scooldown_removed", cd);

	SEND_RPC(rpc("removec_cooldown", spell_id), removec_cooldown(spell_id));
}
Ref<Cooldown> Entity::gets_cooldown(int spell_id) {
	if (!_s_cooldown_map.has(spell_id)) {
		return Ref<Cooldown>();
	}

	return _s_cooldown_map.get(spell_id);
}
Ref<Cooldown> Entity::gets_cooldown_index(int index) {
	ERR_FAIL_INDEX_V(index, _s_cooldowns.size(), Ref<Cooldown>());

	return _s_cooldowns.get(index);
}
int Entity::gets_cooldown_count() {
	return _s_cooldowns.size();
}

bool Entity::hasc_cooldown(int spell_id) {
	return _c_cooldown_map.has(spell_id);
}
void Entity::addc_cooldown(int spell_id, float value) {
	if (_c_cooldown_map.has(spell_id)) {
		Ref<Cooldown> cd = _c_cooldown_map.get(spell_id);

		cd->set_remaining(value);

		con_cooldown_added(cd);

		emit_signal("ccooldown_added", cd);

		return;
	}

	Ref<Cooldown> cd;
	cd.instance();

	cd->set_spell_id(spell_id);
	cd->set_remaining(value);

	_c_cooldown_map.set(spell_id, cd);
	_c_cooldowns.push_back(cd);

	con_cooldown_added(cd);

	emit_signal("ccooldown_added", cd);
}
void Entity::removec_cooldown(int spell_id) {
	Ref<Cooldown> cd;

	if (_c_cooldown_map.has(spell_id)) {
		_c_cooldown_map.erase(spell_id);
	}

	for (int i = 0; i < _c_cooldowns.size(); ++i) {
		if (_c_cooldowns.get(i)->get_spell_id() == spell_id) {
			cd = _c_cooldowns.get(i);
			_c_cooldowns.remove(i);
			break;
		}
	}

	if (!cd.is_valid())
		cd.instance();

	con_cooldown_removed(cd);

	emit_signal("ccooldown_removed", cd);
}
Ref<Cooldown> Entity::getc_cooldown(int spell_id) {
	if (!_c_cooldown_map.has(spell_id)) {
		return Ref<Cooldown>();
	}

	return _c_cooldown_map.get(spell_id);
}
Ref<Cooldown> Entity::getc_cooldown_index(int index) {
	ERR_FAIL_INDEX_V(index, _c_cooldowns.size(), Ref<Cooldown>());

	return _c_cooldowns.get(index);
}
int Entity::getc_cooldown_count() {
	return _c_cooldowns.size();
}

//Category Cooldowns
Vector<Ref<CategoryCooldown> > Entity::gets_category_cooldowns() {
	return _s_category_cooldowns;
}
Vector<Ref<CategoryCooldown> > Entity::getc_category_cooldowns() {
	return _c_category_cooldowns;
}

bool Entity::hass_category_cooldown(int category_id) {
	return (category_id & _s_active_category_cooldowns) > 0;
}
void Entity::adds_category_cooldown(int category_id, float value) {
	if ((category_id & _s_active_category_cooldowns)) {
		for (int i = 0; i < _s_category_cooldowns.size(); ++i) {
			Ref<CategoryCooldown> cc = _s_category_cooldowns.get(i);

			if (cc->get_category_id() == category_id) {
				cc->set_remaining(value);

				son_category_cooldown_added(cc);

				emit_signal("scategory_cooldown_added", cc);

				SEND_RPC(rpc("addc_category_cooldown", category_id, value), addc_category_cooldown(category_id, value));

				return;
			}
		}
	}

	Ref<CategoryCooldown> cc;
	cc.instance();

	cc->set_category_id(category_id);
	cc->set_remaining(value);

	_s_category_cooldowns.push_back(cc);

	_s_active_category_cooldowns |= category_id;

	son_category_cooldown_added(cc);

	emit_signal("scategory_cooldown_added", cc);

	SEND_RPC(rpc("addc_category_cooldown", category_id, value), addc_category_cooldown(category_id, value));
}
void Entity::removes_category_cooldown(int category_id) {
	Ref<CategoryCooldown> cc;

	for (int i = 0; i < _s_category_cooldowns.size(); ++i) {
		if (_s_category_cooldowns.get(i)->get_category_id() == category_id) {
			cc = _s_category_cooldowns.get(i);
			_s_category_cooldowns.remove(i);
			break;
		}
	}

	if (!cc.is_valid())
		return;

	_s_active_category_cooldowns ^= category_id;

	son_category_cooldown_removed(cc);

	emit_signal("scategory_cooldown_removed", cc);

	SEND_RPC(rpc("removec_category_cooldown", category_id), removec_category_cooldown(category_id));
}
Ref<CategoryCooldown> Entity::gets_category_cooldown(int category_id) {
	ERR_FAIL_COND_V(!(category_id & _s_active_category_cooldowns), Ref<CategoryCooldown>());

	Ref<CategoryCooldown> cc;

	for (int i = 0; i < _s_category_cooldowns.size(); ++i) {
		cc = _s_category_cooldowns.get(i);

		if (cc->get_category_id() == category_id) {
			return cc;
		}
	}

	return cc;
}
Ref<CategoryCooldown> Entity::gets_category_cooldown_index(int index) {
	ERR_FAIL_INDEX_V(index, _s_category_cooldowns.size(), Ref<Cooldown>());

	return _s_category_cooldowns.get(index);
}
int Entity::gets_category_cooldown_count() {
	return _s_category_cooldowns.size();
}

bool Entity::hasc_category_cooldown(int category_id) {
	return (category_id & _c_active_category_cooldowns) > 0;
}
void Entity::addc_category_cooldown(int category_id, float value) {
	if (category_id & _c_active_category_cooldowns) {
		for (int i = 0; i < _c_category_cooldowns.size(); ++i) {
			Ref<CategoryCooldown> cc = _c_category_cooldowns.get(i);

			if (cc->get_category_id() == category_id) {
				cc->set_remaining(value);

				con_category_cooldown_added(cc);

				emit_signal("ccategory_cooldown_added", cc);
				return;
			}
		}
	}

	Ref<CategoryCooldown> cc;
	cc.instance();

	cc->set_category_id(category_id);
	cc->set_remaining(value);

	_c_category_cooldowns.push_back(cc);

	_c_active_category_cooldowns |= category_id;

	con_category_cooldown_added(cc);

	emit_signal("ccategory_cooldown_added", cc);
}
void Entity::removec_category_cooldown(int category_id) {
	Ref<CategoryCooldown> cc;

	for (int i = 0; i < _c_category_cooldowns.size(); ++i) {
		if (_c_category_cooldowns.get(i)->get_category_id() == category_id) {
			cc = _c_category_cooldowns.get(i);

			_c_category_cooldowns.remove(i);

			break;
		}
	}

	if (!cc.is_valid())
		return;

	_c_active_category_cooldowns ^= category_id;

	con_category_cooldown_removed(cc);

	emit_signal("ccategory_cooldown_removed", cc);
}
Ref<CategoryCooldown> Entity::getc_category_cooldown(int category_id) {
	ERR_FAIL_COND_V(!(category_id & _c_active_category_cooldowns), Ref<CategoryCooldown>());

	Ref<CategoryCooldown> cc;

	for (int i = 0; i < _c_category_cooldowns.size(); ++i) {
		cc = _c_category_cooldowns.get(i);

		if (cc->get_category_id() == category_id) {
			return cc;
		}
	}

	return cc;
}
Ref<CategoryCooldown> Entity::getc_category_cooldown_index(int index) {
	ERR_FAIL_INDEX_V(index, _c_category_cooldowns.size(), Ref<Cooldown>());

	return _c_category_cooldowns.get(index);
}
int Entity::getc_category_cooldown_count() {
	return _c_category_cooldowns.size();
}

////    Casting System    ////

bool Entity::sis_casting() {
	return _s_spell_cast_info.is_valid();
}
bool Entity::cis_casting() {
	return _c_spell_cast_info.is_valid();
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

void Entity::sremove_auras_with_group(int aura_group) {
	for (int i = 0; i < _s_auras.size(); ++i) {
		Ref<AuraData> ad = _s_auras.get(i);

		if (ad->get_aura()->get_aura_group() == aura_group) {

			cremove_aura(ad);

			_s_auras.remove(i);

			emit_signal("saura_removed", ad);

			cremove_aura(ad);

			i--;
		}
	}
}

void Entity::crequest_target_change(NodePath path) {
	SEND_RPC_TO_SERVER(rpc_id(1, "net_sets_target", path), sets_target(get_node_or_null(path)));
}

void Entity::net_sets_target(NodePath path) {
	if (!get_tree()->is_network_server())
		return;

	Node *p_target = get_node_or_null(path);

	sets_target(p_target);

	if (p_target == NULL) {
		SEND_RPC(rpc("net_setc_target", NodePath()), );
	} else {
		if (gets_target() == NULL) {
			SEND_RPC(rpc("net_setc_target", NodePath()), );
		} else {
			SEND_RPC(rpc("net_setc_target", gets_target()->get_path()), );
		}
	}
}
void Entity::net_setc_target(NodePath path) {
	Node *p_target = get_node_or_null(path);

	setc_target(p_target);
}

Entity *Entity::gets_target() {
	return _s_target;
}

void Entity::sets_target(Node *p_target) {
	if (p_target == NULL) {
		_s_target = NULL;

		for (int i = 0; i < _s_resources.size(); ++i) {
			_s_resources.get(i)->ons_target_changed(_s_target);
		}

		emit_signal("starget_changed", _s_target);
		setc_target(p_target);
		return;
	}

	Entity *e = cast_to<Entity>(p_target);

	if (!e) {
		return;
	}

	_s_target = e;

	for (int i = 0; i < _s_resources.size(); ++i) {
		_s_resources.get(i)->ons_target_changed(_s_target);
	}

	emit_signal("starget_changed", _s_target);

	if (is_inside_tree() && !get_tree()->has_network_peer()) {
		setc_target(p_target);
	}
}

Entity *Entity::getc_target() {
	return _c_target;
}
void Entity::setc_target(Node *p_target) {
	if (p_target == NULL) {
		_c_target = NULL;

		for (int i = 0; i < _c_resources.size(); ++i) {
			_c_resources.get(i)->onc_target_changed(_c_target);
		}

		emit_signal("ctarget_changed", _c_target);

		return;
	}

	Entity *e = cast_to<Entity>(p_target);

	if (!e) {
		return;
	}

	_c_target = e;

	for (int i = 0; i < _c_resources.size(); ++i) {
		_c_resources.get(i)->onc_target_changed(_c_target);
	}

	emit_signal("ctarget_changed", _c_target);
}

////    TalentComponent    ////

void Entity::csend_request_rank_increase(int talentID) {
	//SEND_RPC();
}

void Entity::csend_request_rank_decrease(int talentID) {
}

void Entity::ssend_rank(int talentID, int rank) {
}

void Entity::sreceive_rank_increase(int talentID) {
}

void Entity::sreceive_rank_decrease(int talentID) {
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

//PlayerTalent *Entity::sget_talent(int id, bool create) {
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

//	return NULL;
//}

//PlayerTalent *Entity::cget_talent(int id, bool create) {
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

//	return NULL;
//}


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

void Entity::update(float delta) {
	if (_s_gcd > 0.0000001) {
		_s_gcd -= delta;

		if (_s_gcd <= 0) {
			_s_gcd = 0;

			void son_gcd_finished();

			emit_signal("sgcd_finished");
		}
	}

	if (_c_gcd > 0.0000001) {
		_c_gcd -= delta;

		if (_c_gcd <= 0) {
			_c_gcd = 0;

			void con_gcd_finished();

			emit_signal("cgcd_finished");
		}
	}

	for (int i = 0; i < _c_cooldowns.size(); ++i) {
		Ref<Cooldown> cd = _c_cooldowns.get(i);

		cd->update(delta);

		// 		if (cd->update(delta)) {
		// 			removec_cooldown(cd->get_spell_id());
		// 			--i;
		// 		}
	}

	for (int i = 0; i < _c_category_cooldowns.size(); ++i) {
		Ref<CategoryCooldown> cd = _c_category_cooldowns.get(i);

		cd->update(delta);

		// 		if (cd->update(delta)) {
		// 			removec_category_cooldown(cd->get_category_id());
		// 			--i;
		// 		}
	}

	for (int i = 0; i < _s_cooldowns.size(); ++i) {
		Ref<Cooldown> cd = _s_cooldowns.get(i);

		if (cd->update(delta)) {
			removes_cooldown(cd->get_spell_id());
			--i;
		}
	}

	for (int i = 0; i < _s_category_cooldowns.size(); ++i) {
		Ref<CategoryCooldown> cd = _s_category_cooldowns.get(i);

		if (cd->update(delta)) {
			removes_category_cooldown(cd->get_category_id());
			--i;
		}
	}

	update_auras(delta);

	for (int i = 0; i < _s_resources.size(); ++i) {
		Ref<EntityResource> er = _s_resources.get(i);

		if (er->get_should_process()) {
			er->process(delta);
		}
	}

	if (_s_spell_cast_info.is_valid() && _s_spell_cast_info->get_is_casting()) {
		if (_s_spell_cast_info->update_cast_time(delta)) {
			sfinish_cast();
		}
	}
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
	ADD_SIGNAL(MethodInfo("starget_changed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	ADD_SIGNAL(MethodInfo("ctarget_changed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	ADD_SIGNAL(MethodInfo("son_damage_received", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	ADD_SIGNAL(MethodInfo("con_damage_received", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	ADD_SIGNAL(MethodInfo("con_damage_dealt", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	ADD_SIGNAL(MethodInfo("con_dealt_damage", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	ADD_SIGNAL(MethodInfo("son_heal_received", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	ADD_SIGNAL(MethodInfo("con_heal_received", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));

	ADD_SIGNAL(MethodInfo("con_dealt_heal", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));

	ADD_SIGNAL(MethodInfo("con_heal_dealt", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));

	ADD_SIGNAL(MethodInfo("sentity_data_changed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	ADD_SIGNAL(MethodInfo("centity_data_changed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	ADD_SIGNAL(MethodInfo("sdied", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	ADD_SIGNAL(MethodInfo("cdied", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

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
	//ADD_SIGNAL(MethodInfo("saura_refreshed", PropertyInfo(Variant::OBJECT, "aura_data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));

	ADD_SIGNAL(MethodInfo("caura_added", PropertyInfo(Variant::OBJECT, "aura_data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	ADD_SIGNAL(MethodInfo("caura_removed", PropertyInfo(Variant::OBJECT, "aura_data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	ADD_SIGNAL(MethodInfo("caura_removed_dispelled", PropertyInfo(Variant::OBJECT, "aura_data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	ADD_SIGNAL(MethodInfo("caura_removed_expired", PropertyInfo(Variant::OBJECT, "aura_data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	//ADD_SIGNAL(MethodInfo("caura_refreshed", PropertyInfo(Variant::OBJECT, "aura_data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));

	ClassDB::bind_method(D_METHOD("sdie"), &Entity::sdie);
	ClassDB::bind_method(D_METHOD("cdie"), &Entity::cdie);

	ClassDB::bind_method(D_METHOD("ons_stat_changed", "stat"), &Entity::ons_stat_changed);
	ClassDB::bind_method(D_METHOD("onc_stat_changed", "stat"), &Entity::onc_stat_changed);

	//EventHandlers
	BIND_VMETHOD(MethodInfo("_son_before_cast", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_son_before_cast_target", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_son_cast_started", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_son_cast_failed", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_son_cast_finished", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_son_cast_finished_target", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));

	BIND_VMETHOD(MethodInfo("_son_hit", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	BIND_VMETHOD(MethodInfo("_son_before_damage", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_son_damage_receive", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_son_dealt_damage", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_son_damage_dealt", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	BIND_VMETHOD(MethodInfo("_son_before_heal", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	BIND_VMETHOD(MethodInfo("_son_heal_receive", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	BIND_VMETHOD(MethodInfo("_son_dealt_heal", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	BIND_VMETHOD(MethodInfo("_son_heal_dealt", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));

	BIND_VMETHOD(MethodInfo("_son_before_aura_applied", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_son_after_aura_applied", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));

	BIND_VMETHOD(MethodInfo("_son_death"));

	BIND_VMETHOD(MethodInfo("_son_gcd_started", PropertyInfo(Variant::REAL, "gcd")));
	BIND_VMETHOD(MethodInfo("_son_gcd_finished"));

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

	ClassDB::bind_method(D_METHOD("son_death"), &Entity::son_death);

	ClassDB::bind_method(D_METHOD("son_gcd_started"), &Entity::son_gcd_started);
	ClassDB::bind_method(D_METHOD("son_gcd_finished"), &Entity::son_gcd_finished);

	//Clientside EventHandlers
	BIND_VMETHOD(MethodInfo("_con_cast_failed", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_con_cast_started", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_con_cast_state_changed", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_con_cast_finished", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));
	BIND_VMETHOD(MethodInfo("_con_spell_cast_success", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo")));

	BIND_VMETHOD(MethodInfo("_con_death"));

	BIND_VMETHOD(MethodInfo("con_cooldown_added", PropertyInfo(Variant::OBJECT, "cooldown", PROPERTY_HINT_RESOURCE_TYPE, "Cooldown")));
	BIND_VMETHOD(MethodInfo("con_cooldown_removed", PropertyInfo(Variant::OBJECT, "cooldown", PROPERTY_HINT_RESOURCE_TYPE, "Cooldown")));
	BIND_VMETHOD(MethodInfo("con_category_cooldown_added", PropertyInfo(Variant::OBJECT, "category_cooldown", PROPERTY_HINT_RESOURCE_TYPE, "CategoryCooldown")));
	BIND_VMETHOD(MethodInfo("con_category_cooldown_removed", PropertyInfo(Variant::OBJECT, "category_cooldown", PROPERTY_HINT_RESOURCE_TYPE, "CategoryCooldown")));

	BIND_VMETHOD(MethodInfo("_con_aura_added", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_con_aura_removed", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	BIND_VMETHOD(MethodInfo("_con_aura_refresh", PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));

	BIND_VMETHOD(MethodInfo("_con_damage_dealt", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_con_dealt_damage", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	BIND_VMETHOD(MethodInfo("_con_heal_dealt", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));
	BIND_VMETHOD(MethodInfo("_con_dealt_heal", PropertyInfo(Variant::OBJECT, "info", PROPERTY_HINT_RESOURCE_TYPE, "SpellHealInfo")));

	BIND_VMETHOD(MethodInfo("_con_gcd_started", PropertyInfo(Variant::REAL, "gcd")));
	BIND_VMETHOD(MethodInfo("_con_gcd_finished"));

	ClassDB::bind_method(D_METHOD("con_cast_failed", "info"), &Entity::con_cast_failed);
	ClassDB::bind_method(D_METHOD("con_cast_started", "info"), &Entity::con_cast_started);
	ClassDB::bind_method(D_METHOD("con_cast_state_changed", "info"), &Entity::con_cast_state_changed);
	ClassDB::bind_method(D_METHOD("con_cast_finished", "info"), &Entity::con_cast_finished);
	ClassDB::bind_method(D_METHOD("con_spell_cast_success", "info"), &Entity::con_spell_cast_success);

	ClassDB::bind_method(D_METHOD("con_death"), &Entity::con_death);

	ClassDB::bind_method(D_METHOD("con_cooldown_added", "cooldown"), &Entity::con_cooldown_added);
	ClassDB::bind_method(D_METHOD("con_cooldown_removed", "cooldown"), &Entity::con_cooldown_removed);
	ClassDB::bind_method(D_METHOD("con_category_cooldown_added", "category_cooldown"), &Entity::con_category_cooldown_added);
	ClassDB::bind_method(D_METHOD("con_category_cooldown_removed", "category_cooldown"), &Entity::con_category_cooldown_removed);

	ClassDB::bind_method(D_METHOD("con_aura_added", "data"), &Entity::con_aura_added);
	ClassDB::bind_method(D_METHOD("con_aura_removed", "data"), &Entity::con_aura_removed);
	ClassDB::bind_method(D_METHOD("con_aura_refresh", "data"), &Entity::con_aura_refresh);

	ClassDB::bind_method(D_METHOD("con_damage_dealt", "info"), &Entity::con_damage_dealt);
	ClassDB::bind_method(D_METHOD("con_dealt_damage", "info"), &Entity::con_dealt_damage);
	ClassDB::bind_method(D_METHOD("con_heal_dealt", "info"), &Entity::con_heal_dealt);
	ClassDB::bind_method(D_METHOD("con_dealt_heal", "info"), &Entity::con_dealt_heal);

	ClassDB::bind_method(D_METHOD("con_gcd_started"), &Entity::con_gcd_started);
	ClassDB::bind_method(D_METHOD("con_gcd_finished"), &Entity::con_gcd_finished);

	//Modifiers/Requesters
	ClassDB::bind_method(D_METHOD("sapply_passives_damage_receive", "data"), &Entity::sapply_passives_damage_receive);
	ClassDB::bind_method(D_METHOD("sapply_passives_damage_deal", "data"), &Entity::sapply_passives_damage_deal);

	//Spell operations
	ClassDB::bind_method(D_METHOD("scast_spell", "spell_id"), &Entity::scast_spell);
	ClassDB::bind_method(D_METHOD("crequest_spell_cast", "spell_id"), &Entity::crequest_spell_cast);

	//Damage Operations
	ClassDB::bind_method(D_METHOD("stake_damage", "data"), &Entity::stake_damage);
	ClassDB::bind_method(D_METHOD("sdeal_damage_to", "data"), &Entity::sdeal_damage_to);

	//Heal Operations
	ClassDB::bind_method(D_METHOD("stake_heal", "data"), &Entity::stake_heal);
	ClassDB::bind_method(D_METHOD("sdeal_heal_to", "data"), &Entity::sdeal_heal_to);

	//Aura Manipulation
	ClassDB::bind_method(D_METHOD("sadd_aura", "aura"), &Entity::sadd_aura);
	ClassDB::bind_method(D_METHOD("sremove_aura", "aura"), &Entity::sremove_aura);
	ClassDB::bind_method(D_METHOD("sremove_aura_exact", "aura"), &Entity::sremove_aura_exact);
	ClassDB::bind_method(D_METHOD("sremove_aura_expired", "aura"), &Entity::sremove_aura_expired);
	ClassDB::bind_method(D_METHOD("sremove_aura_dispelled", "aura"), &Entity::sremove_aura_dispelled);
	//ClassDB::bind_method(D_METHOD("saura_refreshed", "aura"), &Entity::saura_refreshed);

	ClassDB::bind_method(D_METHOD("cadd_aura", "aura"), &Entity::cadd_aura);
	ClassDB::bind_method(D_METHOD("cremove_aura", "aura"), &Entity::cremove_aura);
	ClassDB::bind_method(D_METHOD("cremove_aura_exact", "aura"), &Entity::cremove_aura_exact);
	ClassDB::bind_method(D_METHOD("cremove_aura_expired", "aura"), &Entity::cremove_aura_expired);
	ClassDB::bind_method(D_METHOD("cremove_aura_dispelled", "aura"), &Entity::cremove_aura_dispelled);
	//ClassDB::bind_method(D_METHOD("caura_refreshed", "aura"), &Entity::caura_refreshed);

	ClassDB::bind_method(D_METHOD("sremove_auras_with_group", "aura_group"), &Entity::sremove_auras_with_group);

	ClassDB::bind_method(D_METHOD("sget_aura_count"), &Entity::sget_aura_count);
	ClassDB::bind_method(D_METHOD("sget_aura", "index"), &Entity::sget_aura);
	ClassDB::bind_method(D_METHOD("sget_aura_by", "caster", "aura_id"), &Entity::sget_aura_by_bind);

	ClassDB::bind_method(D_METHOD("cget_aura_count"), &Entity::cget_aura_count);
	ClassDB::bind_method(D_METHOD("cget_aura", "index"), &Entity::cget_aura);

	//Hooks
	ClassDB::bind_method(D_METHOD("moved"), &Entity::moved);

	BIND_VMETHOD(MethodInfo("_moved"));

	//Properties
	ClassDB::bind_method(D_METHOD("get_character_skeleton_path"), &Entity::get_character_skeleton_path);
	ClassDB::bind_method(D_METHOD("set_character_skeleton_path", "value"), &Entity::set_character_skeleton_path);
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "character_skeleton_path"), "set_character_skeleton_path", "get_character_skeleton_path");

	ClassDB::bind_method(D_METHOD("gets_entity_data_id"), &Entity::gets_entity_data_id);
	ClassDB::bind_method(D_METHOD("sets_entity_data_id", "value"), &Entity::sets_entity_data_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "characterclass_id"), "sets_entity_data_id", "gets_entity_data_id");

	ClassDB::bind_method(D_METHOD("getc_entity_data_id"), &Entity::getc_entity_data_id);
	ClassDB::bind_method(D_METHOD("setc_entity_data_id", "value"), &Entity::setc_entity_data_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "entity_data_id"), "setc_entity_data_id", "getc_entity_data_id");

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

	ClassDB::bind_method(D_METHOD("gets_level"), &Entity::gets_level);
	ClassDB::bind_method(D_METHOD("sets_level", "value"), &Entity::sets_level);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "s_level"), "sets_level", "gets_level");

	ClassDB::bind_method(D_METHOD("getc_level"), &Entity::getc_level);
	ClassDB::bind_method(D_METHOD("setc_level", "value"), &Entity::setc_level);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "c_level"), "setc_level", "getc_level");

	ClassDB::bind_method(D_METHOD("gets_xp"), &Entity::gets_xp);
	ClassDB::bind_method(D_METHOD("sets_xp", "value"), &Entity::sets_xp);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "s_xp"), "sets_xp", "gets_xp");

	ClassDB::bind_method(D_METHOD("getc_xp"), &Entity::getc_xp);
	ClassDB::bind_method(D_METHOD("setc_xp", "value"), &Entity::setc_xp);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "c_xp"), "setc_xp", "getc_xp");

	ClassDB::bind_method(D_METHOD("gets_entity_data"), &Entity::gets_entity_data);
	ClassDB::bind_method(D_METHOD("sets_entity_data", "value"), &Entity::sets_entity_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "s_entity_data", PROPERTY_HINT_RESOURCE_TYPE, "EntityData"), "sets_entity_data", "gets_entity_data");

	ClassDB::bind_method(D_METHOD("getc_entity_data"), &Entity::getc_entity_data);
	ClassDB::bind_method(D_METHOD("setc_entity_data", "value"), &Entity::setc_entity_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "c_entity_data", PROPERTY_HINT_RESOURCE_TYPE, "EntityData"), "setc_entity_data", "getc_entity_data");

	ClassDB::bind_method(D_METHOD("initialize", "entity_create_info"), &Entity::initialize);

	ClassDB::bind_method(D_METHOD("get_health"), &Entity::get_health);
	ClassDB::bind_method(D_METHOD("get_mana"), &Entity::get_mana);
	ClassDB::bind_method(D_METHOD("get_rage"), &Entity::get_rage);
	ClassDB::bind_method(D_METHOD("get_energy"), &Entity::get_energy);
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

	//Resources
	ClassDB::bind_method(D_METHOD("gets_resource", "index"), &Entity::gets_resource);
	ClassDB::bind_method(D_METHOD("gets_resource_type", "type"), &Entity::gets_resource_type);
	ClassDB::bind_method(D_METHOD("adds_resource", "palyer_resource"), &Entity::adds_resource);
	ClassDB::bind_method(D_METHOD("gets_resource_count"), &Entity::gets_resource_count);
	ClassDB::bind_method(D_METHOD("removes_resource", "index"), &Entity::removes_resource);
	ClassDB::bind_method(D_METHOD("clears_resource"), &Entity::clears_resource);

	ClassDB::bind_method(D_METHOD("getc_resource", "index"), &Entity::getc_resource);
	ClassDB::bind_method(D_METHOD("getc_resource_type", "type"), &Entity::getc_resource_type);
	ClassDB::bind_method(D_METHOD("addc_resource", "palyer_resource"), &Entity::addc_resource);
	ClassDB::bind_method(D_METHOD("getc_resource_count"), &Entity::getc_resource_count);
	ClassDB::bind_method(D_METHOD("removec_resource", "index"), &Entity::removec_resource);
	ClassDB::bind_method(D_METHOD("clearc_resource"), &Entity::clearc_resource);

	//GCD
	ADD_SIGNAL(MethodInfo("sgcd_started", PropertyInfo(Variant::REAL, "value")));
	ADD_SIGNAL(MethodInfo("sgcd_finished"));
	ADD_SIGNAL(MethodInfo("cgcd_started", PropertyInfo(Variant::REAL, "value")));
	ADD_SIGNAL(MethodInfo("cgcd_finished"));

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

	//Casting System

	ClassDB::bind_method(D_METHOD("sis_casting"), &Entity::sis_casting);
	ClassDB::bind_method(D_METHOD("cis_casting"), &Entity::cis_casting);

	ClassDB::bind_method(D_METHOD("gets_spell_cast_info"), &Entity::gets_spell_cast_info);
	ClassDB::bind_method(D_METHOD("sets_spell_cast_info", "value"), &Entity::sets_spell_cast_info);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "sspell_cast_info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo"), "sets_spell_cast_info", "gets_spell_cast_info");

	ClassDB::bind_method(D_METHOD("getc_spell_cast_info"), &Entity::getc_spell_cast_info);
	ClassDB::bind_method(D_METHOD("setc_spell_cast_info", "value"), &Entity::setc_spell_cast_info);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "cspell_cast_info", PROPERTY_HINT_RESOURCE_TYPE, "SpellCastInfo"), "setc_spell_cast_info", "getc_spell_cast_info");

	ClassDB::bind_method(D_METHOD("sstart_casting", "info"), &Entity::sstart_casting);
	ClassDB::bind_method(D_METHOD("sfail_cast"), &Entity::sfail_cast);
	ClassDB::bind_method(D_METHOD("sdelay_cast"), &Entity::sdelay_cast);
	ClassDB::bind_method(D_METHOD("sfinish_cast"), &Entity::sfinish_cast);
	ClassDB::bind_method(D_METHOD("sinterrupt_cast"), &Entity::sinterrupt_cast);

	ClassDB::bind_method(D_METHOD("cstart_casting", "info"), &Entity::cstart_casting);
	ClassDB::bind_method(D_METHOD("cfail_cast"), &Entity::cfail_cast);
	ClassDB::bind_method(D_METHOD("cdelay_cast"), &Entity::cdelay_cast);
	ClassDB::bind_method(D_METHOD("cfinish_cast"), &Entity::cfinish_cast);
	ClassDB::bind_method(D_METHOD("cinterrupt_cast"), &Entity::cinterrupt_cast);

	//Cooldowns
	ADD_SIGNAL(MethodInfo("scooldown_added", PropertyInfo(Variant::OBJECT, "cooldown", PROPERTY_HINT_RESOURCE_TYPE, "Cooldown")));
	ADD_SIGNAL(MethodInfo("scooldown_removed", PropertyInfo(Variant::OBJECT, "cooldown", PROPERTY_HINT_RESOURCE_TYPE, "Cooldown")));
	ADD_SIGNAL(MethodInfo("ccooldown_added", PropertyInfo(Variant::OBJECT, "cooldown", PROPERTY_HINT_RESOURCE_TYPE, "Cooldown")));
	ADD_SIGNAL(MethodInfo("ccooldown_removed", PropertyInfo(Variant::OBJECT, "cooldown", PROPERTY_HINT_RESOURCE_TYPE, "Cooldown")));

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
	ADD_SIGNAL(MethodInfo("scategory_cooldown_removed", PropertyInfo(Variant::OBJECT, "cooldown", PROPERTY_HINT_RESOURCE_TYPE, "CategoryCooldown")));
	ADD_SIGNAL(MethodInfo("ccategory_cooldown_added", PropertyInfo(Variant::OBJECT, "cooldown", PROPERTY_HINT_RESOURCE_TYPE, "CategoryCooldown")));
	ADD_SIGNAL(MethodInfo("ccategory_cooldown_removed", PropertyInfo(Variant::OBJECT, "cooldown", PROPERTY_HINT_RESOURCE_TYPE, "CategoryCooldown")));

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

	ClassDB::bind_method(D_METHOD("crequest_target_change", "path"), &Entity::crequest_target_change);
	ClassDB::bind_method(D_METHOD("net_sets_target", "path"), &Entity::net_sets_target);
	ClassDB::bind_method(D_METHOD("net_setc_target", "path"), &Entity::net_setc_target);

	ClassDB::bind_method(D_METHOD("gets_target"), &Entity::gets_target);
	ClassDB::bind_method(D_METHOD("sets_target", "target"), &Entity::sets_target);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "starget", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "sets_target", "gets_target");

	ClassDB::bind_method(D_METHOD("getc_target"), &Entity::getc_target);
	ClassDB::bind_method(D_METHOD("setc_target", "target"), &Entity::setc_target);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ctarget", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "setc_target", "getc_target");
}
