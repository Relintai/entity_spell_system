#include "RageResource.h"
namespace BS {
	namespace Player {
		int RageResource::getCurrent(){
			return this->current;
		}
		void RageResource::setCurrent(int value)
		{
			if (value > this->max) {
				value = this->max;
			}
			if (value < 0) {
				value = 0;
			}
			PlayerResource::setDirty(true);
			this->current = value;
		}
		int RageResource::getMax()
		{
			return this->max;
		}
		void RageResource::setMax(int value)
		{
			PlayerResource::setDirty(true);
			this->max = value;
		}
		RageResource::RageResource()
		{
			this->current = 0;
			this->max = 100;
		}
		void RageResource::ToJSON(RageResource* rr, JsonWriter* w)
		{
			w->WritePropertyName(new String("RageResource"));
			w->WriteStartObject();
			w->WritePropertyName(new String("Current"));
			w->WriteValue(rr->getCurrent());
			w->WritePropertyName(new String("Max"));
			w->WriteValue(rr->getMax());
			w->WriteEndObject();
		}
		void RageResource::FromJSON(RageResource* rr, JsonReader* r)
		{
			while (r->Read()) {
				if (r->TokenType == JsonToken::PropertyName) {
					String* a = (String*)(r->Value);
					if (!*a == *(new String("Current"))) {
						if (*a == *(new String("Max"))) {
							rr->setMax(r->ReadAsInt32()->Value);
						}
					}
					else {
						rr->setCurrent(r->ReadAsInt32()->Value);
					}
				}
				else {
					if (r->TokenType == JsonToken::EndObject) {
						break;
					}
				}
			}
		}

	}
}
