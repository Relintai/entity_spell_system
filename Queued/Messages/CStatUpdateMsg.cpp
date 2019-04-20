#include "CStatUpdateMsg.h"
namespace BS {
	namespace Networking {
		void CStatUpdateMsg::Initialize(SerializationBuffer* buf){
			this->Buffer = buf;
			this->Buffer->SeekZero();
			this->Buffer->WriteInt(1022);
			this->Buffer->WriteUInt(this->Guid);
		}
		void CStatUpdateMsg::Deserialize(SerializationBuffer* buf)
		{
			this->Buffer = buf;
			this->Guid = this->Buffer->ReadUInt();
			this->next = this->Buffer->ReadInt();
		}
		void CStatUpdateMsg::ResetToStats()
		{
			this->Buffer->SeekZero();
			this->Buffer->ReadInt();
			this->Buffer->ReadUInt();
			this->next = this->Buffer->ReadInt();
		}
		void CStatUpdateMsg::FinishMessage()
		{
			this->Buffer->WriteInt(-1);
		}
		bool CStatUpdateMsg::HasNext()
		{
			return this->next != -1;
		}
		int CStatUpdateMsg::Next()
		{
			return this->next;
		}
		void CStatUpdateMsg::Step()
		{
			this->next = this->Buffer->ReadInt();
		}
		CStatUpdateMsg::CStatUpdateMsg()
		{
		}
		String* CStatUpdateMsg::ToString()
		{
			return new String(CURRENT_TYPE);
		}

	}
}
