#include "CharacterEffectPointGetter.h"
namespace BS {
	namespace Player {
		void CharacterEffectPointGetter::Start(){
			this->owner = MonoBehaviour::GetComponent<WorldEntity>();
			this->pd = this->owner->PlayerData;
			this->pd->OnWeaponChanged += new PlayerData::OnWeapomChangedAction(DELEGATE_FUNC(CharacterEffectPointGetter::OnWeaponChanged, _1));
			MonoBehaviour::GetComponent<PlayerGraphicBuilder>()->RegisterOnGraphicBuildFinished(new PlayerGraphicBuilder::OnCharaterGraphicBuildFinishedAction(DELEGATE_FUNC(CharacterEffectPointGetter::OnGraphicBuilt, _1)));
		}
		void CharacterEffectPointGetter::OnGraphicBuilt(GameObject* go)
		{
			this->bodyParts->Clear();
			this->bodyParts->Add(EffectPoints::WEAPON, go->transform->Find(this->weaponPath));
			this->bodyParts->Add(EffectPoints::BASE, go->transform->Find(this->basePath));
			this->bodyParts->Add(EffectPoints::BODY, go->transform->Find(this->bodyPath));
			this->bodyParts->Add(EffectPoints::RIGHT_HAND, go->transform->Find(this->rightHandPath));
			this->bodyParts->Add(EffectPoints::LEFT_HAND, go->transform->Find(this->leftHandPath));
			this->bodyParts->Add(EffectPoints::HEAD, go->transform->Find(this->headPath));
			this->bodyParts->Add(EffectPoints::RIGHT_EYE, go->transform->Find(this->rightEyePath));
			this->bodyParts->Add(EffectPoints::LEFT_EYE, go->transform->Find(this->leftEyePath));
		}
		Transform* CharacterEffectPointGetter::GetEffectPoint(EffectPoints bodyPartEffectPoint)
		{
			if (!this->bodyParts->ContainsKey(bodyPartEffectPoint)) {
				return null;
			}
			return this->bodyParts->GetData(bodyPartEffectPoint);
		}
		void CharacterEffectPointGetter::AddSpellCastEffect(GameObject* prefab)
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
		void CharacterEffectPointGetter::RemoveSpellCastEffects()
		{
			for (int i = 0; i < this->sces->Count; i += 1) {
				UnityEngine::Object::Destroy(this->sces->GetData(i));
			}
			this->sces->Clear();
		}
		void CharacterEffectPointGetter::OnWeaponChanged(ItemData* id)
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
		void CharacterEffectPointGetter::OnWeaponPrefabLoaded(ItemData* id)
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
		EffectPoints CharacterEffectPointGetter::GetEffectPointForItemData(ItemData* id)
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
		CharacterEffectPointGetter::CharacterEffectPointGetter()
		{
			bodyParts = new Dictionary_T<EffectPoints, Transform>(new EffectPointsComparerClass());
			weaponPath = new String("");
			basePath = new String("Root");
			bodyPath = new String("Root/Hip/Spine0/Spine1");
			rightHandPath = new String("Root/Hip/Spine0/Spine1/Spine2/RightUpperArm/RightLowerArm/RightHand/RightHandAttach");
			leftHandPath = new String("Root/Hip/Spine0/Spine1/Spine2/LeftUpperArm/LeftLowerArm/LeftHand/LeftHandAttach");
			headPath = new String("Root/Hip/Spine0/Spine1/Spine2/Head");
			rightEyePath = new String("Root/Hip/Spine0/Spine1/Spine2/Head");
			leftEyePath = new String("Root/Hip/Spine0/Spine1/Spine2/Head");
			sces = new List_T<GameObject>();
			wepLocalRotation = Quaternion::identity;
			hl = new List_T<GameObject>();
		}

	}
}
