#ifndef ENTITY_SKILL_H
#define ENTITY_SKILL_H

#include "core/reference.h"

class EntitySkill : public Reference {
	GDCLASS(EntitySkill, Reference);

public:
	int get_skill_id();
	void set_skill_id(int value);

	int get_current();
	void set_current(int value);

	int get_max();
	void set_max(int value);

	bool get_disabled();
	void set_disabled(bool value);

	Dictionary to_dict();
	void from_dict(const Dictionary &dict);

	Dictionary _to_dict();
	void _from_dict(const Dictionary &dict);

	EntitySkill();

protected:
	static void _bind_methods();

private:
	int _skill_id;
	int _current;
	int _max;
	bool _disabled;
};

#endif
