
#ifndef ESS_DEFINES_H
#define ESS_DEFINES_H

#include "core/version.h"

#if VERSION_MAJOR >= 4
#define GODOT4 true
#endif

//includes
#if GODOT4
#define spatial_h_path "scene/3d/node_3d.h"
#define visual_server_h_path include "servers/rendering_server.h"

//#include "core/input/input_event.h"
//#include "editor/plugins/node_3d_editor_plugin.h"
//#include "scene/3d/camera_3d.h"
#else
#define spatial_h_path "scene/3d/spatial.h"
#define visual_server_h_path include "servers/visual_server.h"

//#include "core/os/input.h"
//#include "editor/plugins/spatial_editor_plugin.h"
//#include "scene/3d/camera.h"

#endif

//Type Defines
#if GODOT4
#define PhysicsDirectSpaceState PhysicsDirectSpaceState3D
#define SpatialEditor Node3DEditor
#define SpatialEditorPlugin Node3DEditorPlugin
#define SpatialEditorViewport Node3DEditorViewport
#define PoolStringArray PackedStringArray

#define REAL FLOAT

#define POOL_STRING_ARRAY PACKED_STRING_ARRAY
#define POOL_INT_ARRAY PACKED_INT32_ARRAY
#define POOL_REAL_ARRAY PACKED_FLOAT32_ARRAY

#define Spatial Node3D

typedef class RenderingServer VisualServer;
typedef class RenderingServer VS;

#define PoolVector3Array PackedVector3Array
#define PoolVector2Array PackedVector2Array
#define PoolColorArray PackedColorArray
#define PoolIntArray PackedInt64Array
#define PoolRealArray PackedFloat32Array

//toodo figure out a way to have this
//#define Variant::CallError Callable::CallError
#endif

#if GODOT4

#define VARIANT_ARRAY_GET(arr)             \
	Vector<Variant> r;                     \
	for (int i = 0; i < arr.size(); i++) { \
		r.push_back(arr[i]);               \
	}                                      \
	return r;

#else

#define VARIANT_ARRAY_GET(arr)             \
	Vector<Variant> r;                     \
	for (int i = 0; i < arr.size(); i++) { \
		r.push_back(arr[i].get_ref_ptr()); \
	}                                      \
	return r;

#endif

#define VARIANT_ARRAY_SET(arr, arr_into, type) \
	arr_into.clear();                          \
	for (int i = 0; i < arr.size(); i++) {     \
		Ref<type> e = Ref<type>(arr[i]);       \
		arr_into.push_back(e);                 \
	}

#if GODOT4
//TODO do this properly
#define INSTANCE_VALIDATE(var) var
#define CONNECT(sig, obj, target_method_class, method) connect(sig, callable_mp(obj, &target_method_class::method))
#define DISCONNECT(sig, obj, target_method_class, method) disconnect(sig, callable_mp(obj, &target_method_class::method))
#else
#define INSTANCE_VALIDATE(var) ObjectDB::instance_validate(var)
#define CONNECT(sig, obj, target_method_class, method) connect(sig, obj, #method)
#define DISCONNECT(sig, obj, target_method_class, method) disconnect(sig, obj, #method)
#endif

#endif