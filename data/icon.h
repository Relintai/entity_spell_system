#ifndef ICON_H
#define ICON_H

#include "core/resource.h"
#include "scene/resources/texture.h"

class Icon : public Resource {
	GDCLASS(Icon, Resource)

public:
	int get_id();
	void set_id(int value);

	String get_icon_file_name();
	void set_icon_file_name(String value);

	Vector2i get_icon_atlas_position();
	void set_icon_atlas_position(Vector2i value);

	Ref<Texture> get_icon();
	void set_icon(Ref<Texture> value);

	Icon();
	Icon(int id, String _icon_file_name, Vector2i iconAtlasPosition);

	void Load_icon() {}
	//Rect *Get_icon_rect();

	bool is_icon_loaded() { return _icon != nullptr; }

protected:
	static void _bind_methods();

public:
	int _id;
	String _icon_file_name;
	Vector2i _icon_atlas_position;
	Ref<Texture> _icon;
};

#endif
