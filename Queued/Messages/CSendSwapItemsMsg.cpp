#include "CSendSwapItemsMsg.h"
namespace BS {
	namespace Networking {
		void CSendSwapItemsMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1049);
			buf->WriteInt(this->Slot1);
			buf->WriteInt(this->Slot2);
		}
		void CSendSwapItemsMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Slot1 = buf->ReadInt();
			this->Slot2 = buf->ReadInt();
		}
		CSendSwapItemsMsg::CSendSwapItemsMsg()
		{
		}
		String* CSendSwapItemsMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
