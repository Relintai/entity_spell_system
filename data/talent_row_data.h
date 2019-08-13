#ifndef TALENT_ROW_DATA_H
#define TALENT_ROW_DATA_H

#include "core/reference.h"
#include "core/ustring.h"

#include "talent.h"

class Talent;

class TalentRowData : public Resource {
	GDCLASS(TalentRowData, Resource);

public:
	Ref<Talent> get_talent(int index) const;
	void set_talent(int index, Ref<Talent> talent);

	TalentRowData();
	~TalentRowData();

public:
	enum {
		MAX_TALENTS_IN_ROW = 5,
	};

protected:
	static void _bind_methods();

private:
	Ref<Talent> _talents[MAX_TALENTS_IN_ROW];
};

#endif
