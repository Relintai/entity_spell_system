#include "TickSyncMsg.h"
namespace BS {
	namespace Networking {
		void TickSyncMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1004);
			buf->WriteInt(this->Tick);
			buf->WriteInt(this->Timestamp);
		}
		void TickSyncMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Tick = buf->ReadInt();
			this->Timestamp = buf->ReadInt();
		}
		TickSyncMsg::TickSyncMsg()
		{
		}
		String* TickSyncMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
