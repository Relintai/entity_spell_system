#pragma once
#include <System/System.h>
#include "SerializationBuffer.h"

using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct AddCPlayerSpellCooldownDataMsg : public virtual ValueType
		{
				int SpellId;
				float Cooldown;
				float RemainingCooldown;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				AddCPlayerSpellCooldownDataMsg();
				String* ToString();
		};
	}
}
