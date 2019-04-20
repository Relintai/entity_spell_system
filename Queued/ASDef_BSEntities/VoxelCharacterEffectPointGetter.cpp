#include "VoxelCharacterEffectPointGetter.h"
namespace BS {
	namespace Player {
		void VoxelCharacterEffectPointGetter::Start(){
			MonoBehaviour::GetComponent<ModelMaker>()->OnModelChanged += new ModelMaker::ModelChangedAction(DELEGATE_FUNC(VoxelCharacterEffectPointGetter::UmaChanged, _1));
			this->we = MonoBehaviour::GetComponent<WorldEntity>();
			this->pd = this->we->PlayerData;
			this->pd->OnWeaponChanged += new PlayerData::OnWeapomChangedAction(DELEGATE_FUNC(VoxelCharacterEffectPointGetter::OnWeaponChanged, _1));
		}
		Transform* VoxelCharacterEffectPointGetter::GetEffectPoint(EffectPoints bodyPartEffectPoint)
		{
			if (!this->bodyParts->ContainsKey(bodyPartEffectPoint)) {
				return null;
			}
			return this->bodyParts->GetData(bodyPartEffectPoint);
		}
		void VoxelCharacterEffectPointGetter::AddSpellCastEffect(GameObject* prefab)
		{
			if (this->umat == null) {
				return;
			}
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
		void VoxelCharacterEffectPointGetter::RemoveSpellCastEffects()
		{
			for (int i = 0; i < this->sces->Count; i += 1) {
				UnityEngine::Object::Destroy(this->sces->GetData(i));
			}
			this->sces->Clear();
		}
		void VoxelCharacterEffectPointGetter::UmaChanged(GameObject* umaGo)
		{
			this->umat = umaGo->transform;
			this->bodyParts->Clear();
			if (this->umat == null) {
				return;
			}
			this->bodyParts->Add(EffectPoints::BASE, MonoBehaviour::transform);
			this->bodyParts->Add(EffectPoints::BODY, this->umat->Find(new String("Motion/B_Pelvis/B_Spine/B_Spine1/B_Spine2")));
			this->bodyParts->Add(EffectPoints::WEAPON, this->umat->Find(new String("Motion/B_Pelvis/B_Spine/B_Spine1/B_Spine2/B_R_Clavicle/B_R_UpperArm/B_R_Forearm/B_R_Hand/Hand")));
			this->bodyParts->Add(EffectPoints::RIGHT_HAND, this->umat->Find(new String("Motion/B_Pelvis/B_Spine/B_Spine1/B_Spine2/B_R_Clavicle/B_R_UpperArm/B_R_Forearm/B_R_Hand/Hand")));
			this->bodyParts->Add(EffectPoints::LEFT_HAND, this->umat->Find(new String("Motion/B_Pelvis/B_Spine/B_Spine1/B_Spine2/B_L_Clavicle/B_L_UpperArm/B_L_Forearm/B_L_Hand/Hand")));
			this->bodyParts->Add(EffectPoints::HEAD, this->umat->Find(new String("Motion/B_Pelvis/B_Spine/B_Spine1/B_Spine2/B_Neck/B_Head")));
			this->bodyParts->Add(EffectPoints::RIGHT_EYE, this->umat->Find(new String("Motion/B_Pelvis/B_Spine/B_Spine1/B_Spine2/B_Neck/B_Head")));
			this->bodyParts->Add(EffectPoints::LEFT_EYE, this->umat->Find(new String("Motion/B_Pelvis/B_Spine/B_Spine1/B_Spine2/B_Neck/B_Head")));
			if (this->itemData != null) {
				DELEGATE_INVOKE(this->OnWeaponChanged, this->itemData);
			}
		}
		void VoxelCharacterEffectPointGetter::OnWeaponChanged(ItemData* id)
		{
			if (this->umat == null) {
				this->itemData = id;
				return;
			}
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
		void VoxelCharacterEffectPointGetter::OnWeaponPrefabLoaded(ItemData* id)
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
		EffectPoints VoxelCharacterEffectPointGetter::GetEffectPointForItemData(ItemData* id)
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
		VoxelCharacterEffectPointGetter::VoxelCharacterEffectPointGetter()
		{
			bodyParts = new Dictionary_T<EffectPoints, Transform>(new EffectPointsComparerClass());
			sces = new List_T<GameObject>();
			wepLocalRotation = Quaternion::identity;
			hl = new List_T<GameObject>();
		}

	}
}
