#pragma once
#include <System/System.h>
#include "SerializationBuffer.h"

using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct CSendRequestRankIncreaseMsg : public virtual ValueType
		{
				uint Guid;
				int TalentId;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				CSendRequestRankIncreaseMsg();
				String* ToString();
		};
	}
}
