#pragma once
#include <System/System.h>
#include "PlayerLocalSpellData.h"
#include "WorldEntity.h"
#include <System/Collections/Generic/List.h>
#include "TargetComponent.h"
#include "Vector3.h"
#include "RaycastHit.h"
#include "Physics.h"

using namespace System::Collections::Generic;
using namespace UnityEngine;
using namespace System;
namespace BS {
	namespace Player {
		class PlayerLocalTargetNextPrevSpellData : public virtual PlayerLocalSpellData, public virtual Object
		{
			private:
				List_T<WorldEntity>* enemyTargets;
			private:
				int enemyTargetindex;
			private:
				WorldEntity* owner;
			private:
				TargetComponent* tc;
			private:
				Vector3* direction;
			private:
				Array<RaycastHit>* rch;
			private:
				int LAYER;
			public:
				PlayerLocalTargetNextPrevSpellData(WorldEntity* owner);
			public:
				void Refresh();
			public:
				void TargetNextEnemy();
			public:
				void TargetPreviousEnemy();
		};
	}
}
