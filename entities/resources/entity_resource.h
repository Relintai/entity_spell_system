/*
Copyright (c) 2019-2020 Péter Magyar

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

#include "core/reference.h"

class Entity;
class EntityResourceData;

class EntityResource : public Reference {
	GDCLASS(EntityResource, Reference);

public:
	bool get_dirty() const;
	void set_dirty(const bool value);

	bool get_should_process() const;
	void set_should_process(const bool value);

	Ref<EntityResourceData> get_resource_data();
	void set_resource_data(const Ref<EntityResourceData> &value);

	StringName get_data_path() const;
	void set_data_path(const StringName &value);

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

	virtual void resolve_references();

	Dictionary to_dict();
	void from_dict(const Dictionary &dict);

	Dictionary _to_dict();
	void _from_dict(const Dictionary &dict);

	EntityResource();
	~EntityResource();

protected:
	static void _bind_methods();

private:
	bool _server_side;

	Entity *_owner;
	bool _dirty;
	bool _should_process;

	Ref<EntityResourceData> _data;
	StringName _data_path;

	int _current;
	int _max;
};

#endif
