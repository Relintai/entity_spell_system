#include "CSpellCastEventFailedMsg.h"
namespace BS {
	namespace Networking {
		void CSpellCastEventFailedMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1019);
			buf->WriteUInt(this->Guid);
			buf->WriteInt(this->SpellId);
		}
		void CSpellCastEventFailedMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
			this->SpellId = buf->ReadInt();
		}
		CSpellCastEventFailedMsg::CSpellCastEventFailedMsg()
		{
		}
		String* CSpellCastEventFailedMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
