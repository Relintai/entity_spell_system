#pragma once
#include <System/System.h>
#include <System/Delegate.h>
#include "WorldEntity.h"
#include "PlayerResource.h"
#include <System/Collections/Generic/List.h>
#include "CharacterResourceData.h"
#include "Interlocked.h"
#include "PlayerData.h"
#include "RageResource.h"
#include "PlayerResourceTypes.h"
#include "CxNet.h"
#include "SSendRageMsg.h"
#include "SSendAddResourceMsg.h"
#include "SSendClearMsg.h"
#include "JsonWriter.h"
#include "JsonReader.h"
#include "JsonToken.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace UnityEngine;
using namespace System::Threading;
using namespace CxNetworking;
using namespace BS::Networking;
using namespace Newtonsoft::Json;
namespace BS {
	namespace Player {
		//Forward Declaration
		class WorldEntity;

		//Attribute: Serializable*
		class PlayerResourceComponent : public virtual Object{
			public:
				DELEGATE(void) COnResourcesChangedAction;
			private:
				WorldEntity* owner;
			//Attribute: SerializeField*
			private:
				List_T<PlayerResource>* sResources;
			//Attribute: SerializeField*
			private:
				List_T<PlayerResource>* cResources;
			//Attribute: SerializeField*
			private:
				CharacterResourceData* characterResourceData;
			//Attribute: SerializeField*
			private:
				bool init;
			//Attribute: SerializeField*
			private:
				bool loaded;
			public:
				void addCOnResourcesChanged(PlayerResourceComponent::COnResourcesChangedAction* value);
			public:
				void removeCOnResourcesChanged(PlayerResourceComponent::COnResourcesChangedAction* value);
			public:
				List_T<PlayerResource>* getSResources();
				//Ignored empty method declaration
			public:
				List_T<PlayerResource>* getCResources();
				//Ignored empty method declaration
			public:
				bool getFinished();
				//Ignored empty method declaration
			public:
				bool getLoaded();
			public:
				void setLoaded(bool value);
			public:
				PlayerResourceComponent(WorldEntity* owner);
			public:
				void Init();
			public:
				void LateUpdate();
			public:
				void SClear();
			public:
				PlayerResource* SAddResource(PlayerResourceTypes type);
			public:
				void SSendRage(int current);
			public:
				void SSendAddResource(PlayerResourceTypes type);
			public:
				void SSendClear();
			public:
				void CReceiveRageSend(int current);
			public:
				void CReceiveAddResource(PlayerResourceTypes type);
			public:
				void CReceiveClear();
			public:
				PlayerResource* SGetPlayerResource(PlayerResourceTypes type);
			public:
				PlayerResource* CGetPlayerResource(PlayerResourceTypes type);
			public:
				T* SGetPlayerResource<T>();
			public:
				T* CGetPlayerResource<T>();
			public:
				bool SHasPlayerResource<T>();
			public:
				bool CHasPlayerResource<T>();
			public:
				void ToJSON(JsonWriter* w);
			public:
				void FromJSON(JsonReader* r);
		};
	}
}
