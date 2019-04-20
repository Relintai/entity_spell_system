#pragma once
#include <System/System.h>
#include "SerializationBuffer.h"

using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct PlayerRegistrationMsg : public virtual ValueType
		{
				String* PlayerName;
				int classId;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				PlayerRegistrationMsg();
				String* ToString();
		};
	}
}
