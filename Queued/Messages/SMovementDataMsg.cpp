#include "SMovementDataMsg.h"
namespace BS {
	namespace Networking {
		void SMovementDataMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1011);
			buf->WriteUInt(this->Guid);
			buf->WriteVector2(this->Axes);
			buf->WriteFloat(this->Speed);
		}
		void SMovementDataMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
			this->Axes = buf->ReadVector2();
			this->Speed = buf->ReadFloat();
		}
		SMovementDataMsg::SMovementDataMsg()
		{
		}
		String* SMovementDataMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
