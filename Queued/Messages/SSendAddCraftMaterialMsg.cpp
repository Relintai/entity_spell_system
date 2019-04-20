#include "SSendAddCraftMaterialMsg.h"
namespace BS {
	namespace Networking {
		void SSendAddCraftMaterialMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1051);
			buf->WriteInt(this->ItemId);
			buf->WriteInt(this->Count);
		}
		void SSendAddCraftMaterialMsg::Deserialize(SerializationBuffer* buf)
		{
			this->ItemId = buf->ReadInt();
			this->Count = buf->ReadInt();
		}
		SSendAddCraftMaterialMsg::SSendAddCraftMaterialMsg()
		{
		}
		String* SSendAddCraftMaterialMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
