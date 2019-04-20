#ifndef AURA_APPLY_DATA_H
#define AURA_APPLY_DATA_H

#include "AuraGroup.h"

class AuraApplyData : public virtual Object{
	private:
		List_T<AuraGroup>* auraGroups;

	public:
		String* SerializationName;
		List_T<AuraGroup>* getAuraGroups();
		void setAuraGroups(List_T<AuraGroup>* value);
		void FromJSON(JsonReader* r);
		void ToJSON(JsonWriter* w);
		AuraApplyData();
};

#endif
