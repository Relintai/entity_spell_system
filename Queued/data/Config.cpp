#include "Config.h"
namespace BS {
	namespace Configs {
		Dictionary_T<String, String>* Config::LoadDataIntoDictionary(String* filename, String* data){
			Dictionary_T<String, String>* dictionary = new Dictionary_T<String, String>();
			Array<String>* array = data->Split(Environment::NewLine->ToCharArray());
			for (int i = 0; i < array->Length; i += 1){
				String* text = array->GetData(i)->Trim();
				if (!*text == *(new String("")) && (*(text->GetData(0)) != '#')){
					String* arg_48_0 = *text;
					Array<char>* expr_43 = new Array<char>(1);
					expr_43->SetData(0, '=');
					Array<String>* array2 = arg_48_0->Split(expr_43);
					if (dictionary->ContainsKey(array2->GetData(0))){
						Debug::Log((*filename + *(new String(" contains a key multiple times! key: "))) + *(array2->GetData(0)));
					}
					else {
						dictionary->Add(array2->GetData(0), array2->GetData(1));
					}
				}
			}
			return dictionary;
		}

	}
}
