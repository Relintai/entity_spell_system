#ifndef CHARACTER_SPEC_H
#define CHARACTER_SPEC_H

#include "core/resource.h"
#include "core/ustring.h"

#include "talent_row_data.h"

class TalentRowData;
class Talent;

class CharacterSpec : public Resource {
	GDCLASS(CharacterSpec, Resource);

public:
	int get_spec_id();
	void set_spec_id(int value);
	String get_spec_name();
	void set_spec_name(String value);

	Ref<TalentRowData> get_talent_row(int index) const;

	Ref<Talent> get_talent0_in_row(int index) const;
	void set_talent0_in_row(int index, Ref<Talent> talent);

	Ref<Talent> get_talent1_in_row(int index) const;
	void set_talent1_in_row(int index, Ref<Talent> talent);

	Ref<Talent> get_talent2_in_row(int index) const;
	void set_talent2_in_row(int index, Ref<Talent> talent);

	Ref<Talent> get_talent3_in_row(int index) const;
	void set_talent3_in_row(int index, Ref<Talent> talent);

	Ref<Talent> get_talent4_in_row(int index) const;
	void set_talent4_in_row(int index, Ref<Talent> talent);

	CharacterSpec();
	~CharacterSpec();

protected:
	static void _bind_methods();

private:
	enum {
		MAX_TALENT_ROWS = 10,
	};

	int _spec_id;
	String _spec_name;
	Ref<TalentRowData> _rows[MAX_TALENT_ROWS];
};

#endif
