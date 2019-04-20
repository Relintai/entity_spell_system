#include "CharacterMenuData.h"

String* CharacterMenuData::getName(){
	return this->name;
}

void CharacterMenuData::setName(String* value)
{
	this->name = value;
}

int CharacterMenuData::getLevel()
{
	return this->level;
}

void CharacterMenuData::setLevel(int value)
{
	this->level = value;
}

int CharacterMenuData::getClassId()
{
	return this->classid;
}

void CharacterMenuData::setClassId(int value)
{
	this->classid = value;
}

int CharacterMenuData::getGenderId()
{
	return this->genderid;
}

void CharacterMenuData::setGenderId(int value)
{
	this->genderid = value;
}

Character* CharacterMenuData::getCharacter()
{
	return this->character;
}

void CharacterMenuData::setCharacter(Character* value)
{
	this->character = value;
}

CharacterMenuData::CharacterMenuData()
{
}

CharacterMenuData::CharacterMenuData(String* name, int level, int classid, int genderid, Character* character)
{
	this->Set(name, level, classid, genderid, character);
}

void CharacterMenuData::Set(String* name, int level, int classid, int genderid, Character* character)
{
	this->setName(name);
	this->setLevel(level);
	this->setClassId(classid);
	this->setGenderId(genderid);
	this->setCharacter(character);
}

void CharacterMenuData::FromJSON(CharacterMenuData* cmd, JsonReader* r)
{
	bool flag = false;
	while (r->Read()) {
		if (r->TokenType == JsonToken::PropertyName) {
			String* a = (String*)(r->Value);
			if (!flag) {
				if (*a == *(new String("false"))) {
					CharacterMenuData::DoFromJSON(cmd, r);
				}
				if ((*a == *(new String("false"))) || (*a == *(new String("true")))) {
					flag = true;
				}
			}
			if (*a == *(new String("PlayerData"))) {
				CharacterMenuData::DoFromJSON(cmd, r);
				return;
			}
		}
	}
}

void CharacterMenuData::DoFromJSON(CharacterMenuData* cmd, JsonReader* r)
{
	while (r->Read()) {
		if (r->TokenType == JsonToken::PropertyName) {
			String* a = (String*)(r->Value);
			if (!*a == *(new String("Name"))) {
				if (!*a == *(new String("Level"))) {
					if (!*a == *(new String("ClassId"))) {
						if (*a == *(new String("Gender"))) {
							cmd->setGenderId(r->ReadAsInt32()->Value);
						}
					}
					else {
						cmd->setClassId(r->ReadAsInt32()->Value);
					}
				}
				else {
					cmd->setLevel(r->ReadAsInt32()->Value);
				}
			}
			else {
				cmd->setName(r->ReadAsString());
			}
		}
		else {
			if (r->TokenType == JsonToken::EndObject) {
				break;
			}
		}
	}
}

