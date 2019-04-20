#ifndef TALENT_ROW_DATA_H
#define TALENT_ROW_DATA_H

#include "core/reference.h"
#include "core/ustring.h"

#include "talent.h"

class Talent;

class TalentRowData : public Reference {
	GDCLASS(TalentRowData, Reference);

public:
	Ref<Talent> get_talent(int index) const;
	void set_talent(int index, Ref<Talent> talent);

	Ref<Talent> get_talent0() const;
	void set_talent0(Ref<Talent> talent);

	Ref<Talent> get_talent1() const;
	void set_talent1(Ref<Talent> talent);

	Ref<Talent> get_talent2() const;
	void set_talent2(Ref<Talent> talent);

	Ref<Talent> get_talent3() const;
	void set_talent3(Ref<Talent> talent);

	Ref<Talent> get_talent4() const;
	void set_talent4(Ref<Talent> talent);

	TalentRowData() {
		for (int i = 0; i < MAX_TALENTS_IN_ROW; ++i) {
			_talents[i] = Ref<Talent>(NULL);
		}
	}

protected:
	static void _bind_methods();

private:
	enum {
		MAX_TALENTS_IN_ROW = 5,
	};

	Ref<Talent> _talents[MAX_TALENTS_IN_ROW];
};

#endif
