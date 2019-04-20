#include "SpellScriptFactory.h"
namespace BS {
	namespace SpellsNS {
		namespace Utils {
			void SpellScriptFactory::GetScript(String* name, GameObject* g){
				Debug::Log(*(new String("Spellscript not found! name: ")) + *name);
			}
			String* SpellScriptFactory::GetScriptString(GameObject* g)
			{
				return g->GetComponent<SpellScript>()->GetType()->Name;
			}
			void SpellScriptFactory::FromJSON(GameObject* g, JsonReader* r)
			{
				if (r->Read()) {
					SpellScriptFactory::GetScript((String*)(r->Value), g);
				}
			}
			void SpellScriptFactory::ToJSON(GameObject* g, JsonWriter* w)
			{
				w->WritePropertyName(new String("SpellScript"));
				w->WriteValue(SpellScriptFactory::GetScriptString(g));
			}

		}
	}
}
