#ifndef EFFECT_LOADER_H
#define EFFECT_LOADER_H

#include "EffectLoaderHelper.h"

class EffectLoader 
{
    private:
        static EffectLoader* self;
        Dictionary_T<int, EffectLoaderHelper>* assetDict;
        void OnDestroy();


    public:
        List_T<EffectLoaderHelper>* assets;
        static EffectLoader* getInstance();
        EffectLoaderHelper* GetData(int id);
        List_T<EffectLoaderHelper>* getAllAssets();
        virtual void Start();
        void AddData(int id, String* bundle, String* file);
        bool Contains(String* iconBundle, String* iconFile);
        int Find(String* iconBundle, String* iconFile);
        void RefreshDict();
        void LoadIcons();
        EffectLoader();
};

#endif
