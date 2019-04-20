#include "EffectLoaderHelper.h"

//Delegate declaration moved to header file
void EffectLoaderHelper::addOnAssetLoadedEvent(EffectLoaderHelper::AssetLoadedAction* value){
	EffectLoaderHelper::AssetLoadedAction* assetLoadedAction = this->OnAssetLoadedEvent;
	EffectLoaderHelper::AssetLoadedAction* assetLoadedAction2;
	do{
		assetLoadedAction2 = assetLoadedAction;
		EffectLoaderHelper::AssetLoadedAction* value2 = (EffectLoaderHelper::AssetLoadedAction*)(Delegate::Combine(assetLoadedAction2, value));
		assetLoadedAction = Interlocked::CompareExchange<EffectLoaderHelper::AssetLoadedAction*>(this->OnAssetLoadedEvent, value2, assetLoadedAction2);
	}
	while (*assetLoadedAction != *assetLoadedAction2);
}

void EffectLoaderHelper::removeOnAssetLoadedEvent(EffectLoaderHelper::AssetLoadedAction* value)
{
	EffectLoaderHelper::AssetLoadedAction* assetLoadedAction = this->OnAssetLoadedEvent;
	EffectLoaderHelper::AssetLoadedAction* assetLoadedAction2;
	do {
		assetLoadedAction2 = assetLoadedAction;
		EffectLoaderHelper::AssetLoadedAction* value2 = (EffectLoaderHelper::AssetLoadedAction*)(Delegate::Remove(assetLoadedAction2, value));
		assetLoadedAction = Interlocked::CompareExchange<EffectLoaderHelper::AssetLoadedAction*>(this->OnAssetLoadedEvent, value2, assetLoadedAction2);
	}
	while (*assetLoadedAction != *assetLoadedAction2);
}

int EffectLoaderHelper::getID()
{
	return this->id;
}

void EffectLoaderHelper::setID(int value)
{
	this->id = value;
}

String* EffectLoaderHelper::getBundle()
{
	return this->bundle;
}

void EffectLoaderHelper::setBundle(String* value)
{
	this->bundle = value;
}

String* EffectLoaderHelper::getFile()
{
	return this->file;
}

void EffectLoaderHelper::setFile(String* value)
{
	this->file = value;
}

GameObject* EffectLoaderHelper::getAsset()
{
	return this->asset;
}

void EffectLoaderHelper::setAsset(GameObject* value)
{
	this->asset = value;
}

EffectLoaderHelper::EffectLoaderHelper()
{
	file = new String("Warrior");
	bundle = new String("icons/icons");
}

EffectLoaderHelper::EffectLoaderHelper(int id, String* bundle, String* file)
{
	this->id = id;
	this->bundle = bundle;
	this->file = file;
}

void EffectLoaderHelper::RegisterOnAssetLoaded(EffectLoaderHelper::AssetLoadedAction* callback)
{
	if (this->getAsset() != null) {
		callback(this);
		return;
	}
	this->addOnAssetLoadedEvent(callback);
}

void EffectLoaderHelper::OnAssetLoaded(BaseAssetBundleHelper* h)
{
	AssetBundleFileLoadHelper* assetBundleFileLoadHelper = as_cast<AssetBundleFileLoadHelper*>(h);
	this->asset = assetBundleFileLoadHelper->AssetLoadOperation->GetAsset<GameObject>();
	if (this->OnAssetLoadedEvent != null) {
		DELEGATE_INVOKE(this->OnAssetLoadedEvent, this);
		this->OnAssetLoadedEvent = null;
	}
}

void EffectLoaderHelper::Load()
{
	if ((this->bundle == *(new String(""))) || (this->file == *(new String("")))) {
		return;
	}
	if (DataMgr::Instance != null) {
		DataMgr::Instance->RequestAsset(this->bundle, this->file, /*ERROR: Cannot translate: System.NotImplementedException: typeOfExpression: --> TODO: --> http://www.boost.org/doc/libs/1_55_0/doc/html/typeof/tuto.html. Node: ICSharpCode.NRefactory.CSharp.TypeOfExpression*/, new DataMgr::DataLoadFinishAction(this->OnAssetLoaded), null);
	}
}

