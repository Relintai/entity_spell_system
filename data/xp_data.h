#ifndef LEVEL_XP_H
#define LEVEL_XP_H

#include "core/resource.h"
#include "core/variant.h"
#include "core/vector.h"

class XPData : public Resource {
	GDCLASS(XPData, Resource);

private:
	PoolIntArray *_xp_required;

protected:
	static void _bind_methods();

public:
	int get_max_level();
	int xp_required_for_level(int level);
	bool can_level_up(int level);
	XPData();
	~XPData();
};

#endif
