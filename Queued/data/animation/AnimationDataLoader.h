#ifndef ANIMATION_DATA_LOADER_H
#define ANIMATION_DATA_LOADER_H

#include "PAnimationData.h"
#include "AnimationData.h"

class AnimationDataLoader 
{
    private:
        String* folder;
        String* loadFile;
        List_T<PAnimationData>* data;
        static AnimationDataLoader* self;
        void Start();
        void SaveNow();
        void RefreshList();
        void OnAnimationDataLoaded(BaseAssetBundleHelper* h);

    public:
        bool load;
        bool loadEditor;
        static AnimationDataLoader* getInstance();
        void Load();
        void LoadEditor();
        GameObject* getAnimationWithName(String* name);
        GameObject* getAnimationWithId(int id);
        AnimationDataLoader();
};

#endif
