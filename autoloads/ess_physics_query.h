#ifndef ESS_PHYSICS_QUERY_H
#define ESS_PHYSICS_QUERY_H

#include "scene/main/node.h"
#include "core/object.h"

#include "core/os/thread_safe.h"

#include "../entity_enums.h"

class ESSPhysicsQuery : public Node {
	GDCLASS(ESSPhysicsQuery, Node);

	_THREAD_SAFE_CLASS_

public:
	static ESSPhysicsQuery *get_instance();

	void queue_intersect_ray(Object *p_id, const StringName &p_prop, const Vector3 &p_from, const Vector3 &p_to, const Vector<RID> &p_exclude = Vector<RID>());
	//void queue_intersect_shape(const Ref<PhysicsShapeQueryParameters> &p_shape_query, int p_max_results = 32);
	
	//Array _intersect_shape(const Ref<PhysicsShapeQueryParameters> &p_shape_query, int p_max_results = 32);

	void flush();

	ESSPhysicsQuery();
	~ESSPhysicsQuery();

protected:
	static void _bind_methods();
	void _notification(int p_what);

private:
	enum PhysicsQueryType {
		PHYSICS_QUERY_TYPE_RAY = 0,
		PHYSICS_QUERY_TYPE_SPHERE,
		PHYSICS_QUERY_TYPE_BOX,
	};

	enum {
		DEFAULT_QUEUE_SIZE_KB = 1024
	};

	struct QueryData {
		ObjectID instance_id;
		StringName target;
		int16_t type;
		Vector3 position;
		Vector3 rotation;
		Vector3 extents;
	};

	static ESSPhysicsQuery *_instance;

	bool _flushing;

	uint8_t *_buffer;
	uint32_t _buffer_end;
	uint32_t _buffer_max_used;
	uint32_t _buffer_size;
};

#endif
