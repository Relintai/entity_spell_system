#ifndef MOB_SPELL_DATA_ENTRY_H
#define MOB_SPELL_DATA_ENTRY_H

#include "core/object.h"

//bind, att to charclass, add virtual _should use, add should_use
//keep type, and prio
//foeach all keep all, should use, use highest prio
//use one per frame
//basic setup script all types into a class, then have the ability to customize
//can have other classes too, this could work like util ai

//AIAction is a resource
//AIAction base have the virtuals, and c++ stuff to call them
//this inheroths ai action

//AIMoveAction -> kiter classes have higher prio

//this is attach only (for now)


enum class MobSpellDataType{
	ATTACK,
	CHARGE,
	CC,
	DPS,
	REGENERATION,
	STUNBREAK
};

class MobSpellDataEntry : public Object {
    private:
        MobSpellDataType type;
        int spellId;
        int priority;

    public:
        bool moveWhileCasting;
        MobSpellDataType getType();
        int getSpellId();
        int getPriority();
        bool getMoveWhileCasting();
        MobSpellDataEntry();
        MobSpellDataEntry(MobSpellDataType type, int spellId, int priority, bool moveWhileCasting);
        int CompareTo(Object* other);
};

#endif
