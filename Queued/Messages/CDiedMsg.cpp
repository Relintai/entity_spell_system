#include "CDiedMsg.h"
namespace BS {
	namespace Networking {
		void CDiedMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1026);
			buf->WriteUInt(this->Guid);
		}
		void CDiedMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
		}
		CDiedMsg::CDiedMsg()
		{
		}
		String* CDiedMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
