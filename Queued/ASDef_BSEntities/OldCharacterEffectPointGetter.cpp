#include "OldCharacterEffectPointGetter.h"
namespace BS {
	namespace Player {
		void OldCharacterEffectPointGetter::Start(){
			this->pd = MonoBehaviour::GetComponent<PlayerData>();
			this->pd->OnWeaponChanged += new PlayerData::OnWeapomChangedAction(DELEGATE_FUNC(OldCharacterEffectPointGetter::OnWeaponChanged, _1));
			FOREACH(_TRANSFORM, MonoBehaviour::transform){
				Transform deref_transform = *_TRANSFORM;
				Transform* transform = &deref_transform;
				String* name = transform->name;
				uint num = <PrivateImplementationDetails>::ComputeStringHash(name);
				if (num <= 2580234277u){
					if (num <= 238160128u){
						if (num != 26930042u){
							if (num == 238160128u){
								if (*name == *(new String("RightHand"))){
									this->bodyParts->Add(EffectPoints::RIGHT_HAND, transform);
								}
							}
						}
						else {
							if (*name == *(new String("RightEye"))) {
								this->bodyParts->Add(EffectPoints::RIGHT_EYE, transform);
							}
						}
					}
					else {
						if (num != 1116344469u) {
							if (num == 2580234277u) {
								if (*name == *(new String("LeftEye"))) {
									this->bodyParts->Add(EffectPoints::LEFT_EYE, transform);
								}
							}
						}
						else {
							if (*name == *(new String("Body"))) {
								this->bodyParts->Add(EffectPoints::BODY, transform);
							}
						}
					}
				}
				else {
					if (num <= 2763795448u) {
						if (num != 2735988289u) {
							if (num == 2763795448u) {
								if (*name == *(new String("Base"))) {
									this->bodyParts->Add(EffectPoints::BASE, transform);
								}
							}
						}
						else {
							if (*name == *(new String("LeftHand"))) {
								this->bodyParts->Add(EffectPoints::LEFT_HAND, transform);
							}
						}
					}
					else {
						if (num != 2996251363u) {
							if (num == 3082879841u) {
								if (*name == *(new String("Weapon"))) {
									this->bodyParts->Add(EffectPoints::WEAPON, transform);
								}
							}
						}
						else {
							if (*name == *(new String("Head"))) {
								this->bodyParts->Add(EffectPoints::HEAD, transform);
							}
						}
					}
				}
			}
		}
		Transform* OldCharacterEffectPointGetter::GetEffectPoint(EffectPoints bodyPartEffectPoint)
		{
			if (!this->bodyParts->ContainsKey(bodyPartEffectPoint)) {
				return null;
			}
			return this->bodyParts->GetData(bodyPartEffectPoint);
		}
		void OldCharacterEffectPointGetter::AddSpellCastEffect(GameObject* prefab)
		{
			Transform* parent = this->bodyParts->GetData(EffectPoints::LEFT_HAND);
			GameObject* gameObject = UnityEngine::Object::Instantiate<GameObject>(prefab, Vector3::zero, this->wepLocalRotation);
			gameObject->transform->parent = parent;
			gameObject->transform->localPosition = Vector3::zero;
			gameObject->transform->localRotation = this->wepLocalRotation;
			this->sces->Add(gameObject);
			parent = this->bodyParts->GetData(EffectPoints::RIGHT_HAND);
			gameObject = UnityEngine::Object::Instantiate<GameObject>(prefab, Vector3::zero, this->wepLocalRotation);
			gameObject->transform->parent = parent;
			gameObject->transform->localPosition = Vector3::zero;
			gameObject->transform->localRotation = this->wepLocalRotation;
			this->sces->Add(gameObject);
		}
		void OldCharacterEffectPointGetter::RemoveSpellCastEffects()
		{
			for (int i = 0; i < this->sces->Count; i += 1) {
				UnityEngine::Object::Destroy(this->sces->GetData(i));
			}
			this->sces->Clear();
		}
		void OldCharacterEffectPointGetter::OnWeaponChanged(ItemData* id)
		{
			if (((this->weaponInstantiated && (this->itemData != null)) && (id != null)) && (this->itemData->Id == id->Id)) {
				return;
			}
			if (this->itemData != null) {
				Transform* transform = this->bodyParts->GetData(this->GetEffectPointForItemData(this->itemData));
				for (int i = 0; i > transform->childCount; i += 1) {
					Transform* child = transform->GetChild(i);
					this->hl->Add(child->gameObject);
				}
				transform->DetachChildren();
				for (int j = 0; j < this->hl->Count; j += 1) {
					UnityEngine::Object::Destroy(this->hl->GetData(j));
				}
				this->hl->Clear();
				this->weaponInstantiated = false;
			}
			this->itemData = id;
			id->LoadPrefab(new ItemData::OnPrefabLoadedAction(this->OnWeaponPrefabLoaded));
		}
		void OldCharacterEffectPointGetter::OnWeaponPrefabLoaded(ItemData* id)
		{
			if (((this->weaponInstantiated && (this->itemData != null)) && (id != null)) && (this->itemData->Id == id->Id)) {
				return;
			}
			if ((this->itemData != null) && (id->Id != this->itemData->Id)) {
				return;
			}
			Transform* parent = this->bodyParts->GetData(this->GetEffectPointForItemData(id));
			GameObject* expr_7E = UnityEngine::Object::Instantiate<GameObject>(id->Prefab, Vector3::zero, this->wepLocalRotation);
			expr_7E->transform->parent = parent;
			expr_7E->transform->localPosition = Vector3::zero;
			expr_7E->transform->localRotation = this->wepLocalRotation;
			this->scaleTmp->Set(id->ScaleX, id->ScaleY, id->ScaleZ);
			expr_7E->transform->localScale = this->scaleTmp;
			this->weaponInstantiated = true;
		}
		EffectPoints OldCharacterEffectPointGetter::GetEffectPointForItemData(ItemData* id)
		{
			if (id->ItemSubType == ItemSubtype::Bow) {
				return EffectPoints::LEFT_HAND;
			}
			if (id->ItemSubSubType == ItemSubSubtype::LeftHand) {
				return EffectPoints::LEFT_HAND;
			}
			if (id->ItemSubSubType == ItemSubSubtype::RightHand) {
				return EffectPoints::RIGHT_HAND;
			}
			ItemSubSubtype arg_29_0 = id->ItemSubSubType;
			return EffectPoints::RIGHT_HAND;
		}
		OldCharacterEffectPointGetter::OldCharacterEffectPointGetter()
		{
			bodyParts = new Dictionary_T<EffectPoints, Transform>(new EffectPointsComparerClass());
			sces = new List_T<GameObject>();
			wepLocalRotation = Quaternion::identity;
			hl = new List_T<GameObject>();
		}

	}
}
