#include "PlayerAddMsg.h"
namespace BS {
	namespace Networking {
		void PlayerAddMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1002);
			buf->WriteBool(this->Add);
			buf->WriteBool(this->ForLocalPlayer);
			buf->WriteUInt(this->PlayerId);
			buf->WriteString(this->PlayerName);
		}
		void PlayerAddMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Add = buf->ReadBool();
			this->ForLocalPlayer = buf->ReadBool();
			this->PlayerId = buf->ReadUInt();
			this->PlayerName = buf->ReadString();
		}
		PlayerAddMsg::PlayerAddMsg()
		{
		}
		String* PlayerAddMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
