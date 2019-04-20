#include "CResurrectMsg.h"
namespace BS {
	namespace Networking {
		void CResurrectMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1025);
			buf->WriteUInt(this->Guid);
		}
		void CResurrectMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
		}
		CResurrectMsg::CResurrectMsg()
		{
		}
		String* CResurrectMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
