#include "DungeonData.h"

int DungeonData::getId(){
    return this->id;
}

void DungeonData::setId(int value)
{
    this->id = value;
}

String* DungeonData::getDungeonAssetAssetBundleName()
{
    return this->dungeonAssetAssetBundleName;
}

void DungeonData::setDungeonAssetAssetBundleName(String* value)
{
    this->dungeonAssetAssetBundleName = value;
}

String* DungeonData::getDungeonAssetAssetName()
{
    return this->dungeonAssetAssetname;
}

void DungeonData::setDungeonAssetAssetName(String* value)
{
    this->dungeonAssetAssetname = value;
}

String* DungeonData::getMaterialAssetBundleName()
{
    return this->materialAssetBundleName;
}

void DungeonData::setMaterialAssetBundleName(String* value)
{
    this->materialAssetBundleName = value;
}

String* DungeonData::getMaterialAssetName()
{
    return this->materialAssetName;
}

void DungeonData::setMaterialAssetName(String* value)
{
    this->materialAssetName = value;
}

String* DungeonData::getTextureAssetBundleName()
{
    return this->textureAssetBundleName;
}

void DungeonData::setTextureAssetBundleName(String* value)
{
    this->textureAssetBundleName = value;
}

String* DungeonData::getTextureAssetName()
{
    return this->textureAssetName;
}

void DungeonData::setTextureAssetName(String* value)
{
    this->textureAssetName = value;
}

List_T<int>* DungeonData::getMobIds()
{
    return this->mobIds;
}

List_T<MobGroup>* DungeonData::getMobGroups()
{
    return this->mobGroups;
}

Color* DungeonData::getOverlayColor()
{
    return this->overlayColor;
}

void DungeonData::setOverlayColor(Color* value)
{
    this->overlayColor = value;
}

void DungeonData::Set(int id, String* dungeonAssetAssetBundleName, String* dungeonAssetAssetname, String* materialAssetBundleName, String* materialAssetName, String* textureAssetBundleName, String* textureAssetName, List_T<int>* mobIds, List_T<MobGroup>* mobGroups, Color* overlayColor)
{
    this->id = id;
    this->dungeonAssetAssetBundleName = dungeonAssetAssetBundleName;
    this->dungeonAssetAssetname = dungeonAssetAssetname;
    this->materialAssetBundleName = materialAssetBundleName;
    this->materialAssetName = materialAssetName;
    this->textureAssetBundleName = textureAssetBundleName;
    this->textureAssetName = textureAssetName;
    this->mobIds = mobIds;
    this->mobGroups = mobGroups;
    this->overlayColor = overlayColor;
}

void DungeonData::LoadMaterial(DungeonData::LoadFinishedAction* action)
{
}

void DungeonData::RemoveMaterialCallback(DungeonData::LoadFinishedAction* action)
{
    this->onMaterialLoaded = (DungeonData::LoadFinishedAction*)(Delegate::Remove(this->onMaterialLoaded, action));
}

void DungeonData::OnMaterialLoaded(BaseAssetBundleHelper* h)
{
    AssetBundleFileLoadHelper* assetBundleFileLoadHelper = as_cast<AssetBundleFileLoadHelper*>(h);
    this->sharedMaterial = assetBundleFileLoadHelper->AssetLoadOperation->GetAsset<Material>();
    if (this->onMaterialLoaded != null) {
        DELEGATE_INVOKE(this->onMaterialLoaded, this);
        this->onMaterialLoaded = null;
    }
}

void DungeonData::OnTextureLoaded(BaseAssetBundleHelper* h)
{
    AssetBundleFileLoadHelper* assetBundleFileLoadHelper = as_cast<AssetBundleFileLoadHelper*>(h);
    this->sharedTexture = assetBundleFileLoadHelper->AssetLoadOperation->GetAsset<Texture2D>();
    if (this->onTextureLoaded != null) {
        DELEGATE_INVOKE(this->onTextureLoaded, this);
        this->onTextureLoaded = null;
    }
}

void DungeonData::ApplyEffectsToMaterial()
{
    this->LoadMaterial(new DungeonData::LoadFinishedAction(DELEGATE_FUNC(DungeonData::AfterMaterialLoaded, _1)));
}

void DungeonData::AfterMaterialLoaded(DungeonData* d)
{
    if ((this->sharedTexture == null) || (this->sharedMaterial == null)) {
        return;
    }
    this->sharedMaterial->mainTexture = this->sharedTexture;
}

int DungeonData::GetRandomMob()
{
    if (this->getMobIds()->Count == 0) {
        return 0;
    }
    return this->getMobIds()->GetData(UnityEngine::Random::Range(0, this->getMobIds()->Count));
}

MobGroup* DungeonData::GetRandomMobGroup()
{
    if (this->getMobGroups()->Count == 0) {
        return null;
    }
    return this->getMobGroups()->GetData(UnityEngine::Random::Range(0, this->getMobGroups()->Count));
}

void DungeonData::ReleaseRenderTexture()
{
    if (this->rt != null) {
        this->rt->Release();
        this->rt = null;
    }
}

DungeonData::DungeonData()
{
    mobIds = new List_T<int>();
    mobGroups = new List_T<MobGroup>();
}

