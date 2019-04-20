#pragma once
#include <System/System.h>
#include "AuraScript.h"
#include "Aura.h"
#include "WorldEntity.h"
#include "AuraData.h"
#include "DamagePipelineData.h"
#include "EffectPoints.h"
#include "Quaternion.h"
#include "GenericAuraAttributeHelper.h"

using namespace UnityEngine;
using namespace BS::Player;
using namespace System;
namespace BS {
	namespace AurasNS {
		namespace Generic {
			//Forward Declaration
			class AuraScript;

			class GenericAura : public virtual AuraScript, public virtual Object{
				//Attribute: SerializeField*
				private:
					bool hasModifiers;
				public:
					GenericAura(Aura* aura);
				public:
				virtual void Apply(WorldEntity* caster, WorldEntity* target, float spellScale);
				public:
				virtual void DeApply(WorldEntity* target, AuraData* data);
				public:
				virtual bool AuraUpdate(WorldEntity* target, AuraData* data);
				public:
				virtual void POnBeforeDamage(DamagePipelineData* data, AuraData* auraData);
				public:
				virtual void COnAdded(WorldEntity* target, Aura* data, AuraData* auraData);
				public:
				virtual void COnRemoved(WorldEntity* target, Aura* data);
				private:
					void ApplyEffect(WorldEntity* target);
				private:
					void RemoveEffect(WorldEntity* target);
				private:
					void ApplyModifiers(WorldEntity* target);
				private:
					void RemoveModifiers(WorldEntity* target);
			};
		}
	}
}
