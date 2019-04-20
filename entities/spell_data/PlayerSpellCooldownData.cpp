#include "PlayerSpellCooldownData.h"
float PlayerSpellCooldownData::getCooldown(){
	return this->cooldown;
}
void PlayerSpellCooldownData::setCooldown(float value)
{
	this->cooldown = value;
}
float PlayerSpellCooldownData::getRemainingCooldown()
{
	return this->remainingCooldown;
}
void PlayerSpellCooldownData::setRemainingCooldown(float value)
{
	this->remainingCooldown = value;
}
PlayerSpellCooldownData::PlayerSpellCooldownData()
{
}
PlayerSpellCooldownData::PlayerSpellCooldownData(int spellId, float cooldown, float remainingCooldown) : PlayerSpellData(spellId)
{
	this->setCooldown(cooldown);
	this->setRemainingCooldown(remainingCooldown);
}
void PlayerSpellCooldownData::Update(PlayerSpellDataComponent* psdc)
{
	this->remainingCooldown -= Time::deltaTime;
	if (this->remainingCooldown <= (float)0) {
		psdc->RemoveSSpellData(this);
	}
}
void PlayerSpellCooldownData::Serialize(JsonWriter* w)
{
	PlayerSpellCooldownData::ToJSON(this, w);
}
void PlayerSpellCooldownData::ToJSON(PlayerSpellCooldownData* psdc, JsonWriter* w)
{
	w->WritePropertyName(new String("PlayerSpellData"));
	w->WriteStartObject();
	w->WritePropertyName(new String("Cooldown"));
	w->WriteValue(psdc->getCooldown());
	w->WritePropertyName(new String("RemainingCooldown"));
	w->WriteValue(psdc->getRemainingCooldown());
	w->WriteEndObject();
}
void PlayerSpellCooldownData::FromJSON(PlayerSpellCooldownData* psdc, JsonReader* r)
{
	while (r->Read()) {
		if (r->TokenType == JsonToken::PropertyName) {
			String* a = (String*)(r->Value);
			if (!*a == *(new String("Cooldown"))) {
				if (*a == *(new String("RemainingCooldown"))) {
					psdc->setRemainingCooldown((float)(r->ReadAsDouble()->Value));
				}
			}
			else {
				psdc->setCooldown((float)(r->ReadAsDouble()->Value));
			}
		}
		else {
			if (r->TokenType == JsonToken::EndObject) {
				break;
			}
		}
	}
}

