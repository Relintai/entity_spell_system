#include "StateData.h"
StateData::StateType StateData::getType(){
	return this->type;
}
int StateData::getAuraId()
{
	return this->auraId;
}
StateData::StateData()
{
}
StateData::StateData(StateData::StateType type, int auraId)
{
	this->auraId = auraId;
	this->type = type;
}
void StateData::ToJSON(StateData* sd, JsonWriter* w)
{
	w->WritePropertyName(new String("StateData"));
	w->WriteStartObject();
	w->WritePropertyName(new String("Type"));
	w->WriteValue((int)(sd->getType()));
	w->WritePropertyName(new String("AuraId"));
	w->WriteValue(sd->getAuraId());
	w->WriteEndObject();
}
void StateData::FromJSON(StateData* sd, JsonReader* r)
{
	while (r->Read()) {
		if (r->TokenType == JsonToken::PropertyName) {
			String* a = (String*)(r->Value);
			if (!*a == *(new String("Type"))) {
				if (*a == *(new String("AuraId"))) {
					sd->auraId = r->ReadAsInt32()->Value;
				}
			}
			else {
				sd->type = (StateData::StateType)(r->ReadAsInt32()->Value);
			}
		}
		else {
			if (r->TokenType == JsonToken::EndObject) {
				break;
			}
		}
	}
}

