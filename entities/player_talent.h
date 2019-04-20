#ifndef PLAYER_TALENT_H
#define PLAYER_TALENT_H

#include "core/object.h"

class PlayerTalent : public Object {
	GDCLASS(PlayerTalent, Object);

public:
	int get_talent_id();
	void set_talent_id(int value);
	int get_rank();
	void set_rank(int value);
	PlayerTalent();
	PlayerTalent(int talentID);

protected:
	static void _bind_methods();

private:
	int _talent_id;
	int _rank;
};

#endif
