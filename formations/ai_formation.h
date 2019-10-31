#ifndef AI_FORMATION_H
#define AI_FORMATION_H

#include "core/resource.h"
#include "scene/main/node.h"

class Entity;

class AIFormation : public Resource {
	GDCLASS(AIFormation, Resource);

public:
	void set_owner(Entity *entity);
	void set_owner_bind(Node *entity);
	Entity *get_owner();

	void set_editor_description(const String &p_editor_description);
	String get_editor_description() const;

	Vector3 get_position(int slot_index);

	AIFormation();

protected:
	static void _bind_methods();

private:
	Entity *_owner;
};

#endif
