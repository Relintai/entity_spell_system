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

#ifndef ENTITY_RESOURCE_H
#define ENTITY_RESOURCE_H

#include "core/version.h"

#if VERSION_MAJOR > 3
#include "core/io/resource.h"
#else
#include "core/resource.h"
#endif

#include "../../defines.h"

class Entity;

class EntityResource : public Resource {
	GDCLASS(EntityResource, Resource);

public:
	int get_id() const;
	void set_id(const int value);

	String get_text_name() const;
	void set_text_name(const String value);

	bool get_dirty() const;
	void set_dirty(const bool value);

	bool get_should_process() const;
	void set_should_process(const bool value);

	int get_current_value() const;
	void set_current_value(const int value);

	int get_max_value() const;
	void set_max_value(const int value);

	Entity *get_owner();
	void set_owner(Entity *entity);
	void set_owner_bind(Node *owner);

	void ons_added(Entity *owner);
	void onc_added(Entity *owner);

	void notification_sstat_changed(const int statid, const float current);
	void notification_cstat_changed(const int statid, const float current);

	void ons_target_changed(Entity *entity, Entity *old_target);
	void onc_target_changed(Entity *entity, Entity *old_target);

	void process_server(const float delta);
	void _process_server(const float delta);

	void process_client(const float delta);
	void _process_client(const float delta);

	void receivec_update(const int current);
	void receivec_update_full(const int current, const int max);
	void receivec_update_string(const String str);

	PoolRealArray get_stacking_mods();
	void set_stacking_mods(const PoolRealArray &mods);

	void add_stacking_mod(const float value);
	void remove_stacking_mod(const float value);

	PoolRealArray get_non_stacking_mods();
	void set_non_stacking_mods(const PoolRealArray &mods);

	void add_non_stacking_mod(const float value);
	void remove_non_stacking_mod(const float value);

	float get_current_stacking_mod_value() const;
	float get_current_positive_non_stacking_mod_value() const;
	float get_current_negative_non_stacking_mod_value() const;

	void refresh_current_stacking_mod_value();
	void refresh_current_non_stacking_mod_values();

	void mods_changed();

	Dictionary to_dict();
	void from_dict(const Dictionary &dict);

	Dictionary _to_dict();
	void _from_dict(const Dictionary &dict);

	EntityResource();
	~EntityResource();

protected:
	void _stacking_mod_added(const float value);
	void _stacking_mod_removed(const float value);

	void _non_stacking_mod_added(const float value);
	void _non_stacking_mod_removed(const float value);

	void _mods_changed();

	static void _bind_methods();

private:
	int _id;
	String _text_name;

	bool _server_side;

	Entity *_owner;
	bool _dirty;
	bool _should_process;

	int _current;
	int _max;

	float _current_stacking_mod_value;
	float _current_positive_non_stacking_mod_value;
	float _current_negative_non_stacking_mod_value;

	PoolRealArray _stacking_mods;
	PoolRealArray _non_stacking_mods;
};

#endif
