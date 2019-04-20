#pragma once
#include <System/System.h>
#include "MonoBehaviour.h"
#include "MyWorldSnapshot.h"
#include "ISimulationController_T.h"
#include "WorldEntity.h"
#include "CxConnection.h"
#include <System/Collections/Generic/List.h>
#include "Transform.h"
#include "KinematicCharacterSubsystem.h"
#include "MyBotController.h"
#include "Mathf.h"
#include "CxNet.h"
#include "Time.h"
#include "Entity.h"
#include "NetworkedCharacterController.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "SerializationBuffer.h"
#include "NetworkMessageID.h"
#include "TickSyncMsg.h"
#include "LazerFireMsg.h"
#include "SimpleEventMsg.h"
#include "NetworkedPlayerController.h"
#include <System/Exception/SystemException/NotImplementedException.h>

using namespace UnityEngine;
using namespace BS::Player;
using namespace CxNetworking::Sockets;
using namespace System::Collections::Generic;
using namespace System;
using namespace CxNetworking;
using namespace CxNetworking::Utils;
using namespace BS::Networking;
namespace KinematicCharacterController {
	namespace Walkthrough {
		namespace NetworkingExample {
			//Attribute: DefaultExecutionOrder*(-1000)
			class NetworkedMovementManager : public virtual MonoBehaviour, public virtual ISimulationController_T<MyWorldSnapshot>, public virtual Object{
				public:
				class ConnectionInfo : public virtual Object{
					public:
					WorldEntity* entity;
					public:
					CxConnection* Connection;
					public:
					List_T<uint>* PlayerControllerIds;
					public:
					bool IsReady;
					public:
					ConnectionInfo::ConnectionInfo(){
						PlayerControllerIds = new List_T<uint>();
					}
				};
				public:
					bool serverside;
				private:
					Transform* PlayerSpawnPoint;
				public:
					KinematicCharacterSubsystem* KinematicCharacterSubsystem;
				public:
					MyBotController* BotController;
				//Attribute: NonSerialized*
				public:
					List_T<NetworkedMovementManager::ConnectionInfo*>* ConnectionInfos;
				private:
					int MaxLocalPlayers;
				private:
					int MaxPlayers;
				private:
					int MaxCharacters;
				private:
					int characterCounter;
				public:
				static NetworkedMovementManager* getInstance();
				public:
				static void setInstance(NetworkedMovementManager* value);
				public:
					void Awake();
				private:
					void Start();
				public:
					void InitializeSubsystems();
				private:
					void FixedUpdate();
				public:
					void PlaceCharacterAtSpawnPointIndex(NetworkedCharacterController* character, int spawnPointIndex);
				public:
					void SOnConnect(CxConnection* connection);
				public:
					void SOnDisconnect(CxConnection* connection);
				public:
					void SOnData(CxConnection* connection, SerializationBuffer* buffer);
				public:
					void SHandlePlayerClientLoadedMsg(CxConnection* connection);
				public:
					void SHandleTickSyncMsg(TickSyncMsg& msg, CxConnection* connection);
				public:
					void SOnCharacterSpawned(Entity* e);
				public:
					void SHandleLazerFireMsg(LazerFireMsg& msg);
				public:
					void COnConnect(CxConnection* connection);
				public:
					void COnDisconnect(CxConnection* connection);
				public:
					void COnData(CxConnection* connection, SerializationBuffer* buffer);
				public:
					void CHandlePlayerClientLoadedMsg(CxConnection* connection);
				public:
					void CHandleTickSyncMsg(TickSyncMsg& msg, CxConnection* connection);
				public:
					void COnCharacterSpawned(Entity* e);
				public:
					void CHandleLazerFireMsg(LazerFireMsg& msg);
				public:
					NetworkedMovementManager::ConnectionInfo* GetConnectionInfoForConnection(CxConnection* connection);
				public:
					void SimulateStep(float deltaTime);
				public:
					void InitializeSnapshot(MyWorldSnapshot& worldSnapshot);
				public:
					void SaveStateToSnapshot(MyWorldSnapshot& worldSnapshot);
				public:
					void RestoreStateFromSnapshot(MyWorldSnapshot& worldSnapshot);
				public:
					void OnPreSnapshot();
				public:
					void OnPostSnapshot();
				public:
					void OnData(CxConnection* connection, int messageId, SerializationBuffer* buffer);
				public:
					void SOnData(CxConnection* connection, int messageId, SerializationBuffer* buffer);
				public:
					void COnData(CxConnection* connection, int messageId, SerializationBuffer* buffer);
				public:
				static NetworkedMovementManager* Instance_var;
				public:
					NetworkedMovementManager();
			};
		}
	}
}
