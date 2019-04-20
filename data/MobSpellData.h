#ifndef MOB_SPELL_DATA_H
#define MOB_SPELL_DATA_H

#include "MobSpellDataEntry.h"

class MobSpellData : public Object {
    public:
        bool ranged;
        List<MobSpellDataEntry>* attackSpells;
        List<MobSpellDataEntry>* chargeSpells;
        List<MobSpellDataEntry>* ccSpells;
        List<MobSpellDataEntry>* dpsSpells;
        List<MobSpellDataEntry>* regenerationSpells;
        List<MobSpellDataEntry>* stunBreakSpells;

    public:
        bool getRanged();
        void setRanged(bool value);
        List<MobSpellDataEntry>* getAttackSpells();
        List<MobSpellDataEntry>* getChargeSpells();
        List<MobSpellDataEntry>* getCcSpells();
        List<MobSpellDataEntry>* getDpsSpells();
        List<MobSpellDataEntry>* getRegenerationSpells();
        List<MobSpellDataEntry>* getStunBreakSpells();
        void Sort();

        MobSpellData();
};

#endif
