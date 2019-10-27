#ifndef AI_ACTION_H
#define AI_ACTION_H

#include "core/resource.h"
#include "scene/main/node.h"

class Entity;

class AIAction : public Resource {
	GDCLASS(AIAction, Resource);

public:
	int get_utility() const;
	void set_utility(const int value);

	void set_owner(Entity *entity);
	void set_owner_bind(Node *entity);
	Entity *get_owner();

	void set_editor_description(const String &p_editor_description);
	String get_editor_description() const;

	void update(float delta);
	void execute();

	AIAction();

protected:
	static void _bind_methods();

private:
	int _utility;
	Entity *_owner;
};

#endif
