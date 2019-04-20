#include "StateComponent.h"
//Delegate declaration moved to header file
//Delegate declaration moved to header file
void StateComponent::addsOnStateChanged(StateComponent::SOnStateChangedAction* value){
	StateComponent::SOnStateChangedAction* sOnStateChangedAction = this->sOnStateChanged;
	StateComponent::SOnStateChangedAction* sOnStateChangedAction2;
	do{
		sOnStateChangedAction2 = sOnStateChangedAction;
		StateComponent::SOnStateChangedAction* value2 = (StateComponent::SOnStateChangedAction*)(Delegate::Combine(sOnStateChangedAction2, value));
		sOnStateChangedAction = Interlocked::CompareExchange<StateComponent::SOnStateChangedAction*>(this->sOnStateChanged, value2, sOnStateChangedAction2);
	}
	while (*sOnStateChangedAction != *sOnStateChangedAction2);
}
void StateComponent::removesOnStateChanged(StateComponent::SOnStateChangedAction* value)
{
	StateComponent::SOnStateChangedAction* sOnStateChangedAction = this->sOnStateChanged;
	StateComponent::SOnStateChangedAction* sOnStateChangedAction2;
	do {
		sOnStateChangedAction2 = sOnStateChangedAction;
		StateComponent::SOnStateChangedAction* value2 = (StateComponent::SOnStateChangedAction*)(Delegate::Remove(sOnStateChangedAction2, value));
		sOnStateChangedAction = Interlocked::CompareExchange<StateComponent::SOnStateChangedAction*>(this->sOnStateChanged, value2, sOnStateChangedAction2);
	}
	while (*sOnStateChangedAction != *sOnStateChangedAction2);
}

void StateComponent::addCOnStateChanged(StateComponent::COnStateChangedAction* value)
{
	StateComponent::COnStateChangedAction* cOnStateChangedAction = this->COnStateChanged;
	StateComponent::COnStateChangedAction* cOnStateChangedAction2;
	do {
		cOnStateChangedAction2 = cOnStateChangedAction;
		StateComponent::COnStateChangedAction* value2 = (StateComponent::COnStateChangedAction*)(Delegate::Combine(cOnStateChangedAction2, value));
		cOnStateChangedAction = Interlocked::CompareExchange<StateComponent::COnStateChangedAction*>(this->COnStateChanged, value2, cOnStateChangedAction2);
	}
	while (*cOnStateChangedAction != *cOnStateChangedAction2);
}
void StateComponent::removeCOnStateChanged(StateComponent::COnStateChangedAction* value)
{
	StateComponent::COnStateChangedAction* cOnStateChangedAction = this->COnStateChanged;
	StateComponent::COnStateChangedAction* cOnStateChangedAction2;
	do {
		cOnStateChangedAction2 = cOnStateChangedAction;
		StateComponent::COnStateChangedAction* value2 = (StateComponent::COnStateChangedAction*)(Delegate::Remove(cOnStateChangedAction2, value));
		cOnStateChangedAction = Interlocked::CompareExchange<StateComponent::COnStateChangedAction*>(this->COnStateChanged, value2, cOnStateChangedAction2);
	}
	while (*cOnStateChangedAction != *cOnStateChangedAction2);
}

bool StateComponent::getSend()
{
	return this->send;
}
void StateComponent::setSend(bool value)
{
	this->send = value;
}
List_T<StateData>* StateComponent::getActiveStates()
{
	return this->activeStates;
}
int StateComponent::getSStateFlags()
{
	return this->sStateFlags;
}
void StateComponent::setSStateFlags(int value)
{
	this->sStateFlags = value;
}
int StateComponent::getCStateFlags()
{
	return this->cStateFlags;
}
StateComponent::StateComponent(WorldEntity* owner)
{
	activeStates = new List_T<StateData>();
	this->owner = owner;
}
void StateComponent::Update()
{
	if (this->send) {
		this->send = false;
		this->SSendSendFlags(this->sStateFlags);
	}
}
void StateComponent::AddState(int auraId, StateData::StateType type)
{
	if (!CxNet::IsServer) {
		return;
	}
	StateData* state = new StateData(type, auraId);
	this->AddState(state);
	int arg_29_0 = this->sStateFlags;
	this->RecalculateFlags();
	if (arg_29_0 != this->sStateFlags) {
		if (this->sOnStateChanged != null) {
			DELEGATE_INVOKE(this->sOnStateChanged);
		}
		this->SSendSendFlags(this->sStateFlags);
	}
}
bool StateComponent::SHasState(StateData::StateType state)
{
	return (this->sStateFlags & (int)(state)) == (int)(state);
}
bool StateComponent::CHasState(StateData::StateType state)
{
	return (this->cStateFlags & (int)(state)) == (int)(state);
}
void StateComponent::AddState(StateData* state)
{
	if (!CxNet::IsServer) {
		return;
	}
	this->activeStates->Add(state);
	int arg_26_0 = this->sStateFlags;
	this->RecalculateFlags();
	if (arg_26_0 != this->sStateFlags) {
		if (this->sOnStateChanged != null) {
			DELEGATE_INVOKE(this->sOnStateChanged);
		}
		this->SSendSendFlags(this->sStateFlags);
	}
}
void StateComponent::RemoveStateWithAuraId(int auraId)
{
	for (int i = 0; i < this->activeStates->Count; i += 1) {
		if (this->activeStates->GetData(i)->AuraId == auraId) {
			this->activeStates->RemoveAt(i);
			int arg_36_0 = this->sStateFlags;
			this->RecalculateFlags();
			if (arg_36_0 != this->sStateFlags) {
				if (this->sOnStateChanged != null) {
					DELEGATE_INVOKE(this->sOnStateChanged);
				}
				this->SSendSendFlags(this->sStateFlags);
			}
			return;
		}
	}
}
void StateComponent::RemoveStateWithAuraId(int auraId, StateData::StateType type)
{
	for (int i = 0; i < this->activeStates->Count; i += 1) {
		if ((this->activeStates->GetData(i)->AuraId == auraId) && (this->activeStates->GetData(i)->Type == type)) {
			this->activeStates->RemoveAt(i);
			int arg_4A_0 = this->sStateFlags;
			this->RecalculateFlags();
			if (arg_4A_0 != this->sStateFlags) {
				if (this->sOnStateChanged != null) {
					DELEGATE_INVOKE(this->sOnStateChanged);
				}
				this->SSendSendFlags(this->sStateFlags);
			}
			return;
		}
	}
}
void StateComponent::RecalculateFlags()
{
	this->sStateFlags = 0;
	for (int i = 0; i < this->activeStates->Count; i += 1) {
		this->sStateFlags = this->sStateFlags | (int)(this->activeStates->GetData(i)->Type);
	}
}
void StateComponent::SSendSendFlags(int flags)
{
	if (CxNet::IsServer) {
		SSendStateFlagsMsg sSendStateFlagsMsg = SSendStateFlagsMsg();
		sSendStateFlagsMsg.Guid = this->owner->PlayerData->GUID;
		sSendStateFlagsMsg.Flags = flags;
		sSendStateFlagsMsg.Serialize(CxNet::NetBuffer);
		CxNet::SendBufferToAllClients(0);
	}
}
void StateComponent::CReceiveSendFlags(int flags)
{
	this->cStateFlags = flags;
	if (this->COnStateChanged != null) {
		DELEGATE_INVOKE(this->COnStateChanged);
	}
}
void StateComponent::ToJSON(JsonWriter* w)
{
	w->WritePropertyName(new String("StateComponent"));
	w->WriteStartObject();
	w->WritePropertyName(new String("SStateFlags"));
	w->WriteValue(this->getSStateFlags());
	w->WritePropertyName(new String("States"));
	w->WriteStartObject();
	for (int i = 0; i < this->getActiveStates()->Count; i += 1) {
		StateData::ToJSON(this->getActiveStates()->GetData(i), w);
	}
	w->WriteEndObject();
	w->WriteEndObject();
}
void StateComponent::FromJSON(JsonReader* r)
{
	while (r->Read()) {
		if (r->TokenType == JsonToken::PropertyName) {
			String* a = (String*)(r->Value);
			if (!*a == *(new String("SStateFlags"))) {
				if (*a == *(new String("States"))) {
					this->StatesFromJSON(r);
				}
			}
			else {
				this->setSStateFlags(r->ReadAsInt32()->Value);
			}
		}
		else {
			if (r->TokenType == JsonToken::EndObject) {
				break;
			}
		}
	}
}
void StateComponent::StatesFromJSON(JsonReader* r)
{
	while (r->Read()) {
		if (r->TokenType == JsonToken::PropertyName) {
			String* a = (String*)(r->Value);
			if (*a == *(new String("StateData"))) {
				StateData* stateData = new StateData();
				StateData::FromJSON(stateData, r);
				this->getActiveStates()->Add(stateData);
			}
		}
		else {
			if (r->TokenType == JsonToken::EndObject) {
				break;
			}
		}
	}
	this->setSend(true);
}

