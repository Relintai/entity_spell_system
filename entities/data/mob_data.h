#ifndef MOB_DATA_H
#define MOB_DATA_H

#include "core/resource.h"
#include "core/ustring.h"

#include "entity_data.h"
#include "../../loot/loot_data_base.h"

//Add it to the data manager too.

class MobData : public Resource {
	GDCLASS(MobData, Resource);

public:
    int get_id() const;
    void set_id(const int id);
    
    Ref<LootDataBase> get_loot_db() const;
    void set_loot_db(const Ref<LootDataBase> lootdb);
    
    Ref<EntityData> get_entity_data() const;
    void set_entity_data(const Ref<EntityData> entity_data);
    
    String get_player_name();
    
    String get_static_player_name() const;
    void set_static_player_name(const String name);
    
	MobData();
	~MobData();

protected:
	static void _bind_methods();

private:
    int _id;
    Ref<LootDataBase> _lootdb;
    Ref<EntityData> _entity_data;
    String _static_player_name;
    //Skeleton -> basic gear
};


#endif
