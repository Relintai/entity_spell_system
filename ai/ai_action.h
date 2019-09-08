#ifndef AI_ACTION_H
#define AI_ACTION_H

#include "core/resource.h"
#include "scene/main/node.h"

class Entity;

class AIAction : public Resource {
	GDCLASS(AIAction, Resource);

public:
	int get_default_priority() const;
	void set_default_priority(const int value);

	int get_priority(Entity *entity);
	int get_priority_bind(Node *entity);

	int _get_priority(Node *entity);

	bool should_use(Entity *entity);
	bool should_use_bind(Node *entity);

	void set_editor_description(const String &p_editor_description);
	String get_editor_description() const;

	AIAction();

protected:
	static void _bind_methods();

private:
	int _default_priority;
};

#endif
