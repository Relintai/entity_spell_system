#ifndef ENTITY_RESOURCE_H
#define ENTITY_RESOURCE_H

#include "core/reference.h"

class EntityResource : public Reference {
	GDCLASS(EntityResource, Reference);

public:
	bool get_dirty();
	void set_dirty(bool value);

	bool get_should_process();
	void set_should_process(bool value);

	void process(float delta);

	EntityResource();

protected:
	static void _bind_methods();

private:
	bool _dirty;
	bool _should_process;
};

#endif
