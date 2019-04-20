#ifndef TALENT_RANK_DATA_H
#define TALENT_RANK_DATA_H

#include "core/ustring.h"
#include "core/reference.h"

#include "../entities/stats/stat.h"
#include "aura.h"

class Aura;

class TalentRankData : public Reference
{
	GDCLASS(TalentRankData, Reference);

public:
	Stat::StatId get_stat() const { return _stat; }
	void set_stat(Stat::StatId value) { _stat = value; }

	float get_base_mod() const { return _base_mod; }
	void set_base_mod(float value) { _base_mod = value; }

	float get_bonus_mod() const { return _bonus_mod; }
	void set_bonus_mod(float value) { _bonus_mod = value; }

	float get_percent_mod() const { return _percent_mod; }
	void set_percent_mod(float value) { _percent_mod = value; }

    Ref<Aura> get_aura() const { return _aura; }
    void set_aura (Ref<Aura> aura) { _aura = Ref<Aura>(aura); }

	TalentRankData() {
		_stat = Stat::STAT_ID_NONE;
		_base_mod = 0;
		_bonus_mod = 0;
		_percent_mod = 0;
	}

	~TalentRankData() {
	}

protected:
    static void _bind_methods() {
		ClassDB::bind_method(D_METHOD("get_stat"), &TalentRankData::get_stat);
		ClassDB::bind_method(D_METHOD("set_stat", "value"), &TalentRankData::set_stat);
		ADD_PROPERTY(PropertyInfo(Variant::INT, "stat", PROPERTY_HINT_ENUM, Stat::STAT_BINDING_STRING), "set_stat", "get_stat");

		ClassDB::bind_method(D_METHOD("get_base_mod"), &TalentRankData::get_base_mod);
		ClassDB::bind_method(D_METHOD("set_base_mod", "value"), &TalentRankData::set_base_mod);
		ADD_PROPERTY(PropertyInfo(Variant::REAL, "base_mod"), "set_base_mod", "get_base_mod");

		ClassDB::bind_method(D_METHOD("get_bonus_mod"), &TalentRankData::get_bonus_mod);
		ClassDB::bind_method(D_METHOD("set_bonus_mod", "value"), &TalentRankData::set_bonus_mod);
		ADD_PROPERTY(PropertyInfo(Variant::REAL, "bonus_mod"), "set_bonus_mod", "get_bonus_mod");

		ClassDB::bind_method(D_METHOD("get_percent_mod"), &TalentRankData::get_percent_mod);
		ClassDB::bind_method(D_METHOD("set_percent_mod", "value"), &TalentRankData::set_percent_mod);
		ADD_PROPERTY(PropertyInfo(Variant::REAL, "percent_mod"), "set_percent_mod", "get_percent_mod");

		ClassDB::bind_method(D_METHOD("get_aura"), &TalentRankData::get_aura);
		ClassDB::bind_method(D_METHOD("set_aura", "value"), &TalentRankData::set_aura);
		ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura", PROPERTY_HINT_RESOURCE_TYPE, "Aura"), "set_aura", "get_aura");
	}

private:
	Stat::StatId _stat;
	float _base_mod;
	float _bonus_mod;
	float _percent_mod;
    Ref<Aura>_aura;

};

#endif
