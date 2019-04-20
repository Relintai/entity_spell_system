#ifndef MOB_SPELL_DATA_ENTRY_H
#define MOB_SPELL_DATA_ENTRY_H

#include "core/object.h"

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
