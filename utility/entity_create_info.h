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

#ifndef ENTITY_CREATE_INFO_H
#define ENTITY_CREATE_INFO_H

#include "core/version.h"

#if VERSION_MAJOR > 3
#include "core/object/reference.h"
#include "core/string/ustring.h"
#else
#include "core/reference.h"
#include "core/ustring.h"
#endif

#include "../entity_enums.h"

class EntityData;
class SpeciesInstance;
class Entity;

class EntityCreateInfo : public Reference {
	GDCLASS(EntityCreateInfo, Reference);

public:
	int get_guid() const;
	void set_guid(const int value);

	bool get_networked() const;
	void set_networked(const bool value);

	int get_class_id() const;
	void set_class_id(const int value);

	int get_entity_player_type();
	void set_entity_player_type(int value);

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

	Ref<SpeciesInstance> get_species_instance();
	void set_species_instance(const Ref<SpeciesInstance> &value);

	Dictionary get_serialized_data();
	void set_serialized_data(const Dictionary &value);

	NodePath get_parent_path() const;
	void set_parent_path(const NodePath &value);

	Entity *get_created_entity();
	void set_created_entity(Node *value);

	Dictionary to_dict();
	void from_dict(const Dictionary &dict);

	Dictionary _to_dict();
	void _from_dict(const Dictionary &dict);

	EntityCreateInfo();
	~EntityCreateInfo();

protected:
	static void _bind_methods();

private:
	int _guid;
	bool _networked;
	int _class_id;
	int _entity_player_type;
	int _network_owner;
	EntityEnums::EntityController _entity_controller;
	String _entity_name;
	String _node_name;
	int _level;
	int _xp;

	Transform _transform;
	Transform2D _transform2d;

	Ref<EntityData> _entity_data;
	Ref<SpeciesInstance> _species_instance;
	Dictionary _serialized_data;
	NodePath _parent_path;

	Entity *_created_entity;
};

#endif
