#include "xp_data.h"

int XPData::get_max_level()
{
    return _xp_required->size();
}

int XPData::xp_required_for_level(int level) {
    level -= 1;
    if (level >= _xp_required->size()) {
        return -1;
    }
    return _xp_required->get(level);
}

bool XPData::can_level_up(int level)
{
    level -= 1;
	return level < _xp_required->size();
}

XPData::XPData()
{
	_xp_required = memnew(PoolIntArray());
}

XPData::~XPData() {
	memdelete(_xp_required);
}

void XPData::_bind_methods() {

}
