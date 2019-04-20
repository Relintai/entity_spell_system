#include "SSendAddItemMsg.h"
namespace BS {
	namespace Networking {
		void SSendAddItemMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1044);
			buf->WriteInt(this->SlotId);
			buf->WriteInt(this->ItemId);
			buf->WriteInt(this->Count);
		}
		void SSendAddItemMsg::Deserialize(SerializationBuffer* buf)
		{
			this->SlotId = buf->ReadInt();
			this->ItemId = buf->ReadInt();
			this->Count = buf->ReadInt();
		}
		SSendAddItemMsg::SSendAddItemMsg()
		{
		}
		String* SSendAddItemMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
