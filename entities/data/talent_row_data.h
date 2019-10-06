#ifndef TALENT_ROW_DATA_H
#define TALENT_ROW_DATA_H

#include "core/reference.h"
#include "core/ustring.h"

#include "../../data/aura.h"

class Aura;

class TalentRowData : public Resource {
	GDCLASS(TalentRowData, Resource);

public:
	Ref<Aura> get_talent_index(int index) const;
	void set_talent_index(int index, Ref<Aura> talent);

	Ref<Aura> get_talent(int culomn, int rank) const;
	void set_talent(int culomn, int rank, Ref<Aura> talent);

	bool has_talent_with_id(int id);
	Ref<Aura> get_talent_with_id(int id);

	TalentRowData();
	~TalentRowData();

public:
	enum {
		MAX_TALENTS_IN_ROW = 5,
		MAX_TALENTS_PER_ENTRY = 5,
		TOTAL_ENTRIES = MAX_TALENTS_IN_ROW * MAX_TALENTS_PER_ENTRY,
	};

protected:
	static void _bind_methods();

private:
	Ref<Aura> _talents[TOTAL_ENTRIES];
};

#endif
