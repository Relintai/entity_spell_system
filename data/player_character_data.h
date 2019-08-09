#ifndef PLAYER_CHARACTER_DATA_H
#define PLAYER_CHARACTER_DATA_H

#include "core/resource.h"
#include "core/ustring.h"

#include "../data/character_class.h"
#include "../loot/loot_data_base.h"

//same as mob data
//name generator, or name -> probably an overrideable get_name
//class specific strings? like what this class does? lik character creating info? or put that into cc?
//Skeleton -> basic gear
//Add it to the data manager too.

class PlayerCharacterData : public Resource {
	GDCLASS(PlayerCharacterData, Resource);

public:
    int get_id() const;
    void set_id(const int id);
    
    Ref<CharacterClass> get_character_class() const;
    void set_character_class(const Ref<CharacterClass> character_class);
    
    String get_player_name();
    
    String get_static_player_name() const;
    void set_static_player_name(const String name);
    
	PlayerCharacterData();
	~PlayerCharacterData();

protected:
	static void _bind_methods();

private:
    int _id;
    Ref<CharacterClass> _character_class;
    String _static_player_name;
    //Skeleton -> basic gear
};


#endif
