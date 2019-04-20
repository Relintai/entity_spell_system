#include "CMovementDataMsg.h"
namespace BS {
	namespace Networking {
		void CMovementDataMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1010);
			buf->WriteVector2(this->Axes);
			buf->WriteFloat(this->Speed);
		}
		void CMovementDataMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Axes = buf->ReadVector2();
			this->Speed = buf->ReadFloat();
		}
		CMovementDataMsg::CMovementDataMsg()
		{
		}
		String* CMovementDataMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
