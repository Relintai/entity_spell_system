#include "cooldown.h"

int Cooldown::get_spell_id() const
{
    return _spell_id; 
}

void Cooldown::set_spell_id(const int value) 
{ 
    _spell_id = value; 
}

float Cooldown::get_remaining() const
{ 
    return _remaining; 
    
}

void Cooldown::set_remaining(const float value) 
{ 
    _remaining = value; 
}

bool Cooldown::update(const float delta) {
    _remaining -= delta;
    
    if (_remaining <= 0) {
        _remaining = 0;
        
        return true;
    }
    
    return false;
}

	
void Cooldown::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_spell_id"), &Cooldown::get_spell_id);
    ClassDB::bind_method(D_METHOD("set_spell_id", "value"), &Cooldown::set_spell_id);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "spell_id"), "set_spell_id", "get_spell_id");
        
    ClassDB::bind_method(D_METHOD("get_remaining"), &Cooldown::get_remaining);
    ClassDB::bind_method(D_METHOD("set_remaining", "value"), &Cooldown::set_remaining);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "remaining"), "set_remaining", "get_remaining");
    
    ClassDB::bind_method(D_METHOD("update", "delta"), &Cooldown::update);
}
