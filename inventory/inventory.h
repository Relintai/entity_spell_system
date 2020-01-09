#ifndef INVENTORY_H
#define INVENTORY_H

#include "core/reference.h"
#include "core/vector.h"

#include "../item_enums.h"

class Player;
class itemTemplate;
class ItemInstance;

class Inventory : public Reference {
	GDCLASS(Inventory, Reference);

public:
	int get_allowed_item_types() const;
	void set_allowed_item_types(const int value);

	Player *get_target() const;
	void set_target(Player *caster);
	void set_target_bind(Node *caster);

	Inventory();
	~Inventory();

protected:
	static void _bind_methods();

private:
	Player *_target;
	int _allowed_item_types;
};

#endif
