#include "NetworkedMovementManager.h"
namespace KinematicCharacterController {
	namespace Walkthrough {
		namespace NetworkingExample {
			NetworkedMovementManager* NetworkedMovementManager::getInstance(){
				return Instance_var;
			}
			void NetworkedMovementManager::setInstance(NetworkedMovementManager* value)
			{
				Instance_var = value;
			}
			void NetworkedMovementManager::Awake()
			{
				NetworkedMovementManager::setInstance(this);
			}
			void NetworkedMovementManager::Start()
			{
				this->InitializeSubsystems();
				Mathf::CeilToInt(((float)0.001 * CxNet::Server->GetMaxDisconnectTimeout()) / Time::fixedDeltaTime);
				this->KinematicCharacterSubsystem->init = true;
				Entity::OnSPlayerAdded += *(new Entity::OnLocalPlayerChangedAction(this->SOnCharacterSpawned));
			}
			void NetworkedMovementManager::InitializeSubsystems()
			{
				this->KinematicCharacterSubsystem->Initialize(100);
				Array<NetworkedCharacterController>* characters = this->BotController->Characters;
				for (int i = 0; i < characters->Length; i += 1) {
					NetworkedCharacterController* character = characters->GetData(i);
					this->KinematicCharacterSubsystem->RegisterCharacter(character, null);
				}
			}
			void NetworkedMovementManager::FixedUpdate()
			{
				this->KinematicCharacterSubsystem->OnPreTick(Time::fixedDeltaTime);
				this->KinematicCharacterSubsystem->OnPostTick(Time::fixedDeltaTime);
			}
			void NetworkedMovementManager::PlaceCharacterAtSpawnPointIndex(NetworkedCharacterController* character, int spawnPointIndex)
			{
				Vector3* position = *(this->PlayerSpawnPoint->position) + ((Vector3::right * (float)(spawnPointIndex)) * (float)2);
				Quaternion* rotation = this->PlayerSpawnPoint->rotation;
				character->Motor->SetPositionAndRotation(position, rotation, true);
			}
			void NetworkedMovementManager::SOnConnect(CxConnection* connection)
			{
			}
			void NetworkedMovementManager::SOnDisconnect(CxConnection* connection)
			{
			}
			void NetworkedMovementManager::SOnData(CxConnection* connection, SerializationBuffer* buffer)
			{
				buffer->SeekZero();
				NetworkMessageID networkMessageID = (NetworkMessageID)(buffer->ReadInt());
				if (networkMessageID == NetworkMessageID::TickSync) {
					TickSyncMsg tickSyncMsg = TickSyncMsg();
					tickSyncMsg.Deserialize(buffer);
					this->SHandleTickSyncMsg(tickSyncMsg, connection);
					return;
				}
				if (networkMessageID != NetworkMessageID::LazerHit) {
					return;
				}
				LazerFireMsg lazerFireMsg = LazerFireMsg();
				lazerFireMsg.Deserialize(buffer);
				this->SHandleLazerFireMsg(lazerFireMsg);
			}
			void NetworkedMovementManager::SHandlePlayerClientLoadedMsg(CxConnection* connection)
			{
				bool arg_05_0 = CxNet::IsServer;
			}
			void NetworkedMovementManager::SHandleTickSyncMsg(TickSyncMsg& msg, CxConnection* connection)
			{
				if (CxNet::IsClient) {
					Mathf::FloorToInt((connection.GetRemoteDelayTimeMS(msg.Timestamp) * (float)0.001) / Time::fixedDeltaTime);
					SimpleEventMsg simpleEventMsg = SimpleEventMsg();
					simpleEventMsg.Event = SimpleEventMsg::EventType::TickSynced;
					simpleEventMsg.Serialize(CxNet::NetBuffer);
					CxNet::SendBufferToServer(0);
				}
			}
			void NetworkedMovementManager::SOnCharacterSpawned(Entity* e)
			{
				if (CxNet::IsServer) {
					WorldEntity* expr_0D = (WorldEntity*)(*e);
					CxConnection* connection = expr_0D->getConnection();
					expr_0D->GetComponent<NetworkedPlayerController>();
					NetworkedCharacterController* component = expr_0D->GetComponent<NetworkedCharacterController>();
					this->KinematicCharacterSubsystem->RegisterCharacterAtId(component, connection);
					component->Motor->SetPositionAndRotation(e->transform->position, e->transform->localRotation, true);
				}
			}
			void NetworkedMovementManager::SHandleLazerFireMsg(LazerFireMsg& msg)
			{
				int arg_08_0 = msg.HitCharacterId;
			}
			void NetworkedMovementManager::COnConnect(CxConnection* connection)
			{
			}
			void NetworkedMovementManager::COnDisconnect(CxConnection* connection)
			{
				if (CxNet::IsServer) {
					for (int i = this->ConnectionInfos->Count - 1; i >= 0; i -= 1) {
						if (this->ConnectionInfos->GetData(i)->Connection == *connection) {
							FOREACH(_ARG_4B_0, this->ConnectionInfos->GetData(i)->PlayerControllerIds) {
								uint arg_4B_0 = *_ARG_4B_0;
							}
							this->ConnectionInfos->RemoveAt(i);
							return;
						}
					}
					return;
				}
				bool arg_80_0 = CxNet::IsClient;
			}
			void NetworkedMovementManager::COnData(CxConnection* connection, SerializationBuffer* buffer)
			{
				buffer->SeekZero();
				NetworkMessageID networkMessageID = (NetworkMessageID)(buffer->ReadInt());
				if (networkMessageID == NetworkMessageID::TickSync) {
					TickSyncMsg tickSyncMsg = TickSyncMsg();
					tickSyncMsg.Deserialize(buffer);
					this->CHandleTickSyncMsg(tickSyncMsg, connection);
					return;
				}
				if (networkMessageID != NetworkMessageID::LazerHit) {
					return;
				}
				LazerFireMsg lazerFireMsg = LazerFireMsg();
				lazerFireMsg.Deserialize(buffer);
				this->CHandleLazerFireMsg(lazerFireMsg);
			}
			void NetworkedMovementManager::CHandlePlayerClientLoadedMsg(CxConnection* connection)
			{
				if (CxNet::IsServer) {
					TickSyncMsg tickSyncMsg = TickSyncMsg();
					tickSyncMsg.Timestamp = CxNet::GetTimestamp();
					tickSyncMsg.Serialize(CxNet::NetBuffer);
					CxNet::SendBufferToConnection(connection->ConnectionGUID, 0);
				}
			}
			void NetworkedMovementManager::CHandleTickSyncMsg(TickSyncMsg& msg, CxConnection* connection)
			{
				if (CxNet::IsClient) {
					Mathf::FloorToInt((connection.GetRemoteDelayTimeMS(msg.Timestamp) * (float)0.001) / Time::fixedDeltaTime);
					SimpleEventMsg simpleEventMsg = SimpleEventMsg();
					simpleEventMsg.Event = SimpleEventMsg::EventType::TickSynced;
					simpleEventMsg.Serialize(CxNet::NetBuffer);
					CxNet::SendBufferToServer(0);
				}
			}
			void NetworkedMovementManager::COnCharacterSpawned(Entity* e)
			{
				if (CxNet::IsServer) {
					WorldEntity* expr_0D = (WorldEntity*)(*e);
					CxConnection* connection = expr_0D->getConnection();
					expr_0D->GetComponent<NetworkedPlayerController>();
					NetworkedCharacterController* component = expr_0D->GetComponent<NetworkedCharacterController>();
					this->KinematicCharacterSubsystem->RegisterCharacterAtId(component, connection);
					component->Motor->SetPositionAndRotation(e->transform->position, e->transform->localRotation, true);
				}
			}
			void NetworkedMovementManager::CHandleLazerFireMsg(LazerFireMsg& msg)
			{
				int arg_08_0 = msg.HitCharacterId;
			}
			NetworkedMovementManager::ConnectionInfo* NetworkedMovementManager::GetConnectionInfoForConnection(CxConnection* connection)
			{
				for (int i = 0; i < this->ConnectionInfos->Count; i += 1) {
					if (this->ConnectionInfos->GetData(i)->Connection == *connection) {
						return this->ConnectionInfos->GetData(i);
					}
				}
				return null;
			}
			void NetworkedMovementManager::SimulateStep(float deltaTime)
			{
				this->BotController->OnSimulate(deltaTime);
				this->KinematicCharacterSubsystem->OnSimulateStep(deltaTime);
			}
			void NetworkedMovementManager::InitializeSnapshot(MyWorldSnapshot& worldSnapshot)
			{
				this->KinematicCharacterSubsystem->InitializeSnapshot(worldSnapshot.KinematicCharacterSubsystemState, 100);
			}
			void NetworkedMovementManager::SaveStateToSnapshot(MyWorldSnapshot& worldSnapshot)
			{
				this->KinematicCharacterSubsystem->SaveToSnapshot(worldSnapshot.KinematicCharacterSubsystemState);
			}
			void NetworkedMovementManager::RestoreStateFromSnapshot(MyWorldSnapshot& worldSnapshot)
			{
				this->KinematicCharacterSubsystem->RestoreStateFromSnapshot(worldSnapshot.KinematicCharacterSubsystemState);
			}
			void NetworkedMovementManager::OnPreSnapshot()
			{
				this->KinematicCharacterSubsystem->HandlePreSnapshotInterpolation();
			}
			void NetworkedMovementManager::OnPostSnapshot()
			{
				this->KinematicCharacterSubsystem->HandlePostSnapshotInterpolation();
			}
			void NetworkedMovementManager::OnData(CxConnection* connection, int messageId, SerializationBuffer* buffer)
			{
			}
			void NetworkedMovementManager::SOnData(CxConnection* connection, int messageId, SerializationBuffer* buffer)
			{
				throw new NotImplementedException();
			}
			void NetworkedMovementManager::COnData(CxConnection* connection, int messageId, SerializationBuffer* buffer)
			{
				throw new NotImplementedException();
			}
			NetworkedMovementManager* NetworkedMovementManager::Instance_var;
			NetworkedMovementManager::NetworkedMovementManager()
			{
				serverside = true;
				ConnectionInfos = new List_T<NetworkedMovementManager::ConnectionInfo*>();
				MaxLocalPlayers = 1;
				MaxPlayers = 100;
				MaxCharacters = 100;
				Instance_var = (NetworkedMovementManager*)(0);
			}

		}
	}
}
