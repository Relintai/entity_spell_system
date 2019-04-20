#pragma once
#include <System/System.h>
#include "WorldEntity.h"
#include "CxNet.h"
#include "SSendTeamMsg.h"
#include "JsonWriter.h"
#include "JsonReader.h"
#include "JsonToken.h"

using namespace System;
using namespace UnityEngine;
using namespace CxNetworking;
using namespace BS::Networking;
using namespace Newtonsoft::Json;
namespace BS {
	namespace Player {
		//Forward Declaration
		class WorldEntity;

		//Attribute: Serializable*
		class FactionComponent : public virtual Object{
			public:
				int NONE;
			public:
				int TEAM_RED;
			public:
				int TEAM_BLUE;
			public:
				int PLAYER;
			public:
				int MOB;
			//Attribute: SerializeField*
			private:
				int sTeam;
			//Attribute: SerializeField*
			private:
				int cTeam;
			//Attribute: SerializeField*
			private:
				bool send;
			private:
				WorldEntity* owner;
			public:
				bool getSend();
			public:
				void setSend(bool value);
			public:
				int getSTeam();
			public:
				void setSTeam(int value);
			public:
				int getCTeam();
			public:
				void setCTeam(int value);
			public:
				FactionComponent(WorldEntity* owner);
			public:
				void Update();
			public:
				void SSendTeam(int team);
			public:
				void CReceiveSSendTeam(int team);
			public:
				bool SIsEnemy(WorldEntity* player);
			public:
				bool CIsEnemy(WorldEntity* player);
			public:
				void ToJSON(JsonWriter* w);
			public:
				void FromJSON(JsonReader* r);
		};
	}
}
