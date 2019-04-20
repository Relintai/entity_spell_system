#include "CRefreshCasterAuraMsg.h"
namespace BS {
	namespace Networking {
		void CRefreshCasterAuraMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1031);
			buf->WriteUInt(this->Guid);
			buf->WriteUInt(this->CasterGuid);
			buf->WriteInt(this->AuraId);
			buf->WriteFloat(this->Time);
		}
		void CRefreshCasterAuraMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
			this->CasterGuid = buf->ReadUInt();
			this->AuraId = buf->ReadInt();
			this->Time = buf->ReadFloat();
		}
		CRefreshCasterAuraMsg::CRefreshCasterAuraMsg()
		{
		}
		String* CRefreshCasterAuraMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
