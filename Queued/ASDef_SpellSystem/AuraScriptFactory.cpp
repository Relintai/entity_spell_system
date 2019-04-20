#include "AuraScriptFactory.h"
namespace BS {
	namespace AurasNS {
		namespace Utils {
			void AuraScriptFactory::GetScript(String* name, GameObject* g){
			}
			String* AuraScriptFactory::GetScriptString(GameObject* g)
			{
				return g->GetComponent<AuraScript>()->GetType()->Name;
			}
			void AuraScriptFactory::FromJSON(GameObject* g, JsonReader* r)
			{
				if (r->Read()) {
					AuraScriptFactory::GetScript((String*)(r->Value), g);
				}
			}
			void AuraScriptFactory::ToJSON(GameObject* g, JsonWriter* w)
			{
				w->WritePropertyName(new String("AuraScript"));
				w->WriteValue(AuraScriptFactory::GetScriptString(g));
			}

		}
	}
}
