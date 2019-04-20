#include "MobSpellData.h"

bool MobSpellData::getRanged() {
	return this->ranged;
}

void MobSpellData::setRanged(bool value) {
	this->ranged = value;
}

List<MobSpellDataEntry> *MobSpellData::getAttackSpells() {
	return this->attackSpells;
}

List<MobSpellDataEntry> *MobSpellData::getChargeSpells() {
	return this->chargeSpells;
}

List<MobSpellDataEntry> *MobSpellData::getCcSpells() {
	return this->ccSpells;
}

List<MobSpellDataEntry> *MobSpellData::getDpsSpells() {
	return this->dpsSpells;
}

List<MobSpellDataEntry> *MobSpellData::getRegenerationSpells() {
	return this->regenerationSpells;
}

List<MobSpellDataEntry> *MobSpellData::getStunBreakSpells() {
	return this->stunBreakSpells;
}

void MobSpellData::Sort() {
	/*
	this->attackSpells->Sort();
	this->chargeSpells->Sort();
	this->ccSpells->Sort();
	this->dpsSpells->Sort();
	this->regenerationSpells->Sort();
	this->stunBreakSpells->Sort();*/
}

MobSpellData::MobSpellData() {
	attackSpells = new List<MobSpellDataEntry>();
	chargeSpells = new List<MobSpellDataEntry>();
	ccSpells = new List<MobSpellDataEntry>();
	dpsSpells = new List<MobSpellDataEntry>();
	regenerationSpells = new List<MobSpellDataEntry>();
	stunBreakSpells = new List<MobSpellDataEntry>();
}
