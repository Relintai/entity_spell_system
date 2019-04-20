#include "FactionComponent.h"
namespace BS {
	namespace Player {
		bool FactionComponent::getSend(){
			return this->send;
		}
		void FactionComponent::setSend(bool value)
		{
			this->send = value;
		}
		int FactionComponent::getSTeam()
		{
			return this->sTeam;
		}
		void FactionComponent::setSTeam(int value)
		{
			this->sTeam = value;
			this->send = true;
		}
		int FactionComponent::getCTeam()
		{
			return this->cTeam;
		}
		void FactionComponent::setCTeam(int value)
		{
			this->cTeam = value;
		}
		FactionComponent::FactionComponent(WorldEntity* owner)
		{
			MOB = 4;
			PLAYER = 3;
			TEAM_BLUE = 2;
			TEAM_RED = 1;
			NONE = 0;
			this->owner = owner;
		}
		void FactionComponent::Update()
		{
			if (this->send) {
				this->send = false;
				this->SSendTeam(this->sTeam);
			}
		}
		void FactionComponent::SSendTeam(int team)
		{
			if (CxNet::IsServer) {
				SSendTeamMsg sSendTeamMsg = SSendTeamMsg();
				sSendTeamMsg.Guid = this->owner->PlayerData->GUID;
				sSendTeamMsg.Team = team;
				sSendTeamMsg.Serialize(CxNet::NetBuffer);
				CxNet::SendBufferToAllClients(0);
			}
		}
		void FactionComponent::CReceiveSSendTeam(int team)
		{
			this->setCTeam(team);
		}
		bool FactionComponent::SIsEnemy(WorldEntity* player)
		{
			return player->getFactionComponent()->STeam != this->getSTeam();
		}
		bool FactionComponent::CIsEnemy(WorldEntity* player)
		{
			return player->getFactionComponent()->CTeam != this->getCTeam();
		}
		void FactionComponent::ToJSON(JsonWriter* w)
		{
			w->WritePropertyName(new String("PlayerFacingComponent"));
			w->WriteStartObject();
			w->WritePropertyName(new String("STeam"));
			w->WriteValue(this->getSTeam());
			w->WriteEndObject();
		}
		void FactionComponent::FromJSON(JsonReader* r)
		{
			while (r->Read()) {
				if (r->TokenType == JsonToken::PropertyName) {
					String* a = (String*)(r->Value);
					if (*a == *(new String("STeam"))) {
						this->setSTeam(r->ReadAsInt32()->Value);
					}
				}
				else {
					if (r->TokenType == JsonToken::EndObject) {
						break;
					}
				}
			}
		}

	}
}
