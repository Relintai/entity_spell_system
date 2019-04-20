#include "SPositionDataMsg.h"
namespace BS {
	namespace Networking {
		void SPositionDataMsg::Serialize(SerializationBuffer* buf){
			buf->SeekZero();
			buf->WriteInt(1014);
			buf->WriteUInt(this->Guid);
			buf->WriteVector3(this->Position);
			buf->WriteQuaternion(this->Rotation);
		}
		void SPositionDataMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Guid = buf->ReadUInt();
			this->Position = buf->ReadVector3();
			this->Rotation = buf->ReadQuaternion();
		}
		SPositionDataMsg::SPositionDataMsg()
		{
		}
		String* SPositionDataMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
