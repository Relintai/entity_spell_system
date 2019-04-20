#pragma once
#include <System/System.h>
#include "SerializationBuffer.h"

using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct GameDataMsg : public virtual ValueType
		{
				int Seed;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				GameDataMsg();
				String* ToString();
		};
	}
}
