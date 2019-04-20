#pragma once
#include <System/System.h>
#include <System/Collections/Generic/Dictionary.h>
#include "Environment.h"
#include "Debug.h"

using namespace System::Collections::Generic;
using namespace System;
using namespace UnityEngine;
namespace BS {
	namespace Configs {
		class Config : public virtual Object
		{
			private:
				Dictionary_T<String, String>* LoadDataIntoDictionary(String* filename, String* data);
		};
	}
}
