#include "SSpellCastFinishedMsg.h"
namespace BS {
	namespace Networking {
		void SSpellCastFinishedMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1016);
			buf->WriteUInt(this->Guid);
		}
		void SSpellCastFinishedMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
		}
		SSpellCastFinishedMsg::SSpellCastFinishedMsg()
		{
		}
		String* SSpellCastFinishedMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
