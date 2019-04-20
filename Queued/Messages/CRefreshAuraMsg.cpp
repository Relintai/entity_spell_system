#include "CRefreshAuraMsg.h"
namespace BS {
	namespace Networking {
		void CRefreshAuraMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1030);
			buf->WriteUInt(this->Guid);
			buf->WriteInt(this->AuraId);
			buf->WriteFloat(this->Time);
		}
		void CRefreshAuraMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
			this->AuraId = buf->ReadInt();
			this->Time = buf->ReadFloat();
		}
		CRefreshAuraMsg::CRefreshAuraMsg()
		{
		}
		String* CRefreshAuraMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
