#include "PlayerResourceComponent.h"
namespace BS {
	namespace Player {
		//Delegate declaration moved to header file
		void PlayerResourceComponent::addCOnResourcesChanged(PlayerResourceComponent::COnResourcesChangedAction* value){
			PlayerResourceComponent::COnResourcesChangedAction* cOnResourcesChangedAction = this->COnResourcesChanged;
			PlayerResourceComponent::COnResourcesChangedAction* cOnResourcesChangedAction2;
			do{
				cOnResourcesChangedAction2 = cOnResourcesChangedAction;
				PlayerResourceComponent::COnResourcesChangedAction* value2 = (PlayerResourceComponent::COnResourcesChangedAction*)(Delegate::Combine(cOnResourcesChangedAction2, value));
				cOnResourcesChangedAction = Interlocked::CompareExchange<PlayerResourceComponent::COnResourcesChangedAction*>(this->COnResourcesChanged, value2, cOnResourcesChangedAction2);
			}
			while (*cOnResourcesChangedAction != *cOnResourcesChangedAction2);
		}
		void PlayerResourceComponent::removeCOnResourcesChanged(PlayerResourceComponent::COnResourcesChangedAction* value)
		{
			PlayerResourceComponent::COnResourcesChangedAction* cOnResourcesChangedAction = this->COnResourcesChanged;
			PlayerResourceComponent::COnResourcesChangedAction* cOnResourcesChangedAction2;
			do {
				cOnResourcesChangedAction2 = cOnResourcesChangedAction;
				PlayerResourceComponent::COnResourcesChangedAction* value2 = (PlayerResourceComponent::COnResourcesChangedAction*)(Delegate::Remove(cOnResourcesChangedAction2, value));
				cOnResourcesChangedAction = Interlocked::CompareExchange<PlayerResourceComponent::COnResourcesChangedAction*>(this->COnResourcesChanged, value2, cOnResourcesChangedAction2);
			}
			while (*cOnResourcesChangedAction != *cOnResourcesChangedAction2);
		}

		List_T<PlayerResource>* PlayerResourceComponent::getSResources()
		{
			return this->sResources;
		}
		List_T<PlayerResource>* PlayerResourceComponent::getCResources()
		{
			return this->cResources;
		}
		bool PlayerResourceComponent::getFinished()
		{
			return true;
		}
		bool PlayerResourceComponent::getLoaded()
		{
			return this->loaded;
		}
		void PlayerResourceComponent::setLoaded(bool value)
		{
			this->loaded = value;
		}
		PlayerResourceComponent::PlayerResourceComponent(WorldEntity* owner)
		{
			cResources = new List_T<PlayerResource>();
			sResources = new List_T<PlayerResource>();
			this->owner = owner;
		}
		void PlayerResourceComponent::Init()
		{
			PlayerData* playerData = this->owner->PlayerData;
			this->characterResourceData = playerData->getCharacter()->ResourceData;
			if (!this->init && this->characterResourceData->Rage) {
				if (this->owner->isServer) {
					this->sResources->Add(new RageResource());
				}
				if (this->owner->isClient) {
					this->cResources->Add(new RageResource());
					if (this->COnResourcesChanged != null) {
						DELEGATE_INVOKE(this->COnResourcesChanged);
					}
				}
			}
		}
		void PlayerResourceComponent::LateUpdate()
		{
			if (!this->owner->isServer) {
				return;
			}
			if (this->getLoaded()) {
				this->setLoaded(false);
				this->SSendClear();
				for (int i = 0; i < this->sResources->Count; i += 1) {
					if (is_inst_of<RageResource*>(this->sResources->GetData(i))) {
						this->SSendAddResource(PlayerResourceTypes::Rage);
					}
				}
				return;
			}
			for (int j = 0; j < this->sResources->Count; j += 1) {
				PlayerResource* playerResource = this->sResources->GetData(j);
				if (playerResource->getDirty() && is_inst_of<RageResource*>(playerResource)) {
					this->SSendRage(as_cast<RageResource*>(playerResource)->Current);
					playerResource->setDirty(false);
				}
			}
		}
		void PlayerResourceComponent::SClear()
		{
			this->init = true;
			this->sResources->Clear();
			if (!this->getLoaded()) {
				this->SSendClear();
			}
		}
		PlayerResource* PlayerResourceComponent::SAddResource(PlayerResourceTypes type)
		{
			PlayerResource* playerResource = null;
			if (type == PlayerResourceTypes::Rage) {
				playerResource = this->SGetPlayerResource<RageResource>();
				if (playerResource != null) {
					return playerResource;
				}
				playerResource = new RageResource();
				this->sResources->Add(playerResource);
			}
			if (!this->getLoaded()) {
				this->SSendAddResource(type);
			}
			return playerResource;
		}
		void PlayerResourceComponent::SSendRage(int current)
		{
			if (CxNet::IsServer) {
				SSendRageMsg sSendRageMsg = SSendRageMsg();
				sSendRageMsg.Guid = this->owner->PlayerData->GUID;
				sSendRageMsg.Current = current;
				sSendRageMsg.Serialize(CxNet::NetBuffer);
				CxNet::SendBufferToAllClients(0);
			}
		}
		void PlayerResourceComponent::SSendAddResource(PlayerResourceTypes type)
		{
			if (CxNet::IsServer) {
				SSendAddResourceMsg sSendAddResourceMsg = SSendAddResourceMsg();
				sSendAddResourceMsg.Guid = this->owner->PlayerData->GUID;
				sSendAddResourceMsg.Type = (int)(type);
				sSendAddResourceMsg.Serialize(CxNet::NetBuffer);
				CxNet::SendBufferToAllClients(0);
			}
		}
		void PlayerResourceComponent::SSendClear()
		{
			if (CxNet::IsServer) {
				SSendClearMsg sSendClearMsg = SSendClearMsg();
				sSendClearMsg.Guid = this->owner->PlayerData->GUID;
				sSendClearMsg.Serialize(CxNet::NetBuffer);
				CxNet::SendBufferToAllClients(0);
			}
		}
		void PlayerResourceComponent::CReceiveRageSend(int current)
		{
			for (int i = 0; i < this->cResources->Count; i += 1) {
				PlayerResource* playerResource = this->cResources->GetData(i);
				if (is_inst_of<RageResource*>(playerResource)) {
					as_cast<RageResource*>(playerResource)->Current = current;
				}
			}
		}
		void PlayerResourceComponent::CReceiveAddResource(PlayerResourceTypes type)
		{
			if ((type == PlayerResourceTypes::Rage) && !this->CHasPlayerResource<RageResource>()) {
				this->cResources->Add(new RageResource());
				if (this->COnResourcesChanged != null) {
					DELEGATE_INVOKE(this->COnResourcesChanged);
				}
			}
		}
		void PlayerResourceComponent::CReceiveClear()
		{
			this->init = true;
			bool flag = false;
			if (this->cResources->Count > 0) {
				flag = true;
			}
			this->cResources->Clear();
			if (flag && (this->COnResourcesChanged != null)) {
				DELEGATE_INVOKE(this->COnResourcesChanged);
			}
		}
		PlayerResource* PlayerResourceComponent::SGetPlayerResource(PlayerResourceTypes type)
		{
			for (int i = 0; i < this->sResources->Count; i += 1) {
				PlayerResource* playerResource = this->sResources->GetData(i);
				if ((type == PlayerResourceTypes::Rage) && is_inst_of<RageResource*>(playerResource)) {
					return playerResource;
				}
			}
			return null;
		}
		PlayerResource* PlayerResourceComponent::CGetPlayerResource(PlayerResourceTypes type)
		{
			for (int i = 0; i < this->cResources->Count; i += 1) {
				PlayerResource* playerResource = this->cResources->GetData(i);
				if ((type == PlayerResourceTypes::Rage) && is_inst_of<RageResource*>(playerResource)) {
					return playerResource;
				}
			}
			return null;
		}
		T* PlayerResourceComponent::SGetPlayerResource<T>()
		{
			for (int i = 0; i < this->sResources->Count; i += 1) {
				PlayerResource* playerResource = this->sResources->GetData(i);
				if (is_inst_of<T*>(playerResource)) {
					return UNBOX<T*>(as_cast<T*>(playerResource));
				}
			}
			return ;
		}
		T* PlayerResourceComponent::CGetPlayerResource<T>()
		{
			for (int i = 0; i < this->cResources->Count; i += 1) {
				PlayerResource* playerResource = this->cResources->GetData(i);
				if (is_inst_of<T*>(playerResource)) {
					return UNBOX<T*>(as_cast<T*>(playerResource));
				}
			}
			return ;
		}
		bool PlayerResourceComponent::SHasPlayerResource<T>()
		{
			for (int i = 0; i < this->sResources->Count; i += 1) {
				if (is_inst_of<T*>(this->sResources->GetData(i))) {
					return true;
				}
			}
			return false;
		}
		bool PlayerResourceComponent::CHasPlayerResource<T>()
		{
			for (int i = 0; i < this->cResources->Count; i += 1) {
				if (is_inst_of<T*>(this->cResources->GetData(i))) {
					return true;
				}
			}
			return false;
		}
		void PlayerResourceComponent::ToJSON(JsonWriter* w)
		{
			w->WritePropertyName(new String("PlayerResourceComponent"));
			w->WriteStartObject();
			List_T<PlayerResource>* list = this->getSResources();
			for (int i = 0; i < list->Count; i += 1) {
				PlayerResource* playerResource = list->GetData(i);
				if (is_inst_of<RageResource*>(playerResource)) {
					RageResource::ToJSON(as_cast<RageResource*>(playerResource), w);
				}
			}
			w->WriteEndObject();
		}
		void PlayerResourceComponent::FromJSON(JsonReader* r)
		{
			while (r->Read()) {
				if (r->TokenType == JsonToken::PropertyName) {
					String* a = (String*)(r->Value);
					if (*a == *(new String("RageResource"))) {
						RageResource::FromJSON((RageResource*)(this->SAddResource(PlayerResourceTypes::Rage)), r);
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
