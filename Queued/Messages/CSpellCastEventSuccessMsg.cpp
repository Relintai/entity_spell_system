#include "CSpellCastEventSuccessMsg.h"
namespace BS {
	namespace Networking {
		void CSpellCastEventSuccessMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1018);
			buf->WriteUInt(this->Guid);
			buf->WriteInt(this->SpellId);
		}
		void CSpellCastEventSuccessMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
			this->SpellId = buf->ReadInt();
		}
		CSpellCastEventSuccessMsg::CSpellCastEventSuccessMsg()
		{
		}
		String* CSpellCastEventSuccessMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
