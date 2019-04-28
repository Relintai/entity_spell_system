#include "entity.h"

#include "../data/aura.h"
#include "../data/spell.h"
#include "../entities/auras/aura_data.h"
#include "../pipelines/spell_damage_info.h"

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

PlayerStates Entity::getc_state() {
	return _c_state;
}
void Entity::setc_state(PlayerStates state) {
	_c_state = state;
}

PlayerStates Entity::gets_state() {
	return _s_state;
}
void Entity::sets_state(PlayerStates state) {
	_s_state = state;
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

	cHasGlobalCooldown = false;
	sHasGlobalCooldown = false;
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

	_s_target_guid = 0;
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
       INVENTORY_DEFAULT_SIZE = 21;
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
	_melee_damage = Ref<Stat>(get_stat_enum(Stat::STAT_ID_MELEE_DAMAGE));
	_spell_damage = Ref<Stat>(get_stat_enum(Stat::STAT_ID_SPELL_DAMAGE));

	_s_auras = memnew(Vector<Ref<AuraData> >());
	_c_auras = memnew(Vector<Ref<AuraData> >());

}

Entity::~Entity() {
	_s_auras->clear();
	_c_auras->clear();

	memdelete(_s_auras);
	memdelete(_c_auras);
}

void Entity::initialize(EntityCreateInfo *info) {
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
	}
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
	return cHasGlobalCooldown;
}

bool Entity::gets_has_global_cooldown() {
	return sHasGlobalCooldown;
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
	//ERR_FAIL_COND(stat_id == Stat::STAT_ID_NONE);

	if (stat_id == Stat::STAT_ID_NONE) {
		print_error("Add fail cond here, stat has STAT_ID_NONE!");
		_stats[0] = Ref<Stat>(entry);
		return;
	}

	_stats[stat_id] = Ref<Stat>(entry);
}

/*
float Entity::getSRezTimer() {
	return sRezTimer;
}

float Entity::getCRezTimer() {
	return cRezTimer;
}*/
/*
void Entity::Init() {
	s = true;
	if (s && c) {
		localClient = true;
	}
	StatData *stats = owner->PlayerData->Character->Stats;
	if (owner->isServer) {
		stats->GetStatForStat(SHealth);
		stats->GetStatForStat(SMana);
		stats->GetStatForStat(SSpeed);
		stats->GetStatForStat(SGCD);
		stats->GetStatForStat(SMeleeCrit);
		stats->GetStatForStat(SMeleeCritBonus);
		stats->GetStatForStat(SSpellCrit);
		stats->GetStatForStat(SSpellCritBonus);
		stats->GetStatForStat(SBlock);
		stats->GetStatForStat(SParry);
		stats->GetStatForStat(SDamageReduction);
		stats->GetStatForStat(SMeleeDamageReduction);
		stats->GetStatForStat(SSpellDamageReduction);
		stats->GetStatForStat(SDamageTaken);
		stats->GetStatForStat(SMeleeDamage);
		stats->GetStatForStat(SSpellDamage);
		SHealth->Dirty = true;
		SMana->Dirty = true;
		SSpeed->Dirty = true;
		SGCD->Dirty = true;
		SMeleeCrit->Dirty = true;
		SMeleeCritBonus->Dirty = true;
		SSpellCrit->Dirty = true;
		SSpellCritBonus->Dirty = true;
		SBlock->Dirty = true;
		SParry->Dirty = true;
		SDamageReduction->Dirty = true;
		SMeleeDamageReduction->Dirty = true;
		SSpellDamageReduction->Dirty = true;
		SDamageTaken->Dirty = true;
		SMeleeDamage->Dirty = true;
		SSpellDamage->Dirty = true;
	}
	stats->GetStatForStat(CHealth);
	stats->GetStatForStat(CMana);
	stats->GetStatForStat(CSpeed);
	stats->GetStatForStat(CGCD);
	stats->GetStatForStat(CMeleeCrit);
	stats->GetStatForStat(CMeleeCritBonus);
	stats->GetStatForStat(CSpellCrit);
	stats->GetStatForStat(CSpellCritBonus);
	stats->GetStatForStat(CBlock);
	stats->GetStatForStat(CParry);
	stats->GetStatForStat(CDamageReduction);
	stats->GetStatForStat(CMeleeDamageReduction);
	stats->GetStatForStat(CSpellDamageReduction);
	stats->GetStatForStat(CDamageTaken);
	stats->GetStatForStat(CMeleeDamage);
	stats->GetStatForStat(CSpellDamage);
	init = true;
}*/
/*
void Entity::Update() {
	if (!init) {
		return;
	}

	if (cHasGlobalCooldown) {
		Stat *expr_49 = CGCD;
		expr_49->GCDTime -= Time::deltaTime;
		CGCD->Dirty = false;
		if (!CGCD->hasGCD()) {
			cHasGlobalCooldown = false;
		}
	}

	if (owner->isServer) {
		if (sHasGlobalCooldown) {
			Stat *expr_C5 = SGCD;
			expr_C5->GCDTime -= Time::deltaTime;
			SGCD->Dirty = false;
			if (!SGCD->hasGCD()) {
				sHasGlobalCooldown = false;
				if (SOnStatChanged != null) {
					DELEGATE_INVOKE(SOnStatChanged, 3, SGCD);
				}
			}
		}
	}
}

void Entity::LateUpdate() {
	if (!CxNet::IsServer || !init) {
		return;
	}
	if (SHealth->Dirty || SMana->Dirty) {
		CStatUpdateMsg cStatUpdateMsg = CStatUpdateMsg();
		cStatUpdateMsg.Guid = owner->PlayerData->GUID;
		cStatUpdateMsg.Initialize(CxNet::NetBuffer);
		if (SHealth->Dirty) {
			AddStat(cStatUpdateMsg, SHealth);
		}
		if (SMana->Dirty) {
			AddStat(cStatUpdateMsg, SMana);
		}
		cStatUpdateMsg.FinishMessage();
		CxNet::SendBufferToAllClientsExcept(owner->Connection, 0);
	}
	if ((((((((((((((SHealth->Dirty || SMana->Dirty) || SSpeed->Dirty) || SMeleeCrit->Dirty) || SMeleeCritBonus->Dirty) || SSpellCrit->Dirty) || SSpellCritBonus->Dirty) || SBlock->Dirty) || SParry->Dirty) || SDamageReduction->Dirty) || SMeleeDamageReduction->Dirty) || SSpellDamageReduction->Dirty) || SDamageTaken->Dirty) || SMeleeDamage->Dirty) || SSpellDamage->Dirty) {
		CStatUpdateMsg cStatUpdateMsg2 = CStatUpdateMsg();
		cStatUpdateMsg2.Guid = owner->PlayerData->GUID;
		cStatUpdateMsg2.Initialize(CxNet::NetBuffer);
		if (SHealth->Dirty) {
			AddStat(cStatUpdateMsg2, SHealth);
		}
		if (SMana->Dirty) {
			AddStat(cStatUpdateMsg2, SMana);
		}
		if (SSpeed->Dirty) {
			AddStat(cStatUpdateMsg2, SSpeed);
		}
		if (SMeleeCrit->Dirty) {
			AddStat(cStatUpdateMsg2, SMeleeCrit);
		}
		if (SMeleeCritBonus->Dirty) {
			AddStat(cStatUpdateMsg2, SMeleeCritBonus);
		}
		if (SSpellCrit->Dirty) {
			AddStat(cStatUpdateMsg2, SSpellCrit);
		}
		if (SSpellCritBonus->Dirty) {
			AddStat(cStatUpdateMsg2, SSpellCritBonus);
		}
		if (SBlock->Dirty) {
			AddStat(cStatUpdateMsg2, SBlock);
		}
		if (SParry->Dirty) {
			AddStat(cStatUpdateMsg2, SParry);
		}
		if (SDamageReduction->Dirty) {
			AddStat(cStatUpdateMsg2, SDamageReduction);
		}
		if (SMeleeDamageReduction->Dirty) {
			AddStat(cStatUpdateMsg2, SMeleeDamageReduction);
		}
		if (SSpellDamageReduction->Dirty) {
			AddStat(cStatUpdateMsg2, SSpellDamageReduction);
		}
		if (SDamageTaken->Dirty) {
			AddStat(cStatUpdateMsg2, SDamageTaken);
		}
		if (SMeleeDamage->Dirty) {
			AddStat(cStatUpdateMsg2, SMeleeCrit);
		}
		if (SSpellDamage->Dirty) {
			AddStat(cStatUpdateMsg2, SSpellDamage);
		}
		cStatUpdateMsg2.FinishMessage();
		if (owner->Connection != null) {
			owner->Connection->SendBuffer(0, CxNet::NetBuffer);
		} else {
			cStatUpdateMsg2.ResetToStats();
			CHandleStatUpdateMsg(cStatUpdateMsg2);
		}
	}
	if (SHealth->Dirty) {
		if (SOnStatChanged != null) {
			DELEGATE_INVOKE(SOnStatChanged, SHealth->Id, SHealth);
		}
		SHealth->Dirty = false;
	}
	if (SMana->Dirty) {
		if (SOnStatChanged != null) {
			DELEGATE_INVOKE(SOnStatChanged, SMana->Id, SMana);
		}
		SMana->Dirty = false;
	}
	if (SSpeed->Dirty) {
		if (SOnStatChanged != null) {
			DELEGATE_INVOKE(SOnStatChanged, SSpeed->Id, SSpeed);
		}
		SSpeed->Dirty = false;
	}
	if (SGCD->Dirty) {
		if (SOnStatChanged != null) {
			DELEGATE_INVOKE(SOnStatChanged, SGCD->Id, SGCD);
		}
		SGCD->Dirty = false;
	}
	if (SMeleeCrit->Dirty) {
		if (SOnStatChanged != null) {
			DELEGATE_INVOKE(SOnStatChanged, SMeleeCrit->Id, SMeleeCrit);
		}
		SMeleeCrit->Dirty = false;
	}
	if (SMeleeCritBonus->Dirty) {
		if (SOnStatChanged != null) {
			DELEGATE_INVOKE(SOnStatChanged, SMeleeCritBonus->Id, SMeleeCritBonus);
		}
		SMeleeCritBonus->Dirty = false;
	}
	if (SSpellCrit->Dirty) {
		if (SOnStatChanged != null) {
			DELEGATE_INVOKE(SOnStatChanged, SSpellCrit->Id, SSpellCrit);
		}
		SSpellCrit->Dirty = false;
	}
	if (SSpellCritBonus->Dirty) {
		if (SOnStatChanged != null) {
			DELEGATE_INVOKE(SOnStatChanged, SSpellCritBonus->Id, SSpellCritBonus);
		}
		SSpellCritBonus->Dirty = false;
	}
	if (SBlock->Dirty) {
		if (SOnStatChanged != null) {
			DELEGATE_INVOKE(SOnStatChanged, SBlock->Id, SBlock);
		}
		SBlock->Dirty = false;
	}
	if (SParry->Dirty) {
		if (SOnStatChanged != null) {
			DELEGATE_INVOKE(SOnStatChanged, SParry->Id, SParry);
		}
		SParry->Dirty = false;
	}
	if (SDamageReduction->Dirty) {
		if (SOnStatChanged != null) {
			DELEGATE_INVOKE(SOnStatChanged, SDamageReduction->Id, SDamageReduction);
		}
		SDamageReduction->Dirty = false;
	}
	if (SMeleeDamageReduction->Dirty) {
		if (SOnStatChanged != null) {
			DELEGATE_INVOKE(SOnStatChanged, SMeleeDamageReduction->Id, SMeleeDamageReduction);
		}
		SMeleeDamageReduction->Dirty = false;
	}
	if (SSpellDamageReduction->Dirty) {
		if (SOnStatChanged != null) {
			DELEGATE_INVOKE(SOnStatChanged, SSpellDamageReduction->Id, SSpellDamageReduction);
		}
		SSpellDamageReduction->Dirty = false;
	}
	if (SDamageTaken->Dirty) {
		if (SOnStatChanged != null) {
			DELEGATE_INVOKE(SOnStatChanged, SDamageTaken->Id, SDamageTaken);
		}
		SDamageTaken->Dirty = false;
	}
	if (SMeleeDamage->Dirty) {
		if (SOnStatChanged != null) {
			DELEGATE_INVOKE(SOnStatChanged, SMeleeCrit->Id, SMeleeCrit);
		}
		SMeleeCrit->Dirty = false;
	}
	if (SSpellDamage->Dirty) {
		if (SOnStatChanged != null) {
			DELEGATE_INVOKE(SOnStatChanged, SSpellDamage->Id, SSpellDamage);
		}
		SSpellDamage->Dirty = false;
	}
}

void Entity::AddStat(CStatUpdateMsg &msg, Stat *stat) {
	msg.Buffer->WriteInt(stat.Id);
	msg.Buffer->WriteFloat(stat.ModCurrent);
	msg.Buffer->WriteFloat(stat.ModMax);
	msg.Buffer->WriteFloat(stat.ModPercent);
}

void Entity::AddStat(CStatUpdateMsg &msg, Stat *stat) {
	msg.Buffer->WriteInt(stat.Id);
	msg.Buffer->WriteFloat(stat.ModCurrent);
	msg.Buffer->WriteFloat(stat.ModMax);
	msg.Buffer->WriteFloat(stat.ModPercent);
}

void Entity::AddStat(CStatUpdateMsg &msg, Stat *stat) {
	msg.Buffer->WriteInt(stat.Id);
	msg.Buffer->WriteFloat(stat.ModPercent);
}

void Entity::AddStat(CStatUpdateMsg &msg, Stat *stat) {
	msg.Buffer->WriteInt(stat.Id);
	msg.Buffer->WriteFloat(stat.ModPercent);
}

void Entity::CHandleStatUpdateMsg(CStatUpdateMsg &msg) {
	while (msg.HasNext()) {
		CReadStat(msg);
		msg.Step();
	}
}

void Entity::CReadStat(CStatUpdateMsg &msg) {
	if ((msg.Next() >= 16) || (msg.Next() < 0)) {
		return;
	}
	Stat *cStatFromId = GetCStatFromId(msg.Next());
	if (is_inst_of<Stat *>(cStatFromId)) {
		ReadStat(msg, (Stat *)(cStatFromId));
	} else {
		if (is_inst_of<Stat *>(cStatFromId)) {
			ReadStat(msg, (Stat *)(cStatFromId));
		} else {
			if (is_inst_of<Stat *>(cStatFromId)) {
				ReadStat(msg, (Stat *)(cStatFromId));
			}
		}
	}
	cStatFromId.Dirty = false;
	if (OnStatChanged != null) {
		DELEGATE_INVOKE(OnStatChanged, cStatFromId.Id, cStatFromId);
	}
}

void Entity::ReadStat(CStatUpdateMsg &msg, Stat *stat) {
	if ((msg.Next() >= 16) || (msg.Next() < 0)) {
		return;
	}
	stat.ModCurrent = msg.Buffer->ReadFloat();
	stat.ModMax = msg.Buffer->ReadFloat();
	stat.ModPercent = msg.Buffer->ReadFloat();
}

void Entity::ReadStat(CStatUpdateMsg &msg, Stat *stat) {
	stat.ModPercent = msg.Buffer->ReadFloat();
}

void Entity::ReadStat(CStatUpdateMsg &msg, Stat *stat) {
	stat.ModPercent = msg.Buffer->ReadFloat();
}
*/

void Entity::stake_damage(Ref<SpellDamageInfo> data) {
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
	emit_signal("son_damage_taken", this, data);

	if (get_health()->gets_current() <= 0) {
		die();
	}
}

void Entity::son_damage_dealt(Ref<SpellDamageInfo> data) {
	//serverside
	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_damage_dealt(data);
	}
}

void Entity::sdeal_damage_to(Ref<SpellDamageInfo> data) {
	//serverside

	if (gets_is_dead()) {
		return;
	}

	sapply_passives_damage_deal(data);
	data->get_receiver()->stake_damage(data);
	son_damage_dealt(data);
}

void Entity::take_heal(int heal, bool crit, Entity *dealer) {
	/*
	if (sIsDead) {
		return;
	}
	Stat *expr_0F = SHealth;
	expr_0F->Current += (float)(heal);
	if (SHealth->Current > SHealth->Max) {
		SHealth->Current = SHealth->Max;
	}
	if (owner->isServer) {
		SendHealTakenMessage(heal, crit, dealer);
	}*/
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

/*
void Entity::SendDamageTakenMessage(int damage, bool crit, Entity *dealer) {
	CDamageTakenMsg cDamageTakenMsg = CDamageTakenMsg();
	cDamageTakenMsg.Guid = owner->PlayerData->GUID;
	if (dealer != null) {
		cDamageTakenMsg.DealerGuid = dealer->getPlayerData()->GUID;
	}
	cDamageTakenMsg.Crit = crit;
	cDamageTakenMsg.Value = damage;
	cDamageTakenMsg.Serialize(CxNet::NetBuffer);
	bool flag = false;
	if (owner->Connection != null) {
		owner->Connection->SendBuffer(0, CxNet::NetBuffer);
	} else {
		CReceiveDamageTaken(damage, crit, dealer);
		flag = true;
	}
	if ((dealer != null) && (dealer->getConnection() != null)) {
		dealer->getConnection()->SendBuffer(0, CxNet::NetBuffer);
		return;
	}
	if (!flag) {
		CReceiveDamageTaken(damage, crit, dealer);
	}
}

void Entity::SendHealTakenMessage(int heal, bool crit, Entity *dealer) {
	CHealTakenMsg cHealTakenMsg = CHealTakenMsg();
	cHealTakenMsg.Guid = owner->PlayerData->GUID;
	if (dealer != null) {
		cHealTakenMsg.DealerGuid = dealer->getPlayerData()->GUID;
	}
	cHealTakenMsg.Crit = crit;
	cHealTakenMsg.Value = heal;
	cHealTakenMsg.Serialize(CxNet::NetBuffer);
	bool flag = false;
	if (owner->Connection != null) {
		owner->Connection->SendBuffer(0, CxNet::NetBuffer);
	} else {
		CReceiveHealTaken(heal, crit, dealer);
		flag = true;
	}
	if ((dealer != null) && (dealer->getConnection() != null)) {
		dealer->getConnection()->SendBuffer(0, CxNet::NetBuffer);
		return;
	}
	if (!flag) {
		CReceiveHealTaken(heal, crit, dealer);
	}
}

void Entity::SendResurrectMessage() {
	if (owner->Connection != null) {
		CResurrectMsg cResurrectMsg = CResurrectMsg();
		cResurrectMsg.Guid = owner->PlayerData->GUID;
		cResurrectMsg.Serialize(CxNet::NetBuffer);
		owner->Connection->SendBuffer(0, CxNet::NetBuffer);
		return;
	}
	CReceiveResurrect();
}

void Entity::SendDieMessage() {
	if (owner->Connection != null) {
		CDiedMsg cDiedMsg = CDiedMsg();
		cDiedMsg.Guid = owner->PlayerData->GUID;
		cDiedMsg.Serialize(CxNet::NetBuffer);
		owner->Connection->SendBuffer(0, CxNet::NetBuffer);
		return;
	}
	CReceiveDied();
}

void Entity::SendTriggerGCDMessage() {
	if (owner->Connection != null) {
		CTriggerGCDMsg cTriggerGCDMsg = CTriggerGCDMsg();
		cTriggerGCDMsg.Guid = owner->PlayerData->GUID;
		cTriggerGCDMsg.Serialize(CxNet::NetBuffer);
		owner->Connection->SendBuffer(0, CxNet::NetBuffer);
		return;
	}
	CReceiveTriggerGlobalCooldown();
}*/

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
	//the current c health should probably be set here.
	emit_signal("con_damage_taken", this, data);
}

void Entity::creceiveon_damage_dealt(Ref<SpellDamageInfo> data) {
	//the current c health should probably be set here.
	emit_signal("con_damage_dealt", this, data);
}

void Entity::creceive_heal_taken(int heal, bool crit, Entity *dealer) {
	/*
	if (CHealth->Current > CHealth->Max) {
		CHealth->Current = CHealth->Max;
	}
	if (COnHealTaken != null) {
		DELEGATE_INVOKE(COnHealTaken, heal, crit, owner, dealer);
	}*/
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
	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_before_aura_applied(data);
	}
}

void Entity::son_after_aura_applied(Ref<AuraData> data) {
	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		if (ad == data) {
			continue;
		}

		ad->get_aura()->son_after_aura_applied(data);
	}
}

void Entity::trigger_global_cooldown() {
	/*
	if (!owner->isServer) {
		return;
	}
	sHasGlobalCooldown = true;
	if (BSSettings::Getinstance()->AnimStopEnabled) {
		SGCD->ModCurrent = SGCD->ModMax - BSSettings::Getinstance()->GetBSTestAnimStopDataForClass(owner->PlayerData->ClassId)->GCDReduce;
	} else {
		SGCD->ModCurrent = SGCD->ModMax;
	}
	SGCD->Dirty = false;
	if (SOnStatChanged != null) {
		DELEGATE_INVOKE(SOnStatChanged, 3, SGCD);
	}
	SendTriggerGCDMessage();*/
}

void Entity::creceive_trigger_global_cooldown() {
	/*
	if (!owner->isClient) {
		return;
	}
	CGCD->ModCurrent = CGCD->ModMax;
	CGCD->Dirty = false;
	cHasGlobalCooldown = true;
	if (OnStatChanged != null) {
		DELEGATE_INVOKE(OnStatChanged, 3, CGCD);
	}*/
}
/*
Stat *Entity::GetSStatFromId(int id) {
	switch (id) {
		case 0:
			return SHealth;

		case 1:
			return SSpeed;

		case 2:
			return SMana;

		case 3:
			return SGCD;

		case 4:
			return SMeleeCrit;

		case 5:
			return SMeleeCrit;

		case 6:
			return SSpellCrit;

		case 7:
			return SSpellCritBonus;

		case 8:
			return SBlock;

		case 9:
			return SParry;

		case 10:
			return SDamageReduction;

		case 11:
			return SMeleeDamageReduction;

		case 12:
			return SSpellDamageReduction;

		case 13:
			return SDamageTaken;

		case 14:
			return SMeleeDamage;

		case 15:
			return SSpellDamage;

		default:
			return null;
	}
}

Stat *Entity::GetCStatFromId(int id) {
	switch (id) {
		case 0:
			return CHealth;

		case 1:
			return CSpeed;

		case 2:
			return CMana;

		case 3:
			return CGCD;

		case 4:
			return CMeleeCrit;

		case 5:
			return CMeleeCrit;

		case 6:
			return CSpellCrit;

		case 7:
			return CSpellCritBonus;

		case 8:
			return CBlock;

		case 9:
			return CParry;

		case 10:
			return CDamageReduction;

		case 11:
			return CMeleeDamageReduction;

		case 12:
			return CSpellDamageReduction;

		case 13:
			return CDamageTaken;

		case 14:
			return CMeleeDamage;

		case 15:
			return CSpellDamage;

		default:
			return null;
	}
}

int Entity::GetStatIdFromString(String *name) {
	uint num = <PrivateImplementationDetails>::ComputeStringHash(name);
	if (num <= 2653573473u) {
		if (num <= 792771830u) {
			if (num <= 637686477u) {
				if (num != 310003575u) {
					if (num == 637686477u) {
						if (*name == *(new String("STAT_MELEE_CRIT_BONUS"))) {
							return 5;
						}
					}
				} else {
					if (*name == *(new String("STAT_MANA"))) {
						return 2;
					}
				}
			} else {
				if (num != 755108934u) {
					if (num == 792771830u) {
						if (*name == *(new String("STAT_SPELL_DAMAGE"))) {
							return 15;
						}
					}
				} else {
					if (*name == *(new String("STAT_PARRY"))) {
						return 9;
					}
				}
			}
		} else {
			if (num <= 1547871327u) {
				if (num != 858277321u) {
					if (num == 1547871327u) {
						if (*name == *(new String("STAT_SPELL_CRIT_BONUS"))) {
							return 7;
						}
					}
				} else {
					if (*name == *(new String("STAT_BLOCK"))) {
						return 8;
					}
				}
			} else {
				if (num != 2430374284u) {
					if (num == 2653573473u) {
						if (*name == *(new String("STAT_GLOBAL_COOLDOWN"))) {
							return 3;
						}
					}
				} else {
					if (*name == *(new String("STAT_MELEE_DAMAGE"))) {
						return 14;
					}
				}
			}
		}
	} else {
		if (num <= 3359549743u) {
			if (num <= 3041242134u) {
				if (num != 2914522126u) {
					if (num == 3041242134u) {
						if (*name == *(new String("STAT_MELEE_REDUCTION"))) {
							return 11;
						}
					}
				} else {
					if (*name == *(new String("STAT_HEALTH"))) {
						return 0;
					}
				}
			} else {
				if (num != 3083148548u) {
					if (num == 3359549743u) {
						if (*name == *(new String("STAT_DAMAGE_REDUCTION"))) {
							return 10;
						}
					}
				} else {
					if (*name == *(new String("STAT_SPELL_DAMAGE_REDUCTION"))) {
						return 12;
					}
				}
			}
		} else {
			if (num <= 3609862625u) {
				if (num != 3408551541u) {
					if (num == 3609862625u) {
						if (*name == *(new String("STAT_MELEE_CRIT"))) {
							return 4;
						}
					}
				} else {
					if (*name == *(new String("STAT_DAMAGE_TAKEN"))) {
						return 13;
					}
				}
			} else {
				if (num != 4043142103u) {
					if (num == 4290636275u) {
						if (*name == *(new String("STAT_SPEED"))) {
							return 1;
						}
					}
				} else {
					if (*name == *(new String("STAT_SPELL_CRIT"))) {
						return 6;
					}
				}
			}
		}
	}
	Debug::Log((*(new String("Stat: ")) + *name) + *(new String(" doesn't exists!")));
	return 0;
}
*/
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

void Entity::casting_finished(Entity *caster, int spellId, float scale) {
}

void Entity::update_auras(float delta) {
	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->supdate(ad, delta);
	}
}

void Entity::son_before_cast(Ref<SpellCastInfo> info) {
	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_before_cast(info);
	}
}

void Entity::son_before_cast_target(Ref<SpellCastInfo> info) {
	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_before_cast_target(info);
	}
}

void Entity::son_hit(Ref<SpellDamageInfo> data) {
	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_hit(data);
	}
}

void Entity::son_before_damage(Ref<SpellDamageInfo> data) {
	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_before_damage(data);
	}
}

void Entity::son_damage_receive(Ref<SpellDamageInfo> data) {
	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_damage_receive(data);
	}
}

void Entity::son_dealt_damage(Ref<SpellDamageInfo> data) {
	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_damage_dealt(data);
	}
}

void Entity::sapply_passives_damage_receive(Ref<SpellDamageInfo> data) {
	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->sapply_passives_damage_receive(data);
	}
}

void Entity::sapply_passives_damage_deal(Ref<SpellDamageInfo> data) {
	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->sapply_passives_damage_deal(data);
	}
}


void Entity::remove_auras_with_group(Entity *ac, int auraGroup) {
}

void Entity::sremove_aura_expired(Ref<AuraData> aura) {
	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_remove(aura);
	}

	for (int i = 0; i < _s_auras->size(); ++i) {
		if (_s_auras->get(i) == aura) {
			_s_auras->remove(i);
		}
	}
}

void Entity::cremove_aura_expired(Ref<AuraData> aura) {
	for (int i = 0; i < _s_auras->size(); ++i) {
		if (_c_auras->get(i) == aura) {
			_c_auras->remove(i);
		}
	}
}

void Entity::sremove_aura(Ref<AuraData> aura) {
	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_remove(aura);
	}

	for (int i = 0; i < _s_auras->size(); ++i) {
		if (_s_auras->get(i) == aura) {
			_s_auras->remove(i);
		}
	}
}

void Entity::cremove_aura(Ref<AuraData> aura) {
	for (int i = 0; i < _s_auras->size(); ++i) {
		if (_c_auras->get(i) == aura) {
			_c_auras->remove(i);
		}
	}
}

void Entity::crefresh_aura(Entity *ac, int auraId, float time) {
}

void Entity::crefresh_caster_aura(Entity *ac, int auraId, Entity *caster, float time) {
}

void Entity::caura_added(Entity *ac, int id, float remaining, Entity *caster, int casterGUID) {
}

void Entity::caura_removed(Entity *ac, int id) {
}

void Entity::setup_on_player_moves(Entity *bopmccc, Vector<int> *sspells) {
}

void Entity::con_cast_failed(Entity *caster, int spellId) {
}

void Entity::con_cast_started(Entity *caster, int spellId) {
}

void Entity::con_cast_state_changed(Entity *caster, int spellId) {
}

void Entity::con_cast_finished(Entity *caster, int spellId) {
}

void Entity::con_spell_cast_success(Entity *caster, int spellId) {
}

////    Casting System    ////

void Entity::AfterLoadFinished() {
	/*
       for (int i = 0; i < serverAuras->Count; i += 1) {
       AuraData *auraData = serverAuras->GetData(i);
       if (auraData->CasterGUID != 0u) {
       auraData->Caster = Entity::SGetPLayerWithGUID(auraData->CasterGUID)->GetComponent<Entity>();
       }
       }

       if (serverAuras->Count > 0) {
       send = true;
       }

    //targetComponent
    if (getSTargetGUID() != 0u) {
    AISetTarget((Entity *)(Entity::SGetPLayerWithGUID(getSTargetGUID())));
    }

    state = PlayerStates.STATE_NORMAL;

    if (owner.isServer) {
    if (Type != (int)EntityType.Mob && ClassId != 0) {
    character = CharacterDataLoader.Instance[ClassId];
    } else {
    character = CharacterDataLoader.Instance[ClassId];
    }

    //itemDataLoader = GameObject.FindGameObjectWithTag("Data").GetComponent<CG>().GetChild("Items").GetComponent<ItemDataLoader>();
    itemDataLoader = ItemDataLoader.Instance;

    weaponId = GetWeaponForClass();

    OnWeaponChangedHook(WeaponId);

    if (applyModifiersOnInit) {
    applyModifiersOnInit = false;

    ApplyLevelModifiers();
    }
    }*/
}

//void Entity::ssend_start_casting(int spellId, float castTime) {
	/*
       if (CxNet::IsServer) {
       SSpellCastStartedMsg sSpellCastStartedMsg = SSpellCastStartedMsg();
       sSpellCastStartedMsg.Guid = owner->PlayerData->GUID;
       sSpellCastStartedMsg.SpellId = spellId;
       sSpellCastStartedMsg.CastTime = castTime;
       sSpellCastStartedMsg.Serialize(CxNet::NetBuffer);
       CxNet::SendBufferToAllClients(0);
       }*/
//}

//void Entity::ssend_cast_failed() {
	/*
       if (CxNet::IsServer) {
       SSpellCastFailedMsg sSpellCastFailedMsg = SSpellCastFailedMsg();
       sSpellCastFailedMsg.Guid = owner->PlayerData->GUID;
       sSpellCastFailedMsg.Serialize(CxNet::NetBuffer);
       CxNet::SendBufferToAllClients(0);
       }*/
//}

//void Entity::ssend_cast_finished(int spellId) {
	/*
       if (CxNet::IsServer) {
       SSpellCastFinishedMsg sSpellCastFinishedMsg = SSpellCastFinishedMsg();
       sSpellCastFinishedMsg.Guid = owner->PlayerData->GUID;
       sSpellCastFinishedMsg.Serialize(CxNet::NetBuffer);
       CxNet::SendBufferToAllClients(0);
       }*/
//}

//void Entity::creceive_start_casting(int spellId, float castTime) {

	/*
       Spell *spell = Spells::Instance->GetData(spellId);
       setCSpellName(spell->SpellName);
       setCCastTime(castTime);
       setCCasting(true);
       setCCurrentCastTime((float)0);
       SpellMgr::COnCastStarted(owner, spellId);
       if (COnCastStart != null) {
       DELEGATE_INVOKE(COnCastStart, spellId);
       }*/
//}

//void Entity::creceive_cast_finished() {
	/*
       setCCasting(false);
       if (COnCastFinished != null) {
       DELEGATE_INVOKE(COnCastFinished, getCSpellId());
       }
       if (COnCastEnded != null) {
       DELEGATE_INVOKE(COnCastEnded, getCSpellId());
       }
       DELEGATE_INVOKE(SpellMgr::COnCastFinished, owner, getCSpellId());
       */
//}

//void Entity::creceive_cast_failed() {
	/*
       setCCasting(false);
       if (COnCastFailed != null) {
       DELEGATE_INVOKE(COnCastFailed, getCSpellId());
       }
       if (COnCastEnded != null) {
       DELEGATE_INVOKE(COnCastEnded, getCSpellId());
       }
       DELEGATE_INVOKE(SpellMgr::COnCastFailed, owner, getCSpellId());
       */
//}

//void Entity::on_cast_state_change() {
	/*
       if (getCCasting()) {
       SpellMgr::COnCastStateChanged(owner, getCSpellId());
       }*/
//}

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

void Entity::sdelay_cast()  {
	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_before_cast(_s_spell_cast_info);
	}

	emit_signal("scast_delayed", _s_spell_cast_info);
}

void Entity::sfinish_cast()  {

	for (int i = 0; i < _s_auras->size(); ++i) {
		Ref<AuraData> ad = _s_auras->get(i);

		ad->get_aura()->son_cast_finished(_s_spell_cast_info);
	}

	_s_spell_cast_info->get_spell()->casting_finished(_s_spell_cast_info);

	emit_signal("scast_finished", _s_spell_cast_info);

	_s_spell_cast_info = Ref<SpellCastInfo>(NULL);

	cfinish_cast();
}

void Entity::sinterrupt_cast()  {
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

//void Entity::sstart_casting(int PspellId, float PcastTime, float scale) {
	/*
       Spell *spell = Spells::Instance->GetData(PspellId);
       StartCasting(spell, PspellId, PcastTime, scale);
       */
//}

//void Entity::sstart_casting(Spell *spell, int PspellId, float PcastTime, float spellScale) {
	/*
       animReduction = (float)0;
       if (BSSettings::Getinstance()->AnimStopEnabled) {
       animReduction = BSSettings::Getinstance()->GetBSTestAnimStopDataForClass(owner->PlayerData->ClassId)->Value;
       PcastTime -= animReduction;
       }
       setSSpellId(PspellId);
       setSCastTime(PcastTime);
       setSSpellScale(spellScale);
       setSCasting(true);
       setSCurrentCastTime((float)0);
       setCSpellId(PspellId);
       setCSpellName(spell->SpellName);
       setCCastTime(PcastTime);
       setCCasting(true);
       setCCurrentCastTime((float)0);
       if (CxNet::IsServer) {
       SSendStartCasting(getSSpellId(), PcastTime);
       }*/
//}

//void Entity::sstart_casting(int PspellId, String PspellName, float PcastTime, float spellScale) {
	/*
       animReduction = (float)0;
       if (BSSettings::Getinstance()->AnimStopEnabled) {
       animReduction = BSSettings::Getinstance()->GetBSTestAnimStopDataForClass(owner->PlayerData->ClassId)->Value;
       PcastTime -= animReduction;
       }
       setSSpellId(PspellId);
       setSCastTime(PcastTime);
       setSSpellScale(spellScale);
       setSCasting(true);
       setSCurrentCastTime((float)0);
       setCSpellId(PspellId);
       setCSpellName(PspellName);
       setCCastTime(PcastTime);
       setCCasting(true);
       setCCurrentCastTime((float)0);
       if (CxNet::IsServer) {
       SSendStartCasting(getSSpellId(), PcastTime);
       }*/
//}


void Entity::start_animation_time(float time) {
	/*
       setSSpellId(-1);
       setSCastTime(time);
       setSSpellScale((float)0);
       setSCasting(true);
       setSCurrentCastTime((float)0);
       setCSpellId(-1);
       setCSpellName(new String(""));
       setCCastTime(time);
       setCCasting(true);
       setCCurrentCastTime((float)0);
       */
}

void Entity::scast_finished() {
	/*
       setSCasting(false);
       if (CxNet::IsServer) {
       if (getSSpellId() == -1) {
       return;
       }
       int spellId = getSSpellId();
       SpellMgr::CastingFinished(owner, getSSpellId(), getSSpellScale());
       SSendCastFinished(spellId);
       }*/
}

void Entity::ccast_finished() {
	//setCCasting(false);
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

void Entity::on_state_changed(PlayerStates newState) {
	/*
       if (getSSpellId() == -1) {
       setSCasting(false);
       return;
       }
       if (getCSpellId() == -1) {
       setCCasting(false);
       return;
       }
       if ((newState != PlayerStates::STATE_NORMAL) && getCCasting()) {
       DELEGATE_INVOKE(SpellMgr::COnCastFailed, owner, getCSpellId());
       }*/
}



//void Entity::Set(bool casting, int spellId, float currentCastTime, float castTime, String spellName, float spellScale, int _s_targetGUID, int sSpellCastGameObjectGUID) {

/*
   setSCasting(casting);
   setSSpellId(spellId);
   setSCurrentCastTime(currentCastTime);
   setSCastTime(castTime);
   setCSpellName(spellName);
   setSSpellScale(spellScale);
   _s_targetGUID = _s_targetGUID;
   sSpellCastGameObjectGUID = sSpellCastGameObjectGUID;
   */
//}

void Entity::son_death() {
}

void Entity::just_remove_aura(int auraId) {
	/*
       if (!owner->isServer) {
       return;
       }
       for (int i = 0; i < serverAuras->Count; i += 1) {
       AuraData *auraData = serverAuras->GetData(i);
       if (auraData->AuraId == auraId) {
       serverAuras->RemoveAt(i);
       SSendAuraRemoved(auraData->AuraId);
       return;
       }
       }
       */
}

void Entity::remove_aura(Ref<AuraData> data) {
	for (int i = 0; i < _s_auras->size(); i++) {
		if (_s_auras->get(i) == data) {
			_s_auras->remove(i);
			break;
		}
	}

	for (int i = 0; i < _c_auras->size(); i++) {
		if (_c_auras->get(i) == data) {
			_c_auras->remove(i);
			break;
		}
	}

	emit_signal("saura_removed", data);
	emit_signal("caura_removed", data);
}

void Entity::add_aura(Ref<AuraData> data) {
	son_before_aura_applied(data);

	data->set_owner(this);

	_s_auras->push_back(data);
	_c_auras->push_back(data);

	son_after_aura_applied(data);

	emit_signal("saura_added", data);
	emit_signal("caura_added", data);
}

void Entity::remove_auras_with_group(int auraGroup) {
	/*
       if (!owner->isServer) {
       return;
       }
       SpellMgr::RemoveAurasWithGroup(this, auraGroup);
       */
}

void Entity::refresh_aura(int auraId, float time) {
	/*
       if (!owner->isServer) {
       return;
       }
       for (int i = 0; i < serverAuras->Count; i += 1) {
       if (serverAuras->GetData(i)->AuraId == auraId) {
       serverAuras->GetData(i)->Refresh(time);
       SSendRefreshAura(auraId, time);
       }
       }*/
}

void Entity::refresh_aura(int auraId, Entity *caster, float time) {
	/*
       if (!owner->isServer) {
       return;
       }
       for (int i = 0; i < serverAuras->Count; i += 1) {
       if ((serverAuras->GetData(i)->AuraId == auraId) && (serverAuras->GetData(i)->Caster == *caster)) {
       serverAuras->GetData(i)->Refresh(time);
       SSendRefreshCasterAura(auraId, caster, time);
       }
       }*/
}

void Entity::ssend_refresh_aura(int auraId, float time) {
	/*
       if (CxNet::IsServer) {
       CRefreshAuraMsg cRefreshAuraMsg = CRefreshAuraMsg();
       cRefreshAuraMsg.Guid = owner->PlayerData->GUID;
       cRefreshAuraMsg.AuraId = auraId;
       cRefreshAuraMsg.Time = time;
       cRefreshAuraMsg.Serialize(CxNet::NetBuffer);
       CxNet::SendBufferToAllClients(0);
       }
       */
}

void Entity::ssend_refresh_caster_aura(int auraId, Entity *caster, float time) {
	/*
       if (CxNet::IsServer) {
       CRefreshCasterAuraMsg cRefreshCasterAuraMsg = CRefreshCasterAuraMsg();
       cRefreshCasterAuraMsg.Guid = owner->PlayerData->GUID;
       cRefreshCasterAuraMsg.CasterGuid = (Entity *)(caster)->PlayerData->GUID;
       cRefreshCasterAuraMsg.AuraId = auraId;
       cRefreshCasterAuraMsg.Time = time;
       cRefreshCasterAuraMsg.Serialize(CxNet::NetBuffer);
       CxNet::SendBufferToAllClients(0);
       }*/
}

void Entity::ssend_aura_added(int auraId, float time, Entity *caster) {
	/*
       if (CxNet::IsServer) {
       CAuraAddedMsg cAuraAddedMsg = CAuraAddedMsg();
       cAuraAddedMsg.Guid = owner->PlayerData->GUID;
       cAuraAddedMsg.CasterGuid = (Entity *)(caster)->PlayerData->GUID;
       cAuraAddedMsg.AuraId = auraId;
       cAuraAddedMsg.Time = time;
       cAuraAddedMsg.Serialize(CxNet::NetBuffer);
       CxNet::SendBufferToAllClients(0);
       }*/
}

void Entity::ssend_aura_removed(int auraId) {
	/*
       if (CxNet::IsServer) {
       CAuraRemovedMsg cAuraRemovedMsg = CAuraRemovedMsg();
       cAuraRemovedMsg.Guid = owner->PlayerData->GUID;
       cAuraRemovedMsg.AuraId = auraId;
       cAuraRemovedMsg.Serialize(CxNet::NetBuffer);
       CxNet::SendBufferToAllClients(0);
       }*/
}

void Entity::creceive_refresh_aura(int auraId, float time) {
	//SpellMgr::CRefreshAura(this, auraId, time);
}

void Entity::creceive_refresh_caster_aura(int auraId, Entity *caster, float time) {
	//SpellMgr::CRefreshCasterAura(this, auraId, caster, time);
}

void Entity::creceive_aura_added(int id, float remaining, Entity *caster) {
	//SpellMgr::CAuraAdded(this, id, remaining, caster, owner->PlayerData->GUID);
}

void Entity::creceive_aura_removed(int id) {
	//SpellMgr::CAuraRemoved(this, id);
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

int Entity::get_starget_guid() {
	return _s_target_guid;
}

void Entity::set_starget_guid(int value) {
	_s_target_guid = value;
}

void Entity::set_target(Entity *t) {
	/*
       if (_c_target == *t) {
       return;
       }
       _c_target = t;
       if (OnTargetChange != null) {
       DELEGATE_INVOKE(OnTargetChange, t);
       }
       if (CxNet::IsClient) {
       CSendTarget();
       }*/
}

void Entity::sbroadcast_target_change() {
	/*
       STargetChangedMsg _s_targetChangedMsg = STargetChangedMsg();
       _s_targetChangedMsg.Guid = owner->PlayerData->GUID;
       if (getSTarget() != null) {
       _s_targetChangedMsg.TargetGuid = getSTarget()->PlayerData->GUID;
       }
       _s_targetChangedMsg.Serialize(CxNet::NetBuffer);
       CxNet::SendBufferToAllClientsExcept(owner->Connection, 0);
       */
}

void Entity::csend_target() {
	/*
       CTargetChangedMsg _c_targetChangedMsg = CTargetChangedMsg();
       _c_targetChangedMsg.Guid = owner->PlayerData->GUID;
       if (getCTarget() != null) {
       _c_targetChangedMsg.TargetGuid = getCTarget()->PlayerData->GUID;
       }
       _c_targetChangedMsg.Serialize(CxNet::NetBuffer);
       CxNet::SendBufferToServer(0);
       */
}

void Entity::sreceive_ctarget_change(Entity *t) {
	/*
       _s_target = t;
       if (t != null) {
       _s_targetGUID = t->getPlayerData()->GUID;
       } else {
       _s_targetGUID = 0u;
       }
       if (SOnTargetChange != null) {
       DELEGATE_INVOKE(SOnTargetChange, t);
       }
       */
}

void Entity::ai_set_target(Entity *t) {
	/*
       if (_c_target == *t) {
       return;
       }
       _c_target = t;
       if (OnTargetChange != null) {
       DELEGATE_INVOKE(OnTargetChange, t);
       }
       _s_target = t;
       if (SOnTargetChange != null) {
       DELEGATE_INVOKE(SOnTargetChange, t);
       }
       CSendTarget();
       */
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

////    PlayerSpellDataComponent    ////

/*
   Vector<PlayerSpellData> *Entity::getSSpellData() {
   return sSpellData;
   }

   Vector<PlayerSpellData> *Entity::getCSpellData() {
   return cSpellData;
   }
   Dictionary_T<int, PlayerLocalSpellData> *Entity::getLocalSpellData() {
   return localSpellData;
   }

   bool Entity::getSend() {
   return send;
   }

   void Entity::setSend(bool value) {
   send = value;
   }*/

//void Entity::AddSSpellData(PlayerSpellData *psd) {
/*
   sSpellData->Add(psd);
   if (owner->isServer && is_inst_of<PlayerSpellCooldownData *>(psd)) {
   PlayerSpellCooldownData *playerSpellCooldownData = as_cast<PlayerSpellCooldownData *>(psd);
   SSendAddCPlayerSpellCooldownData(playerSpellCooldownData->SpellId, playerSpellCooldownData->getCooldown(), playerSpellCooldownData->getRemainingCooldown());
   }*/
//}

//void Entity::AddCSpellData(PlayerSpellData *psd) {
/*
   cSpellData->Add(psd);
   if (COnSpellDataAdded != null) {
   DELEGATE_INVOKE(COnSpellDataAdded, psd);
   }*/
//}

//void Entity::RemoveSSpellData(PlayerSpellData *psd) {
/*
   for (int i = 0; i < sSpellData->Count; i += 1) {
   if (*(sSpellData->GetData(i)) == *psd) {
   sSpellData->RemoveAt(i);
   break;
   }
   }
   if (owner->isServer && is_inst_of<PlayerSpellCooldownData *>(psd)) {
   SSendRemoveCPlayerSpellCooldownData(psd->getSpellId());
   }*/
//}

//void Entity::SSendAddCPlayerSpellCooldownData(int spellId, float cooldown, float remainingCooldown) {
/*
   if (CxNet::IsServer && (owner->Connection != null)) {
   AddCPlayerSpellCooldownDataMsg addCPlayerSpellCooldownDataMsg = AddCPlayerSpellCooldownDataMsg();
   addCPlayerSpellCooldownDataMsg.SpellId = spellId;
   addCPlayerSpellCooldownDataMsg.Cooldown = cooldown;
   addCPlayerSpellCooldownDataMsg.RemainingCooldown = remainingCooldown;
   addCPlayerSpellCooldownDataMsg.Serialize(CxNet::NetBuffer);
   owner->Connection->SendBuffer(0, CxNet::NetBuffer);
   }*/
//}

void Entity::ssend_remove_cplayer_spell_cooldown_data(int spellId) {
	/*
       if (CxNet::IsServer && (owner->Connection != null)) {
       RemoveCPlayerSpellCooldownDataMsg removeCPlayerSpellCooldownDataMsg = RemoveCPlayerSpellCooldownDataMsg();
       removeCPlayerSpellCooldownDataMsg.SpellId = spellId;
       removeCPlayerSpellCooldownDataMsg.Serialize(CxNet::NetBuffer);
       owner->Connection->SendBuffer(0, CxNet::NetBuffer);
       }*/
}
void Entity::creceive_add_cplayer_spell_cooldown_data(int spellId, float cooldown, float remainingCooldown) {
	//AddCSpellData(new PlayerSpellCooldownData(spellId, cooldown, remainingCooldown));
}

void Entity::creceive_remove_cplayer_spell_cooldown_data(int spellId) {
	//RemoveCSpellData(spellId, /*ERROR: Cannot translate: System.NotImplementedException: typeOfExpression: --> TODO: --> http://www.boost.org/doc/libs/1_55_0/doc/html/typeof/tuto.html. Node: ICSharpCode.NRefactory.CSharp.TypeOfExpression*/);
}

//void Entity::RemoveCSpellData(int spellId, Type *type) {
/*
   PlayerSpellData *playerSpellData = null;
   for (int i = 0; i < cSpellData->Count; i += 1) {
   if ((cSpellData->GetData(i)->SpellId == spellId) && (cSpellData->GetData(i)->GetType() == *type)) {
   playerSpellData = cSpellData->GetData(i);
   cSpellData->RemoveAt(i);
   break;
   }
   }
   if ((COnSpellDataRemoved != null) && (playerSpellData != null)) {
   DELEGATE_INVOKE(COnSpellDataRemoved, playerSpellData);
   }*/
//}

////    Inventory    ////

Vector<ItemInstance *> *Entity::get_sinventory() {
	return _s_inventory;
}

Vector<ItemInstance *> *Entity::get_cinventory() {
	return _c_inventory;
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
	update_auras(delta);
	
	if (_s_spell_cast_info.is_valid() && _s_spell_cast_info->get_is_casting() ) {
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

void Entity::LateUpdate() {
	/*
       playerResourceComponent->LateUpdate();
       getStats()->LateUpdate();*/
}

String Entity::request_spell_name(int spellId) {
	return "";
}

String Entity::request_spell_description(int spellId, int level) {
	return "";
}

/*
   void Entity::AddGraphicScripts() {
   if (BrokenSeals::GraphicType == BrokenSealsPlayerGraphicType::Sprites) {
   Entity::gameObject->AddComponent<PlayerGraphicBuilder>()->characterGraphicPrefab = characterGraphicPrefab;
   Entity::gameObject->AddComponent<CharacterEffectPointGetter>();
   return;
   }
   if (BrokenSeals::GraphicType == BrokenSealsPlayerGraphicType::Test) {
   GameObject *gameObject = new GameObject(new String("Container"));
   gameObject->transform->SetParent(Entity::gameObject->transform);
   gameObject->transform->localPosition = new Vector3((float)0, (float)1.1, (float)0.4);
   gameObject->transform->localRotation = Quaternion::Euler((float)30, (float)-45, (float)0);
   GameObject *expr_BE = UnityEngine::Object::Instantiate<GameObject>(testCharacterGraphicPrefab, new Vector3((float)0, (float)0, (float)0), Quaternion::identity, gameObject->transform);
   expr_BE->transform->localPosition = new Vector3((float)0, (float)0, (float)0);
   expr_BE->transform->localRotation = Quaternion::identity;
   Entity::gameObject->AddComponent<SimpleCharacterEffectPointGetter>();
   return;
   }
   if (BrokenSeals::GraphicType == BrokenSealsPlayerGraphicType::Voxel) {
   ModelMaker *expr_10C = Entity::gameObject->AddComponent<ModelMaker>();
   expr_10C->malePrefab = malePrefab;
   expr_10C->femalePrefab = femalePrefab;
   expr_10C->outlineMaterial = outlineMaterial;
   expr_10C->useOutline = useOutline;
   expr_10C->generateOnStart = generateOnStart;
   expr_10C->defaultGender = defaultGender;
   Entity::gameObject->AddComponent<VoxelCharacterEffectPointGetter>();
   }
   }

   GameObject *Entity::SEntitySpawn(EntityType type, int classId, int level, String name, int Guid, CxConnection *connection, bool owner, Vector3 *position, Quaternion *rotation) {
   if (Guid == 0u) {
   Guid = Entity::GetNextEntityGUID();
   }
   if (BrokenSeals::Instance->Networking) {
   return Entity::NetworkSpawnCharacter(Guid, type, classId, level, name, connection, owner, position, rotation);
   }
   return Entity::CEntitySpawn(Guid, type, classId, level, name, connection, owner, position, rotation);
   }

   GameObject *Entity::NetworkSpawnCharacter(int Guid, EntityType type, int classId, int level, String name, CxConnection *connection, bool owner, Vector3 *position, Quaternion *rotation) {
   SpawnCharacterMsg spawnCharacterMsg = SpawnCharacterMsg();
   spawnCharacterMsg.Guid = Guid;
   spawnCharacterMsg.ClassId = classId;
   spawnCharacterMsg.Type = type;
   spawnCharacterMsg.Name = name;
   spawnCharacterMsg.SpawnPosition = position;
   spawnCharacterMsg.SpawnRotation = rotation;
   spawnCharacterMsg.Serialize(CxNet::NetBuffer);
   if (connection == null) {
   spawnCharacterMsg.IsLocalPlayer = false;
   spawnCharacterMsg.Serialize(CxNet::NetBuffer);
   CxNet::SendBufferToAllClients(0);
   return Entity::CEntitySpawn(Guid, type, classId, level, name, connection, false, position, rotation);
   }
   spawnCharacterMsg.IsLocalPlayer = owner;
   spawnCharacterMsg.Serialize(CxNet::NetBuffer);
   CxNet::SendBufferToConnection(connection->ConnectionGUID, 0);
   spawnCharacterMsg.IsLocalPlayer = false;
   spawnCharacterMsg.Serialize(CxNet::NetBuffer);
   CxNet::SendBufferToAllClientsExcept(connection->ConnectionGUID, 0);
   if (connection->IsLocal) {
   return Entity::CEntitySpawn(Guid, type, classId, level, name, connection, true, position, rotation);
   }
   return Entity::CEntitySpawn(Guid, type, classId, level, name, connection, false, position, rotation);
   }

   GameObject *Entity::CEntitySpawn(int Guid, EntityType type, int classId, int level, String name, CxConnection *connection, bool owner, Vector3 *position, Quaternion *rotation) {
   if (!CharacterDataLoader::Instance->IsCharacterExists(classId)) {
   Debug::LogError(new String("Class doesn't exists!"));
   return null;
}
GameObject *gameObject = null;
if ((type == EntityType::Player) || (type == EntityType::Ai)) {
    gameObject = UnityEngine::Object::Instantiate<GameObject>(PrefabLoader::Instance->GetData(1)->Asset, position, rotation);
}
if (type == EntityType::Mob) {
    gameObject = UnityEngine::Object::Instantiate<GameObject>(PrefabLoader::Instance->GetData(2)->Asset, position, rotation);
}
Entity *component = gameObject->GetComponent<Entity>();
component->setConnection(connection);
component->type = type;
Character *arg_7C_0 = CharacterDataLoader::Instance->GetData(classId);
PlayerData *expr_83 = component->getPlayerData();
expr_83->setClassId(classId);
expr_83->setType((int)(type));
expr_83->setName(name);
component->gameObject->name = name;
expr_83->setLevel(level);
expr_83->setGUID(BrokenSeals::BSState->GameData->NextPlayerGUID);
expr_83->GetWeaponForClass();
expr_83->setGender(UnityEngine::Random::Range(0, 2));
component->isLocalPlayer = owner;
if (owner) {
    BSInputManager::GetInstance()->CharacterId = classId;
}
if (BrokenSeals::CameraType != BrokenSealsCameraType::MMO) {
    gameObject->gameObject->AddComponent<CharacterController>();
    if ((type == EntityType::Player) & owner) {
        gameObject->gameObject->AddComponent<PlayerController>();
    }
}
if (BSState::Instance->IsClient) {
    component->AddGraphicScripts();
}
if (BSState::Instance->IsClient & owner) {
    if (BrokenSeals::CameraType == BrokenSealsCameraType::Isometric) {
        GameObject::FindGameObjectWithTag(new String("MainCamera"))->AddComponent<IsometricCamera>();
    } else {
        if (BrokenSeals::CameraType == BrokenSealsCameraType::MMO) {
            GameObject::FindGameObjectWithTag(new String("MainCamera"))->GetComponent<Camera>()->orthographic = false;
            UnityEngine::Object::Destroy(gameObject->GetComponent<KinematicCharacterMotor>());
            UnityEngine::Object::Destroy(gameObject->GetComponent<CapsuleCollider>());
            gameObject->gameObject->AddComponent<RPGMotor>();
            gameObject->gameObject->AddComponent<RPGViewFrustum>();
            gameObject->gameObject->AddComponent<RPGCamera>();
            gameObject->gameObject->AddComponent<RPGController>();
            if (owner) {
                gameObject->gameObject->AddComponent<VoxelPlayerController>();
            }
            CharacterController *expr_1D1 = gameObject->GetComponent<CharacterController>();
            expr_1D1->radius = (float)0.3;
            expr_1D1->center = new Vector3((float)0, (float)0.8, (float)0);
            expr_1D1->height = (float)1.6;
        }
    }
    if (BrokenSeals::GraphicType == BrokenSealsPlayerGraphicType::Sprites) {
        gameObject->gameObject->AddComponent<LocalPlayerAnimationController>();
    } else {
        if (BrokenSeals::GraphicType == BrokenSealsPlayerGraphicType::Test) {
            gameObject->gameObject->AddComponent<SpriteAnimationController>();
        } else {
            if (BrokenSeals::GraphicType == BrokenSealsPlayerGraphicType::Voxel) {
                gameObject->gameObject->AddComponent<VoxelLocalPlayerAnimationController>();
            }
        }
    }
}
if (BSState::Instance->IsClient && !owner) {
    if (BrokenSeals::GraphicType == BrokenSealsPlayerGraphicType::Sprites) {
        gameObject->gameObject->AddComponent<NetworkedPlayerAnimationController>();
    } else {
        if (BrokenSeals::GraphicType == BrokenSealsPlayerGraphicType::Test) {
            gameObject->gameObject->AddComponent<SpriteAnimationController>();
        } else {
            if (BrokenSeals::GraphicType == BrokenSealsPlayerGraphicType::Voxel) {
                gameObject->gameObject->AddComponent<VoxelNetworkedPlayerAnimationController>();
            }
        }
    }
}
if (!owner) {
    UnityEngine::Object::Instantiate<GameObject>(PrefabLoader::Instance->GetData(3)->Asset, Vector3::zero, Quaternion::identity)->transform->SetParent(gameObject->transform);
}
if (BSState::Instance->IsServer) {
    PlayerData *arg_2D3_0 = component->getPlayerData();
    if (type == EntityType::Player) {
        component->getFactionComponent()->STeam = 3;
    }
    if (type == EntityType::Ai) {
        component->transform->name = component->getPlayerData()->Name;
    }
    if (BSState::Instance->IsServer && (type == EntityType::Mob)) {
        component->getFactionComponent()->STeam = 4;
        component->gameObject->AddComponent<AIComponent>();
        gameObject->transform->name = component->getPlayerData()->Name;
    }
}
component->components->Refresh(gameObject);
if (BSState::Instance->IsClient) {
    if (owner) {
        Entity::RegisterLocalPlayer(Guid, component);
    } else {
        if ((type == EntityType::Ai) || (type == EntityType::Mob)) {
            Entity::CRegisterAIPlayer(Guid, component);
        } else {
            Entity::CRegisterNetworkedPlayer(Guid, component);
        }
    }
}
if (BSState::Instance->IsServer) {
    if ((type == EntityType::Ai) || (type == EntityType::Mob)) {
        Entity::SRegisterAIPlayer(Guid, component);
    } else {
        Entity::SRegisterNetworkedPlayer(Guid, component);
    }
}
if (CxNet::IsServer) {
    EntityNetworkManager::getInstance()->OnSPlayerAdded(component);
}
if (CxNet::IsClient) {
    EntityNetworkManager::getInstance()->OnCPlayerAdded(component);
}
return gameObject;
}

void Entity::OnPlayerSpawneds(Entity *player, bool isClientPlayer, bool isServerPlayer, bool isLocalPlayerPlayer) {
    if (isClientPlayer | isLocalPlayerPlayer) {
        AddGraphicScripts();
    }
    if (isLocalPlayerPlayer) {
        if (BrokenSeals::CameraType == BrokenSealsCameraType::Isometric) {
            GameObject::FindGameObjectWithTag(new String("MainCamera"))->AddComponent<IsometricCamera>();
        } else {
            if (BrokenSeals::CameraType == BrokenSealsCameraType::MMO) {
                GameObject::FindGameObjectWithTag(new String("MainCamera"))->GetComponent<Camera>()->orthographic = false;
                UnityEngine::Object::Destroy(player->GetComponent<KinematicCharacterMotor>());
                UnityEngine::Object::Destroy(player->GetComponent<CapsuleCollider>());
                player->gameObject->AddComponent<RPGMotor>();
                player->gameObject->AddComponent<RPGViewFrustum>();
                player->gameObject->AddComponent<RPGCamera>();
                player->gameObject->AddComponent<RPGController>();
                player->gameObject->AddComponent<VoxelPlayerController>();
                CharacterController *expr_A7 = player->GetComponent<CharacterController>();
                expr_A7->radius = (float)0.3;
                expr_A7->center = new Vector3((float)0, (float)0.8, (float)0);
                expr_A7->height = (float)1.6;
            }
        }
        if (addGraphic) {
            if (BrokenSeals::GraphicType == BrokenSealsPlayerGraphicType::Sprites) {
                player->gameObject->AddComponent<LocalPlayerAnimationController>();
            } else {
                if (BrokenSeals::GraphicType == BrokenSealsPlayerGraphicType::Test) {
                    player->gameObject->AddComponent<SpriteAnimationController>();
                } else {
                    if (BrokenSeals::GraphicType == BrokenSealsPlayerGraphicType::Voxel) {
                        player->gameObject->AddComponent<VoxelLocalPlayerAnimationController>();
                        player->gameObject->AddComponent<VoxelPlayerController>();
                    }
                }
            }
        }
    }
    if ((isClientPlayer && !isLocalPlayerPlayer) && addGraphic) {
        if (BrokenSeals::GraphicType == BrokenSealsPlayerGraphicType::Sprites) {
            player->gameObject->AddComponent<NetworkedPlayerAnimationController>();
        } else {
            if (BrokenSeals::GraphicType == BrokenSealsPlayerGraphicType::Test) {
                player->gameObject->AddComponent<SpriteAnimationController>();
            } else {
                if (BrokenSeals::GraphicType == BrokenSealsPlayerGraphicType::Voxel) {
                    player->gameObject->AddComponent<VoxelNetworkedPlayerAnimationController>();
                }
            }
        }
    }
    if (!isLocalPlayerPlayer) {
        UnityEngine::Object::Instantiate<GameObject>(PrefabLoader::Instance->GetData(3)->Asset, Vector3::zero, Quaternion::identity)->transform->SetParent(player->transform);
    }
    if (isServerPlayer) {
        EntityType entityType = (EntityType)(player->getPlayerData()->Type);
        if (entityType == EntityType::Player) {
            player->getFactionComponent()->STeam = 3;
        }
        if (entityType == EntityType::Ai) {
            player->transform->name = player->getPlayerData()->Name;
        }
        if (isServerPlayer && (entityType == EntityType::Mob)) {
            player->gameObject->AddComponent<CharacterController>();
            player->getFactionComponent()->STeam = 4;
            player->gameObject->AddComponent<AIComponent>();
            player->transform->name = player->getPlayerData()->Name;
        }
    }
    components->Refresh(Entity::gameObject);
}
*/

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

//COnCastStartAction;
//CONCastEndedAction;
//CONCastFinishedAction;
//CONCastFailedAction;
//DELEGATE(void, PlayerSpellData *)
//CSpellDataRemovedAction;
//DELEGATE(void, PlayerSpellData *)
//CSpellDataAddedAction;
//void addCOnSpellDataRemoved(PlayerSpellDataComponent::CSpellDataRemovedAction *value);
//void removeCOnSpellDataRemoved(PlayerSpellDataComponent::CSpellDataRemovedAction *value);
//void addCOnSpellDataAdded(PlayerSpellDataComponent::CSpellDataAddedAction *value);
//void removeCOnSpellDataAdded(PlayerSpellDataComponent::CSpellDataAddedAction *value);
//void addOnCTalenChangedAction(TalentComponent::OnTalenChangedAction *value);
//void removeOnCTalenChangedAction(TalentComponent::OnTalenChangedAction *value);ű
//void addOnTargetChange(TargetComponent::targetChanged *value);
//void removeOnTargetChange(TargetComponent::targetChanged *value);
//void addSOnTargetChange(TargetComponent::sTargetChanged *value);
//void removeSOnTargetChange(TargetComponent::sTargetChanged *value);
//delegate void OnStateChangedAction(PlayerStates newState);
//event OnStateChangedAction OnStateChanged;
//delegate void OnLevelUpAction(Entity player);
//event OnLevelUpAction COnLevelUp;
//event OnLevelUpAction SOnLevelUp;
//delegate void OnLevelChangedAction(Entity player, int newLevel);
//event OnLevelChangedAction COnLevelChanged;
//event OnLevelChangedAction SOnLevelChanged;
//delegate void OnXPChangedAction(Entity player, int newXp);
//event OnXPChangedAction COnXPChanged;
//delegate void OnWeapomChangedAction(ItemData wd);
//event OnWeapomChangedAction OnWeaponChanged;
//delegate void StatDataRequestAction(StatData sdc);
//StatDataRequestAction statDataRequests;
//delegate void GameObjectDataRequestAction(GameObject go);
//GameObjectDataRequestAction gameObjectDataRequests;

//void addCOnCastStart(SpellCastData::COnCastStartAction *value);
//void removeCOnCastStart(SpellCastData::COnCastStartAction *value);
//void addCOnCastFinished(SpellCastData::CONCastFinishedAction *value);
//void removeCOnCastFinished(SpellCastData::CONCastFinishedAction *value);
//void addCOnCastEnded(SpellCastData::CONCastEndedAction *value);
//void removeCOnCastEnded(SpellCastData::CONCastEndedAction *value);
//void addCOnCastFailed(SpellCastData::CONCastFailedAction *value);
//void removeCOnCastFailed(SpellCastData::CONCastFailedAction *value);

//DELEGATE(void, ItemInstance *)
//InventoryAction;
//DELEGATE(void)
//ItemRemovedAction;
//DELEGATE(void)
//ItemMovedAction;
/*
	void addSOnItemAdded(Inventory::InventoryAction *value);
	void removeSOnItemAdded(Inventory::InventoryAction *value);
	void addCOnItemAdded(Inventory::InventoryAction *value);
	void removeCOnItemAdded(Inventory::InventoryAction *value);
	void addSOnItemCountChanged(Inventory::InventoryAction *value);
	void removeSOnItemCountChanged(Inventory::InventoryAction *value);
	void addCOnItemCountChanged(Inventory::InventoryAction *value);
	void removeCOnItemCountChanged(Inventory::InventoryAction *value);
	void addSOnItemRemoved(Inventory::ItemRemovedAction *value);
	void removeSOnItemRemoved(Inventory::ItemRemovedAction *value);
	void addCOnItemRemoved(Inventory::ItemRemovedAction *value);
	void removeCOnItemRemoved(Inventory::ItemRemovedAction *value);
	void addSOnItemMoved(Inventory::ItemMovedAction *value);
	void removeSOnItemMoved(Inventory::ItemMovedAction *value);
	void addCOnItemMoved(Inventory::ItemMovedAction *value);
	void removeCOnItemMoved(Inventory::ItemMovedAction *value);
	void addSOnCraftMaterialAdded(Inventory::InventoryAction *value);
	void removeSOnCraftMaterialAdded(Inventory::InventoryAction *value);
	void addCOnCraftMaterialAdded(Inventory::InventoryAction *value);
	void removeCOnCraftMaterialAdded(Inventory::InventoryAction *value);
	void addSOnCraftMaterialRemoved(Inventory::ItemRemovedAction *value);
	void removeSOnCraftMaterialRemoved(Inventory::ItemRemovedAction *value);
	void addCOnCraftMaterialRemoved(Inventory::ItemRemovedAction *value);
	void removeCOnCraftMaterialRemoved(Inventory::ItemRemovedAction *value);
	void addCOnCraftMaterialsLoaded(Inventory::ItemRemovedAction *value);
	void removeCOnCraftMaterialsLoaded(Inventory::ItemRemovedAction *value);
	void addCOnItemsLoaded(Inventory::ItemRemovedAction *value);
	void removeCOnItemsLoaded(Inventory::ItemRemovedAction *value);
	*/
/*
		DELEGATE(void) SOnDeathAction;
		DELEGATE(void) OnDeathAction;
		DELEGATE(void) SOnResurrectAction;
		DELEGATE(void) OnResurrectAction;
		DELEGATE(void, int, Stat*) OnStatChangeAction;
		DELEGATE(void, int, Stat*) SOnStatChangeAction;
		DELEGATE(void, int, bool, Entity*, Entity*) OnDamageTakenAction;
		DELEGATE(void, int, bool, Entity*, Entity*) OnHealTakenAction;
		*/

void Entity::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_ENTER_TREE: {
			if (!Engine::get_singleton()->is_editor_hint())
				set_process(true);
		} break;
		case NOTIFICATION_PROCESS: {
			update(get_process_delta_time());
		} break;
		case NOTIFICATION_EXIT_TREE: {
			
		} break;
	}
}

void Entity::_bind_methods() {
	ADD_SIGNAL(MethodInfo("starget_changed", PropertyInfo(Variant::OBJECT, "Entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	ADD_SIGNAL(MethodInfo("ctarget_changed", PropertyInfo(Variant::OBJECT, "Entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	ADD_SIGNAL(MethodInfo("son_damage_taken", PropertyInfo(Variant::OBJECT, "Entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "damage_pipeline_data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));
	ADD_SIGNAL(MethodInfo("con_damage_taken", PropertyInfo(Variant::OBJECT, "Entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "damage_pipeline_data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	ADD_SIGNAL(MethodInfo("con_damage_dealt", PropertyInfo(Variant::OBJECT, "Entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "damage_pipeline_data", PROPERTY_HINT_RESOURCE_TYPE, "SpellDamageInfo")));

	ADD_SIGNAL(MethodInfo("scharacter_class_changed", PropertyInfo(Variant::OBJECT, "Entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	ADD_SIGNAL(MethodInfo("ccharacter_class_changed", PropertyInfo(Variant::OBJECT, "Entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	ADD_SIGNAL(MethodInfo("saura_added", PropertyInfo(Variant::OBJECT, "aura_data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	ADD_SIGNAL(MethodInfo("caura_added", PropertyInfo(Variant::OBJECT, "aura_data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));

	ADD_SIGNAL(MethodInfo("saura_removed", PropertyInfo(Variant::OBJECT, "aura_data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));
	ADD_SIGNAL(MethodInfo("caura_removed", PropertyInfo(Variant::OBJECT, "aura_data", PROPERTY_HINT_RESOURCE_TYPE, "AuraData")));


	////    SpellCastSignals    ////
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

	////    Targeting System    ////

	ClassDB::bind_method(D_METHOD("gets_target"), &Entity::gets_target);
	ClassDB::bind_method(D_METHOD("sets_target", "target"), &Entity::sets_target);

	ClassDB::bind_method(D_METHOD("getc_target"), &Entity::getc_target);
	ClassDB::bind_method(D_METHOD("setc_target", "target"), &Entity::setc_target);

	////    Spell System    ////
	ClassDB::bind_method(D_METHOD("scast_spell", "spell_id"), &Entity::scast_spell);
	ClassDB::bind_method(D_METHOD("crequest_spell_cast", "spell_id"), &Entity::crequest_spell_cast);
	ClassDB::bind_method(D_METHOD("add_aura", "aura"), &Entity::add_aura);

	ClassDB::bind_method(D_METHOD("stake_damage", "data"), &Entity::stake_damage);
	ClassDB::bind_method(D_METHOD("son_damage_dealt", "data"), &Entity::son_damage_dealt);
	ClassDB::bind_method(D_METHOD("sdeal_damage_to", "data"), &Entity::sdeal_damage_to);
}
