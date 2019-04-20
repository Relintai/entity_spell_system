#pragma once
#include <System/System.h>
#include <System/Delegate.h>
#include "StateData.h"
#include <System/Collections/Generic/List.h>
#include "WorldEntity.h"
#include "Interlocked.h"
#include "CxNet.h"
#include "SSendStateFlagsMsg.h"
#include "JsonWriter.h"
#include "JsonReader.h"
#include "JsonToken.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace UnityEngine;
using namespace BS::Player;
using namespace System::Threading;
using namespace CxNetworking;
using namespace BS::Networking;
using namespace Newtonsoft::Json;
//Forward Declaration
class WorldEntity;

//Attribute: Serializable*
class StateComponent : public virtual Object{
	public:
		DELEGATE(void) SOnStateChangedAction;
	public:
		DELEGATE(void) COnStateChangedAction;
	//Attribute: SerializeField*
	private:
		List_T<StateData>* activeStates;
	//Attribute: SerializeField*
	private:
		int sStateFlags;
	//Attribute: SerializeField*
	private:
		int cStateFlags;
	//Attribute: SerializeField*
	private:
		bool send;
	private:
		WorldEntity* owner;
	public:
		void addsOnStateChanged(StateComponent::SOnStateChangedAction* value);
	public:
		void removesOnStateChanged(StateComponent::SOnStateChangedAction* value);
	public:
		void addCOnStateChanged(StateComponent::COnStateChangedAction* value);
	public:
		void removeCOnStateChanged(StateComponent::COnStateChangedAction* value);
	public:
		bool getSend();
	public:
		void setSend(bool value);
	public:
		List_T<StateData>* getActiveStates();
		//Ignored empty method declaration
	public:
		int getSStateFlags();
	public:
		void setSStateFlags(int value);
	public:
		int getCStateFlags();
		//Ignored empty method declaration
	public:
		StateComponent(WorldEntity* owner);
	public:
		void Update();
	public:
		void AddState(int auraId, StateData::StateType type);
	public:
		bool SHasState(StateData::StateType state);
	public:
		bool CHasState(StateData::StateType state);
	public:
		void AddState(StateData* state);
	public:
		void RemoveStateWithAuraId(int auraId);
	public:
		void RemoveStateWithAuraId(int auraId, StateData::StateType type);
	public:
		void RecalculateFlags();
	public:
		void SSendSendFlags(int flags);
	public:
		void CReceiveSendFlags(int flags);
	public:
		void ToJSON(JsonWriter* w);
	public:
		void FromJSON(JsonReader* r);
	public:
		void StatesFromJSON(JsonReader* r);
};
