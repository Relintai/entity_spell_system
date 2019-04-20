#pragma once
#include <System/System.h>
#include "EntityType.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "SerializationBuffer.h"

using namespace BS::Player;
using namespace UnityEngine;
using namespace CxNetworking::Utils;
using namespace System;
namespace BS {
	namespace Networking {
		struct SpawnCharacterMsg : public virtual ValueType
		{
				uint Guid;
				int ClassId;
				EntityType Type;
				String* Name;
				bool IsLocalPlayer;
				Vector3* SpawnPosition;
				Quaternion* SpawnRotation;
				void Serialize(SerializationBuffer* buf);
				void Deserialize(SerializationBuffer* buf);
				SpawnCharacterMsg();
				String* ToString();
		};
	}
}
