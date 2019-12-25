#ifndef MESH_DATA_REOURCE_H
#define MESH_DATA_REOURCE_H

#include "core/resource.h"
#include "core/array.h"
#include "scene/resources/mesh.h"

class MeshDataResource : public Resource {

	GDCLASS(MeshDataResource, Resource);
	RES_BASE_EXTENSION("mdres");

public:
	Array get_array();
	void set_array(const Array &p_arrays);

	MeshDataResource();

protected:
	static void _bind_methods();

private:
	Array _arrays;
};

#endif
