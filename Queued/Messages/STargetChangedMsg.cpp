#include "STargetChangedMsg.h"
namespace BS {
	namespace Networking {
		void STargetChangedMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1029);
			buf->WriteUInt(this->Guid);
			buf->WriteUInt(this->TargetGuid);
		}
		void STargetChangedMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
			this->TargetGuid = buf->ReadUInt();
		}
		STargetChangedMsg::STargetChangedMsg()
		{
		}
		String* STargetChangedMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
