#pragma once
#include <System/System.h>
#include "PlayerSpellData.h"
#include "PlayerSpellDataComponent.h"
#include "Time.h"
#include "JsonWriter.h"
#include "JsonReader.h"
#include "JsonToken.h"

using namespace UnityEngine;
using namespace Newtonsoft::Json;
using namespace System;
//Forward Declaration
class PlayerSpellData;

class PlayerSpellCooldownData : public virtual PlayerSpellData, public virtual Object{
	private:
		float cooldown;
	private:
		float remainingCooldown;
	public:
		float getCooldown();
	public:
		void setCooldown(float value);
	public:
		float getRemainingCooldown();
	public:
		void setRemainingCooldown(float value);
	public:
		PlayerSpellCooldownData();
	public:
		PlayerSpellCooldownData(int spellId, float cooldown, float remainingCooldown);
	public:
	virtual void Update(PlayerSpellDataComponent* psdc);
	public:
	virtual void Serialize(JsonWriter* w);
	public:
	static void ToJSON(PlayerSpellCooldownData* psdc, JsonWriter* w);
	public:
	static void FromJSON(PlayerSpellCooldownData* psdc, JsonReader* r);
};
