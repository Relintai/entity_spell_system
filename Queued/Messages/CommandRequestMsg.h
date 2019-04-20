#pragma once
#include <System/System.h>
#include "SerializationBuffer.h"

using namespace CxNetworking::Utils;
using namespace System;
namespace KinematicCharacterController {
	namespace Walkthrough {
		namespace NetworkingExample {
			struct CommandRequestMsg : public virtual ValueType
			{
					uint ForPlayerId;
					int ForTick;
					void Serialize(SerializationBuffer* buf);
					void Deserialize(SerializationBuffer* buf);
					CommandRequestMsg();
					String* ToString();
			};
		}
	}
}
