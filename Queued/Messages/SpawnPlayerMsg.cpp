#include "SpawnPlayerMsg.h"
namespace BS {
	namespace Networking {
		void SpawnPlayerMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1006);
			buf->WriteInt(this->PlayerId);
			buf->WriteBool(this->IsLocalPlayer);
		}
		void SpawnPlayerMsg::Deserialize(SerializationBuffer* buf)
		{
			this->PlayerId = buf->ReadInt();
			this->IsLocalPlayer = buf->ReadBool();
		}
		SpawnPlayerMsg::SpawnPlayerMsg()
		{
		}
		String* SpawnPlayerMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
