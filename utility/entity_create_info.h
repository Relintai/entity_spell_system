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

#ifndef ENTITY_CREATE_INFO_H
#define ENTITY_CREATE_INFO_H

#include "../entities/data/entity_data.h"
#include "../entity_enums.h"
#include "core/reference.h"
#include "core/ustring.h"

class EntityCreateInfo : public Reference {
	GDCLASS(EntityCreateInfo, Reference);

public:
	int get_guid() const;
	void set_guid(const int value);

	int get_class_id() const;
	void set_class_id(const int value);

	int get_network_owner() const;
	void set_network_owner(const int value);

	EntityEnums::EntityController get_entity_controller() const;
	void set_entity_controller(const EntityEnums::EntityController value);

	String get_entity_name() const;
	void set_entity_name(const String &value);

	String get_node_name() const;
	void set_node_name(const String &value);

	int get_level() const;
	void set_level(const int value);

	int get_xp() const;
	void set_xp(const int value);

	Transform get_transform() const;
	void set_transform(const Transform &value);

	Transform2D get_transform2d() const;
	void set_transform2d(const Transform2D &value);

	Ref<EntityData> get_entity_data() const;
	void set_entity_data(const Ref<EntityData> &value);

	EntityCreateInfo();
	~EntityCreateInfo();

protected:
	static void _bind_methods();

private:
	int _guid;
	int _class_id;
	int _network_owner;
	EntityEnums::EntityController _entity_controller;
	String _entity_name;
	int _level;
	int _xp;

	Transform _transform;
	Transform2D _transform2d;

	Ref<EntityData> _entity_data;
};

#endif
