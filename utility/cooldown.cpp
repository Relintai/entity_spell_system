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

Dictionary Cooldown::to_dict() {
	return call("_to_dict");
}
void Cooldown::from_dict(const Dictionary &dict) {
	call("_from_dict", dict);
}

Dictionary Cooldown::_to_dict() {
	Dictionary dict;

	dict["spell_id"] = _spell_id;
	dict["remaining"] = _remaining;

	return dict;
}
void Cooldown::_from_dict(const Dictionary &dict) {
	ERR_FAIL_COND(dict.empty());
}
	
void Cooldown::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_spell_id"), &Cooldown::get_spell_id);
    ClassDB::bind_method(D_METHOD("set_spell_id", "value"), &Cooldown::set_spell_id);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "spell_id"), "set_spell_id", "get_spell_id");
        
    ClassDB::bind_method(D_METHOD("get_remaining"), &Cooldown::get_remaining);
    ClassDB::bind_method(D_METHOD("set_remaining", "value"), &Cooldown::set_remaining);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "remaining"), "set_remaining", "get_remaining");
    
    ClassDB::bind_method(D_METHOD("update", "delta"), &Cooldown::update);

	//Serialization
	BIND_VMETHOD(MethodInfo("_from_dict", PropertyInfo(Variant::DICTIONARY, "dict")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::DICTIONARY, "dict"), "_to_dict"));

	ClassDB::bind_method(D_METHOD("from_dict", "dict"), &Cooldown::from_dict);
	ClassDB::bind_method(D_METHOD("to_dict"), &Cooldown::to_dict);

	ClassDB::bind_method(D_METHOD("_from_dict", "dict"), &Cooldown::_from_dict);
	ClassDB::bind_method(D_METHOD("_to_dict"), &Cooldown::_to_dict);
}
