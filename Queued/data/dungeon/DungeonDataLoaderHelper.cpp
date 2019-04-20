#include "DungeonDataLoaderHelper.h"

//Delegate declaration moved to header file
void DungeonDataLoaderHelper::addOnAssetLoadedEvent(DungeonDataLoaderHelper::AssetLoadedAction* value){
	DungeonDataLoaderHelper::AssetLoadedAction* assetLoadedAction = this->OnAssetLoadedEvent;
	DungeonDataLoaderHelper::AssetLoadedAction* assetLoadedAction2;
	do{
		assetLoadedAction2 = assetLoadedAction;
		DungeonDataLoaderHelper::AssetLoadedAction* value2 = (DungeonDataLoaderHelper::AssetLoadedAction*)(Delegate::Combine(assetLoadedAction2, value));
		assetLoadedAction = Interlocked::CompareExchange<DungeonDataLoaderHelper::AssetLoadedAction*>(this->OnAssetLoadedEvent, value2, assetLoadedAction2);
	}
	while (*assetLoadedAction != *assetLoadedAction2);
}

void DungeonDataLoaderHelper::removeOnAssetLoadedEvent(DungeonDataLoaderHelper::AssetLoadedAction* value)
{
	DungeonDataLoaderHelper::AssetLoadedAction* assetLoadedAction = this->OnAssetLoadedEvent;
	DungeonDataLoaderHelper::AssetLoadedAction* assetLoadedAction2;
	do {
		assetLoadedAction2 = assetLoadedAction;
		DungeonDataLoaderHelper::AssetLoadedAction* value2 = (DungeonDataLoaderHelper::AssetLoadedAction*)(Delegate::Remove(assetLoadedAction2, value));
		assetLoadedAction = Interlocked::CompareExchange<DungeonDataLoaderHelper::AssetLoadedAction*>(this->OnAssetLoadedEvent, value2, assetLoadedAction2);
	}
	while (*assetLoadedAction != *assetLoadedAction2);
}

int DungeonDataLoaderHelper::getID()
{
	return this->id;
}

void DungeonDataLoaderHelper::setID(int value)
{
	this->id = value;
}

String* DungeonDataLoaderHelper::getBundle()
{
	return this->bundle;
}

void DungeonDataLoaderHelper::setBundle(String* value)
{
	this->bundle = value;
}

String* DungeonDataLoaderHelper::getFile()
{
	return this->file;
}

void DungeonDataLoaderHelper::setFile(String* value)
{
	this->file = value;
}

BSMesh* DungeonDataLoaderHelper::getMesh()
{
	return this->mesh;
}

void DungeonDataLoaderHelper::setMesh(BSMesh* value)
{
	this->mesh = value;
}

DungeonDataLoaderHelper::DungeonDataLoaderHelper()
{
	file = new String("Warrior");
	bundle = new String("icons/icons");
}

DungeonDataLoaderHelper::DungeonDataLoaderHelper(int id, String* bundle, String* file)
{
	this->id = id;
	this->bundle = bundle;
	this->file = file;
}

void DungeonDataLoaderHelper::RegisterOnAssetLoaded(DungeonDataLoaderHelper::AssetLoadedAction* callback)
{
	if (this->getMesh() != null) {
		callback(this);
		return;
	}
	this->addOnAssetLoadedEvent(callback);
}

void DungeonDataLoaderHelper::OnAssetLoaded(BaseAssetBundleHelper* h)
{
	GameObject* asset = as_cast<AssetBundleFileLoadHelper*>(h)->AssetLoadOperation->GetAsset<GameObject>();
	this->mesh = asset->GetComponent<BSMeshMergeData>()->Mesh;
	if (this->OnAssetLoadedEvent != null) {
		DELEGATE_INVOKE(this->OnAssetLoadedEvent, this);
		this->OnAssetLoadedEvent = null;
	}
}

void DungeonDataLoaderHelper::Load()
{
	if ((this->bundle == *(new String(""))) || (this->file == *(new String("")))) {
		return;
	}
	if (DataMgr::Instance != null) {
		DataMgr::Instance->RequestAsset(this->bundle, this->file, /*ERROR: Cannot translate: System.NotImplementedException: typeOfExpression: --> TODO: --> http://www.boost.org/doc/libs/1_55_0/doc/html/typeof/tuto.html. Node: ICSharpCode.NRefactory.CSharp.TypeOfExpression*/, new DataMgr::DataLoadFinishAction(this->OnAssetLoaded), null);
	}
}

