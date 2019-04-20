#pragma once
#include <System/System.h>
#include "GameObject.h"
#include "Debug.h"
#include "SpellScript.h"
#include "JsonReader.h"
#include "JsonWriter.h"

using namespace UnityEngine;
using namespace Newtonsoft::Json;
using namespace System;
namespace BS {
	namespace SpellsNS {
		namespace Utils {
			class SpellScriptFactory : public virtual Object
			{
				public:
				static void GetScript(String* name, GameObject* g);
				public:
				static String* GetScriptString(GameObject* g);
				public:
				static void FromJSON(GameObject* g, JsonReader* r);
				public:
				static void ToJSON(GameObject* g, JsonWriter* w);
			};
		}
	}
}
