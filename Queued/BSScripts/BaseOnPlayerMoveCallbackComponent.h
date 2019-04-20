#pragma once
#include <System/System.h>
#include "Entity.h"
#include <System/Delegate.h>
#include "Interlocked.h"
#include <System/Collections/Generic/List.h>
#include "JsonWriter.h"
#include "JsonReader.h"

using namespace BS::Player;
using namespace System;
using namespace System::Threading;
using namespace System::Collections::Generic;
using namespace Newtonsoft::Json;
class BaseOnPlayerMoveCallbackComponent : public abstract virtual Object
{
	public:
		DELEGATE(void, Entity*) OnPlayerMoved;
	public:
		void addCOnPlayerMove(BaseOnPlayerMoveCallbackComponent::OnPlayerMoved* value);
	public:
		void removeCOnPlayerMove(BaseOnPlayerMoveCallbackComponent::OnPlayerMoved* value);
	public:
		void addSOnPlayerMove(BaseOnPlayerMoveCallbackComponent::OnPlayerMoved* value);
	public:
		void removeSOnPlayerMove(BaseOnPlayerMoveCallbackComponent::OnPlayerMoved* value);
	public:
		List_T<int>* getCSpells();
		//Ignored empty method declaration
	public:
		List_T<int>* getSSpells();
		//Ignored empty method declaration
	public:
		virtual void ServerCallbackAdded() = 0;
	public:
		virtual void RegisterCOnPlayerMove(BaseOnPlayerMoveCallbackComponent::OnPlayerMoved* callback, int spellId) = 0;
	public:
		virtual void RegisterSOnPlayerMove(BaseOnPlayerMoveCallbackComponent::OnPlayerMoved* callback, int spellId) = 0;
	public:
		virtual void RemoveCOnPlayerMove(BaseOnPlayerMoveCallbackComponent::OnPlayerMoved* callback, int spellId) = 0;
	public:
		virtual void RemoveSOnPlayerMove(BaseOnPlayerMoveCallbackComponent::OnPlayerMoved* callback, int spellId) = 0;
	public:
		virtual void ToJSON(JsonWriter* w) = 0;
	public:
		virtual void FromJSON(JsonReader* r) = 0;
	public:
		void CallCOnPlayerMove(Entity* player);
	public:
		void CallSOnPlayerMove(Entity* player);
	public:
		bool COnPlayerMoveIsNull();
	public:
		bool SOnPlayerMoveIsNull();
	public:
	virtual List_T<int>* CSpells_var;
	public:
	virtual List_T<int>* SSpells_var;
	public:
		BaseOnPlayerMoveCallbackComponent();
};
