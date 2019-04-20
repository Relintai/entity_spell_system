#include "CSendCraftItemRequestMsg.h"
namespace BS {
	namespace Networking {
		void CSendCraftItemRequestMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1050);
			buf->WriteInt(this->CraftId);
		}
		void CSendCraftItemRequestMsg::Deserialize(SerializationBuffer* buf)
		{
			this->CraftId = buf->ReadInt();
		}
		CSendCraftItemRequestMsg::CSendCraftItemRequestMsg()
		{
		}
		String* CSendCraftItemRequestMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
