#include "AuraApplyData.h"

List_T<AuraGroup>* AuraApplyData::getAuraGroups(){
	return this->auraGroups;
}

void AuraApplyData::setAuraGroups(List_T<AuraGroup>* value)
{
	this->auraGroups = value;
}

void AuraApplyData::FromJSON(JsonReader* r)
{
	while (r->Read()) {
		if (r->TokenType == JsonToken::PropertyName) {
			String* arg_16_0 = (String*)(r->Value);
		}
		else {
			if (r->TokenType == JsonToken::EndObject) {
				break;
			}
		}
	}
}

void AuraApplyData::ToJSON(JsonWriter* w)
{
	w->WritePropertyName(new String("AuraApplyData"));
	w->WriteStartObject();
	w->WriteEndObject();
}

AuraApplyData::AuraApplyData()
{
	SerializationName = new String("AuraApplyData");
}

