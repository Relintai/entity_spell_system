#ifndef ENTITY_SKILL_DATA_H
#define ENTITY_SKILL_DATA_H

#include "core/resource.h"
#include "core/ustring.h"

class EntitySkillData : public Resource {
	GDCLASS(EntitySkillData, Resource);

public:
	int get_id() const;
	void set_id(const int value);

	int get_default_value() const;
	void set_default_value(const int value);

	int get_max_value() const;
	void set_max_value(const int value);

	String get_text_description() const;
	void set_text_description(const String value);

	EntitySkillData();
	~EntitySkillData();

protected:
	static void _bind_methods();

private:
	int _id;
	int _default_value;
	int _max_value;
	String _text_description;
};

#endif
