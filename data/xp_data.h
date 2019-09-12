#ifndef LEVEL_XP_H
#define LEVEL_XP_H

#include "core/resource.h"
#include "core/variant.h"
#include "core/vector.h"

class XPData : public Resource {
	GDCLASS(XPData, Resource);

public:
	int get_max_level();
	int xp_required_for_level(int level);
	bool can_level_up(int level);

	PoolIntArray get_xps();
	void set_xps(const PoolIntArray &xps);

	XPData();
	~XPData();

protected:
	static void _bind_methods();


private:
	PoolIntArray _xp_required;
};

#endif
