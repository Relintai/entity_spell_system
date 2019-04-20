#include "talent.h"

int Talent::get_id(){
	return _id;
}

void Talent::set_id(int value)
{
	_id = value;
}


Ref<TalentRankData> Talent::get_rank_data(int index)
{
	return _ranks[index];
}

String Talent::get_talent_name()
{
	return _talent_name;
}

void Talent::set_talent_name(String value)
{
	_talent_name = value;
}

String Talent::get_description()
{
	return _description;
}

void Talent::set_description(String value)
{
	_description = value;
}


int Talent::get_max_rank()
{
	return _max_rank;
}

void Talent::set_max_rank(int value)
{
	_max_rank = value;
}

Stat::StatId Talent::get_talent_stat_attribute_stat(int index) const {
	ERR_FAIL_INDEX_V(index, MAX_RANKS, Stat::STAT_ID_NONE);

	return _ranks[index]->get_stat();
}
void Talent::set_talent_stat_attribute_stat(int index, const Stat::StatId value) {
	ERR_FAIL_INDEX(index, MAX_RANKS);

	_ranks[index]->set_stat(value);
}

float Talent::get_talent_stat_attribute_base_mod(int index) const {
	ERR_FAIL_INDEX_V(index, MAX_RANKS, 0);

	return _ranks[index]->get_base_mod();
}
void Talent::set_talent_stat_attribute_base_mod(int index, float value) {
	ERR_FAIL_INDEX(index, MAX_RANKS);

	_ranks[index]->set_base_mod(value);
}

float Talent::get_talent_stat_attribute_bonus_mod(int index) const {
	ERR_FAIL_INDEX_V(index, MAX_RANKS, 0);

	return _ranks[index]->get_bonus_mod();
}

void Talent::set_talent_stat_attribute_bonus_mod(int index, float value) {
	ERR_FAIL_INDEX(index, MAX_RANKS);

	_ranks[index]->set_bonus_mod(value);
}

float Talent::get_talent_stat_attribute_percent_mod(int index) const {
	ERR_FAIL_INDEX_V(index, MAX_RANKS, 0);

	return _ranks[index]->get_percent_mod();
}

void Talent::set_talent_stat_attribute_percent_mod(int index, float value) {
	ERR_FAIL_INDEX(index, MAX_RANKS);

	_ranks[index]->set_percent_mod(value);
}

Ref<Aura> Talent::get_talent_aura(int index) const {
	ERR_FAIL_INDEX_V(index, MAX_RANKS, 0);

	return _ranks[index]->get_aura();
}

void Talent::set_talent_aura(int index, Ref<Aura> value) {
	ERR_FAIL_INDEX(index, MAX_RANKS);

	_ranks[index]->set_aura(value);
}

Talent::Talent()
{
	for (int i = 0; i < MAX_RANKS; ++i)
	{
		_ranks[i] = Ref<TalentRankData>(memnew(TalentRankData()));
	}

	_id = 0;
	_talent_name = "";
    _description = "";

    _max_rank = 0;
}

Talent::~Talent()
{
}

void Talent::_validate_property(PropertyInfo &property) const {

	String prop = property.name;
	if (prop.begins_with("TalentRank_")) {
		int frame = prop.get_slicec('/', 0).get_slicec('_', 1).to_int();
		if (frame >= _max_rank) {
			property.usage = 0;
		}
	}
}


void Talent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_id"), &Talent::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &Talent::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ClassDB::bind_method(D_METHOD("get_talent_name"), &Talent::get_talent_name);
	ClassDB::bind_method(D_METHOD("set_talent_name", "value"), &Talent::set_talent_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "talent_name"), "set_talent_name", "get_talent_name");

	ClassDB::bind_method(D_METHOD("get_description"), &Talent::get_description);
	ClassDB::bind_method(D_METHOD("set_description", "value"), &Talent::set_description);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "description"), "set_description", "get_description");

	////    Ranks    ////
	ADD_GROUP("Rank", "rank");
	ClassDB::bind_method(D_METHOD("get_max_rank"), &Talent::get_max_rank);
	ClassDB::bind_method(D_METHOD("set_max_rank", "value"), &Talent::set_max_rank);

	ClassDB::bind_method(D_METHOD("get_talent_stat_attribute_stat", "index"), &Talent::get_talent_stat_attribute_stat);
	ClassDB::bind_method(D_METHOD("set_talent_stat_attribute_stat", "index", "value"), &Talent::set_talent_stat_attribute_stat);

	ClassDB::bind_method(D_METHOD("get_talent_stat_attribute_base_mod", "index"), &Talent::get_talent_stat_attribute_base_mod);
	ClassDB::bind_method(D_METHOD("set_talent_stat_attribute_base_mod", "index", "value"), &Talent::set_talent_stat_attribute_base_mod);

	ClassDB::bind_method(D_METHOD("get_talent_stat_attribute_bonus_mod", "index"), &Talent::get_talent_stat_attribute_bonus_mod);
	ClassDB::bind_method(D_METHOD("set_talent_stat_attribute_bonus_mod", "index", "value"), &Talent::set_talent_stat_attribute_bonus_mod);

	ClassDB::bind_method(D_METHOD("get_talent_stat_attribute_percent_mod", "index"), &Talent::get_talent_stat_attribute_percent_mod);
	ClassDB::bind_method(D_METHOD("set_talent_stat_attribute_percent_mod", "index", "value"), &Talent::set_talent_stat_attribute_percent_mod);

	ClassDB::bind_method(D_METHOD("get_talent_aura", "index"), &Talent::get_talent_aura);
	ClassDB::bind_method(D_METHOD("set_talent_aura", "index", "value"), &Talent::set_talent_aura);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "max_rank", PROPERTY_HINT_RANGE, "0," + itos(MAX_RANKS), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_max_rank", "get_max_rank");

	for (int i = 0; i < MAX_RANKS; ++i) {
		ADD_PROPERTYI(PropertyInfo(Variant::INT, "TalentRank_" + itos(i) + "/stat", PROPERTY_HINT_ENUM, Stat::STAT_BINDING_STRING, PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_talent_stat_attribute_stat", "get_talent_stat_attribute_stat", i);

		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "TalentRank_" + itos(i) + "/base_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_talent_stat_attribute_base_mod", "get_talent_stat_attribute_base_mod", i);

		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "TalentRank_" + itos(i) + "/bonus_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_talent_stat_attribute_bonus_mod", "get_talent_stat_attribute_bonus_mod", i);

		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "TalentRank_" + itos(i) + "/percent_mod", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_talent_stat_attribute_percent_mod", "get_talent_stat_attribute_percent_mod", i);

		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "TalentRank_" + itos(i) + "/aura", PROPERTY_HINT_RESOURCE_TYPE, "Aura", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_talent_aura", "get_talent_aura", i);
	}

	ClassDB::bind_method(D_METHOD("get_rank_data", "index"), &Talent::get_rank_data);

	BIND_CONSTANT(MAX_RANKS);
}
