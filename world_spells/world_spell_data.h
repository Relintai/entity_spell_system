#ifndef WORLD_SPELL_DATA_H
#define WORLD_SPELL_DATA_H

#include "core/resource.h"

#include "core/vector.h"
#include "scene/resources/packed_scene.h"

#include "../spell_enums.h"

class WorldSpellData : public Resource {
	GDCLASS(WorldSpellData, Resource);

public:
	int get_id();
	void set_id(int value);

	SpellEnums::ColliderType get_collider_type();
	void set_collider_type(SpellEnums::ColliderType value);

	Vector3 get_collider_box_extents();
	void set_collider_box_extents(Vector3 value);

	float get_collider_sphere_radius();
	void set_collider_sphere_radius(float value);

	SpellEnums::TargetType get_target_type();
	void set_target_type(SpellEnums::TargetType value);

	int get_target_bone_id();
	void set_target_bone_id(int value);

	bool get_move();
	void set_move(bool value);

	float get_movement_speed();
	void set_movement_speed(float value);

	Vector3 get_movement_dir();
	void set_movement_dir(Vector3 value);

	float get_max_dist();
	void set_max_dist(float value);

	Ref<PackedScene> get_effect();
	void set_effect(Ref<PackedScene> value);

	Vector3 get_effect_offset();
	void set_effect_offset(Vector3 value);

	WorldSpellData();
	~WorldSpellData();

protected:
	static void _bind_methods();

private:
	int _id;

	SpellEnums::ColliderType _collider_type;
	Vector3 _collider_box_extents;
	float _collider_sphere_radius;

	SpellEnums::TargetType _target_type;
	int _target_bone_id;

	bool _move;
	float _movement_speed;
	Vector3 _movement_dir;

	float _max_dist;

	Ref<PackedScene> _effect;
	Vector3 _effect_offset;
};

#endif
