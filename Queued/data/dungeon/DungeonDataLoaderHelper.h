#ifndef DUNGEON_DATA_LOADER_H
#define DUNGEON_DATA_LOADER_H

#include "BSMesh.h"
#include "BSMeshMergeData.h"

class DungeonDataLoaderHelper : public virtual Object{
	private:
		int id;
		String* bundle;
		String* file;
		BSMesh* mesh;
		void OnAssetLoaded(BaseAssetBundleHelper* h);

	public:
		DELEGATE(void, DungeonDataLoaderHelper*) AssetLoadedAction;
		void addOnAssetLoadedEvent(DungeonDataLoaderHelper::AssetLoadedAction* value);
		void removeOnAssetLoadedEvent(DungeonDataLoaderHelper::AssetLoadedAction* value);
		int getID();
		void setID(int value);
		void setBundle(String* value);
		String* getFile();
		void setFile(String* value);
		BSMesh* getMesh();
		void setMesh(BSMesh* value);
		DungeonDataLoaderHelper();
		DungeonDataLoaderHelper(int id, String* bundle, String* file);
		void RegisterOnAssetLoaded(DungeonDataLoaderHelper::AssetLoadedAction* callback);
		void Load();
};

#endif
