#pragma once
#include <System/System.h>
#include "CharacterSpells.h"
#include <System/Collections/Generic/List.h>
#include "ItemDataLoader.h"
#include "WorldEntity.h"
#include "Character.h"
#include "Spells.h"
#include "Spell.h"
#include "SpellMgr.h"
#include "PlayerStates.h"
#include "ItemData.h"
#include "CxNet.h"
#include "SSpellCastRequestMsg.h"
#include "SItemSpellCastRequestMsg.h"
#include "CSpellCastEventSuccessMsg.h"
#include "CSpellCastEventFailedMsg.h"
#include "BrokenSeals.h"

using namespace System;
using namespace UnityEngine;
using namespace System::Collections::Generic;
using namespace BS::Data::Items;
using namespace BS::Player;
using namespace CxNetworking;
using namespace BS::Networking;
//Forward Declaration
class WorldEntity;

//Attribute: Serializable*
class SpellMgrComponent : public virtual Object{
	//Attribute: SerializeField*
	private:
		CharacterSpells* spellIds;
	//Attribute: SerializeField*
	private:
		List_T<int>* mobSpellIds;
	//Attribute: SerializeField*
	private:
		ItemDataLoader* itemDataLoader;
	private:
		bool init;
	private:
		bool eventAdded;
	private:
		int lastLevel;
	private:
		bool dataPresent;
	private:
		WorldEntity* owner;
	public:
		SpellMgrComponent(WorldEntity* owner);
	public:
		void Init();
	private:
		void OnLevelLoaded();
	public:
		void CSendCastSpellRequest(int spellId);
	public:
		void CSendCastItemSpellRequest(ItemData* itemData);
	private:
		void CSendCastSpell(int spellId);
	private:
		void CSendCastItemSpell(int itemId);
	public:
		void SSendSpellCastSuccess(int spellId);
	public:
		void SSendSpellCastFailed(int spellId);
	public:
		void CReceiveSpellCastSuccess(int spellId);
	public:
		void CReceiveSpellSpellCastFailed(int spellId);
	public:
		void SReceiveCastSpellRequest(int spellId);
	public:
		void SReceiveCastItemSpellRequest(int itemId);
	public:
		void SCastSpell(int spellId);
	public:
		void AICastSpell(int spellId);
	public:
		bool PlayerKnowsSpell(int spellID);
};
