#pragma once
#include <System/System.h>
#include "MonoBehaviour.h"
#include <System/Delegate.h>
#include "EntityType.h"
#include "CxConnection.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "GameObject.h"
#include <System/Collections/Generic/List.h>
#include <System/Collections/Generic/Dictionary.h>
#include "Interlocked.h"
#include "Debug.h"

using namespace UnityEngine;
using namespace CxNetworking::Sockets;
using namespace System::Collections::Generic;
using namespace System;
using namespace System::Threading;
namespace BS {
	namespace Player {
		class Entity : public abstract virtual MonoBehaviour, public abstract virtual Object
		{
			public:
				DELEGATE(void, Entity*) OnLocalPlayerChangedAction;
			public:
				DELEGATE(void, Entity*) OnPlayerChangedAction;
			public:
				DELEGATE(GameObject*, EntityType, int, int, String*, uint, CxConnection*, bool, Vector3*, Quaternion*) SSpawnDelegate;
			public:
				DELEGATE(GameObject*, uint, EntityType, int, int, String*, CxConnection*, bool, Vector3*, Quaternion*) CSpawnDelegate;
			public:
			static uint nextEntityGUID;
			private:
			static Entity* localPlayer;
			private:
			static List_T<Entity>* sNetworkedPlayers;
			private:
			static List_T<Entity>* sPlayers;
			private:
			static List_T<Entity>* sAis;
			private:
			static Dictionary_T<uint, Entity>* sPlayerGUIDS;
			private:
			static List_T<Entity>* cNetworkedPlayers;
			private:
			static List_T<Entity>* cPlayers;
			private:
			static List_T<Entity>* cAis;
			private:
			static Dictionary_T<uint, Entity>* cPlayerGUIDS;
			public:
			static Entity::SSpawnDelegate* SSpawn;
			public:
			static Entity::CSpawnDelegate* CSpawn;
			public:
			static Entity* self;
			public:
			static void addOnLocalPlayerChange(Entity::OnLocalPlayerChangedAction* value);
			public:
			static void removeOnLocalPlayerChange(Entity::OnLocalPlayerChangedAction* value);
			public:
			static void addOnSNetworkedPlayerAdded(Entity::OnLocalPlayerChangedAction* value);
			public:
			static void removeOnSNetworkedPlayerAdded(Entity::OnLocalPlayerChangedAction* value);
			public:
			static void addOnSNetworkedPlayerRemoved(Entity::OnLocalPlayerChangedAction* value);
			public:
			static void removeOnSNetworkedPlayerRemoved(Entity::OnLocalPlayerChangedAction* value);
			public:
			static void addOnSAiPlayerAdded(Entity::OnLocalPlayerChangedAction* value);
			public:
			static void removeOnSAiPlayerAdded(Entity::OnLocalPlayerChangedAction* value);
			public:
			static void addOnSAiPlayerRemoved(Entity::OnLocalPlayerChangedAction* value);
			public:
			static void removeOnSAiPlayerRemoved(Entity::OnLocalPlayerChangedAction* value);
			public:
			static void addOnSPlayerAdded(Entity::OnLocalPlayerChangedAction* value);
			public:
			static void removeOnSPlayerAdded(Entity::OnLocalPlayerChangedAction* value);
			public:
			static void addOnCNetworkedPlayerAdded(Entity::OnLocalPlayerChangedAction* value);
			public:
			static void removeOnCNetworkedPlayerAdded(Entity::OnLocalPlayerChangedAction* value);
			public:
			static void addOnCNetworkedPlayerRemoved(Entity::OnLocalPlayerChangedAction* value);
			public:
			static void removeOnCNetworkedPlayerRemoved(Entity::OnLocalPlayerChangedAction* value);
			public:
			static void addOnCAiPlayerAdded(Entity::OnLocalPlayerChangedAction* value);
			public:
			static void removeOnCAiPlayerAdded(Entity::OnLocalPlayerChangedAction* value);
			public:
			static void addOnCAiPlayerRemoved(Entity::OnLocalPlayerChangedAction* value);
			public:
			static void removeOnCAiPlayerRemoved(Entity::OnLocalPlayerChangedAction* value);
			public:
			static void addOnCPlayerAdded(Entity::OnLocalPlayerChangedAction* value);
			public:
			static void removeOnCPlayerAdded(Entity::OnLocalPlayerChangedAction* value);
			public:
			static Entity* getLocalPlayer();
				//Ignored empty method declaration
			public:
			static List_T<Entity>* getSNetworkedPlayers();
				//Ignored empty method declaration
			public:
			static List_T<Entity>* getSPlayers();
				//Ignored empty method declaration
			public:
			static List_T<Entity>* getSAis();
				//Ignored empty method declaration
			public:
			static Dictionary_T<uint, Entity>* getSPlayerGUIDS();
				//Ignored empty method declaration
			public:
			static List_T<Entity>* getCNetworkedPlayers();
				//Ignored empty method declaration
			public:
			static List_T<Entity>* getCPlayers();
				//Ignored empty method declaration
			public:
			static List_T<Entity>* getCAis();
				//Ignored empty method declaration
			public:
			static Dictionary_T<uint, Entity>* getCPlayerGUIDS();
				//Ignored empty method declaration
			static:
				Entity();
			public:
			static void RegisterLocalPlayer(uint playerGUID, Entity* lp);
			public:
			static void SRegisterAIPlayer(uint playerGUID, Entity* lp);
			public:
			static void SRegisterNetworkedPlayer(uint playerGUID, Entity* lp);
			public:
			static void SRegisterPlayer(uint PlayerGUID, Entity* player);
			public:
			static void CRegisterAIPlayer(uint playerGUID, Entity* lp);
			public:
			static void CRegisterNetworkedPlayer(uint playerGUID, Entity* lp);
			public:
			static void CRegisterPlayer(uint playerGUID, Entity* player);
			public:
			static void UnRegisterLocalPlayer(uint playerGUID);
			public:
			static void SUnregisterNetworkedPlayer(uint playerGUID, Entity* player);
			public:
			static void SUnregisterAIPlayer(uint playerGUID, Entity* player);
			public:
			static void SUnRegisterPlayer(uint playerGUID, Entity* player);
			public:
			static void CUnregisterNetworkedPlayer(uint playerGUID, Entity* player);
			public:
			static void CUnregisterAIPlayer(uint playerGUID, Entity* player);
			public:
			static void CUnRegisterPlayer(uint playerGUID, Entity* player);
			public:
			static void RegisterOnLocalPlayerChange(Entity::OnLocalPlayerChangedAction* action);
			public:
			static Entity* SGetPLayerWithGUID(uint guid);
			public:
			static Entity* CGetPLayerWithGUID(uint guid);
			public:
			static uint GetNextEntityGUID();
		};
	}
}
