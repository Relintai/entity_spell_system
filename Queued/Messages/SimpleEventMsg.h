#pragma once
#include <System/System.h>
#include "SerializationBuffer.h"

using namespace System;
using namespace CxNetworking::Utils;
namespace BS {
	namespace Networking {
		struct SimpleEventMsg : public virtual ValueType
		{
			enum class EventType
			{
				Invalid,
				TickSynced,
				InitiateGame
			};
				SimpleEventMsg::EventType Event;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				SimpleEventMsg();
				String* ToString();
		};
	}
}
