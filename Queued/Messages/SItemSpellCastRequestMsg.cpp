#include "SItemSpellCastRequestMsg.h"
namespace BS {
	namespace Networking {
		void SItemSpellCastRequestMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1021);
			buf->WriteInt(this->ItemId);
		}
		void SItemSpellCastRequestMsg::Deserialize(SerializationBuffer* buf)
		{
			this->ItemId = buf->ReadInt();
		}
		SItemSpellCastRequestMsg::SItemSpellCastRequestMsg()
		{
		}
		String* SItemSpellCastRequestMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
