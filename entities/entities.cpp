#include "Entity.h"
namespace BS {
	namespace Player {
		//Delegate declaration moved to header file
		//Delegate declaration moved to header file
		//Delegate declaration moved to header file
		//Delegate declaration moved to header file
		uint Entity::nextEntityGUID;
		Entity* Entity::localPlayer;
		List_T<Entity>* Entity::sNetworkedPlayers;
		List_T<Entity>* Entity::sPlayers;
		List_T<Entity>* Entity::sAis;
		Dictionary_T<uint, Entity>* Entity::sPlayerGUIDS;
		List_T<Entity>* Entity::cNetworkedPlayers;
		List_T<Entity>* Entity::cPlayers;
		List_T<Entity>* Entity::cAis;
		Dictionary_T<uint, Entity>* Entity::cPlayerGUIDS;
		Entity::SSpawnDelegate* Entity::SSpawn;
		Entity::CSpawnDelegate* Entity::CSpawn;
		Entity* Entity::self;
		void Entity::addOnLocalPlayerChange(Entity::OnLocalPlayerChangedAction* value){
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction = Entity::OnLocalPlayerChange;
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction2;
			do{
				onLocalPlayerChangedAction2 = onLocalPlayerChangedAction;
				Entity::OnLocalPlayerChangedAction* value2 = (Entity::OnLocalPlayerChangedAction*)(Delegate::Combine(onLocalPlayerChangedAction2, value));
				onLocalPlayerChangedAction = Interlocked::CompareExchange<Entity::OnLocalPlayerChangedAction*>(Entity::OnLocalPlayerChange, value2, onLocalPlayerChangedAction2);
			}
			while (*onLocalPlayerChangedAction != *onLocalPlayerChangedAction2);
		}
		void Entity::removeOnLocalPlayerChange(Entity::OnLocalPlayerChangedAction* value)
		{
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction = Entity::OnLocalPlayerChange;
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction2;
			do {
				onLocalPlayerChangedAction2 = onLocalPlayerChangedAction;
				Entity::OnLocalPlayerChangedAction* value2 = (Entity::OnLocalPlayerChangedAction*)(Delegate::Remove(onLocalPlayerChangedAction2, value));
				onLocalPlayerChangedAction = Interlocked::CompareExchange<Entity::OnLocalPlayerChangedAction*>(Entity::OnLocalPlayerChange, value2, onLocalPlayerChangedAction2);
			}
			while (*onLocalPlayerChangedAction != *onLocalPlayerChangedAction2);
		}

		void Entity::addOnSNetworkedPlayerAdded(Entity::OnLocalPlayerChangedAction* value)
		{
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction = Entity::OnSNetworkedPlayerAdded;
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction2;
			do {
				onLocalPlayerChangedAction2 = onLocalPlayerChangedAction;
				Entity::OnLocalPlayerChangedAction* value2 = (Entity::OnLocalPlayerChangedAction*)(Delegate::Combine(onLocalPlayerChangedAction2, value));
				onLocalPlayerChangedAction = Interlocked::CompareExchange<Entity::OnLocalPlayerChangedAction*>(Entity::OnSNetworkedPlayerAdded, value2, onLocalPlayerChangedAction2);
			}
			while (*onLocalPlayerChangedAction != *onLocalPlayerChangedAction2);
		}
		void Entity::removeOnSNetworkedPlayerAdded(Entity::OnLocalPlayerChangedAction* value)
		{
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction = Entity::OnSNetworkedPlayerAdded;
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction2;
			do {
				onLocalPlayerChangedAction2 = onLocalPlayerChangedAction;
				Entity::OnLocalPlayerChangedAction* value2 = (Entity::OnLocalPlayerChangedAction*)(Delegate::Remove(onLocalPlayerChangedAction2, value));
				onLocalPlayerChangedAction = Interlocked::CompareExchange<Entity::OnLocalPlayerChangedAction*>(Entity::OnSNetworkedPlayerAdded, value2, onLocalPlayerChangedAction2);
			}
			while (*onLocalPlayerChangedAction != *onLocalPlayerChangedAction2);
		}

		void Entity::addOnSNetworkedPlayerRemoved(Entity::OnLocalPlayerChangedAction* value)
		{
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction = Entity::OnSNetworkedPlayerRemoved;
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction2;
			do {
				onLocalPlayerChangedAction2 = onLocalPlayerChangedAction;
				Entity::OnLocalPlayerChangedAction* value2 = (Entity::OnLocalPlayerChangedAction*)(Delegate::Combine(onLocalPlayerChangedAction2, value));
				onLocalPlayerChangedAction = Interlocked::CompareExchange<Entity::OnLocalPlayerChangedAction*>(Entity::OnSNetworkedPlayerRemoved, value2, onLocalPlayerChangedAction2);
			}
			while (*onLocalPlayerChangedAction != *onLocalPlayerChangedAction2);
		}
		void Entity::removeOnSNetworkedPlayerRemoved(Entity::OnLocalPlayerChangedAction* value)
		{
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction = Entity::OnSNetworkedPlayerRemoved;
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction2;
			do {
				onLocalPlayerChangedAction2 = onLocalPlayerChangedAction;
				Entity::OnLocalPlayerChangedAction* value2 = (Entity::OnLocalPlayerChangedAction*)(Delegate::Remove(onLocalPlayerChangedAction2, value));
				onLocalPlayerChangedAction = Interlocked::CompareExchange<Entity::OnLocalPlayerChangedAction*>(Entity::OnSNetworkedPlayerRemoved, value2, onLocalPlayerChangedAction2);
			}
			while (*onLocalPlayerChangedAction != *onLocalPlayerChangedAction2);
		}

		void Entity::addOnSAiPlayerAdded(Entity::OnLocalPlayerChangedAction* value)
		{
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction = Entity::OnSAiPlayerAdded;
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction2;
			do {
				onLocalPlayerChangedAction2 = onLocalPlayerChangedAction;
				Entity::OnLocalPlayerChangedAction* value2 = (Entity::OnLocalPlayerChangedAction*)(Delegate::Combine(onLocalPlayerChangedAction2, value));
				onLocalPlayerChangedAction = Interlocked::CompareExchange<Entity::OnLocalPlayerChangedAction*>(Entity::OnSAiPlayerAdded, value2, onLocalPlayerChangedAction2);
			}
			while (*onLocalPlayerChangedAction != *onLocalPlayerChangedAction2);
		}
		void Entity::removeOnSAiPlayerAdded(Entity::OnLocalPlayerChangedAction* value)
		{
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction = Entity::OnSAiPlayerAdded;
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction2;
			do {
				onLocalPlayerChangedAction2 = onLocalPlayerChangedAction;
				Entity::OnLocalPlayerChangedAction* value2 = (Entity::OnLocalPlayerChangedAction*)(Delegate::Remove(onLocalPlayerChangedAction2, value));
				onLocalPlayerChangedAction = Interlocked::CompareExchange<Entity::OnLocalPlayerChangedAction*>(Entity::OnSAiPlayerAdded, value2, onLocalPlayerChangedAction2);
			}
			while (*onLocalPlayerChangedAction != *onLocalPlayerChangedAction2);
		}

		void Entity::addOnSAiPlayerRemoved(Entity::OnLocalPlayerChangedAction* value)
		{
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction = Entity::OnSAiPlayerRemoved;
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction2;
			do {
				onLocalPlayerChangedAction2 = onLocalPlayerChangedAction;
				Entity::OnLocalPlayerChangedAction* value2 = (Entity::OnLocalPlayerChangedAction*)(Delegate::Combine(onLocalPlayerChangedAction2, value));
				onLocalPlayerChangedAction = Interlocked::CompareExchange<Entity::OnLocalPlayerChangedAction*>(Entity::OnSAiPlayerRemoved, value2, onLocalPlayerChangedAction2);
			}
			while (*onLocalPlayerChangedAction != *onLocalPlayerChangedAction2);
		}
		void Entity::removeOnSAiPlayerRemoved(Entity::OnLocalPlayerChangedAction* value)
		{
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction = Entity::OnSAiPlayerRemoved;
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction2;
			do {
				onLocalPlayerChangedAction2 = onLocalPlayerChangedAction;
				Entity::OnLocalPlayerChangedAction* value2 = (Entity::OnLocalPlayerChangedAction*)(Delegate::Remove(onLocalPlayerChangedAction2, value));
				onLocalPlayerChangedAction = Interlocked::CompareExchange<Entity::OnLocalPlayerChangedAction*>(Entity::OnSAiPlayerRemoved, value2, onLocalPlayerChangedAction2);
			}
			while (*onLocalPlayerChangedAction != *onLocalPlayerChangedAction2);
		}

		void Entity::addOnSPlayerAdded(Entity::OnLocalPlayerChangedAction* value)
		{
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction = Entity::OnSPlayerAdded;
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction2;
			do {
				onLocalPlayerChangedAction2 = onLocalPlayerChangedAction;
				Entity::OnLocalPlayerChangedAction* value2 = (Entity::OnLocalPlayerChangedAction*)(Delegate::Combine(onLocalPlayerChangedAction2, value));
				onLocalPlayerChangedAction = Interlocked::CompareExchange<Entity::OnLocalPlayerChangedAction*>(Entity::OnSPlayerAdded, value2, onLocalPlayerChangedAction2);
			}
			while (*onLocalPlayerChangedAction != *onLocalPlayerChangedAction2);
		}
		void Entity::removeOnSPlayerAdded(Entity::OnLocalPlayerChangedAction* value)
		{
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction = Entity::OnSPlayerAdded;
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction2;
			do {
				onLocalPlayerChangedAction2 = onLocalPlayerChangedAction;
				Entity::OnLocalPlayerChangedAction* value2 = (Entity::OnLocalPlayerChangedAction*)(Delegate::Remove(onLocalPlayerChangedAction2, value));
				onLocalPlayerChangedAction = Interlocked::CompareExchange<Entity::OnLocalPlayerChangedAction*>(Entity::OnSPlayerAdded, value2, onLocalPlayerChangedAction2);
			}
			while (*onLocalPlayerChangedAction != *onLocalPlayerChangedAction2);
		}

		void Entity::addOnCNetworkedPlayerAdded(Entity::OnLocalPlayerChangedAction* value)
		{
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction = Entity::OnCNetworkedPlayerAdded;
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction2;
			do {
				onLocalPlayerChangedAction2 = onLocalPlayerChangedAction;
				Entity::OnLocalPlayerChangedAction* value2 = (Entity::OnLocalPlayerChangedAction*)(Delegate::Combine(onLocalPlayerChangedAction2, value));
				onLocalPlayerChangedAction = Interlocked::CompareExchange<Entity::OnLocalPlayerChangedAction*>(Entity::OnCNetworkedPlayerAdded, value2, onLocalPlayerChangedAction2);
			}
			while (*onLocalPlayerChangedAction != *onLocalPlayerChangedAction2);
		}
		void Entity::removeOnCNetworkedPlayerAdded(Entity::OnLocalPlayerChangedAction* value)
		{
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction = Entity::OnCNetworkedPlayerAdded;
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction2;
			do {
				onLocalPlayerChangedAction2 = onLocalPlayerChangedAction;
				Entity::OnLocalPlayerChangedAction* value2 = (Entity::OnLocalPlayerChangedAction*)(Delegate::Remove(onLocalPlayerChangedAction2, value));
				onLocalPlayerChangedAction = Interlocked::CompareExchange<Entity::OnLocalPlayerChangedAction*>(Entity::OnCNetworkedPlayerAdded, value2, onLocalPlayerChangedAction2);
			}
			while (*onLocalPlayerChangedAction != *onLocalPlayerChangedAction2);
		}

		void Entity::addOnCNetworkedPlayerRemoved(Entity::OnLocalPlayerChangedAction* value)
		{
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction = Entity::OnCNetworkedPlayerRemoved;
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction2;
			do {
				onLocalPlayerChangedAction2 = onLocalPlayerChangedAction;
				Entity::OnLocalPlayerChangedAction* value2 = (Entity::OnLocalPlayerChangedAction*)(Delegate::Combine(onLocalPlayerChangedAction2, value));
				onLocalPlayerChangedAction = Interlocked::CompareExchange<Entity::OnLocalPlayerChangedAction*>(Entity::OnCNetworkedPlayerRemoved, value2, onLocalPlayerChangedAction2);
			}
			while (*onLocalPlayerChangedAction != *onLocalPlayerChangedAction2);
		}
		void Entity::removeOnCNetworkedPlayerRemoved(Entity::OnLocalPlayerChangedAction* value)
		{
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction = Entity::OnCNetworkedPlayerRemoved;
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction2;
			do {
				onLocalPlayerChangedAction2 = onLocalPlayerChangedAction;
				Entity::OnLocalPlayerChangedAction* value2 = (Entity::OnLocalPlayerChangedAction*)(Delegate::Remove(onLocalPlayerChangedAction2, value));
				onLocalPlayerChangedAction = Interlocked::CompareExchange<Entity::OnLocalPlayerChangedAction*>(Entity::OnCNetworkedPlayerRemoved, value2, onLocalPlayerChangedAction2);
			}
			while (*onLocalPlayerChangedAction != *onLocalPlayerChangedAction2);
		}

		void Entity::addOnCAiPlayerAdded(Entity::OnLocalPlayerChangedAction* value)
		{
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction = Entity::OnCAiPlayerAdded;
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction2;
			do {
				onLocalPlayerChangedAction2 = onLocalPlayerChangedAction;
				Entity::OnLocalPlayerChangedAction* value2 = (Entity::OnLocalPlayerChangedAction*)(Delegate::Combine(onLocalPlayerChangedAction2, value));
				onLocalPlayerChangedAction = Interlocked::CompareExchange<Entity::OnLocalPlayerChangedAction*>(Entity::OnCAiPlayerAdded, value2, onLocalPlayerChangedAction2);
			}
			while (*onLocalPlayerChangedAction != *onLocalPlayerChangedAction2);
		}
		void Entity::removeOnCAiPlayerAdded(Entity::OnLocalPlayerChangedAction* value)
		{
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction = Entity::OnCAiPlayerAdded;
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction2;
			do {
				onLocalPlayerChangedAction2 = onLocalPlayerChangedAction;
				Entity::OnLocalPlayerChangedAction* value2 = (Entity::OnLocalPlayerChangedAction*)(Delegate::Remove(onLocalPlayerChangedAction2, value));
				onLocalPlayerChangedAction = Interlocked::CompareExchange<Entity::OnLocalPlayerChangedAction*>(Entity::OnCAiPlayerAdded, value2, onLocalPlayerChangedAction2);
			}
			while (*onLocalPlayerChangedAction != *onLocalPlayerChangedAction2);
		}

		void Entity::addOnCAiPlayerRemoved(Entity::OnLocalPlayerChangedAction* value)
		{
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction = Entity::OnCAiPlayerRemoved;
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction2;
			do {
				onLocalPlayerChangedAction2 = onLocalPlayerChangedAction;
				Entity::OnLocalPlayerChangedAction* value2 = (Entity::OnLocalPlayerChangedAction*)(Delegate::Combine(onLocalPlayerChangedAction2, value));
				onLocalPlayerChangedAction = Interlocked::CompareExchange<Entity::OnLocalPlayerChangedAction*>(Entity::OnCAiPlayerRemoved, value2, onLocalPlayerChangedAction2);
			}
			while (*onLocalPlayerChangedAction != *onLocalPlayerChangedAction2);
		}
		void Entity::removeOnCAiPlayerRemoved(Entity::OnLocalPlayerChangedAction* value)
		{
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction = Entity::OnCAiPlayerRemoved;
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction2;
			do {
				onLocalPlayerChangedAction2 = onLocalPlayerChangedAction;
				Entity::OnLocalPlayerChangedAction* value2 = (Entity::OnLocalPlayerChangedAction*)(Delegate::Remove(onLocalPlayerChangedAction2, value));
				onLocalPlayerChangedAction = Interlocked::CompareExchange<Entity::OnLocalPlayerChangedAction*>(Entity::OnCAiPlayerRemoved, value2, onLocalPlayerChangedAction2);
			}
			while (*onLocalPlayerChangedAction != *onLocalPlayerChangedAction2);
		}

		void Entity::addOnCPlayerAdded(Entity::OnLocalPlayerChangedAction* value)
		{
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction = Entity::OnCPlayerAdded;
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction2;
			do {
				onLocalPlayerChangedAction2 = onLocalPlayerChangedAction;
				Entity::OnLocalPlayerChangedAction* value2 = (Entity::OnLocalPlayerChangedAction*)(Delegate::Combine(onLocalPlayerChangedAction2, value));
				onLocalPlayerChangedAction = Interlocked::CompareExchange<Entity::OnLocalPlayerChangedAction*>(Entity::OnCPlayerAdded, value2, onLocalPlayerChangedAction2);
			}
			while (*onLocalPlayerChangedAction != *onLocalPlayerChangedAction2);
		}
		void Entity::removeOnCPlayerAdded(Entity::OnLocalPlayerChangedAction* value)
		{
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction = Entity::OnCPlayerAdded;
			Entity::OnLocalPlayerChangedAction* onLocalPlayerChangedAction2;
			do {
				onLocalPlayerChangedAction2 = onLocalPlayerChangedAction;
				Entity::OnLocalPlayerChangedAction* value2 = (Entity::OnLocalPlayerChangedAction*)(Delegate::Remove(onLocalPlayerChangedAction2, value));
				onLocalPlayerChangedAction = Interlocked::CompareExchange<Entity::OnLocalPlayerChangedAction*>(Entity::OnCPlayerAdded, value2, onLocalPlayerChangedAction2);
			}
			while (*onLocalPlayerChangedAction != *onLocalPlayerChangedAction2);
		}

		Entity* Entity::getLocalPlayer()
		{
			return Entity::localPlayer;
		}
		List_T<Entity>* Entity::getSNetworkedPlayers()
		{
			return Entity::sNetworkedPlayers;
		}
		List_T<Entity>* Entity::getSPlayers()
		{
			return Entity::sPlayers;
		}
		List_T<Entity>* Entity::getSAis()
		{
			return Entity::sAis;
		}
		Dictionary_T<uint, Entity>* Entity::getSPlayerGUIDS()
		{
			return Entity::sPlayerGUIDS;
		}
		List_T<Entity>* Entity::getCNetworkedPlayers()
		{
			return Entity::cNetworkedPlayers;
		}
		List_T<Entity>* Entity::getCPlayers()
		{
			return Entity::cPlayers;
		}
		List_T<Entity>* Entity::getCAis()
		{
			return Entity::cAis;
		}
		Dictionary_T<uint, Entity>* Entity::getCPlayerGUIDS()
		{
			return Entity::cPlayerGUIDS;
		}
		Entity::Entity()
		{
			Entity::nextEntityGUID = 1u;
			Entity::sPlayers = new List_T<Entity>();
			Entity::sAis = new List_T<Entity>();
			Entity::sNetworkedPlayers = new List_T<Entity>();
			Entity::sPlayerGUIDS = new Dictionary_T<uint, Entity>();
			Entity::cPlayers = new List_T<Entity>();
			Entity::cAis = new List_T<Entity>();
			Entity::cNetworkedPlayers = new List_T<Entity>();
			Entity::cPlayerGUIDS = new Dictionary_T<uint, Entity>();
		}
		void Entity::RegisterLocalPlayer(uint playerGUID, Entity* lp)
		{
			Entity::localPlayer = lp;
			Entity::SRegisterPlayer(playerGUID, lp);
			Entity::CRegisterPlayer(playerGUID, lp);
			if (Entity::OnLocalPlayerChange != null) {
				DELEGATE_INVOKE(Entity::OnLocalPlayerChange, lp);
			}
		}
		void Entity::SRegisterAIPlayer(uint playerGUID, Entity* lp)
		{
			Entity::sAis->Add(lp);
			Entity::SRegisterPlayer(playerGUID, lp);
			if (Entity::OnSAiPlayerAdded != null) {
				DELEGATE_INVOKE(Entity::OnSAiPlayerAdded, lp);
			}
		}
		void Entity::SRegisterNetworkedPlayer(uint playerGUID, Entity* lp)
		{
			Entity::sNetworkedPlayers->Add(lp);
			Entity::SRegisterPlayer(playerGUID, lp);
			if (Entity::OnSNetworkedPlayerAdded != null) {
				DELEGATE_INVOKE(Entity::OnSNetworkedPlayerAdded, lp);
			}
		}
		void Entity::SRegisterPlayer(uint PlayerGUID, Entity* player)
		{
			if (Entity::sPlayerGUIDS->ContainsKey(PlayerGUID)) {
				Debug::LogWarning(new String("SRegisterPlayer already containt player! FIX"));
				return;
			}
			Entity::sPlayers->Add(player);
			Entity::sPlayerGUIDS->Add(PlayerGUID, player);
			if (Entity::OnSPlayerAdded != null) {
				DELEGATE_INVOKE(Entity::OnSPlayerAdded, player);
			}
		}
		void Entity::CRegisterAIPlayer(uint playerGUID, Entity* lp)
		{
			Entity::cAis->Add(lp);
			Entity::CRegisterPlayer(playerGUID, lp);
			if (Entity::OnCAiPlayerAdded != null) {
				DELEGATE_INVOKE(Entity::OnCAiPlayerAdded, lp);
			}
		}
		void Entity::CRegisterNetworkedPlayer(uint playerGUID, Entity* lp)
		{
			Entity::cNetworkedPlayers->Add(lp);
			Entity::CRegisterPlayer(playerGUID, lp);
			if (Entity::OnCNetworkedPlayerAdded != null) {
				DELEGATE_INVOKE(Entity::OnCNetworkedPlayerAdded, lp);
			}
		}
		void Entity::CRegisterPlayer(uint playerGUID, Entity* player)
		{
			Entity::cPlayers->Add(player);
			Entity::cPlayerGUIDS->Add(playerGUID, player);
			if (Entity::OnCPlayerAdded != null) {
				DELEGATE_INVOKE(Entity::OnCPlayerAdded, player);
			}
		}
		void Entity::UnRegisterLocalPlayer(uint playerGUID)
		{
			Entity::SUnRegisterPlayer(playerGUID, Entity::getLocalPlayer());
			Entity::CUnRegisterPlayer(playerGUID, Entity::getLocalPlayer());
			Entity::localPlayer = null;
			if (Entity::OnLocalPlayerChange != null) {
				DELEGATE_INVOKE(Entity::OnLocalPlayerChange, null);
			}
		}
		void Entity::SUnregisterNetworkedPlayer(uint playerGUID, Entity* player)
		{
			Entity::sNetworkedPlayers->Remove(player);
			Entity::SUnRegisterPlayer(playerGUID, player);
			if (Entity::OnSNetworkedPlayerRemoved != null) {
				DELEGATE_INVOKE(Entity::OnSNetworkedPlayerRemoved, player);
			}
		}
		void Entity::SUnregisterAIPlayer(uint playerGUID, Entity* player)
		{
			Entity::sAis->Remove(player);
			Entity::SUnRegisterPlayer(playerGUID, player);
			if (Entity::OnSAiPlayerRemoved != null) {
				DELEGATE_INVOKE(Entity::OnSAiPlayerRemoved, player);
			}
		}
		void Entity::SUnRegisterPlayer(uint playerGUID, Entity* player)
		{
			Entity::sPlayers->Remove(player);
			Entity::sPlayerGUIDS->Remove(playerGUID);
		}
		void Entity::CUnregisterNetworkedPlayer(uint playerGUID, Entity* player)
		{
			Entity::cNetworkedPlayers->Remove(player);
			Entity::CUnRegisterPlayer(playerGUID, player);
			if (Entity::OnCNetworkedPlayerRemoved != null) {
				DELEGATE_INVOKE(Entity::OnCNetworkedPlayerRemoved, player);
			}
		}
		void Entity::CUnregisterAIPlayer(uint playerGUID, Entity* player)
		{
			Entity::cAis->Remove(player);
			Entity::CUnRegisterPlayer(playerGUID, player);
			if (Entity::OnCAiPlayerRemoved != null) {
				DELEGATE_INVOKE(Entity::OnCAiPlayerRemoved, player);
			}
		}
		void Entity::CUnRegisterPlayer(uint playerGUID, Entity* player)
		{
			Entity::cPlayers->Remove(player);
			Entity::cPlayerGUIDS->Remove(playerGUID);
		}
		void Entity::RegisterOnLocalPlayerChange(Entity::OnLocalPlayerChangedAction* action)
		{
			if (Entity::localPlayer != null) {
				action(Entity::localPlayer);
			}
			Entity::OnLocalPlayerChange += action;
		}
		Entity* Entity::SGetPLayerWithGUID(uint guid)
		{
			if (Entity::sPlayerGUIDS->ContainsKey(guid)) {
				return Entity::sPlayerGUIDS->GetData(guid);
			}
			return null;
		}
		Entity* Entity::CGetPLayerWithGUID(uint guid)
		{
			if (Entity::cPlayerGUIDS->ContainsKey(guid)) {
				return Entity::cPlayerGUIDS->GetData(guid);
			}
			return null;
		}
		uint Entity::GetNextEntityGUID()
		{
			return Entity::nextEntityGUID++;
		}

	}
}
