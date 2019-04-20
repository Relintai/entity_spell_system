#pragma once
#include <System/System.h>
#include "SerializationBuffer.h"

using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct SSendTeamMsg : public virtual ValueType
		{
				uint Guid;
				int Team;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				SSendTeamMsg();
				String* ToString();
		};
	}
}
