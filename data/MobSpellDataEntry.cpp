#include "MobSpellDataEntry.h"

MobSpellDataType MobSpellDataEntry::getType(){
	return this->type;
}

int MobSpellDataEntry::getSpellId()
{
	return this->spellId;
}

int MobSpellDataEntry::getPriority()
{
	return this->priority;
}

bool MobSpellDataEntry::getMoveWhileCasting()
{
	return this->moveWhileCasting;
}

MobSpellDataEntry::MobSpellDataEntry()
{
}

MobSpellDataEntry::MobSpellDataEntry(MobSpellDataType type, int spellId, int priority, bool moveWhileCasting)
{
	this->type = type;
	this->spellId = spellId;
	this->priority = priority;
	this->moveWhileCasting = moveWhileCasting;
}


