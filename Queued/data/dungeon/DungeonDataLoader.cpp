#include "DungeonDataLoader.h"

DungeonDataLoader* DungeonDataLoader::self;
DungeonDataLoader* DungeonDataLoader::getInstance(){
	return DungeonDataLoader::self;
}

DungeonDataLoaderHelper* DungeonDataLoader::GetData(int id)
{
	return this->assetDict->GetData(id);
}

List_T<DungeonDataLoaderHelper>* DungeonDataLoader::getAllAssets()
{
	return this->assets;
}

void DungeonDataLoader::Start()
{
	DungeonDataLoader::self = this;
	this->RefreshDict();
	this->LoadIcons();
}

void DungeonDataLoader::OnDestroy()
{
	DungeonDataLoader::self = null;
}

void DungeonDataLoader::AddData(int id, String* bundle, String* file)
{
	DungeonDataLoaderHelper* item = new DungeonDataLoaderHelper(id, bundle, file);
	this->assets->Add(item);
}

bool DungeonDataLoader::Contains(String* iconBundle, String* iconFile)
{
	for (int i = 0; i < this->assets->Count; i += 1) {
		DungeonDataLoaderHelper* dungeonDataLoaderHelper = this->assets->GetData(i);
		if (dungeonDataLoaderHelper->getBundle()->Equals(iconBundle) && dungeonDataLoaderHelper->getFile()->Equals(iconFile)) {
			return true;
		}
	}
	return false;
}

int DungeonDataLoader::Find(String* iconBundle, String* iconFile)
{
	for (int i = 0; i < this->assets->Count; i += 1) {
		DungeonDataLoaderHelper* dungeonDataLoaderHelper = this->assets->GetData(i);
		if (dungeonDataLoaderHelper->getBundle()->Equals(iconBundle) && dungeonDataLoaderHelper->getFile()->Equals(iconFile)) {
			return i;
		}
	}
	return -1;
}

void DungeonDataLoader::RefreshDict()
{
	this->assetDict->Clear();
	for (int i = 0; i < this->assets->Count; i += 1) {
		this->assetDict->Add(this->assets->GetData(i)->ID, this->assets->GetData(i));
	}
}

void DungeonDataLoader::LoadIcons()
{
	for (int i = 0; i < this->assets->Count; i += 1) {
		this->assets->GetData(i)->Load();
	}
}

DungeonDataLoader::DungeonDataLoader()
{
	assets = new List_T<DungeonDataLoaderHelper>();
	assetDict = new Dictionary_T<int, DungeonDataLoaderHelper>();
}

