#include "SimpleEventMsg.h"
namespace BS {
	namespace Networking {
		void SimpleEventMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1005);
			buf->WriteInt((int)(this->Event));
		}
		void SimpleEventMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Event = (SimpleEventMsg::EventType)(buf->ReadInt());
		}
		SimpleEventMsg::SimpleEventMsg()
		{
		}
		String* SimpleEventMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
