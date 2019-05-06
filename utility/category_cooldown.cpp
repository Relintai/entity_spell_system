#include "category_cooldown.h"

int CategoryCooldown::get_category_id() 
{ 
    return _category_id; 
}

void CategoryCooldown::set_category_id(int value) 
{ 
    _category_id = value; 
}

int CategoryCooldown::get_remaining() 
{ 
    return _remaining; 
    
}

void CategoryCooldown::set_remaining(int value) 
{ 
    _remaining = value; 
}

	
void CategoryCooldown::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_category_id"), &CategoryCooldown::get_category_id);
    ClassDB::bind_method(D_METHOD("set_category_id", "value"), &CategoryCooldown::set_category_id);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "category_id"), "set_category_id", "get_category_id");
        
    ClassDB::bind_method(D_METHOD("get_remaining"), &CategoryCooldown::get_remaining);
    ClassDB::bind_method(D_METHOD("set_remaining", "value"), &CategoryCooldown::set_remaining);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "remaining"), "set_remaining", "get_remaining");
}
