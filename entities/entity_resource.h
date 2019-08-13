#ifndef ENTITY_RESOURCE_H
#define ENTITY_RESOURCE_H

#include "core/reference.h"

class Stat;
class Entity;

class EntityResource : public Reference {
	GDCLASS(EntityResource, Reference);

public:
	bool get_dirty();
	void set_dirty(bool value);

	bool get_should_process();
	void set_should_process(bool value);

	int get_resource_type();
	void set_resource_type(int value);

	int get_current();
	void set_current(int value);

	int get_max();
	void set_max(int value);

	Entity *get_owner();
	void set_owner(Entity *entity);
	void set_owner_bind(Node *owner);

	void ons_added(Entity *owner);
	void onc_added(Entity *owner);

	void ons_stat_changed(Ref<Stat> stat);
	void onc_stat_changed(Ref<Stat> stat);

	void ons_target_changed(Entity *target);
	void onc_target_changed(Entity *target);

	void process(float delta);
	void _process(float delta);

	String gets_update_string();
	void receivec_update_string(String str);

	EntityResource();

protected:
	static void _bind_methods();

private:
	Entity *_owner;
	bool _dirty;
	bool _should_process;
	int _type;
	int _current;
	int _max;
};

#endif
