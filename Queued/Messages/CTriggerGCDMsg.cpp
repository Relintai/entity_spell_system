#include "CTriggerGCDMsg.h"
namespace BS {
	namespace Networking {
		void CTriggerGCDMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1027);
			buf->WriteUInt(this->Guid);
		}
		void CTriggerGCDMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
		}
		CTriggerGCDMsg::CTriggerGCDMsg()
		{
		}
		String* CTriggerGCDMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
