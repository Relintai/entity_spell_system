#include "SSendRemoveCraftMaterialMsg.h"
namespace BS {
	namespace Networking {
		void SSendRemoveCraftMaterialMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1052);
			buf->WriteInt(this->ItemId);
			buf->WriteInt(this->Count);
		}
		void SSendRemoveCraftMaterialMsg::Deserialize(SerializationBuffer* buf)
		{
			this->ItemId = buf->ReadInt();
			this->Count = buf->ReadInt();
		}
		SSendRemoveCraftMaterialMsg::SSendRemoveCraftMaterialMsg()
		{
		}
		String* SSendRemoveCraftMaterialMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
