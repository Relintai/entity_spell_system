#ifndef WORLD_SPELL_DATA_H
#define WORLD_SPELL_DATA_H

#include "core/resource.h"

#include "core/vector.h"
#include "scene/resources/packed_scene.h"

#include "../spell_enums.h"

class WorldSpellData : public Resource {
	GDCLASS(WorldSpellData, Resource);

public:
	int get_id() const;
	void set_id(const int value);

	SpellEnums::ColliderType get_collider_type() const;
	void set_collider_type(const SpellEnums::ColliderType value);

	Vector3 get_collider_box_extents() const;
	void set_collider_box_extents(const Vector3 &value);

	float get_collider_sphere_radius() const;
	void set_collider_sphere_radius(const float value);

	SpellEnums::TargetType get_target_type() const;
	void set_target_type(const SpellEnums::TargetType value);

	int get_target_bone_id() const;
	void set_target_bone_id(const int value);

	bool get_move() const;
	void set_move(const bool value);

	float get_movement_speed() const;
	void set_movement_speed(const float value);

	Vector3 get_movement_dir() const;
	void set_movement_dir(const Vector3 &value);

	float get_max_dist() const;
	void set_max_dist(const float value);

	Ref<PackedScene> get_effect();
	void set_effect(const Ref<PackedScene> &value);

	Vector3 get_effect_offset() const;
	void set_effect_offset(const Vector3 &value);

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
