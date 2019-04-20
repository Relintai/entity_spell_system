#pragma once
#include <System/System.h>
#include "JsonWriter.h"
#include "JsonReader.h"
#include "JsonToken.h"

using namespace System;
using namespace Newtonsoft::Json;
class StateData : public virtual Object
{
	public:
	enum class StateType
	{
		TYPE_NONE,
		TYPE_STUN,
		TYPE_ROOT,
		TYPE_FROZEN = 4
	};
	private:
		StateData::StateType type;
	private:
		int auraId;
	public:
		StateData::StateType getType();
		//Ignored empty method declaration
	public:
		int getAuraId();
		//Ignored empty method declaration
	public:
		StateData();
	public:
		StateData(StateData::StateType type, int auraId);
	public:
	static void ToJSON(StateData* sd, JsonWriter* w);
	public:
	static void FromJSON(StateData* sd, JsonReader* r);
};
