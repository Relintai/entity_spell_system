#ifndef DUNGEON_DATA_LOADER_H
#define DUNGEON_DATA_LOADER_H

#include "DungeonDataLoaderHelper.h"

class DungeonDataLoader 
{
    private:
        static DungeonDataLoader* self;
        Dictionary_T<int, DungeonDataLoaderHelper>* assetDict;
        void OnDestroy();

    public:
        List_T<DungeonDataLoaderHelper>* assets;
        static DungeonDataLoader* getInstance();
        DungeonDataLoaderHelper* GetData(int id);
        List_T<DungeonDataLoaderHelper>* getAllAssets();
        virtual void Start();
        void AddData(int id, String* bundle, String* file);
        bool Contains(String* iconBundle, String* iconFile);
        int Find(String* iconBundle, String* iconFile);
        void RefreshDict();
        void LoadIcons();
        DungeonDataLoader();
};

#endif
