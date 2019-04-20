#include "CTargetChangedMsg.h"
namespace BS {
	namespace Networking {
		void CTargetChangedMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1028);
			buf->WriteUInt(this->Guid);
			buf->WriteUInt(this->TargetGuid);
		}
		void CTargetChangedMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
			this->TargetGuid = buf->ReadUInt();
		}
		CTargetChangedMsg::CTargetChangedMsg()
		{
		}
		String* CTargetChangedMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
