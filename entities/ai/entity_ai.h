/*
Copyright (c) 2019-2022 Péter Magyar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef ENTITY_AI_H
#define ENTITY_AI_H

#include "core/version.h"

#if VERSION_MAJOR > 3
#include "core/io/resource.h"
#else
#include "core/resource.h"
#endif

#include "scene/main/node.h"

#include "../../entity_enums.h"

class AuraData;
class SpellHealInfo;
class SpellDamageInfo;
class SpellCastInfo;
class ItemInstance;
class EntityResource;
class Entity;

class EntityAI : public Resource {
	GDCLASS(EntityAI, Resource);

public:
	bool get_enabled();
	void set_enabled(bool value);

	void set_owner(Entity *entity);
	void set_owner_bind(Node *entity);
	Entity *get_owner();

	Vector<int> get_spec_distribution();
	void set_spec_distribution(Vector<int> data);

	int get_spec_variance();
	void set_spec_variance(int value);

	EntityEnums::AIStates get_state();
	void set_state(EntityEnums::AIStates state);

	EntityEnums::AIStates get_force_state();
	void set_force_state(EntityEnums::AIStates state);

	void set_editor_description(const String &p_editor_description);
	String get_editor_description() const;

	void update(float delta);
	void pet_update(float delta);

	void move(float delta);
	void pet_move(float delta);

	void _on_set_owner();

	////    Spell System    ////

	void start_casting(int spell_id, Entity *caster, float spellScale);

	void notification_saura(int what, Ref<AuraData> data);
	void notification_sheal(int what, Ref<SpellHealInfo> info);
	void notification_scast(int what, Ref<SpellCastInfo> info);
	void notification_sdamage(int what, Ref<SpellDamageInfo> info);

	void notification_sdeath(Entity *entity);
	void notification_sdeath_bind(Node *entity);

	void notification_scooldown_added(int id, float value);
	void notification_scooldown_removed(int id, float value);

	void notification_scategory_cooldown_added(int id, float value);
	void notification_scategory_cooldown_removed(int id, float value);

	void notification_sgcd_started(Entity *entity, float gcd);
	void notification_sgcd_finished(Entity *entity);
	void notification_sgcd_started_bind(Node *entity, float gcd);
	void notification_sgcd_finished_bind(Node *entity);

	void notification_sxp_gained(Entity *entity, int value);
	void notification_sxp_gained_bind(Node *entity, int value);
	void notification_slevel_up(Entity *entity, int value);
	void notification_slevel_up_bind(Node *entity, int value);

	void notification_sentity_resource_added(Ref<EntityResource> resource);
	void notification_sentity_resource_removed(Ref<EntityResource> resource);

	//Equipment

	bool equip_should_deny(Entity *entity, int equip_slot, Ref<ItemInstance> item);
	bool equip_should_deny_bind(Node *entity, int equip_slot, Ref<ItemInstance> item);

	void equip_son_success(Entity *entity, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);
	void equip_son_success_bind(Node *entity, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);
	void equip_son_fail(Entity *entity, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);
	void equip_son_fail_bind(Node *entity, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);

	void equip_con_success(Entity *entity, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);
	void equip_con_success_bind(Node *entity, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);
	void equip_con_fail(Entity *entity, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);
	void equip_con_fail_bind(Node *entity, int equip_slot, Ref<ItemInstance> item, Ref<ItemInstance> old_item, int bag_slot);

	EntityAI();
	~EntityAI();

protected:
	static void _bind_methods();

private:
	bool _enabled;
	Entity *_owner;

	Vector<int> _spec_distribution;
	int _spec_variance;

	EntityEnums::AIStates _state;
	EntityEnums::AIStates _force_state;
};

#endif
