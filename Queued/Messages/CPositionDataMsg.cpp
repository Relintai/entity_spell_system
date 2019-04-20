#include "CPositionDataMsg.h"
namespace BS {
	namespace Networking {
		void CPositionDataMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1013);
			buf->WriteVector3(this->Position);
			buf->WriteQuaternion(this->Rotation);
		}
		void CPositionDataMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Position = buf->ReadVector3();
			this->Rotation = buf->ReadQuaternion();
		}
		CPositionDataMsg::CPositionDataMsg()
		{
		}
		String* CPositionDataMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
