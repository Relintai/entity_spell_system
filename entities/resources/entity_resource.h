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

class Stat;
class Entity;
class EntityResourceData;

class EntityResource : public Reference {
	GDCLASS(EntityResource, Reference);

public:
	bool get_dirty();
	void set_dirty(bool value);

	bool get_should_process();
	void set_should_process(bool value);

	Ref<EntityResourceData> get_resource_data();
	void set_resource_data(Ref<EntityResourceData> value);

	int get_data_id();
	void set_data_id(int value);

	int get_current_value();
	void set_current_value(int value);

	int get_max_value();
	void set_max_value(int value);

	Entity *get_owner();
	void set_owner(Entity *entity);
	void set_owner_bind(Node *owner);

	void ons_added(Entity *owner);
	void onc_added(Entity *owner);

	void ons_stat_changed(Ref<Stat> stat);
	void onc_stat_changed(Ref<Stat> stat);

	void ons_target_changed(Entity *entity, Entity *old_target);
	void onc_target_changed(Entity *entity, Entity *old_target);

	void process_server(float delta);
	void _process_server(float delta);

	void process_client(float delta);
	void _process_client(float delta);

	void receivec_update(int current);
	void receivec_update_full(int current, int max);
	void receivec_update_string(String str);

	void resolve_references();

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
	int _data_id;

	int _current;
	int _max;
};

#endif
