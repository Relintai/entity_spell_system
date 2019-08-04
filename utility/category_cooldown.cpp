#include "category_cooldown.h"

int CategoryCooldown::get_category_id() const
{ 
    return _category_id; 
}

void CategoryCooldown::set_category_id(const int value) 
{ 
    _category_id = value; 
}

float CategoryCooldown::get_remaining() const
{ 
    return _remaining; 
    
}

void CategoryCooldown::set_remaining(const float value) 
{ 
    _remaining = value; 
}

bool CategoryCooldown::update(const float delta) {
    _remaining -= delta;
    
    if (_remaining <= 0) {
        _remaining = 0;
        
        return true;
    }
    
    return false;
}

	
void CategoryCooldown::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_category_id"), &CategoryCooldown::get_category_id);
    ClassDB::bind_method(D_METHOD("set_category_id", "value"), &CategoryCooldown::set_category_id);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "category_id"), "set_category_id", "get_category_id");
        
    ClassDB::bind_method(D_METHOD("get_remaining"), &CategoryCooldown::get_remaining);
    ClassDB::bind_method(D_METHOD("set_remaining", "value"), &CategoryCooldown::set_remaining);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "remaining"), "set_remaining", "get_remaining");
    
    ClassDB::bind_method(D_METHOD("update", "delta"), &CategoryCooldown::update);
}
