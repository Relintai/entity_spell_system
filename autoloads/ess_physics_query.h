#ifndef ESS_PHYSICS_QUERY_H
#define ESS_PHYSICS_QUERY_H

#include "scene/main/node.h"

class ESSPhysicsQuery : public Node {
	GDCLASS(ESSPhysicsQuery, Node);

public:
	static ESSPhysicsQuery *get_instance();

	ESSPhysicsQuery();
	~ESSPhysicsQuery();

protected:
	static void _bind_methods();
	void _notification(int p_what);

private:
	static ESSPhysicsQuery *instance;
};

#endif
