#include "PlayerRegistrationMsg.h"
namespace BS {
	namespace Networking {
		void PlayerRegistrationMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1000);
			buf->WriteString(this->PlayerName);
			buf->WriteInt(this->classId);
		}
		void PlayerRegistrationMsg::Deserialize(SerializationBuffer* buf)
		{
			this->PlayerName = buf->ReadString();
			this->classId = buf->ReadInt();
		}
		PlayerRegistrationMsg::PlayerRegistrationMsg()
		{
		}
		String* PlayerRegistrationMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
