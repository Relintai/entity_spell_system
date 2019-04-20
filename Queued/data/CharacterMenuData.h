#ifndef CHARACTER_MENU_DATA_H
#define CHARACTER_MENU_DATA_H

#include "Character.h"

class CharacterMenuData : public virtual Object
{
    private:
        String* name;
        int level;
        int classid;
        int genderid;
        Character* character;

    public:
        String* getName();
        void setName(String* value);
        int getLevel();
        void setLevel(int value);
        int getClassId();
        void setClassId(int value);
        int getGenderId();
        void setGenderId(int value);
        Character* getCharacter();
        void setCharacter(Character* value);
        CharacterMenuData();
        CharacterMenuData(String* name, int level, int classid, int genderid, Character* character);
        void Set(String* name, int level, int classid, int genderid, Character* character);
        static void FromJSON(CharacterMenuData* cmd, JsonReader* r);
        static void DoFromJSON(CharacterMenuData* cmd, JsonReader* r);
};

#endif
