#pragma once
#include <System/System.h>
#include "SerializationBuffer.h"

using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct SSendSentCraftMaterialsMsg : public virtual ValueType
		{
				String* Materials;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				SSendSentCraftMaterialsMsg();
				String* ToString();
		};
	}
}
