#include "EffectLoader.h"

EffectLoader* EffectLoader::self;
EffectLoader* EffectLoader::getInstance(){
	return EffectLoader::self;
}

EffectLoaderHelper* EffectLoader::GetData(int id)
{
	return this->assetDict->GetData(id);
}

List_T<EffectLoaderHelper>* EffectLoader::getAllAssets()
{
	return this->assets;
}

void EffectLoader::Start()
{
	EffectLoader::self = this;
	this->RefreshDict();
	this->LoadIcons();
}

void EffectLoader::OnDestroy()
{
	EffectLoader::self = null;
}

void EffectLoader::AddData(int id, String* bundle, String* file)
{
	EffectLoaderHelper* item = new EffectLoaderHelper(id, bundle, file);
	this->assets->Add(item);
}

bool EffectLoader::Contains(String* iconBundle, String* iconFile)
{
	for (int i = 0; i < this->assets->Count; i += 1) {
		EffectLoaderHelper* effectLoaderHelper = this->assets->GetData(i);
		if (effectLoaderHelper->getBundle()->Equals(iconBundle) && effectLoaderHelper->getFile()->Equals(iconFile)) {
			return true;
		}
	}
	return false;
}

int EffectLoader::Find(String* iconBundle, String* iconFile)
{
	for (int i = 0; i < this->assets->Count; i += 1) {
		EffectLoaderHelper* effectLoaderHelper = this->assets->GetData(i);
		if (effectLoaderHelper->getBundle()->Equals(iconBundle) && effectLoaderHelper->getFile()->Equals(iconFile)) {
			return i;
		}
	}
	return -1;
}

void EffectLoader::RefreshDict()
{
	this->assetDict->Clear();
	for (int i = 0; i < this->assets->Count; i += 1) {
		this->assetDict->Add(this->assets->GetData(i)->ID, this->assets->GetData(i));
	}
}

void EffectLoader::LoadIcons()
{
	for (int i = 0; i < this->assets->Count; i += 1) {
		this->assets->GetData(i)->Load();
	}
}

EffectLoader::EffectLoader()
{
	assets = new List_T<EffectLoaderHelper>();
	assetDict = new Dictionary_T<int, EffectLoaderHelper>();
}

