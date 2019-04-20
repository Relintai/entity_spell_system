#ifndef TALENT_H
#define TALENT_H

#include "core/resource.h"
#include "core/ustring.h"

#include "../entities/stats/stat.h"
#include "aura.h"
#include "talent_rank_data.h"

class TalentRankData;
class Aura;

class Talent : public Resource {
	GDCLASS(Talent, Resource);

public:
	int get_id();
	void set_id(int value);

	String get_talent_name();
	void set_talent_name(String value);

	String get_description();
	void set_description(String value);

	Ref<TalentRankData> get_rank_data(int index);

	int get_max_rank();
	void set_max_rank(int value);

	Stat::StatId get_talent_stat_attribute_stat(int index) const;
	void set_talent_stat_attribute_stat(int index, const Stat::StatId value);

	float get_talent_stat_attribute_base_mod(int index) const;
	void set_talent_stat_attribute_base_mod(int index, float value);

	float get_talent_stat_attribute_bonus_mod(int index) const;
	void set_talent_stat_attribute_bonus_mod(int index, float value);

	float get_talent_stat_attribute_percent_mod(int index) const;
	void set_talent_stat_attribute_percent_mod(int index, float value);

	Ref<Aura> get_talent_aura(int index) const;
	void set_talent_aura(int index, Ref<Aura> value);

	Talent();
	~Talent();

protected:
	static void _bind_methods();
	void _validate_property(PropertyInfo &property) const;

private:
	enum {
		MAX_RANKS = 5,
	};

	int _id;
	String _talent_name;
	String _description;

	int _max_rank;
	Ref<TalentRankData> _ranks[MAX_RANKS];
};

#endif
