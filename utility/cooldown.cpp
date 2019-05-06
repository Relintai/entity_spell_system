#include "cooldown.h"

int Cooldown::get_spell_id() 
{ 
    return _spell_id; 
}

void Cooldown::set_spell_id(int value) 
{ 
    _spell_id = value; 
}

int Cooldown::get_remaining() 
{ 
    return _remaining; 
    
}

void Cooldown::set_remaining(int value) 
{ 
    _remaining = value; 
}

	
void Cooldown::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_spell_id"), &Cooldown::get_spell_id);
    ClassDB::bind_method(D_METHOD("set_spell_id", "value"), &Cooldown::set_spell_id);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "spell_id"), "set_spell_id", "get_spell_id");
        
    ClassDB::bind_method(D_METHOD("get_remaining"), &Cooldown::get_remaining);
    ClassDB::bind_method(D_METHOD("set_remaining", "value"), &Cooldown::set_remaining);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "remaining"), "set_remaining", "get_remaining");
}
